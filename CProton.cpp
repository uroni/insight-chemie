#pragma hdrstop
#include "CProton.h"
#include "types.h"
#include "settings.h"

CProton::CProton(scene::ISceneNode* p_node)
{
        node=p_node;
}

void CProton::addOtherNeutron(scene::ISceneNode* p_node)
{
        neutrons.push_back(p_node);
}

void CProton::addOtherProton(scene::ISceneNode* p_node)
{
        protons.push_back(p_node);
}

scene::ISceneNode* CProton::getNode(void)
{
        return node;
}

void CProton::Step(u32 time)
{
        //Die Abstoﬂung
        for(size_t t=0;t<protons.size();++t)
        {
                scene::ISceneNode *proton=protons[t];

                core::line3d<f32> line(proton->getPosition(),node->getPosition() );

                f32 linel=line.getLength();
                f32 step=(time*catom_stepsize)/pow(linel,catom_core_exp);
                if(linel<catom_stepsize+catom_r_neutron*2+100)
                {
                        //abstoﬂen node richtung neutron
                        core::vector3df Vector=proton->getPosition()-node->getPosition() ;
                        core::vector3df ppos=node->getPosition();
                        ppos-= Vector * step;
                        node->setPosition(ppos);
                }
        }
        //die Anziehungskr‰fte
        for(size_t t=0;t<neutrons.size();++t)
        {
                scene::ISceneNode *neutron=neutrons[t];

                core::line3d<f32> line(neutron->getPosition(),node->getPosition() );

                f32 linel=line.getLength();
                f32 step=time*catom_stepsize*catom_core_phi;
                
                if(linel>catom_stepsize*time*catom_core_phi+catom_r_proton+catom_r_neutron)
                {
                        //anziehen node richtung neutron
                        core::vector3df Vector = neutron->getPosition() - node->getPosition();
                        core::vector3df ppos=node->getPosition();
                        ppos+= Vector * step;

                        bool doit=true;
                        f32 r_neutron_sq=pow(catom_r_neutron*2,2);
                        for(size_t i=0;i<neutrons.size();++i)
                        {
                                if(ppos.getDistanceFromSQ(neutrons[i]->getPosition() )<r_neutron_sq)
                                {
                                        doit=false;
                                }
                        }

                        if(doit==true)
                                node->setPosition(ppos);
                }
        }
                
}
