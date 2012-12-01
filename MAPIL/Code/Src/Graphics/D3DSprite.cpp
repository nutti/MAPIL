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
#if ( DIRECT3D_VERSION == D3D_VER_9_0_C )

#include "../../Include/MAPIL/Graphics/D3DSprite.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

#include <list>

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{

	

	SpriteCore::SpriteCore( SharedPointer < GraphicsDevice > dev ) : m_ImgList(), m_Dev( dev ), m_Vertices()
	{
		m_ImgList.clear();
		m_Vertices.clear();
		m_Vertices.reserve( 2000 );

		D3DVERTEXELEMENT9 elements[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION, 0 },	//Position
			{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },	//Color
			{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //Texture coordinate
			D3DDECL_END()
		};

		// Create vertex declaration
		if( FAILED( m_Dev->GetDev().GetPointer()->CreateVertexDeclaration( elements, &m_pVertexDecl ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create vertex declaration." ), -1 );
		}
	}

	SpriteCore::~SpriteCore()
	{
		m_ImgList.clear();
		m_Vertices.clear();
	}

	MapilVoid SpriteCore::Begin()
	{
		m_ImgList.clear();
	}

	MapilVoid SpriteCore::End()
	{
		Flush();
	}

	MapilVoid SpriteCore::Commit( SharedPointer < Texture > texture, const ::D3DXMATRIXA16& worldMat )
	{
		ImageUnit unit = { worldMat };
		unit.m_WorldMat._42 = -unit.m_WorldMat._42;
		::LPDIRECT3DTEXTURE9 tex = reinterpret_cast < ::LPDIRECT3DTEXTURE9 > ( texture->Get() );
		m_ImgList[ tex ].m_Width = texture->GetSize().m_X;
		m_ImgList[ tex ].m_Height = texture->GetSize().m_Y;
		m_ImgList[ tex ].m_ImageUnits.push_back( unit );
	}

	MapilVoid SpriteCore::Flush()
	{
		// Save current environment.
		::D3DXMATRIXA16 origViewMat;
		::D3DXMATRIXA16 origProjMat;
		::DWORD origLighting;
		m_Dev->GetDev().GetPointer()->GetTransform( ::D3DTS_VIEW, &origViewMat );
		m_Dev->GetDev().GetPointer()->GetTransform( ::D3DTS_PROJECTION, &origProjMat );
		m_Dev->GetDev().GetPointer()->GetRenderState( ::D3DRS_LIGHTING, &origLighting );

		// Clear z-buffer.
		m_Dev->GetDev().GetPointer()->Clear( 0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 40, 40, 80 ), 1.0f, 0 );

		// Adopt transformation matrix for 2D rendering.
		m_WndWidth = 640;
		m_WndHeight = 480;
		::D3DXMATRIXA16 newViewMat;
		::D3DXMATRIXA16 newProjMat;
		::D3DXMatrixIdentity( &newViewMat );
		::D3DXMatrixIdentity( &newProjMat );
		newProjMat._11 = 2.0f / m_WndWidth;
		newProjMat._22 = 2.0f / m_WndHeight;
		m_Dev->GetDev().GetPointer()->SetTransform( ::D3DTS_VIEW, &newViewMat );
		m_Dev->GetDev().GetPointer()->SetTransform( ::D3DTS_PROJECTION, &newProjMat );

		m_Dev->GetDev().GetPointer()->SetVertexDeclaration( m_pVertexDecl );

		// Draw all registered textures.
		typedef std::map < ::LPDIRECT3DTEXTURE9, ImageChunk > ::iterator TextureIter;
		typedef std::list < ImageUnit > ::iterator UnitIter;
		
		MapilFloat32 offsetX = m_WndWidth / 2.0f;
		MapilFloat32 offsetY = m_WndHeight / 2.0f;
		for( TextureIter it = m_ImgList.begin(); it != m_ImgList.end(); ++it ){
			m_Dev->GetDev().GetPointer()->SetTexture( 0, it->first );
			MapilBool firstTime = MapilTrue;
			for( UnitIter uit = it->second.m_ImageUnits.begin(); uit != it->second.m_ImageUnits.end(); ++uit ){
				
				if( firstTime ){
					SpriteCore::VertexFormat fmt[ 5 ];
					fmt[ 0 ].m_Pos.x = -offsetX;
					fmt[ 0 ].m_Pos.y = offsetY;
					fmt[ 0 ].m_Pos.z = 0.1f;
					fmt[ 0 ].m_Color = 0xFFFFFFFF;
					fmt[ 0 ].m_TexCoord.x = 0.0f;
					fmt[ 0 ].m_TexCoord.y = 0.0f;
					fmt[ 1 ].m_Pos.x = -offsetX;
					fmt[ 1 ].m_Pos.y = offsetY - it->second.m_Height;
					fmt[ 1 ].m_Pos.z = 0.1f;
					fmt[ 1 ].m_Color = 0xFFFFFFFF;
					fmt[ 1 ].m_TexCoord.x = 0.0f;
					fmt[ 1 ].m_TexCoord.y = 1.0f;
					fmt[ 2 ].m_Pos.x = -offsetX + it->second.m_Width;
					fmt[ 2 ].m_Pos.y = offsetY;
					fmt[ 2 ].m_Pos.z = 0.1f;
					fmt[ 2 ].m_Color = 0xFFFFFFFF;
					fmt[ 2 ].m_TexCoord.x = 1.0f;
					fmt[ 2 ].m_TexCoord.y = 0.0f;
					fmt[ 3 ].m_Pos.x = -offsetX + it->second.m_Width;
					fmt[ 3 ].m_Pos.y = offsetY - it->second.m_Height;
					fmt[ 3 ].m_Pos.z = 0.1f;
					fmt[ 3 ].m_Color = 0xFFFFFFFF;
					fmt[ 3 ].m_TexCoord.x = 1.0f;
					fmt[ 3 ].m_TexCoord.y = 1.0f;
					fmt[ 4 ].m_Pos.x = -offsetX + it->second.m_Width;
					fmt[ 4 ].m_Pos.y = offsetY - it->second.m_Height;
					fmt[ 4 ].m_Pos.z = 0.1f;
					for( int i = 0; i < 5; ++i ){
						::D3DXVec3TransformCoord( &fmt[ i ].m_Pos, &fmt[ i ].m_Pos, &uit->m_WorldMat );
						m_Vertices.push_back( fmt[ i ] );
					}
					firstTime = MapilFalse;
				}
				else{
					SpriteCore::VertexFormat fmt[ 6 ];
					fmt[ 0 ].m_Pos.x = -offsetX;
					fmt[ 0 ].m_Pos.y = offsetY;
					fmt[ 0 ].m_Pos.z = 0.1f;
					fmt[ 1 ].m_Pos.x = -offsetX;
					fmt[ 1 ].m_Pos.y = offsetY;
					fmt[ 1 ].m_Pos.z = 0.1f;
					fmt[ 1 ].m_Color = 0xFFFFFFFF;
					fmt[ 1 ].m_TexCoord.x = 0.0f;
					fmt[ 1 ].m_TexCoord.y = 0.0f;
					fmt[ 2 ].m_Pos.x = -offsetX;
					fmt[ 2 ].m_Pos.y = offsetY - it->second.m_Height;
					fmt[ 2 ].m_Pos.z = 0.1f;
					fmt[ 2 ].m_Color = 0xFFFFFFFF;
					fmt[ 2 ].m_TexCoord.x = 0.0f;
					fmt[ 2 ].m_TexCoord.y = 1.0f;
					fmt[ 3 ].m_Pos.x = -offsetX + it->second.m_Width;
					fmt[ 3 ].m_Pos.y = offsetY;
					fmt[ 3 ].m_Pos.z = 0.1f;
					fmt[ 3 ].m_Color = 0xFFFFFFFF;
					fmt[ 3 ].m_TexCoord.x = 1.0f;
					fmt[ 3 ].m_TexCoord.y = 0.0f;
					fmt[ 4 ].m_Pos.x = -offsetX + it->second.m_Width;
					fmt[ 4 ].m_Pos.y = offsetY - it->second.m_Height;
					fmt[ 4 ].m_Pos.z = 0.1f;
					fmt[ 4 ].m_Color = 0xFFFFFFFF;
					fmt[ 4 ].m_TexCoord.x = 1.0f;
					fmt[ 4 ].m_TexCoord.y = 1.0f;
					fmt[ 5 ].m_Pos.x = -offsetX + it->second.m_Width;
					fmt[ 5 ].m_Pos.y = offsetY - it->second.m_Height;
					fmt[ 5 ].m_Pos.z = 0.1f;
					for( int i = 0; i < 6; ++i ){
						::D3DXVec3TransformCoord( &fmt[ i ].m_Pos, &fmt[ i ].m_Pos, &uit->m_WorldMat );
						m_Vertices.push_back( fmt[ i ] );
					}
				}
			}
			m_Dev->GetDev().GetPointer()->DrawPrimitiveUP(	::D3DPT_TRIANGLESTRIP,
															m_Vertices.size() - 3,
															&m_Vertices[ 0 ],
															sizeof( SpriteCore::VertexFormat ) );
			m_Vertices.clear();
		}

		// Restore previous environment.
		m_Dev->GetDev().GetPointer()->SetTransform( ::D3DTS_VIEW, &origViewMat );
		m_Dev->GetDev().GetPointer()->SetTransform( ::D3DTS_PROJECTION, &origProjMat );
		m_Dev->GetDev().GetPointer()->GetRenderState( ::D3DRS_LIGHTING, &origLighting );

		m_ImgList.clear();
	}


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

	MapilVoid D3DSprite::DrawTexture(	SharedPointer < Texture > pTexture,
										MapilFloat32 x, MapilFloat32 y,
										MapilBool centerize, MapilUInt32 color )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The sprite isn't created yet." ), -1 );

		D3DXMATRIXA16 matWorld;
		::D3DXMatrixIdentity( &matWorld );

		//World coordinate transformation
		if( centerize ){
			matWorld._41 = x - pTexture->GetSize().m_X / 2.0f;
			matWorld._42 = y - pTexture->GetSize().m_Y / 2.0f;
		}
		else{
			matWorld._41 = x;
			matWorld._42 = y;
		}
		m_pD3DSprite->SetTransform( &matWorld );

		// Set range of drawing.
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
										color ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to draw." ), -1 );
		}
	}

	MapilVoid D3DSprite::DrawScaledTexture(	SharedPointer < Texture > pTexture,
											MapilFloat32 x, MapilFloat32 y, MapilFloat32 sx, MapilFloat32 sy,
											MapilBool centerize, MapilUInt32 color )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The sprite isn't created yet." ), -1 );

		D3DXMATRIXA16 matWorld;
		::D3DXMatrixIdentity( &matWorld );

		//World coordinate transformation
		if( centerize ){
			//matWorld._11 = sx;
			//matWorld._11 = 
			matWorld._41 = x - pTexture->GetSize().m_X / 2.0f;
			matWorld._42 = y - pTexture->GetSize().m_Y / 2.0f;
		}
		else{
			matWorld._41 = x;
			matWorld._42 = y;
		}
		m_pD3DSprite->SetTransform( &matWorld );

		// Set range of drawing.
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
										color ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to draw." ), -1 );
		}
	}

	MapilVoid D3DSprite::DrawRotateTexture(	SharedPointer < Texture > pTexture,
											MapilFloat32 x, MapilFloat32 y, MapilFloat32 angle,
											MapilBool centerize, MapilUInt32 color )
	{
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

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D