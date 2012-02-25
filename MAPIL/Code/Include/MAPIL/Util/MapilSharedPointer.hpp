/**
*	@file	MapilSharedPointer.hpp
*	@brief	
*	@date	2011.6.12(Sun) 11:43
*/

#ifndef INCLUDED_MAPIL_MAPILSHAREDPOINTER_HPP
#define INCLUDED_MAPIL_MAPILSHAREDPOINTER_HPP

#include "Memory.hpp"
#include "../Type.h"

namespace MAPIL
{

	template < typename T >
	class MapilSharedPointer
	{
	public:
		T*					m_pPointer;		//Pointer
		MapilInt32*		m_pNumRef;			//Number of reference

		//Add number of reference
		MapilVoid AddRef();
		//Subtract number of reference
		//If number of reference is 0, pointer of type will be deleted
		MapilVoid Release();

	public:
		//Constructer (1)
		MapilSharedPointer();
		//Constructer (2)
		explicit MapilSharedPointer( T* pointer );
		// Constructer ( 3 )
		explicit MapilSharedPointer( T* pPtr, MapilInt32 numRef );
		//Destructer
		~MapilSharedPointer();
		//Copy constructer
		MapilSharedPointer( const MapilSharedPointer& sp );
		//Substitute (Overload of = operator)
		MapilSharedPointer& operator=( const MapilSharedPointer < T >& sp );
		//Set pointer
		MapilVoid SetPointer( T* pointer );
		//Get pointer
		T* GetPointer() const;
		//Arrow operator (Overload of -> operator)
		T* operator->() const;
		//Dereference operator (Overload of * operator)
		T& operator*() const;
		//Index operator (Overload of [] operator)
		T& operator[]( MapilInt32 index ) const;
		//Equivalence (Overload of == operator)
		MapilBool operator==( const MapilSharedPointer < T >& sp );
		//Difference (Overload of != operator)
		MapilBool operator!=( const MapilSharedPointer < T >& sp );
		//Get number of reference
		MapilInt32 GetNumRef() const;

		template < typename Type2 > MapilSharedPointer& operator=( const MapilSharedPointer < Type2 >& sp )
		{
			if( sp.GetPointer() == m_pPointer ){
				return *this;
			}

			Release();

			m_pPointer = sp.m_pPointer;
			m_pNumRef = sp.m_pNumRef;

			AddRef();

			return *this;
		}

		template < typename Type2 > MapilSharedPointer( const MapilSharedPointer < Type2 >& sp )
		{
			m_pPointer = sp.m_pPointer;
			m_pNumRef = sp.m_pNumRef;

			AddRef();
		}

		// Down cast.
		template < typename Type2 >
		MapilBool DownCast( const MapilSharedPointer < Type2 >& sp )
		{
			T* pCast = dynamic_cast < T* > ( sp.m_pPointer );
			// Down cast is succeeded.
			if( pCast ){
				Release();
				m_pPointer = pCast;
				m_pNumRef = sp.m_pNumRef;
				AddRef();
				return true;
			}

			return false;
		}
	};

	//Constructer (1)
	template < typename T >
	MapilSharedPointer < T > ::MapilSharedPointer() : m_pPointer( 0 ), m_pNumRef( 0 )
	{
		m_pNumRef = new MapilInt32;
		*m_pNumRef = 0;
		AddRef();
	}

	//Constructer (2)
	template < typename T >
	MapilSharedPointer < T > ::MapilSharedPointer( T* pointer )
	{
		m_pPointer = pointer;
		m_pNumRef = new MapilInt32;
		*m_pNumRef = 0;
		AddRef();
	}

	// Constructor. ( 3 )
	template < typename T >
	MapilSharedPointer < T > ::MapilSharedPointer( T* pPtr, MapilInt32 numRef )
	{
		m_pNumRef = new MapilInt32;
		*m_pNumRef = numRef;
		m_pPointer = pPtr;
		AddRef();
	}

	//Destructer
	template < typename T >
	MapilSharedPointer < T > ::~MapilSharedPointer()
	{
		Release();
	}

	//Add number of reference
	template < typename T >
	MapilVoid MapilSharedPointer < T > ::AddRef()
	{
		( *m_pNumRef )++;
	}

	//Subtract number of reference
	//If number of reference is 0, pointer of type will be deleted
	template < typename T >
	MapilVoid MapilSharedPointer < T > ::Release()
	{
		( *m_pNumRef )--;
		if( *m_pNumRef <= 0 ){
			SafeDelete( m_pNumRef );
			//SafeDelete can't be used in visual C++ 2010 express edition.
			//So creating code which behaves correctly whether pointer is array, is necessary.
			SafeDelete( m_pPointer );
		}
	}

	//Copy constructer
	template < typename T >
	MapilSharedPointer < T > ::MapilSharedPointer( const MapilSharedPointer < T >& sp )
	{
		//Copy of pointer
		m_pPointer = sp.m_pPointer;
		m_pNumRef = sp.m_pNumRef;
		AddRef();
	}

	//Substitute (Overload of = operator)
	template < typename T >
	MapilSharedPointer < T >& MapilSharedPointer < T > ::operator=( const MapilSharedPointer < T >& sp )
	{
		//If this description isn't here, release which will be occurred later, may make pointer dangling pointer
		if( m_pPointer == sp.m_pPointer ){
			return *this;
		}

		//Subtract my number of reference
		Release();

		//Copy of pointer
		m_pPointer = sp.m_pPointer;
		m_pNumRef = sp.m_pNumRef;

		//Add number of reference
		AddRef();

		return *this;
	}

	//Set pointer
	template < typename T >
	MapilVoid MapilSharedPointer < T > ::SetPointer( T* pointer )
	{
		Release();

		m_pNumRef = new MapilInt32;
		*m_pNumRef = 0;
		m_pPointer = pointer;

		AddRef();
	}

	//Get pointer
	template < typename T >
	T* MapilSharedPointer < T > ::GetPointer() const
	{
		return m_pPointer;
	}

	//Get number of reference
	template < typename T >
	MapilInt32 MapilSharedPointer < T > ::GetNumRef() const
	{
		return *m_pNumRef;
	}

	//Access object (Overload of -> operator)
	template < typename T >
	T* MapilSharedPointer < T > ::operator->() const
	{
		return m_pPointer;
	}

	//Index operator (Overload of [] operator)
	template < typename T >
	T& MapilSharedPointer < T > ::operator[]( MapilInt32 index ) const
	{
		return m_pPointer[ index ];
	}

	//Equivalence (Overload of == operator)
	template < typename T >
	MapilBool MapilSharedPointer < T > ::operator==( const MapilSharedPointer < T >& sp )
	{
		return ( m_pPointer == sp.m_pPointer ) ? MapilTrue : MapilFalse;
	}

	//Difference (Overload of != operator)
	template < typename T >
	MapilBool MapilSharedPointer < T > ::operator!=( const MapilSharedPointer < T >& sp )
	{
		return ( m_pPointer != sp.m_pPointer ) ? MapilTrue : MapilFalse;
	}

}

#endif
