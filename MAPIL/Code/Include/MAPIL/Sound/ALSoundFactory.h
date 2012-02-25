/**
*	@file	ALSoundFactory.h
*	@brief	ALSoundFactory class provides the interface which creates
*			the classes related to OpenAL. ALSoundFacotry also manages
*			these classes.
*	@date	2011.8.6 (Sat) 21:07
*/

#ifndef INCLUDED_MAPIL_ALSOUNDFACTORY_H
#define INCLUDED_MAPIL_ALSOUNDFACTORY_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#ifdef API_OPENAL

#include "SoundFactory.h"
#include "SoundResourceManager.hpp"
#include "ALStaticBuffer.h"
#include "ALStreamingBuffer.h"

//-------------------------------------------------------------------
// Class definition.
//-------------------------------------------------------------------

namespace MAPIL
{

	class SoundDevice;
	class ALSoundFactory : public SoundFactory
	{
		SoundResourceManager < ALStaticBuffer >			m_StaticBufRM;		///< Resource manager of ALStaticBuffer class.
		SoundResourceManager < ALStreamingBuffer >		m_StreamingBufRM;	///< Resource manager of ALStreamingBuffer class.
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to SoundDevice.
		*/
		ALSoundFactory( SharedPointer < SoundDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~ALSoundFactory();
		/**
		*	@brief Create StaticBuffer class.
		*	@param pKeyStr String which indentify the instance.
		*/
		IStaticBuffer CreateStaticBuffer( const MapilTChar* pKeyStr );
		/**
		*	@brief Create StreamingBuffer class.
		*	@param pKeyStr String which indentify the instance.
		*/
		IStreamingBuffer CreateStreamingBuffer( const MapilTChar* pKeyStr );
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*/
		MapilVoid Reflesh();
	};
}

#endif	// API_WIN32API

#endif	// INCLUDED_MAPIL_ALSOUNDFACTORY_H