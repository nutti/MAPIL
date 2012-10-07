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
#include "../GUI/WinAPIWindow.h"

namespace MAPIL
{
	class DIKeyboard : public Keyboard
	{
	private:
		::LPDIRECTINPUTDEVICE8			m_pKeyboardDev;
		MapilBool						m_IsUsed;
		SharedPointer < WinAPIWindow >	m_pWnd;
		MapilBool						m_IsInputActive;
		MapilUChar						m_KeyStatus[ 256 ];
	public:
		DIKeyboard( SharedPointer < InputDevice > pDev );
		~DIKeyboard();
		MapilVoid Create( SharedPointer < Window > pWnd );
		MapilVoid Update();
		MapilVoid GetKeyMap( MapilUChar* pOut );
		MapilBool IsPushed( MapilInt32 key );
	};
}

#endif	// API_DIRECTINPUT

#endif