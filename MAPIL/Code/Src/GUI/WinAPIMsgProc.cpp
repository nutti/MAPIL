/**
*	@file	WinAPIMsgProc.cpp
*	@brief	
*	@date	2011.7.10(Sun) 15:42
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_WIN32API )

#include "../../Include/MAPIL/GUI/WinAPIMsgProc.h"
#include "../../Include/MAPIL/GUI/ExposeSignal.h"
#include "../../Include/MAPIL/GUI/KeyboardSignal.h"
#include "../../Include/MAPIL/GUI/ButtonPushedSignal.h"

namespace MAPIL
{
	WinAPIMsgProc::WinAPIMsgProc() :	MapilObject(),
										m_HWnd( NULL ),
										m_pExposeSig( NULL ),
										m_pKeyboardSig( NULL ),
										m_pButtonPushedSig( NULL )
	{
	}

	WinAPIMsgProc::~WinAPIMsgProc()
	{
	}

	// これは結局継承されるわけだから、関数の内容はあまり必要ないと思われる。
	LRESULT WinAPIMsgProc::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
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
			default:
				break;
		}

		return DefWindowProc( hWnd, msg, wParam, lParam );
	}

	// Set pointer
	MapilVoid WinAPIMsgProc::SetPtr( HWND hWnd )
	{
		SetWindowLong( hWnd, GWL_USERDATA, reinterpret_cast < LONG > ( this ) );
	}

	HWND WinAPIMsgProc::GetHWnd()
	{
		return m_HWnd;
	}

	//MapilVoid WinAPIMsgProc::Connect( ExposeSignal* pSig )
	//{
	//	m_pExposeSig = pSig;
	//}
}

#endif	// API_WIN32API