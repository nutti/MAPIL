/**
*	@file	GraphicsResourceManager.hpp
*	@brief	
*	@date	2011.6.18 (Mon) 11:31
*/

#ifndef INCLUDED_MAPIL_GRAPHICSRESOURCEMANAGER_HPP
#define INCLUDED_MAPIL_GRAPHICSRESOURCEMANAGER_HPP

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Util/ResourceManager.hpp"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class GraphicsDevice;

	template < typename Type >
	class GraphicsResourceManager : public ResourceManager < Type >, public Graphics
	{
	protected:
		SharedPointer < Type > CreateInst();
	public:
		GraphicsResourceManager( SharedPointer < GraphicsDevice > pDev );
		~GraphicsResourceManager();
		MapilVoid LostAllResources();
		MapilVoid RestoreAllResources();
	};

	template < typename Type >
	GraphicsResourceManager < Type > ::GraphicsResourceManager( SharedPointer < GraphicsDevice > pDev ) :	ResourceManager < Type > (),
																											Graphics( pDev )
	{
	}
	
	template < typename Type >
	GraphicsResourceManager < Type > ::~GraphicsResourceManager()
	{
	}

	template < typename Type >
	SharedPointer < Type > GraphicsResourceManager < Type > ::CreateInst()
	{
		SharedPointer < Type > newResource( new Type( m_pDev ) );

		return newResource;
	}

	template < typename Type >
	MapilVoid GraphicsResourceManager < Type > ::LostAllResources()
	{
#if defined ( LIB_STL )
		std::map < std::basic_string < MapilTChar >, SharedPointer < Type > > ::iterator it = m_Holder.begin();
		// Lost all resources.
		while( it != m_Holder.end() ){
			( *it ).second->LostResource();
			++it;
		}
#endif
	}

	template < typename Type >
	MapilVoid GraphicsResourceManager < Type > ::RestoreAllResources()
	{
#if defined ( LIB_STL )
		std::map < std::basic_string < MapilTChar >, SharedPointer < Type > > ::iterator it = m_Holder.begin();
		// Lost all resources.
		while( it != m_Holder.end() ){
			( *it ).second->RestoreResource();
			++it;
		}
#endif
	}
}

#endif