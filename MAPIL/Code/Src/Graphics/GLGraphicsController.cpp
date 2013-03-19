/**
*	@file	GLGraphicsController.cpp
*	@brief	Implementation of GLGraphicsController.
*	@date	2011.6.21 (Tue) 17:07
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#if defined ( API_WIN32API )
#include <Windows.h>
#endif
#if defined ( OS_WIN_32BIT )
#include <gl/GL.h>
#endif
#if defined ( OS_LINUX_32BIT )
#include <GL/gl.h>
#endif

#include "../../Include/MAPIL/Graphics/GLGraphicsController.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/IO/BMPFile.h"
#include "../../Include/MAPIL/Util/String.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GLGraphicsController::GLGraphicsController( SharedPointer < GraphicsDevice > pDev ) :	GraphicsController( pDev ),
																							m_pGC(),
																							m_IsGLControlled( MapilFalse )
	{
	}
	
	GLGraphicsController::~GLGraphicsController()
	{
		m_IsGLControlled = MapilFalse;
	}

	MapilVoid GLGraphicsController::Create( SharedPointer < GraphicsContext > pGC )
	{
		m_pGC = pGC;
		m_IsGLControlled = MapilFalse;
	}

	MapilVoid GLGraphicsController::Create( SharedPointer < Window > pWin )
	{
		m_pWin = pWin;
		m_IsGLControlled = MapilTrue;
	}
	
	// Begin rendering
	MapilVoid GLGraphicsController::BeginRendering()
	{
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}
	
	// End rendering
	MapilVoid GLGraphicsController::EndRendering()
	{
		m_pGC->Swap();
#if defined ( API_WIN32API )
		SwapBuffers( m_pDev->m_HDC );
#endif
		glFlush();
	}
	
	// Set viewport
	MapilVoid GLGraphicsController::SetViewport(	MapilInt32 x,
														MapilInt32 y,
														MapilInt32 width,
														MapilInt32 height )
	{
		glViewport( x, y, width, height );
	}
	
	// Enable z buffer
	MapilVoid GLGraphicsController::EnableZBuffer( MapilBool status )
	{
		if( status ){
			glEnable( GL_DEPTH_TEST );
		}
		else{
			glDisable( GL_DEPTH_TEST );
		}
	}
	
	// Enable light
	MapilVoid GLGraphicsController::EnableLight( MapilBool status )
	{
		if( status ){
			glEnable( GL_LIGHTING );
		}
		else{
			glDisable( GL_LIGHTING );
		}
	}
	
	// Enable blend
	MapilVoid GLGraphicsController::EnableBlend( MapilBool status )
	{
		if( status ){
			glEnable( GL_BLEND );
		}
		else{
			glDisable( GL_BLEND );
		}
	}
	
	// Enable fog.
	MapilVoid GLGraphicsController::EnableFog( MapilBool status )
	{
		if( status ){
			glEnable( GL_FOG );
		}
		else{
			glDisable( GL_FOG );
		}
	}
	
	// Set alpha blend mode
	MapilVoid GLGraphicsController::SetAlphaBlendMode( MapilInt32 mode )
	{
		switch( mode ){
			case ALPHA_BLEND_MODE_NO_TRANSPARENT:
				glBlendFunc( GL_ONE, GL_ZERO );
				break;
			case ALPHA_BLEND_MODE_SEMI_TRANSPARENT:
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				break;
			case ALPHA_BLEND_MODE_ADD:
				glBlendFunc( GL_ONE, GL_ONE );
				break;
			case ALPHA_BLEND_MODE_ADD_SEMI_TRANSPARENT:
				glBlendFunc( GL_SRC_ALPHA, GL_ONE );
				break;
			case ALPHA_BLEND_MODE_SUBTRACT_1:
				glBlendFunc( GL_ZERO, GL_ONE_MINUS_SRC_COLOR );
				break;
			case ALPHA_BLEND_MODE_MULTIPLY_1:
				glBlendFunc( GL_ZERO, GL_SRC_COLOR );
				break;
			case ALPHA_BLEND_MODE_MULTIPLY_2:
				glBlendFunc( GL_DST_COLOR, GL_SRC_COLOR );
				break;
			case ALPHA_BLEND_MODE_SCREEN:
				glBlendFunc( GL_ONE_MINUS_DST_COLOR, GL_ONE );
				break;
			case ALPHA_BLEND_MODE_REVERSE_1:
				glBlendFunc( GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR );
				break;
			default:
				break;
		}
	}
	
	// Set cull mode
	MapilVoid GLGraphicsController::SetCullMode( MapilInt32 mode )
	{
		glFrontFace( GL_CCW );

		switch( mode ){
			case CULL_MODE_DISABLED:
				glDisable( GL_CULL_FACE );
				break;
			case CULL_MODE_CLOCKWISE:
				glEnable( GL_CULL_FACE );
				glCullFace( GL_BACK );
				break;
			case CULL_MODE_COUNTERCLOCKWISE:
				glEnable( GL_CULL_FACE );
				glCullFace( GL_FRONT );
				break;
			case CULL_MODE_BOTH:
				glEnable( GL_CULL_FACE );
				glCullFace( GL_FRONT_AND_BACK );
				break;
			default:
				break;
		}
	}
	
	// Set texture mode
	MapilVoid GLGraphicsController::SetTextureMode( MapilInt32 mode )
	{
		switch( mode ){
			case TEXTURE_MODE_2D:
				glEnable( GL_TEXTURE_2D );
				break;
			default:
				break;
		}
	}
	
	// Set fog parameter.
	MapilVoid GLGraphicsController::SetFogParam(	const ColorARGB < MapilFloat32 >& color,
													MapilInt32 mode,
													MapilFloat32 begin,
													MapilFloat32 end,
													MapilFloat32 density )
	{
		GLfloat col[ 4 ] = { color.m_R, color.m_G, color.m_B, color.m_A };

		glFogfv( GL_FOG_COLOR, col );
		glFogi( GL_FOG_MODE, mode );
		//glFogi( GL_FOG_HINT, hint );
		glFogf( GL_FOG_DENSITY, density );
		glFogf( GL_FOG_START, begin );
		glFogf( GL_FOG_END, end );
	}

	// Set fog parameter.
	MapilVoid GLGraphicsController::SetFogParam(	const ColorARGB < MapilUChar >& color,
													MapilInt32 mode,
													MapilFloat32 begin,
													MapilFloat32 end,
													MapilFloat32 density )
	{
		GLint col[ 4 ] = { color.m_R, color.m_G, color.m_B, color.m_A };

		glFogiv( GL_FOG_COLOR, col );
		glFogi( GL_FOG_MODE, mode );
		//glFogi( GL_FOG_HINT, hint );
		glFogf( GL_FOG_DENSITY, density );
		glFogf( GL_FOG_START, begin );
		glFogf( GL_FOG_END, end );
	}

	MapilVoid GLGraphicsController::SetFogParam(	MapilUInt32 color,
													MapilInt32 mode,
													MapilFloat32 begin,
													MapilFloat32 end,
													MapilFloat32 density )
	{
		GLint col[ 4 ] = { ( color >> 24 ) & 0xFF, ( color >> 16 ) & 0xFF, ( color >> 8 ) & 0xFF, color & 0xFF };

		glFogiv( GL_FOG_COLOR, col );
		glFogi( GL_FOG_MODE, mode );
		//glFogi( GL_FOG_HINT, hint );
		glFogf( GL_FOG_DENSITY, density );
		glFogf( GL_FOG_START, begin );
		glFogf( GL_FOG_END, end );
	}

	// Set vsync.
	MapilVoid GLGraphicsController::EnableVSync( MapilBool status )
	{
#if defined ( API_WIN32API )
		typedef BOOL ( APIENTRY *PFNWGLSWAPINTERVALFARPROC ) ( BOOL );
		PFNWGLSWAPINTERVALFARPROC wglSwapInterval = ( PFNWGLSWAPINTERVALFARPROC ) wglGetProcAddress( "wglSwapIntervalEXT" );
		if( !wglSwapInterval ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GLGraphicsController" ),
									TSTR( "EnableVSync" ),
									TSTR( "Failed to setup vsync." ),
									-1 );
		}
		else{
			wglSwapInterval( TRUE );
		}
#endif
	}

	MapilVoid GLGraphicsController::CaptureScreen( const MapilTChar* pFileName )
	{
		BMPFile bmp;
		MapilChar fileName[ 256 ];
		MapilInt32 len = _tcslen( pFileName );
		const MapilInt32 pixelDataSize = 24;


#if defined ( API_WIN32API )
		SharedPointer < WinAPIGraphicsContext > pContext;
#elif defined ( API_GTK )
		SharedPointer < GTKGraphicsContext > pContext;
#endif
		pContext.DownCast( m_pDev->GetContext() );

		MapilInt32 width = pContext->GetWidth();
		MapilInt32 height = pContext->GetHeight();

		MapilInt32 dataSize = height * ( ( ( ( width * pixelDataSize / 8 ) + 3 ) >> 2 ) << 2 );
		MapilInt32 format;
		if( pixelDataSize == 24 ){
			format = GL_RGB;
		}
		else if( pixelDataSize == 32 ){
			format = GL_RGBA;
		}

		GLubyte* pBuf = new GLubyte [ dataSize ];

		::glReadPixels( 0, 0, width, height, format, GL_UNSIGNED_BYTE, pBuf );

		ConvertToMultiByte( pFileName, len, fileName, len );
		bmp.Open( fileName, FILE_OPEN_WRITE_MODE );
#if defined ( API_WIN32API )
		if( pContext->IsWndMode() ){
			bmp.SetHeight( pContext->GetHeight() );
			bmp.SetWidth( pContext->GetWidth() );
			for( MapilInt32 h = 0; h < height; ++h ){
				for( MapilInt32 w = 0; w < width; ++w ){
					bmp.SetPixelColor( w, h, MAPIL::ColorRGB < MapilUChar > (	pBuf[ ( h * width + w ) ],
																				pBuf[ ( h * width + w + 1 ) ],
																				pBuf[ ( h * width + w + 2 ) ] ) );
				}
			}
		}
		else{
		}
#endif

		bmp.Save( fileName, pixelDataSize );
		bmp.Close();
		SafeDeleteArray( pBuf );
	}

	MapilVoid GLGraphicsController::SetWndMode( MapilInt32 mode )
	{
	}

	MapilVoid GLGraphicsController::SetGraphicsFactory( GraphicsFactory* pFactory )
	{
	}

	MapilInt32 GLGraphicsController::GetAlphaBlendMode() const
	{
		return 0;
	}
}

#endif	// API_OPENGL
