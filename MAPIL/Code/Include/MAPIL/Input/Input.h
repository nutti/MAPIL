/**
*	@file	Input.h
*	@brief	
*	@date	2011.7.23 (Sat) 20:01
*/

#ifndef INCLUDED_MAPIL_INPUT_H
#define INCLUDED_MAPIL_INPUT_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "InputDevice.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class InputDevice;
	class Input : public MapilObject
	{
	protected:
		SharedPointer < InputDevice >		m_pDev;
	public:
		Input( SharedPointer < InputDevice > pDev );
		virtual ~Input();
	};
}

#endif