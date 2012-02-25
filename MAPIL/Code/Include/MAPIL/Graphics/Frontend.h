/**
*	@file	Frontend.h
*	@brief	
*	@date	2011.8.13 (Sat) 11:19
*/

#ifndef INCLUDED_MAPIL_FRONTEND_H
#define INCLUDED_MAPIL_FRONTEND_H

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "Texture.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class Frontend : public Graphics
	{
	public:
		Frontend( GraphicsDevice* pDev );
		virtual ~Frontend();
		virtual MapilVoid Create( SharedPointer < Texture > pTex ) = 0;
	};
}

#endif