/**
*	@file	Sound.h
*	@brief	
*	@date	2011.6.25(Sat) 10:29
*/

#ifndef INCLUDED_MAPIL_SOUND_H
#define INCLUDED_MAPIL_SOUND_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "SoundDevice.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class SoundDevice;
	class Sound : public MapilObject
	{
	protected:
		SharedPointer < SoundDevice >			m_pDev;
	public:
		Sound( SharedPointer < SoundDevice > pDev );
		virtual ~Sound();
	};
}

#endif
