/**
*	@file	SoundDevice.cpp
*	@brief	
*	@date	2011.6.25(Sat) 10:54
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Sound/SoundDevice.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

namespace MAPIL
{
	SoundDevice::SoundDevice( SoundAPI api ) : Device() , m_pDev( NULL ), m_API( api )
	{
	}
	
	SoundDevice::~SoundDevice()
	{
		SafeDelete( m_pDev );
		m_API = SOUND_API_UNKNOWN;
	}
	
	MapilVoid SoundDevice::Create()
	{
#if defined ( API_ALSA )
		m_pDev = new ALSASoundDevice();
#elif defined ( API_OPENAL )
		m_pDev = new ALSoundDevice();
		m_pDev->Init();
#endif
	}
	
	MapilVoid SoundDevice::Destroy()
	{
		SafeDelete( m_pDev );
	}
	
#if defined ( API_ALSA )
	ALSASoundDevice* SoundDevice::GetDev() const
	{
		return m_pDev;
	}
#elif defined ( API_OPENAL )
	ALSoundDevice* SoundDevice::GetDev() const
	{
		return m_pDev;
	}
#endif

	ISoundDevice CreateSoundDevice( SoundAPI api )
	{
		SharedPointer < SoundDevice > pSD( new SoundDevice( api ) );

		return pSD;
	}
}
