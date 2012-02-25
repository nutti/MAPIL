/**
*	@file	Shape.cpp
*	@brief	
*	@date	2011.9.24 (Sat) 10:46
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Shape.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	Shape::Shape( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}

	Shape::~Shape()
	{
	}
}