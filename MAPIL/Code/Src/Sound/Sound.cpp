/**
*	@file	Sound.cpp
*	@brief	
*	@date	2011.6.25(Sat) 10:52
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Sound/Sound.h"

namespace MAPIL
{
	Sound::Sound( SharedPointer < SoundDevice > pDev ) : MapilObject(), m_pDev( pDev )
	{
	}
	
	Sound::~Sound()
	{
	}
}
