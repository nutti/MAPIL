/**
*	@file	InputFactory.h
*	@brief	
*	@date	2011.7.23 (Sat) 20:21
*/

#ifndef INCLUDED_MAPIL_INPUTFACTORY_H
#define INCLUDED_MAPIL_INPUTFACTORY_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "../Util/SharedPointer.hpp"
#include "../TChar.h"

namespace MAPIL
{
	class Keyboard;
	class Mouse;
	class InputDevice;

	typedef SharedPointer < Keyboard >		IKeyboard;
	typedef SharedPointer < Mouse >			IMouse;

	class InputFactory : public MapilObject
	{
		SharedPointer < InputDevice >		m_pDev;
	public:
		InputFactory( SharedPointer < InputDevice > pDev );
		virtual ~InputFactory();
		virtual IKeyboard CreateKeyboard( const MapilTChar* pKeyStr ) = 0;
		virtual IMouse CreateMouse( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*/
		virtual MapilVoid Reflesh() = 0;
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*	@param Reflesh count.
		*/
		MapilVoid Reflesh( MapilInt32 count );
	};
}

#endif