/**
*	@file	HeapAllocator.hpp
*	@brief	HeapAllocator class provides memory pool. The users can
*			obtain the memory faster than the method which operating
*			system provides.
*	@date	2012.10.12 (Fri) 22:34
*/

#ifndef INCLUDED_MAPIL_HEAPALLOCATOR_H
#define INCLUDED_MAPIL_HEAPALLOCATOR_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "../Type.h"

//-------------------------------------------------------------------
// Definitions and implementations.
//-------------------------------------------------------------------

namespace MAPIL
{
	class HeapAllocator
	{
	private:
		MapilChar*		m_pPool;						///< Memory pool.
		MapilInt32*		m_pIndex;				///< Index of each blocks.
		MapilInt32		m_NextIndex;					///< Next index.
		MapilInt32		m_NumRestBlocks;				///< Number of rest blocks.
		MapilInt32		m_Depth;
		MapilInt32		m_Size;
	public:
		/**
		*	@brief Constructor.
		*/
		HeapAllocator( int size, int depth );
		/**
		*	@brief Destructor.
		*/
		virtual ~HeapAllocator();
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

	// Delete.
	template < typename Type >
	MapilVoid HeapAllocator::Delete( Type* p )
	{
		p->~Type();
		Free( p );
	}

}

#endif	// INCLUDED_MAPIL_HEAPALLOCATOR_H