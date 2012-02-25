/**
*	@file	ALSoundFactory.cpp
*	@brief	Implementation of ALSoundFactory.
*	@date	2011.8.6 (Sat) 21:18
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENAL )

#include "../../Include/MAPIL/Sound/ALSoundFactory.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	ALSoundFactory::ALSoundFactory( SharedPointer < SoundDevice > pDev ) :	SoundFactory( pDev ),
																			m_StaticBufRM( pDev ),
																			m_StreamingBufRM( pDev )
	{
		m_StaticBufRM.Init();
		m_StreamingBufRM.Init();
	}

	ALSoundFactory::~ALSoundFactory()
	{
	}

	IStaticBuffer ALSoundFactory::CreateStaticBuffer( const MapilTChar* pKeyStr )
	{
		return m_StaticBufRM.Create( pKeyStr );
	}

	IStreamingBuffer ALSoundFactory::CreateStreamingBuffer( const MapilTChar* pKeyStr )
	{
		return m_StreamingBufRM.Create( pKeyStr );
	}

	MapilVoid ALSoundFactory::Reflesh()
	{
		m_StaticBufRM.Reflesh();
		m_StreamingBufRM.Reflesh();
	}

}

#endif	// API_OPENAL