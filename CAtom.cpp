#pragma hdrstop
#include "LoadingScreen.h"
#include "CAtom.h"
#include "resources.h"
#include "engine-req.h"
#include "settings.h"
#include "3dmath.h"
#include "RotationAnimator.h"
#include "simfuncts.h"
#include "CSimMgr.h"

//#define NO_ELEKTRONS
#define PRESTEP

const f32 core_phi2=0.0001f;
const f32 core_exp=2;

CAtom::CAtom(sElementData cs_emd, bool bdetailed, int pID, int posx, int posy, int posz, std::string pName)
{
        eldata=cs_emd;
        details=bdetailed;
        name=pName;

        id=pID;

        if(posx<0 )
                --posx;
        if(posy<0)
                --posy;
        if(posz<0)
                --posz;

        f32 minX=posx*sandboxsize.X-sandboxsize.X/2;
        f32 maxX=(posx+1)*sandboxsize.X-sandboxsize.X/2;

        f32 minY=posy*sandboxsize.Y-sandboxsize.Y/2;
        f32 maxY=(posy+1)*sandboxsize.Y-sandboxsize.Y/2;

        f32 minZ=posz*sandboxsize.Z-sandboxsize.Z/2;
        f32 maxZ=(posy+1)*sandboxsize.Z-sandboxsize.Z/2;

        f32 X=(rand()%(int)(maxX-minX)) + minX;
        f32 Y=(rand()%(int)(maxY-minY)) + minY;
        f32 Z=(rand()%(int)(maxZ-minZ)) + minZ;

        position=core::vector3df(X,Y,Z);
        default_position=position;

        Create();

        age=0;
        freeze=0;

        molecule_id=-1;

        num_invconn=0;

        frozen=false;

        conn_plane_activ=false;
        calculated_plane=false;

        visible=true;
}

CAtom::~CAtom(void)
{
        Destroy();
}

void CAtom::Reset(void)
{
        setPosition(  default_position );
}

int CAtom::getID(void)
{
        return id;
}

int CAtom::getMoleculeID(void)
{
        return molecule_id;
}

void CAtom::setMoleculeID(int pID)
{
        molecule_id=pID;
}

void CAtom::Create(void)
{
        if(details==true)
        {
                for(_u32 i=0;i<eldata.num_protons;++i)
                {
                        scene::ISceneNode* node=smgr->addMeshSceneNode(r_proton_mesh->getMesh(0) );
                        core::vector3df position=core::vector3df(rand()%(_u32)sandboxsize.X-sandboxsize.X/2,rand()%(_u32)sandboxsize.Y-sandboxsize.Y/2,rand()%(_u32)sandboxsize.Z-sandboxsize.Z/2);
                        position*=catom_positionscale;
                        node->setPosition(position);
                        node->setMaterialTexture( 0, r_proton_texture );
                        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

                        protons.push_back(new CProton(node) );
                }

                for(_u32 i=0;i<eldata.num_neutrons;++i)
                {
                        scene::ISceneNode* node=smgr->addMeshSceneNode(r_neutron_mesh->getMesh(0) );
                        core::vector3df position=core::vector3df(rand()%(_u32)sandboxsize.X-sandboxsize.X/2,rand()%(_u32)sandboxsize.Y-sandboxsize.Y/2,rand()%(_u32)sandboxsize.Z-sandboxsize.Z/2 );
                        position*=catom_positionscale;
                        node->setPosition(position);
                        node->setMaterialTexture( 0, r_neutron_texture );
                        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

                        neutrons.push_back(new CNeutron(node) );
                }

                for(size_t i=0;i<neutrons.size();++i)
                {
                        for(size_t u=0;u<neutrons.size();++u)
                        {
                                if(u!=i)
                                        neutrons[i]->addOtherNeutron(neutrons[u]->getNode());
                        }
                        for(size_t u=0;u<protons.size();++u)
                        {
                                neutrons[i]->addOtherProton(protons[u]->getNode());
                        }
                }

                for(size_t i=0;i<protons.size();++i)
                {
                        for(size_t u=0;u<protons.size();++u)
                        {
                                if(u!=i)
                                        protons[i]->addOtherProton(protons[u]->getNode());
                        }
                        for(size_t u=0;u<neutrons.size();++u)
                        {
                                protons[i]->addOtherNeutron(neutrons[u]->getNode());
                        }
                }
        }
        else
        {
                corenode=smgr->addMeshSceneNode( r_atom1u_mesh->getMesh(0) );
                corenode->setScale(core::vector3df(eldata.modelsize, eldata.modelsize,eldata.modelsize));

                corenode->setMaterialTexture( 0, eldata.texture );
                corenode->setMaterialFlag(irr::video::EMF_LIGHTING, false);

                corenode->setPosition(position);

                eldata.bbsize=(r_atom1u_mesh->getBoundingBox().MaxEdge.Y-r_atom1u_mesh->getBoundingBox().MinEdge.Y)/2;
                eldata.bbsize*=eldata.modelsize;

                _u32 uOEls=getoelektrons(eldata.num_elektrons);
                for(size_t i=0;i<(size_t)(uOEls/2);++i)
                {
                        CElektronBank* bank=new CElektronBank(position, true, eldata.bbsize+catom_bank_distance, eldata.modelsize, this);
                        banks.push_back(bank);
                }
                if(uOEls%2!=0)
                {
                        CElektronBank* bank=new CElektronBank(position, false, eldata.bbsize+catom_bank_distance, eldata.modelsize, this);
                        banks.push_back(bank);
                }
                        
                        

                for(size_t i=0;i<banks.size();++i)
                        for(size_t t=0;t<banks.size();++t)
                                if(t!=i)
                                        banks[i]->addOtherBank(banks[t]);
        }

#ifndef NO_ELEKTRONS
        if(details==true)
        {
                _u32 s_sizes[6]={2,10,18,36,54,8};
                _f32 s_speeds[6]={0.3f,0.4f,0.5f,0.005f,0.001f,0.0005f};
                _f32 s_distances[6]={1000,2000,600,800,1000,1350};

                
                for(_u32 i=0;i<eldata.num_elektrons+1;++i)
                {
                        scene::ISceneNode* node=smgr->addMeshSceneNode(r_elektron_mesh->getMesh(0) );
                        core::vector3df position=core::vector3df(rand()%200-100,rand()%200-100,rand()%200-100 );
                        position*=catom_positionscale;
                        node->setPosition(position);
                        node->setMaterialTexture( 0, r_elektron_texture );
                        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

                        for(_u32 u=0;u<6;++u)
                        {
                                if( (u==0&&i<s_sizes[u]) || (u>0&&i<s_sizes[u]&&i>=s_sizes[u-1]) )
                                        elektrons.push_back(new CElektron(node,s_distances[u],core::vector3df(rand()%200-100,rand()%200-100,rand()%200-100 ), s_speeds[u]) );
                        }
                }

                for(_u32 i=0;i<elektrons.size();++i)
                {
                        for(_u32 u=0;u<6;++u)
                        {
                                if( (u==0&&i<s_sizes[u]) || (u>0&&i<s_sizes[u]&&i>=s_sizes[u-1]) )
                                {
                                        _u32 start;
                                        if(u==0)start=0;
                                        else start=s_sizes[u-1];

                                        for(_u32 p=start;p<s_sizes[u]&&p<elektrons.size();++p)
                                                if(p!=i)
                                                        elektrons[i]->addOtherElektron(elektrons[p]);
                                }
                        }
                                
                }
#ifdef PRESTEP
                FLoadingScreen->Visible=true;
                FLoadingScreen->StatusBar1->SimpleText="Simuliere Atomkern";
                FLoadingScreen->ProgressBar1->Position=0;
                FLoadingScreen->ProgressBar1->Max=catom_numsteps;

                for(_u32 i=0;i<(_u32)catom_numsteps;++i)
                {
                        FLoadingScreen->ProgressBar1->Position=i;

                        if(i%500==0)
                                Application->ProcessMessages();

                        StepKern(200);
                }

                FLoadingScreen->Visible=false;
#endif //Prestep
        }
#endif //NO_ELEKTRONS
}

void CAtom::Destroy(void)
{
        if(details==false)
        {
                while( connections.size()> 0 )
                {
                        simmgr->Disconnect( connections[0] );
                }

                while( banks.size()>0 )
                {
                        simmgr->RemoveBank(banks[0]);
                }

                corenode->remove();
        }
        else
        {
                for( size_t i=0;i<neutrons.size();++i)
                {
                        neutrons[i]->getNode()->remove();
                }
                for( size_t i=0;i<protons.size();++i)
                {
                        protons[i]->getNode()->remove();
                }
                for( size_t i=0;i<elektrons.size();++i)
                {
                        elektrons[i]->getNode()->remove();
                }
                neutrons.clear();
                protons.clear();
                elektrons.clear();
        }
}



void CAtom::StepKern(f32 time)
{
        age+=time;
        
        if(details==true)
        {

                for(size_t i=0;i<protons.size();++i)
                        protons[i]->Step(time);
                for(size_t i=0;i<neutrons.size();++i)
                        neutrons[i]->Step(time);
#ifndef NO_ELEKTRONS
                for(size_t i=0;i<elektrons.size();++i)
                        elektrons[i]->Step(time);
#endif


                core::aabbox3d<f32> box;

                for(size_t i=0;i<protons.size();++i)
                {
                        if(i==0) box.reset(protons[i]->getNode()->getPosition());
                        else box.addInternalPoint(protons[i]->getNode()->getPosition());
                }

                for(size_t i=0;i<neutrons.size();++i)
                {
                        if( protons.size()==0 && i==0 ) box.reset(neutrons[i]->getNode()->getPosition());
                        box.addInternalPoint(neutrons[i]->getNode()->getPosition());
                }

                position=box.getCenter();

                //driver->draw3DBox(box,video::SColor(255,255,255,255));

                f32 dist=box.getCenter().getDistanceFromSQ(lastcenter);
                if(dist>2)
                {
                        for(size_t i=0;i<elektrons.size();++i)
                        {
                                elektrons[i]->setCorePosition(box.getCenter());
                        }
                }

                lastcenter=box.getCenter();

                for(size_t i=0;i<banks.size();++i)
                {
                        banks[i]->Step(time);
                }
        }
        else
        {
                //zur Kamera schauen
                core::vector3df rot=getRotationToTarget(corenode->getPosition(), camera->getPosition());
                corenode->setRotation(rot);


                //driver->draw3DLine(getAbsolutePosition(), simmgr->getRootNode()->getPosition());

                if( freeze>0 )
                {
                        freeze-=time;
                        return;
                } 

                //Bänke ausrichten
                std::vector<CElektronBank*> t_banks=banks;
                //for(size_t i=0;i<banks.size();++i)
                while(t_banks.size()>0)
                {
                        int i=rand()%t_banks.size();
                        CElektronBank* bank=t_banks[i];
                        bank->Step(time);
                        t_banks.erase( t_banks.begin()+i );

                        /*
                        //Bewegung der Bänke verschnellern
                        core::line3d<f32> line(banks[i]->getNode()->getPosition(), position );
                        while( line.getLengthSQ() > catom_banks_distance_cap*catom_banks_distance_cap )
                        {
                                banks[i]->Step(time);
                                line.start=banks[i]->getNode()->getPosition();
                        }
                        if( line.getLengthSQ() > catom_banks_distance_cap*catom_banks_distance_cap )
                        {
                                banks[i]->getNode()->setPosition(position);
                        }  */
                }


                if( conn_plane_activ==true)
                {
                        if( calculated_plane==true )
                        {
                                conn_plane_activ=false;
                        }
                        else
                        {
                                bool doubleconn=false;
                                for(size_t i=0;i<connections.size();++i)
                                {
                                        if( connections[i]->getDouble()!=-1 )
                                        {
                                                doubleconn=true;
                                                break;
                                        }
                                }
                                for(size_t i=0;i<connections.size() && doubleconn==true;++i)
                                {
                                        CAtom* otherA=connections[i]->getAtom1();
                                        if( otherA==this )
                                                otherA=connections[i]->getAtom2();

                                        /*if( otherA->isCalculatingPlane() )
                                                continue;*/

                                        core::vector3df npos;
                                        if( conn_plane.getIntersectionWithLine(otherA->getPosition(), conn_plane.Normal, npos) )
                                        {
                                                /*core::line3d<f32> dist(this->getPosition(), otherA->getPosition() );
                                                npos=getTargetDistance(this->getPosition(), npos, dist.getLength() );*/

                                                core::line3d<f32> line(otherA->getPosition(), npos);

                                                f32 length=line.getLength();

                                                f32 force=length*time*catom_plane_force;

                                                force=std::min(force, length);

                                                core::vector3df pos=getTargetDistance(otherA->getPosition(),npos, force);
                                                
                                                otherA->setPosition(pos);
                                        }
                                }
                                conn_plane_activ=false;
                        }
                }
        }
                
}

sElementData CAtom::getElementData(void)
{
        return eldata;
}

core::vector3df CAtom::getPosition(void)
{
        if(details==true)
        {
                return lastcenter;
        }
        else
        {
                return position;
        }
}


void CAtom::setPosition(core::vector3df newpos)
{
        if(details==true)
        {
                core::vector3df vect=newpos-lastcenter;

                for(size_t i=0;i<protons.size();++i)
                {
                        core::vector3df pos=protons[i]->getNode()->getPosition();
                        protons[i]->getNode()->setPosition( pos+vect );
                }

                for(size_t i=0;i<neutrons.size();++i)
                {
                        core::vector3df pos=neutrons[i]->getNode()->getPosition();
                        neutrons[i]->getNode()->setPosition( pos+vect );
                }
        }
        else
        {
                position=newpos;
                corenode->setPosition(newpos);
        }
}

void CAtom::addConnection(CConnection* connection)
{
        connections.push_back(connection);

        connection->getNode()->setVisible(visible);

        eldata.num_elektrons++;

        bool half=false;
        for(size_t i=0;i<banks.size();++i)
        {
                if(banks[i]->isFull()==false)
                {
                        CElektronBank *bank=banks[i];

                        simmgr->RemoveBank(bank);

                        half=true;
                        break;
                }
        }

        if(half==false)
        {
                if(banks.size()>0)
                {
                        CElektronBank *dbank=banks[0];
                        simmgr->RemoveBank(dbank);

                        CElektronBank* bank=new CElektronBank(position, false, eldata.bbsize+catom_bank_distance, eldata.modelsize, this);

                        bank->getNode()->setVisible(visible);

                        for(size_t t=0;t<banks.size();++t)
                        {
                                //banks[t]->removeOtherBank(dbank);
                                banks[t]->addOtherBank(bank);
                                bank->addOtherBank(banks[t]);
                        }

                        banks.push_back(bank);
                }
        }

        for(size_t i=0;i<banks.size();++i)
                banks[i]->addConnection(connection);
}

void CAtom::ReconfigureConnections(void)
{
        for(size_t i=0;i<connections.size();++i)
        {
                for(size_t j=0;j<banks.size();++j)
                {
                        if( connections[i]->getAtom1()==this )
                                connections[i]->addBankA1(banks[j] );
                        else
                                connections[i]->addBankA2(banks[j] );
                }
        }        
}

size_t CAtom::NumConnections(void)
{
        return connections.size();
}

CConnection* CAtom::getConnection(size_t num)
{
        if( num<connections.size() )
                return connections[num];
        else
                return NULL;
}

int CAtom::getTotalConnectionNum(std::vector<CAtom*> *exclude, bool *inRing)
{
        for(size_t i=0;i<exclude->size();++i)
        {
                if( this==(*exclude)[i] )
                        return -1;
        }

        exclude->push_back(this);

        int nblocked=0;
        int num=0;
        bool blockedfirst=false;
        
        for(size_t i=0;i<connections.size();++i)
        {
                if( !connections[i]->getCounting() )
                        continue;

                CAtom *other=connections[i]->getAtom1();
                if( other==this )
                        other=connections[i]->getAtom2();

                int rc=other->getTotalConnectionNum(exclude,inRing);
                if( rc==-1 )
                {
                        if( exclude->size()>0 && (*exclude)[0]==other )
                                blockedfirst=true;
                                
                        ++nblocked;
                }
                else
                        num+=rc;

                if( nblocked>1 && inRing!=NULL && blockedfirst==true)
                {
                        *inRing=true;
                }
        }

        num+=connections.size();

        return num+num_invconn;
}

void CAtom::PreStep(void)
{
        if( freeze > 0 )
                return;

        connection_positions.clear();
        bank_positions.clear();

        //TODO: SPEED UP(PERFORMACE)

        for(size_t i=0;i<connections.size();++i)
        {
                connection_positions.push_back(connections[i]->getPosition());
        }

        for(size_t i=0;i<banks.size();++i)
        {
                bank_positions.push_back(banks[i]->getPosition() );
        }

        old_position=position;
}

void CAtom::PostStep(void)
{
        if( freeze > 0 )
                return;
                
        position_lengths.clear();

        bool reset=false;

        for(size_t i=0;i<connections.size();++i)
        {
                if( VerifyPosition( connection_positions[i],  connections[i]->getPosition() ) == false )
                {
                        reset=true;
                }
        }

        for(size_t i=0;i<banks.size();++i)
        {
                if( VerifyPosition( bank_positions[i],  banks[i]->getPosition() ) == false )
                {
                        reset=true;
                }
        }

        if( reset==true )
        {
                freeze=100;
                frozen=true;
                for(size_t i=0;i<connections.size();++i)
                {
                        CAtom *other=connections[i]->getAtom1();
                        if( other==this )
                                other=connections[i]->getAtom2();

                        std::vector<CAtom*> exclude;
                        exclude.push_back( this );

                        if( other->getTotalConnectionNum(&exclude)<2 )
                        {
                                connections[i]->getAtom1()->setPosition( connections[i]->getAtom1()->getOldPosition() );
                                connections[i]->getAtom2()->setPosition( connections[i]->getAtom2()->getOldPosition() );
                                connections[i]->setFreeze(freeze);
                        }
                }

                for(size_t i=0;i<banks.size();++i)
                {
                        banks[i]->setPosition( bank_positions[i] );
                }
        }
        else
                frozen=false;
}

core::vector3df CAtom::getOldPosition(void)
{
        return old_position;
}

bool CAtom::VerifyPosition(core::vector3df old_pos, core::vector3df pos)
{
        f32 length;
        core::vector3df pos1=getTargetDistance(old_position,old_pos, 1000);
        core::vector3df pos2=getTargetDistance(old_position,pos, 1000);
        core::line3d<f32> line(pos1, pos2);
        length=line.getLength();

        for(size_t i=0;i<position_lengths.size();++i)
        {
                if( (position_lengths[i]+catom_change_cap>length && position_lengths[i]-catom_change_cap<length)
                        && age>60000 && length!=0)
                {
                        position_lengths.push_back(length);
                        return false;
                }
        } 

        position_lengths.push_back(length);
        return true;
}

bool CAtom::RemoveBank(CElektronBank* bank)
{
        bool found=false;
        for(size_t i=0;i<banks.size();++i)
        {
                if( banks[i]==bank )
                {
                        banks.erase( banks.begin()+i );
                        found=true;
                }
        }

        for(size_t t=0;t<banks.size();++t)
                banks[t]->removeOtherBank(bank);

        return found;
}

int CAtom::getCharge(void)
{
        int els=0;
        for(size_t i=0;i<banks.size();++i)
        {
                if( banks[i]->isFull()==true )
                        els+=2;
                else
                        ++els;
        }

        for(size_t i=0;i<connections.size();++i)
        {                        
                CAtom *otherA=connections[i]->getAtom1();
                if( otherA==this )
                        otherA=connections[i]->getAtom2();

                if( otherA->getElementData().elektroneg<eldata.elektroneg )
                {
                        els+=2;
                }
                else if( otherA->getElementData().elektroneg==eldata.elektroneg )
                {
                        ++els;
                }
        }

        return getoelektrons(eldata.normal_elektrons)-els;
}

scene::ISceneNode* CAtom::getNode(void)
{
        return corenode;
}

bool CAtom::isOwningNode( scene::ISceneNode* node )
{
        if( node==corenode )
                return true;

        for(size_t i=0;i<banks.size();++i)
        {
                if( banks[i]->getNode()==node )
                        return true;
        }

        return false;
}

bool CAtom::removeConnection(CConnection* connection, int elektrons)
{
        bool found=false;
        for( size_t i=0;i<connections.size();++i)
        {
                if(connections[i]==connection)
                {
                        connections.erase(connections.begin()+i);
                        found=true;
                        break;
                }
        }

        if( found==false )
                return false;

        eldata.num_elektrons-=elektrons;

        if( elektrons!=0)
        {
                bool full=false;
                for(size_t i=0;i<banks.size();++i)
                {
                        if(banks[i]->isFull()==false )
                        {
                                if( elektrons==1 )
                                        simmgr->RemoveBank(banks[i]);

                                full=true;
                                break;
                        }
                }

                CElektronBank* bank;

                if( elektrons==1 )
                {
                        bank=new CElektronBank(position, full, eldata.bbsize+catom_bank_distance, eldata.modelsize, this);
                }
                else if( elektrons==2 )
                {
                        bank=new CElektronBank(position, true, eldata.bbsize+catom_bank_distance, eldata.modelsize, this);
                        bank->getNode()->setVisible(visible);
                }


                for(size_t t=0;t<banks.size();++t)
                {
                        banks[t]->addOtherBank(bank);
                        bank->addOtherBank(banks[t]);
                }

                banks.push_back(bank);
        }

        for(size_t i=0;i<banks.size();++i)
                banks[i]->removeConnection(connection);

        return true;
}

std::string CAtom::getName(void)
{
        return name;
}

void CAtom::setName(std::string pName)
{
        name=pName;
}

vector<CElektronBank*> CAtom::getBanks(void)
{
        return banks;
}

bool CAtom::isFrozen(void)
{
        if( frozen==true )
                return true;

        for(size_t i=0;i<connections.size();++i)
        {
                if( connections[i]->isFrozen()==true )
                        return true;
        }


        return false;
}

void CAtom::setFrozen(int fr)
{
        freeze=fr;
        if( fr>0 )
        {
                frozen=false;
        }
        else
                frozen=true;
}

void CAtom::ResetAge(void)
{
        age=0;
}

void CAtom::AddInvisibleConnection(int num)
{
        num_invconn=num;
}

bool CAtom::calculateConnPlane(void)
{
        if(conn_plane_activ==false)
        {
                if( connections.size()>2 )
                {
                        std::vector<core::vector3df> points;
                        for(size_t i=0;i<connections.size();++i )
                        {
                                if( connections[i]->getDouble()==-1 || connections[i]->getDouble()==0 )
                                {
                                        points.push_back( connections[i]->getPosition() );
                                }
                        }

                        if( points.size()>2 )
                        {
                                conn_plane.setPlane(points[0], points[1], points[2] );
                                conn_plane_activ=true;
                                calculated_plane=true;
                                return true;
                        }
                }
        }
        return false;
}

void CAtom::setConnPlane(const core::plane3d<f32> &plane, std::vector<CAtom*> *exclude)
{
        if( conn_plane_activ==false )
        {
                bool doubleconn=false;
                int nconns=0;

                for(size_t i=0;i<connections.size();++i)
                {
                        if(connections[i]->getDouble()!=-1)
                        {
                                doubleconn=true;
                        }
                        if( connections[i]->getDouble()==-1 || connections[i]->getDouble()==0 )
                                ++nconns;
                }

                if( doubleconn==true && nconns>2 )
                {
                        conn_plane=plane;
                        conn_plane_activ=true;
                        calculated_plane=false;

                        for(size_t i=0;i<connections.size();++i)
                        {
                                CAtom *otherA=connections[i]->getAtom1();
                                if( otherA==this )
                                        otherA=connections[i]->getAtom2();

                                bool found=false;
                                for(size_t t=0;t<exclude->size();++t)
                                {
                                        if( otherA==(*exclude)[t] )
                                        {
                                                found=true;
                                                break;
                                        }
                                }

                                if( found==false )
                                {
                                        otherA->setConnPlane( plane, exclude );
                                }
                        }
                }
                
        }
}

core::plane3d<f32> CAtom::getConnPlane(void)
{
        return conn_plane;
}

bool CAtom::isCalculatingPlane(void)
{
        return calculated_plane;
}

f32 CAtom::CalculateForce2Atom(f32 newforce)
{
        f32 diff=oldforce-newforce;
        oldforce=newforce;
        if(diff<1 && diff>-1)
                return 0;
        else
                return newforce;
}

bool CAtom::getCalculationDirection(void)
{
        if( calc_dir==true )
                calc_dir=false;
        else
                calc_dir=true;

        return calc_dir;
}

void CAtom::Hide(void)
{
        visible=false;

        corenode->setVisible(visible);

        for(size_t i=0;i<banks.size();++i)
        {
                banks[i]->getNode()->setVisible(visible);
        }
        for(size_t i=0;i<connections.size();++i)
        {
                connections[i]->getNode()->setVisible(visible);
        }
}
void CAtom::Show(void)
{
        visible=true;

        corenode->setVisible(visible);

        for(size_t i=0;i<banks.size();++i)
        {
                banks[i]->getNode()->setVisible(visible);
        }
        for(size_t i=0;i<connections.size();++i)
        {
                connections[i]->getNode()->setVisible(visible);
        }
}

bool CAtom::isVisible(void)
{
        return visible;
}

        
        
                



