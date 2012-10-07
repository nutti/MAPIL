/**
*	@file	Shader.cpp
*	@brief	Implementation of Shader.h.
*	@date	2012.10.6 (Sat) 22:24
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Shader.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	Shader::Shader( SharedPointer < GraphicsDevice > pDev ) : Graphics( pDev )
	{
	}

	Shader::~Shader()
	{
	}
}
