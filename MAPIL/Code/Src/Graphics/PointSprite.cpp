/**
*	@file	PointSprite.cpp
*	@brief	Implementation of PointSprite.h
*	@date	2011.8.7 (Sun) 21:08
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/PointSprite.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	PointSprite::PointSprite( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}

	PointSprite::~PointSprite()
	{
	}
}