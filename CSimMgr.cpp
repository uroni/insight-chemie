#include <limits>
#pragma hdrstop
#include "CSimMgr.h"
#include "simfuncts.h"
#include "settings.h"
#include "meshlist.h"
#include "engine-req.h"
#include "3dmath.h"
#include "stringtools.h"

void Respeed(void);

CSimMgr::CSimMgr(void)
{
        bdetailed=false;
        currid=0;
        pres_atom_id=0;
        pres_capturing=false;
        hidenewatoms=false;
        newcapturemol=true;
        allow_pause=true;
}

void CSimMgr::init(void)
{
}

CSimMgr::~CSimMgr(void)
{
        std::map<SConnectionFunction*, bool> functs;

        for(conn_array::iterator i=conn_functs.begin();i!=conn_functs.end();++i)
        {
                for(size_t j=0;j<i->second.size();++j)
                {
                        functs[i->second[j]]=true;
                }
        }

        for(std::map<SConnectionFunction*, bool>::iterator i=functs.begin();i!=functs.end();++i)
        {
                delete i->first;
        }
}

int CSimMgr::addAtom(sElementData sEmd, std::string pName, float posx, float posy, float posz)
{
        Respeed();
        
        if( sEmd.element==true )
        {
                CAtom* atom=new CAtom(sEmd, bdetailed,currid,0,0,0,pName);
                atoms.push_back(atom);

                if( hidenewatoms==true )
                {
                        atom->Hide();
                }


                ++currid;

                if( posx==0 && posy==0 && posz==0 )
                {
                        core::vector3df rpos=atom->getPosition();
                        posx=rpos.X;
                        posy=rpos.Y;
                        posz=rpos.Z;
                }

                std::string descr="PRES_ADD_ATOM_DESCR|TYPE="+sEmd.name+"|X="+convert(posx)+"|Y="+convert(posy)+"|Z="+convert(posz);
                std::string data="local ["+convert(currid-1)+"]=CreateAtom(\""+sEmd.name+"\",\""+pName+"\", "+convert(posx)+", "+convert(posy)+", "+convert(posz)+");";

                AddPresentationItem("PRES_ADD_ATOM",descr, data);

                return atom->getID();
        }
        else
                return -1;
}

bool CSimMgr::removeAtom(sElementData sEmd)
{
        Respeed();
        
        for(size_t i=0;i<atoms.size();++i)
        {
                if(atoms[i]->getElementData().name==sEmd.name)
                {
                        CAtom* atom=atoms[i];
                        delete atom;
                        atoms.erase(atoms.begin()+i);
                        return true;
                }
        }

        return false;
}

bool CSimMgr::removeAtom(int id)
{
        Respeed();


        for(size_t i=0;i<atoms.size();++i)
        {
                if( id==atoms[i]->getID() )
                {
                        CAtom* atom=atoms[i];
                        std::string descr="PRES_REMOVE_ATOM_DESCR|TYPE="+atom->getElementData().name;
                        std::string data="RemoveAtom(["+convert(atom->getID())+"]);";

                        AddPresentationItem("PRES_REMOVE_ATOM",descr, data);

                        if( hidenewatoms==false )
                        {
                                delete atom;
                                atoms.erase(atoms.begin()+i);
                        }
                        return true;
                }
        }
        return false;
}

void CSimMgr::removeAll(void)
{
        while(atoms.size()>0)
        {
                removeAtom(atoms[0]->getID() );
        }

        atoms.clear();
}

void CSimMgr::Simulate(f32 time)
{
        if( time > time_cap )
                return;
                
        if( catom_allow_freeze==1 )
        {
                for(size_t i=0;i<atoms.size();++i)
                        atoms[i]->PreStep();
        }

        /*int start=rand()%2;
        int ddone=0;
        while( ddone<2 )
        {
                if( start==0 )
                {
                        std::vector<CAtom*> t_atoms=atoms;  */
                        for(size_t i=0;i<atoms.size();++i)
                        //while(t_atoms.size()>0)
                        {
                                //int i=rand()%t_atoms.size();
                                //CAtom* atom=t_atoms[i];
                                CAtom* atom=atoms[i];
                                atom->StepKern(time);
                                //t_atoms.erase( t_atoms.begin()+i );
                        }
       /*                 start=1;
                }
                else
                {
                        std::vector<CConnection*> t_connections=connections;  */
                        for(size_t i=0;i<connections.size();++i)
                        //while( t_connections.size()>0)
                        {
                                //int i=rand()%t_connections.size();
                                //CConnection* connection=t_connections[i];
                                CConnection* connection=connections[i];
                                connection->Step(time);
                                //t_connections.erase( t_connections.begin()+i );
                        }
    /*                    start=0;
                }
                ++ddone;
        }*/


        if( catom_allow_freeze==1 )
        {
                for(size_t i=0;i<atoms.size();++i)
                        atoms[i]->PostStep();
        }

        SimulateRejection(time);
}

void CSimMgr::setDetail(bool bdetail)
{
        bdetailed=bdetail;
}

sElementData CSimMgr::getElement(std::string name)
{
        std::map<std::string, sElementData>::iterator iter=elements.find(name);
        if( iter!=elements.end() )
                return iter->second;
        else
        {
                sElementData emd;
                emd.element=false;
                return emd;
        }
}

bool CSimMgr::LoadElements(std::string sfile)
{
        meshlist ml;
        ml.open(sfile.c_str());

        for(int i=1;ml.selectmesh(i)==true;++i)
        {
                sElementData dat;
                dat.name=ml.getnamebyid(i);
                dat.num_elektrons=atoi(ml.getvalue("num_elektrons").c_str() );
                dat.num_neutrons=atoi(ml.getvalue("num_neutrons").c_str() );
                dat.num_protons=atoi( ml.getvalue("num_protons").c_str() );

                dat.elektroneg=atof(ml.getvalue("elektroneg").c_str() );
                dat.texture=driver->getTexture( ml.getvalue("texture").c_str() );
                dat.modelsize=atoi( ml.getvalue("modelsize").c_str() );
                dat.normal_elektrons=atoi(ml.getvalue("normal_elektrons").c_str() );
                dat.element=true;

                elements[dat.name]=dat;
        }
        return true;
}

CAtom* CSimMgr::getAtom(int id)
{
        for(size_t i=0;i<atoms.size();++i)
        {
                if( atoms[i]->getID()==id )
                        return atoms[i];
        }
        return NULL;
}

bool CSimMgr::Connect(int atom1, int atom2)
{
        Respeed();

        if( atom1==atom2 )
                return false;

        CAtom *pa1=getAtom(atom1);
        CAtom *pa2=getAtom(atom2);

        if( pa1==NULL || pa2==NULL )
                return false;

        if( pa1->getBanks().size()==0 || pa2->getBanks().size()==0 )
                return false;

        if( hidenewatoms==false )
        {

                std::vector<CConnection*> other_cons;

                for(size_t t=0;t<connections.size();++t)
                {
                        CConnection *other=connections[t];
                        if( (other->getAtom1()==pa1 && other->getAtom2()==pa2)
                                || (other->getAtom2()==pa1 && other->getAtom1()==pa2) )
                        {
                                other_cons.push_back(other);

                                if( other->getAtom1()!= pa1 )
                                {
                                        //Swap
                                        CAtom *tmp;
                                        tmp=pa1;pa1=pa2;pa2=tmp;
                                }
                        }
                }



                CConnection* con=new CConnection(pa1, pa2,(pa1->getElementData().modelsize+pa2->getElementData().modelsize)*catom_connection_size);

                connected[pa1].push_back(con);
                connected[pa2].push_back(con);

                if( other_cons.size() > 0 )
                {
                        for(size_t i=0;i<other_cons.size();++i)
                        {
                                other_cons[i]->addOtherConnection(con);
                                con->addOtherConnection( other_cons[i] );
                        }
                }

               //--->

                for(size_t t=0;other_cons.size()==0 && t<connections.size();++t)
                {
                        CConnection *other=connections[t];
                        if( other->getAtom1()==con->getAtom1()|| other->getAtom1()==con->getAtom2() )
                        {
                                other->addConnectionA1(con);
                                if( other->getAtom1()==con->getAtom1() )
                                        con->addConnectionA1(other);
                                else
                                        con->addConnectionA2(other);
                        }
                        else if( other->getAtom2()==con->getAtom2() ||other->getAtom2()==con->getAtom1() )
                        {
                                other->addConnectionA2(con);
                                if( other->getAtom2()==con->getAtom2() )
                                        con->addConnectionA2(other);
                                else
                                        con->addConnectionA1(other);
                        }
                }

                connections.push_back(con);

                pa1->addConnection(con);
                pa2->addConnection(con);

                ReconfigureConnections();

                if( isNewRing(pa1,pa2) )
                {
                        con->setCounting(false);
                }

                if(other_cons.size()>0 )
                {
                        con->setDouble(0);

                        for(size_t i=0;i<other_cons.size();++i)
                                other_cons[i]->setDouble((int)i+1);
                }
        }


        std::string descr="PRES_CONNECT_DESCR|ATOM1="+pa1->getElementData().name+"|ATOM2="+pa2->getElementData().name;
        std::string data="Connect(["+convert(pa1->getID())+"], ["+convert(pa2->getID())+"]);";

        AddPresentationItem("PRES_CONNECT",descr, data);


        return true;
}

void CSimMgr::ReconfigureConnections(void)
{
        for(size_t i=0;i<connections.size();++i)
        {
                connections[i]->ResetBanks();
        }

        for(size_t i=0;i<atoms.size();++i)
        {
                atoms[i]->ReconfigureConnections();
        }
}

bool CSimMgr::RemoveBank(CElektronBank* bank)
{
        bool found=false;
        for(size_t i=0;i<connections.size();++i)
        {
                bool b=connections[i]->RemoveBank(bank);
                if( b==true )
                        found=true;
        }

        for(size_t i=0;i<atoms.size();++i)
        {
                if( atoms[i]->RemoveBank(bank)==true )
                        found=true;
        }

        ReconfigureConnections();

        delete bank;

        return found;
}

void CSimMgr::SimulateRejection(f32 time)
{
        std::vector<CAtom*> t_atoms=atoms;
//        for(size_t i=0;i<atoms.size();++i)
        while( t_atoms.size()>0 )
        {
                int i=rand()%(int)t_atoms.size();
                CAtom* atom=t_atoms[i];
                
                if( atom->isFrozen()==true )
                        continue;

                core::vector3df position=atom->getPosition();
                int charge=atoms[i]->getCharge();

                for(size_t j=0;j<atoms.size();j++)
                {
                        if( atoms[j]!=atom && atoms[j]->isFrozen()==false )
                        {
                                int other_charge=atoms[j]->getCharge();

                                int diff_charge=abs(other_charge)+abs(charge);
                                int fz;

                                if( (other_charge >=0 && charge <=0) || (other_charge<=0 && charge >=0) )
                                        fz=1;  // anziehen
                                else
                                        fz=-1; // abstoﬂen

                                core::line3d<f32> line( position, atoms[j]->getPosition() );

                                f32 distance=line.getLength();

                                if( distance < catom2catom_distance_cap )
                                {
                                        fz=-1;
                                        diff_charge=catom2catom_distance_cap-distance;
                                }

                                f32 step=(f32)diff_charge;
                                step*=catom2catom_force_scale*time*(1.0f/distance );

                                step=std::min(time*time, step);

                                step*=(f32)fz;

                                position=getTargetDistance(position, atoms[j]->getPosition(), step );
                        }
                }

                atom->setPosition( position );

                t_atoms.erase( t_atoms.begin()+i );
        }
}

CAtom* CSimMgr::FindSceneNode(irr::scene::ISceneNode* node)
{
        for(size_t i=0;i<atoms.size();++i)
        {
                if( atoms[i]->isOwningNode(node) == true )
                {
                        return atoms[i];
                }
        }
        return NULL;
}

core::aabbox3d<f32> CSimMgr::getSandbox(void)
{
        core::aabbox3d<f32> ret;
        if( atoms.size()>0 )
        {
                core::vector3df pos1=atoms[0]->getPosition();
                core::vector3df pos2=atoms[0]->getPosition();

                if( pos1.X==std::numeric_limits<f32>::infinity() ||
                                pos1.Y==std::numeric_limits<f32>::infinity() ||
                                pos1.Z==std::numeric_limits<f32>::infinity() )
                {
                                atoms[0]->Reset();
                                pos1=atoms[0]->getPosition();
                                pos2=atoms[0]->getPosition();
                }

                pos1.X+=atoms[0]->getElementData().bbsize;
                pos1.Y+=atoms[0]->getElementData().bbsize;
                pos1.Z+=atoms[0]->getElementData().bbsize;
                pos2.X-=atoms[0]->getElementData().bbsize;
                pos2.Y-=atoms[0]->getElementData().bbsize;
                pos2.Z-=atoms[0]->getElementData().bbsize;

                ret.MaxEdge=pos1;
                ret.MinEdge=pos2;

                for(size_t i=1;i<atoms.size();++i)
                {
                        if( atoms[i]->isVisible()==false )
                                continue;

                        core::vector3df pos1=atoms[i]->getPosition();
                        core::vector3df pos2=atoms[i]->getPosition();

                        if( pos1.X==std::numeric_limits<f32>::infinity() ||
                                pos1.Y==std::numeric_limits<f32>::infinity() ||
                                pos1.Z==std::numeric_limits<f32>::infinity() )
                        {
                                atoms[i]->Reset();
                                pos1=atoms[i]->getPosition();
                                pos2=atoms[i]->getPosition();
                        }

                        pos1.X+=atoms[i]->getElementData().bbsize;
                        pos1.Y+=atoms[i]->getElementData().bbsize;
                        pos1.Z+=atoms[i]->getElementData().bbsize;
                        pos2.X-=atoms[i]->getElementData().bbsize;
                        pos2.Y-=atoms[i]->getElementData().bbsize;
                        pos2.Z-=atoms[i]->getElementData().bbsize;

                        ret.addInternalPoint( pos1 );
                        ret.addInternalPoint( pos2 );
                }
        }

        ret.repair();

        return ret;
}

bool CSimMgr::Disconnect(int atom1, int atom2, bool cap)
{        
        CAtom* a1=getAtom(atom1);
        CAtom* a2=getAtom(atom2);

        if( a1==NULL || a2==NULL ) return false;

        std::string descr="PRES_DISCONNECT_DESCR|ATOM1="+a1->getElementData().name+"|ATOM2="+a2->getElementData().name;
        std::string data="Disconnect(["+convert(a1->getID())+"], ["+convert(a2->getID())+"]);";

        AddPresentationItem("PRES_DISCONNECT",descr, data);

        if( hidenewatoms==true )
                return true;

        for(int i=(int)connections.size()-1;i>-1;--i)
        {
                CConnection *connection=connections[i];
                if( (connection->getAtom1()==a1 && connection->getAtom2()==a2)
                        || (connection->getAtom2()==a1 && connection->getAtom1()==a2 ) )
                {
                        if( cap==false )
                                atom1=-1;

                        Disconnect(connection, atom1 );
                        return true;
                }
        }
        return false;
}

void CSimMgr::Disconnect(CConnection* connection, int cap)
{
        Respeed();
        
        CAtom *a1=connection->getAtom1();
        CAtom *a2=connection->getAtom2();

        if( isNewRing(a1,a2) )
        {
                //TODO: Set isCounting(true);
        }

        int ea1=1;
        int ea2=1;

        if( a1->getID()==cap )
        {
                ea1=0; ea2=2;
        }
        else if(a2->getID()==cap )
        {
                ea2=0; ea1=2;
        }

        a1->removeConnection(connection,ea1);
        a2->removeConnection(connection,ea2);

        for(size_t i=0;i<connections.size();++i)
        {
                connections[i]->removeConnection( connection );
        }

        for(size_t i=0;i<connections.size();++i)
        {
                if( connections[i]==connection)
                {
                        connections.erase(connections.begin()+i);
                        break;
                }
        }

        delete connection;

        ReconfigureConnections();
}

core::vector3df CSimMgr::RotateNodeAxis(core::vector3df pos,const core::vector3df &rot, const core::line3d<f32> &XLine, const core::line3d<f32> &YLine)
{
        core::vector3df MX=XLine.getClosestPoint(pos);
        core::vector3df MY=YLine.getClosestPoint(pos);

        pos.rotateYZBy(rot.X, MX );
        pos.rotateXZBy(rot.Y, MY );

        return pos;
}

void CSimMgr::RotateWorld(core::vector3df rotation, core::vector3df center)
{
        UnfreezeAll();
        core::aabbox3d<f32> sandbox=getSandbox();
        core::vector3df dimension=sandbox.MaxEdge-sandbox.MinEdge;
        dimension*=100;
        core::line3d<f32> XLine(center.X+dimension.X,center.Y,center.Z,center.X-dimension.X,center.Y,center.Z);
        core::line3d<f32> YLine(center.X,center.Y+dimension.Y,center.Z,center.X,center.Y-dimension.Y,center.Z);

        driver->draw3DLine(XLine.start, XLine.end);
        driver->draw3DLine(YLine.start, YLine.end);

        for(size_t i=0;i<atoms.size();++i)
        {
                atoms[i]->setPosition(RotateNodeAxis(atoms[i]->getPosition(), rotation, XLine, YLine ));

                std::vector<CElektronBank*> banks=atoms[i]->getBanks();

                for(size_t j=0;j<banks.size();++j)
                {
                        banks[j]->setPosition( RotateNodeAxis(banks[j]->getPosition(), rotation, XLine,YLine) );
                }
        }

        for(size_t i=0;i<connections.size();++i)
        {
                connections[i]->setPosition( RotateNodeAxis(connections[i]->getPosition(),rotation, XLine, YLine ) );
        }
}

void CSimMgr::CenterWorld(void)
{
        core::vector3df center(0,0,0);
        core::vector3df newcenter=getSandbox().getCenter();
        core::vector3df vect=newcenter-center;

        for(size_t i=0;i<atoms.size();++i)
        {
                atoms[i]->setPosition( atoms[i]->getPosition() - vect );

                std::vector<CElektronBank*> banks=atoms[i]->getBanks();

                for(size_t j=0;j<banks.size();++j)
                {
                        banks[j]->setPosition( banks[j]->getPosition()-vect);
                }
        }

        for(size_t i=0;i<connections.size();++i)
        {
                connections[i]->setPosition( connections[i]->getPosition()-vect );
        }
}

std::string getLetter(std::string aname, int &ca, int &cc, int &ch, int &co )
{
        std::string letter;
        if( aname=="Sauerstoff" )
        {
                letter="o"+convert(co);
                ++co;
        }
        else if( aname=="Wasserstoff" )
        {
                letter="h"+convert(ch);
                ++ch;
        }
        else if( aname=="Kohlenstoff" )
        {
                letter="c"+convert(cc);
                ++cc;
        }
        else
        {
                letter="a"+convert(ca);
                ++ca;
        }
        return letter;
}

std::string CSimMgr::getSaveScript(void)
{
        if( atoms.size()==0 )
                return "";

        bool samename=true;
        std::string name=atoms[0]->getName();

        for(size_t i=0;i<atoms.size();++i)
        {
                if( atoms[i]->getName()!= name )
                {
                        samename=false;
                        break;
                }
        }

        std::string script;
        if( samename==true )
        {
                script+="local name=\""+name+"\";\r\n";
        }
        script+="local m={};\r\n\r\n";


        int ca=1;
        int cc=1;
        int ch=1;
        int co=1;

        std::vector<std::string> letters;

        for(size_t i=0;i<atoms.size();++i)
        {
                std::string letter;
                std::string aname=atoms[i]->getElementData().name;

                letter=getLetter(aname,ca,cc,ch,co);
                letters.push_back( letter );
                
                script+="m."+letter+"=CreateAtom(\""+atoms[i]->getElementData().name+"\", ";
                if( samename==true )
                        script+="name, ";
                else
                        script+="\""+atoms[i]->getName()+"\", ";

                core::vector3df posa=atoms[i]->getPosition();
                script+=convert(posa.X);
                script+=", ";
                script+=convert(posa.Y);
                script+=", ";
                script+=convert(posa.Z);
                script+=");\r\n";
        }

        for(size_t i=0;i<connections.size();++i)
        {
                CAtom *a1=connections[i]->getAtom1();
                CAtom *a2=connections[i]->getAtom2();

                int ida1=-1;
                int ida2=-1;

                for(size_t j=0;j<atoms.size();++j)
                {
                        if( atoms[j]==a1 )
                                ida1=(int)j;
                        if( atoms[j]==a2 )
                                ida2=(int)j;
                }

                if( ida1!=-1 && ida2!=-1 )
                {
                        script+="Connect(m."+letters[ida1]+", m."+letters[ida2]+");\r\n";
                }

        }

        if( samename==true )
                script+="\r\nRegisterMolecule(name, m);\r\n";

        return script;
}

void CSimMgr::getMolecule(CAtom* currnode, std::vector<CAtom*> &atoms)
{
        atoms.push_back(currnode);
        for(unsigned int i=0;i<currnode->NumConnections();++i)
        {
                CConnection *con=currnode->getConnection(i);
                CAtom* other=con->getAtom1();
                if( other==currnode )
                        other=con->getAtom2();

                bool found=false;
                for(size_t j=0;j<atoms.size();++j)
                {
                        if( atoms[j]==other )
                        {
                                found=true;
                                break;
                        }
                }

                if( found==false )
                {
                        getMolecule(other,atoms);
                }
        }
}

void CSimMgr::addAction( std::string mname, std::string aname, std::string fname)
{
        actions[mname][aname]=fname;
}

std::string CSimMgr::getActionFunction(std::string mname, std::string aname)
{
        return actions[mname][aname];
}

std::vector<std::string> CSimMgr::getActions(std::string mname)
{
        std::vector<std::string> ret;

        std::map<std::string, std::map<std::string,std::string> >::iterator iter=actions.find(mname);

        if( iter!=actions.end() )
        {
                for( std::map<std::string,std::string>::iterator i=iter->second.begin();i!=iter->second.end();++i)
                {
                        ret.push_back( i->first );
                }
        }

        return ret;
}

void CSimMgr::addConnectionFunction(SConnectionFunction *conn)
{
        for(size_t i=0;i<conn->molecules.size();++i)
        {
                conn_functs[conn->molecules[i]].push_back(conn);
        }
}

std::vector<SConnectionFunction*> CSimMgr::getConnectionFunctions(std::string mname)
{
        conn_array::iterator iter=conn_functs.find( mname );

        if( iter!=conn_functs.end() )
                return iter->second;
        else
        {
                std::vector<SConnectionFunction*> ret;
                return ret;
        }
}

std::vector<std::string> CSimMgr::getMoleculeNames(void)
{
        std::vector<std::string> ret;

        for(size_t i=0;i<atoms.size();++i)
        {
                std::string name=atoms[i]->getName();
                bool found=false;
                for(size_t j=0;j<ret.size();++j)
                {
                        if( ret[j]==name )
                        {
                                found=true;
                                break;
                        }
                }

                if( found==false )
                {
                        ret.push_back( name );
                }
        }

        return ret;
}

std::map<std::string,bool> CSimMgr::getMoleculeNamesMap(void)
{
        std::map<std::string,bool> ret;
        for(size_t i=0;i<atoms.size();++i)
        {
                std::string name=atoms[i]->getName();
                ret[ name ]=true;
        }
        return ret;
}

int CSimMgr::getAtomIDbyName(std::string name)
{
        for( size_t i=0;i<atoms.size();++i)
        {
                if( atoms[i]->getName()==name )
                        return atoms[i]->getID();
        }
        return -1;
}

int CSimMgr::getMolceuleIDbyName(std::string name)
{
        for( size_t i=0;i<atoms.size();++i)
        {
                if( atoms[i]->getName()==name )
                        return atoms[i]->getMoleculeID();
        }
        return -1;
}

void CSimMgr::UnfreezeAll(bool reset_age)
{
  
        if( catom_allow_freeze!=1 )
                return;

        for(size_t i=0;i<atoms.size();++i)
        {
                atoms[i]->setFrozen(0);

                if( reset_age==true )
                        atoms[i]->ResetAge();

                /*std::vector<CElektronBank*> banks=atoms[i]->getBanks();

                for(size_t j=0;j<banks.size();++j)
                {
                        banks[j]->setFrozen(0);
                } */
        }

        for(size_t i=0;i<connections.size();++i)
        {
                connections[i]->setFreeze(0);
        }
}

void CSimMgr::setPresentationCapturingEnabled(bool b)
{
        pres_capturing=b;
}

void PresentationItemCallback(SPresItem item);

void CSimMgr::AddPresentationItem(std::string title, std::string description, std::string data)
{
        if( pres_capturing==false )
                return;


        if( data.find("[")!=-1 )
        {
                if( data.find("CreateAtom")!=-1 )
                {
                        int id=atoi( getbetween("[","]", data).c_str() );
                        pres_id_map[id]=pres_atom_id;
                        data=replaceonce("["+convert(id)+"]", "a"+convert(pres_atom_id), data);
                        ++pres_atom_id;
                }
                else
                {
                        while(data.find("[")!=-1)
                        {
                                int id=atoi( getbetween("[","]", data).c_str() );
                                data=replaceonce("["+convert(id)+"]", "a"+convert(pres_id_map[id]), data);
                        }
                }
        }
        /*else if( data.find("CreateAtom") )
        {
                int id=atoi(getbetween(" a","=", data).c_str() );
                if( id+1 > pres_atom_id )
                        pres_atom_id=id+1;

                pres_id_map[]
        }  */

        SPresItem item;
        item.title=title;
        item.description=description;
        item.data=data;//+"  --"+title+"|"+description;
        item.molname=pres_curr_name;

        if( newcapturemol==true )
        {
                item.newmol=true;
                newcapturemol=false;
        }
        else
                item.newmol=false;

        PresentationItemCallback(item);
}

bool CSimMgr::isCapturing(void)
{
        return pres_capturing;
}

void CSimMgr::SaveState(void)
{
        states.push_back(getSaveScript() );

        while( (int)states.size()>num_undo_states )
        {
                states.erase( states.begin() );
        }
}

void CSimMgr::getLastState(std::string &data, bool &last)
{
        if( states.size()>0 )
        {
                data=states[states.size()-1];
                states.erase(states.end() );
                if( states.size()==0 )
                        last=true;
                else
                        last=false;
        }
        else
                last=true;
}

bool CSimMgr::isNewRing(CAtom* a1, CAtom* a2)
{
        std::vector<CAtom*> exclude1;
        std::vector<CAtom*> exclude2;
        bool inRing1=false;
        bool inRing2=false;

        int na1=a1->getTotalConnectionNum(&exclude1, &inRing1);
        int na2=a2->getTotalConnectionNum(&exclude2, &inRing2);

        if( na1 == na2 && inRing1 && inRing2 )
        {
                /*a1->AddInvisibleConnection(1);
                a2->AddInvisibleConnection(1);*/
                return true;
        }
        return false;
}

void CSimMgr::SeparateMolecules(void)
{
        std::vector< std::vector<CAtom*> > molecules;

        for( size_t i=0;i<atoms.size();++i)
        {
                bool found=false;
                for(size_t j=0;j<molecules.size();++j)
                {
                        for(size_t k=0;k<molecules[j].size();++k)
                        {
                                if( molecules[j][k]==atoms[i] )
                                {
                                        found=true;
                                        break;
                                }
                        }
                }

                if( found==false )
                {
                        std::vector<CAtom*> molecule;
                        getMolecule(atoms[i], molecule);

                        molecules.push_back( molecule );
                }
        }

        std::vector< core::aabbox3d<f32> > boxes;
        for(size_t i=0;i<molecules.size();++i)
        {
                if( molecules[i].size()>0 )
                {
                        core::aabbox3d<f32> box=core::aabbox3d<f32>(molecules[i][0]->getPosition());
                        for( size_t j=1;j<molecules[i].size();++j)
                        {
                                box.addInternalPoint(molecules[i][j]->getPosition() );
                        }
                        boxes.push_back( box );
                }
        }

        std::vector< core::vector3df > vectors;
        std::vector< int > translation;

        for(size_t i=0;i<boxes.size();++i)
        {
                core::vector3df vec;
                vec.X=rand()%1000-500;
                vec.Y=rand()%1000-500;
                vec.Z=rand()%1000-500;

                vec.normalize();
                vec*=200;

                vectors.push_back( vec );
                translation.push_back(0);
        }

        int c=0;
        bool end=false;
        while( c<500 && end==false )
        {
                end=true;
                for(size_t i=0;i<boxes.size();++i)
                {
                        for(size_t j=0;j<boxes.size();++j)
                        {
                                if( j!=i )
                                {
                                        if( boxes[i].intersectsWithBox( boxes[j] ) )
                                        {
                                                end=false;
                                                boxes[i].MinEdge+=vectors[i];
                                                boxes[i].MaxEdge+=vectors[i];
                                                ++translation[i];
                                        }
                                }
                        }
                }
                ++c;
        }

        for(size_t i=0;i<molecules.size();++i)
        {
                core::vector3df v_translation=vectors[i]*translation[i];
                for(size_t j=0;j<molecules[i].size();++j)
                {
                        molecules[i][j]->setPosition( molecules[i][j]->getPosition() + v_translation );
                }
        }
}

void CSimMgr::HideNewAtoms(bool b)
{
        hidenewatoms=b;
}

void CSimMgr::ResetCapturing(void)
{
        pres_atom_id=0;
        pres_id_map.clear();
}

void CSimMgr::setCaptureMoleculeName(std::string pName)
{
        CaptureNewMol();
        pres_curr_name=pName;
}

void CSimMgr::CaptureNewMol(void)
{
        newcapturemol=true;
}

std::vector<int> CSimMgr::getCapturedAtomIDs(void)
{
        std::vector<int> ret;
        for(std::map<int,int>::iterator iter=pres_id_map.begin();iter!=pres_id_map.end();++iter)
        {
                ret.push_back( iter->first );
        }

        return ret;
}

std::string CSimMgr::getCaptureID(int rID)
{
        return "a"+convert(pres_id_map[rID]);
}

bool CSimMgr::allowPause(void)
{
        return allow_pause;
}

void CSimMgr::setAllowPause(bool b)
{
        allow_pause=b;
}

        
        


