/**
*	@file	InputResourceManager.hpp
*	@brief	
*	@date	2011.7.23 (Sat) 20:34
*/

#ifndef INCLUDED_MAPIL_INPUTRESOURCEMANAGER_HPP
#define INCLUDED_MAPIL_INPUTRESOURCEMANAGER_HPP

#include "../CrossPlatform.h"

#include "Input.h"
#include "../Util/ResourceManager.hpp"

namespace MAPIL
{
	class InputDevice;

	template < typename Type >
	class InputResourceManager : public ResourceManager < Type >, public Input
	{
	protected:
		SharedPointer < Type > CreateInst();
	public:
		InputResourceManager( SharedPointer < InputDevice > pDev );
		~InputResourceManager();
	};

	template < typename Type >
	InputResourceManager < Type > ::InputResourceManager( SharedPointer < InputDevice > pDev ) :	ResourceManager < Type > (), Input( pDev )
	{
	}
	
	template < typename Type >
	InputResourceManager < Type > ::~InputResourceManager()
	{
	}

	template < typename Type >
	SharedPointer < Type > InputResourceManager < Type > ::CreateInst()
	{
		SharedPointer < Type > newResource( new Type( m_pDev ) );

		return newResource;
	}
}

#endif