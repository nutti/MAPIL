/**
*	@file	DIInputFactory.h
*	@brief	
*	@date	2012.5.20 (Sun) 8:53
*/

#ifndef INCLUDED_MAPIL_DIINPUTFACTORY_H
#define INCLUDED_MAPIL_DIINPUTFACTORY_H

#include "../CrossPlatform.h"

#if defined ( API_WIN32API )
#if defined ( API_DIRECTINPUT )

#include "InputFactory.h"
#include "ConstNums.h"
#include "DIKeyboard.h"
#include "DIMouse.h"
#include "InputResourceManager.hpp"

namespace MAPIL
{

	class DIInputFactory : public InputFactory
	{
		InputResourceManager < DIKeyboard >		m_KeyboardRM;
		InputResourceManager < DIMouse >		m_MouseRM;
	public:
		DIInputFactory( SharedPointer < InputDevice > pDev );
		~DIInputFactory();
		IKeyboard CreateKeyboard( const MapilTChar* pKeyStr );
		IMouse CreateMouse( const MapilTChar* pKeyStr );
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*/
		MapilVoid Reflesh();
	};
}

#endif	// API_DIRECTINPUT
#endif	// API_WIN32API

#endif