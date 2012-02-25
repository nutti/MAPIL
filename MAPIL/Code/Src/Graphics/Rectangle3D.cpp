/**
*	@file	Rectangle3D.cpp
*	@brief	Implementation of Rectangle3D.h.
*	@date	2011.8.18 (Thu) 16:35
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Rectangle3D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	Rectangle3D::Rectangle3D( SharedPointer < GraphicsDevice > pDev ) : Polygon3D( pDev )
	{
	}

	Rectangle3D::~Rectangle3D()
	{
	}
}