/**
*	@file	GLGraphicsFont.cpp
*	@brief	Implementation of GLGraphicsFont.
*	@date	2011.7.31 (Sun) 10:06
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#include "../../Include/MAPIL/Graphics/GLGraphicsFont.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

#include <stdarg.h>

#if defined ( OS_WIN_32BIT )
#pragma warning ( disable : 4996 )
#endif

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
#if defined ( API_WIN32API )

	GLGraphicsFont::GLGraphicsFont( SharedPointer < GraphicsDevice > pDev ) : GraphicsFont( pDev ), m_HFont( NULL ), m_HDC( NULL )
	{
	}

	GLGraphicsFont::~GLGraphicsFont()
	{
		m_HFont = NULL;
		m_HDC = NULL;
	}

	MapilVoid GLGraphicsFont::Create( const FontFormat& fmt )
	{
		m_HFont = CreateFont(	fmt.m_Height,
								fmt.m_Width,
								fmt.m_SlopeEntire,
								fmt.m_Slope,
								fmt.m_Thickness,
								fmt.m_IsItalic,
								fmt.m_HasUnderline,
								fmt.m_HasStrikeOut,
								fmt.m_CharSet,
								fmt.m_Precision,
								fmt.m_ClipPrecision,
								fmt.m_Quality,
								fmt.m_PitchAndFamily,
								fmt.m_FontFaceName );
		m_HDC = wglGetCurrentDC();
		
	}

	MapilVoid GLGraphicsFont::Draw( MapilTChar* pStr )
	{
		if( !pStr ){
			return;
		}

		SelectObject( m_HDC, m_HFont );

		MapilInt32 len = _tcslen( pStr );
		MapilInt32 list = glGenLists( len );
				
		for( MapilInt32 i = 0; i < len; i++ ){
			wglUseFontBitmaps( m_HDC, pStr[ i ], 1, list + i );
		}

		//glDisable( GL_LIGHTING );

		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		glRasterPos2i( 0, 0 );
		for( MapilInt32 i = 0; i < len; i++ ){
			glCallList( list + i );
		}

		//glEnable( GL_LIGHTING );

		glDeleteLists( list, len );
	}

	MapilVoid GLGraphicsFont::Draw(	MapilInt32 posX, MapilInt32 posY,
									MapilFloat32 colR, MapilFloat32 colG, MapilFloat32 colB,
									MapilTChar* pStr, ... )
	{
		if( !pStr ){
			return;
		}

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

		SelectObject( m_HDC, m_HFont );
				
		MapilInt32 list = glGenLists( len );

		for( MapilInt32 i = 0; i < len; i++ ){
			wglUseFontBitmaps( m_HDC, str[ i ], 1, list + i );
		}

		//glDisable( GL_LIGHTING );

		glColor4f( colR, colG, colB, 1.0f );
		glRasterPos2i( posX, posY );
		for( MapilInt32 i = 0; i < len; i++ ){
			glCallList( list + i );
		}

		//glEnable( GL_LIGHTING );

		glDeleteLists( list, len );
	}

	MapilInt32 GLGraphicsFont::Get()
	{
		return reinterpret_cast < MapilInt32 > ( m_HFont );
	}

#else
	GLGraphicsFont::GLGraphicsFont( SharedPointer < GraphicsDevice > pDev ) : GraphicsFont( pDev )
	{
	}
	
	GLGraphicsFont::~GLGraphicsFont()
	{
	}
	
	MapilVoid GLGraphicsFont::Create( const FontFormat& fmt )
	{
		
	}

	MapilVoid GLGraphicsFont::Draw( MapilTChar* pStr )
	{
	}

	MapilVoid GLGraphicsFont::Draw(	MapilInt32 posX, MapilInt32 posY,
									MapilFloat32 colR, MapilFloat32 colG, MapilFloat32 colB,
									MapilTChar* pStr, ... )
	{
	}
#endif
}

#endif	// API_OPENGL