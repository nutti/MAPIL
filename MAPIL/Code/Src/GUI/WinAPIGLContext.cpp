/**
*	@file	WinAPIContext.cpp
*	@brief	
*	@date	2011.7.10(Sun) 14:59
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_OPENGL
#ifdef API_WIN32API

#include "../../Include/MAPIL/GUI/WinAPISignalServer.h"
#include "../../Include/MAPIL/GUI/WinAPIGLContext.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

namespace MAPIL
{
	WinAPIGLContext::WinAPIGLContext() :	GLContext(),
											WinAPIMsgProc(),
											//WinAPIWidget(),
											//m_HWnd( NULL ),
											m_HWndParent( NULL ),
											m_HInst( NULL ),
											m_Width( 0 ),
											m_Height( 0 ),
											m_ClassName(),
											m_WndName(),
											m_HDC( NULL ),
											m_WndParent()
	{
		ZeroObject( &m_PFD, sizeof( m_PFD ) );
	}

	WinAPIGLContext::~WinAPIGLContext()
	{
		UnregisterClass( m_ClassName.c_str(), m_HInst );

		m_HWnd = NULL;
		m_HInst = NULL;
		m_Width = 0;
		m_Height = 0;

		wglMakeCurrent( m_HDC, 0 );
		wglDeleteContext( m_HRC );
		ZeroObject( &m_PFD, sizeof( m_PFD ) );
	}

	MapilVoid WinAPIGLContext::Create(	MapilInt32* argc,
										MapilChar** argv[],
										MapilInt32 height,
										MapilInt32 width,
										SharedPointer < Window > pParent )
										//WinAPIWidget* pParent )
	{
		m_HInst = GetModuleHandle( NULL );

		m_Width = width;
		m_Height = height;
		m_ClassName = TSTR( "testt" );
		m_WndName = m_ClassName + TSTR( ".cls" );

		m_WndParent.DownCast( pParent );

		WNDCLASS wc;			// Window class

		// Set window class
		wc.style			= CS_HREDRAW | CS_VREDRAW;			// Redraw when window size is changed
		wc.lpfnWndProc		= WinAPISignalServer::MsgProc;		// Register window procedure
		wc.cbClsExtra		= 0;								// Unused
		wc.cbWndExtra		= 0;								// Unused
		wc.hInstance		= m_HInst;							// Instance handle
		wc.hIcon			= NULL;								// Specify icon
		wc.hCursor			= NULL;								// Specify cursor
		wc.hbrBackground	= ( HBRUSH )( COLOR_WINDOW + 1 );	// Background color of client region
		wc.lpszMenuName		= NULL;								// Menu name
		wc.lpszClassName	= m_ClassName.c_str();

		// Create window class
		if( !RegisterClass( &wc ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "WinAPIGLContext" ),
									TSTR( "Create" ),
									TSTR( "Registration of window class failed.\n" ),
									-1 );
		}

		// Create window
		if( ( m_HWnd = CreateWindow(	m_ClassName.c_str(),						// Window class name
										m_WndName.c_str(),							// Window name
										WS_CHILD,									// Window style
										0,											// Initial position x of window
										0,											// Initial position y of window
										m_Width,									// Window width
										m_Height,									// Window height
										m_WndParent->GetHWnd(),							// Sub window
										reinterpret_cast < HMENU > ( static_cast < INT_PTR > ( 1 ) ),										// Position where menu set
										m_HInst,									// Instance handle
										NULL ) ) == NULL ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "WinAPIGLContext" ),
									TSTR( "Create" ),
									TSTR( "Creation of window failed.\n" ),
									-2 );
		}

		m_HWndParent = reinterpret_cast < WNDPROC > ( SetWindowLong( m_HWnd, GWL_WNDPROC, ( LONG ) ( WinAPISignalServer::MsgProc ) ) );
		SetPtr( m_HWnd );

		// Display window
		ShowWindow( m_HWnd, SW_SHOW );
		UpdateWindow( m_HWnd );

		m_PFD.nSize			= sizeof( PIXELFORMATDESCRIPTOR );		// Size of PIXELFORMATDESCRIPTOR structure.
		m_PFD.nVersion		= 1;									// Version of OpenGL.
		m_PFD.dwFlags		=	PFD_DRAW_TO_WINDOW |				// Draw directly in window.
								PFD_SUPPORT_OPENGL |				// Support OpenGL.
								PFD_DOUBLEBUFFER;					// Use double buffer.
		m_PFD.iPixelType	= PFD_TYPE_RGBA;						// Display pixel with RGBA color.
		m_PFD.dwLayerMask	= PFD_MAIN_PLANE;						// Layer type. Windows must set this value.
		m_PFD.cColorBits	= 32;									// Display by 32bits RGBA.
		m_PFD.cDepthBits	= 16;									// Maintain the distance from the aspect by 16bits.

		m_HDC = GetDC( m_HWnd );
		m_PixelFormat = ChoosePixelFormat( m_HDC, &m_PFD );
		SetPixelFormat( m_HDC, m_PixelFormat, &m_PFD );

		m_HRC = wglCreateContext( m_HDC );
		wglMakeCurrent( m_HDC, m_HRC );
	}

	MapilVoid WinAPIGLContext::Resize( MapilInt32 height, MapilInt32 width )
	{
	}

	MapilVoid WinAPIGLContext::Add()
	{
	}

	MapilInt32 WinAPIGLContext::ProcessMessage()
	{
		return 0;
	}

	MapilVoid WinAPIGLContext::Run()
	{
	}

	MapilVoid WinAPIGLContext::Show()
	{
	}

	MapilVoid WinAPIGLContext::Connect( ExposeSignal* pSig )
	{
	}

	MapilVoid WinAPIGLContext::Swap()
	{
		SwapBuffers( m_HDC );
	}

	LRESULT WinAPIGLContext::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		//switch( msg ){
		//	default:
		//		break;
		//}

		return DefWindowProc( hWnd, msg, wParam, lParam );
	}

	HWND WinAPIGLContext::GetHWnd() const
	{
		return m_HWnd;
	}
}

#endif	// API_WIN32API
#endif	// API_OPENGL