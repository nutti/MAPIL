/**
*	@file	GLLine2D.h
*	@brief	
*	@date	2011.9.24 (Sat) 11:39
*/

#ifndef INCLUDED_MAPIL_GLLINE2D_H
#define INCLUDED_MAPIL_GLLINE2D_H

#include "../CrossPlatform.h"

#if defined ( API_OPENGL )

#include "Line2D.h"
#include "../Util/Color.hpp"

namespace MAPIL
{
	class GLLine2D : public Line2D
	{
	public:
		GLLine2D( SharedPointer < GraphicsDevice > pDev );
		virtual ~GLLine2D();
		MapilVoid Draw();
	};
}

#endif	// API_OPENGL

#endif