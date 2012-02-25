/**
*	@file	Polygon3D.cpp
*	@brief	
*	@date	2011.8.18 (Thu) 16:00
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Polygon3D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	Polygon3D::Polygon3D( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}

	Polygon3D::~Polygon3D()
	{
	}
}