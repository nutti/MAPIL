/**
*	@file	Frontend.cpp
*	@brief	
*	@date	2011.8.13 (Sat) 11:27
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Frontend.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	Frontend::Frontend( GraphicsDevice* pDev ) : Graphics( pDev )
	{
	}

	Frontend::~Frontend()
	{
	}
}