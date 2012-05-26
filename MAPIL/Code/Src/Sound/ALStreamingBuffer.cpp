/**
*	@file	ALStreamingBuffer.cpp
*	@brief	Implementation of ALStreamingBuffer.
*	@date	2011.7.18 (Mon) 16:13
*/

#include "../../Include/MAPIL/CrossPlatform.h"

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#ifdef API_OPENAL

#if defined ( API_WIN32API )
#include <Windows.h>
#endif

#include "../../Include/MAPIL/IO/Archiver.h"
#include "../../Include/MAPIL/Sound/ALStreamingBuffer.h"
#include "../../Include/MAPIL/Sound/SoundDevice.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Util/String.h"

#include <iostream>

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{

#if defined ( API_WIN32API )
	ALStreamingBuffer::ALStreamingBuffer( SharedPointer < SoundDevice > pDev ) :	StreamingBuffer( pDev ),
																					m_pWavFile( NULL ),
																					m_pArchiver( NULL ),
																					m_DataSize( 0 ),
																					m_IsPlaying( MapilFalse ),
																					m_IsPausing( MapilFalse ),
																					m_HasTermSig( MapilFalse ),
																					m_HasExtArchive( MapilFalse )
	{
		ZeroObject( m_Pos, sizeof( m_Pos ) );
	}

	ALStreamingBuffer::~ALStreamingBuffer()
	{
		Destroy();
	
		if( m_pWavFile ){
			m_pWavFile->Close();
		}
		SafeDelete( m_pWavFile );
		if( !m_HasExtArchive ){
			SafeDelete( m_pArchiver );
		}
		m_DataSize = 0;

		alSourceStop( m_Src );
		alDeleteSources( 1, &m_Src );
		alDeleteBuffers( 2, m_Bufs );

		ZeroObject( m_Pos, sizeof( m_Pos ) );
	}

	MapilInt32 ALStreamingBuffer::WAVFileThread()
	{
		while( !m_HasTermSig ){
			if( m_IsPlaying ){

				WAVFileHeader wfh = m_pWavFile->GetWAVFileHeader();

				// Format.
				ALenum fmt;
				if( wfh.m_NumChannel == 1 ){
					fmt = ( wfh.m_BitPerSample == 8 ) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
				}
				else{
					fmt = ( wfh.m_BitPerSample == 8 ) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
				}
				MapilInt32 empty = 0;						// Number of empty.
				MapilChar data[ 4 * 1024 * 25 ];			// Wav data.
				MapilInt32 size;							// Read size.
				MapilInt32 offset = 0;						// Offset.

				// Load wav data.
				for( MapilInt32 i = 0; i < 2; ++i ){
					m_pWavFile->Load(	m_pWavFile->GetDataPos() + offset,
										m_pWavFile->GetInfoPos(),
										data,
										&size,
										sizeof( data ) );
					offset += size;
					alGenBuffers( 1, &m_Bufs[ i ] );
					alBufferData( m_Bufs[ i ], fmt, data, size, wfh.m_SampleRate );
				}

				// Create queue.
				alSourceQueueBuffers( m_Src, 2, m_Bufs );

				alSourcePlay( m_Src );

				while( 1 ){
					ALint state;
					alGetSourcei( m_Src, AL_SOURCE_STATE, &state );
					// Replay if the buffer becomes empty.
					if( ( state == AL_STOPPED && m_IsPlaying ) || state == AL_PAUSED ){
						alSourcePlay( m_Src );
					}
					alGetSourcei( m_Src, AL_BUFFERS_PROCESSED, &empty );
					while( empty >= 1 ){
						ALuint buf;
						alSourceUnqueueBuffers( m_Src, 1, &buf );
						alGenBuffers( 1, &buf );
						m_pWavFile->Load(	m_pWavFile->GetDataPos() + offset,
											m_pWavFile->GetInfoPos(),
											data,
											&size,
											sizeof( data ) );
						offset += size;
						alBufferData( buf, fmt, data, size, wfh.m_SampleRate );

						alSourceQueueBuffers( m_Src, 1, &buf );
						--empty;
					}
					Sleep( 1 );
					// Pause state
					while( m_IsPausing && m_IsPlaying ){
						Sleep( 1 );
					}
					if( !m_IsPlaying ){
						break;
					}
				}
			}
			else{
				Sleep( 1 );
			}
		}
		
		return 0;
	}

	MapilInt32 ALStreamingBuffer::ArchiverThread()
	{
		while( !m_HasTermSig ){
			if( m_IsPlaying ){

				WAVFileHeader wfh = m_pWavFile->GetWAVFileHeader();

				// Format.
				ALenum fmt;
				if( wfh.m_NumChannel == 1 ){
					fmt = ( wfh.m_BitPerSample == 8 ) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
				}
				else{
					fmt = ( wfh.m_BitPerSample == 8 ) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
				}
				MapilInt32 empty = 0;						// Number of empty.
				MapilChar data[ 4 * 1024 * 25 ];			// Wav data.
				MapilInt32 size;							// Read size.
				MapilInt32 offset = 0;						// Offset.

				// Load wav data.
				for( MapilInt32 i = 0; i < 2; ++i ){
					m_pArchiver->Load(	m_FileName.c_str(),
										data,
										m_pWavFile->GetDataPos() + offset,
										sizeof( data ),
										&size );
					offset += size;
					alGenBuffers( 1, &m_Bufs[ i ] );
					alBufferData( m_Bufs[ i ], fmt, data, size, wfh.m_SampleRate );
				}

				// Create queue.
				alSourceQueueBuffers( m_Src, 2, m_Bufs );

				alSourcePlay( m_Src );

				while( 1 ){
					ALint state;
					alGetSourcei( m_Src, AL_SOURCE_STATE, &state );
					// Replay if the buffer becomes empty.
					if( ( state == AL_STOPPED && m_IsPlaying ) || state == AL_PAUSED ){
						alSourcePlay( m_Src );
					}
					alGetSourcei( m_Src, AL_BUFFERS_PROCESSED, &empty );
					while( empty >= 1 ){
						ALuint buf;
						alSourceUnqueueBuffers( m_Src, 1, &buf );
						alGenBuffers( 1, &buf );
						m_pArchiver->Load(	m_FileName.c_str(),
											data,
											m_pWavFile->GetDataPos() + offset,
											sizeof( data ),
											&size );
						offset += size;
						alBufferData( buf, fmt, data, size, wfh.m_SampleRate );

						alSourceQueueBuffers( m_Src, 1, &buf );
						--empty;
					}
					Sleep( 1 );
					// Pause state
					while( m_IsPausing && m_IsPlaying ){
						Sleep( 1 );
					}
					if( !m_IsPlaying ){
						break;
					}
				}
			}
			else{
				Sleep( 1 );
			}
		}

		return 0;
	}

	MapilInt32 ALStreamingBuffer::ThreadFunc()
	{
		MapilInt32 ret = 0;

		if( m_HasWavFile ){
			ret = WAVFileThread();
		}
		else{
			ret = ArchiverThread();
		}

		return ret;
	}

	MapilVoid ALStreamingBuffer::Create( const MapilTChar* pFileName )
	{
		MapilChar name[ 1024 ];
		ConvertToMultiByte( pFileName, -1, name, 1024 );

		alGenSources( 1, &m_Src );

		m_pWavFile = new WAVFile();
		m_pWavFile->Open( name, FILE_OPEN_READ_MODE );
		m_pWavFile->LoadHeader();
		m_pWavFile->LoadInfo();
		
		// Calculate size of sound data.
		m_DataSize = m_pWavFile->GetInfoPos() - m_pWavFile->GetDataPos();

		m_HasWavFile = MapilTrue;

		WinAPIThread::Create();
	}

	MapilVoid ALStreamingBuffer::Create( const MapilTChar* pArchiveFileName, const MapilTChar* pFileName )
	{
		m_pArchiver = new Archiver();
		MapilChar name[ 1024 ];
		ConvertToMultiByte( pArchiveFileName, -1, name, 1024 );
		m_pArchiver->Open( name, FILE_OPEN_READ_MODE );

		ConvertToMultiByte( pFileName, -1, name, 1024 );
		m_FileName = name;

		alGenSources( 1, &m_Src );

		// Get WAVFileHeader.
		MapilInt32 size = m_pArchiver->GetContentsSize( name );
		MapilChar* pWavData = new MapilChar [ size ];
		m_pArchiver->Load( name, pWavData );
		WAVFileHeader wfh;
		GetWAVFileHeader( pWavData, &wfh );
		SafeDeleteArray( pWavData );

		m_pWavFile = new WAVFile();
		m_pWavFile->SetWAVFileHeader( wfh );

		m_DataSize = size - 44;

		m_HasWavFile = MapilFalse;
		m_HasExtArchive = MapilFalse;

		WinAPIThread::Create();
	}

	MapilVoid ALStreamingBuffer::Create( Archiver* pArchiver, const MapilTChar* pFileName )
	{
		m_pArchiver = pArchiver;

		MapilChar name[ 1024 ];
		ConvertToMultiByte( pFileName, -1, name, 1024 );

		alGenSources( 1, &m_Src );

		// Get WAVFileHeader.
		MapilInt32 size = m_pArchiver->GetContentsSize( name );
		MapilChar* pWavData = new MapilChar [ size ];
		m_pArchiver->Load( name, pWavData );
		WAVFileHeader wfh;
		GetWAVFileHeader( pWavData, &wfh );
		SafeDeleteArray( pWavData );

		m_pWavFile = new WAVFile();
		m_pWavFile->SetWAVFileHeader( wfh );

		m_DataSize = size - 44;

		m_HasWavFile = MapilFalse;
		m_HasExtArchive = MapilTrue;

		WinAPIThread::Create();
	}

	MapilVoid ALStreamingBuffer::Play()
	{
		m_IsPlaying = MapilTrue;
		m_IsPausing = MapilFalse;
	}

	MapilVoid ALStreamingBuffer::Stop()
	{
		alSourceStop( m_Src );
		m_IsPlaying = MapilFalse;
		m_IsPausing = MapilFalse;
	}

	MapilVoid ALStreamingBuffer::Pause()
	{
		::alSourcePause( m_Src );
		m_IsPausing = MapilTrue;
	}

	MapilVoid ALStreamingBuffer::Destroy()
	{
		m_HasTermSig = MapilTrue;
		m_IsPlaying = MapilFalse;
	}

	MapilVoid ALStreamingBuffer::SetVolume( MapilFloat32 volume )
	{
		m_Volume = volume;
		alSourcef( m_Src, AL_GAIN, m_Volume );
	}

	MapilVoid ALStreamingBuffer::SetPosition( const Vector3 < MapilFloat32 >& pos )
	{
		m_Pos[ 0 ] = pos.m_X;
		m_Pos[ 1 ] = pos.m_Y;
		m_Pos[ 2 ] = pos.m_Z;

		alSource3f( m_Src, AL_POSITION, m_Pos[ 0 ], m_Pos[ 1 ], m_Pos[ 2 ] );
	}


#elif defined ( API_POSIX )
	ALStreamingBuffer::ALStreamingBuffer( SharedPointer < SoundDevice > pDev ) :	StreamingBuffer( pDev ),
																					m_pWavFile( NULL ),
																					m_DataSize( 0 ),
																					m_IsPlaying( MapilFalse ),
																					m_HasTermSig( MapilFalse )
	{
	}

	ALStreamingBuffer::~ALStreamingBuffer()
	{
		Destroy();
	
		if( m_pWavFile ){
			m_pWavFile->Close();
		}
		SafeDelete( m_pWavFile );
		m_DataSize = 0;

		alSourceStop( m_Src );
		alDeleteSources( 1, &m_Src );
		alDeleteBuffers( 2, m_Bufs );
	}

	MapilInt32 ALStreamingBuffer::ThreadFunc()
	{
		while( !m_HasTermSig ){
			if( m_IsPlaying ){

				WAVFileHeader wfh = m_pWavFile->GetWAVFileHeader();

				// Format.
				ALenum fmt;
				if( wfh.m_NumChannel == 1 ){
					fmt = ( wfh.m_BitPerSample == 8 ) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
				}
				else{
					fmt = ( wfh.m_BitPerSample == 8 ) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
				}
				MapilInt32 empty = 0;						// Number of empty.
				MapilChar data[ 4 * 1024 * 25 ];			// Wav data.
				MapilInt32 size;							// Read size.
				MapilInt32 offset = 0;						// Offset.

				// Load wav data.
				for( MapilInt32 i = 0; i < 2; ++i ){
					m_pWavFile->Load(	m_pWavFile->GetDataPos() + offset,
										m_pWavFile->GetInfoPos(),
										data,
										&size,
										sizeof( data ) );
					offset += size;
					alGenBuffers( 1, &m_Bufs[ i ] );
					alBufferData( m_Bufs[ i ], fmt, data, size, wfh.m_SampleRate );
				}

				// Create queue.
				alSourceQueueBuffers( m_Src, 2, m_Bufs );

				alSourcePlay( m_Src );

				while( 1 ){
					alGetSourcei( m_Src, AL_BUFFERS_PROCESSED, &empty );
					while( empty >= 1 ){
						ALuint buf;
						alSourceUnqueueBuffers( m_Src, 1, &buf );

						alGenBuffers( 1, &buf );
						m_pWavFile->Load(	m_pWavFile->GetDataPos() + offset,
											m_pWavFile->GetInfoPos(),
											data,
											&size,
											sizeof( data ) );
						offset += size;
						alBufferData( buf, fmt, data, size, wfh.m_SampleRate );

						alSourceQueueBuffers( m_Src, 1, &buf );
						--empty;
					}
					usleep( 1 );
					if( !m_IsPlaying ){
						break;
					}
				}
			}
			else{
				usleep( 1 );
			}
		}
		
		return 0;
	}

	MapilVoid ALStreamingBuffer::Create( const MapilTChar* pFileName )
	{
		MapilChar name[ 1024 ];
		ConvertToMultiByte( pFileName, -1, name, 1024 );

		alGenSources( 1, &m_Src );

		m_pWavFile = new WAVFile();
		m_pWavFile->Open( name, FILE_OPEN_READ_MODE );
		m_pWavFile->LoadHeader();
		m_pWavFile->LoadInfo();
		
		// Calculate size of sound data.
		m_DataSize = m_pWavFile->GetInfoPos() - m_pWavFile->GetDataPos();
		MapilInt32 size = 0;

		POSIXThread::Create();
	}

	MapilVoid ALStreamingBuffer::Play()
	{
		m_IsPlaying = MapilTrue;	
	}

	MapilVoid ALStreamingBuffer::Stop()
	{
		alSourceStop( m_Src );
		m_IsPlaying = MapilFalse;
	}

	MapilVoid ALStreamingBuffer::Pause()
	{
		m_IsPlaying = MapilFalse;
	}

	MapilVoid ALStreamingBuffer::Destroy()
	{
		m_HasTermSig = MapilTrue;
		m_IsPlaying = MapilFalse;
	}

	MapilVoid ALStreamingBuffer::SetVolume()
	{
	}
#endif
}

#endif	// API_OPENAL
