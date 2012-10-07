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
	SoundDevice::SoundDevice( MapilInt32 api ) : m_pDev( NULL ), m_API( api )
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
	
	MapilVoid SoundDevice::SetVolume( MapilUInt32 volume )
	{
		m_pDev->SetVolume( volume );
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

	MapilInt32 SoundDevice::GetSoundAPI() const
	{
		return m_API;
	}

	ISoundDevice CreateSoundDevice( MapilInt32 api )
	{
		SharedPointer < SoundDevice > pSD( new SoundDevice( api ) );

		return pSD;
	}
}
