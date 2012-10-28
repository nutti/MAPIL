/**
*	@file	RadioButton.h
*	@brief	
*	@date	2012.10.28 (Sun) 13:28
*/

#ifndef INCLUDED_MAPIL_RADIOBUTTON_H
#define INCLUDED_MAPIL_RADIOBUTTON_H

#include "../CrossPlatform.h"

#include "Control.h"

namespace MAPIL
{
	class ExposeSignal;
	class Window;
	class RadioButton : public Control
	{
	public:
		RadioButton();
		virtual ~RadioButton();
		virtual MapilVoid Create(	MapilTChar* pWndName,
									MapilInt32 width,
									MapilInt32 heght ) = 0;
		virtual MapilVoid Create(	MapilTChar* pWndName,
									MapilInt32 width,
									MapilInt32 height,
									SharedPointer < Window > pParent ) = 0;
		virtual MapilVoid Create(	MapilTChar* pWndName,
									MapilInt32 x,
									MapilInt32 y,
									MapilInt32 width,
									MapilInt32 height,
									SharedPointer < Window > pParent,
									MapilInt32 id ) = 0;
		virtual MapilVoid Resize( MapilInt32 width, MapilInt32 height ) = 0;
		virtual MapilVoid Add() = 0;
		virtual MapilInt32 ProcessMessage() = 0;
		virtual MapilVoid Run() = 0;
		virtual MapilVoid Show() = 0;
		virtual MapilVoid Connect( ExposeSignal* pSig ) = 0;
		virtual MapilVoid Connect( KeyboardSignal* pSig ) = 0;
		virtual MapilBool Checked() = 0;
		virtual MapilVoid Swap() = 0;
		virtual SharedPointer < Window > GetParentWnd() const = 0;
	};
}

#endif