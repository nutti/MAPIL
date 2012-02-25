/**
*	@file	Device.h
*	@brief	Device class is the base class for the device of each module.
*	@date	2011.6.15 (Wed) 17:44
*/

#ifndef INCLUDED_MAPIL_DEVICE_H
#define INCLUDED_MAPIL_DEVICE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "MapilObject.h"
#include "../Type.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class Device : public MapilObject
	{
	public:
		/**
		*	@brief Constructor.
		*/
		Device();
		/**
		*	@brief Destructor.
		*/
		virtual ~Device();
	};
}

#endif	// INCLUDED_MAPIL_DEVICE_H
