/**
*	@file	ALSAStaticBuffer.h
*	@brief	ALSAStaticBuffer class is used to play music.
*			This class loads all sound data into memory.
*			If the user want to decrease memory usage, the
*			user should use ALSAStreamingBuffer instead.
*	@date	2011.7.3 (Sun) 11:28
*/

#ifndef INCLUDED_MAPIL_ALSASTATICBUFFER_H
#define INCLUDED_MAPIL_ALSASTATICBUFFER_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "StaticBuffer.h"
#include "../IO/WAVFile.h"

#include "../Type.h"

//-------------------------------------------------------------------
// Class definition.
//-------------------------------------------------------------------

namespace MAPIL
{
	class SoundDevice;
	class ALSAStaticBuffer : public StaticBuffer
	{
	private:
		WAVFile*			m_pWavFile;		///< WAVFile class.
		MapilChar*			m_pWavData;		///< Sound data.
		MapilInt32			m_DataSize;		///< Size of sound data.
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to SoundDevice class.
		*/
		ALSAStaticBuffer( SharedPointer < SoundDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~ALSAStaticBuffer();
		/**
		*	@brief Create ALSAStaticBuffer from sound file.
		*	@param pFileName Name of sound file.
		*/
		MapilVoid Create( const MapilChar* pFileName );
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
		MapilVoid SetVolume();
	};
}

#endif	// INCLUDED_MAPIL_ALSASTATICBUFFER_H
