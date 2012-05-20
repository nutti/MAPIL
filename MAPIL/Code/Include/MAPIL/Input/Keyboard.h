/**
*	@file	Keyboard.h
*	@brief	
*	@date	2011.7.23 (Sat) 20:06
*/

#ifndef INCLUDED_MAPIL_KEYBOARD_H
#define INCLUDED_MAPIL_KEYBOARD_H

#include "../CrossPlatform.h"

#include "Input.h"
#include "../Util/SharedPointer.hpp"
#include "ConstNums.h"
#include "../GUI/Window.h"

namespace MAPIL
{
	class Keyboard : public Input
	{
	public:
		Keyboard( SharedPointer < InputDevice > pDev );
		virtual ~Keyboard();
		virtual MapilVoid Create( SharedPointer < Window > pWnd ) = 0;
		virtual MapilVoid GetKeyMap( MapilUChar* pOut ) = 0;
		virtual MapilBool IsPushed( MapilInt32 key ) = 0;
	};

	MapilInt32 GetKeyboardKeyNum( InputAPI api, KeyboardKey key );

	MapilInt32 GetKeyboardKeyNum( SharedPointer < InputDevice > pDev, KeyboardKey key );

	MapilBool IsKeyPushed( MapilInt32 key );
}

#endif