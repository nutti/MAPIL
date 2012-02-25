/**
*	@file	GraphicsController.cpp
*	@brief	Implementation of GraphicsController.
*	@date	2011.6.21 (Tue) 16:50
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/GraphicsController.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GraphicsController::GraphicsController( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}
	
	GraphicsController::~GraphicsController()
	{
	}
}
