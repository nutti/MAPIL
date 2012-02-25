/**
*	@file	Rectangle2D.h
*	@brief	
*	@date	2011.9.24 (Sat) 10:52
*/

#ifndef INCLUDED_MAPIL_RECTANGLE2D_H
#define INCLUDED_MAPIL_RECTANGLE2D_H

#include "../CrossPlatform.h"

#include "Shape2D.h"
#include "../Util/Color.hpp"

namespace MAPIL
{
	class Rectangle2D : public Shape2D
	{
	public:
		MapilInt32					m_X1;
		MapilInt32					m_Y1;
		MapilInt32					m_X2;
		MapilInt32					m_Y2;
		MapilInt32					m_Width;
		ColorARGB < MapilFloat32 >	m_Col;
		MapilBool					m_IsFilled;
	public:
		Rectangle2D( SharedPointer < GraphicsDevice > pDev );
		virtual ~Rectangle2D();
		MapilVoid Create(	MapilInt32 x1,
							MapilInt32 y1,
							MapilInt32 x2,
							MapilInt32 y2,
							const ColorARGB < MapilFloat32 >& color,
							MapilInt32 width,
							MapilBool isFilled = MapilTrue );
	};
}

#endif