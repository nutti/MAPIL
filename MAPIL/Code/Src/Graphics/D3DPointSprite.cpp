/**
*	@file	D3DPointSprite.cpp
*	@brief	Implementation of D3DPointSprite.h
*	@date	2011.8.31 (Wed) 8:17
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "../../Include/MAPIL/Graphics/D3DPointSprite.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Math/Transformation.hpp"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DPointSprite::D3DPointSprite( SharedPointer < GraphicsDevice > pDev ) :	PointSprite( pDev ),
																				m_pVertexBuf( NULL ),
																				m_pVertexDecl( NULL ),
																				m_NumVertex( 0 ),
																				m_pTex(),
																				m_pNonBufVertex( NULL ),
																				m_VertexManageMethod( VERTEX_MANAGEMENT_NONE )
						
	{
	}

	D3DPointSprite::~D3DPointSprite()
	{
		m_VertexManageMethod = VERTEX_MANAGEMENT_NONE;
		SafeDeleteArray( m_pNonBufVertex );
		m_NumVertex = 0;
		SafeRelease( m_pVertexDecl );
		SafeRelease( m_pVertexBuf );
	}

	MapilVoid D3DPointSprite::Create(	MapilInt32 numVertex, SharedPointer < Texture > pTex,
										VertexManagementMethod manageMethod )
	{
		m_pTex = pTex;
		m_NumVertex = numVertex;
		m_VertexManageMethod = manageMethod;

		//Vertex elements of mesh
		D3DVERTEXELEMENT9 vertexElements[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION, 0 },	//Position
			{ 0, 12, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0 },	//PSize
			{ 0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },	//Color
			{ 0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //Texture coordinate
			D3DDECL_END()
		};

		//Create vertex declaration
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexDeclaration( vertexElements, &m_pVertexDecl ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DPointSprite" ),
									TSTR( "Create" ),
									TSTR( "Failed to create vertex declaration" ),
									-1 );
		}

		if( m_VertexManageMethod == VERTEX_MANAGEMENT_NONE ){
			SafeDeleteArray( m_pNonBufVertex );
			m_pNonBufVertex = new VertexFormat [ m_NumVertex ];
			ZeroObject( m_pNonBufVertex, sizeof( VertexFormat ) * m_NumVertex );
		}
		else if( m_VertexManageMethod == VERTEX_MANAGEMENT_BUFFER ){
			if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexBuffer(	sizeof( VertexFormat ) * m_NumVertex,		// Multiply size of vertex and number of vertex
																			0,											// Usage
																			0,											// Non-FVF vertex buffer
																			D3DPOOL_MANAGED,							// Memory is managed by Direct 3D
																			&m_pVertexBuf,								// Vertex buffer
																			NULL ) ) ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "D3DPointSprite" ),
										TSTR( "Create" ),
										TSTR( "Failed to create vertex buffer" ),
										-1 );
			}
		}
	}

	MapilVoid D3DPointSprite::Create(	MapilInt32 numVertex,
										VertexManagementMethod manageMethod )
	{
		m_NumVertex = numVertex;

		//Vertex elements of mesh
		D3DVERTEXELEMENT9 vertexElements[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION, 0 },	//Position
			{ 0, 12, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0 },	//PSize
			{ 0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },	//Color
			{ 0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //Texture coordinate
			D3DDECL_END()
		};

		//Create vertex declaration
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexDeclaration( vertexElements, &m_pVertexDecl ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DPointSprite" ),
									TSTR( "Create" ),
									TSTR( "Failed to create vertex declaration" ),
									-1 );
		}

		if( m_VertexManageMethod == VERTEX_MANAGEMENT_NONE ){
			SafeDeleteArray( m_pNonBufVertex );
			m_pNonBufVertex = new VertexFormat [ m_NumVertex ];
			ZeroObject( m_pNonBufVertex, sizeof( VertexFormat ) * m_NumVertex );
		}
		else if( m_VertexManageMethod == VERTEX_MANAGEMENT_BUFFER ){
			if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexBuffer(	sizeof( VertexFormat ) * m_NumVertex,		//Multiply size of vertex and number of vertex
																			0,											//Usage
																			0,											//Non-FVF vertex buffer
																			D3DPOOL_MANAGED,							//Memory is managed by Direct 3D
																			&m_pVertexBuf,								//Vertex buffer
																			NULL ) ) ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "D3DPointSprite" ),
										TSTR( "Create" ),
										TSTR( "Failed to create vertex buffer" ),
										-1 );
			}
		}
	}

	MapilVoid D3DPointSprite::Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
										MapilFloat32 size, MapilUInt32 color )
	{
		if( m_VertexManageMethod == VERTEX_MANAGEMENT_NONE ){
			m_pNonBufVertex[ index ].m_X = vPos.m_X;
			m_pNonBufVertex[ index ].m_Y = vPos.m_Y;
			m_pNonBufVertex[ index ].m_Z = vPos.m_Z;
			m_pNonBufVertex[ index ].m_PSize = size;
			m_pNonBufVertex[ index ].m_Col = color;
		}
		else if( m_VertexManageMethod == VERTEX_MANAGEMENT_BUFFER ){
			VertexFormat* pVertexBuf;

			if( FAILED( m_pVertexBuf->Lock( sizeof( VertexFormat ) * index,
											sizeof( VertexFormat ),
											reinterpret_cast < MapilVoid** > ( &pVertexBuf ),
											D3DLOCK_DISCARD ) ) ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "D3DPointSprite" ),
										TSTR( "Move" ),
										TSTR( "Failed to lock vertex buffer." ),
										-2 );
			}

			pVertexBuf->m_X = vPos.m_X;
			pVertexBuf->m_Y = vPos.m_Y;
			pVertexBuf->m_Z = vPos.m_Z;
			pVertexBuf->m_PSize = size;
			pVertexBuf->m_Col = color;

			m_pVertexBuf->Unlock();
		}
	}

	MapilVoid D3DPointSprite::Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
										MapilFloat32 size, const ColorARGB < MapilFloat32 >& color )
	{
		if( index >= m_NumVertex || index < 0 ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DPointSprite" ),
									TSTR( "Move" ),
									TSTR( "Bad index value was substituted." ),
									-1 );
		}

		MapilInt32 colorVal = D3DCOLOR_ARGB(	static_cast < MapilInt32 > ( color.m_A * 255 ),
												static_cast < MapilInt32 > ( color.m_R * 255 ),
												static_cast < MapilInt32 > ( color.m_G * 255 ),
												static_cast < MapilInt32 > ( color.m_B * 255 ) );

		Update( index, vPos, size, colorVal );
	}

	MapilVoid D3DPointSprite::Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
										MapilFloat32 size, const ColorARGB < MapilUChar >& color )
	{
		Assert( index < m_NumVertex || index >= 0, CURRENT_POSITION, TSTR( "Bad index value was substituted." ), -1 );

		MapilInt32 colorVal = D3DCOLOR_ARGB( color.m_A, color.m_R, color.m_G, color.m_B );

		Update( index, vPos, size, colorVal );
	}

	MapilVoid D3DPointSprite::Draw()
	{
		// Disable alpha blending.
		DWORD blendingStatus;
		m_pDev->GetDev().GetPointer()->GetRenderState( ::D3DRS_ALPHABLENDENABLE, &blendingStatus );
		m_pDev->GetDev().GetPointer()->SetRenderState( ::D3DRS_ALPHABLENDENABLE, TRUE );

		// If this procedure isn't here, privious operation remains.
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity( &matWorld );
		m_pDev->GetDev().GetPointer()->SetTransform( D3DTS_WORLD, &matWorld );

		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_POINTSPRITEENABLE, TRUE );		//Enable point sprite
		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_POINTSCALEENABLE, TRUE );		//Enable point scale

		//Minimum size of point
		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_POINTSIZE_MIN, TransformFloatIntoDWORD( 0.00f ) );

		//Scale coefficient of point
		//m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_POINTSIZE, TransformFloatIntoDWORD( 0.25f ) );
		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_POINTSCALE_A, TransformFloatIntoDWORD( 0.00f ) );
		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_POINTSCALE_B, TransformFloatIntoDWORD( 0.00f ) );
		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_POINTSCALE_C, TransformFloatIntoDWORD( 1.00f ) );

		if( m_pTex.GetPointer() ){
			m_pDev->GetDev().GetPointer()->SetTexture( 0, reinterpret_cast < LPDIRECT3DTEXTURE9 > (  m_pTex->Get() ) );
		}

		m_pDev->GetDev().GetPointer()->SetVertexDeclaration( m_pVertexDecl );

		if( m_VertexManageMethod == VERTEX_MANAGEMENT_NONE ){
			m_pDev->GetDev().GetPointer()->DrawPrimitiveUP( D3DPT_POINTLIST, m_NumVertex, m_pNonBufVertex, sizeof( VertexFormat ) );
		}
		else if( m_VertexManageMethod == VERTEX_MANAGEMENT_BUFFER ){
			m_pDev->GetDev().GetPointer()->SetStreamSource( 0, m_pVertexBuf, 0, sizeof( VertexFormat ) );
			m_pDev->GetDev().GetPointer()->DrawPrimitive( D3DPT_POINTLIST, 0, m_NumVertex );
		}

		m_pDev->GetDev().GetPointer()->SetTexture( 0, NULL );

		//Release of point sprite
		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_POINTSIZE, TransformFloatIntoDWORD( 1.00f ) );
		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE );
		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_POINTSCALEENABLE, FALSE );

		// Restore alpha blending status.
		m_pDev->GetDev().GetPointer()->SetRenderState( ::D3DRS_ALPHABLENDENABLE, blendingStatus );
	}

}

#endif	// API_DIRECT3D