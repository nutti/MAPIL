/**
*	@file	ALStaticBuffer.h
*	@brief	ALStaticBuffer class is used to play music.
*			This class loads all sound data into memory.
*			If the user want to decrease memory usage, the
*			user should use ALStaticBuffer instead.
*	@date	2011.7.9 (Sat) 11:59
*/

#ifndef INCLUDED_MAPIL_ALSTATICBUFFER_H
#define INCLUDED_MAPIL_ALSTATICBUFFER_H

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

#include "StaticBuffer.h"

#include "../IO/WAVFile.h"
#include "../Type.h"

#if defined ( API_WIN32API )
#include "../Thread/WinAPIThread.h"
#endif

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class SoundDevice;
	class Archiver;
	class ALStaticBuffer : public StaticBuffer
	{
	private:
		WAVFile*			m_pWavFile;		///< WAVFile class.
		MapilChar*			m_pWavData;		///< Sound data.
		MapilInt32			m_DataSize;		///< Size of sound data.
		MapilUInt32			m_Volume;		///< Volume.
		ALuint				m_Src;			///< Handler.
		ALuint				m_Buf;			///< Handler.
		MapilBool			m_IsPlaying;	///< Is sound playing now?
		MapilBool			m_IsPausing;	///< Is sound pausing now?
		MapilFloat32		m_Pos[ 3 ];		///< Sound source position.
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to SoundDevice.
		*/
		ALStaticBuffer( SharedPointer < SoundDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~ALStaticBuffer();
		/**
		*	@brief Create ALStaticBuffer from sound file.
		*	@param pFileName Name of sound file.
		*/
		MapilVoid Create( const MapilTChar* pFileName );
		/**
		*	@brief Create ALStaticBuffer from sound file.
		*	@param pArchiver	Archiver.
		*	@param pFileName	Name of sound file.
		*/
		MapilVoid Create( Archiver* pArchiver, const MapilTChar* pFileName );
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
		*	@brief Destroy ALSAStaticBuffer.
		*/
		MapilVoid Destroy();
		/**
		*	@brief Set volume.
		*/
		MapilVoid SetVolume( MapilUInt32 volume );
		/**
		*	@brief Set sound source position.
		*	@param pos	Position.
		*/
		MapilVoid SetPosition( const Vector3 < MapilFloat32 >& pos );
		/**
		*	@brief	Is static buffer pausing now?
		*	@return	True if static buffer is pausing.
		*/
		MapilBool IsPausing() const;
		/**
		*	@brief	Is static buffer stoping now?
		*	@return	True if static buffer is pausing.
		*/
		MapilBool IsStopping() const;
	};
}

#endif	// API_OPENAL

#endif	// INCLUDED_MAPIL_ALSTATICBUFFER_H
