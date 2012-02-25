/**
*	@file	Archiver.h
*	@brief	Archiver class provides to handle the archive file.
*	@date	2012.2.4 (Sat) 9:07
*/

#ifndef INCLUDED_MAPIL_LZ_H
#define INCLUDED_MAPIL_LZ_H

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

	class LZ
	{
	private:
		MapilChar*			m_pRaw;
		MapilChar*			m_pComp;
		MapilChar*			m_pWinBeg;
		MapilChar*			m_pWinEnd;
		MapilChar*			m_pDataEnd;
		const MapilUChar	WINDOW_SIZE;
		const MapilUChar	MINIMUM_ADOPTION_SIZE;
		const MapilChar		ESCAPE_CHAR;

		MapilInt32 Search( MapilUChar* pIndex, MapilUChar* pLen );
	public:
		LZ( MapilUChar winSize, MapilUChar minAdoptionSize, MapilChar escape = '[' );
		~LZ();
		MapilVoid Reset();
		MapilVoid Compress( MapilChar* pRaw, MapilInt32 rawLen, MapilChar** ppComp, MapilInt32* pCompLen );
		MapilVoid Expand( MapilChar* pComp, MapilInt32 compLen, MapilChar** ppRaw, MapilInt32* pRawLen );
	};
}

#endif	// INCLUDED_MAPIL_LZ_H
