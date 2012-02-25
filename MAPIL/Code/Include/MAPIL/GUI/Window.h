/**
*	@file	Window.h
*	@brief	
*	@date	2011.6.15(Wed) 8:6
*/

#ifndef INCLUDED_MAPIL_WINDOW_H
#define INCLUDED_MAPIL_WINDOW_H

#include "../CrossPlatform.h"

#include <string>

#include "../Type.h"
#include "../GUI/Widget.h"
#include "../Math/Vector.hpp"

namespace MAPIL
{
	class ExposeSignal;
	class KeyboardSignal;
	class Window : public Widget
	{
	protected:
		std::basic_string < MapilTChar >	m_ClassName;		// Window class name
		std::basic_string < MapilTChar >	m_WndName;			// Window name
		MapilBool							m_IsWndMode;		// Flag which window is window mode now
	public:
		Window();
		virtual ~Window();
		virtual MapilVoid Create(	MapilTChar* pWndName,
									MapilInt32 width,
									MapilInt32 height ) = 0;
		virtual MapilVoid Resize( MapilInt32 width, MapilInt32 height ) = 0;
		virtual MapilVoid Add() = 0;
		virtual MapilInt32 ProcessMessage() = 0;
		virtual MapilVoid Run() = 0;
		virtual MapilVoid Show() = 0;
		virtual MapilVoid Connect( ExposeSignal* pSig ) = 0;
		virtual MapilVoid Connect( KeyboardSignal* pSig ) = 0;
		virtual MapilVoid SetWndMode( MapilInt32 mode ) = 0;
		virtual MapilVoid ChangePosToClient(	const Vector2 < MapilInt32 >& in,
												Vector2 < MapilInt32 >* pOut ) = 0;
		virtual MapilVoid ChangePosToScreen(	const Vector2 < MapilInt32 >& in,
												Vector2 < MapilInt32 >* pOut ) = 0;
		virtual MapilVoid SetIcon( const MapilTChar* pFileName ) = 0;
	};
}

#endif
