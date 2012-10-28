/**
*	@file	ButtonPushedSignal.h
*	@brief	ButtonPushedSignal class handles the event occurring when the button is pushed.
*	@date	2012.10.28 (Sun) 14:33
*/

#ifndef INCLUDED_MAPIL_BUTTONPUSHEDSIGNAL_H
#define INCLUDED_MAPIL_BUTTONPUSHEDSIGNAL_H

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
	class ButtonPushedSignal : public Signal
	{
	protected:
		MapilInt32				m_ID;		// ƒ{ƒ^ƒ“ID
	public:
		/**
		*	@brief Constructor.
		*/
		ButtonPushedSignal();
		/**
		*	@brief Destructor.
		*/
		virtual ~ButtonPushedSignal();
		/**
		*	@brief Handle the button checked signal.
		*/
		virtual MapilVoid Handle() = 0;
		MapilVoid SetID( int id );
		MapilInt32 GetID() const;
	};
}

#endif	// INCLUDED_MAPIL_EXPOSESIGNAL_H
