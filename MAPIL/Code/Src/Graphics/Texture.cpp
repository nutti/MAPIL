/**
*	@file	Texture.cpp
*	@brief	Implementation of Texture.h.
*	@date	2011.7.17 (Sun) 12:09
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Texture.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	Texture::Texture( SharedPointer < GraphicsDevice > pDev ) :	Graphics( pDev ),
																m_TexSize(),
																m_pBeginPosList( NULL ),
																m_pSizeList( NULL ),
																m_SplitTotal( 0 ),
																m_SplitIndex( -1 )
	{
	}

	Texture::~Texture()
	{
		m_SplitTotal = 0;
		SafeDeleteArray( m_pSizeList );
		SafeDeleteArray( m_pBeginPosList );
	}

	MapilVoid Texture::SetSplitIndex( MapilInt32 index )
	{
		if( m_SplitTotal <= index ){
			return;
		}

		m_SplitIndex = index;
	}

	Vector2 < MapilInt32 > Texture::GetSplitSize() const
	{
		if( m_SplitTotal == 0 ){
			return m_TexSize;
		}
		else{
			return m_pSizeList[ m_SplitIndex ];
		}
	}

	Vector2 < MapilInt32 > Texture::GetSplitBeginPos() const
	{
		if( m_SplitTotal == 0 ){
			return Vector2 < MapilInt32 > ( 0, 0 );
		}
		else{
			return m_pBeginPosList[ m_SplitIndex ];
		}
	}

	MapilBool Texture::IsSplit() const
	{
		return ( m_SplitTotal != 0 ) ? MapilTrue : MapilFalse;
	}
}