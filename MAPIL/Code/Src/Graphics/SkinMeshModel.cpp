/**
*	@file	SkinMeshModel.cpp
*	@brief	Implementation of SkinMeshModel.h.
*	@date	2013.8.24 (Sat) 14:05
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/SkinMeshModel.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	SkinMeshModel::SkinMeshModel( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}

	SkinMeshModel::~SkinMeshModel()
	{
	}
}