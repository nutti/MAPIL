/**
*	@file	SoundDevice.h
*	@brief	
*	@date	2011.6.25(Sat) 10:32
*/

#ifndef INCLUDED_MAPIL_SOUNDDEVICE_H
#define INCLUDED_MAPIL_SOUNDDEVICE_H

#include "../CrossPlatform.h"

#if defined ( API_ALSA )
#include "ALSASoundDevice.h"
#elif defined( API_OPENAL )
#include "ALSoundDevice.h"
#endif

#include "../Util/MapilObject.h"
#include "../Type.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	enum SoundAPI
	{
		SOUND_API_UNKNOWN	= 0,
		SOUND_API_ALSA		= 1,
		SOUND_API_OPENAL	= 2,
	};

	class SoundDevice : public MapilObject
	{
#if defined ( API_ALSA )
		ALSASoundDevice*		m_pDev;
#elif defined ( API_OPENAL )
		ALSoundDevice*			m_pDev;
#else
		MapilVoid*				m_pDev;		// For dummy.
#endif
		SoundAPI				m_API;
	public:
		SoundDevice( SoundAPI api );
		~SoundDevice();
		MapilVoid Create();
		MapilVoid Destroy();
#if defined ( API_ALSA )
		ALSASoundDevice* GetDev() const;
#elif defined ( API_OPENAL )
		ALSoundDevice* GetDev() const;
#endif
	};

	typedef SharedPointer < SoundDevice >		ISoundDevice;

	ISoundDevice CreateSoundDevice( SoundAPI api );
}

#endif
