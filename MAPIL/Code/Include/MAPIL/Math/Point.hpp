/**
*	@file	Point.hpp
*	@brief	
*	@date	2011.6.13(Mon) 11:47
*/

#ifndef INCLUDED_MAPIL_POINT_HPP
#define INCLUDED_MAPIL_POINT_HPP

#include "../Util/MapilObject.h"
#include "../Type.h"

namespace MAPIL
{
	template < typename Type >
	class Point : public MapilObject
	{
	public:
		Point();
		virtual ~Point();
	};
	
	template < typename Type >
	Point < Type >::Point()
	{
	}
	
	template < typename Type >
	Point < Type >::~Point()
	{
	}
	
	
	
	template < typename Type >
	class Point2 : public Point < Type >
	{
	public:
		union
		{
			struct
			{
				Type		m_X;
				Type		m_Y;
			};
			Type	m_Elm[ 2 ];
		};
		Point2();
		Point2( Type x, Type y );
		Point2( const Point2 < Type >& p );
		virtual ~Point2();
		//Substitute (Overload of = operator)
		Point2& operator=( const Point2 < Type >& p );
		//Equivalence (Overload of == operator)
		MapilBool operator==( const Point2 < Type >& p );
		
		
		
	};
	
	template < typename Type >
	Point2 < Type >::Point2() : m_X( 0 ), m_Y( 0 )
	{
	}
	
	template < typename Type >
	Point2 < Type >::Point2( Type x, Type y ) : m_X( x ), m_Y( y )
	{
	}
	
	template < typename Type >
	Point2 < Type >::Point2( const Point2 < Type >& p ) : m_X( p.m_X ), m_Y( p.m_Y )
	{
	}
	
	template < typename Type >
	Point2 < Type >::~Point2()
	{
		m_X = 0;
		m_Y = 0;
	}
	
	template < typename Type >
	Point2 < Type >& Point2 < Type > ::operator=( const Point2 < Type >& p )
	{
		m_X = p.m_X;
		m_Y = p.m_Y;
		
		return *this;
	}
	
	//Equivalence (Overload of == operator)
	template < typename Type >
	MapilBool Point2 < Type > ::operator==( const Point2 < Type >& p )
	{
		return ( ( m_X == p.m_X ) && ( m_Y == p.m_Y ) );
	}
	
	template < typename Type >
	class Point3 : public Point < Type >
	{
	public:
		union
		{
			struct
			{
				Type		m_X;
				Type		m_Y;
				Type		m_Z;
			};
			Type	m_Elm[ 3 ];
		};
		Point3();
		Point3( Type x, Type y, Type z );
		Point3( const Point3 < Type >& p );
		virtual ~Point3();
	};
	
	template < typename Type >
	Point3 < Type >::Point3() : m_X( 0 ), m_Y( 0 ), m_Z( 0 )
	{
	}
	
	template < typename Type >
	Point3 < Type >::Point3( Type x, Type y, Type z ) : m_X( x ), m_Y( y ), m_Z( z )
	{
	}
	
	template < typename Type >
	Point3 < Type >::Point3( const Point3 < Type >& p ) : m_X( p.m_X ), m_Y( p.m_Y ), m_Z( p.m_Z )
	{
	}
	
	template < typename Type >
	Point3 < Type >::~Point3()
	{
		m_X = 0;
		m_Y = 0;
		m_Z = 0;
	}
	
	
	
	template < typename Type >
	class Point4 : public Point < Type >
	{
	public:
		union
		{
			struct
			{
				Type		m_X;
				Type		m_Y;
				Type		m_Z;
				Type		m_W;
			};
			Type	m_Elm[ 4 ];
		};
		Point4();
		Point4( Type x, Type y, Type z, Type w );
		Point4( const Point4 < Type >& p );
		virtual ~Point4();
	};
	
	template < typename Type >
	Point4 < Type >::Point4() : m_X( 0 ), m_Y( 0 ), m_Z( 0 ), m_W( 0 )
	{
	}
	
	template < typename Type >
	Point4 < Type >::Point4( Type x, Type y, Type z, Type w ) :	m_X( x ),
																			m_Y( y ),
																			m_Z( z ),
																			m_W( w )
	{
	}
	
	template < typename Type >
	Point4 < Type >::Point4( const Point4 < Type >& p ) :	m_X( p.m_X ),
																		m_Y( p.m_Y ),
																		m_Z( p.m_Z ),
																		m_W( p.m_W )
	{
	}
	
	template < typename Type >
	Point4 < Type >::~Point4()
	{
		m_X = 0;
		m_Y = 0;
		m_Z = 0;
		m_W = 0;
	}
}

#endif
