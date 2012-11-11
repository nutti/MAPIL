/**
*	@file	DeviceGraphicsResourceManager.hpp
*	@brief	
*	@date	2012.11.9 (Fri) 18:42
*/

#ifndef INCLUDED_MAPIL_DEVICEGRAPHICSRESOURCEMANAGER_HPP
#define INCLUDED_MAPIL_DEVICEGRAPHICSRESOURCEMANAGER_HPP

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Util/ResourceManager.hpp"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class GraphicsDevice;

	template < typename Type >
	class DeviceGraphicsResourceManager : public ResourceManager < Type >, public Graphics
	{
	protected:
		SharedPointer < Type > CreateInst();
	public:
		DeviceGraphicsResourceManager( SharedPointer < GraphicsDevice > pDev );
		~DeviceGraphicsResourceManager();
		MapilVoid LostAllResources();
		MapilVoid RestoreAllResources();
	};

	template < typename Type >
	DeviceGraphicsResourceManager < Type > ::DeviceGraphicsResourceManager( SharedPointer < GraphicsDevice > pDev ) :	ResourceManager < Type > (),
																											Graphics( pDev )
	{
	}
	
	template < typename Type >
	DeviceGraphicsResourceManager < Type > ::~DeviceGraphicsResourceManager()
	{
	}

	template < typename Type >
	SharedPointer < Type > DeviceGraphicsResourceManager < Type > ::CreateInst()
	{
		SharedPointer < Type > newResource( new Type( m_pDev ) );

		return newResource;
	}

	template < typename Type >
	MapilVoid DeviceGraphicsResourceManager < Type > ::LostAllResources()
	{
#if defined ( LIB_STL )
		typename std::map < std::basic_string < MapilTChar >, SharedPointer < Type > > ::iterator it = m_Holder.begin();
		// Lost all resources.
		while( it != m_Holder.end() ){
			( *it ).second->LostResource();
			++it;
		}
#endif
	}

	template < typename Type >
	MapilVoid DeviceGraphicsResourceManager < Type > ::RestoreAllResources()
	{
#if defined ( LIB_STL )
		typename std::map < std::basic_string < MapilTChar >, SharedPointer < Type > > ::iterator it = m_Holder.begin();
		// Lost all resources.
		while( it != m_Holder.end() ){
			( *it ).second->RestoreResource();
			++it;
		}
#endif
	}
}

#endif
