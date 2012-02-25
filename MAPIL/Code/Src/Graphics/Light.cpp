/**
*	@file	Light.cpp
*	@brief	
*	@date	2011.7.16 (Sat) 16:20
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Light.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	// Constructor.
	Light::Light( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}

	// Destructor.
	Light::~Light()
	{
	}
}