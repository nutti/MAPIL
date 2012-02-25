/**
*	@file	PointLight.cpp
*	@brief	Implementation of PointLight.h.
*	@date	2011.7.16 (Sat) 18:42
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/PointLight.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	// Constructor.
	PointLight::PointLight( SharedPointer < GraphicsDevice > pDev ) : Light( pDev )
	{
	}

	// Destructor.
	PointLight::~PointLight()
	{
	}
}