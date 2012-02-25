/**
*	@file	GLCircle2D.h
*	@brief	
*	@date	2011.9.25 (Sun) 9:17
*/

#ifndef INCLUDED_MAPIL_GLCIRCLE2D_H
#define INCLUDED_MAPIL_GLCIRCLE2D_H

#include "../CrossPlatform.h"

#include "Circle2D.h"
#include "../Util/Color.hpp"

namespace MAPIL
{
	class GLCircle2D : public Circle2D
	{
	public:
		GLCircle2D( SharedPointer < GraphicsDevice > pDev );
		virtual ~GLCircle2D();
		MapilVoid Draw();
	};
}

#endif