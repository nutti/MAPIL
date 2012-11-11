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
		SOUND_API_NONE		= 0,
		SOUND_API_ALSA		= 1,
		SOUND_API_OPENAL	= 2,
		SOUND_API_UNKNOWN	= 3,
	};

	class SoundDevice : public MapilObject
	{
#if defined ( API_ALSA )
		ALSASoundDevice*		m_pDev;
#elif defined ( API_OPENAL )
		ALSoundDevice*			m_pDev;
#endif
		MapilInt32				m_API;
	public:
		explicit SoundDevice( MapilInt32 api );
		~SoundDevice();
		MapilVoid Create();
		MapilVoid Destroy();
		/**
		*	@brief			Set master volume.
		*	@param volume	Volume.
		*/
		MapilVoid SetVolume( MapilUInt32 volume );
#if defined ( API_ALSA )
		ALSASoundDevice* GetDev() const;
#elif defined ( API_OPENAL )
		ALSoundDevice* GetDev() const;
#endif
		MapilInt32 GetSoundAPI() const;
	};

	typedef SharedPointer < SoundDevice >		ISoundDevice;

	ISoundDevice CreateSoundDevice( MapilInt32 api );
}

#endif

