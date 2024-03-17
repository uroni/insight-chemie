#include "irrlicht/irrlicht.h"

using namespace irr;

class RotationAnimator : public scene::ISceneNodeAnimator
{
public:
        RotationAnimator(u32 time, const core::vector3df& center, const core::vector3df& rot, f32 radius, f32 speed);

        virtual ~RotationAnimator();

        virtual void animateNode(scene::ISceneNode* node, u32 timeMs);

private:

	core::vector3df Center;
	core::vector3df Rotation;
	f32 Radius;
	f32 Speed;
	u32 StartTime;
};
