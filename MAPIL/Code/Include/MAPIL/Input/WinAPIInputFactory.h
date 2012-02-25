/**
*	@file	WinAPIInputFactory.h
*	@brief	
*	@date	2011.7.23 (Sat) 20:28
*/

#ifndef INCLUDED_MAPIL_WINAPIINPUTFACTORY_H
#define INCLUDED_MAPIL_WINAPIINPUTFACTORY_H

#include "../CrossPlatform.h"

#ifdef API_WIN32API

#include "InputFactory.h"
#include "ConstNums.h"
#include "WinAPIKeyboard.h"
#include "WinAPIMouse.h"
#include "InputResourceManager.hpp"

namespace MAPIL
{

	class WinAPIInputFactory : public InputFactory
	{
		InputResourceManager < WinAPIKeyboard >		m_KeyboardRM;
		InputResourceManager < WinAPIMouse >		m_MouseRM;
	public:
		WinAPIInputFactory( SharedPointer < InputDevice > pDev );
		~WinAPIInputFactory();
		IKeyboard CreateKeyboard( const MapilTChar* pKeyStr );
		IMouse CreateMouse( const MapilTChar* pKeyStr );
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*/
		MapilVoid Reflesh();
	};
}

#endif	// API_WIN32API

#endif