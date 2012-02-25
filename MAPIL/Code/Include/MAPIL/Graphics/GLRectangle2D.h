/**
*	@file	GLRectangle2D.h
*	@brief	
*	@date	2011.9.24 (Sat) 10:59
*/

#ifndef INCLUDED_MAPIL_GLRECTANGLE2D_H
#define INCLUDED_MAPIL_GLRECTANGLE2D_H

#include "../CrossPlatform.h"

#if defined ( API_OPENGL )

#include "Rectangle2D.h"


namespace MAPIL
{
	class GLRectangle2D : public Rectangle2D
	{
	public:
		GLRectangle2D( SharedPointer < GraphicsDevice > pDev );
		virtual ~GLRectangle2D();
		MapilVoid Draw();
	};
}

#endif	// API_OPENGL

#endif