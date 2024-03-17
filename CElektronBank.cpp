#pragma hdrstop
#include "CElektronBank.h"
#include "resources.h"
#include "engine-req.h"
#include "settings.h"
#include "3dmath.h"
#include "CConnection.h"
#include "CAtom.h"
#include "CSimMgr.h"

CElektronBank::CElektronBank(core::vector3df v_corepos, bool b_full, f32 f_distance, f32 f_scale, CAtom* pOwner)
{
        corepos=v_corepos;
        full=b_full;
        scale=f_scale;
        owner=pOwner;
        bbsize=f_distance-catom_bank_distance;


        core::vector3df position=core::vector3df(rand()%(_u32)sandboxsize.X-sandboxsize.X/2,rand()%(_u32)sandboxsize.Y-sandboxsize.Y/2,rand()%(_u32)sandboxsize.Z-sandboxsize.Z/2);
        position*=catom_positionscale;

        if(full==true)
        {
                node=smgr->addMeshSceneNode(r_bank_mesh->getMesh(0));
                
                node->setPosition(position);
                node->setMaterialTexture( 0, r_bank_texture );
                node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                node->setScale(core::vector3df(scale, scale, scale));
                node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        }
        else
        {
                node=smgr->addMeshSceneNode(r_bank_dot_mesh->getMesh(0));
                
                node->setPosition(position);
                node->setMaterialTexture( 0, r_bank_texture );
                node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                node->setScale(core::vector3df(scale, scale, scale));
                node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        }
                
}

CElektronBank::~CElektronBank(void)
{
        node->remove();
}

scene::ISceneNode* CElektronBank::getNode(void)
{
        return node;
}

void CElektronBank::addOtherBank(CElektronBank* bank)
{
        banks.push_back(bank);
}

void CElektronBank::addConnection(CConnection *connection)
{
        connections.push_back(connection);
}

bool CElektronBank::isFull(void)
{
        return full;
}
        
            

void CElektronBank::Step(_f32 time)
{
        f32 distance_sq=catom_bank_distance+bbsize;

        corepos=owner->getPosition();
                
        if( full==true )
        {
                //face core
                core::vector3df rot=getRotationToTarget(node->getPosition(), corepos);

                node->setRotation(rot);
        }
        
        core::vector3df newpos=node->getPosition();

        std::vector<CElektronBank*> t_banks=banks;
//        for(size_t i=0;i<banks.size();++i)
        while( t_banks.size()>0 )
        {
                int i=rand()%(int)t_banks.size();

                core::line3d<f32> line(newpos, t_banks[i]->getPosition());
                newpos=getTargetDistance(newpos, t_banks[i]->getPosition(),-1*catom_bank_force*time*(1.0f/line.getLength() ));

                t_banks.erase( t_banks.begin()+i);
        }

        std::vector<CConnection*> t_connections=connections;
        //for(size_t i=0;i<connections.size();++i)
        while( t_connections.size()>0 )
        {
                int i=rand()%t_connections.size();

                CAtom *otherA=t_connections[i]->getAtom1();
                if( otherA==owner )
                        otherA=t_connections[i]->getAtom2();

                core::vector3df imgpos=getTargetDistance(corepos, otherA->getPosition(), distance_sq);
                core::line3d<f32> line(newpos, imgpos);

                f32 dist=-1*catom_connection2bank_force*time*(1.0f/line.getLength());

                if( full==false )
                        dist*=2.0f;

                newpos=getTargetDistance(newpos, imgpos,dist);

                t_connections.erase( t_connections.begin()+i );
        }

        newpos=getTargetDistance(corepos, newpos, distance_sq );

        node->setPosition(newpos);

        position=newpos;
}

bool CElektronBank::removeOtherBank(CElektronBank *bank)
{
        for(size_t i=0;i<banks.size();++i)
        {
                if(banks[i]==bank)
                {
                        banks.erase(banks.begin()+i);
                        return true;
                }
        }

        return false;
}

core::vector3df CElektronBank::getPosition(void)
{
        return position;
}

void CElektronBank::setPosition(core::vector3df nposition)
{
        position=nposition;
        node->setPosition(position);
}

bool CElektronBank::removeConnection(CConnection *connection)
{
        for(size_t i=0;i<connections.size();++i)
        {
                if( connections[i]==connection )
                {
                        connections.erase(connections.begin()+i);
                        return true;
                }
        }
        return false;
}
                        

        
        

