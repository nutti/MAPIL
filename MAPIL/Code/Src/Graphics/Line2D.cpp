/**
*	@file	Line2D.cpp
*	@brief	
*	@date	2011.9.24 (Sat) 11:34
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Line2D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	Line2D::Line2D( SharedPointer < GraphicsDevice > pDev ) :	Shape2D( pDev ),
																m_StartX( 0 ),
																m_StartY( 0 ),
																m_EndX( 0 ),
																m_EndY( 0 ),
																m_Col(),
																m_Width( 0 )
	{
	}

	Line2D::~Line2D()
	{
		m_StartX = 0;
		m_StartY = 0;
		m_StartX = 0;
		m_StartY = 0;
		m_Width = 0;
	}

	MapilVoid Line2D::Create(	MapilInt32 x1,
								MapilInt32 y1,
								MapilInt32 x2,
								MapilInt32 y2,
								const ColorARGB < MapilFloat32 >& color,
								MapilInt32 width )
	{
		m_StartX = x1;
		m_StartY = y1;
		m_EndX = x2;
		m_EndY = y2;
		m_Col = color;
		m_Width = width;
	}
}