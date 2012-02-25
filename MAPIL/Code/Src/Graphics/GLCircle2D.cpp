/**
*	@file	GLCircle2D.cpp
*	@brief	
*	@date	2011.9.24 (Sat) 11:50
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/GLCircle2D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	GLCircle2D::GLCircle2D( SharedPointer < GraphicsDevice > pDev ) : Circle2D( pDev )
	{
	}

	GLCircle2D::~GLCircle2D()
	{
	}

	MapilVoid GLCircle2D::Draw()
	{
		const MapilDouble pi = 3.1415;
		for( MapilDouble angle1 = 0.0; angle1 < 360.0; angle1 += 1.0 ){
			MapilDouble angle2 = angle1 + 1.0;
			MapilDouble theta1 = angle1 * pi / 180.0;
			MapilDouble theta2 = angle2 * pi / 180.0;

			MapilFloat32 x1 = static_cast < MapilFloat32 > ( m_Radius * cos( theta1 ) + m_CenterX );
			MapilFloat32 y1 = static_cast < MapilFloat32 > ( m_Radius * sin( theta1 ) + m_CenterY );
			MapilFloat32 x2 = static_cast < MapilFloat32 > ( m_Radius * cos( theta2 ) + m_CenterX );
			MapilFloat32 y2 = static_cast < MapilFloat32 > ( m_Radius * sin( theta2 ) + m_CenterY );

			if( m_IsFilled ){
				glBegin( GL_TRIANGLES );
			}
			else{
				glLineWidth( static_cast < MapilFloat32 > ( m_Width ) );
				glBegin( GL_LINES );
			}
			glColor4f( m_Col.m_R, m_Col.m_G, m_Col.m_B, m_Col.m_A );
			glVertex2f( static_cast < MapilFloat32 > ( m_CenterX ), static_cast < MapilFloat32 > ( m_CenterY ) );
			glVertex2f( x1, y1 );
			glVertex2f( x2, y2 );
			glEnd();
		}
	}
}