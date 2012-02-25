/**
*	@file	Rectangle2D.cpp
*	@brief	
*	@date	2011.9.24 (Sat) 10:54
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Rectangle2D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	Rectangle2D::Rectangle2D( SharedPointer < GraphicsDevice > pDev ) :	Shape2D( pDev ),
																		m_X1( 0 ),
																		m_Y1( 0 ),
																		m_X2( 0 ),
																		m_Y2( 0 ),
																		m_Col(),
																		m_Width( 0 ),
																		m_IsFilled( MapilFalse )
	{
	}

	Rectangle2D::~Rectangle2D()
	{
		m_X1 = 0;
		m_Y1 = 0;
		m_X2 = 0;
		m_Y2 = 0;
		m_Width = 0;
		m_IsFilled = MapilFalse;
	}

	MapilVoid Rectangle2D::Create(	MapilInt32 x1,
									MapilInt32 y1,
									MapilInt32 x2,
									MapilInt32 y2,
									const ColorARGB < MapilFloat32 >& color,
									MapilInt32 width,
									MapilBool isFilled )
	{
		m_X1 = x1;
		m_Y1 = y1;
		m_X2 = x2;
		m_Y2 = y2;
		m_Col = color;
		m_Width = width;
		m_IsFilled = isFilled;
	}
}