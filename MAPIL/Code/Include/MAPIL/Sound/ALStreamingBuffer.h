/**
*	@file	ALStreamingBuffer.h
*	@brief	ALStreamingBuffer class is used to play music.
*			This class always loads the few part of data into memory.
*			The new thread is started when this class is constructed.			
*	@date	2011.7.18 (Mon) 16:12
*/

#ifndef INCLUDED_MAPIL_ALSTREAMINGBUFFER_H
#define INCLUDED_MAPIL_ALSTREAMINGBUFFER_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_OPENAL )

#if defined ( OS_WIN_32BIT )
#include <al.h>
#include <alc.h>
#elif defined ( OS_LINUX_32BIT )
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include "StreamingBuffer.h"

#include "../IO/WAVFile.h"
#include "../Type.h"

#if defined ( API_WIN32API )
#include "../Thread/WinAPIThread.h"
#elif defined ( API_POSIX )
#include "../Thread/POSIXThread.h"
#endif

//-------------------------------------------------------------------
// Class definition.
//-------------------------------------------------------------------

namespace MAPIL
{
#if defined ( API_WIN32API )
	class SoundDevice;
	class Archiver;
	class ALStreamingBuffer : public StreamingBuffer, public WinAPIThread
	{
	private:
		WAVFile*			m_pWavFile;		///< WAVFile class.
		Archiver*			m_pArchiver;	///< Archiver class.
		std::basic_string < MapilChar >		m_FileName;
		MapilInt32			m_DataSize;		///< Size of sound data.
		ALuint				m_Src;			///< Handler.
		ALuint				m_Bufs[ 2 ];	///< Handler.
		ALuint				m_BufSize;		///< Buffer size.
		MapilBool			m_IsPlaying;	///< Is sound playing now?
		MapilBool			m_IsPausing;	///< Is sound pausing now?
		MapilBool			m_HasTermSig;	///< Does this class have the signal of terminal?
		MapilFloat32		m_Volume;		///< Volume.
		MapilBool			m_HasWavFile;	///< Is based on WAVFile class?
		MapilBool			m_HasExtArchive;	///< Has the external archive file?
		/**
		*	@brief	The process contents of the thread.
		*	@return	Return value of the thread.
		*/
		MapilInt32 ThreadFunc();
		MapilInt32 WAVFileThread();
		MapilInt32 ArchiverThread();
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to SoundDevice.
		*/
		ALStreamingBuffer( SharedPointer < SoundDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~ALStreamingBuffer();
		/**
		*	@brief Create ALStreamingBuffer from sound file.
		*	@param pFileName Name of sound file.
		*/
		MapilVoid Create( const MapilTChar* pFileName );
		/**
		*	@brief				Create ALStreamingBuffer from sound file.
		*	@param pArchiver	Archiver.
		*	@param pFileName	Name of sound file.
		*/
		MapilVoid Create( Archiver* pArchiver, const MapilTChar* pFileName );
		/**
		*	@brief						Create ALStreamingBuffer from sound file.
		*	@param pArchiveFileName		Name of the archive file.
		*	@param pFileName			Name of sound file.
		*/
		MapilVoid Create( const MapilTChar* pArchiveFileName, const MapilTChar* pFileName );
		/**
		*	@brief Play sound.
		*/
		MapilVoid Play();
		/**
		*	@brief Stop playing sound.
		*/
		MapilVoid Stop();
		/**
		*	@brief Pause playing sound.
		*/
		MapilVoid Pause();
		/**
		*	@brief Destroy ALStreamingBuffer.
		*/
		MapilVoid Destroy();
		/**
		*	@brief Set volume.
		*/
		MapilVoid SetVolume( MapilFloat32 volume );
	};
#elif defined( API_POSIX )
	class SoundDevice;
	class ALStreamingBuffer : public StreamingBuffer, public POSIXThread
	{
	private:
		WAVFile*			m_pWavFile;		///< WAVFile class.
		MapilInt32			m_DataSize;		///< Size of sound data.
		ALuint				m_Src;			///< Handler.
		ALuint				m_Bufs[ 2 ];	///< Handler.
		ALuint				m_BufSize;		///< Buffer size.
		MapilBool			m_IsPlaying;	///< Is sound playing now?
		MapilBool			m_HasTermSig;	///< Does this class have the signal of terminal?
		/**
		*	@brief	The process contents of the thread.
		*	@return	Return value of the thread.
		*/
		MapilInt32 ThreadFunc();
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to SoundDevice.
		*/
		ALStreamingBuffer( SharedPointer < SoundDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~ALStreamingBuffer();
		/**
		*	@brief Create ALStreamingBuffer from sound file.
		*	@param pFileName Name of sound file.
		*/
		MapilVoid Create( const MapilTChar* pFileName );
		/**
		*	@brief Play sound.
		*/
		MapilVoid Play();
		/**
		*	@brief Stop playing sound.
		*/
		MapilVoid Stop();
		/**
		*	@brief Pause playing sound.
		*/
		MapilVoid Pause();
		/**
		*	@brief Destroy ALSreamingBuffer.
		*/
		MapilVoid Destroy();
		/**
		*	@brief Set volume.
		*/
		MapilVoid SetVolume();
	};
#endif
}

#endif	// API_OPENAL

#endif	// INCLUDED_MAPIL_ALSTREAMINGBUFFER_H
