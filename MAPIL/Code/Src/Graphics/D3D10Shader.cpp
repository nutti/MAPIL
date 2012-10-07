/**
*	@file	D3D10Shader.cpp
*	@brief	Implementation of D3D10Shader.h.
*	@date	2012.10.6 (Sat) 22:20
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_10_0 )

#include "../../Include/MAPIL/Graphics/D3D10Shader.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3D10Shader::D3D10Shader( SharedPointer < GraphicsDevice > pDev ) :	Shader( pDev ),
																		m_IsUsed( MapilFalse ),
																		m_pEffectTech( NULL )
	{
	}

	D3D10Shader::~D3D10Shader()
	{
		m_IsUsed = MapilFalse;
	}

	MapilVoid D3D10Shader::Create( const MapilTChar* pFileName, const MapilChar* pTechName )
	{
		::ID3D10InputLayout* pLayout;
		::ID3D10Effect* pEffect;
		::ID3D10Blob* pBlob;

		if( FAILED( ::D3DX10CreateEffectFromFile(	pFileName,
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
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create effect from file" ), -1 );
		}

		m_pEffectTech = pEffect->GetTechniqueByName( pTechName );
		m_pEffectTech->GetPassByIndex( 0 )->GetDesc( &m_PassDesc );
	//	if( FAILED( m_pDev->GetDev().GetPointer()->CreateInputLayout( 
	}
}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D