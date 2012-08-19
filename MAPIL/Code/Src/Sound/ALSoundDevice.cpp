/**
*	@file	ALSoundDevice.cpp
*	@brief	Implementation of ALSoundDevice.
*	@date	2011.7.9 (Sat) 11:47
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_OPENAL

#include "../../Include/MAPIL/Sound/ALSoundDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	ALSoundDevice::ALSoundDevice() : m_pDev( NULL ), m_pContext( NULL )
	{
	}

	ALSoundDevice::~ALSoundDevice()
	{
		alcMakeContextCurrent( NULL );
		alcDestroyContext( m_pContext );
		alcCloseDevice( m_pDev );
	}

	MapilVoid ALSoundDevice::Init()
	{
		m_pDev = alcOpenDevice( NULL );
		m_pContext = alcCreateContext( m_pDev, NULL );
		alcMakeContextCurrent( m_pContext );
	}

	MapilVoid ALSoundDevice::SetVolume( MapilUInt32 volume )
	{
		if( volume > 100 ){
			volume = 100;
		}
		::alListenerf( AL_GAIN, volume / 100.0f );
	}
}

#endif	// API_OPENAL