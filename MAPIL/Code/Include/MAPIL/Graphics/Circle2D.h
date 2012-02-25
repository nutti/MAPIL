/**
*	@file	Circle2D.h
*	@brief	
*	@date	2011.9.24 (Sat) 11:49
*/

#ifndef INCLUDED_MAPIL_CIRCLE2D_H
#define INCLUDED_MAPIL_CIRCLE2D_H

#include "../CrossPlatform.h"

#include "Shape2D.h"
#include "../Util/Color.hpp"

namespace MAPIL
{
	class Circle2D : public Shape2D
	{
	public:
		MapilInt32					m_CenterX;
		MapilInt32					m_CenterY;
		MapilInt32					m_Radius;
		MapilInt32					m_Width;
		ColorARGB < MapilFloat32 >	m_Col;
		MapilBool					m_IsFilled;
	public:
		Circle2D( SharedPointer < GraphicsDevice > pDev );
		virtual ~Circle2D();
		MapilVoid Create(	MapilInt32 centerX,
							MapilInt32 centerY,
							MapilFloat32 radius,
							const ColorARGB < MapilFloat32 >& color,
							MapilFloat32 width,
							MapilBool isFilled );
	};
}

#endif