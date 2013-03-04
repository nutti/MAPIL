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
		INPUT_API_NONE			= 0,
		INPUT_API_WIN32API		= 1,
		INPUT_API_DIRECTINPUT	= 2,
		INPUT_API_UNKNOWN		= 3,
	};

	class InputDevice : public MapilObject
	{
		MapilInt32		m_API;
#if defined ( API_DIRECTINPUT )
		COMPointer < IDirectInput8 >		m_DI;		///< Direct input interface.
		::HWND								m_HWnd;		///< Window handle.
		::HINSTANCE							m_HInst;	///< Instance handle.
#endif
	public:
		explicit InputDevice( MapilInt32 api );
		~InputDevice();
		MapilVoid Create();
		MapilVoid Destroy();
#if defined ( API_WIN32API ) && defined ( API_DIRECTINPUT )
		COMPointer < IDirectInput8 > GetDev();
#endif
		MapilInt32 GetInputAPI() const;
	};

	typedef SharedPointer < InputDevice >		IInputDevice;

	IInputDevice CreateInputDevice( MapilInt32 api );

}

#endif
