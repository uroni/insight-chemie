#pragma hdrstop
#include "RotationAnimator.h"
#include "3dmath.h"

RotationAnimator::RotationAnimator(u32 time, const core::vector3df& center, const core::vector3df& rot, f32 radius, f32 speed)
{
        Radius=radius;
        Center=center;
        Rotation=rot;
        Speed=speed;
        StartTime=time;
}



RotationAnimator::~RotationAnimator()
{
}
		

void RotationAnimator::animateNode(scene::ISceneNode* node, u32 timeMs)
{
        core::matrix4 mat;
			
        f32 t = (timeMs-StartTime) * Speed;

        core::vector3df circle(Radius * (f32)sin(t), 0, Radius * (f32)cos(t));
        circle.rotateYZBy(Rotation.X, Center);
        circle.rotateXZBy(Rotation.Y, Center);
        circle.rotateXYBy(Rotation.Z, Center);
        core::vector3df npos=Center + circle;
        node->setPosition(npos);
}


