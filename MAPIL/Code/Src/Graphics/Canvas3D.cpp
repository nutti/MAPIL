/**
*	@file	Canvas3D.cpp
*	@brief	Implementation of Canvas3D.
*	@date	2012.8.16 (Thu) 9:58
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Canvas3D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	Canvas3D::Canvas3D( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}
	
	Canvas3D::~Canvas3D()
	{
	}
}
