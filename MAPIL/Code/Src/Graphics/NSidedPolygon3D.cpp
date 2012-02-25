/**
*	@file	NSidedPolygon3D.cpp
*	@brief	
*	@date	2011.12.31 (Sat) 13:15
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/NSidedPolygon3D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	NSidedPolygon3D::NSidedPolygon3D( SharedPointer < GraphicsDevice > pDev ) : Polygon3D( pDev )
	{
	}

	NSidedPolygon3D::~NSidedPolygon3D()
	{
	}
}