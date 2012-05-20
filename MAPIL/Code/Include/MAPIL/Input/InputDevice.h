/**
*	@file	InputDevice.h
*	@brief	
*	@date	2011.7.23 (Sat) 19:54
*/

#ifndef INCLUDED_MAPIL_INPUTDEVICE_H
#define INCLUDED_MAPIL_INPUTDEVICE_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "../Type.h"
#include "../Util/SharedPointer.hpp"
#include "../Util/COMPointer.hpp"

#if defined ( API_DIRECTINPUT )
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#endif

namespace MAPIL
{
	enum InputAPI
	{
		INPUT_API_UNKNOWN	= 0,
		INPUT_API_WIN32API	= 1,
		INPUT_API_DIRECTINPUT = 2,
	};

	class InputDevice : public MapilObject
	{
		InputAPI		m_API;
#if defined ( API_DIRECTINPUT )
		COMPointer < IDirectInput8 >		m_DI;		///< Direct input interface.
		::HWND								m_HWnd;		///< Window handle.
		::HINSTANCE							m_HInst;	///< Instance handle.
#endif
	public:
		InputDevice( InputAPI api );
		~InputDevice();
		MapilVoid Create();
		MapilVoid Destroy();
		COMPointer < IDirectInput8 > GetDev();
		InputAPI GetInputAPI() const;
	};

	typedef SharedPointer < InputDevice >		IInputDevice;

	IInputDevice CreateInputDevice( InputAPI api );

}

#endif