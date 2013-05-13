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

	

	SpriteCore::SpriteCore( SharedPointer < GraphicsDevice > dev ) : m_DrawList(), m_Dev( dev )
	{
		m_DrawList.clear();

		// Create common vertex buffer.
		MapilFloat32 vertex[] = {	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,	// v0
									1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	// v1
									0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// v2
									1.0f, 1.0f, 0.0f, 1.0f, 1.0f };	// v3
		if( FAILED( m_Dev->GetDev().GetPointer()->CreateVertexBuffer(	sizeof( vertex ),
																		0, 0, ::D3DPOOL_MANAGED,
																		&m_pVertexBuf, 0 ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create vertex buffer." ), -1 );
		}
		MapilFloat32* p = 0;
		m_pVertexBuf->Lock( 0, 0, reinterpret_cast < MapilVoid** > ( &p ), 0 );
		::memcpy( p, vertex, sizeof( vertex ) );
		m_pVertexBuf->Unlock();

		// Create shader.
		::ID3DXBuffer* pError = NULL;
		if( FAILED( ::D3DXCreateEffectFromFile( m_Dev->GetDev().GetPointer(), TSTR( "sprite.fx" ), 0, 0, 0, 0, &m_pEffect, &pError ) ) ){
			OutputDebugStringA( ( const MapilChar* ) ( pError->GetBufferPointer() ) );
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create shader." ), -1 );
		}

		// Create vertex declaration.
		::D3DVERTEXELEMENT9 elements[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	// Position.
			{ 0, sizeof( MapilFloat32 ) * 3, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// Texture coordinate.
			D3DDECL_END()
		};
		if( FAILED( m_Dev->GetDev().GetPointer()->CreateVertexDeclaration( elements, &m_pVertexDecl ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create vertex declaration." ), -1 );
		}

		m_WndWidth = 640.0f;
		m_WndHeight = 480.0f;
	}

	SpriteCore::~SpriteCore()
	{
		m_DrawList.clear();
		SafeRelease( m_pVertexBuf );
		SafeRelease( m_pEffect );
		SafeRelease( m_pVertexDecl );
	}

	MapilVoid SpriteCore::Begin()
	{
	}

	MapilVoid SpriteCore::End()
	{
		Flush();
		m_DrawList.clear();
	}

	MapilVoid SpriteCore::Commit( SharedPointer < Texture > texture, const ::D3DXMATRIX& worldMat )
	{
		SpriteData sprite = { worldMat, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
		::LPDIRECT3DTEXTURE9 tex = reinterpret_cast < ::LPDIRECT3DTEXTURE9 > ( texture->Get() );
		m_DrawList[ tex ].push_back( sprite );
	}

	MapilVoid SpriteCore::Flush()
	{
		// Set vertex buffer and vertex declaration.
		m_Dev->GetDev().GetPointer()->SetStreamSource( 0, m_pVertexBuf, 0, sizeof( MapilFloat32 ) * 5 );
		m_Dev->GetDev().GetPointer()->SetVertexDeclaration( m_pVertexDecl );

		// Create projection matrix.
		::D3DXMATRIX projMat;
		::D3DXMatrixIdentity( &projMat );
		// Left-top coord is (0,0).
		projMat._41 = -1.0f;
		projMat._42 = 1.0f;
		// Pseudo-screen transformation.
		projMat._11 = 2.0f / m_WndWidth;
		projMat._22 = -2.0f / m_WndHeight;

		// Configure shader.
		::UINT passTotal = 0;
		m_pEffect->SetTechnique( "Tech" );
		m_pEffect->Begin( &passTotal, 0 );
		m_pEffect->BeginPass( 0 );

		// Draw all registered sprite.
		DrawSpriteList::iterator itTex = m_DrawList.begin();
		for( ; itTex != m_DrawList.end(); ++itTex ){
			m_pEffect->SetTexture( "tex", itTex->first );
			m_pEffect->SetMatrix( "proj", &projMat );
			typedef std::vector < SpriteData >	SpriteList;
			SpriteList::iterator it = itTex->second.begin();
			for( ; it != itTex->second.end(); ++it ){
				// Setup shader parameter.
				::D3DXMATRIX world;
				::D3DXMatrixScaling( &world, 128.0f, 128.0f, 1.0f );
				world = world * it->m_TransMat;
				m_pEffect->SetMatrix( "world", &world );
				m_pEffect->SetFloat( "uv_left", it->m_UVLeft );
				m_pEffect->SetFloat( "uv_top", it->m_UVTop );
				m_pEffect->SetFloat( "uv_width", it->m_UVHeight );
				m_pEffect->SetFloat( "uv_height", it->m_UVHeight );
				m_pEffect->SetFloat( "alpha", it->m_Alpha );
				// Change notification of shader parameter.
				m_pEffect->CommitChanges();
				m_Dev->GetDev().GetPointer()->DrawPrimitive( ::D3DPT_TRIANGLESTRIP, 0, 2 );
			}
		}
		
		m_pEffect->EndPass();
		m_pEffect->End();
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

	MapilVoid D3DSprite::Create( SharedPointer < GraphicsController > pCtrl )
	{
		Assert(	!m_IsUsed, CURRENT_POSITION, TSTR( "The sprite was already created." ), -1 );

		//Create sprite
		if( FAILED( D3DXCreateSprite( m_pDev->GetDev().GetPointer(), &m_pD3DSprite ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create sprite." ), -1 );
		}

		m_pGraphicsCtrl = pCtrl;

		m_IsUsed = MapilTrue;
	}

	MapilVoid D3DSprite::Begin()
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The sprite isn't created yet." ), -1 );

		m_PrevAlphaBlendMode = m_pGraphicsCtrl->GetAlphaBlendMode();

		m_pD3DSprite->Begin( D3DXSPRITE_ALPHABLEND );

		m_pGraphicsCtrl->SetAlphaBlendMode( ALPHA_BLEND_MODE_SEMI_TRANSPARENT );
	}

	MapilVoid D3DSprite::End()
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The sprite isn't created yet." ), -1 );

		m_pD3DSprite->End();

		m_pGraphicsCtrl->SetAlphaBlendMode( m_PrevAlphaBlendMode );
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
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The sprite isn't created yet." ), -1 );

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
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to draw." ), -1 );
		}
	}

	// Draw texture.
	MapilVoid D3DSprite::DrawTexture(	SharedPointer < Texture > pTexture,
										ImageTransformationMethod method,
										const Vector2 < MapilFloat32 >& v )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The sprite isn't created yet." ), -1 );

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
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to draw." ), -1 );
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

	MapilVoid D3DSprite::DrawClipedTexture(	SharedPointer < Texture > pTexture,
											MapilFloat32 x, MapilFloat32 y,
											MapilFloat32 texCoordX, MapilFloat32 texCoordY,
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
		rc.bottom	= static_cast < MapilInt32 > ( texCoordY * pTexture->GetSize().m_Y );
		rc.left		= 0;
		rc.right	= static_cast < MapilInt32 > ( texCoordX * pTexture->GetSize().m_X );

		// Draw
		if( FAILED( m_pD3DSprite->Draw(	reinterpret_cast < LPDIRECT3DTEXTURE9 > ( pTexture.GetPointer()->Get() ),
										&rc,
										NULL,
										NULL,
										color ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to draw." ), -1 );
		}
	}

	MapilVoid D3DSprite::DrawClipedTexture(	SharedPointer < Texture > pTexture,
											MapilFloat32 x, MapilFloat32 y,
											MapilFloat32 sx, MapilFloat32 sy,
											MapilFloat32 angle,
											MapilFloat32 cx1, MapilFloat32 cy1,
											MapilFloat32 cx2, MapilFloat32 cy2,
											MapilBool centerize, MapilUInt32 color )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The sprite isn't created yet." ), -1 );

		MapilFloat32 width = cx2 - cx1;
		MapilFloat32 height = cy2 - cy1;

		D3DXMATRIXA16 matWorld;
		::D3DXMatrixIdentity( &matWorld );

		::D3DXMATRIXA16 trans;
		::D3DXMATRIXA16 scale;
		::D3DXMATRIXA16 rot;
		::D3DXMATRIXA16 offset;

		::D3DXMatrixIdentity( &trans );
		::D3DXMatrixIdentity( &scale );
		::D3DXMatrixIdentity( &rot );

		// World coordinate transformation
		if( centerize ){
			::D3DXMatrixIdentity( &offset );
			offset._41 = - width / 2.0f;
			offset._42 = - height / 2.0f;
		}
		trans._41 = x;
		trans._42 = y;
		scale._11 = sx;
		scale._22 = sy;
		::D3DXMatrixRotationZ( &rot, angle );

		matWorld = offset * scale * rot * trans;	// Centering -> Scaling -> Rotation -> Translation.

		m_pD3DSprite->SetTransform( &matWorld );

		// Set range of drawing.
		RECT rc;
		rc.top		= static_cast < MapilInt32 > ( cy1 );
		rc.bottom	= static_cast < MapilInt32 > ( cy2 );
		rc.left		= static_cast < MapilInt32 > ( cx1 );
		rc.right	= static_cast < MapilInt32 > ( cx2 );

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

	MapilVoid D3DSprite::SetAlphaBlendMode( MapilInt32 mode )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The sprite isn't created yet." ), -1 );

		if( mode != m_pGraphicsCtrl->GetAlphaBlendMode() ){
			m_pD3DSprite->End();
			m_pD3DSprite->Begin( D3DXSPRITE_ALPHABLEND );
			m_pGraphicsCtrl->SetAlphaBlendMode( mode );
		}
	}

	MapilVoid D3DSprite::DrawString(	SharedPointer < GraphicsFont > pFont,
										const MapilTChar* pStr,
										ImageTransformationMethod method,
										const Vector2 < MapilFloat32 >& v,
										MapilUInt32 color )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The sprite isn't created yet." ), -1 );

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
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to draw." ), -1 );
		}
	}

	MapilVoid D3DSprite::DrawString(	SharedPointer < GraphicsFont > pFont,
										const MapilTChar* pStr,
										const Matrix4x4 < MapilFloat32 >& mat )
	{
		Assert( m_IsUsed, CURRENT_POSITION, TSTR( "The sprite isn't created yet." ), -1 );

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
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to draw." ), -1 );
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