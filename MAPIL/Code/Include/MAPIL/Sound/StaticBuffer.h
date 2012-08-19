/**
*	@file	StaticBuffer.h
*	@brief	
*	@date	2011.6.25(Sat) 10:37
*/

#ifndef INCLUDED_MAPIL_STATICBUFFER_H
#define INCLUDED_MAPIL_STATICBUFFER_H

#include "../CrossPlatform.h"

#include "Sound.h"
#include "../Math/Vector.hpp"

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
		virtual MapilVoid SetVolume( MapilUInt32 volume ) = 0;
		/**
		*	@brief		Set sound source position.
		*	@param pos	Position.
		*/
		virtual MapilVoid SetPosition( const Vector3 < MapilFloat32 >& pos ) = 0;
		/**
		*	@brief	Is static buffer pausing now?
		*	@return	True if static buffer is pausing.
		*/
		virtual MapilBool IsPausing() const = 0;
		/**
		*	@brief	Is static buffer stoping now?
		*	@return	True if static buffer is pausing.
		*/
		virtual MapilBool IsStopping() const = 0;
	};
}

#endif
