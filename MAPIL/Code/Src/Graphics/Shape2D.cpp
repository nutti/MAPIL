/**
*	@file	Shape2D.cpp
*	@brief	
*	@date	2011.9.24 (Sat) 10:49
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Shape2D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	Shape2D::Shape2D( SharedPointer < GraphicsDevice > pDev ) : Shape( pDev )
	{
	}

	Shape2D::~Shape2D()
	{
	}
}