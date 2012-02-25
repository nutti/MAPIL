/**
*	@file	WinAPISignalServer.cpp
*	@brief	
*	@date	2011.7.10(Sun) 10:48
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_WIN32API

#include "../../Include/MAPIL/GUI/WinAPISignalServer.h"
#include "../../Include/MAPIL/GUI/WinAPIMsgProc.h"
#include "../../Include/MAPIL/GUI/WinAPIWindow.h"

namespace MAPIL
{
	WinAPISignalServer::WinAPISignalServer() : SignalServer()
	{
	}

	WinAPISignalServer::~WinAPISignalServer()
	{
	}

	// Window procedure
	LRESULT CALLBACK WinAPISignalServer::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		//WinAPIWindow* pWnd = reinterpret_cast < WinAPIWindow* > ( GetWindowLong( hWnd, GWL_USERDATA ) );
		WinAPIMsgProc* pWnd = reinterpret_cast < WinAPIMsgProc* > ( GetWindowLong( hWnd, GWL_USERDATA ) );


		if( !pWnd ){
			if( msg == WM_CREATE ){
				//pWnd = reinterpret_cast < WinAPIWindow* > ( reinterpret_cast < LPCREATESTRUCT > ( lParam )->lpCreateParams );
				pWnd = reinterpret_cast < WinAPIMsgProc* > ( reinterpret_cast < LPCREATESTRUCT > ( lParam )->lpCreateParams );

			}
			if( pWnd ){
				pWnd->SetPtr( hWnd );
			}
		}
				
		if( pWnd ){
			return pWnd->WndProc( hWnd, msg, wParam, lParam );
		}

		return DefWindowProc( hWnd, msg, wParam, lParam );
	}

	
}

#endif	// API_WIN32API