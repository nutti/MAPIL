/**
*	@file	Caesar.h
*	@brief	.
*	@date	2012.2.14 (Tue) 14:28
*/

#ifndef INCLUDED_MAPIL_CAESAR_H
#define INCLUDED_MAPIL_CAESAR_H

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

	class Caesar 
	{
	private:
		MapilInt32	m_SlideCount;
	public:
		Caesar( MapilInt32 slideCount );
		~Caesar();
		MapilVoid Encrypt( MapilChar* pStr, MapilInt32 strLen );
		MapilVoid Decrypt( MapilChar* pStr, MapilInt32 strLen );
	};
}

#endif	// INCLUDED_MAPIL_CAESAR_H
