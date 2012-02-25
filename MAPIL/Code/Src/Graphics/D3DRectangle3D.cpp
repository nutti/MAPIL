/**
*	@file	D3DRectangle3D.cpp
*	@brief	Implementation of D3DRectangle3D.h.
*	@date	2011.8.25 (Thu) 20:51
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "../../Include/MAPIL/Graphics/D3DRectangle3D.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DRectangle3D::D3DRectangle3D( SharedPointer < GraphicsDevice > pDev ) :	Rectangle3D( pDev ),
																				m_pVertex( NULL ),
																				m_pVertexDecl( NULL ),
																				m_IsUsed( MapilFalse ),
																				m_pTexture(),
																				m_pNonBufVertex( NULL ),
																				m_VertexManageMethod( VERTEX_MANAGEMENT_NONE )
	{
	}

	D3DRectangle3D::~D3DRectangle3D()
	{
		m_VertexManageMethod = VERTEX_MANAGEMENT_NONE;
		SafeDeleteArray( m_pNonBufVertex );
		SafeRelease( m_pVertexDecl );
		SafeRelease( m_pVertex );
		m_IsUsed = MapilFalse;
	}

	MapilVoid D3DRectangle3D::Create(	const Rectangle3DVertexFormat& fmt,
										SharedPointer < Texture > pTex,
										VertexManagementMethod manageMethod )
	{
		m_pTexture = pTex;

		Create( fmt, manageMethod );
	}

	MapilVoid D3DRectangle3D::Create(	const Rectangle3DVertexFormat& fmt,
										VertexManagementMethod manageMethod )
	{
		m_VertexManageMethod = manageMethod;

		D3DVERTEXELEMENT9 elements[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION, 0 },	//Position
			{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },	//Color
			{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //Texture coordinate
			D3DDECL_END()
		};

		// Create vertex declaration
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexDeclaration( elements, &m_pVertexDecl ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DRectangle3D" ),
									TSTR( "Create" ),
									TSTR( "Failed to create vertex declaration." ),
									-1 );
		}

		if( m_VertexManageMethod == VERTEX_MANAGEMENT_NONE ){
			SafeDeleteArray( m_pNonBufVertex );
			m_pNonBufVertex = new VertexFormat [ 4 ];
			for( MapilInt32 i = 0; i < 4; ++i ){
				m_pNonBufVertex[ i ].m_X		= fmt.m_Pos[ i ].m_X;
				m_pNonBufVertex[ i ].m_Y		= fmt.m_Pos[ i ].m_Y;
				m_pNonBufVertex[ i ].m_Z		= fmt.m_Pos[ i ].m_Z;
				m_pNonBufVertex[ i ].m_Col		= D3DCOLOR_ARGB( fmt.m_Col[ i ].m_A, fmt.m_Col[ i ].m_R, fmt.m_Col[ i ].m_G, fmt.m_Col[ i ].m_B );
				m_pNonBufVertex[ i ].m_U		= fmt.m_Tex[ i ].m_U;
				m_pNonBufVertex[ i ].m_V		= fmt.m_Tex[ i ].m_V;
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
										TSTR( "D3DRectangle3D" ),
										TSTR( "Create" ),
										TSTR( "Failed to create vertex buffer." ),
										-2 );
			}

			// Write to vertex buffer
			VertexFormat* pBuf;
			if( m_pVertex->Lock( 0, 0, reinterpret_cast < LPVOID* > ( &pBuf ), 0 ) ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "D3DRectangle3D" ),
										TSTR( "Create" ),
										TSTR( "Failed to lock vertex buffer." ),
										-3 );
			}

			for( MapilInt32 i = 0; i < 4; ++i ){
				pBuf[ i ].m_X		= fmt.m_Pos[ i ].m_X;
				pBuf[ i ].m_Y		= fmt.m_Pos[ i ].m_Y;
				pBuf[ i ].m_Z		= fmt.m_Pos[ i ].m_Z;
				pBuf[ i ].m_Col		= D3DCOLOR_ARGB( fmt.m_Col[ i ].m_A, fmt.m_Col[ i ].m_R, fmt.m_Col[ i ].m_G, fmt.m_Col[ i ].m_B );
				pBuf[ i ].m_U		= fmt.m_Tex[ i ].m_U;
				pBuf[ i ].m_V		= fmt.m_Tex[ i ].m_V;
			}

			m_pVertex->Unlock();
		}
	}

	MapilVoid D3DRectangle3D::Update(	const Rectangle3DVertexFormat& fmt,
										SharedPointer < Texture > pTex )
	{
		// Write to vertex buffer
		VertexFormat* pBuf;
		if( m_pVertex->Lock( 0, 0, reinterpret_cast < LPVOID* > ( &pBuf ), 0 ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DRectangle3D" ),
									TSTR( "Update" ),
									TSTR( "Failed to lock vertex buffer." ),
									-1 );
		}

		for( MapilInt32 i = 0; i < 4; ++i ){
			pBuf[ i ].m_X		= fmt.m_Pos[ i ].m_X;
			pBuf[ i ].m_Y		= fmt.m_Pos[ i ].m_Y;
			pBuf[ i ].m_Z		= fmt.m_Pos[ i ].m_Z;
			pBuf[ i ].m_Col		= D3DCOLOR_ARGB( fmt.m_Col[ i ].m_A, fmt.m_Col[ i ].m_R, fmt.m_Col[ i ].m_G, fmt.m_Col[ i ].m_B );
			pBuf[ i ].m_U		= fmt.m_Tex[ i ].m_U;
			pBuf[ i ].m_V		= fmt.m_Tex[ i ].m_V;
		}

		m_pVertex->Unlock();
	}

	MapilVoid D3DRectangle3D::Update( const Rectangle3DVertexFormat& fmt )
	{
		// Write to vertex buffer
		VertexFormat* pBuf;
		if( m_pVertex->Lock( 0, 0, reinterpret_cast < LPVOID* > ( &pBuf ), 0 ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DRectangle3D" ),
									TSTR( "Update" ),
									TSTR( "Failed to lock vertex buffer." ),
									-1 );
		}

		for( MapilInt32 i = 0; i < 4; ++i ){
			pBuf[ i ].m_X		= fmt.m_Pos[ i ].m_X;
			pBuf[ i ].m_Y		= fmt.m_Pos[ i ].m_Y;
			pBuf[ i ].m_Z		= fmt.m_Pos[ i ].m_Z;
			pBuf[ i ].m_Col		= D3DCOLOR_ARGB( fmt.m_Col[ i ].m_A, fmt.m_Col[ i ].m_R, fmt.m_Col[ i ].m_G, fmt.m_Col[ i ].m_B );
			pBuf[ i ].m_U		= fmt.m_Tex[ i ].m_U;
			pBuf[ i ].m_V		= fmt.m_Tex[ i ].m_V;
		}

		m_pVertex->Unlock();
	}

	MapilVoid D3DRectangle3D::Draw()
	{
		::D3DXMATRIX matWorld;
		::D3DXMatrixIdentity( &matWorld );
		m_pDev->GetDev().GetPointer()->SetTransform( D3DTS_WORLD, &matWorld );

		DrawVertex();
	}

	MapilVoid D3DRectangle3D::Draw( const Matrix4x4 < MapilFloat32 >& mat )
	{
		::D3DXMATRIX matWorld;
		for( int colmun = 0; colmun < 4; ++colmun ){
			for( int row = 0; row < 4; ++row ){
				matWorld.m[ colmun ][ row ] = mat.m_Elm[ colmun ][ row ];
			}
		}
		m_pDev->GetDev().GetPointer()->SetTransform( D3DTS_WORLD, &matWorld );

		DrawVertex();
	}

	MapilVoid D3DRectangle3D::DrawVertex()
	{
		if( m_pTexture.GetPointer() ){
			m_pDev->GetDev().GetPointer()->SetTexture( 0, reinterpret_cast < ::LPDIRECT3DTEXTURE9 > ( m_pTexture->Get() ) );
		}
		m_pDev->GetDev().GetPointer()->SetVertexDeclaration( m_pVertexDecl );
		if( m_VertexManageMethod == VERTEX_MANAGEMENT_NONE ){
			m_pDev->GetDev().GetPointer()->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, m_pNonBufVertex, sizeof( VertexFormat ) );
		}
		else if( m_VertexManageMethod == VERTEX_MANAGEMENT_BUFFER ){
			m_pDev->GetDev().GetPointer()->SetStreamSource( 0, m_pVertex, 0, sizeof( VertexFormat ) );
			m_pDev->GetDev().GetPointer()->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		}
	}
}

#endif	// API_DIRECT3D