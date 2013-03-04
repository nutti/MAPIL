/**
*	@file	SoundFactory.cpp
*	@brief	
*	@date	2011.8.6 (Sat) 21:04
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Sound/SoundFactory.h"
#include "../../Include/MAPIL/Sound/SoundDevice.h"
#include "../../Include/MAPIL/Sound/ALSoundFactory.h"

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

	SoundFactory* CreateSoundFactory( SharedPointer < SoundDevice > pDev )
	{
		MapilInt32 api = pDev->GetSoundAPI();

		if( api == SOUND_API_OPENAL ){
			//return SharedPointer < GraphicsFactory > ( new D3DGraphicsFactory( pDev ) );
#if defined ( API_OPENAL )
			return new ALSoundFactory( pDev );
#endif
		}
		else{
			return NULL;
		}

		return NULL;
	}
}