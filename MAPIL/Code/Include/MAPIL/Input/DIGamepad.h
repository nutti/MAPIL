/**
*	@file	DIGamepad.h
*	@brief	
*	@date	2012.5.20 (Sun) 15:20
*/

#ifndef INCLUDED_MAPIL_DIGAMEPAD_H
#define INCLUDED_MAPIL_DIGAMEPAD_H

#include "../CrossPlatform.h"

#if defined ( API_DIRECTINPUT )

#if defined ( API_DIRECTINPUT )
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#endif

#include "Mouse.h"
#include "../Util/SharedPointer.hpp"
#include "../GUI/WinAPIWindow.h"


namespace MAPIL
{
	class DIGamepad : public Input
	{
	private:
		::LPDIRECTINPUTDEVICE8			m_pGamepadDev;
		MapilBool						m_IsUsed;
		SharedPointer < WinAPIWindow >	m_pWnd;
		MapilBool						m_IsInputActive;

		struct CallBackParam
		{
			::IDirectInput8*				m_pDev;
			::LPDIRECTINPUTDEVICE8			m_pGamepadDev;
		};

		static BOOL CALLBACK GetGamepad( ::LPDIDEVICEINSTANCE pDIDev, LPVOID pParam );
	public:
		DIGamepad( SharedPointer < InputDevice > pDev );
		~DIGamepad();
		MapilVoid Create( SharedPointer < Window > pWnd );
		MapilBool IsPushed( MapilInt32 button );
	};
}

#endif	// API_DIRECTINPUT

#endif