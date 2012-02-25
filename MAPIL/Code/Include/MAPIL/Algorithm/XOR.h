/**
*	@file	XOR.h
*	@brief	.
*	@date	2012.2.14 (Tue) 14:50
*/

#ifndef INCLUDED_MAPIL_XOR_H
#define INCLUDED_MAPIL_XOR_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "../Type.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{

	class XOR
	{
	private:
		MapilInt32	m_Key;
	public:
		XOR( MapilInt32 key );
		~XOR();
		MapilVoid Encrypt( MapilChar* pStr, MapilInt32 strLen );
		MapilVoid Decrypt( MapilChar* pStr, MapilInt32 strLen );
	};
}

#endif	// INCLUDED_MAPIL_XOR_H
