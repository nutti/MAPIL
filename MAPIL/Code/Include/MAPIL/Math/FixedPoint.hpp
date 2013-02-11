/**
*	@file	FixedPoint.hpp
*	@brief	
*	@date	2013.2.2 (Sat) 14:52
*/

#ifndef INCLUDED_MAPIL_FIXEDPOINT_HPP
#define INCLUDED_MAPIL_FIXEDPOINT_HPP

#include "../CrossPlatform.h"

#include "../Type.h"

namespace MAPIL
{
	class FixedPoint
	{
	private:
		MapilInt32		m_Value;
	public:
		FixedPoint();
		~FixedPoint();
		FixedPoint( const FixedPoint& fp );
		explicit FixedPoint( MapilInt32 i );
		FixedPoint( MapilInt32 i, MapilInt32 decimal );
		FixedPoint& operator=( const FixedPoint& fp );

		MapilInt32 GetRawValue() const;
		FixedPoint operator+( const FixedPoint& fp );
		FixedPoint operator-( const FixedPoint& fp );
		FixedPoint operator*( const FixedPoint& fp );
		FixedPoint operator/( const FixedPoint& fp );
		FixedPoint operator>>( MapilInt32 shift );
		FixedPoint operator<<( MapilInt32 shift );
		FixedPoint& operator+=( const FixedPoint& fp );
		FixedPoint& operator-=( const FixedPoint& fp );
		FixedPoint& operator*=( const FixedPoint& fp );
		FixedPoint& operator/=( const FixedPoint& fp );
		FixedPoint& operator>>=( MapilInt32 shift );
		FixedPoint& operator<<=( MapilInt32 shift );
		
	};

	inline MapilInt32 FixedPoint::GetRawValue() const
	{
		return m_Value;
	}

	FixedPoint::FixedPoint() : m_Value( 0 )
	{
	}

	FixedPoint::~FixedPoint()
	{
	}

	FixedPoint::FixedPoint( const FixedPoint& fp )
	{
		m_Value = fp.m_Value;
	}

	FixedPoint::FixedPoint( MapilInt32 i )
	{
		m_Value = i << 16;
	}

	FixedPoint::FixedPoint( MapilInt32 i, MapilInt32 decimal )
	{
		m_Value = static_cast < MapilInt32 > ( ( static_cast < MapilInt64 > ( i ) << 16 ) / decimal );
	}

	inline FixedPoint& FixedPoint::operator=( const FixedPoint& fp )
	{
		m_Value = fp.m_Value;
		return *this;
	}

	inline FixedPoint FixedPoint::operator+( const FixedPoint& fp )
	{
		FixedPoint tmp( *this );
		tmp += fp;
		return tmp;
	}

	inline FixedPoint FixedPoint::operator-( const FixedPoint& fp )
	{
		FixedPoint tmp( *this );
		tmp -= fp;
		return tmp;
	}

	inline FixedPoint FixedPoint::operator*( const FixedPoint& fp )
	{
		FixedPoint tmp( *this );
		tmp *= fp;
		return tmp;
	}

	inline FixedPoint FixedPoint::operator/( const FixedPoint& fp )
	{
		FixedPoint tmp( *this );
		tmp /= fp;
		return tmp;
	}

	inline FixedPoint FixedPoint::operator>>( MapilInt32 shift )
	{
		FixedPoint tmp( *this );
		tmp >>= shift;
		return tmp;
	}

	inline FixedPoint FixedPoint::operator<<( MapilInt32 shift )
	{
		FixedPoint tmp( *this );
		tmp <<= shift;
		return tmp;
	}

	inline FixedPoint& FixedPoint::operator+=( const FixedPoint& fp )
	{
		m_Value += fp.m_Value;

		return *this;
	}

	inline FixedPoint& FixedPoint::operator-=( const FixedPoint& fp )
	{
		m_Value -= fp.m_Value;

		return *this;
	}

	inline FixedPoint& FixedPoint::operator*=( const FixedPoint& fp )
	{
		m_Value = ( m_Value >> 8 ) * ( fp.m_Value >> 8 );
		return *this;
	}

	inline FixedPoint& FixedPoint::operator/=( const FixedPoint& fp )
	{
		m_Value = ( static_cast < MapilInt64 > ( m_Value << 32 ) / fp.m_Value ) >> 16;
		return *this;
	}

	inline FixedPoint& FixedPoint::operator>>=( MapilInt32 shift )
	{
		m_Value >>= shift;
		return *this;
	}

	inline FixedPoint& FixedPoint::operator<<=( MapilInt32 shift )
	{
		m_Value <<= shift;
		return *this;
	}





	inline FixedPoint operator+( const FixedPoint& fp1, const FixedPoint& fp2 )
	{
		FixedPoint tmp( fp1 );
		tmp += fp2;
		return tmp;
	}

	inline FixedPoint operator-( const FixedPoint& fp1, const FixedPoint& fp2 )
	{
		FixedPoint tmp( fp1 );
		tmp -= fp2;
		return tmp;
	}

	inline FixedPoint operator*( const FixedPoint& fp1, const FixedPoint& fp2 )
	{
		FixedPoint tmp( fp1 );
		tmp *= fp2;
		return tmp;
	}

	inline FixedPoint operator/( const FixedPoint& fp1, const FixedPoint& fp2 )
	{
		FixedPoint tmp( fp1 );
		tmp /= fp2;
		return tmp;
	}

	inline FixedPoint operator>>( const FixedPoint& fp1, MapilInt32 shift )
	{
		FixedPoint tmp( fp1 );
		tmp >>= shift;
		return tmp;
	}

	inline MapilBool operator==( const FixedPoint& fp1, const FixedPoint& fp2 )
	{
		return ( fp1.GetRawValue() == fp2.GetRawValue() );
	}

	inline MapilBool operator!=( const FixedPoint& fp1, const FixedPoint& fp2 )
	{
		return !( fp1 == fp2 );
	}

	inline MapilBool operator>( const FixedPoint& fp1, const FixedPoint& fp2 )
	{
		return ( fp1.GetRawValue() > fp2.GetRawValue() );
	}

	inline MapilBool operator<( const FixedPoint& fp1, const FixedPoint& fp2 )
	{
		return ( fp2 > fp1 );
	}

	inline MapilBool operator>=( const FixedPoint& fp1, const FixedPoint& fp2 )
	{
		return !( fp1 < fp2 );
	}

	inline MapilBool operator<=( const FixedPoint& fp1, const FixedPoint& fp2 )
	{
		return !( fp1 > fp2 );
	}
}

#endif