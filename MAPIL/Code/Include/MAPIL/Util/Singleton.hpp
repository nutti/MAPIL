/**
*	@file	Singleton.hpp
*	@brief	
*	@date	2011.7.23 (Sat) 8:35
*/

#ifndef INCLUDED_MAPIL_SINGLETON_HPP
#define INCLUDED_MAPIL_SINGLETON_HPP

#include "../CrossPlatform.h"

#include "../Type.h"

namespace MAPIL
{
	template < typename Type >
	class Singleton
	{
	private:
		Singleton( const Singleton < Type >& s );
		Singleton& operator=( const Singleton < Type >& s );
	protected:
		Singleton();
		virtual ~Singleton();
	public:
		static Type* GetInst();
	};

	template < typename Type >
	Singleton < Type > ::Singleton()
	{
	}

	template < typename Type >
	Singleton < Type > ::~Singleton()
	{
	}

	template < typename Type >
	inline Type* Singleton < Type > ::GetInst()
	{
		static Type inst;
		return &inst;
	}
}

#endif