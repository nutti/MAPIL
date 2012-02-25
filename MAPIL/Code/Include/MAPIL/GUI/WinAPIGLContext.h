/**
*	@file	WinAPIContext.h
*	@brief	
*	@date	2011.7.10(Sun) 11:55
*/

#ifndef INCLUDED_MAPIL_WINAPIGLCONTEXT_H
#define INCLUDED_MAPIL_WINAPIGLCONTEXT_H

#include "../CrossPlatform.h"

#ifdef API_OPENGL
#ifdef API_WIN32API

#include <Windows.h>
#include <gl/GL.h>

#include <string>

#include "GLContext.h"
#include "../Type.h"
#include "../TChar.h"
#include "WinAPIMsgProc.h"
#include "WinAPIWindow.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class ExposeSignal;
	class WinAPIGLContext : public GLContext, public WinAPIMsgProc//public WinAPIWidget
	{
	private:
		//HWND								m_HWnd;				// Window handle
		
		WNDPROC								m_HWndParent;
		HINSTANCE							m_HInst;			// Instance handle
		MapilInt32							m_Width;			// Width of window
		MapilInt32							m_Height;			// Height of window
		std::basic_string < MapilTChar >	m_ClassName;		// Window class name
		std::basic_string < MapilTChar >	m_WndName;			// Window name
		HDC									m_HDC;				// Device context handle
		MapilInt32							m_PixelFormat;		// Pixel format
		PIXELFORMATDESCRIPTOR				m_PFD;				// PIXELFORMATDESCRIPTOR structure
		HGLRC								m_HRC;				// OpenGL rendering context

		SharedPointer < WinAPIWindow >		m_WndParent;		// Parent window.
	public:
		WinAPIGLContext();
		~WinAPIGLContext();
		MapilVoid Create(	MapilInt32* argc,
									MapilChar** argv[],
									MapilInt32 height,
									MapilInt32 width ){}
		MapilVoid Create(	MapilInt32* argc,
									MapilChar** argv[],
									MapilInt32 height,
									MapilInt32 width,
									SharedPointer < Window > pParent );
									//WinAPIWidget* pParent );
		MapilVoid Resize( MapilInt32 height, MapilInt32 width );
		MapilVoid Add();
		MapilInt32 ProcessMessage();
		MapilVoid Run();
		MapilVoid Show();
		MapilVoid Connect( ExposeSignal* pSig );
		MapilVoid Swap();

		LRESULT WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

		HWND GetHWnd() const;
	};
}

#endif	// API_WIN32API
#endif	// API_OPENGL

#endif