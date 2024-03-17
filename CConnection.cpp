#pragma hdrstop
#include "CConnection.h"
#include "CElektronBank.h"
#include "engine-req.h"
#include "resources.h"
#include "settings.h"
#include "3dmath.h"
#include "simfuncts.h"
#include "CSimMgr.h"

using namespace irr;

CConnection::CConnection(CAtom *p_A1, CAtom *p_A2, f32 scale)
{
        pA1=p_A1;
        pA2=p_A2;
        fScale=scale;
        fDistance=pow(scale/4,2);

        node=smgr->addMeshSceneNode(r_box1_mesh->getMesh(0));

        f32 msize1=pA1->getElementData().bbsize;
        f32 msize2=pA2->getElementData().bbsize;

        core::vector3df possa1=getTargetDistance(pA1->getPosition(), pA2->getPosition(),msize1);
        core::vector3df possa2=getTargetDistance(pA2->getPosition(), pA1->getPosition(),msize2);

        core::line3d<f32> line(possa1, possa2 );

        node->setPosition(line.getMiddle() );
        node->setMaterialTexture( 0, r_bank_texture );
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setScale(core::vector3df(scale, scale, scale));
        node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

        texture=-1;

        changing=false;
        counting=true;
        conn_double=-1;
        freeze=0;

        chtime=0;
}

CConnection::~CConnection(void)
{
        node->remove();
}

void CConnection::Step(f32 time)
{
        /*if( changing==true )
        {
                chtime+=time;
        }

        if( changing==true && connections.size()==0 )
                changing=false;*/

        if( freeze>0 )
        {
                freeze-=time;
                return;
        }

        {
                StepBanks(time,banks1,connections1, pA1, pA2 );
                StepBanks(time,banks2,connections2, pA2, pA1 );
        }

        f32 msize1=pA1->getElementData().bbsize;
        f32 msize2=pA2->getElementData().bbsize;

        core::vector3df possa1=getTargetDistance(pA1->getPosition(), pA2->getPosition(),msize1);
        core::vector3df possa2=getTargetDistance(pA2->getPosition(), pA1->getPosition(),msize2);

        core::line3d<f32> line(possa1, possa2 );

        //driver->draw3DLine(line.start, line.end);

        core::vector3df dest=line.getMiddle();

        core::vector3df oldpos=node->getPosition()-dest;

        core::line3d<f32> line2(node->getPosition(), dest );

        //driver->draw3DLine(line2.start, line2.end);

        //core::vector3df destrot=getRotationToTarget(node->getPosition(), dest);

        core::vector3df newpos;

        {
                f32 stepp1=catom_connection_centerscale;
                f32 stepp2=line2.getLength()*time;
                f32 step=std::min(stepp1*stepp2 , time*time);

                newpos=getTargetDistance( node->getPosition(), dest, step);//getTarget(node->getPosition(), destrot, step );

                node->setPosition(newpos);
        }

        core::vector3df rot=getRotationToTarget(dest, pA1->getPosition());
        node->setRotation(rot);

        if( connections.size()>0 )
        {
                //in die Mitte bringen
                core::line3d<f32> linep1(node->getPosition(), possa1 );
                core::line3d<f32> linep2(node->getPosition(), possa2 );

                f32 dist=linep1.getLengthSQ()-linep2.getLengthSQ();
                f32 step=std::min( dist*time*catom_connection_forcescale, time*2 );

                //if( changing==true )
                //        step*=2;


                node->setPosition( getTargetDistance( node->getPosition(), possa1, step) );
        }


        //L‰nge setzten
        node->setScale(core::vector3df(fScale, fScale , line.getLength()*catom_connection_length));


        //Abstoﬂen von anderen Verbindungen
        for(size_t i=0;i<connections.size();++i)
        {
                core::line3d<f32> line(connections[i]->getNodePosition(), newpos );
                f32 dist=line.getLength();

                core::vector3df rot=getRotationToTarget(node->getPosition(), connections[i]->getNode()->getPosition() );

                f32 backdrift;
                //if( changing==true )
                //        backdrift=catom_connection_backdrift_changing;
                //else
                        backdrift=catom_connection_backdrift;

                f32 step=std::min( (1.0f/dist)*time*backdrift, time);
                step*=-1;
                newpos=getTarget(node->getPosition(), rot, step );

                node->setPosition(newpos);
        }


        possa1=pA1->getPosition();
        possa2=pA2->getPosition();
        line.start=possa1;
        line.end=possa2;

        //Anziehung der Kerne

        // atom1 zu atom2
        f32 asize=pA1->getElementData().bbsize+pA2->getElementData().bbsize;

        f32 destabs=pow(asize+catom_inter_connection_distance_multi,2);
        destabs=line.getLengthSQ()-destabs;

        if( destabs>catom_connection_visible_distance && destabs>catom_connection_transparent_distance )
                node->setVisible(false);
        else if( destabs>catom_connection_visible_distance && destabs<catom_connection_transparent_distance )
        {
                float transp_part=catom_connection_transparent_distance-catom_connection_visible_distance;
                float perc=(destabs-catom_connection_visible_distance)/(transp_part/100);

                int i_perc=100-(int)perc;

                if( texture!=i_perc  && i_perc<100)
                {
                        node->setMaterialTexture( 0, r_pc_bank_textures[i_perc] );
                        texture=i_perc;
                }
                node->setVisible(true);
        }
        else
        {
                if( texture!=-1 )
                {
                        node->setMaterialTexture( 0, r_bank_texture );
                        texture=-1;
                }
                node->setVisible(true);
        }


        f32 step=destabs*time*catom_inter_connection_forcescale;
        if( step>0 )
                step=std::min(step, time );
        else
                step=std::max(step, -1*time);

        pA1->setPosition( getTargetDistance( possa1, possa2, step) );
        pA2->setPosition( getTargetDistance( possa2, possa1, step) );

        /*if(>pow(,2) )
        {
                step=std::min( line.getLengthSQ()*catom_inter_connection_forcescale*time, time);
                
                core::vector3df rotA1=getRotationToTarget(possa1, possa2);
                core::vector3df rotA2=getRotationToTarget(possa2, possa1);

                core::vector3df newA1pos=getTarget(possa1, rotA1, step );
                core::vector3df newA2pos=getTarget(possa2, rotA2, step );

                pA1->setPosition(newA1pos);
                pA2->setPosition(newA2pos);
        }
        else
        {
                step=std::min( line.getLengthSQ()*catom_inter_connection_forcescale*time, time);
                step*=-1;
                
                core::vector3df rotA1=getRotationToTarget(possa1, possa2);
                core::vector3df rotA2=getRotationToTarget(possa2, possa1);

                core::vector3df newA1pos=getTarget(possa1, rotA1, step );
                core::vector3df newA2pos=getTarget(possa2, rotA2, step );

                pA1->setPosition(newA1pos);
                pA2->setPosition(newA2pos);
        } */



        core::line3d<f32> line1(oldpos, node->getPosition()-dest );

        position=node->getPosition();

        /*if(changing==true && line1.getLengthSQ() < catom_connection_change_limit*time && chtime>10000 )
        {
                changing=false;
                for(size_t i=0;i<connections.size();++i)
                {
                        connections[i]->setChanging(false);
                }
        } */
}

irr::scene::ISceneNode* CConnection::getNode(void)
{
        return node;
}

void CConnection::addOtherConnection(CConnection *connection)
{
        connections.push_back(connection);
}

CAtom* CConnection::getAtom1(void)
{
        return pA1;
}

CAtom* CConnection::getAtom2(void)
{
        return pA2;
}

void CConnection::addBankA1(CElektronBank* bank)
{
        banks1.push_back(bank);
}

void CConnection::addBankA2(CElektronBank* bank)
{
        banks2.push_back(bank);
}

void CConnection::addConnectionA1(CConnection* connection)
{
        connections1.push_back(connection);
}

void CConnection::addConnectionA2(CConnection* connection)
{
        connections2.push_back(connection);
}

void CConnection::StepBanks(_f32 time, const std::vector<CElektronBank*> &banks, const  std::vector<CConnection*> &connections, CAtom* a1, CAtom* a2)
{
        std::vector<CAtom*> exclude1,exclude2;
        exclude1.push_back(a1);
        exclude2.push_back(a2);
        size_t num1=a2->getTotalConnectionNum(&exclude1);
        size_t num2=a1->getTotalConnectionNum(&exclude2);
        if( num1>=num2 )
                return;

        //Position im Radius r vom Atom ausrechnen
        f32 core_distance=a1->getElementData().bbsize+catom_bank_distance;
        core::vector3df currpos=getTargetDistance(a1->getPosition(), a2->getPosition(), core_distance);

        core::vector3df oldpos=currpos;

        std::vector<CElektronBank*> t_banks=banks;

        while( t_banks.size()>0 )
        {
                int i=rand()%(int)t_banks.size();

                core::line3d<f32> line(currpos, t_banks[i]->getPosition());
                _f32 dist=-1*catom_bank2connection_force*time*(1.0f/line.getLength());

                if( banks[i]->isFull()==false )
                        dist*=0.5f;

                currpos=getTargetDistance(currpos, t_banks[i]->getPosition(), dist );

                t_banks.erase( t_banks.begin()+i);
        }

        bool doubleconn=false;
        int nconns=0;

        std::vector< CConnection* > t_connections=connections;

        //for(size_t i=0;i<connections.size();++i)
        while( t_connections.size()>0 )
        {
                int i=rand()%(int)t_connections.size();

                if( t_connections[i]->getDouble()!=-1 )
                {
                        doubleconn=true;
                }
                ++nconns;

                CAtom *otherA=t_connections[i]->getAtom1();
                if(otherA==a1)
                        otherA=t_connections[i]->getAtom2();

                /*if( otherA->isCalculatingPlane()==true )
                        continue;*/

                core::line3d<f32> line(a1->getPosition(), otherA->getPosition() );

                if( line.getLengthSQ() <= catom_connection_distance_cap_sq )                        
                {
                        _f32 dist=-1*catom_connection2connection_force*time;

                        //Position der Verbindung ermitteln
                        core::vector3df conn_pos=getTargetDistance(a1->getPosition(), otherA->getPosition(), core_distance);

                        core::line3d<f32> line(currpos, conn_pos);
                        dist*=1.0f/line.getLength();

                        dist=std::max( dist, -time );

                        dist/=otherA->getElementData().elektroneg;

                        currpos=getTargetDistance(currpos, conn_pos, dist);
                }

                t_connections.erase(t_connections.begin()+i) ; 
        }

        if( doubleconn==true && nconns>2 )
        {
                std::vector<CAtom*> exclude;
                exclude.push_back(a1);
                
                if(a1->calculateConnPlane())
                {
                        for(size_t i=0;i<connections.size();++i)
                        {
                                CAtom *otherA=connections[i]->getAtom1();
                                if(otherA==a1)
                                        otherA=connections[i]->getAtom2();

                                otherA->setConnPlane( a1->getConnPlane(), &exclude );
                        }
                }
        }


        //Note: Die Position von a2 muss ver‰ndert werden!

        //Die Position von a2 ausrechenen zur¸ckberechnen

        /*core::vector3df rot=getRotationToTarget(a1->getPosition(), currpos);
        core::line3d<f32> line(a1->getPosition(), a2->getPosition() );

        a2->setPosition(getTarget(a1->getPosition(), rot, line.getLength());*/

        /*{
                core::line3d<f32> line(oldpos, currpos );

                f32 force=a2->CalculateForce2Atom( line.getLength() );

                currpos=getTargetDistance(oldpos, currpos, force );
        } */

        core::line3d<f32> line(a1->getPosition(), a2->getPosition() );
        a2->setPosition( getTargetDistance(a1->getPosition(), currpos, line.getLength() ) );
}

void CConnection::ResetBanks(void)
{
        banks1.clear();
        banks2.clear();
}

core::vector3df CConnection::getNodePosition(void)
{
        return position;
}

core::vector3df CConnection::getPosition(void)
{
        return node->getPosition();
}

void CConnection::setPosition(core::vector3df npos)
{
        CConnection::node->setPosition(npos);
}

void CConnection::setFreeze(int pFreeze)
{
        freeze=pFreeze;
}

bool CConnection::RemoveBank(CElektronBank* bank)
{
        bool found=false;
        for(size_t i=0;i<banks1.size();++i)
        {
                if( banks1[i]==bank )
                {
                        banks1.erase( banks1.begin()+i );
                        found=true;
                }
        }
        for(size_t i=0;i<banks2.size();++i)
        {
                if( banks2[i]==bank )
                {
                        banks2.erase( banks2.begin()+i );
                        found=true;
                }
        }

        return found;
}

bool CConnection::removeConnection(CConnection* connection)
{
        bool found=false;
        for(size_t i=0;i<connections.size();++i)
        {
                if( connections[i]==connection )
                {
                        connections.erase(connections.begin()+i);
                        found=true;
                        break;
                }
        }

        for(size_t i=0;i<connections1.size();++i)
        {
                if( connections1[i]==connection )
                {
                        connections1.erase(connections1.begin()+i);
                        found=true;
                        break;
                }
        }

        for(size_t i=0;i<connections2.size();++i)
        {
                if( connections2[i]==connection )
                {
                        connections2.erase(connections2.begin()+i);
                        found=true;
                        break;
                }
        }

        return found;
}

void CConnection::setChanging(bool b)
{
        changing=b;
}

bool CConnection::isFrozen(void)
{
        if( freeze>0 )
                return true;
        else
                return false;
}

void CConnection::setCounting(bool b)
{
        counting=b;
}

bool CConnection::getCounting(void)
{
        return counting;
}

void CConnection::setDouble(int b)
{
        conn_double=b;
}

int CConnection::getDouble(void)
{
        return conn_double;
}

