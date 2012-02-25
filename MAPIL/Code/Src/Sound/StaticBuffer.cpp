/**
*	@file	StaticBuffer.cpp
*	@brief	
*	@date	2011.7.3(Sun) 16:23
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Sound/StaticBuffer.h"

namespace MAPIL
{
	StaticBuffer::StaticBuffer( SharedPointer < SoundDevice > pDev ) : Sound( pDev )
	{
	}
	
	StaticBuffer::~StaticBuffer()
	{
	}
}
