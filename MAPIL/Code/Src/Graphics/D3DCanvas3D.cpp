/**
*	@file	D3DCanvas3D.cpp
*	@brief	Implementation of D3DCanvas3D.
*	@date	2012.8.16 (Thu) 10:03
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_9_0_C )

#include "../../Include/MAPIL/Graphics/D3DCanvas3D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DCanvas3D::D3DCanvas3D( SharedPointer < GraphicsDevice > pDev ) :	Canvas3D( pDev ),
																		m_pVertexDecl( NULL )
	{
	}
	
	D3DCanvas3D::~D3DCanvas3D()
	{
	}


	MapilVoid D3DCanvas3D::Create()
	{
		D3DVERTEXELEMENT9 elements[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION, 0 },	//Position
			{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },	//Color
			{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //Texture coordinate
			D3DDECL_END()
		};

		// Create vertex declaration
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexDeclaration( elements, &m_pVertexDecl ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create vertex declaration." ), -1 );
		}
	}

	MapilVoid D3DCanvas3D::Begin()
	{
	}

	MapilVoid D3DCanvas3D::End()
	{
	}

	MapilVoid D3DCanvas3D::DrawPolygon( const Polygon3DVertexFormat* pFmt, MapilInt32 polygonTotal )
	{
		m_pDev->GetDev().GetPointer()->SetVertexDeclaration( m_pVertexDecl );
		m_pDev->GetDev().GetPointer()->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP,
														polygonTotal,
														pFmt,
														sizeof( Polygon3DVertexFormat ) );
	}

	MapilVoid D3DCanvas3D::DrawPolygon(	const Polygon3DVertexFormat* pFmt,
										MapilInt32 polygonTotal,
										SharedPointer < Texture > texture )
	{
		if( texture.GetPointer() ){
			m_pDev->GetDev().GetPointer()->SetTexture( 0, reinterpret_cast < ::LPDIRECT3DTEXTURE9 > ( texture->Get() ) );
		}
		m_pDev->GetDev().GetPointer()->SetVertexDeclaration( m_pVertexDecl );
		m_pDev->GetDev().GetPointer()->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP,
														polygonTotal,
														pFmt,
														sizeof( Polygon3DVertexFormat ) );
	}
}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D