/**
*	@file	SafeArray.hpp
*	@brief	
*	@date	2011.6.13(Mon) 12:20
*/

#ifndef INCLUDED_MAPIL_SAFEARRAY_HPP
#define INCLUDED_MAPIL_SAFEARRAY_HPP

#include "Assertion.hpp"
#include "../Type.h"
#include "../Util/Memory.hpp"

namespace MAPIL
{
	template < typename Type >
	class SafeArray
	{
	private:
		Type*							m_pData;
		MapilInt32			m_Size;
	public:
		//Constructor
		explicit SafeArray( MapilInt32 size );
		//Destructor
		~SafeArray();
		//Get data
		Type GetData( MapilInt32 index ) const;
		//Set data
		MapilVoid SetData( MapilInt32 index, Type data );
		//Index operator (Overload of [] operator)
		Type& operator[]( MapilInt32 index );
	};

	//Constructor
	template < typename Type >
	SafeArray < Type > ::SafeArray( MapilInt32 size ) : m_pData( 0 ), m_Size( size )
	{
		m_pData = new Type[ size ];
	}

	//Destructor
	template < typename Type >
	SafeArray < Type > ::~SafeArray()
	{
		Utility::SafeDeleteArray( m_pData );
		m_Size = 0;
	}

	//Get data
	template < typename Type >
	Type SafeArray < Type > ::GetData( MapilInt32 index ) const
	{
		Assert(	( index < size ) &&  ( index >= 0 ),
					TSTR( "Nutti::Lib::Utility" ),
					TSTR( "SafeArray" ),
					TSTR( "GetData" ),
					TSTR( "Bad index value is substituted." ),
					-1 );

		return m_pData[ index ];
	}

	//Set data
	template < typename Type >
	MapilVoid SafeArray < Type > ::SetData( MapilInt32 index, Type data )
	{
		Assert(	( index < size ) &&  ( index >= 0 ),
					TSTR( "Nutti::Lib::Utility" ),
					TSTR( "SafeArray" ),
					TSTR( "SetData" ),
					TSTR( "Bad index value is substituted." ),
					-1 );

		return m_pData[ index ] = data;
	}

	//Index operator (Overload of [] operator)
	template < typename Type >
	Type& SafeArray < Type > ::operator[]( MapilInt32 index )
	{
		Assert(	( index < size ) &&  ( index >= 0 ),
					TSTR( "Nutti::Lib::Utility" ),
					TSTR( "SafeArray" ),
					TSTR( "operator[]" ),
					TSTR( "Bad index value is substituted." ),
					-1 );

		return m_pData [ index ];
	}

}

#endif
