/**
*	@file	KeyboardSignal.h
*	@brief	
*	@date	2011.7.22 (Fri) 21:03
*/

#ifndef INCLUDED_MAPIL_KEYBOARDSIGNAL_H
#define INCLUDED_MAPIL_KEYBOARDSIGNAL_H

#include "../CrossPlatform.h"

#include "Signal.h"
#include "../Type.h"

namespace MAPIL
{
	class KeyboardSignal : public Signal
	{
	public:
		KeyboardSignal();
		virtual ~KeyboardSignal();
		virtual MapilVoid Handle() = 0;
	};
}

#endif
