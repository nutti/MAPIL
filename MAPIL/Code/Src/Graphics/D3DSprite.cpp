/**
*	@file	D3DSprite.cpp
*	@brief	Implementation of D3DSprite.h.
*	@date	2011.6.15 (Wed) 18:34
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "../../Include/MAPIL/Graphics/D3DSprite.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DSprite::D3DSprite( SharedPointer < GraphicsDevice > pDev ) :	Sprite( pDev ),
																	m_pD3DSprite( NULL ),
																	m_IsUsed( MapilFalse )
	{
	}
	
	D3DSprite::~D3DSprite()
	{
		SafeRelease( m_pD3DSprite );
		m_IsUsed = MapilFalse;
	}

	MapilVoid D3DSprite::Create()
	{
		Assert(	!m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DSprite" ),
				TSTR( "Create" ),
				TSTR( "The sprite was already created." ),
				-1 );

		//Create sprite
		if( FAILED( D3DXCreateSprite( m_pDev->GetDev().GetPointer(), &m_pD3DSprite ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "Sprite" ),
									TSTR( "Create" ),
									TSTR( "Failed to create sprite." ),
									-1 );
		}

		m_IsUsed = MapilTrue;
	}

	MapilVoid D3DSprite::Begin()
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DSprite" ),
				TSTR( "Begin" ),
				TSTR( "The sprite isn't created yet." ),
				-1 );

		//Begin drawing sprite
	//	if( isAlphaBlendEnable ){
			m_pD3DSprite->Begin( D3DXSPRITE_ALPHABLEND );
	//	}
	//	else{
	//		m_pD3DSprite->Begin( 0 );
	//	}
	}

	MapilVoid D3DSprite::End()
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DSprite" ),
				TSTR( "End" ),
				TSTR( "The sprite isn't created yet." ),
				-1 );

		m_pD3DSprite->End();
	}

	// Draw texture.
	MapilVoid D3DSprite::DrawTexture(	SharedPointer < Texture > pTexture,
										const Matrix4x4 < MapilFloat32 >& mat )
	{
		DrawTexture( pTexture, mat, 0xFFFFFFFF );
	}

	MapilVoid D3DSprite::DrawTexture(	SharedPointer < Texture > pTexture,
										const Matrix4x4 < MapilFloat32 >& mat,
										MapilUInt32 color )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DSprite" ),
				TSTR( "DrawTexture" ),
				TSTR( "The sprite isn't created yet." ),
				-1 );

		D3DXMATRIXA16 matWorld;
		for( MapilInt32 i = 0; i < 4; ++i ){
			for( MapilInt32 j = 0; j < 4; ++j ){
				matWorld.m[ i ][ j ] = mat.m_Elm[ i ][ j ];
			}
		}

		//World coordinate transformation
		m_pD3DSprite->SetTransform( &matWorld );


		//Set range of drawing
		RECT rc;
		rc.top		= 0;
		rc.bottom	= pTexture->GetSize().m_Y;
		rc.left		= 0;
		rc.right	= pTexture->GetSize().m_X;

		//Draw
		if( FAILED( m_pD3DSprite->Draw(	reinterpret_cast < LPDIRECT3DTEXTURE9 > ( pTexture.GetPointer()->Get() ),
										&rc,
										NULL,
										NULL,
										color ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DSprite" ),
									TSTR( "DrawTexture" ),
									TSTR( "Failed to draw." ),
									-1 );
		}
	}

	// Draw texture.
	MapilVoid D3DSprite::DrawTexture(	SharedPointer < Texture > pTexture,
										ImageTransformationMethod method,
										const Vector2 < MapilFloat32 >& v )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DSprite" ),
				TSTR( "DrawTexture" ),
				TSTR( "The sprite isn't created yet." ),
				-1 );

		D3DXMATRIXA16 matWorld;

		switch( method ){
			case IMAGE_TRANSFORMATION_METHOD_MOVE:				//Move
				D3DXMatrixTranslation( &matWorld, v.m_X, v.m_Y, 0.0f );
				break;
			case IMAGE_TRANSFORMATION_METHOD_SCALE:			//Scale
				D3DXMatrixScaling( &matWorld, v.m_X, v.m_Y, 0.0f );
				break;
			case IMAGE_TRANSFORMATION_METHOD_CENTER_MOVE:		// Center - Move
			{
				D3DXMATRIXA16 matCenter;
				D3DXMatrixTranslation( &matCenter, - pTexture->GetSize().m_X / 2.0f, - pTexture->GetSize().m_Y / 2.0f, 0.0f );
				D3DXMatrixTranslation( &matWorld, v.m_X, v.m_Y, 0.0f );
				D3DXMatrixMultiply( &matWorld, &matWorld, &matCenter );
				matWorld *= matCenter;
				break;
			}
			case IMAGE_TRANSFORMATION_METHOD_CENTER_SCALE:		// Center - Scale
			{
				D3DXMATRIXA16 matCenter;
				D3DXMatrixTranslation( &matCenter, - pTexture->GetSize().m_X / 2.0f, - pTexture->GetSize().m_Y / 2.0f, 0.0f );
				D3DXMatrixScaling( &matWorld, v.m_X, v.m_Y, 0.0f );
				D3DXMatrixMultiply( &matWorld, &matWorld, &matCenter );
				matWorld *= matCenter;
				break;
			}
			default:
				break;
		}

		//World coordinate transformation
		m_pD3DSprite->SetTransform( &matWorld );

		// Set range of drawing.
		//RECT rc;
		RECT rc;
		rc.top		= 0;
		rc.bottom	= pTexture->GetSize().m_Y;
		rc.left		= 0;
		rc.right	= pTexture->GetSize().m_X;

		// Draw
		if( FAILED( m_pD3DSprite->Draw(	reinterpret_cast < LPDIRECT3DTEXTURE9 > ( pTexture.GetPointer()->Get() ),
										&rc,
										NULL,
										NULL,
										D3DCOLOR_ARGB( 255, 255, 255, 255 ) ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DSprite" ),
									TSTR( "DrawTexture" ),
									TSTR( "Failed to draw." ),
									-1 );
		}
	}

	MapilVoid D3DSprite::DrawString(	SharedPointer < GraphicsFont > pFont,
										const MapilTChar* pStr,
										ImageTransformationMethod method,
										const Vector2 < MapilFloat32 >& v,
										MapilUInt32 color )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DSprite" ),
				TSTR( "DrawString" ),
				TSTR( "The sprite isn't created yet." ),
				-1 );

		//World coordinate transformation
		D3DXMATRIXA16 matWorld;
		D3DXMatrixTranslation( &matWorld, v.m_X, v.m_Y, 0.0f );
		m_pD3DSprite->SetTransform( &matWorld );

		if( FAILED( reinterpret_cast < ::LPD3DXFONT > ( pFont->Get() )->DrawText(	m_pD3DSprite,
																					pStr,										//String
																					-1,											//Number of character (-1 mean that whole string will be drawn)
																					NULL,										//Region of drawing
																					DT_LEFT | DT_NOCLIP,						//Style
																					color ) ) ){		//Character color
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DSprite" ),
									TSTR( "DrawString" ),
									TSTR( "Failed to draw." ),
									-1 );
		}
	}

	MapilVoid D3DSprite::DrawString(	SharedPointer < GraphicsFont > pFont,
										const MapilTChar* pStr,
										const Matrix4x4 < MapilFloat32 >& mat )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DSprite" ),
				TSTR( "DrawString" ),
				TSTR( "The sprite isn't created yet." ),
				-1 );

		//World coordinate transformation
		D3DXMATRIXA16 matWorld;
		for( MapilInt32 i = 0; i < 4; ++i ){
			for( MapilInt32 j = 0; j < 4; ++j ){
				matWorld.m[ i ][ j ] = mat.m_Elm[ i ][ j ];
			}
		}
		m_pD3DSprite->SetTransform( &matWorld );

		if( FAILED( reinterpret_cast < ::LPD3DXFONT > ( pFont->Get() )->DrawText(	m_pD3DSprite,
																					pStr,										//String
																					-1,											//Number of character (-1 mean that whole string will be drawn)
																					NULL,										//Region of drawing
																					DT_LEFT | DT_NOCLIP,						//Style
																					D3DCOLOR_XRGB( 255, 255, 255 ) ) ) ){		//Character color
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DSprite" ),
									TSTR( "DrawString" ),
									TSTR( "Failed to draw." ),
									-1 );
		}
	}

	MapilVoid D3DSprite::LostResource()
	{
		if( m_pD3DSprite ){
			m_pD3DSprite->OnLostDevice();
		}
	}

	MapilVoid D3DSprite::RestoreResource()
	{
		if( m_pD3DSprite ){
			m_pD3DSprite->OnResetDevice();
		}
	}
}


#endif	// API_DIRECT3D