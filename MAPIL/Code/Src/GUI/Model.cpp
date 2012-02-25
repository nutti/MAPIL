/**
*	@file	Model.cpp
*	@brief	Implementation of Model.h.
*	@date	2011.7.16 (Sat) 10:33
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Model.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	Model::Model( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}

	Model::~Model()
	{
	}
}