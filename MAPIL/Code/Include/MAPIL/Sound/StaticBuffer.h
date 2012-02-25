/**
*	@file	StaticBuffer.h
*	@brief	
*	@date	2011.6.25(Sat) 10:37
*/

#ifndef INCLUDED_MAPIL_STATICBUFFER_H
#define INCLUDED_MAPIL_STATICBUFFER_H

#include "../CrossPlatform.h"

#include "Sound.h"

namespace MAPIL
{
	class Archiver;
	class StaticBuffer : public Sound
	{
	public:
		StaticBuffer( SharedPointer < SoundDevice > pDev );
		virtual ~StaticBuffer();
		virtual MapilVoid Create( const MapilTChar* pFileName ) = 0;
		virtual MapilVoid Create( Archiver* pArchiver, const MapilTChar* pFileName ) = 0;
		virtual MapilVoid Play() = 0;
		virtual MapilVoid Stop() = 0;
		virtual MapilVoid Pause() = 0;
		virtual MapilVoid Destroy() = 0;
		virtual MapilVoid SetVolume() = 0;
	};
}

#endif
