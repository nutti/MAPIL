/**
*	@file	Memory.hpp
*	@brief	This file contains utility functions which handle memory.
*	@date	2011.5.25 13:40
*/

#ifndef INCLUDED_MAPIL_UTIL_MEMORY_HPP
#define INCLUDED_MAPIL_UTIL_MEMORY_HPP

#include <memory.h>

#include "../Type.h"

namespace MAPIL
{
	template < typename Type >
	inline MapilVoid SafeDelete( Type*& p )
	{
		if( p ){
			delete p;
			p = 0;
		}
	}

	template < typename Type >
	inline MapilVoid SafeDeleteArray( Type*& p ){
		if( p ){
			delete[] p;
			p = 0;
		}
	}

	template < typename Type >
	inline MapilVoid SafeRelease( Type*& p ){
		if( p ){
			p->Release();
			p = 0;
		}
	}

	template < typename Type >
	inline MapilVoid ZeroObject( Type* obj, MapilInt32 size )
	{
		memset( obj, 0, size );
	}
}

#endif
