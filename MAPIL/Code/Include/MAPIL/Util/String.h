/**
*	@file	String.h
*	@brief	
*	@date	2011.7.17 (Sun) 15:38
*/

#ifndef INCLUDED_MAPIL_STRING_H
#define INCLUDED_MAPIL_STRING_H

#include "../CrossPlatform.h"

#include "../Type.h"

namespace MAPIL
{
	//Function which returns string created from various types
	const MapilTChar* GetFlexibleString( const MapilTChar* pStr, ... );

	//Function which creates string from various type
	MapilInt32 CreateFlexibleString( MapilTChar* pStrDst, MapilInt32 strLenDst, const MapilTChar* pStrSrc, ... );

	// Convert to unicode.
	MapilVoid ConvertToUnicode( const MapilChar* pSrc, MapilInt32 srcSize, MapilWChar* pDst, MapilInt32 dstSize );

	// Convert to multibyte.
	MapilVoid ConvertToMultiByte( const MapilWChar* pSrc, MapilInt32 srcSize, MapilChar* pDst, MapilInt32 dstSize );

	// Convert to tchar.
	MapilVoid ConvertToTChar( const MapilChar* pSrc, MapilInt32 srcSize, MapilTChar* pDst, MapilInt32 dstSize );

	// Convert to tchar.
	MapilVoid ConvertToTChar( const MapilWChar* pSrc, MapilInt32 srcSize, MapilTChar* pDst, MapilInt32 dstSize );
}

#endif