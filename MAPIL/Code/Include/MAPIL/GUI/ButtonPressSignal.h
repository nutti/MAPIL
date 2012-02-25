/**
*	@file	ButtonPressSignal.h
*	@brief	
*	@date	2011.6.17(Fri) 22:53
*/

#ifndef INCLUDED_MAPIL_BUTTONPRESSSIGNAL_H
#define INCLUDED_MAPIL_BUTTONPRESSSIGNAL_H

#include "../CrossPlatform.h"

#include "Signal.h"
#include "../Type.h"

namespace MAPIL
{
	class ButtonPressSignal : public Signal
	{
	public:
		ButtonPressSignal();
		virtual ~ButtonPressSignal();
		virtual MapilVoid HandleButtonPress() = 0;
	};
}

#endif
