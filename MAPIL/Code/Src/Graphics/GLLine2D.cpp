/**
*	@file	GLLine2D.cpp
*	@brief	
*	@date	2011.9.24 (Sat) 11:41
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#include "../../Include/MAPIL/Graphics/GLLine2D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	GLLine2D::GLLine2D( SharedPointer < GraphicsDevice > pDev ) : Line2D( pDev )
	{
	}

	GLLine2D::~GLLine2D()
	{
	}

	MapilVoid GLLine2D::Draw()
	{
		glLineWidth( static_cast < MapilFloat32 > ( m_Width ) );
		glBegin( GL_LINES );
		glColor4f( m_Col.m_R, m_Col.m_G, m_Col.m_B, m_Col.m_A );
		glVertex2i( m_StartX, m_StartY );
		glColor4f( m_Col.m_G, m_Col.m_R, m_Col.m_B, m_Col.m_A );
		glVertex2i( m_EndX, m_EndY );
		glEnd();
	}
}

#endif	// API_OPENGL