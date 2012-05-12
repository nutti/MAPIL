/**
*	@file	DIKeyboard.cpp
*	@brief	
*	@date	2012.3.7 (Wed) 15:09
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECTINPUT )

#include <Windows.h>

#include "../../Include/MAPIL/Input/DIKeyboard.h"

namespace MAPIL
{
	DIKeyboard::DIKeyboard( SharedPointer < InputDevice > pDev ) : Keyboard( pDev )
	{
	}

	DIKeyboard::~DIKeyboard()
	{
	}

	MapilVoid DIKeyboard::GetKeyMap( MapilUChar* pOut )
	{
	}

	MapilBool DIKeyboard::IsPushed( MapilInt32 key )
	{
	}
}

#endif	// API_WIN32API