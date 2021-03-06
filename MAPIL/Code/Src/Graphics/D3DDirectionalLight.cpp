/**
*	@file	D3DDirectionalLight.cpp
*	@brief	Implementation of D3DDirectionalLight.
*	@date	2011.8.24 (Wed) 20:30
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_9_0_C )

#include "../../Include/MAPIL/Graphics/D3DDirectionalLight.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DDirectionalLight::D3DDirectionalLight( SharedPointer < GraphicsDevice > pDev ) :	DirectionalLight( pDev ),
																						m_IsActive( MapilFalse ),
																						m_LightIndex( -1 )
	{
		ZeroObject( &m_D3DLight, sizeof( m_D3DLight ) );
	}

	D3DDirectionalLight::~D3DDirectionalLight()
	{
		ReleaseLightIndex( m_LightIndex );
		ZeroObject( &m_D3DLight, sizeof( m_D3DLight ) );
		m_IsActive = MapilFalse;
		m_IsUsed = MapilFalse;
		m_LightIndex = -1;
	}

	// Create.
	MapilVoid D3DDirectionalLight::Create(	const ColorARGB < MapilFloat32 >& colorDiffuse,
											const ColorARGB < MapilFloat32 >& colorAmbient,
											const ColorARGB < MapilFloat32 >& colorSpecular,
											const Vector3 < MapilFloat32 >& vDir,
											MapilFloat32 attenuation0, MapilFloat32 attenuation1, MapilFloat32 attenuation2 )
	{
		Assert(	!m_IsUsed, CURRENT_POSITION, TSTR( "The directional light was already created." ), -1 );

		m_LightIndex = AttachLightIndex();

		Assert(	m_LightIndex != -1, CURRENT_POSITION, TSTR( "Reached max light index." ), -2 );

		m_IsUsed = MapilTrue;

		//Type of light
		m_D3DLight.Type = ::D3DLIGHT_DIRECTIONAL;
		SetDiffuseColor( colorDiffuse );
		SetAmbientColor( colorAmbient );
		SetSpecularColor( colorSpecular );
		SetDirection( vDir );
	}

	// Enagle light
	MapilVoid D3DDirectionalLight::Enable()
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The light isn't created yet." ), -1 );

		//Case that light has already being drawn
		if( m_IsActive ){
			m_pDev->GetDev().GetPointer()->SetLight( m_LightIndex, &m_D3DLight );
			m_pDev->GetDev().GetPointer()->LightEnable( m_LightIndex, TRUE );
		}
		else{
			m_pDev->GetDev().GetPointer()->SetLight( m_LightIndex, &m_D3DLight );
			m_pDev->GetDev().GetPointer()->LightEnable( m_LightIndex, TRUE );
			m_IsActive = MapilTrue;
		}
	}

	// Set diffuse color
	MapilVoid D3DDirectionalLight::SetDiffuseColor( const ColorARGB < MapilFloat32 >& colorDiffuse )
	{
		Assert( m_IsUsed, CURRENT_POSITION, TSTR( "The light isn't created yet." ), -1 );

		m_D3DLight.Diffuse.r = colorDiffuse.m_R;
		m_D3DLight.Diffuse.g = colorDiffuse.m_G;
		m_D3DLight.Diffuse.b = colorDiffuse.m_B;
		m_D3DLight.Diffuse.a = colorDiffuse.m_A;
	}

	// Set ambient color
	MapilVoid D3DDirectionalLight::SetAmbientColor( const ColorARGB < MapilFloat32 >& colorAmbient )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The light isn't created yet." ), -1 );

		m_D3DLight.Ambient.r = colorAmbient.m_R;
		m_D3DLight.Ambient.g = colorAmbient.m_G;
		m_D3DLight.Ambient.b = colorAmbient.m_B;
		m_D3DLight.Ambient.a = colorAmbient.m_A;
	}

	// Set specular color
	MapilVoid D3DDirectionalLight::SetSpecularColor( const ColorARGB < MapilFloat32 >& colorSpecular )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The light isn't created yet." ), -1 );

		m_D3DLight.Specular.r = colorSpecular.m_R;
		m_D3DLight.Specular.g = colorSpecular.m_G;
		m_D3DLight.Specular.b = colorSpecular.m_B;
		m_D3DLight.Specular.a = colorSpecular.m_A;
	}

	// Set diffuse color
	MapilVoid D3DDirectionalLight::SetDiffuseColor( const ColorARGB < MapilUChar >& color )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The light isn't created yet." ), -1 );

		m_D3DLight.Diffuse.r = color.m_R / 255.0f;
		m_D3DLight.Diffuse.g = color.m_G / 255.0f;
		m_D3DLight.Diffuse.b = color.m_B / 255.0f;
		m_D3DLight.Diffuse.a = color.m_A / 255.0f;
	}

	// Set ambient color
	MapilVoid D3DDirectionalLight::SetAmbientColor( const ColorARGB < MapilUChar >& color )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The light isn't created yet." ), -1 );

		m_D3DLight.Ambient.r = color.m_R / 255.0f;
		m_D3DLight.Ambient.g = color.m_G / 255.0f;
		m_D3DLight.Ambient.b = color.m_B / 255.0f;
		m_D3DLight.Ambient.a = color.m_A / 255.0f;
	}

	// Set specular color
	MapilVoid D3DDirectionalLight::SetSpecularColor( const ColorARGB < MapilUChar >& color )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The light isn't created yet." ), -1 );

		m_D3DLight.Specular.r = color.m_R / 255.0f;
		m_D3DLight.Specular.g = color.m_G / 255.0f;
		m_D3DLight.Specular.b = color.m_B / 255.0f;
		m_D3DLight.Specular.a = color.m_A / 255.0f;
	}

	// Set attenuation of light
	MapilVoid D3DDirectionalLight::SetAttenuation( MapilFloat32 attenuation0, MapilFloat32 attenuation1, MapilFloat32 attenuation2 )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The light isn't created yet." ), -1 );
		m_D3DLight.Attenuation0 = attenuation0;
		m_D3DLight.Attenuation1 = attenuation1;
		m_D3DLight.Attenuation2 = attenuation2;
	}
	
	// Set position.
	MapilVoid D3DDirectionalLight::SetDirection( const Vector3 < MapilFloat32 >& vDir )
	{
		Assert( m_IsUsed, CURRENT_POSITION, TSTR( "The light isn't created yet." ), -1 );

		D3DXVECTOR3 vDXDir( vDir.m_X, vDir.m_Y, vDir.m_Z );
		D3DXVec3Normalize( static_cast < D3DXVECTOR3* > ( &m_D3DLight.Direction ), &vDXDir );		//Normalize
	}
}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D