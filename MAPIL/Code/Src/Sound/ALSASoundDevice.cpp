/**
*	@file	ALSASoundDevice.cpp
*	@brief	Implementation of ALSASoundDevice class.
*	@date	2011.6.25 (Sat) 11:00
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_ALSA

#include "../../Include/MAPIL/Sound/ALSASoundDevice.h"


//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{

	// Constructor.
	ALSASoundDevice::ALSASoundDevice() :	m_pHandle( NULL ),
											m_Mode( PCM_DEV_OPEN_NONE_MODE ),
											m_pParam( NULL )
	{
	}

	// Destructor.
	ALSASoundDevice::~ALSASoundDevice()
	{
		snd_pcm_drain( m_pHandle );
		snd_pcm_close( m_pHandle );
		m_Mode = PCM_DEV_OPEN_NONE_MODE;
	}

	// Open.
	MapilVoid ALSASoundDevice::Open( PCMDeviceOpenMode mode )
	{
		snd_pcm_stream_t openMod[] = {	SND_PCM_STREAM_PLAYBACK,
										SND_PCM_STREAM_CAPTURE };
		m_Mode = mode;
		if( snd_pcm_open( &m_pHandle, "default", openMod[ mode - 1 ] , 0 ) < 0 ){
			exit( 1 );
		}
	}

	// Close.
	MapilVoid ALSASoundDevice::Close()
	{
		snd_pcm_close( m_pHandle );
	}

	// Set device parameters.
	MapilVoid ALSASoundDevice::SetParam( PCMDevConf* pConf )
	{
		_snd_pcm_format pcmFmt[] = {	SND_PCM_FORMAT_UNKNOWN,
										SND_PCM_FORMAT_U8,
										SND_PCM_FORMAT_S8,
										SND_PCM_FORMAT_U16_LE,
										SND_PCM_FORMAT_U16_BE,
										SND_PCM_FORMAT_S16_LE,
										SND_PCM_FORMAT_S16_BE };

		// Allocate hardware parameter.
		snd_pcm_hw_params_alloca( &m_pParam );
		// Get default hardware parameter.
		snd_pcm_hw_params_any( m_pHandle, m_pParam );

		// Set parameters.
		snd_pcm_hw_params_set_access( m_pHandle, m_pParam, SND_PCM_ACCESS_RW_INTERLEAVED );
		snd_pcm_hw_params_set_format( m_pHandle, m_pParam, pcmFmt[ pConf->m_Fmt ] );
		snd_pcm_hw_params_set_channels( m_pHandle, m_pParam, pConf->m_Channel );
		MapilInt32 val;
		snd_pcm_hw_params_set_rate_near( m_pHandle, m_pParam, &pConf->m_Freq, &val );
		snd_pcm_uframes_t frame = 32;
		snd_pcm_hw_params_set_period_size_near( m_pHandle, m_pParam, &frame, &val );

		if( snd_pcm_hw_params( m_pHandle, m_pParam ) < 0 ){
			exit( 1 );
		}
	}

	// Write.
	MapilVoid ALSASoundDevice::Write(	const MapilChar* pData,
											MapilInt32 dataSize )
	{
		snd_pcm_sframes_t frame;
		frame = snd_pcm_writei( m_pHandle, reinterpret_cast < const void* > ( pData ), dataSize );
	}

	// Write.
	MapilVoid ALSASoundDevice::Write(	const MapilShortInt32* pData,
											MapilInt32 dataSize )
	{
		snd_pcm_sframes_t frame;
		frame = snd_pcm_writei( m_pHandle, reinterpret_cast < const void* > ( pData ), dataSize );
	}

	// Read.
	MapilVoid ALSASoundDevice::Read(	MapilChar* pData,
										MapilInt32 dataSize )
	{
		snd_pcm_sframes_t frame;
		frame = snd_pcm_readi( m_pHandle, pData, dataSize );
		if( frame < 0 ){
			frame = snd_pcm_recover( m_pHandle, frame, 0 );
			if( frame < 0 ){
				exit( 1 );
			}
		}
	}
	
}

#endif	// API_ALSA