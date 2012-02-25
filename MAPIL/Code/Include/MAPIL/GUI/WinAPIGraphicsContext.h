/**
*	@file	WinAPIGraphicsContext.h
*	@brief	
*	@date	2011.8.27 (Sat) 19:23
*/

#ifndef INCLUDED_MAPIL_WINAPIGRAPHICSCONTEXT_H
#define INCLUDED_MAPIL_WINAPIGRAPHICSCONTEXT_H

#include "../CrossPlatform.h"

#ifdef API_WIN32API

#include <Windows.h>
#include <gl/GL.h>

#include <string>

#include "GraphicsContext.h"
#include "../Type.h"
#include "../TChar.h"
#include "WinAPIMsgProc.h"
#include "WinAPIWindow.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class ExposeSignal;
	class WinAPIGraphicsContext : public GraphicsContext, public WinAPIMsgProc//public WinAPIWidget
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
		WinAPIGraphicsContext();
		~WinAPIGraphicsContext();
		MapilVoid Create(	MapilTChar* pWndName,
									MapilInt32 width,
									MapilInt32 height ){}
		MapilVoid Create(	MapilTChar* pWndName,
									MapilInt32 width,
									MapilInt32 height,
									SharedPointer < Window > pParent );
									//WinAPIWidget* pParent );
		MapilVoid Resize( MapilInt32 width, MapilInt32 height );
		MapilVoid Add();
		MapilInt32 ProcessMessage();
		MapilVoid Run();
		MapilVoid Show();
		MapilVoid Connect( ExposeSignal* pSig );
		MapilVoid Connect( KeyboardSignal* pSig );
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