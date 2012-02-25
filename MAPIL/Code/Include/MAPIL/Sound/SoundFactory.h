/**
*	@file	SoundFactory.h
*	@brief	
*	@date	2011.8.6 (Sat) 20:58
*/

#ifndef INCLUDED_MAPIL_SOUNDFACTORY_H
#define INCLUDED_MAPIL_SOUNDFACTORY_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "../Util/SharedPointer.hpp"
#include "../TChar.h"

namespace MAPIL
{
	class SoundDevice;
	class StaticBuffer;
	class StreamingBuffer;

	typedef SharedPointer < StaticBuffer >		IStaticBuffer;
	typedef SharedPointer < StreamingBuffer >	IStreamingBuffer;

	class SoundFactory : public MapilObject
	{
		SharedPointer < SoundDevice >		m_pDev;
	public:
		SoundFactory( SharedPointer < SoundDevice > pDev );
		virtual ~SoundFactory();
		virtual IStaticBuffer CreateStaticBuffer( const MapilTChar* pKeyStr ) = 0;
		virtual IStreamingBuffer CreateStreamingBuffer( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*/
		virtual MapilVoid Reflesh() = 0;
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*	@param Reflesh count.
		*/
		MapilVoid Reflesh( MapilInt32 count );
	};
}

#endif