#pragma hdrstop
#include "CNeutron.h"
#include "types.h"
#include "settings.h"

CNeutron::CNeutron(scene::ISceneNode* p_node)
{
        node=p_node;
}

void CNeutron::addOtherNeutron(scene::ISceneNode* p_node)
{
        neutrons.push_back(p_node);
}

void CNeutron::addOtherProton(scene::ISceneNode* p_node)
{
        protons.push_back(p_node);
}

scene::ISceneNode* CNeutron::getNode(void)
{
        return node;
}

void CNeutron::Step(u32 time)
{
        for(size_t t=0;t<neutrons.size();++t)
        {
                scene::ISceneNode *neutron=neutrons[t];

                core::line3d<f32> line(neutron->getPosition(),node->getPosition() );

                f32 linel=line.getLength();
                f32 step=(time*catom_stepsize*catom_core_away)/pow(linel,catom_core_exp);
                if(linel<catom_r_neutron*2)
                {
                        //abstoßen node richtung neutron
                        core::vector3df Vector=neutron->getPosition()-node->getPosition() ;
                        core::vector3df ppos=node->getPosition();
                        ppos-= Vector * step;
                        node->setPosition(ppos);
                }
        }
        //die Anziehungskräfte
        for(size_t t=0;t<protons.size();++t)
        {
                scene::ISceneNode *proton=protons[t];

                core::line3d<f32> line(proton->getPosition(),node->getPosition() );

                f32 linel=line.getLength();
                f32 step=time*catom_stepsize*catom_core_phi;
                
                if(linel>catom_stepsize*time*catom_core_phi+catom_r_proton+catom_r_neutron)
                {
                        //anziehen node richtung neutron
                        core::vector3df Vector = proton->getPosition() - node->getPosition();
                        core::vector3df ppos=node->getPosition();
                        ppos+= Vector * step;

                        node->setPosition(ppos);
                }
        }
}


