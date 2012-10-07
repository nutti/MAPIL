/**
*	@file	WinAPIKeyboard.cpp
*	@brief	
*	@date	2011.7.23 (Sat) 20:10
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_WIN32API

#include <Windows.h>

#include "../../Include/MAPIL/Input/WinAPIKeyboard.h"

namespace MAPIL
{
	WinAPIKeyboard::WinAPIKeyboard( SharedPointer < InputDevice > pDev ) : Keyboard( pDev )
	{
	}

	WinAPIKeyboard::~WinAPIKeyboard()
	{
	}

	MapilVoid WinAPIKeyboard::Create( SharedPointer < Window > pWnd )
	{
	}

	MapilVoid WinAPIKeyboard::Update()
	{
	}

	MapilVoid WinAPIKeyboard::GetKeyMap( MapilUChar* pOut )
	{
		::GetKeyboardState( pOut );
	}

	MapilBool WinAPIKeyboard::IsPushed( MapilInt32 key )
	{
		return ( ::GetKeyState( key ) & 0x80 ) ? MapilTrue : MapilFalse;
	}
}

#endif	// API_WIN32API