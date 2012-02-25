/**
*	@file	Vector.hpp
*	@brief	
*	@date	2011.6.13(Mon) 11:34
*/

#ifndef INCLUDED_MAPIL_VECTOR_HPP
#define INCLUDED_MAPIL_VECTOR_HPP

#include "Point.hpp"
#include "Matrix.hpp"
#include "../Type.h"

namespace MAPIL
{
	template < typename Type >
	class Vector2 : public Point2 < Type >
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

		//Constructer(1)
		Vector2();
		//Constructer(2)
		Vector2( Type x, Type y );
		//Constructer(3)
		Vector2( const Vector2 < Type >& v );
		//Destructer
		~Vector2();
		//Add / Ternary operator (Overload of + operator)
		Vector2 operator+( const Vector2 < Type >& v );
		//Subtract / Ternary operator (Overload of - operator)
		Vector2 operator-( const Vector2 < Type >& v );
		//Substitute (Overload of = operator)
		//Vector2& operator=( const Vector2 < Type >& v );
		//Equivalence (Overload of == operator)
		MapilBool operator==( const Vector2 < Type >& v );
		//Add / Binary operator (Overload of += operator)
		Vector2& operator+=( const Vector2 < Type >& v );
		//Subtract / Binary operator (Overload of -= operator)
		Vector2& operator-=( const Vector2 < Type >& v );
		//Add
		MapilVoid Add( const Vector2 < Type >& v );
		//Subtract
		MapilVoid Sub( const Vector2 < Type >& v );
		//Multiply constant
		MapilVoid MulConst( Type num );
		//Rotate
		MapilVoid Rot( Type angle );
		//Get sum of square
		Type GetSumSquare() const;
		//Get norm
		Type GetNorm() const;
		//Normalize
		MapilVoid Normalize();
		//Get inner product
		Type GetInnerProduct( const Vector2 < Type >& v ) const;
		//Get outer product
		Type GetOuterProduct( const Vector2 < Type >& v ) const;
	};

	//Constructer(1)
	template < typename Type >
	Vector2 < Type > ::Vector2() : m_X( 0 ), m_Y( 0 )
	{
	}

	//Constructer(2)
	template < typename Type >
	Vector2 < Type > ::Vector2( Type x, Type y ) : m_X( x ), m_Y( y )
	{
	}

	//Constructer(3)
	template < typename Type >
	Vector2 < Type > ::Vector2( const Vector2 < Type >& v ) : m_X( v.m_X ), m_Y( v.m_Y )
	{
	}

	//Destructer
	template < typename Type >
	Vector2 < Type > ::~Vector2()
	{
	}

	//Add / Ternary operator (Overload of + operator)
	template < typename Type >
	Vector2 < Type > Vector2 < Type > ::operator+( const Vector2 < Type >& v )
	{
		Vector2 < Type > vTmp;

		vTmp.m_X = m_X + v.m_X;
		vTmp.m_Y = m_Y + v.m_Y;

		return vTmp;
	}

	//Subtract / Ternary operator (Overload of - operator)
	template < typename Type >
	Vector2 < Type > Vector2 < Type > ::operator-( const Vector2 < Type >& v )
	{
		Vector2 < Type > vTmp;

		vTmp.m_X = m_X - v.m_X;
		vTmp.m_Y = m_Y - v.m_Y;

		return vTmp;
	}

	//Substitute (Overload of = operator)
	//template < typename Type >
	//Vector2 < Type >& Vector2 < Type > ::operator=( const Vector2 < Type >& v )
	//{
	//	m_X = v.m_X;
	//	m_Y = v.m_Y;

//		return *this;
	//}

	//Equivalence (Overload of == operator)
	template < typename Type >
	MapilBool Vector2 < Type > ::operator==( const Vector2 < Type >& v )
	{
		return ( ( m_X == v.m_X ) && ( m_Y == v.m_Y ) );
	}

	//Add / Binary operator (Overload of += operator)
	template < typename Type >
	Vector2 < Type >& Vector2 < Type > ::operator+=( const Vector2 < Type >& v )
	{
		m_X += v.m_X;
		m_Y += v.m_Y;

		return *this;
	}

	//Subtract / Binary operator (Overload of -= operator)
	template < typename Type >
	Vector2 < Type >& Vector2 < Type > ::operator-=( const Vector2 < Type >& v )
	{
		m_X -= v.m_X;
		m_Y -= v.m_Y;

		return *this;
	}

	//Add
	template < typename Type >
	MapilVoid Vector2 < Type > ::Add( const Vector2 < Type >& v )
	{
		m_X += v.m_X;
		m_Y += v.m_Y;
	}

	//Subtract
	template < typename Type >
	MapilVoid Vector2 < Type > ::Sub( const Vector2 < Type >& v )
	{
		m_X -= v.m_X;
		m_Y -= v.m_Y;
	}

	//Multiply constant
	template < typename Type >
	MapilVoid Vector2 < Type > ::MulConst( Type num )
	{
		m_X *= num;
		m_Y *= num;
	}

	//Rotate
	template < typename Type >
	MapilVoid Vector2 < Type > ::Rot( Type angle )
	{
		Type tmpX = m_X;			//Speed-up / Only m_X will be changed in first expression

		m_X = m_X * cos( angle ) - m_Y * sin( angle );
		m_Y = tmpX * sin( angle ) + m_Y * cos( angle );
	}

	//Get sum of square
	template < typename Type >
	Type Vector2 < Type > ::GetSumSquare() const
	{
		return ( m_X * m_X + m_Y * m_Y );
	}

	//Get norm
	template < typename Type >
	Type Vector2 < Type > ::GetNorm() const
	{
		return sqrt( m_X * m_X + m_Y * m_Y );
	}

	//Normalize
	template < typename Type >
	MapilVoid Vector2 < Type > ::Normalize()
	{
		Type mulConst = 1 / sqrt( m_X * m_X + m_Y * m_Y );

		m_X *= mulConst;
		m_Y *= mulConst;
	}

	//Get inner product
	template < typename Type >
	Type Vector2 < Type > ::GetInnerProduct( const Vector2 < Type >& v ) const
	{
		return ( m_X * v.m_X + m_Y * v.m_Y );
	}

	//Get outer product
	template < typename Type >
	Type Vector2 < Type > ::GetOuterProduct( const Vector2 < Type >& v ) const
	{
		return ( m_X * v.m_Y - m_Y * v.m_X );
	}

	template < typename Type >
	class Vector3 : public Point3 < Type >
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

		//Constructer(1)
		Vector3();
		//Constructer(2)
		Vector3( Type x, Type y, Type z );
		//Constructer(3)
		Vector3( const Vector3 < Type >& v );
		//Destructer
		~Vector3();
		// Sign inversion / Unary operator. ( Overload of - operator )
		Vector3 operator-();
		//Add / Ternary operator (Overload of + operator)
		Vector3 operator+( const Vector3 < Type >& v );
		//Subtract / Ternary operator (Overload of - operator)
		Vector3 operator-( const Vector3 < Type >& v );
		// Multiply / Ternary operator. ( Overload of * operator )
		Vector3 operator*( Type n );
		//Substitute (Overload of = operator)
		Vector3& operator=( const Vector3 < Type >& v );
		//Equivalence (Overload of == operator)
		MapilBool operator==( const Vector3 < Type >& v );
		//Add / Binary operator (Overload of += operator)
		Vector3& operator+=( const Vector3 < Type >& v );
		//Subtract / Binary operator (Overload of -= operator)
		Vector3& operator-=( const Vector3 < Type >& v );
		//Add
		MapilVoid Add( const Vector3 < Type >& v );
		//Subtract
		MapilVoid Sub( const Vector3 < Type >& v );
		//Multiply constant
		MapilVoid MulConst( Type num );
		//Rotate around the x axis
		MapilVoid RotX( Type angle );
		//Rotate around the y axis
		MapilVoid RotY( Type angle );
		//Rotate around the z axis
		MapilVoid RotZ( Type angle );
		//Rotate around the x axis at first, and rotate around the y axis next
		MapilVoid RotXY( Type angleX, Type angleY );
		//Rotate around the y axis at first, and rotate around the x axis next
		MapilVoid RotYX( Type angleY, Type angleX );
		//Get sum of square
		Type GetSumSquare() const;
		//Get norm
		Type GetNorm() const;
		//Normalize
		MapilVoid Normalize();
		//Get inner product
		Type GetInnerProduct( const Vector3 < Type >& v ) const;
		//Get outer product
		Vector3 GetOuterProduct( const Vector3 < Type >& v ) const;
	};

	//Constructer(1)
	template < typename Type >
	Vector3 < Type > ::Vector3() : m_X( 0 ), m_Y( 0 ), m_Z( 0 )
	{
	}

	//Constructer(2)
	template < typename Type >
	Vector3 < Type > ::Vector3( Type x, Type y, Type z ) : m_X( x ), m_Y( y ), m_Z( z )
	{
	}

	//Constructer(3)
	template < typename Type >
	Vector3 < Type > ::Vector3( const Vector3 < Type >& v ) : m_X( v.m_X ), m_Y( v.m_Y ), m_Z( v.m_Z )
	{
	}

	//Destructer
	template < typename Type >
	Vector3 < Type > ::~Vector3()
	{
	}

	// Sign inversion / Unary operator. ( Overload of - operator )
	template < typename Type >
	Vector3 < Type > Vector3 < Type > ::operator-()
	{
		Vector3 < Type > vTmp;

		vTmp.m_X = -m_X;
		vTmp.m_Y = -m_Y;
		vTmp.m_Z = -m_Z;

		return vTmp;
	}

	//Add / Ternary operator (Overload of + operator)
	template < typename Type >
	Vector3 < Type > Vector3 < Type > ::operator+( const Vector3 < Type >& v )
	{
		Vector3 < Type > vTmp;

		vTmp.m_X = m_X + v.m_X;
		vTmp.m_Y = m_Y + v.m_Y;
		vTmp.m_Z = m_Z + v.m_Z;

		return vTmp;
	}

	//Subtract / Ternary operator (Overload of - operator)
	template < typename Type >
	Vector3 < Type > Vector3 < Type > ::operator-( const Vector3 < Type >& v )
	{
		Vector3 < Type > vTmp;

		vTmp.m_X = m_X - v.m_X;
		vTmp.m_Y = m_Y - v.m_Y;
		vTmp.m_Z = m_Z - v.m_Z;

		return vTmp;
	}

	// Multiply / Ternary operator. ( Overload of * operator )
	template < typename Type >
	Vector3 < Type > Vector3 < Type > ::operator*( Type n )
	{
		Vector3 < Type > vTmp;

		vTmp.m_X = m_X * n;
		vTmp.m_Y = m_Y * n;
		vTmp.m_Z = m_Z * n;

		return vTmp;
	}

	//Substitute (Overload of = operator)
	template < typename Type >
	Vector3 < Type >& Vector3 < Type > ::operator=( const Vector3 < Type >& v )
	{
		m_X = v.m_X;
		m_Y = v.m_Y;
		m_Z = v.m_Z;

		return *this;
	}

	//Equivalence (Overload of == operator)
	template < typename Type >
	MapilBool Vector3 < Type > ::operator==( const Vector3 < Type >& v )
	{
		return ( ( m_X == v.m_X ) && ( m_Y == v.m_Y ) && ( m_Z == v.m_Z ) );
	}

	//Add / Binary operator (Overload of += operator)
	template < typename Type >
	Vector3 < Type >& Vector3 < Type > ::operator+=( const Vector3 < Type >& v )
	{
		m_X += v.m_X;
		m_Y += v.m_Y;
		m_Z += v.m_Z;

		return *this;
	}

	//Subtract / Binary operator (Overload of -= operator)
	template < typename Type >
	Vector3 < Type >& Vector3 < Type > ::operator-=( const Vector3 < Type >& v )
	{
		m_X -= v.m_X;
		m_Y -= v.m_Y;
		m_Z -= v.m_Z;

		return *this;
	}

	//Add
	template < typename Type >
	MapilVoid Vector3 < Type > ::Add( const Vector3 < Type >& v )
	{
		m_X += v.m_X;
		m_Y += v.m_Y;
		m_Z += v.m_Z;
	}

	//Subtract
	template < typename Type >
	MapilVoid Vector3 < Type > ::Sub( const Vector3 < Type >& v )
	{
		m_X -= v.m_X;
		m_Y -= v.m_Y;
		m_Z -= v.m_Z;
	}

	//Multiply constant
	template < typename Type >
	MapilVoid Vector3 < Type > ::MulConst( Type num )
	{
		m_X *= num;
		m_Y *= num;
		m_Z *= num;
	}

	//Rotate around the x axis
	template < typename Type >
	MapilVoid Vector3 < Type > ::RotX( Type angle )
	{
		Type tmpY = m_Y;				//Speed-up / Only m_Y will be changed in first expression

		m_Y = m_Y * cos( angle ) + m_Z * sin( angle );
		m_Z = -tmpY * sin( angle ) + m_Z * cos( angle );

		// RH
		//m_Y = m_Y * cos( angle ) - m_Z * sin( angle );
		//m_Z = tmpY * sin( angle ) + m_Z * cos( angle );
	}

	//Rotate around the y axis
	template < typename Type >
	MapilVoid Vector3 < Type > ::RotY( Type angle )
	{
		Type tmpZ = m_Z;				//Speed-up / Only m_Z will be changed in first expression

		m_Z = m_Z * cos( angle ) + m_X * sin( angle );
		m_X = -tmpZ * sin( angle ) + m_X * cos( angle );

		// RH
		// m_Z = m_Z * cos( angle ) - m_X * sin( angle );
		// m_X = tmpZ * sin( angle ) + m_X * cos( angle );
	}

	//Rotate around the z axis
	template < typename Type >
	MapilVoid Vector3 < Type > ::RotZ( Type angle )
	{
		Type tmpX = m_X;				//Speed-up / Only m_X will be changed in first expression

		m_X = m_X * cos( angle ) + m_Y * sin( angle );
		m_Y = -tmpX * sin( angle ) + m_Y * cos( angle );

		// RH
		//m_X = m_X * cos( angle ) - m_Y * sin( angle );
		//m_Y = tmpX * sin( angle ) + m_Y * cos( angle );
	}

	//Rotate around the x axis at first, and rotate around the y axis next
	template < typename Type >
	MapilVoid Vector3 < Type > ::RotXY( Type angleX, Type angleY )
	{
		Type tmpX = m_X;
		Type tmpY = m_Y;

		m_X = m_X * cos( angleY ) + m_Y * sin( angleX ) * sin( angleY ) + m_Z * cos( angleX ) * sin( angleY );
		m_Y = m_Y * cos( angleX ) - m_Z * sin( angleX );
		m_Z = -tmpX * sin( angleY ) + tmpY * sin( angleX ) * cos( angleY ) + m_Z * cos( angleX ) * cos( angleY );
	}

	//Rotate around the y axis at first, and rotate around the x axis next
	template < typename Type >
	MapilVoid Vector3 < Type > ::RotYX( Type angleY, Type angleX )
	{
		Type tmpX = m_X;
		Type tmpY = m_Y;

		m_X = m_X * cos( angleY ) + m_Z * sin( angleY );
		m_Y = tmpX * sin( angleX ) * sin( angleY ) + m_Y *cos( angleX ) - m_Z * sin( angleX ) * cos( angleY );
		m_Z = -tmpX * cos( angleX ) * sin( angleY ) + tmpY * sin( angleX ) + m_Z * cos( angleX ) * cos( angleY );
	}

	//Get sum of square
	template < typename Type >
	Type Vector3 < Type > ::GetSumSquare() const
	{
		return ( m_X * m_X + m_Y * m_Y + m_Z * m_Z );
	}

	//Get norm
	template < typename Type >
	Type Vector3 < Type > ::GetNorm() const
	{
		return sqrt( m_X * m_X + m_Y * m_Y + m_Z * m_Z );
	}

	//Normalize
	template < typename Type >
	MapilVoid Vector3 < Type > ::Normalize()
	{
		Type mulConst = 1 / sqrt( m_X * m_X + m_Y * m_Y + m_Z * m_Z );

		m_X *= mulConst;
		m_Y *= mulConst;
		m_Z *= mulConst;
	}

	//Get inner product
	template < typename Type >
	Type Vector3 < Type > ::GetInnerProduct( const Vector3 < Type >& v ) const
	{
		return ( m_X * v.m_X + m_Y * v.m_Y + m_Z * v.m_Z );
	}

	//Get outer product
	template < typename Type >
	Vector3 < Type > Vector3 < Type > ::GetOuterProduct( const Vector3 < Type >& v ) const
	{
		return Vector3 < Type > ( ( m_Y * v.m_Z - m_Z * v.m_Y ), ( m_Z * v.m_X - m_X * v.m_Z ), ( m_X * v.m_Y - m_Y * v.m_X ) );
	}

	template < typename Type >
	class Vector4 : public Point4 < Type >
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

		//Constructer(1)
		Vector4();
		//Constructer(2)
		Vector4( Type x, Type y, Type z, Type w );
		//Constructer(3)
		Vector4( const Vector4 < Type >& v );
		//Destructer
		~Vector4();
		//Add / Ternary operator (Overload of + operator)
		Vector4 operator+( const Vector4 < Type >& v );
		//Subtract / Ternary operator (Overload of - operator)
		Vector4 operator-( const Vector4 < Type >& v );
		//Substitute (Overload of = operator)
		Vector4& operator=( const Vector4 < Type >& v );
		// Multiply / Ternary operator ( Overload of * operator ).
		Vector4& operator*( const Matrix4x4 < Type >& m );
		//Equivalence (Overload of == operator)
		MapilBool operator==( const Vector4 < Type >& v );
		//Add / Binary operator (Overload of += operator)
		Vector4& operator+=( const Vector4 < Type >& v );
		//Subtract / Binary operator (Overload of -= operator)
		Vector4& operator-=( const Vector4 < Type >& v );
		//Add
		MapilVoid Add( const Vector4 < Type >& v );
		//Subtract
		MapilVoid Sub( const Vector4 < Type >& v );
		//Multiply constant
		MapilVoid MulConst( Type num );
		//Get sum of square
		Type GetSumSquare() const;
		//Get norm
		Type GetNorm() const;
		//Normalize
		MapilVoid Normalize();
		//Get inner product
		Type GetInnerProduct( const Vector4 < Type >& v ) const;
	};

	//Constructer(1)
	template < typename Type >
	Vector4 < Type > ::Vector4() : m_X( 0 ), m_Y( 0 ), m_Z( 0 ), m_W( 0 )
	{
	}

	//Constructer(2)
	template < typename Type >
	Vector4 < Type > ::Vector4( Type x, Type y, Type z, Type w ) : m_X( x ), m_Y( y ), m_Z( z ), m_W( w )
	{
	}

	//Constructer(3)
	template < typename Type >
	Vector4 < Type > ::Vector4( const Vector4 < Type >& v ) : m_X( v.m_X ), m_Y( v.m_Y ), m_Z( v.m_Z ), m_W( v.m_W )
	{
	}

	//Destructer
	template < typename Type >
	Vector4 < Type > ::~Vector4()
	{
	}

	//Add / Ternary operator (Overload of + operator)
	template < typename Type >
	Vector4 < Type > Vector4 < Type > ::operator+( const Vector4 < Type >& v )
	{
		Vector4 < Type > vTmp;

		vTmp.m_X = m_X + v.m_X;
		vTmp.m_Y = m_Y + v.m_Y;
		vTmp.m_Z = m_Z + v.m_Z;
		vTmp.m_W = m_W + v.m_W;

		return vTmp;
	}

	//Subtract / Ternary operator (Overload of - operator)
	template < typename Type >
	Vector4 < Type > Vector4 < Type > ::operator-( const Vector4 < Type >& v )
	{
		Vector4 < Type > vTmp;

		vTmp.m_X = m_X - v.m_X;
		vTmp.m_Y = m_Y - v.m_Y;
		vTmp.m_Z = m_Z - v.m_Z;
		vTmp.m_W = m_W - v.m_W;

		return vTmp;
	}

	//Substitute (Overload of = operator)
	template < typename Type >
	Vector4 < Type >& Vector4 < Type > ::operator=( const Vector4 < Type >& v )
	{
		m_X = v.m_X;
		m_Y = v.m_Y;
		m_Z = v.m_Z;
		m_W = v.m_W;

		return *this;
	}

	// Multiply / Ternary operator ( Overload of * operator ).
	template < typename Type >
	Vector4 < Type >& Vector4 < Type > ::operator*( const Matrix4x4 < Type >& m )
	{
		Vector4 < Type > vTmp = *this;

		m_X = vTmp.m_X * m.m_11 + vTmp.m_Y * m.m_21 + vTmp.m_Z * m.m_31 + vTmp.m_W * m.m_41;
		m_Y = vTmp.m_X * m.m_12 + vTmp.m_Y * m.m_22 + vTmp.m_Z * m.m_32 + vTmp.m_W * m.m_42;
		m_Z = vTmp.m_X * m.m_13 + vTmp.m_Y * m.m_23 + vTmp.m_Z * m.m_33 + vTmp.m_W * m.m_43;
		m_W = vTmp.m_X * m.m_14 + vTmp.m_Y * m.m_24 + vTmp.m_Z * m.m_34 + vTmp.m_W * m.m_44;

		return *this;
	}

	//Equivalence (Overload of == operator)
	template < typename Type >
	MapilBool Vector4 < Type > ::operator==( const Vector4 < Type >& v )
	{
		return ( ( m_X == v.m_X ) && ( m_Y == v.m_Y ) && ( m_Z == v.m_Z ) && ( m_W == v.m_W ) );
	}

	//Add / Binary operator (Overload of += operator)
	template < typename Type >
	Vector4 < Type >& Vector4 < Type > ::operator+=( const Vector4 < Type >& v )
	{
		m_X += v.m_X;
		m_Y += v.m_Y;
		m_Z += v.m_Z;
		m_W += v.m_W;

		return *this;
	}

	//Subtract / Binary operator (Overload of -= operator)
	template < typename Type >
	Vector4 < Type >& Vector4 < Type > ::operator-=( const Vector4 < Type >& v )
	{
		m_X -= v.m_X;
		m_Y -= v.m_Y;
		m_Z -= v.m_Z;
		m_W -= v.m_W;

		return *this;
	}

	//Add
	template < typename Type >
	MapilVoid Vector4 < Type > ::Add( const Vector4 < Type >& v )
	{
		m_X += v.m_X;
		m_Y += v.m_Y;
		m_Z += v.m_Z;
		m_W += v.m_W;
	}

	//Subtract
	template < typename Type >
	MapilVoid Vector4 < Type > ::Sub( const Vector4 < Type >& v )
	{
		m_X -= v.m_X;
		m_Y -= v.m_Y;
		m_Z -= v.m_Z;
		m_W -= v.m_W;
	}

	//Multiply constant
	template < typename Type >
	MapilVoid Vector4 < Type > ::MulConst( Type num )
	{
		m_X *= num;
		m_Y *= num;
		m_Z *= num;
		m_W *= num;
	}

	//Get sum of square
	template < typename Type >
	Type Vector4 < Type > ::GetSumSquare() const
	{
		return ( m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W );
	}

	//Get norm
	template < typename Type >
	Type Vector4 < Type > ::GetNorm() const
	{
		return sqrt( m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W );
	}

	//Normalize
	template < typename Type >
	MapilVoid Vector4 < Type > ::Normalize()
	{
		Type mulConst = 1 / sqrt( m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W );

		m_X *= mulConst;
		m_Y *= mulConst;
		m_Z *= mulConst;
		m_W *= mulConst;
	}

	//Get inner product
	template < typename Type >
	Type Vector4 < Type > ::GetInnerProduct( const Vector4 < Type >& v ) const
	{
		return ( m_X * v.m_X + m_Y * v.m_Y + m_Z * v.m_Z + m_W * v.m_W );
	}

	// Rotate X. ( Right-handed system. )
	//		template < typename Type >
	//		Portabillity::PortVoid RotateXRH(	Vector3 < Type >* pOutV,
	//									const Vector3 < Type >& inV,
	//									MapilFloat32 angle )
	//		{
	////	pOutV->m_X = inV
	//		}


	template < typename Type, MapilInt32 DIM >
	class VectorN
	{
	public:
		Type	m_Elm[ DIM ];
		VectorN();
		VectorN( const VectorN < Type, DIM >& v );
		~VectorN();
	};

	template < typename Type, MapilInt32 DIM >
	VectorN < Type, DIM > ::VectorN()
	{
		for( MapilInt32 i = 0; i < DIM; ++i ){
			m_Elm[ i ] = 0;
		}
	}

	template < typename Type, MapilInt32 DIM >
	VectorN < Type, DIM > ::VectorN( const VectorN < Type, DIM >& v )
	{
		for( MapilInt32 i = 0; i < DIM; ++i ){
			m_Elm[ i ] = v.m_Elm[ i ];
		}
	}

	template < typename Type, MapilInt32 DIM >
	VectorN < Type, DIM > ::~VectorN()
	{
		for( MapilInt32 i = 0; i < DIM; ++i ){
			m_Elm[ i ] = 0;
		}
	}


	template < typename Type >
	Type CalcDeterminant(	const Vector3 < Type >& v0,
							const Vector3 < Type >& v1,
							const Vector3 < Type >& v2 )
	{
		return	v0.m_X * v1.m_Y * v2.m_Z + v1.m_X * v2.m_Y * v0.m_Z + v2.m_X * v0.m_Y * v1.m_Z
				- v0.m_X * v2.m_Y * v1.m_Z - v1.m_X * v0.m_Y * v2.m_Z - v2.m_X * v1.m_Y * v0.m_Z;
	}
}

#endif
