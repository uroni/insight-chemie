// Copyright (C) 2002-2005 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in Irrlicht.h

#ifndef __I_LIGHT_SCENE_NODE_H_INCLUDED__
#define __I_LIGHT_SCENE_NODE_H_INCLUDED__

#include "ISceneNode.h"
#include "SLight.h"

namespace irr
{
namespace scene
{

//! Scene node which is a dynamic light. 
/** You can switch the light on and off by 
making it visible or not, and let it be animated by ordinary scene node animators.
*/
class ILightSceneNode : public ISceneNode
{
public:

	//! constructor
	ILightSceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id, 
		const core::vector3df& position = core::vector3df(0,0,0))
		: ISceneNode(parent, mgr, id, position) {}

	//! \return Returns the light data.
	virtual video::SLight& getLightData() = 0;
};

} // end namespace scene
} // end namespace irr


#endif

