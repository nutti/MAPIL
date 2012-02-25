/**
*	@file	Widget.h
*	@brief	
*	@date	2011.7.20 (Wed) 21:13
*/

#ifndef INCLUDED_MAPIL_WIDGET_H
#define INCLUDED_MAPIL_WIDGET_H

#include "../CrossPlatform.h"

#include "../Type.h"
#include "../Util/MapilObject.h"

namespace MAPIL
{
	class ExposeSignal;
	class KeyboardSignal;
	class Widget : public MapilObject
	{
	protected:
		MapilInt32			m_Width;
		MapilInt32			m_Height;
	public:
		Widget();
		virtual ~Widget();
		virtual MapilInt32 GetWidth() const;
		virtual MapilInt32 GetHeight() const;
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
	};
}

#endif
