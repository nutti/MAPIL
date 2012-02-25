/**
*	@file	GLTexture.cpp
*	@brief	Implementation of GLTexture.h.
*	@date	2011.7.17 (Sun) 12:13
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#include "../../Include/MAPIL/Graphics/GLTexture.h"
#include "../../Include/MAPIL/IO/BMPFile.h"
#include "../../Include/MAPIL/IO/PNGFile.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Util/String.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GLTexture::GLTexture( SharedPointer < GraphicsDevice > pDev ) :	Texture( pDev ),
																	m_TexName( 0 ),
																	m_pData( NULL )
	{
	}

	GLTexture::~GLTexture()
	{
		glDeleteTextures( 1, &m_TexName );

		m_TexName = 0;
		SafeDeleteArray( m_pData );
	}

	// Create.
	MapilVoid GLTexture::Create( const MapilTChar* pFileName )
	{
		MapilChar name[ 1024 ];
		ConvertToMultiByte( pFileName, -1, name, 1024 );

		PNGFile pf;

		pf.Open( name, FILE_OPEN_READ_MODE );
		pf.Load();

		m_TexSize.m_X = pf.GetWidth();
		m_TexSize.m_Y = pf.GetHeight();

		m_pData = new GLubyte[ pf.GetDataSize() ];

		ZeroObject( m_pData, sizeof( GLubyte ) * pf.GetDataSize() );

		pf.Copy( m_pData );

		pf.Close();



		//BMPFile bf;

		//bf.Open( name, FILE_OPEN_READ_MODE );
		//bf.Load( name );

		//m_TexSize.m_X = bf.GetWidth();
		//m_TexSize.m_Y = bf.GetHeight();

		//m_pData = new GLubyte[ m_TexSize.m_X * m_TexSize.m_Y * 4 ];

		//for( MapilInt32 i = 0; i < m_TexSize.m_Y; i++ ){
		//	for( MapilInt32 j = 0; j < m_TexSize.m_X; j++ ){
		//		ColorRGB < MapilUChar > col = bf.GetPixelColor( j, i );
		//		MapilInt32 offset = i * m_TexSize.m_X;
		//		m_pData[ j * 4 + offset * 4 ] = col.m_R;
		//		m_pData[ j * 4 + offset * 4 + 1 ] = col.m_G;
		//		m_pData[ j * 4 + offset * 4 + 2 ] = col.m_B;
		//		m_pData[ j * 4 + offset * 4 + 3 ] = 255;
		//	}
		//}

		

		glGenTextures( 1, &m_TexName );
		glBindTexture( GL_TEXTURE_2D, m_TexName );
		glTexImage2D(	GL_TEXTURE_2D,
						0,
						( pf.GetChannel() == 4 ) ? GL_RGBA :GL_RGB,
						m_TexSize.m_X,
						m_TexSize.m_Y,
						0,
						( pf.GetChannel() == 4 ) ? GL_RGBA :GL_RGB,
						GL_UNSIGNED_BYTE,
						m_pData );
		//gluBuild2DMipmaps(	GL_TEXTURE_2D,
		//					( pf.GetChannel() == 4 ) ? GL_RGBA : GL_RGB,
		//					m_TexSize.m_X,
		//					m_TexSize.m_Y,
		//					( pf.GetChannel() == 4 ) ? GL_RGBA : GL_RGB,
		//					GL_UNSIGNED_BYTE,
		//					m_pData );
	}

	MapilVoid GLTexture::Create( Archiver* pArchiver, const MapilTChar* pFileName )
	{
	}
	

	MapilInt32 GLTexture::Get()
	{
		return m_TexName;
	}

	Vector2 < MapilInt32 > GLTexture::GetSize()
	{
		return m_TexSize;
	}
}

#endif	// API_OPENGL