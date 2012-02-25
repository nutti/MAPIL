/**
*	@file	Transformation.hpp
*	@brief	
*	@date	2011.8.31 (Wed) 8:52
*/

#ifndef INCLUDED_MAPIL_TRANSFORMATOIN_HPP
#define INCLUDED_MAPIL_TRANSFORMATION_HPP

#include "../CrossPlatform.h"

#if defined ( API_WIN32API )
#include <Windows.h>
#endif

#include "../Type.h"

namespace MAPIL
{
#if defined ( API_WIN32API )
	//Transform float into DWORD
	inline DWORD TransformFloatIntoDWORD( MapilFloat32 f )
	{
		return *( reinterpret_cast < DWORD* > ( &f ) );
	}
#endif	// API_WIN32API

#if defined ( PI )
#else
#define PI ( 3.141592653589793238 )
#endif

	
	inline MapilDouble RadToDeg( MapilDouble rad )
	{
		return rad * 180.0 / PI;
	}

	inline MapilDouble DegToRad( MapilDouble deg )
	{
		return deg * PI / 180.0;
	}

	enum ByteOrder
	{
		BYTE_ORDER_LITTLE	= 0,
		BYTE_ORDER_BIG		= 1,
	};

	inline MapilInt32 TransformCharIntoInt32( const MapilChar* pData, MapilInt32 byteOrder )
	{
		MapilInt32 value = 0;

		if( byteOrder == BYTE_ORDER_BIG ){
			value = pData[ 0 ];
			value |= ( pData[ 1 ] << 8 );
			value |= ( pData[ 2 ] << 16 );
			value |= ( pData[ 3 ] << 24 );
		}
		else if( byteOrder == BYTE_ORDER_LITTLE ){
			value = ( pData[ 3 ] & 0xFF );
			value |= ( pData[ 2 ] & 0xFF ) << 8;
			value |= ( pData[ 1 ] & 0xFF ) << 16;
			value |= ( pData[ 0 ] & 0xFF ) << 24;
		}

		return value;
	}

	inline MapilVoid TransformInt32IntoChar( MapilInt32 data, MapilChar* pOut, MapilInt32 byteOrder )
	{
		if( byteOrder == BYTE_ORDER_BIG ){
			pOut[ 0 ] = data & 0xFF;
			pOut[ 1 ] = ( data >> 8 ) & 0xFF;
			pOut[ 2 ] = ( data >> 16 ) & 0xFF;
			pOut[ 3 ] = ( data >> 24 ) & 0xFF;
		}
		else if( byteOrder == BYTE_ORDER_LITTLE ){
			pOut[ 3 ] = data & 0xFF;
			pOut[ 2 ] = ( data >> 8 ) & 0xFF;
			pOut[ 1 ] = ( data >> 16 ) & 0xFF;
			pOut[ 0 ] = ( data >> 24 ) & 0xFF;
		}
	}
}

#endif