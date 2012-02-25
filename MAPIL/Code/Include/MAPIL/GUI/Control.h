/**
*	@file	Control.h
*	@brief	
*	@date	2011.7.10(Sun) 11:49
*/

#ifndef INCLUDED_MAPIL_CONTROL_H
#define INCLUDED_MAPIL_CONTROL_H

#include "../CrossPlatform.h"

#include "Widget.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class ExposeSignal;
	class KeyboardSignal;
	class Window;
	class Control : public Widget
	{
	public:
		Control();
		virtual ~Control();
		virtual MapilVoid Create(	MapilTChar* pWndName,
									MapilInt32 width,
									MapilInt32 height ) = 0;
		virtual MapilVoid Create(	MapilTChar* pWndName,
									MapilInt32 width,
									MapilInt32 height,
									SharedPointer < Window > pParent ) = 0;
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