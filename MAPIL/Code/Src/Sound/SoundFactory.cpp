/**
*	@file	SoundFactory.cpp
*	@brief	
*	@date	2011.8.6 (Sat) 21:04
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Sound/SoundFactory.h"
#include "../../Include/MAPIL/Sound/SoundDevice.h"

namespace MAPIL
{
	SoundFactory::SoundFactory( SharedPointer < SoundDevice > pDev ) : m_pDev( pDev )
	{
	}

	SoundFactory::~SoundFactory()
	{
	}

	MapilVoid SoundFactory::Reflesh( MapilInt32 count )
	{
		for( MapilInt32 i = 0; i < count; ++i ){
			Reflesh();
		}
	}
}