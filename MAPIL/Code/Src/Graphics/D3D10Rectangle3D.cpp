/**
*	@file	D3D10Rectangle3D.cpp
*	@brief	Implementation of D3D10Rectangle3D.h.
*	@date	2012.10.6 (Sat) 21:26
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_10_0 )

#include "../../Include/MAPIL/Graphics/D3D10Rectangle3D.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3D10Rectangle3D::D3D10Rectangle3D( SharedPointer < GraphicsDevice > pDev ) :	Rectangle3D( pDev ),
																					m_IsUsed( MapilFalse ),
																					m_pTexture(),
																					m_pBuffer( NULL )
	{
	}

	D3D10Rectangle3D::~D3D10Rectangle3D()
	{
		m_IsUsed = MapilFalse;
	}

	MapilVoid D3D10Rectangle3D::Create(	const Rectangle3DVertexFormat& fmt,
										SharedPointer < Texture > pTex,
										VertexManagementMethod manageMethod )
	{
		m_pTexture = pTex;

		Create( fmt, manageMethod );
	}

	MapilVoid D3D10Rectangle3D::Create(	const Rectangle3DVertexFormat& fmt,
										SharedPointer < Texture > pTex,
										const MapilTChar* pShaderFileName, const MapilChar* pTechName,
										VertexManagementMethod manageMethod )
	{
		Create( fmt, pTex, manageMethod );

		::ID3D10InputLayout* pLayout;
		::ID3D10Effect* pEffect;
		::ID3D10Blob* pBlob;

		if( FAILED( ::D3DX10CreateEffectFromFile(	pShaderFileName,
													0,
													0,
													"fx_4_0",
													D3D10_SHADER_ENABLE_STRICTNESS,
													0,
													m_pDev->GetDev().GetPointer(),
													0,
													0,
													&pEffect,
													&pBlob,
													0 ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create effect from file." ), -1 );
		}

		m_pEffectTech = pEffect->GetTechniqueByName( pTechName );
		m_pEffectTech->GetPassByIndex( 0 )->GetDesc( &m_PassDesc );
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateInputLayout(	m_ElmDesc, sizeof( m_ElmDesc ) / sizeof( ::D3D10_INPUT_ELEMENT_DESC ),
																		m_PassDesc.pIAInputSignature, m_PassDesc.IAInputSignatureSize, &pLayout ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create input layout." ), -1 );
		}
		m_pDev->GetDev().GetPointer()->IASetInputLayout( pLayout );

	}

	MapilVoid D3D10Rectangle3D::Create(	const Rectangle3DVertexFormat& fmt,
										VertexManagementMethod manageMethod )
	{
		// Set up vertices.
		for( int i = 0; i < 4; ++i ){
			m_VertexFmt[ i ].m_Pos.x = fmt.m_Pos[ i ].m_X;
			m_VertexFmt[ i ].m_Pos.y = fmt.m_Pos[ i ].m_Y;
			m_VertexFmt[ i ].m_Pos.z = fmt.m_Pos[ i ].m_Z;
			m_VertexFmt[ i ].m_Color.x = fmt.m_Col[ i ].m_R;
			m_VertexFmt[ i ].m_Color.y = fmt.m_Col[ i ].m_G;
			m_VertexFmt[ i ].m_Color.z = fmt.m_Col[ i ].m_B;
		}

		// Vertex information.
		::D3D10_INPUT_ELEMENT_DESC elmDesc[] = {
			{ "POSITION_IN", 0, ::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, ::D3D10_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR_IN", 0, ::DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof( ::D3DXVECTOR3 ), ::D3D10_INPUT_PER_VERTEX_DATA, 0 },
		};
		::memcpy( m_ElmDesc, elmDesc, sizeof( m_ElmDesc ) );

		// Create vertex buffer.
		::D3D10_BUFFER_DESC bufferDesc = { 4 * sizeof( VertexFormat ), ::D3D10_USAGE_DEFAULT, ::D3D10_BIND_VERTEX_BUFFER, 0, 0 };
		::D3D10_SUBRESOURCE_DATA subrcData;
		subrcData.pSysMem = m_VertexFmt;
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateBuffer( &bufferDesc, &subrcData, &m_pBuffer ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create buffer." ), -1 );
		}
	}

	MapilVoid D3D10Rectangle3D::Update(	const Rectangle3DVertexFormat& fmt,
										SharedPointer < Texture > pTex )
	{
		
	}

	MapilVoid D3D10Rectangle3D::Update( const Rectangle3DVertexFormat& fmt )
	{
	}

	MapilVoid D3D10Rectangle3D::Draw()
	{
		DrawVertex();
	}

	MapilVoid D3D10Rectangle3D::Draw( const Matrix4x4 < MapilFloat32 >& mat )
	{
	}

	MapilVoid D3D10Rectangle3D::DrawVertex()
	{
		::UINT stride = sizeof( VertexFormat );
		::UINT offset = 0;
		m_pDev->GetDev().GetPointer()->IASetVertexBuffers( 0, 1, &m_pBuffer, &stride, &offset );
		// Primitive definition.
		m_pDev->GetDev().GetPointer()->IASetPrimitiveTopology( ::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
		
		::D3D10_TECHNIQUE_DESC techDesc;
		m_pEffectTech->GetDesc( &techDesc );
		for( UINT p = 0; p < techDesc.Passes; ++p ){
			m_pEffectTech->GetPassByIndex( p )->Apply( 0 );
			m_pDev->GetDev().GetPointer()->Draw( 4, 0 );
		}
	}
}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D