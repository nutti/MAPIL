/**
*	@file	Shape.h
*	@brief	
*	@date	2011.9.24 (Sat) 10:45
*/

#ifndef INCLUDED_MAPIL_SHAPE_H
#define INCLUDED_MAPIL_SHAPE_H

#include "../CrossPlatform.h"

#include "Graphics.h"


namespace MAPIL
{
	class Shape : public Graphics
	{
	public:
		Shape( SharedPointer < GraphicsDevice > pDev );
		virtual ~Shape();
	};
}

#endif