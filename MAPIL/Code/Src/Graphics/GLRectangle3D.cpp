/**
*	@file	GLRectangle3D.cpp
*	@brief	Implementation of GLRectangle3D.h
*	@date	2011.8.18 (Thu) 16:39
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#include "../../Include/MAPIL/Graphics/GLRectangle3D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GLRectangle3D::GLRectangle3D( SharedPointer < GraphicsDevice > pDev ) :	Rectangle3D( pDev ),
																			m_Fmt(),
																			m_pTex()
	{
	}

	GLRectangle3D::~GLRectangle3D()
	{
	}

	MapilVoid GLRectangle3D::Create(	const Rectangle3DVertexFormat& fmt,
										SharedPointer < Texture > pTex,
										VertexManagementMethod manageMethod )
	{
		m_Fmt = fmt;
		m_pTex = pTex;
	}

	MapilVoid GLRectangle3D::Create(	const Rectangle3DVertexFormat& fmt,
										VertexManagementMethod manageMethod )
	{
		m_Fmt = fmt;
	}

	MapilVoid GLRectangle3D::Update(	const Rectangle3DVertexFormat& fmt,
										SharedPointer < Texture > pTex )
	{
		m_Fmt = fmt;
		m_pTex = pTex;
	}

	MapilVoid GLRectangle3D::Update( const Rectangle3DVertexFormat& fmt )
	{
		m_Fmt = fmt;
	}

	MapilVoid GLRectangle3D::DrawVertex()
	{
		glEnableClientState( GL_VERTEX_ARRAY );
		if( m_pTex.GetPointer() ){
			glEnableClientState( GL_COLOR_ARRAY );
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		}
		else{
			glEnableClientState( GL_COLOR_ARRAY );
		}
		glVertexPointer( 3, GL_FLOAT, 0, m_Fmt.m_PosElm );
		if( m_pTex.GetPointer() ){
			glColorPointer( 4, GL_UNSIGNED_BYTE, 0, m_Fmt.m_ColElm );
			glTexCoordPointer( 2, GL_FLOAT, 0, m_Fmt.m_TexElm );
			glBindTexture( GL_TEXTURE_2D, m_pTex->Get() );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		}
		else{
			glColorPointer( 4, GL_UNSIGNED_BYTE, 0, m_Fmt.m_ColElm );
		}
		glDrawArrays( GL_QUADS, 0, 4 );
		if( m_pTex.GetPointer() ){
			glBindTexture( GL_TEXTURE_2D, 0 );
			glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			glDisableClientState( GL_COLOR_ARRAY );
		}
		else{
			glDisableClientState( GL_COLOR_ARRAY );
		}
		glDisableClientState( GL_VERTEX_ARRAY );
	}

	MapilVoid GLRectangle3D::Draw()
	{
		DrawVertex();

		glFlush();
	}

	MapilVoid GLRectangle3D::Draw( const Matrix4x4 < MapilFloat32 >& mat )
	{
		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
		glMultMatrixf( mat.m_Elm1 );
		DrawVertex();
		glPopMatrix();

		glFlush();
	}
}

#endif	// API_OPENGL