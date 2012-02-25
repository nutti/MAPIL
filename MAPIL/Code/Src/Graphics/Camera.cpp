/**
*	@file	Camera.cpp
*	@brief	Implementation of Camera.
*	@date	2011.6.19 (Sun) 12:2
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Camera.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	Camera::Camera( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}
	
	Camera::~Camera()
	{
	}
}
