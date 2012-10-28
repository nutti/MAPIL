/**
*	@file	WinAPIRadioButton.h
*	@brief	
*	@date	2012.10.28 (Sun) 13:31
*/

#ifndef INCLUDED_MAPIL_WINAPIRADIOBUTTON_H
#define INCLUDED_MAPIL_WINAPIRADIOBUTTON_H

#include "../CrossPlatform.h"

#if defined ( API_WIN32API )

#include <Windows.h>
#include <string>

#include "RadioButton.h"
#include "../Type.h"
#include "../TChar.h"
#include "WinAPIMsgProc.h"
#include "WinAPIWindow.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class ExposeSignal;
	class WinAPIRadioButton: public RadioButton, public WinAPIMsgProc
	{
	private:		
		WNDPROC								m_HWndParent;
		HINSTANCE							m_HInst;			// Instance handle
		MapilInt32							m_Width;			// Width of window
		MapilInt32							m_Height;			// Height of window
		std::basic_string < MapilTChar >	m_ClassName;		// Window class name
		std::basic_string < MapilTChar >	m_WndName;			// Window name

		MapilBool							m_IsWndMode;		// Is window mode?

		SharedPointer < WinAPIWindow >		m_WndParent;		// Parent window.
	public:
		WinAPIRadioButton();
		~WinAPIRadioButton();
		MapilVoid Create(	MapilTChar* pWndName,
							MapilInt32 width,
							MapilInt32 height );
		MapilVoid Create(	MapilTChar* pWndName,
							MapilInt32 width,
							MapilInt32 height,
							SharedPointer < Window > pParent );
		MapilVoid Create(	MapilTChar* pWndName,
							MapilInt32 x,
							MapilInt32 y,
							MapilInt32 width,
							MapilInt32 height,
							SharedPointer < Window > pParent,
							MapilInt32 id );
		MapilVoid Resize( MapilInt32 width, MapilInt32 height );
		MapilVoid Add();
		MapilInt32 ProcessMessage();
		MapilVoid Run();
		MapilVoid Show();
		MapilVoid Connect( ExposeSignal* pSig );
		MapilVoid Connect( KeyboardSignal* pSig );
		MapilBool Checked();
		MapilVoid Swap();
		MapilInt32 GetWidth() const;
		MapilInt32 GetHeight() const;
		MapilBool IsWndMode() const;
		LRESULT WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
		SharedPointer < Window > GetParentWnd() const;
		HWND GetHWnd() const;
	};
}

#endif	// API_WIN32API

#endif