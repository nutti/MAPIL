/**
*	@file	InputDevice.cpp
*	@brief	
*	@date	2011.7.23 (Sat) 19:57
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Input/InputDevice.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

namespace MAPIL
{
	InputDevice::InputDevice( InputAPI api ) :  m_API( api )
	{
	}

	InputDevice::~InputDevice()
	{
		Destroy();
		m_API = INPUT_API_UNKNOWN;
	}

	MapilVoid InputDevice::Create()
	{
	}

	MapilVoid InputDevice::Destroy()
	{
	}

	InputAPI InputDevice::GetInputAPI() const
	{
		return m_API;
	}

	IInputDevice CreateInputDevice( InputAPI api )
	{
		SharedPointer < InputDevice > pID( new InputDevice( api ) );

		return pID;
	}

	
}