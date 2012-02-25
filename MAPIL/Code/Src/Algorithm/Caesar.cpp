/**
*	@file	Caesar.cpp
*	@brief	Implementation of Caesar.h.
*	@date	2012.2.14 (Tue) 14:28
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Algorithm/Caesar.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	Caesar::Caesar( MapilInt32 slideCount ) : m_SlideCount( slideCount )
	{
	}

	Caesar::~Caesar()
	{
		m_SlideCount = 0;
	}

	MapilVoid Caesar::Encrypt( MapilChar* pStr, MapilInt32 strLen )
	{
		for( MapilInt32 i = 0; i < strLen; ++i ){
			pStr[ i ] += m_SlideCount;
		}
	}

	MapilVoid Caesar::Decrypt( MapilChar* pStr, MapilInt32 strLen )
	{
		for( MapilInt32 i = 0; i < strLen; ++i ){
			pStr[ i ] -= m_SlideCount;
		}
	}
}