/**
*	@file	D3DNSidedPolygon3D.cpp
*	@brief	
*	@date	2011.12.31 (Sat) 13:15
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "../../Include/MAPIL/Graphics/D3DNSidedPolygon3D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DNSidedPolygon3D::D3DNSidedPolygon3D( SharedPointer < GraphicsDevice > pDev ) :	NSidedPolygon3D( pDev ),
																						m_pVertex( NULL ),
																						m_pVertexDecl( NULL ),
																						m_IsUsed( MapilFalse ),
																						m_pTexture(),
																						m_pNonBufVertex( NULL ),
																						m_VertexManageMethod( VERTEX_MANAGEMENT_NONE )
	{
	}

	D3DNSidedPolygon3D::~D3DNSidedPolygon3D()
	{
		m_VertexManageMethod = VERTEX_MANAGEMENT_NONE;
		SafeDeleteArray( m_pNonBufVertex );
		SafeRelease( m_pVertexDecl );
		SafeRelease( m_pVertex );
		m_IsUsed = MapilFalse;
	}

	MapilVoid D3DNSidedPolygon3D::Create(	MapilInt32 vertexTotal, const NSidedPolygon3DVertexFmt fmt[],
											SharedPointer < Texture > pTex, VertexManagementMethod manageMethod )
	{
		m_pTexture = pTex;

		Create( vertexTotal, fmt, manageMethod );
	}

	MapilVoid D3DNSidedPolygon3D::Create(	MapilInt32 vertexTotal, const NSidedPolygon3DVertexFmt fmt[],
											VertexManagementMethod manageMethod )
	{
		m_VertexManageMethod = manageMethod;
		m_VertexTotal = vertexTotal;

		D3DVERTEXELEMENT9 elements[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION, 0 },	//Position
			{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },	//Color
			{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //Texture coordinate
			D3DDECL_END()
		};

		// Create vertex declaration
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexDeclaration( elements, &m_pVertexDecl ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DNSidedPolygon3D" ),
									TSTR( "Create" ),
									TSTR( "Failed to create vertex declaration." ),
									-1 );
		}

		if( m_VertexManageMethod == VERTEX_MANAGEMENT_NONE ){
			SafeDeleteArray( m_pNonBufVertex );
			m_pNonBufVertex = new VertexFormat [ m_VertexTotal ];
			for( MapilInt32 i = 0; i < m_VertexTotal; ++i ){
				m_pNonBufVertex[ i ].m_X		= fmt[ i ].m_Pos.m_X;
				m_pNonBufVertex[ i ].m_Y		= fmt[ i ].m_Pos.m_Y;
				m_pNonBufVertex[ i ].m_Z		= fmt[ i ].m_Pos.m_Z;
				m_pNonBufVertex[ i ].m_Col		= D3DCOLOR_ARGB( fmt[ i ].m_Col.m_A, fmt[ i ].m_Col.m_R, fmt[ i ].m_Col.m_G, fmt[ i ].m_Col.m_B );
				m_pNonBufVertex[ i ].m_U		= fmt[ i ].m_Tex.m_U;
				m_pNonBufVertex[ i ].m_V		= fmt[ i ].m_Tex.m_V;
			}
		}
		else if( m_VertexManageMethod == VERTEX_MANAGEMENT_BUFFER ){
			if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexBuffer(	sizeof( VertexFormat ) * 4,
																			0,
																			0,
																			D3DPOOL_MANAGED,
																			&m_pVertex,
																			NULL ) ) ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "D3DNSidedPolygon3D" ),
										TSTR( "Create" ),
										TSTR( "Failed to create vertex buffer." ),
										-2 );
			}

			// Write to vertex buffer
			VertexFormat* pBuf;
			if( m_pVertex->Lock( 0, 0, reinterpret_cast < LPVOID* > ( &pBuf ), 0 ) ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "D3DNSidedPolygon3D" ),
										TSTR( "Create" ),
										TSTR( "Failed to lock vertex buffer." ),
										-3 );
			}

			for( MapilInt32 i = 0; i < m_VertexTotal; ++i ){
				pBuf[ i ].m_X		= fmt[ i ].m_Pos.m_X;
				pBuf[ i ].m_Y		= fmt[ i ].m_Pos.m_Y;
				pBuf[ i ].m_Z		= fmt[ i ].m_Pos.m_Z;
				pBuf[ i ].m_Col		= D3DCOLOR_ARGB( fmt[ i ].m_Col.m_A, fmt[ i ].m_Col.m_R, fmt[ i ].m_Col.m_G, fmt[ i ].m_Col.m_B );
				pBuf[ i ].m_U		= fmt[ i ].m_Tex.m_U;
				pBuf[ i ].m_V		= fmt[ i ].m_Tex.m_V;
			}

			m_pVertex->Unlock();
		}
	}

	MapilVoid D3DNSidedPolygon3D::Update( MapilInt32 index, const NSidedPolygon3DVertexFmt& fmt )
	{
		// Write to vertex buffer
		VertexFormat* pBuf;
		if( m_pVertex->Lock( index * sizeof( VertexFormat ), sizeof( VertexFormat ), reinterpret_cast < LPVOID* > ( &pBuf ), 0 ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DRectangle3D" ),
									TSTR( "Update" ),
									TSTR( "Failed to lock vertex buffer." ),
									-1 );
		}
		pBuf[ index ].m_X		= fmt.m_Pos.m_X;
		pBuf[ index ].m_Y		= fmt.m_Pos.m_Y;
		pBuf[ index ].m_Z		= fmt.m_Pos.m_Z;
		pBuf[ index ].m_Col		= D3DCOLOR_ARGB( fmt.m_Col.m_A, fmt.m_Col.m_R, fmt.m_Col.m_G, fmt.m_Col.m_B );
		pBuf[ index ].m_U		= fmt.m_Tex.m_U;
		pBuf[ index ].m_V		= fmt.m_Tex.m_V;

		m_pVertex->Unlock();
	}

	MapilVoid D3DNSidedPolygon3D::Draw( MapilInt32 method, MapilInt32 count )
	{
		::D3DXMATRIX matWorld;
		::D3DXMatrixIdentity( &matWorld );
		m_pDev->GetDev().GetPointer()->SetTransform( D3DTS_WORLD, &matWorld );

		DrawVertex( method, count );
	}

	MapilVoid D3DNSidedPolygon3D::DrawVertex( MapilInt32 method, MapilInt32 count )
	{
		::D3DPRIMITIVETYPE primitive[] = {	::D3DPT_POINTLIST,
											::D3DPT_LINELIST,
											::D3DPT_LINESTRIP,
											::D3DPT_TRIANGLELIST,
											::D3DPT_TRIANGLESTRIP,
											::D3DPT_TRIANGLEFAN };

		if( m_pTexture.GetPointer() ){
			m_pDev->GetDev().GetPointer()->SetTexture( 0, reinterpret_cast < ::LPDIRECT3DTEXTURE9 > ( m_pTexture->Get() ) );
		}
		m_pDev->GetDev().GetPointer()->SetVertexDeclaration( m_pVertexDecl );
		if( m_VertexManageMethod == VERTEX_MANAGEMENT_NONE ){
			m_pDev->GetDev().GetPointer()->DrawPrimitiveUP( primitive[ method ], count, m_pNonBufVertex, sizeof( VertexFormat ) );
		}
		else if( m_VertexManageMethod == VERTEX_MANAGEMENT_BUFFER ){
			m_pDev->GetDev().GetPointer()->SetStreamSource( 0, m_pVertex, 0, sizeof( VertexFormat ) );
			m_pDev->GetDev().GetPointer()->DrawPrimitive( primitive[ method ], 0, count );
		}
	}
}

#endif	// API_DIRECT3D