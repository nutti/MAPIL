/**
*	@file	ExposeSignal.h
*	@brief	ExposeSignal class handles the event occurring when the window appears.
*	@date	2011.6.17 (Fri) 16:32
*/

#ifndef INCLUDED_MAPIL_EXPOSESIGNAL_H
#define INCLUDED_MAPIL_EXPOSESIGNAL_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Signal.h"
#include "../Type.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class ExposeSignal : public Signal
	{
	public:
		/**
		*	@brief Constructor.
		*/
		ExposeSignal();
		/**
		*	@brief Destructor.
		*/
		virtual ~ExposeSignal();
		/**
		*	@brief Handle the expose signal.
		*/
		virtual MapilVoid Handle() = 0;
	};
}

#endif	// INCLUDED_MAPIL_EXPOSESIGNAL_H
