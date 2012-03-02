/**
*	@file	String.h
*	@brief	
*	@date	2011.7.17 (Sun) 15:38
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include <cstdarg>

#ifdef OS_WIN_32BIT
#include <Windows.h>
#endif

#include "../../Include/MAPIL/Util/String.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/TChar.h"

#ifdef OS_WIN_32BIT
#pragma warning ( disable : 4996 )
#endif

namespace MAPIL
{

	//Function which returns string created from various types
	const MapilTChar* GetFlexibleString( const MapilTChar* pStr, ... )
	{
		static MapilTChar strBuf[ 1024 ];		//Buffer which string is stored
		va_list list;										//Variable-length list
		MapilInt32 strLen;						//String length

		va_start( list, pStr );
#ifdef OS_WIN_32BIT
		strLen = _vsctprintf( pStr, list ) + 1;				//Length of created string (NULL character isn't included, so +1 is needed)
		if( strLen > 1024 ){
			return NULL;
		}
		_vstprintf( strBuf, pStr, list );			//Create string
#endif
		return strBuf;
	}

	//Function which creates string from various type
	MapilInt32 CreateFlexibleString( MapilTChar* pStrDst, MapilInt32 strLenDst, const MapilTChar* pStrSrc, ... )
	{
		MapilTChar* pStrBuf;			//Buffer which string is stored
		va_list list;								//Variable-length list
		MapilInt32 strLen;				//String length

		va_start( list, pStrSrc );
#ifdef OS_WIN_32BIT
		strLen = _vsctprintf( pStrSrc, list ) + 1;
		if( strLen > strLenDst ){
			return -1;
		}
		pStrBuf = new MapilTChar [ strLen ];
		_vstprintf( pStrBuf, pStrSrc, list );

		_tcscpy_s( pStrDst, strLenDst, pStrBuf );
		SafeDeleteArray( pStrBuf );
#endif

		return 0;
	}

	// Convert to unicode.
	MapilVoid ConvertToUnicode( const MapilChar* pSrc, MapilInt32 srcSize, MapilWChar* pDst, MapilInt32 dstSize )
	{
#ifdef OS_WIN_32BIT
		MultiByteToWideChar( CP_ACP, 0, pSrc, srcSize, pDst, dstSize );
#endif
	}

	// Convert to multibyte.
	MapilVoid ConvertToMultiByte( const MapilWChar* pSrc, MapilInt32 srcSize, MapilChar* pDst, MapilInt32 dstSize )
	{
#ifdef OS_WIN_32BIT
		WideCharToMultiByte( CP_ACP, 0, pSrc, srcSize, pDst, dstSize, NULL, NULL );
#endif
	}

	// Convert to tchar.
	MapilVoid ConvertToTChar( const MapilChar* pSrc, MapilInt32 srcSize, MapilTChar* pDst, MapilInt32 dstSize )
	{
#if defined ( CHAR_CODE_UNICODE )
		::MultiByteToWideChar( CP_ACP, 0, pSrc, srcSize, pDst, dstSize );
#elif defined( CHAR_CODE_MULTIBYTE )
		::strcpy_s( pDst, srcSize, pSrc );
#endif
	}

	// Convert to tchar.
	MapilVoid ConvertToTChar( const MapilWChar* pSrc, MapilInt32 srcSize, MapilTChar* pDst, MapilInt32 dstSize )
	{
#if defined ( CHAR_CODE_UNICODE )
		::wcscpy_s( pDst, srcSize, pSrc );
#elif defined ( CHAR_CODE_MULTIBYTE )
		::WideCharToMultiByte( CP_ACP, 0, pSrc, srcSize, pDst, dstSize, NULL, NULL );
#endif
	}
}
