/**
*	@file	Graphics.cpp
*	@brief	
*	@date	2011.6.15(Wed) 18:4
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Graphics.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	Graphics::Graphics( GraphicsDevice* pDev ) : MapilObject(), m_pDev( pDev )
	{
	}

	Graphics::Graphics( SharedPointer < GraphicsDevice > pDev ) : MapilObject(), m_pDev( pDev )
	{
	}
	
	Graphics::~Graphics()
	{
	}

	MapilVoid Graphics::LostResource()
	{
	}

	MapilVoid Graphics::RestoreResource()
	{
	}
}
