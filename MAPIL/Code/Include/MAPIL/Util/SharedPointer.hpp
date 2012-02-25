/**
*	@file	SharedPointer.hpp
*	@brief	
*	@date	2011.6.12(Sun) 11:13
*/

#ifndef INCLUDED_MAPIL_SHAREDPOINTER_HPP
#define INCLUDED_MAPIL_SHAREDPOINTER_HPP

#include "../CrossPlatform.h"

#ifdef LIB_BOOST
#include <boost/shared_ptr.hpp>
#endif

#include "MapilSharedPointer.hpp"

#include "MapilObject.h"

namespace MAPIL
{
	template < typename T >
	class SharedPointer : public MapilObject
	{
	public:
#ifdef LIB_BOOST
		boost::shared_ptr < T >		m_Ptr;
#else
		MapilSharedPointer < T >		m_Ptr;
#endif
	public:
		SharedPointer();
		explicit SharedPointer( T* p );
		~SharedPointer();
		SharedPointer( const SharedPointer& sp );
		//Substitute (Overload of = operator)
		SharedPointer& operator=( const SharedPointer < T >& sp );
		//Set pointer
		MapilVoid SetPointer( T* p );
		//Get pointer
		T* GetPointer() const;
		//Arrow operator (Overload of -> operator)
		T* operator->() const;
		//Dereference operator (Overload of * operator)
		T& operator*() const;
		//Index operator (Overload of [] operator)
		T& operator[]( MapilInt32 index ) const;
		//Equivalence (Overload of == operator)
		MapilBool operator==( const SharedPointer < T >& sp );
		//Difference (Overload of != operator)
		MapilBool operator!=( const SharedPointer < T >& sp );
		//Get number of reference
		MapilInt32 GetNumRef() const;

		template < typename Type2 > SharedPointer& operator=( const SharedPointer < Type2 >& sp )
		{
			m_Ptr = sp.m_Ptr;

			return *this;
		}

		template < typename Type2 > SharedPointer( const SharedPointer < Type2 >& sp )
		{
			m_Ptr = sp.m_Ptr;
		}

		template < typename Type2 >
		MapilBool DownCast( const SharedPointer < Type2 >& sp )
		{
#ifdef LIB_BOOST
			m_Ptr = boost::dynamic_pointer_cast < T > ( sp.m_Ptr );
			return true;
#else
			return m_Ptr.DownCast( sp.m_Ptr );
#endif
		}
	};
	
	template < typename T >
	SharedPointer < T >::SharedPointer() : m_Ptr()
	{
	}
	
	template < typename T >
	SharedPointer < T >::SharedPointer( T* p ) : m_Ptr( p )
	{
	}
	
	template < typename T >
	SharedPointer < T >::~SharedPointer()
	{
	}
	
	template < typename T >
	SharedPointer < T >::SharedPointer( const SharedPointer < T >& sp ) : m_Ptr( sp.m_Ptr )
	{
	}
	
	//Substitute (Overload of = operator)
	template < typename T >
	SharedPointer < T >& SharedPointer < T >::operator=( const SharedPointer < T >& sp )
	{
		m_Ptr = sp.m_Ptr;

		return *this;
	}
	
	//Set pointer
	template < typename T >
	MapilVoid SharedPointer < T >::SetPointer( T* p )
	{
	}
	
	//Get pointer
	template < typename T >
	T* SharedPointer < T >::GetPointer() const
	{
#ifdef LIB_BOOST
		return m_Ptr.get();
#else
		return m_Ptr.GetPointer();
#endif
	}
	
	//Arrow operator (Overload of -> operator)
	template < typename T >
	T* SharedPointer < T >::operator->() const
	{
#ifdef LIB_BOOST
		return m_Ptr.get();
#else
		return m_Ptr.GetPointer();
#endif
	}
	
	//Dereference operator (Overload of * operator)
	template < typename T >
	T& SharedPointer < T >::operator*() const
	{
	}
	
	//Index operator (Overload of [] operator)
	template < typename T >
	T& SharedPointer < T >::operator[]( MapilInt32 index ) const
	{
#ifdef LIB_BOOST
		return *( m_Ptr.get() + sizeof( T ) * index );
#else
		return m_Ptr[ index ];
#endif
	}
	
	//Equivalence (Overload of == operator)
	template < typename T >
	MapilBool SharedPointer < T >::operator==( const SharedPointer < T >& sp )
	{
		return ( m_Ptr == sp.m_Ptr ) ? MapilTrue : MapilFalse;
	}
	
	//Difference (Overload of != operator)
	template < typename T >
	MapilBool SharedPointer < T >::operator!=( const SharedPointer < T >& sp )
	{
		return ( m_Ptr != sp.m_Ptr ) ? MapilTrue : MapilFalse;
	}
	
	//Get number of reference
	template < typename T >
	MapilInt32 SharedPointer < T >::GetNumRef() const
	{
#ifdef LIB_BOOST
		return m_Ptr.use_count();;
#else
		return m_Ptr.GetNumRef();
#endif
	}
}

#endif
