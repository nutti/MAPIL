/**
*	@file	D3DTexture.cpp
*	@brief	Implementation of D3DTexture.h.
*	@date	2011.8.25 (Thu) 18:37
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_9_0_C )

#include "../../Include/MAPIL/IO/Archiver.h"
#include "../../Include/MAPIL/Util/String.h"
#include "../../Include/MAPIL/Graphics/D3DTexture.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DTexture::D3DTexture( SharedPointer < GraphicsDevice > pDev ) :	Texture( pDev ),
																		m_pD3DTexture( NULL ),
																		m_ppD3DTexture( NULL )
	{
	}

	D3DTexture::~D3DTexture()
	{
		if( m_ppD3DTexture ){
			for( MapilInt32 i = 0; i < m_SplitTotal; ++i ){
				SafeRelease( m_ppD3DTexture[ i ] );
			}
			SafeDeleteArray( m_ppD3DTexture );
		}
		SafeRelease( m_pD3DTexture );
		m_IsUsed = MapilFalse;
	}

	MapilVoid D3DTexture::Create( const MapilTChar* pFileName )
	{
		Assert(	!m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DTexture" ),
				TSTR( "Create" ),
				TSTR( "The texture was already created." ),
				-1 );

		//Load texture from file
		if( FAILED( ::D3DXCreateTextureFromFileEx(	m_pDev->GetDev().GetPointer(),
													pFileName,
													D3DX_DEFAULT_NONPOW2,
													D3DX_DEFAULT_NONPOW2,
													D3DX_DEFAULT,
													0,
													D3DFMT_UNKNOWN,
													D3DPOOL_MANAGED,
													D3DX_FILTER_NONE,
													D3DX_DEFAULT,
													0,
													NULL,
													NULL,
													&m_pD3DTexture ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DTexture" ),
									TSTR( "Create" ),
									TSTR( "Failed to load texture from file." ),
									-1 );
		}

		//Calculate center coordinate of texture
		::D3DXIMAGE_INFO imgInfo;
		::D3DXGetImageInfoFromFile( pFileName, &imgInfo );
		m_TexSize.m_X = imgInfo.Width;
		m_TexSize.m_Y = imgInfo.Height;

		m_IsUsed = MapilTrue;
	}

	MapilVoid D3DTexture::Create( Archiver* pArchiver, const MapilTChar* pFileName )
	{
		Assert(	!m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DTexture" ),
				TSTR( "Create" ),
				TSTR( "The texture was already created." ),
				-1 );

		MapilChar name[ 1024 ];
		ConvertToMultiByte( pFileName, -1, name, 1024 );

		MapilInt32 size = pArchiver->GetContentsSize( name );
		MapilChar* pData = new MapilChar [ size ];
		pArchiver->Load( name, pData );

		//Load texture from file
		if( FAILED( ::D3DXCreateTextureFromFileInMemoryEx(	m_pDev->GetDev().GetPointer(),
															pData,
															size,
															D3DX_DEFAULT_NONPOW2,
															D3DX_DEFAULT_NONPOW2,
															D3DX_DEFAULT,
															0,
															D3DFMT_UNKNOWN,
															D3DPOOL_MANAGED,
															D3DX_FILTER_NONE,
															D3DX_DEFAULT,
															0,
															NULL,
															NULL,
															&m_pD3DTexture ) ) ){
			SafeDeleteArray( pData );
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DTexture" ),
									TSTR( "Create" ),
									TSTR( "Failed to load texture from file." ),
									-1 );
		}

		//Calculate center coordinate of texture
		::D3DXIMAGE_INFO imgInfo;
		::D3DXGetImageInfoFromFileInMemory( pData, size, &imgInfo );
		m_TexSize.m_X = imgInfo.Width;
		m_TexSize.m_Y = imgInfo.Height;

		SafeDeleteArray( pData );

		m_IsUsed = MapilTrue;
	}

	MapilVoid D3DTexture::Split( MapilInt32 column, MapilInt32 row, MapilInt32 width, MapilInt32 height )
	{
		m_SplitTotal = column * row;

		// No operation occurs, when the size of texture doesn't match with the sum of size
		// to be split.
		if( m_TexSize.m_X < row * width ){
			return;
		}
		if( m_TexSize.m_Y < column * height ){
			return;
		}

		// Set up the list.
		m_SplitIndex = 0;
		m_SplitTotal = row * column;
		m_pSizeList = new Vector2 < MapilInt32 > [ m_SplitTotal ];
		m_pBeginPosList = new Vector2 < MapilInt32 > [ m_SplitTotal ];
		//MapilInt32 xSize = m_TexSize.m_X / row;
		//MapilInt32 ySize = m_TexSize.m_Y / column;
		MapilInt32 xSize = width;
		MapilInt32 ySize = height;
		MapilInt32 xPos = 0;
		MapilInt32 yPos = 0;
		for( MapilInt32 i = 0; i < column; ++i ){
			for( MapilInt32 j = 0; j < row; ++j ){
				m_pBeginPosList[ i * row + j ].m_X = xPos;
				m_pBeginPosList[ i * row + j ].m_Y = yPos;
				m_pSizeList[ i * row + j ].m_X = xSize;
				m_pSizeList[ i * row + j ].m_Y = ySize;
				xPos += xSize;
			}
			xPos = 0;
			yPos += ySize;
		}

		m_ppD3DTexture = new ::LPDIRECT3DTEXTURE9[ m_SplitTotal ];

		// Lock the source texture.
		::D3DLOCKED_RECT srcRect;
		if( FAILED( m_pD3DTexture->LockRect( 0, &srcRect, NULL, D3DLOCK_DISCARD ) ) ){
			if( FAILED( m_pD3DTexture->LockRect( 0, &srcRect, NULL, 0 ) ) ){
				throw MapilException( CURRENT_POSITION, TSTR( "Failed to lock rectangle of the source texture." ), -1 );
			}
		}

		// Get information of the original texture.
		D3DSURFACE_DESC desc;
		m_pD3DTexture->GetLevelDesc( 0, &desc );

		// Construct the images.
		for( MapilInt32 i = 0; i < m_SplitTotal; ++i ){
			if( FAILED( m_pDev->GetDev().GetPointer()->CreateTexture(	m_pSizeList[ i ].m_X,
																		m_pSizeList[ i ].m_Y,
																		1,
																		D3DUSAGE_DYNAMIC,
																		D3DFMT_A8R8G8B8,
																		D3DPOOL_MANAGED,
																		&m_ppD3DTexture[ i ],
																		NULL ) ) ){
				if( FAILED( m_pDev->GetDev().GetPointer()->CreateTexture(	m_pSizeList[ i ].m_X,
																			m_pSizeList[ i ].m_Y,
																			1,
																			0,
																			D3DFMT_A8R8G8B8,
																			D3DPOOL_MANAGED,
																			&m_ppD3DTexture[ i ],
																			NULL ) ) ){
					throw MapilException( CURRENT_POSITION, TSTR( "Failed to create texture resources." ), -2 );
				}
			}

			::D3DLOCKED_RECT dstRect;
			if( FAILED( m_ppD3DTexture[ i ]->LockRect( 0, &dstRect, NULL, D3DLOCK_DISCARD ) ) ){
				if( FAILED( m_ppD3DTexture[ i ]->LockRect( 0, &dstRect, NULL, 0 ) ) ){
					throw MapilException(	TSTR( "Mapil" ),
											TSTR( "D3DTexture" ),
											TSTR( "Split" ),
											TSTR( "Failed to lock rectangle of the destination texture." ),
											-3 );
				}
			}
			
			// Copy the source texture to the destination texture.
			DWORD* pDstPtr = static_cast < DWORD* > ( dstRect.pBits );
			DWORD* pSrcPtr = static_cast < DWORD* > ( srcRect.pBits );
			pSrcPtr += m_pBeginPosList[ i ].m_Y * srcRect.Pitch / sizeof( DWORD );
			for( MapilInt32 j = 0; j < m_pSizeList[ i ].m_Y; ++j ){
				for( MapilInt32 k = 0; k < m_pSizeList[ i ].m_X; ++k ){
					pDstPtr[ k ] = pSrcPtr[ k + m_pBeginPosList[ i ].m_X ];
				}
				// Pitch = width * DWORD (Color component.)
				pDstPtr += dstRect.Pitch / sizeof( DWORD );
				pSrcPtr += srcRect.Pitch / sizeof( DWORD );
			}

			m_ppD3DTexture[ i ]->UnlockRect( 0 );
		}

		// Release the original texture.
		m_pD3DTexture->UnlockRect( 0 );
		SafeRelease( m_pD3DTexture );
	}

	MapilVoid D3DTexture::SplitCopy(	SharedPointer < Texture >* pTexture,
										MapilInt32 column,
										MapilInt32 row,
										MapilInt32 width,
										MapilInt32 height )
	{
		MapilInt32 splitTotal = column * row;

		// No operation occurs, when the size of texture doesn't match with the sum of size
		// to be split.
		if( m_TexSize.m_X < row * width ){
			return;
		}
		if( m_TexSize.m_Y < column * height ){
			return;
		}

		// Set up the list.
		MapilInt32 splitIndex = 0;
		splitTotal = row * column;
		Vector2 < MapilInt32 >* pSizeList = new Vector2 < MapilInt32 > [ splitTotal ];
		Vector2 < MapilInt32 >* pBeginPosList = new Vector2 < MapilInt32 > [ splitTotal ];
		//MapilInt32 xSize = m_TexSize.m_X / row;
		//MapilInt32 ySize = m_TexSize.m_Y / column;
		MapilInt32 xSize = width;
		MapilInt32 ySize = height;
		MapilInt32 xPos = 0;
		MapilInt32 yPos = 0;
		for( MapilInt32 i = 0; i < column; ++i ){
			for( MapilInt32 j = 0; j < row; ++j ){
				pBeginPosList[ i * row + j ].m_X = xPos;
				pBeginPosList[ i * row + j ].m_Y = yPos;
				pSizeList[ i * row + j ].m_X = xSize;
				pSizeList[ i * row + j ].m_Y = ySize;
				xPos += xSize;
			}
			xPos = 0;
			yPos += ySize;
		}

		// Lock the source texture.
		::D3DLOCKED_RECT srcRect;
		if( FAILED( m_pD3DTexture->LockRect( 0, &srcRect, NULL, D3DLOCK_DISCARD ) ) ){
			if( FAILED( m_pD3DTexture->LockRect( 0, &srcRect, NULL, 0 ) ) ){
				throw MapilException( CURRENT_POSITION, TSTR( "Failed to lock rectangle of the source texture." ), -1 );
			}
		}

		// Get information of the original texture.
		D3DSURFACE_DESC desc;
		m_pD3DTexture->GetLevelDesc( 0, &desc );

		// Construct the images.
		for( MapilInt32 i = 0; i < splitTotal; ++i ){
			SharedPointer < D3DTexture > pD3DTex;
			pD3DTex.DownCast( pTexture[ i ] );
			if( FAILED( m_pDev->GetDev().GetPointer()->CreateTexture(	pSizeList[ i ].m_X,
																		pSizeList[ i ].m_Y,
																		1,
																		D3DUSAGE_DYNAMIC,
																		D3DFMT_A8R8G8B8,
																		D3DPOOL_MANAGED,
																		&pD3DTex->m_pD3DTexture,
																		NULL ) ) ){
				if( FAILED( m_pDev->GetDev().GetPointer()->CreateTexture(	pSizeList[ i ].m_X,
																			pSizeList[ i ].m_Y,
																			1,
																			0,
																			D3DFMT_A8R8G8B8,
																			D3DPOOL_MANAGED,
																			&pD3DTex->m_pD3DTexture,
																			NULL ) ) ){
					throw MapilException( CURRENT_POSITION, TSTR( "Failed to create texture resources." ), -2 );
				}
			}

			::D3DLOCKED_RECT dstRect;
			if( FAILED( pD3DTex->m_pD3DTexture->LockRect( 0, &dstRect, NULL, D3DLOCK_DISCARD ) ) ){
				if( FAILED( pD3DTex->m_pD3DTexture->LockRect( 0, &dstRect, NULL, 0 ) ) ){
					throw MapilException( CURRENT_POSITION, TSTR( "Failed to lock rectangle of the destination texture." ), -3 );
				}
			}
			
			// Copy the source texture to the destination texture.
			DWORD* pDstPtr = static_cast < DWORD* > ( dstRect.pBits );
			DWORD* pSrcPtr = static_cast < DWORD* > ( srcRect.pBits );
			pSrcPtr += pBeginPosList[ i ].m_Y * srcRect.Pitch / sizeof( DWORD );
			for( MapilInt32 j = 0; j < pSizeList[ i ].m_Y; ++j ){
				for( MapilInt32 k = 0; k < pSizeList[ i ].m_X; ++k ){
					pDstPtr[ k ] = pSrcPtr[ k + pBeginPosList[ i ].m_X ];
				}
				// Pitch = width * DWORD (Color component.)
				pDstPtr += dstRect.Pitch / sizeof( DWORD );
				pSrcPtr += srcRect.Pitch / sizeof( DWORD );
			}
			pD3DTex->m_pD3DTexture->UnlockRect( 0 );
			pD3DTex->m_TexSize = pSizeList[ i ];
			pD3DTex->m_IsUsed = MapilTrue;
		}

		m_pD3DTexture->UnlockRect( 0 );

		SafeDeleteArray( pSizeList );
		SafeDeleteArray( pBeginPosList );
	}

	MapilInt32 D3DTexture::Get()
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DTexture" ),
				TSTR( "Get" ),
				TSTR( "The texture isn't created yet." ),
				-1 );
		if( m_SplitTotal == 0 ){
			return reinterpret_cast < MapilInt32 > ( m_pD3DTexture );
		}
		else{
			return reinterpret_cast < MapilInt32 > ( m_ppD3DTexture[ m_SplitIndex ] );
		}
	}

	Vector2 < MapilInt32 > D3DTexture::GetSize()
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DTexture" ),
				TSTR( "GetSize" ),
				TSTR( "The texture isn't created yet." ),
				-1 );

		if( m_SplitTotal == 0 ){
			return m_TexSize;
		}
		else{
			return m_pSizeList[ m_SplitIndex ];
		}
	}

}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D