/**
*	@file	Line2D.h
*	@brief	
*	@date	2011.9.24 (Sat) 11:32
*/

#ifndef INCLUDED_MAPIL_LINE2D_H
#define INCLUDED_MAPIL_LINE2D_H

#include "../CrossPlatform.h"

#include "Shape2D.h"
#include "../Util/Color.hpp"

namespace MAPIL
{
	class Line2D : public Shape2D
	{
	public:
		MapilInt32					m_StartX;
		MapilInt32					m_StartY;
		MapilInt32					m_EndX;
		MapilInt32					m_EndY;
		MapilInt32					m_Width;
		ColorARGB < MapilFloat32 >	m_Col;
	public:
		Line2D( SharedPointer < GraphicsDevice > pDev );
		virtual ~Line2D();
		MapilVoid Create(	MapilInt32 x1,
							MapilInt32 y1,
							MapilInt32 x2,
							MapilInt32 y2,
							const ColorARGB < MapilFloat32 >& color,
							MapilInt32 width );
	};
}

#endif