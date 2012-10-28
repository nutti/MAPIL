/**
*	@file	WinAPIWindow.h
*	@brief	
*	@date	2011.7.10(Sun) 10:22
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_WIN32API )

#include "../../Include/MAPIL/GUI/WinAPISignalServer.h"
#include "../../Include/MAPIL/GUI/WinAPIWindow.h"
#include "../../Include/MAPIL/GUI/ExposeSignal.h"
#include "../../Include/MAPIL/GUI/KeyboardSignal.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

namespace MAPIL
{
	WinAPIWindow::WinAPIWindow() :	Window(), WinAPIMsgProc(), m_IsActive( MapilFalse )
	{
	}

	WinAPIWindow::~WinAPIWindow()
	{
		m_IsActive = MapilFalse;
	}

	MapilVoid WinAPIWindow::Create(	MapilTChar* pWndName,
									MapilInt32 width,
									MapilInt32 height )
	{
		m_HInst = GetModuleHandle( NULL );
		
		m_Height = height;
		m_Width = width;
		m_WndName = pWndName;
		m_ClassName = m_WndName + TSTR( ".cls" );
		m_IsWndMode = MapilTrue;

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
			throw MapilException( CURRENT_POSITION, TSTR( "Registration of window class failed.\n" ), -1 );
		}

		// Change from window size to client size
		MapilInt32 clientWidth = m_Width + GetSystemMetrics( SM_CXFIXEDFRAME ) * 2;
		MapilInt32 clientHeight = m_Height + GetSystemMetrics( SM_CYFIXEDFRAME )* 2 + GetSystemMetrics( SM_CYCAPTION );

		// Set position where window is created to center
		MapilInt32 wndPosX = ( GetSystemMetrics( SM_CXSCREEN ) - clientWidth ) / 2;
		MapilInt32 wndPosY = ( GetSystemMetrics( SM_CYSCREEN ) - clientHeight ) / 2;

		// Create window
		if( ( m_HWnd = CreateWindow(	m_ClassName.c_str(),						// Window class name
										m_WndName.c_str(),							// Window name
										WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION,	// Window style
										wndPosX,									// Initial position x of window
										wndPosY,									// Initial position y of window
										clientWidth,								// Window width
										clientHeight,								// Window height
										NULL,										// Sub window
										NULL,										// Position where menu set
										m_HInst,									// Instance handle
										this ) ) == NULL ){
			throw MapilException( CURRENT_POSITION, TSTR( "Creation of window failed.\n" ), -2 );
		}

		// Display window
		ShowWindow( m_HWnd, SW_SHOWNORMAL );
		UpdateWindow( m_HWnd );
	}

	MapilVoid WinAPIWindow::Destroy()
	{
		SendMessage( m_HWnd, WM_CLOSE, 0, 0 );
	}

	MapilVoid WinAPIWindow::Resize( MapilInt32 width, MapilInt32 height )
	{
	}

	MapilVoid WinAPIWindow::Add()
	{
	}

	MapilInt32 WinAPIWindow::ProcessMessage()
	{
		MSG msg;
		ZeroObject( &msg, sizeof( msg ) );

		// Main loop
		while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ){
			if( msg.message == WM_QUIT ){
				break;
			}
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		if( msg.message == WM_QUIT ){
			return 1;
		}

		return 0;
	}

	MapilVoid WinAPIWindow::Run()
	{
	}

	MapilVoid WinAPIWindow::Show()
	{
	}

	MapilVoid WinAPIWindow::Connect( ExposeSignal* pSig )
	{
		m_pExposeSig = pSig;
	}

	MapilVoid WinAPIWindow::Connect( KeyboardSignal* pSig )
	{
		m_pKeyboardSig = pSig;
	}

	MapilVoid WinAPIWindow::Connect( ButtonPushedSignal* pSig )
	{
		m_pButtonPushedSig = pSig;
	}

	MapilVoid WinAPIWindow::SetWndMode( MapilInt32 mode )
	{
		// Full screen mode.
		if( mode == 1 ){
			MapilInt32 width = 640;
			MapilInt32 height = 480;
			MapilInt32 bitPerPixel = 32;
			MapilInt32 freq = 60;
			DEVMODE devMod;

			ZeroObject( &devMod, sizeof( devMod ) );
			devMod.dmSize				= sizeof( devMod );
			devMod.dmFields				=	DM_BITSPERPEL |
											DM_PELSWIDTH |
											DM_PELSHEIGHT |
											DM_DISPLAYFREQUENCY |
											DM_DISPLAYFLAGS;
			devMod.dmPelsWidth			= width;
			devMod.dmPelsHeight			= height;
			devMod.dmBitsPerPel			= bitPerPixel;
			devMod.dmDisplayFrequency	= freq;
			devMod.dmDisplayFlags		= 0;

			if( ChangeDisplaySettingsEx( NULL, &devMod, NULL, CDS_TEST | CDS_FULLSCREEN, NULL ) == DISP_CHANGE_SUCCESSFUL ){
				ChangeDisplaySettingsEx( NULL, &devMod, NULL, CDS_FULLSCREEN, NULL );
			}
			else{
				throw MapilException( CURRENT_POSITION, TSTR( "Failed to change window mode into full screen mode.\n" ), -1 );
			}

			SetWindowLong( m_HWnd, GWL_STYLE, GetWindowLong( m_HWnd, GWL_STYLE ) & ~( WS_CAPTION | WS_BORDER | WS_THICKFRAME ) );
			SetWindowLong( m_HWnd, GWL_EXSTYLE, GetWindowLong( m_HWnd, GWL_EXSTYLE ) & ~( WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE ) );
			SetWindowPos(  m_HWnd, HWND_TOPMOST, 0, 0, devMod.dmPelsWidth, devMod.dmPelsHeight, SWP_SHOWWINDOW );
		}
		// Window mode.
		else{
			ChangeDisplaySettingsEx( NULL, NULL, NULL, 0, NULL );
			SetWindowLong( m_HWnd, GWL_STYLE, GetWindowLong( m_HWnd, GWL_STYLE ) | ( WS_CAPTION | WS_BORDER | WS_THICKFRAME ) );
			SetWindowLong( m_HWnd, GWL_EXSTYLE, GetWindowLong( m_HWnd, GWL_EXSTYLE ) | ( WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE ) );
			SetWindowPos( m_HWnd, HWND_NOTOPMOST, 0, 0, m_Width, m_Height, 0 );
		}
	}

	MapilVoid WinAPIWindow::ChangePosToClient(	const Vector2 < MapilInt32 >& in,
												Vector2 < MapilInt32 >* pOut )
	{
		::POINT p;
		p.x = in.m_X;
		p.y = in.m_Y;
		::ScreenToClient( m_HWnd, &p );
		pOut->m_X = p.x;
		pOut->m_Y = p.y;
	}

	MapilVoid WinAPIWindow::ChangePosToScreen(	const Vector2 < MapilInt32 >& in,
												Vector2 < MapilInt32 >* pOut )
	{
		::POINT p;
		p.x = in.m_X;
		p.y = in.m_Y;
		::ClientToScreen( m_HWnd, &p );
		pOut->m_X = p.x;
		pOut->m_Y = p.y;
	}

	MapilBool WinAPIWindow::IsWndMode() const
	{
		return m_IsWndMode;
	}

	MapilBool WinAPIWindow::IsActive() const
	{
		return m_IsActive;
	}

	LRESULT WinAPIWindow::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		switch( msg ){
			case WM_DESTROY:
				PostQuitMessage( 0 );
				return 0;
				break;
			case WM_PAINT:
				if( m_pExposeSig ){
					m_pExposeSig->Handle();
				}
				break;
			case WM_KEYDOWN:
				if( m_pKeyboardSig ){
					m_pKeyboardSig->Handle();
				}
				break;
			case WM_ACTIVATE:			//This message will be issued when active status of window is changed
				//Window becomes non-active
				if( wParam == WA_INACTIVE ){
					m_IsActive = MapilFalse;
				}
				else{
					m_IsActive = MapilTrue;
					//Re-acquisition of Direct Input device
					//m_pDIManagerAll->StartControl();
				}
				break;
			default:
				break;
		}

		return DefWindowProc( hWnd, msg, wParam, lParam );
	}

	HWND WinAPIWindow::GetHWnd() const
	{
		return m_HWnd;
	}

	MapilVoid WinAPIWindow::SetIcon( const MapilTChar* pFileName )
	{
		::HICON hIcon = static_cast < ::HICON > ( LoadImage( NULL, pFileName, IMAGE_ICON, 0, 0, LR_LOADFROMFILE ) );
		::SendMessage( m_HWnd, WM_SETICON, ICON_SMALL, reinterpret_cast < LPARAM > ( hIcon ) );
	}
}

#endif