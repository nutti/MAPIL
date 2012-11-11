/**
*	@file	ResourceManager.hpp
*	@brief	
*	@date	2011.6.18 (Mon) 10:37
*/

#ifndef INCLUDED_MAPIL_RESOURCEMANAGER_HPP
#define INCLUDED_MAPIL_RESOURCEMANAGER_HPP

#include "../CrossPlatform.h"

#include <string>
#include <iostream>

#if defined ( LIB_STL )
#include <map>
#endif

#include "../Util/MapilObject.h"
#include "../Util/SharedPointer.hpp"
#include "../Type.h"

namespace MAPIL
{
	template < typename Type >
	class ResourceManager : public MapilObject
	{
	protected:
#if defined ( LIB_STL )
		std::map < std::basic_string < MapilTChar >, SharedPointer < Type > >		m_Holder;
#endif

		virtual SharedPointer < Type > CreateInst() = 0;
	public:
		// Constructor.
		ResourceManager();
		// Destructor.
		virtual ~ResourceManager();
		// Init.
		MapilVoid Init();
		// Create resource.
		SharedPointer < Type > Create( const MapilTChar* pKeyStr );
		// Get resource.
		SharedPointer < Type > Get( const MapilTChar* pKeyStr );
		// Delete resource.
		MapilVoid Delete( const MapilTChar* pKeyStr );
		MapilVoid Reflesh();
	};

	template < typename Type >
	ResourceManager < Type > ::ResourceManager() : MapilObject(), m_Holder()
	{
	}

	template < typename Type >
	ResourceManager < Type > ::~ResourceManager()
	{
		m_Holder.clear();
	}

	template < typename Type >
	MapilVoid ResourceManager < Type > ::Init()
	{
		m_Holder.clear();
	}

	//template < typename Type >
	//SharedPointer < Type > ResourceManager < Type > ::CreateInst()
	//{
	//	SharedPointer < Type > newResource();

	//	return newResource;
	//}

	// Create resource.
	template < typename Type >
	SharedPointer < Type > ResourceManager < Type > ::Create( const MapilTChar* pKeyStr )
	{
		SharedPointer < Type > newResource = CreateInst();

#ifdef LIB_STL
		m_Holder.insert( std::pair < std::basic_string < MapilTChar >, SharedPointer < Type > > ( pKeyStr, newResource ) );
#endif

		return newResource; 
	}

	// Get resource.
	template < typename Type >
	SharedPointer < Type > ResourceManager < Type > ::Get( const MapilTChar* pKeyStr )
	{
#ifdef LIB_STL
		return m_Holder.find( pKeyStr )->second;
#endif
	}

	// Delete resource.
	template < typename Type >
	MapilVoid ResourceManager < Type > ::Delete( const MapilTChar* pKeyStr )
	{
#if defined ( LIB_STL )
		if( m_Holder.find( pKeyStr )->second.GetNumRef() <= 2 ){
			m_Holder.erase( pKeyStr );
		}
#endif
	}

	template < typename Type >
	MapilVoid ResourceManager < Type > ::Reflesh()
	{
#if defined ( LIB_STL )
		typename std::map < std::basic_string < MapilTChar >, SharedPointer < Type > > ::iterator it = m_Holder.begin();
		// Delete all objects no other refers.
		while( it != m_Holder.end() ){
			// Before deleting, next iterator must be stored.
			typename std::map < std::basic_string < MapilTChar >, SharedPointer < Type > > ::iterator itPrev = it;
			++itPrev;
			// If the resource is only referenced by ResourceManager objects, current
			// reference count is 1.
			if( ( *it ).second.GetNumRef() <= 1 ){
				m_Holder.erase( it );
			}
			it = itPrev;
		}
#endif
	}
}

#endif
