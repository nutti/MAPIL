/**
*	@file	XOR.cpp
*	@brief	Implementation of XOR.h.
*	@date	2012.2.14 (Tue) 14:50
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Algorithm/XOR.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	XOR::XOR( MapilInt32 key ) : m_Key( key )
	{
	}

	XOR::~XOR()
	{
	}

	MapilVoid XOR::Encrypt( MapilChar* pStr, MapilInt32 strLen )
	{
		for( MapilInt32 i = 0; i < strLen; ++i ){
			pStr[ i ] ^= m_Key;
		}
	}

	MapilVoid XOR::Decrypt( MapilChar* pStr, MapilInt32 strLen )
	{
		for( MapilInt32 i = 0; i < strLen; ++i ){
			pStr[ i ] ^= m_Key;
		}
	}
}