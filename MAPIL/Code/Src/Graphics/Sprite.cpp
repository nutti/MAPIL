/**
*	@file	Sprite.cpp
*	@brief	Implementation of Sprite.h.
*	@date	2011.9.5 (Mon) 10:40
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Sprite.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	Sprite::Sprite( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}
	
	Sprite::~Sprite()
	{
	}
}
