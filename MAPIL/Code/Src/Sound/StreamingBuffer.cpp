/**
*	@file	StreamingBuffer.cpp
*	@brief	
*	@date	2011.7.18 (Mon) 16:10
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Sound/StreamingBuffer.h"

namespace MAPIL
{
	StreamingBuffer::StreamingBuffer( SharedPointer < SoundDevice > pDev ) : Sound( pDev )
	{
	}
	
	StreamingBuffer::~StreamingBuffer()
	{
	}
}
