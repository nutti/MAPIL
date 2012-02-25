/**
*	@file	GUIResourceManager.hpp
*	@brief	
*	@date	2011.6.20 (Wed) 7:57
*/

#ifndef INCLUDED_MAPIL_GUIRESOURCEMANAGER_HPP
#define INCLUDED_MAPIL_GUIRESOURCEMANAGER_HPP

#include "../CrossPlatform.h"

#include "../Util/ResourceManager.hpp"

namespace MAPIL
{

	template < typename Type >
	class GUIResourceManager : public ResourceManager < Type >
	{
	protected:
		SharedPointer < Type > CreateInst();
	public:
		GUIResourceManager();
		~GUIResourceManager();
	};

	template < typename Type >
	GUIResourceManager < Type > ::GUIResourceManager() :	ResourceManager < Type > ()
	{
	}
	
	template < typename Type >
	GUIResourceManager < Type > ::~GUIResourceManager()
	{
	}

	template < typename Type >
	SharedPointer < Type > GUIResourceManager < Type > ::CreateInst()
	{
		SharedPointer < Type > newResource( new Type() );

		return newResource;
	}
}

#endif