/**
*	@file	GraphicsFont.cpp
*	@brief	Implementation of GraphicsFont.
*	@date	2011.7.31 (Sun) 12:00
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/GraphicsFont.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GraphicsFont::GraphicsFont( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}

	GraphicsFont::~GraphicsFont()
	{
	}
}