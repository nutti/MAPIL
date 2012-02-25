/**
*	@file	DirectionalLight.cpp
*	@brief	Implementation of DirectionalLight.h.
*	@date	2011.7.16 (Sat) 16:18
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/DirectionalLight.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	// Constructor.
	DirectionalLight::DirectionalLight( SharedPointer < GraphicsDevice > pDev ) : Light( pDev )
	{
	}

	// Destructor.
	DirectionalLight::~DirectionalLight()
	{
	}
}