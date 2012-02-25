/**
*	@file	ALSoundDevice.h
*	@brief	ALSoundDevice class is needed when the user
*			uses class related to OpenAL. This class will
*			be contained to SoundDevice class.
*	@date	2011.7.9 (Sat) 11:26
*/

#ifndef INCLUDED_MAPIL_ALSOUNDDEVICE_H
#define INCLUDED_MAPIL_ALSOUNDDEVICE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#ifdef API_OPENAL

#if defined ( OS_WIN_32BIT )
#include <al.h>
#include <alc.h>
#elif defined ( OS_LINUX_32BIT )
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include "../Util/MapilObject.h"
#include "../Type.h"

//-------------------------------------------------------------------
// Class definition.
//-------------------------------------------------------------------

namespace MAPIL
{
	class ALSoundDevice : public MapilObject
	{
		ALCdevice*		m_pDev;			///< Device.
		ALCcontext*		m_pContext;		///< Context.
	public:
		/**
		*	@brief Constructor.
		*/
		ALSoundDevice();
		/**
		*	@brief Destructor.
		*/
		~ALSoundDevice();
		/**
		*	@brief Initialize ALSoundDevice class.
		*/
		MapilVoid Init();
	};
}

#endif	// API_OPENAL

#endif	//INCLUDED_MAPIL_ALSOUNDDEVICE_H
