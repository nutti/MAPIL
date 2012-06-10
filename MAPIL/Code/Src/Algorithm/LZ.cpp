/**
*	@file	LZ.cpp
*	@brief	Implementation of LZ.
*	@date	2012.2.11 (Sat) 16:40
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Algorithm/LZ.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	LZ::LZ(	MapilUChar winSize, 
			MapilUChar minAdoptionSize,
			MapilChar escape ) :	m_pRaw( NULL ),
									m_pComp( NULL ),
									m_pWinBeg( NULL ),
									m_pWinEnd( NULL ),
									m_pDataEnd( NULL ),
									WINDOW_SIZE( winSize ),
									MINIMUM_ADOPTION_SIZE( minAdoptionSize ),
									ESCAPE_CHAR( escape )
	{
	}

	LZ::~LZ()
	{
		Reset();
	}

	MapilVoid LZ::Reset()
	{
		m_pRaw = NULL;
		m_pComp = NULL;
		m_pWinBeg = NULL;
		m_pWinEnd = NULL;
		m_pDataEnd = NULL;
	}

	MapilInt32 LZ::Search( MapilUChar* pIndex, MapilUChar* pLen )
	{
		MapilUInt32 count = 0;

		for( MapilChar* p = m_pWinBeg; p < m_pWinEnd; ++p ){
			for( count = 0; m_pWinEnd[ count ] == p[ count ]; ++count ){
				if( count >= WINDOW_SIZE || &p[ count ] >= m_pWinEnd ){
					break;
				}
			}
			if( count >= MINIMUM_ADOPTION_SIZE && -( p - m_pWinEnd ) != ESCAPE_CHAR ){
				*pIndex = -( p - m_pWinEnd );
				*pLen = count;
				return 1;
			}
		}

		*pIndex = 0;
		*pLen = 0;

		return 0;
	}

	MapilVoid LZ::Compress(	MapilChar* pRaw,
							MapilInt32 rawLen,
							MapilChar** ppComp,
							MapilInt32 bufLen,
							MapilInt32* pCompLen )
	{
		m_pRaw = pRaw;
		m_pComp = new MapilChar [ rawLen * 2 ];		// Internal buffer.
		ZeroObject( m_pComp, rawLen * 2 );
		m_pWinBeg = pRaw;
		m_pWinEnd = pRaw;
		m_pDataEnd = pRaw + rawLen;

		MapilChar* q = m_pComp;

		for( ; m_pWinEnd < m_pDataEnd; ){
			MapilUChar index;
			MapilUChar len;
			MapilInt32 result;
			result = Search( &index, &len );
			// Check if the string pointer is in the valid range.
			MapilInt32 surplus = m_pDataEnd - m_pWinEnd;
			if( len > surplus ){
				len = surplus;
			}

			if( result == 1 ){
				if( index > 0 && len >= MINIMUM_ADOPTION_SIZE ){
					*q++ = ESCAPE_CHAR;
					*q++ = index;
					*q++ = len;
					m_pWinEnd += len;
					if( m_pWinEnd - m_pWinBeg > WINDOW_SIZE ){
						m_pWinBeg = m_pWinEnd - WINDOW_SIZE;
					}
				}
			}
			else if( result == 0 ){
				if( *m_pWinEnd == ESCAPE_CHAR ){
					*q++ = ESCAPE_CHAR;
				}
				*q++ = *m_pWinEnd;
				++m_pWinEnd;
				if( m_pWinEnd - m_pWinBeg > WINDOW_SIZE ){
					m_pWinBeg = m_pWinEnd - WINDOW_SIZE;
				}
			}	
		}

		*pCompLen = q - m_pComp;
		// If length is bigger than buffer length, it is an error case.
		if( bufLen < *pCompLen ){
			return;
		}
		::memcpy( *ppComp, m_pComp, *pCompLen );

		SafeDeleteArray( m_pComp );
	}

	MapilVoid LZ::Expand(	MapilChar* pComp,
							MapilInt32 compLen,
							MapilChar** ppRaw,
							MapilInt32 bufLen,
							MapilInt32* pRawLen )
	{
		m_pComp = pComp;
		m_pRaw = new MapilChar [ compLen * 1000 ];		// Internal buffer.
		ZeroObject( m_pRaw, compLen * 1000 );
		
		MapilChar* p = m_pComp;
		MapilChar* q = m_pRaw;

		for( ; p < compLen + m_pComp; ){
			if( *p == ESCAPE_CHAR ){
				if( *( p + 1 ) == ESCAPE_CHAR ){
					*q++ = ESCAPE_CHAR;
					p += 2;
				}
				else{
					MapilUChar index = *( p + 1 );
					MapilUChar size = *( p + 2 );
					MapilChar* pCopy = q - index;
					for( MapilInt32 i = 0; i < size; ++i ){
						*q++ = pCopy[ i ];
					}
					p += 3;
				}
			}
			else{
				*q++ = *p++;
			}
		}

		*pRawLen = q - m_pRaw;
		// If length is bigger than buffer length, it is an error case.
		if( bufLen < *pRawLen ){
			return;
		}
		::memcpy( *ppRaw, m_pRaw, *pRawLen );

		SafeDeleteArray( m_pRaw );
	}
}