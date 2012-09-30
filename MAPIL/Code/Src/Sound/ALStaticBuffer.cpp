/**
*	@file	ALStaticBuffer.cpp
*	@brief	Implementation of ALStaticBuffer.
*	@date	2011.7.9 (Sat) 17:12
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENAL )

#include "../../Include/MAPIL/IO/Archiver.h"
#include "../../Include/MAPIL/Sound/ALStaticBuffer.h"
#include "../../Include/MAPIL/Sound/SoundDevice.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Util/String.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	ALStaticBuffer::ALStaticBuffer( SharedPointer < SoundDevice > pDev ) :	StaticBuffer( pDev ),
																			m_pWavFile( NULL ),
																			m_pWavData( NULL ),
																			m_DataSize( 0 ),
																			m_IsPlaying( MapilFalse ),
																			m_IsPausing( MapilFalse ),
																			m_Volume( 100 )
	{
		ZeroObject( m_Pos, sizeof( m_Pos ) );
	}

	ALStaticBuffer::~ALStaticBuffer()
	{
		Destroy();

		if( m_pWavFile ){
			m_pWavFile->Close();
		}
		SafeDelete( m_pWavFile );
		SafeDeleteArray( m_pWavData );
		m_DataSize = 0;

		alDeleteSources( 1, &m_Src );
		alDeleteBuffers( 1, &m_Buf );

		ZeroObject( m_Pos, sizeof( m_Pos ) );
	}

	MapilVoid ALStaticBuffer::Create( const MapilTChar* pFileName )
	{
		MapilChar name[ 1024 ];
		ConvertToMultiByte( pFileName, -1, name, 1024 );

		alGenSources( 1, &m_Src );
		alGenBuffers( 1, &m_Buf );

		m_pWavFile = new WAVFile();
		m_pWavFile->Open( name, FILE_OPEN_READ_MODE );
		m_pWavFile->LoadHeader();
		m_pWavFile->LoadInfo();
		
		// Calculate size of sound data.
		m_DataSize = m_pWavFile->GetInfoPos() - m_pWavFile->GetDataPos();
		MapilInt32 size = 0;
		
		// Load sound data.
		m_pWavData = new MapilChar[ m_DataSize ];
		m_pWavFile->Load(	m_pWavFile->GetDataPos(),
							m_pWavFile->GetInfoPos(),
							m_pWavData,
							&size,
							m_DataSize );

		WAVFileHeader wfh = m_pWavFile->GetWAVFileHeader();

		// Format.
		ALenum fmt;
		if( wfh.m_NumChannel == 1 ){
			fmt = ( wfh.m_BitPerSample == 8 ) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
		}
		else{
			fmt = ( wfh.m_BitPerSample == 8 ) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
		}

		alBufferData( m_Buf, fmt, m_pWavData, m_DataSize, wfh.m_SampleRate );
		alSourcei( m_Src, AL_BUFFER, m_Buf );
	}

	MapilVoid ALStaticBuffer::Create( Archiver* pArchiver, const MapilTChar* pFileName )
	{
		MapilChar name[ 1024 ];
		ConvertToMultiByte( pFileName, -1, name, 1024 );

		alGenSources( 1, &m_Src );
		alGenBuffers( 1, &m_Buf );

		MapilInt32 size = pArchiver->GetContentsSize( name );
		m_pWavData = new MapilChar [ size ];
		pArchiver->Load( name, m_pWavData );

		WAVFileHeader wfh;
		GetWAVFileHeader( m_pWavData, &wfh );

		SafeDeleteArray( m_pWavData );

		MapilInt32 readSize = 0;
		m_pWavData = new MapilChar [ size - 44 ];
		pArchiver->Load( name, m_pWavData, 44, size - 44, &readSize );

		// Format.
		ALenum fmt;
		if( wfh.m_NumChannel == 1 ){
			fmt = ( wfh.m_BitPerSample == 8 ) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
		}
		else{
			fmt = ( wfh.m_BitPerSample == 8 ) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
		}

		alBufferData( m_Buf, fmt, m_pWavData, size - 44, wfh.m_SampleRate );
		alSourcei( m_Src, AL_BUFFER, m_Buf );

	}

	MapilVoid ALStaticBuffer::Play()
	{
		alSourcePlay( m_Src );
		m_IsPlaying = MapilTrue;
		m_IsPausing = MapilFalse;
	}

	MapilVoid ALStaticBuffer::Stop()
	{
		alSourceStop( m_Src );
		m_IsPlaying = MapilFalse;
		m_IsPausing = MapilFalse;
	}

	MapilVoid ALStaticBuffer::Pause()
	{
		::alSourcePause( m_Src );
		m_IsPlaying = MapilFalse;
		m_IsPausing = MapilTrue;
	}

	MapilVoid ALStaticBuffer::Destroy()
	{
		m_IsPlaying = MapilFalse;
		m_IsPausing = MapilFalse;
	}

	MapilVoid ALStaticBuffer::SetVolume( MapilUInt32 volume )
	{
		if( volume > 100 ){
			m_Volume = 100;
		}
		m_Volume = volume;
		::alSourcef( m_Src, AL_GAIN, m_Volume / 100.0f );
	}

	MapilVoid ALStaticBuffer::SetPosition( const Vector3 < MapilFloat32 >& pos )
	{
		m_Pos[ 0 ] = pos.m_X;
		m_Pos[ 1 ] = pos.m_Y;
		m_Pos[ 2 ] = pos.m_Z;

		alSource3f( m_Src, AL_POSITION, m_Pos[ 0 ], m_Pos[ 1 ], m_Pos[ 2 ] );
	}

	MapilBool ALStaticBuffer::IsPausing() const
	{
		return m_IsPausing;
	}

	MapilBool ALStaticBuffer::IsStopping() const
	{
		return !m_IsPlaying;
	}
}

#endif	// API_OPENAL