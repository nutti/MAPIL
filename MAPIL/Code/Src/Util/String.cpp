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
			va_end( list );
			return NULL;
		}
		_vstprintf( strBuf, pStr, list );			//Create string
		va_end( list );
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
			va_end( list );
			return -1;
		}
		pStrBuf = new MapilTChar [ strLen ];
		_vstprintf( pStrBuf, pStrSrc, list );
		va_end( list );

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
#if defined ( OS_WIN_32BIT )
		WideCharToMultiByte( CP_ACP, 0, pSrc, srcSize, pDst, dstSize, NULL, NULL );
#endif
	}

	// Convert to multibyte.
	MapilVoid ConvertToMultiByte( const MapilChar* pSrc, MapilInt32 srcSize, MapilChar* pDst, MapilInt32 dstSize )
	{
		if( ::strlen( pSrc ) < srcSize ){
			::strcpy( pDst, pSrc );
		}
	}

	// Convert to tchar.
	MapilVoid ConvertToTChar( const MapilChar* pSrc, MapilInt32 srcSize, MapilTChar* pDst, MapilInt32 dstSize )
	{
#if defined ( CHAR_CODE_UNICODE )
		::MultiByteToWideChar( CP_ACP, 0, pSrc, srcSize, pDst, dstSize );
#elif defined( CHAR_CODE_MULTIBYTE )
		if( ::strlen( pSrc ) < srcSize ){
			::strcpy( pDst, pSrc );
		}
#endif
	}

	// Convert to tchar.
	MapilVoid ConvertToTChar( const MapilWChar* pSrc, MapilInt32 srcSize, MapilTChar* pDst, MapilInt32 dstSize )
	{
#if defined ( CHAR_CODE_UNICODE )
		::wcscpy_s( pDst, srcSize, pSrc );
#elif defined ( CHAR_CODE_MULTIBYTE )
#if defined ( OS_WIN_32BIT )
		::WideCharToMultiByte( CP_ACP, 0, pSrc, srcSize, pDst, dstSize, NULL, NULL );
#endif
#endif
	}

	// Get token list from string.
	AStringList GetTokenListFromAString( const AString& str, const AString& delim )
	{
		AStringList strList;
		AString::size_type start = 0;
		while( MapilTrue ){
			AString::size_type end = str.find( delim, start );
			// Delimiter found.
			if( end != AString::npos ){
				strList.push_back( str.substr( start, end - start ) );
			}
			// Delimiter not found.
			else{
				strList.push_back( str.substr( start, str.length() - start ) );
				break;
			}
			start = end + delim.length();
		}

		return strList;
	}

	// Get token list from wstring.
	WStringList GetTokenListFromWString( const WString& str, const WString& delim )
	{
		WStringList strList;
		WString::size_type start = 0;
		while( MapilTrue ){
			WString::size_type end = str.find( delim, start );
			// Delimiter found.
			if( end != WString::npos ){
				strList.push_back( str.substr( start, end - start ) );
			}
			// Delimiter not found.
			else{
				strList.push_back( str.substr( start, str.length() - start ) );
				break;
			}
			start = end + delim.length();
		}

		return strList;
	}

	// Get token list from tstring.
	TStringList GetTokenListFromTString( const TString& str, const TString& delim )
	{
#if defined ( CHAR_CODE_UNICODE )
		return GetTokenListFromWString( str, delim );
#elif defined ( CHAR_CODE_MULTIBYTE )
#if defined ( OS_WIN_32BIT )
		return GetTokenListFromAString( str, delim );
#endif
#endif
	}
}
