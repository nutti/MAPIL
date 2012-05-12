/**
*	@file	DIKeyboard.h
*	@brief	
*	@date	2012.3.7 (Wed) 15:06
*/

#ifndef INCLUDED_MAPIL_DIKEYBOARD_H
#define INCLUDED_MAPIL_DIKEYBOARD_H

#include "../CrossPlatform.h"

#if defined ( API_DIRECTINPUT )

#include "Keyboard.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class DIKeyboard : public Keyboard
	{
	public:
		DIKeyboard( SharedPointer < InputDevice > pDev );
		~DIKeyboard();
		MapilVoid GetKeyMap( MapilUChar* pOut );
		MapilBool IsPushed( MapilInt32 key );
	};
}

#endif	// API_DIRECTINPUT

#endif