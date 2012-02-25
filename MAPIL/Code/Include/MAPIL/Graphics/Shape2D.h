/**
*	@file	Shape2D.h
*	@brief	
*	@date	2011.9.24 (Sat) 10:49
*/

#ifndef INCLUDED_MAPIL_SHAPE2D_H
#define INCLUDED_MAPIL_SHAPE2D_H

#include "../CrossPlatform.h"

#include "Shape.h"


namespace MAPIL
{
	class Shape2D : public Shape
	{
	public:
		Shape2D( SharedPointer < GraphicsDevice > pDev );
		virtual ~Shape2D();
	};
}

#endif