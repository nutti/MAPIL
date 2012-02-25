/**
*	@file	Canvas2D.cpp
*	@brief	Implementation of GLSprite.h.
*	@date	2011.6.15 (Wed) 18:34
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#include "../../Include/MAPIL/Graphics/GLSprite.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GLSprite::GLSprite( SharedPointer < GraphicsDevice > pDev ) :	Sprite( pDev ),
																	m_pPrevTexture()
	{
	}
	
	GLSprite::~GLSprite()
	{
	}

	MapilVoid GLSprite::Create()
	{
	}

	MapilVoid GLSprite::Begin()
	{
		// Store the previous transformation matrix.
		glGetFloatv( GL_MODELVIEW_MATRIX, m_ViewMat );
		glGetFloatv( GL_PROJECTION_MATRIX, m_ProjMat );

		// Set up the transformation matrix for the 2D drawing.
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho( 0, 640, 480, 0, -1, 1 );

		// Set up the texture parameters for the sprite.
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	}

	MapilVoid GLSprite::End()
	{
		// Restore the previous transformation matrix.
		glMatrixMode( GL_MODELVIEW );
		glLoadMatrixf( m_ViewMat );
		glMatrixMode( GL_PROJECTION );
		glLoadMatrixf( m_ProjMat );

		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );
	}

	MapilVoid GLSprite::DrawTexture( SharedPointer < Texture > pTexture )
	{
		GLfloat texCoord[ 8 ] = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f };
		GLfloat vertexCoord[ 8 ] = {	0.0f,
										0.0f,
										0.0f,
										static_cast < MapilFloat32 > ( pTexture->GetSize().m_Y ),
										static_cast < MapilFloat32 > ( pTexture->GetSize().m_X ),
										static_cast < MapilFloat32 > ( pTexture->GetSize().m_Y ),
										static_cast < MapilFloat32 > ( pTexture->GetSize().m_X ),
										0.0f };

		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

		// When the different texture is set, calls glBindTexture.
		MapilBool isNewTexture = (	!( m_pPrevTexture.GetPointer() ) ||
									m_pPrevTexture->Get() != pTexture->Get() );
		if( isNewTexture ){
			glBindTexture( GL_TEXTURE_2D, 0 );
			m_pPrevTexture = pTexture;
			glBindTexture( GL_TEXTURE_2D, pTexture->Get() );
		}

		glVertexPointer( 2, GL_FLOAT, 0, vertexCoord );
		glTexCoordPointer( 2, GL_FLOAT, 0, texCoord );
		glDrawArrays( GL_QUADS, 0, 4 );
	}

	// Draw texture.
	MapilVoid GLSprite::DrawTexture(	SharedPointer < Texture > pTexture,
										const Matrix4x4 < MapilFloat32 >& mat )
	{
		// If texture hasn't been created, this function returns immediately.
		if( !pTexture.GetPointer() ){
			return;
		}

		// Set up the transformation matrix for the image.
		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
		glLoadMatrixf( mat.m_Elm1 );

		// Draw texture.
		DrawTexture( pTexture );
		glFlush();

		// Restore the transformation matrix.
		glPopMatrix();
	}

	// Draw texture.
	MapilVoid GLSprite::DrawTexture(	SharedPointer < Texture > pTexture,
										ImageTransformationMethod method,
										const Vector2 < MapilFloat32 >& v )
	{
		// If texture hasn't been created, this function returns immediately.
		if( !pTexture.GetPointer() ){
			return;
		}

		// Set up the transformation matrix for the image.
		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();

		// Set up the transformation matrix for the image.
		switch( method ){
			case IMAGE_TRANSFORMATION_METHOD_MOVE:
				glTranslatef( v.m_X, v.m_Y, 0.0f );
				break;
			default:
				break;
		}

		// Draw texture.
		DrawTexture( pTexture );
		glFlush();

		// Restore the transformation matrix.
		glPopMatrix();
	}

	MapilVoid GLSprite::DrawString(	SharedPointer < GraphicsFont > pFont,
									const MapilTChar* pStr,
									ImageTransformationMethod method,
									const Vector2 < MapilFloat32 >& v,
									MapilUInt32 color )
	{
		if( !pStr ){
			return;
		}

		::HDC hdc = wglGetCurrentDC();

		// Build string to be displayed.
		MapilTChar str[ 4096 ];
		va_list vl;
		MapilInt32 len;
		
		va_start( vl, pStr );
		len = _vsctprintf( pStr, vl ) + 1;
		if( len > sizeof( str ) ){
			return;
		}
		_vstprintf( str, pStr, vl );
		va_end( vl );
		len = _tcslen( str );

		SelectObject( hdc, reinterpret_cast < HFONT > ( pFont->Get() ) );
				
		MapilInt32 list = glGenLists( len );

		for( MapilInt32 i = 0; i < len; i++ ){
			wglUseFontBitmaps( hdc, str[ i ], 1, list + i );
		}

		//glDisable( GL_LIGHTING );

		glColor4i( ( color >> 16 ) & 0xFF , ( color >> 8 ) & 0xFF, color & 0xFF, ( color >> 24 ) & 0xFF );
		//glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
		glRasterPos2f( v.m_X, v.m_Y );
		for( MapilInt32 i = 0; i < len; i++ ){
			glCallList( list + i );
		}

		//glEnable( GL_LIGHTING );

		glDeleteLists( list, len );
	}

	MapilVoid GLSprite::DrawString(	SharedPointer < GraphicsFont > pFont,
									const MapilTChar* pStr,
									const Matrix4x4 < MapilFloat32 >& mat )
	{
		if( !pStr ){
			return;
		}

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();

		glLoadMatrixf( mat.m_Elm1 );

		::HDC hdc = wglGetCurrentDC();

		// Build string to be displayed.
		MapilTChar str[ 4096 ];
		va_list vl;
		MapilInt32 len;
		
		va_start( vl, pStr );
		len = _vsctprintf( pStr, vl ) + 1;
		if( len > sizeof( str ) ){
			return;
		}
		_vstprintf( str, pStr, vl );
		va_end( vl );
		len = _tcslen( str );

		SelectObject( hdc, reinterpret_cast < HFONT > ( pFont->Get() ) );
				
		MapilInt32 list = glGenLists( len );

		for( MapilInt32 i = 0; i < len; i++ ){
			wglUseFontBitmaps( hdc, str[ i ], 1, list + i );
		}

		//glDisable( GL_LIGHTING );

		//glColor4f( colR, colG, colB, 1.0f );
		glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
		//glRasterPos2i( vPos.m_X, vPos.m_Y );
		glRasterPos2i( 0, 0 );
		for( MapilInt32 i = 0; i < len; i++ ){
			glCallList( list + i );
		}

		//glEnable( GL_LIGHTING );

		glDeleteLists( list, len );

		glPopMatrix();
	}
}


#endif	// API_OPENGL