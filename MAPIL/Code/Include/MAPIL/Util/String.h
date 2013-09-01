/**
*	@file	String.h
*	@brief	
*	@date	2011.7.17 (Sun) 15:38
*/

#ifndef INCLUDED_MAPIL_STRING_H
#define INCLUDED_MAPIL_STRING_H

#include "../CrossPlatform.h"

#include "../Type.h"

#include <vector>

namespace MAPIL
{
	typedef std::basic_string < MapilTChar >		TString;
	typedef std::basic_string < MapilChar >			AString;
	typedef std::basic_string < MapilWChar >		WString;
	typedef std::vector < TString >					TStringList;
	typedef std::vector < AString >					AStringList;
	typedef std::vector < WString >					WStringList;


	//Function which returns string created from various types
	const MapilTChar* GetFlexibleString( const MapilTChar* pStr, ... );

	//Function which creates string from various type
	MapilInt32 CreateFlexibleString( MapilTChar* pStrDst, MapilInt32 strLenDst, const MapilTChar* pStrSrc, ... );

	// Convert to unicode.
	MapilVoid ConvertToUnicode( const MapilChar* pSrc, MapilInt32 srcSize, MapilWChar* pDst, MapilInt32 dstSize );

	// Convert to multibyte.
	MapilVoid ConvertToMultiByte( const MapilWChar* pSrc, MapilInt32 srcSize, MapilChar* pDst, MapilInt32 dstSize );

	// Convert to multibyte.
	MapilVoid ConvertToMultiByte( const MapilChar* pSrc, MapilInt32 srcSize, MapilChar* pDst, MapilInt32 dstSize );

	// Convert to tchar.
	MapilVoid ConvertToTChar( const MapilChar* pSrc, MapilInt32 srcSize, MapilTChar* pDst, MapilInt32 dstSize );

	// Convert to tchar.
	MapilVoid ConvertToTChar( const MapilWChar* pSrc, MapilInt32 srcSize, MapilTChar* pDst, MapilInt32 dstSize );

	// Get token list from string.
	AStringList GetTokenListFromAString( const AString& str, const AString& delim );

	// Get token list from wstring.
	WStringList GetTokenListFromWString( const WString& str, const WString& delim );

	// Get token list from tstring.
	TStringList GetTokenListFromTString( const TString& str, const TString& delim );
}

#endif
