/**
*	@file	COMPointer.hpp
*	@brief	COMPointer acts as the shared pointer. The difference between these
*			is that Release method is called when the object is deleted. It also
*			calls Addref method when the object is created. This class is only
*			applicable to Direct 3D resources.
*	@date	2011.8.24 (Wed) 21:15
*/

#ifndef INCLUDED_MAPIL_COMPOINTER_HPP
#define INCLUDED_MAPIL_COMPOINTER_HPP

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "Memory.hpp"
#include "../Type.h"

//-------------------------------------------------------------------
// Definitions and implementations.
//-------------------------------------------------------------------

namespace MAPIL
{

	template < typename Type >
	class COMPointer
	{
	private:
		Type*			m_pPointer;			///< Raw pointer.
	public:
		/**
		*	@brief			Constructor.
		*	@param pPointer	Pointer to be managed.
		*/
		explicit COMPointer( Type* pPointer );
		/**
		*	@brief Destructor.
		*/
		~COMPointer();
		/**
		*	@brief		Copy Constructor.
		*	@param cp	COMPointer to be copied.
		*/
		COMPointer( const COMPointer < Type >& cp );
		/**
		*	@brief		Substitute (Overload of = operator)
		*	@param cp	COMPointer to be copied.
		*	@return		Copied COMPointer.
		*/
		COMPointer& operator=( const COMPointer < Type >& cp );
		/**
		*	@brief		Get pointer
		*	@return		Get raw pointer.
		*/
		Type* GetPointer() const;
		/**
		*	@brief		Get pointer of pointer to be changed.
		*	@return		Get pointer of pointer.
		*/
		Type** GetPointerOfPointerWithChange();
		/**
		*	@brief		Equivalence (Overload of == operator)
		*	@param cp	COMPointer object to be compared.
		*	@return		True if the pointer is equivalent.
		*/
		MapilBool operator==( const COMPointer < Type >& cp );
		/**
		*	@brief		Difference (Overload of != operator)
		*	@param cp	COMPointer object to be compared.
		*	@return		True if the pointer is different.
		*/
		MapilBool operator!=( const COMPointer < Type >& cp );
	};

	//Constructor
	template < typename Type >
	COMPointer < Type > ::COMPointer( Type* pPointer )
	{
		//Add number of reference
		if( pPointer ){
			pPointer->AddRef();
		}

		//Copy of pointer
		m_pPointer = pPointer;
	}

	//Destructor
	template < typename Type >
	COMPointer < Type > ::~COMPointer()
	{
		//Subtract number of reference
		SafeRelease( m_pPointer );
	}

	//Copy constructer
	template < typename Type >
	COMPointer < Type > ::COMPointer( const COMPointer < Type >& cp )
	{
		//Add number of reference
		if( cp.m_pPointer ){
			cp.m_pPointer->AddRef();
		}

		m_pPointer = cp.m_pPointer;
	}

	//Substitute (Overload of = operator)
	template < typename Type >
	COMPointer < Type >& COMPointer < Type > ::operator=( const COMPointer < Type >& cp )
	{
		//Add number of reference of source pointer
		if( cp.m_pPointer ){
			cp.m_pPointer->AddRef();
		}

		//Subtract number of reference
		SafeRelease( m_pPointer );

		m_pPointer = cp.m_pPointer;

		return *this;
	}

	//Get pointer
	template < typename Type >
	Type* COMPointer < Type > ::GetPointer() const
	{
		return m_pPointer;
	}

	//Get pointer of pointer with change
	template < typename Type >
	Type** COMPointer < Type > ::GetPointerOfPointerWithChange()
	{
		SafeRelease( m_pPointer );

		return &m_pPointer;
	}

	//Equivalence (Overload of == operator)
	template < typename Type >
	MapilBool COMPointer < Type > ::operator==( const COMPointer < Type >& cp )
	{
		return ( m_pPointer == cp.m_pPointer ) ? MapilTrue : MapilFalse;
	}

	//Difference (Overload of != operator)
	template < typename Type >
	MapilBool COMPointer < Type > ::operator!=( const COMPointer < Type >& cp )
	{
		return ( m_pPointer != cp.m_pPointer ) ? MapilTrue : MapilFalse;
	}

}


#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_COMPOINTER_HPP