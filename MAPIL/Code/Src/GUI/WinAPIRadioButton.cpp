/**
*	@file	WinAPIRadioButton.cpp
*	@brief	
*	@date	2012.10.28 (Sun) 13:34
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_WIN32API )

#include "../../Include/MAPIL/GUI/WinAPISignalServer.h"
#include "../../Include/MAPIL/GUI/WinAPIRadioButton.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

namespace MAPIL
{
	WinAPIRadioButton::WinAPIRadioButton() :	RadioButton(),
												WinAPIMsgProc(),
												m_HWndParent( NULL ),
												m_HInst( NULL ),
												m_Width( 0 ),
												m_Height( 0 ),
												m_ClassName(),
												m_WndName()
	{
	}
	
	WinAPIRadioButton::~WinAPIRadioButton()
	{
		UnregisterClass( m_ClassName.c_str(), m_HInst );

		m_HInst = NULL;
		m_Width = 0;
		m_Height = 0;
	}

	MapilVoid WinAPIRadioButton::Create(	MapilTChar* pWndName,
											MapilInt32 width,
											MapilInt32 height )
	{
		m_HInst = GetModuleHandle( NULL );
		
		m_Height = height;
		m_Width = width;
		m_WndName = pWndName;
		m_ClassName = TSTR( "BUTTON" );
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
										WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | BS_AUTORADIOBUTTON,	// Window style
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

	MapilVoid WinAPIRadioButton::Create(	MapilTChar* pWndName,
											MapilInt32 width,
											MapilInt32 height,
											SharedPointer < Window > pParent )
	{
		Create( pWndName, 0, 0, width, height, pParent, 0 );
	}

	MapilVoid WinAPIRadioButton::Create(	MapilTChar* pWndName,
											MapilInt32 x,
											MapilInt32 y,
											MapilInt32 width,
											MapilInt32 height,
											SharedPointer < Window > pParent,
											MapilInt32 id )
	{
		m_HInst = GetModuleHandle( NULL );

		m_Width = width;
		m_Height = height;
		m_ClassName = TSTR( "BUTTON" );
		m_WndName = pWndName;

		m_WndParent.DownCast( pParent );

		// Create window
		if( ( m_HWnd = CreateWindow(	m_ClassName.c_str(),						// Window class name
										m_WndName.c_str(),							// Window name
										WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,	// Window style
										x,											// Initial position x of window
										y,											// Initial position y of window
										m_Width,									// Window width
										m_Height,									// Window height
										m_WndParent->GetHWnd(),							// Sub window
										reinterpret_cast < HMENU > ( static_cast < INT_PTR > ( id ) ),										// Position where menu set
										m_HInst,									// Instance handle
										NULL ) ) == NULL ){
			throw MapilException( CURRENT_POSITION, TSTR( "Creation of window failed.\n" ), -2 );
		}

		SetPtr( m_HWnd );

		// Display window
		ShowWindow( m_HWnd, SW_SHOW );
		UpdateWindow( m_HWnd );
	}

	MapilVoid WinAPIRadioButton::Resize( MapilInt32 width, MapilInt32 height )
	{
	}

	MapilVoid WinAPIRadioButton::Add()
	{
	}

	MapilInt32 WinAPIRadioButton::ProcessMessage()
	{
		return 0;
	}

	MapilVoid WinAPIRadioButton::Run()
	{
	}

	MapilVoid WinAPIRadioButton::Show()
	{
	}

	MapilVoid WinAPIRadioButton::Connect( ExposeSignal* pSig )
	{
	}

	MapilVoid WinAPIRadioButton::Connect( KeyboardSignal* pSig )
	{
	}

	MapilBool WinAPIRadioButton::Checked()
	{
		int checked = static_cast < int > ( ::SendMessage( m_HWnd, BM_GETCHECK, 0, 0 ) );
		return checked == BST_CHECKED;
	}

	MapilVoid WinAPIRadioButton::Swap()
	{
	}

	MapilInt32 WinAPIRadioButton::GetWidth() const
	{
		return m_Width;
	}

	MapilInt32 WinAPIRadioButton::GetHeight() const
	{
		return m_Height;
	}

	LRESULT WinAPIRadioButton::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{

		return DefWindowProc( hWnd, msg, wParam, lParam );
	}

	MapilBool WinAPIRadioButton::IsWndMode() const
	{
		return m_IsWndMode;
	}

	SharedPointer < Window > WinAPIRadioButton::GetParentWnd() const
	{
		return m_WndParent;
	}

	HWND WinAPIRadioButton::GetHWnd() const
	{
		return m_HWnd;
	}
}

#endif	// API_WIN32API