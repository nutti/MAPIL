/**
*	@file	HeapAllocator.cpp
*	@brief	
*	@date	2012.10.12 (Fri) 22:55
*/

#include "../../Include/MAPIL/CrossPlatform.h"

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/Util/HeapAllocator.hpp"

#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"

//-------------------------------------------------------------------
// Definitions and implementations.
//-------------------------------------------------------------------

namespace MAPIL
{
	// Constructor.
	HeapAllocator::HeapAllocator( int size, int depth ) : m_Depth( depth ), m_Size( size )
	{
		m_pIndex = new MapilInt32[ m_Depth ];
		m_pPool = new MapilChar[ m_Depth * m_Size ];
		for( MapilInt32 i = 0; i < m_Depth; i++ ){
			m_pIndex[ i ] = i + 1;
		}
		m_NextIndex = 0;
		m_NumRestBlocks = m_Depth;
	}

	// Destructor.
	HeapAllocator::~HeapAllocator()
	{
		SafeDeleteArray( m_pIndex );
		SafeDeleteArray( m_pPool );
		m_NextIndex = 0;
		m_NumRestBlocks = 0;
		m_Depth = 0;
		m_Size = 0;
	}

	// Allocate.
	MapilVoid* HeapAllocator::Alloc()
	{
		if( m_NextIndex >= m_Depth ){
			throw MapilException( CURRENT_POSITION, TSTR( "Can not allocate memory." ), -1 );
		}

		MapilInt32 index = m_NextIndex;
		m_NextIndex = m_pIndex[ index ];
		m_NumRestBlocks--;

		return &m_pPool[ index * m_Size ];
	}

	// Free.
	MapilVoid HeapAllocator::Free( MapilVoid* p )
	{
		MapilInt32 index =  ( static_cast < char* > ( p ) - m_pPool ) / m_Size;

		if( index < 0 || index >= m_Depth ){
			throw MapilException( CURRENT_POSITION, TSTR( "Memory access violation." ), -1 );
		}

		m_NumRestBlocks++;

		m_pIndex[ index ] = m_NextIndex;
		m_NextIndex = index;
	}

	// Get number of rest blocks.
	MapilInt32 HeapAllocator::GetNumRestBlocks() const
	{
		return m_NumRestBlocks;
	}
}
