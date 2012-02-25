/**
*	@file	GLRectangle2D.cpp
*	@brief	
*	@date	2011.9.24 (Sat) 11:01
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#include "../../Include/MAPIL/Graphics/GLRectangle2D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	GLRectangle2D::GLRectangle2D( SharedPointer < GraphicsDevice > pDev ) : Rectangle2D( pDev )
	{
	}

	GLRectangle2D::~GLRectangle2D()
	{
	}

	MapilVoid GLRectangle2D::Draw()
	{
		if( m_IsFilled ){
			glBegin( GL_QUADS );
		}
		else{
			glLineWidth( static_cast < MapilFloat32 > ( m_Width ) );
			glBegin( GL_LINE_LOOP );
		}
		glColor4f( m_Col.m_R, m_Col.m_G, m_Col.m_B, m_Col.m_A );
		glVertex2i( m_X1, m_Y1 );
		glVertex2i( m_X1, m_Y2 );
		glVertex2i( m_X2, m_Y2 );
		glVertex2i( m_X2, m_Y1 );
		glEnd();
	}
}

#endif	// API_OPENGL