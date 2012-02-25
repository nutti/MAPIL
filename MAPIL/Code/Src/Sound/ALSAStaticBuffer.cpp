/**
*	@file	ALSAStaticBuffer.cpp
*	@brief	Implementation of ALSAStaticBuffer class.
*	@date	2011.7.3 (Sun) 11:35
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_ALSA

#include "../../Include/MAPIL/Sound/ALSAStaticBuffer.h"
#include "../../Include/MAPIL/Sound/SoundDevice.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	ALSAStaticBuffer::ALSAStaticBuffer( SharedPointer < SoundDevice > pDev ) :	StaticBuffer( pDev ),
																				m_pWavFile( NULL ),
																				m_pWavData( NULL ),
																				m_DataSize( 0 )
	{
	}
	
	ALSAStaticBuffer::~ALSAStaticBuffer()
	{
		m_pWavFile->Close();
		SafeDelete( m_pWavFile );
		SafeDeleteArray( m_pWavData );
		m_DataSize = 0;
	}
	
	MapilVoid ALSAStaticBuffer::Create( const MapilChar* pFileName )
	{
		// Analyze WAV file.
		m_pWavFile = new WAVFile();
		m_pWavFile->Open( pFileName, FILE_OPEN_READ_MODE );
		m_pWavFile->LoadHeader();
		m_pWavFile->LoadInfo();
		
		// Calculate size of sound data.
		m_DataSize = m_pWavFile->GetFileSize() - m_pWavFile->GetDataPos();
		MapilInt32 size = 0;
		
		// Load sound data.
		m_pWavData = new MapilChar[ m_DataSize ];
		m_pWavFile->Load(	m_pWavFile->GetDataPos(),
							m_pWavFile->GetFileSize(),
							m_pWavData,
							&size,
							m_DataSize );
		
		
		// 名前が被る可能性があるので、ALSAPCMDevConfにする。
		// Open and configure ALSA device.
		PCMDevConf conf;
		conf.m_Fmt = PCM_DEV_FMT_SIGNED_16BIT_LE;				// WAV format.
		conf.m_Channel = m_pWavFile->GetNumChannel();			// Number of channel.
		conf.m_Freq = m_pWavFile->GetSampleRate();				// Sampling rate.
		m_pDev->GetDev()->Open( PCM_DEV_OPEN_WRITE_MODE );
		m_pDev->GetDev()->SetParam( &conf );
	}
	
	MapilVoid ALSAStaticBuffer::Play()
	{
		m_pDev->GetDev()->Write( m_pWavData, m_DataSize );
	}
	
	MapilVoid ALSAStaticBuffer::Stop()
	{
	}
	
	MapilVoid ALSAStaticBuffer::Pause()
	{
	}
	
	MapilVoid ALSAStaticBuffer::Destroy()
	{
	}
	
	MapilVoid ALSAStaticBuffer::SetVolume()
	{
	}
}

#endif	// API_ALSA