/**
*	@file	Canvas2D.cpp
*	@brief	Implementation of Canvas2D.
*	@date	2011.6.15 (Wed) 18:34
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Canvas2D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	Canvas2D::Canvas2D( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}
	
	Canvas2D::~Canvas2D()
	{
	}
}
