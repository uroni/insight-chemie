// Copyright (C) 2002-2005 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in Irrlicht.h

#ifndef __I_SHADER_CONSTANT_SET_CALLBACT_H_INCLUDED__
#define __I_SHADER_CONSTANT_SET_CALLBACT_H_INCLUDED__

#include "IUnknown.h"

namespace irr
{
namespace video  
{
	class IMaterialRendererServices;

//! Interface making it possible to set constants for gpu programs every frame. 
/* Implement this interface in an own class and pass a pointer to it to one of the methods in
 IGPUProgrammingServices when creating a shader. The OnSetConstants method will be called
 every frame now. */
class IShaderConstantSetCallBack : public IUnknown
{
public:

	//! Destructor.
	virtual ~IShaderConstantSetCallBack() {}

	//! Called by the engine when the vertex and/or pixel shader constants for an
	//! material renderer should be set.
	//! Implement the IShaderConstantSetCallBack in an own class and implement your own
	//! OnSetConstants method using the given IMaterialRendererServices interface.
	//! Pass a pointer to this class to one of the methods in IGPUProgrammingServices 
	//! when creating a shader. The OnSetConstants method will now be called every time
	//! before geometry is being drawn using your shader material. A sample implementation
	//! would look like this:
	//! \code
	//! virtual void OnSetConstants(video::IMaterialRendererServices* services)
	//! {
	//!   video::IVideoDriver* driver = services->getVideoDriver();
	//!
	//!   // set clip matrix at register 4
	//!   core::matrix4 worldViewProj;
	//!   worldViewProj = driver->getTransform(video::ETS_PROJECTION);			
	//!   worldViewProj *= driver->getTransform(video::ETS_VIEW);
	//!   worldViewProj *= driver->getTransform(video::ETS_WORLD);
	//!   services->setVertexShaderConstant(&worldViewProj.M[0], 4, 4);
	//!   // for high level shading languages, this would be another solution:
	//!   //services->setVertexShaderConstant("mWorldViewProj", worldViewProj.M, 16);
	//!   
	//!   // set some light color at register 9
	//!   video::SColorf col(0.0f,1.0f,1.0f,0.0f);
	//!   services->setVertexShaderConstant(reinterpret_cast<f32*>(&col), 9, 1);
	//!   // for high level shading languages, this would be another solution:
	//!   //services->setVertexShaderConstant("myColor", reinterpret_cast<f32*>(&col), 4);
	//! }
	//! \endcode
	virtual void OnSetConstants(IMaterialRendererServices* services) = 0;
};


} // end namespace video
} // end namespace irr

#endif


