/**
*	@file	Allocator.hpp
*	@brief	Allocator class provides memory pool. The users can
*			obtain the memory faster than the method which oper-
*			ating system provides.
*	@date	2011.7.23 (Sat) 10:05
*/

#ifndef INCLUDED_MAPIL_ALLOCATOR_H
#define INCLUDED_MAPIL_ALLOCATOR_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Memory.hpp"
#include "../Type.h"
#include "../Diag/MapilException.h"

//-------------------------------------------------------------------
// Definitions and implementations.
//-------------------------------------------------------------------

namespace MAPIL
{
	template < MapilInt32 SIZE = 1, MapilInt32 DEPTH = 1 >
	class Allocator
	{
	private:
		MapilChar		m_Pool[ SIZE * DEPTH ];			///< Memory pool.
		MapilInt32		m_Index[ DEPTH ];				///< Index of each blocks.
		MapilInt32		m_NextIndex;					///< Next index.
		MapilInt32		m_NumRestBlocks;				///< Number of rest blocks.
	public:
		/**
		*	@brief Constructor.
		*/
		Allocator();
		/**
		*	@brief Destructor.
		*/
		virtual ~Allocator();
		/**
		*	@brief Allocate memory from memory pool.
		*	@return Allocated memory address.
		*/
		MapilVoid* Alloc();
		/**
		*	@brief Free allocated memory.
		*	@param p Address of allocated memory.
		*/
		MapilVoid Free( MapilVoid* p );
		/**
		*	@brief Free allocated memory and call destructor.
		*	@param p Address of allocated memory.
		*/
		template < typename Type >
		MapilVoid Delete( Type* p );
		/**
		*	@brief Get number of rest blocks.
		*	@return Number of rest blocks.
		*/
		MapilInt32 GetNumRestBlocks() const;
	};

	// Constructor.
	template < MapilInt32 SIZE, MapilInt32 DEPTH >
	Allocator < SIZE, DEPTH > ::Allocator()
	{
		for( MapilInt32 i = 0; i < DEPTH; i++ ){
			m_Index[ i ] = i + 1;
		}
		m_NextIndex = 0;
		m_NumRestBlocks = DEPTH;
	}

	// Destructor.
	template < MapilInt32 SIZE, MapilInt32 DEPTH >
	Allocator < SIZE, DEPTH > ::~Allocator()
	{
		ZeroObject( m_Pool, SIZE * DEPTH );
		ZeroObject( m_Index, DEPTH );
		m_NextIndex = 0;
		m_NumRestBlocks = DEPTH;
	}

	// Allocate.
	template < MapilInt32 SIZE, MapilInt32 DEPTH >
	MapilVoid* Allocator < SIZE, DEPTH > ::Alloc()
	{
		if( m_NextIndex >= DEPTH ){
			return 0;
		}

		MapilInt32 index = m_NextIndex;
		m_NextIndex = m_Index[ index ];
		m_NumRestBlocks--;

		return &m_Pool[ index * SIZE ];
	}

	// Free.
	template < MapilInt32 SIZE, MapilInt32 DEPTH >
	MapilVoid Allocator < SIZE, DEPTH > ::Free( MapilVoid* p )
	{
		MapilInt32 index =  ( static_cast < char* > ( p ) - m_Pool ) / SIZE;

		if( index < 0 || index >= DEPTH ){
			return;
		}

		m_NumRestBlocks++;

		m_Index[ index ] = m_NextIndex;
		m_NextIndex = index;
	}

	// Delete.
	template < MapilInt32 SIZE, MapilInt32 DEPTH >
	template < typename Type >
	MapilVoid Allocator < SIZE, DEPTH > ::Delete( Type* p )
	{
		p->~Type();
		Free( p );
	}

	// Get number of rest blocks.
	template < MapilInt32 SIZE, MapilInt32 DEPTH >
	MapilInt32 Allocator < SIZE, DEPTH > ::GetNumRestBlocks() const
	{
		return m_NumRestBlocks;
	}
}

#endif	// INCLUDED_MAPIL_ALLOCATOR_H