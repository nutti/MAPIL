/**
*	@file	SoundResourceManager.hpp
*	@brief	
*	@date	2011.8.6 (Sat) 21:16
*/

#ifndef INCLUDED_MAPIL_SOUNDRESOURCEMANAGER_HPP
#define INCLUDED_MAPIL_SOUNDRESOURCEMANAGER_HPP

#include "../CrossPlatform.h"

#include "Sound.h"
#include "../Util/ResourceManager.hpp"

namespace MAPIL
{
	class SoundDevice;

	template < typename Type >
	class SoundResourceManager : public ResourceManager < Type >, public Sound
	{
	protected:
		SharedPointer < Type > CreateInst();
	public:
		SoundResourceManager( SharedPointer < SoundDevice > pDev );
		~SoundResourceManager();
	};

	template < typename Type >
	SoundResourceManager < Type > ::SoundResourceManager( SharedPointer < SoundDevice > pDev ) :	ResourceManager < Type > (), Sound( pDev )
	{
	}
	
	template < typename Type >
	SoundResourceManager < Type > ::~SoundResourceManager()
	{
	}

	template < typename Type >
	SharedPointer < Type > SoundResourceManager < Type > ::CreateInst()
	{
		SharedPointer < Type > newResource( new Type( m_pDev ) );

		return newResource;
	}
}

#endif