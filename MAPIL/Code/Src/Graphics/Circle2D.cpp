/**
*	@file	Circle2D.cpp
*	@brief	
*	@date	2011.9.24 (Sat) 11:50
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Circle2D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	Circle2D::Circle2D( SharedPointer < GraphicsDevice > pDev ) :	Shape2D( pDev ),
																	m_CenterX( 0 ),
																	m_CenterY( 0 ),
																	m_Radius( 0 ),
																	m_Width( 0 ),
																	m_Col(),
																	m_IsFilled( MapilFalse )
	{
	}

	Circle2D::~Circle2D()
	{
		m_CenterX = 0;
		m_CenterY = 0;
		m_Radius = 0;
		m_Width = 0;
		m_IsFilled = MapilFalse;
	}

	MapilVoid Circle2D::Create(	MapilInt32 centerX,
								MapilInt32 centerY,
								MapilFloat32 radius,
								const ColorARGB < MapilFloat32 >& color,
								MapilFloat32 width,
								MapilBool isFilled )
	{
		m_CenterX = centerX;
		m_CenterY = centerY;
		m_Radius = radius;
		m_Col = color;
		m_Width = width;
		m_IsFilled = isFilled;
	}
}