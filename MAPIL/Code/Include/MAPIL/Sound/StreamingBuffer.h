/**
*	@file	StreamingBuffer.h
*	@brief	
*	@date	2011.7.18 (Mon) 16:09
*/

#ifndef INCLUDED_MAPIL_STREAMINGBUFFER_H
#define INCLUDED_MAPIL_STREAMINGBUFFER_H

#include "../CrossPlatform.h"

#include "Sound.h"

namespace MAPIL
{
	class Archiver;
	class StreamingBuffer : public Sound
	{
	public:
		StreamingBuffer( SharedPointer < SoundDevice > pDev );
		virtual ~StreamingBuffer();
		virtual MapilVoid Create( const MapilTChar* pFileName ) = 0;
		virtual MapilVoid Create( Archiver* pArchiver, const MapilTChar* pFileName ) = 0;
		virtual MapilVoid Create( const MapilTChar* pArchiveFileName, const MapilTChar* pFileName ) = 0;
		virtual MapilVoid Play() = 0;
		virtual MapilVoid Stop() = 0;
		virtual MapilVoid Pause() = 0;
		virtual MapilVoid Destroy() = 0;
		virtual MapilVoid SetVolume( MapilFloat32 volume ) = 0;
	};
}

#endif
