#pragma hdrstop
#include "CElektron.h"
#include "3dmath.h"
#include "types.h"
#include "settings.h"
#include "engine-req.h"



CElektron::CElektron(scene::ISceneNode* p_node, f32 f_distance, core::vector3df v_corepos,  f32 f_speed)
{
        distance=f_distance;
        node=p_node;
        corepos=v_corepos;
        speed=f_speed;
        velocity=core::vector3df(rand()%360, rand()%360, rand()%360);
        coreforce=0;
}

void CElektron::setCorePosition(core::vector3df v_corepos)
{
        corepos=v_corepos;
}

void CElektron::addOtherElektron(CElektron* p_elektron)
{
        elektrons.push_back(p_elektron);
}

scene::ISceneNode* CElektron::getNode(void)
{
        return node;
}

void CElektron::Step(u32 time)
{
        if(catom_draw_elcoreline==true)
                driver->draw3DLine(node->getPosition(), corepos,video::SColor(255,255,255,255) );

        core::vector3df endpos=getTarget(node->getPosition(), velocity, speed*time);

        core::vector3df corerot=getRotationToTarget(endpos,corepos);

        //anziehung zum Kern
        endpos=getTarget(endpos,corerot, coreforce*time);

        //abstoﬂung von anderen Elektronen
        for(size_t i=0;i<elektrons.size();++i)
        {
                core::line3d<f32> line(endpos,elektrons[i]->getNode()->getPosition());
                f32 elektronforce;

                elektronforce=-1*((1)/(line.getLengthSQ()))-((speed*(catom_elektron_force))/(elektrons.size()));

                core::vector3df elrot=getRotationToTarget(endpos, elektrons[i]->getNode()->getPosition() );

                endpos=getTarget(endpos, elrot, elektronforce*pow(time,2) );
        }

        velocity=getRotationToTarget(node->getPosition(), endpos);

        node->setPosition(endpos);

        core::line3d<f32> line(endpos,corepos);

        //const f32 lov1=0.00001f;

        f32 linel=line.getLength();
        if(linel>distance)
        {
                coreforce=pow( linel-distance,2)*(catom_core_coreforcescale/time);
                coreforce=min( speed, coreforce);
        }
        else
        {
                coreforce=pow( distance-linel,2)*(catom_core_coreforcescale/time);
                coreforce=min( speed, coreforce);
                coreforce*=-1;
        }
}



        
        
