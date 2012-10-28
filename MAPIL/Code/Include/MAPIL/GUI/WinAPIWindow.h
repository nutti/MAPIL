/**
*	@file	WinAPIWidget.h
*	@brief	
*	@date	2011.7.10(Sun) 9:42
*/

#ifndef INCLUDED_MAPIL_WINAPIWINDOW_H
#define INCLUDED_MAPIL_WINAPIWINDOW_H

#include "../CrossPlatform.h"

#if defined ( API_WIN32API )

#include "Window.h"
#include "WinAPIMsgProc.h"

namespace MAPIL
{
	class WinAPIWindow : public WinAPIMsgProc, public Window
	{
		HINSTANCE			m_HInst;
		MapilBool			m_IsActive;
	public:
		WinAPIWindow();
		virtual ~WinAPIWindow();
		virtual MapilVoid Create(	MapilTChar* pWndName,
									MapilInt32 width,
									MapilInt32 height );
		MapilVoid Destroy();
		virtual MapilVoid Resize( MapilInt32 width, MapilInt32 height );
		virtual MapilVoid Add();
		virtual MapilInt32 ProcessMessage();
		virtual MapilVoid Run();
		virtual MapilVoid Show();
		virtual MapilVoid Connect( ExposeSignal* pSig );
		virtual MapilVoid Connect( KeyboardSignal* pSig );
		virtual MapilVoid Connect( ButtonPushedSignal* pSig );
		virtual MapilVoid SetWndMode( MapilInt32 mode );
		MapilVoid ChangePosToClient(	const Vector2 < MapilInt32 >& in,
										Vector2 < MapilInt32 >* pOut );
		MapilVoid ChangePosToScreen(	const Vector2 < MapilInt32 >& in,
										Vector2 < MapilInt32 >* pOut );
		HWND GetHWnd() const;
		MapilBool IsWndMode() const;
		MapilBool IsActive() const;
		LRESULT WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
		MapilVoid SetIcon( const MapilTChar* pFileName );
	};
}

#endif	// API_WIN32API

#endif