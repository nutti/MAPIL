/**
*	@file	WinAPIKeyboard.h
*	@brief	
*	@date	2011.7.23 (Sat) 20:12
*/

#ifndef INCLUDED_MAPIL_WINAPIKEYBOARD_H
#define INCLUDED_MAPIL_WINAPIKEYBOARD_H

#include "../CrossPlatform.h"

#ifdef API_WIN32API

#include "Keyboard.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class WinAPIKeyboard : public Keyboard
	{
	public:
		WinAPIKeyboard( SharedPointer < InputDevice > pDev );
		~WinAPIKeyboard();
		MapilVoid GetKeyMap( MapilUChar* pOut );
		MapilBool IsPushed( MapilInt32 key );
	};
}

#endif	// API_WIN32API

#endif