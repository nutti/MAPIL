/**
*	@file	WinAPIGraphicsContext.cpp
*	@brief	
*	@date	2011.8.27 (Sat) 19:22
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_WIN32API

#include "../../Include/MAPIL/GUI/WinAPISignalServer.h"
#include "../../Include/MAPIL/GUI/WinAPIGraphicsContext.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

namespace MAPIL
{
	WinAPIGraphicsContext::WinAPIGraphicsContext() :	GraphicsContext(),
														WinAPIMsgProc(),
														m_HWndParent( NULL ),
														m_HInst( NULL ),
														m_Width( 0 ),
														m_Height( 0 ),
														m_ClassName(),
														m_WndName()
	{
	}

	WinAPIGraphicsContext::~WinAPIGraphicsContext()
	{
		UnregisterClass( m_ClassName.c_str(), m_HInst );

		m_HInst = NULL;
		m_Width = 0;
		m_Height = 0;
	}

	MapilVoid WinAPIGraphicsContext::Create(	MapilTChar* pWndName,
												MapilInt32 width,
												MapilInt32 height,
												SharedPointer < Window > pParent )
	{
		m_HInst = GetModuleHandle( NULL );

		m_Width = width;
		m_Height = height;
		m_ClassName = pWndName;
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
									TSTR( "WinAPIGraphicsContext" ),
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
									TSTR( "WinGraphicsGLContext" ),
									TSTR( "Create" ),
									TSTR( "Creation of window failed.\n" ),
									-2 );
		}

		m_HWndParent = reinterpret_cast < WNDPROC > ( SetWindowLong( m_HWnd, GWL_WNDPROC, ( LONG ) ( WinAPISignalServer::MsgProc ) ) );
		SetPtr( m_HWnd );

		// Display window
		ShowWindow( m_HWnd, SW_SHOW );
		UpdateWindow( m_HWnd );
	}

	MapilVoid WinAPIGraphicsContext::Resize( MapilInt32 width, MapilInt32 height )
	{
	}

	MapilVoid WinAPIGraphicsContext::Add()
	{
	}

	MapilInt32 WinAPIGraphicsContext::ProcessMessage()
	{
		return 0;
	}

	MapilVoid WinAPIGraphicsContext::Run()
	{
	}

	MapilVoid WinAPIGraphicsContext::Show()
	{
	}

	MapilVoid WinAPIGraphicsContext::Connect( ExposeSignal* pSig )
	{
	}

	MapilVoid WinAPIGraphicsContext::Connect( KeyboardSignal* pSig )
	{
	}

	MapilVoid WinAPIGraphicsContext::Swap()
	{
	}

	MapilInt32 WinAPIGraphicsContext::GetWidth() const
	{
		return m_Width;
	}

	MapilInt32 WinAPIGraphicsContext::GetHeight() const
	{
		return m_Height;
	}

	LRESULT WinAPIGraphicsContext::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		switch( msg ){
			default:
				break;
		}

		return DefWindowProc( hWnd, msg, wParam, lParam );
	}

	MapilBool WinAPIGraphicsContext::IsWndMode() const
	{
		return m_IsWndMode;
	}

	SharedPointer < Window > WinAPIGraphicsContext::GetParentWnd() const
	{
		return m_WndParent;
	}

	HWND WinAPIGraphicsContext::GetHWnd() const
	{
		return m_HWnd;
	}
}

#endif	// API_WIN32API