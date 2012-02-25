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

#include "../../Include/MAPIL/Graphics/D3DDirectionalLight.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DDirectionalLight::D3DDirectionalLight( SharedPointer < GraphicsDevice > pDev ) :	DirectionalLight( pDev ),
																						m_IsActive( MapilFalse ),
																						m_IsUsed( MapilFalse )
	{
		ZeroObject( &m_D3DLight, sizeof( m_D3DLight ) );
	}

	D3DDirectionalLight::~D3DDirectionalLight()
	{
		ZeroObject( &m_D3DLight, sizeof( m_D3DLight ) );
		m_IsActive = MapilFalse;
		m_IsUsed = MapilFalse;
	}

	// Create.
	MapilVoid D3DDirectionalLight::Create(	const ColorARGB < MapilFloat32 >& colorDiffuse,
											const ColorARGB < MapilFloat32 >& colorAmbient,
											const ColorARGB < MapilFloat32 >& colorSpecular,
											const Vector3 < MapilFloat32 >& vDir,
											MapilFloat32 attenuation0, MapilFloat32 attenuation1, MapilFloat32 attenuation2 )
	{
		Assert(	!m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DDirectionalLight" ),
				TSTR( "Create" ),
				TSTR( "The directional light was already created." ),
				-1 );

		//Type of light
		m_D3DLight.Type = ::D3DLIGHT_DIRECTIONAL;
		SetDiffuseColor( colorDiffuse );
		SetAmbientColor( colorAmbient );
		SetSpecularColor( colorSpecular );
		SetDirection( vDir );

		m_IsUsed = MapilTrue;
	}

	// Enagle light
	MapilVoid D3DDirectionalLight::Enable()
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "Enable" ),
				TSTR( "Enable" ),
				TSTR( "The light isn't created yet." ),
				-1 );

		//Case that light has already being drawn
		if( m_IsActive ){
			int m_Index = 0;
			m_pDev->GetDev().GetPointer()->SetLight( m_Index, &m_D3DLight );
			m_pDev->GetDev().GetPointer()->LightEnable( m_Index, TRUE );
		}
		else{
			int m_Index = 0;
			m_pDev->GetDev().GetPointer()->SetLight( m_Index, &m_D3DLight );
			m_pDev->GetDev().GetPointer()->LightEnable( m_Index, TRUE );
			m_IsActive = MapilTrue;
		}
	}

	// Set diffuse color
	MapilVoid D3DDirectionalLight::SetDiffuseColor( const ColorARGB < MapilFloat32 >& colorDiffuse )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DDirectionalLight" ),
				TSTR( "SetDiffuseColor" ),
				TSTR( "The light isn't created yet." ),
				-1 );

		m_D3DLight.Diffuse.r = colorDiffuse.m_R;
		m_D3DLight.Diffuse.g = colorDiffuse.m_G;
		m_D3DLight.Diffuse.b = colorDiffuse.m_B;
		m_D3DLight.Diffuse.a = colorDiffuse.m_A;
	}

	// Set ambient color
	MapilVoid D3DDirectionalLight::SetAmbientColor( const ColorARGB < MapilFloat32 >& colorAmbient )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DDirectionalLight" ),
				TSTR( "SetAmbientColor" ),
				TSTR( "The light isn't created yet." ),
				-1 );

		m_D3DLight.Ambient.r = colorAmbient.m_R;
		m_D3DLight.Ambient.g = colorAmbient.m_G;
		m_D3DLight.Ambient.b = colorAmbient.m_B;
		m_D3DLight.Ambient.a = colorAmbient.m_A;
	}

	// Set specular color
	MapilVoid D3DDirectionalLight::SetSpecularColor( const ColorARGB < MapilFloat32 >& colorSpecular )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DDirectionalLight" ),
				TSTR( "SetSpecularColor" ),
				TSTR( "The light isn't created yet." ),
				-1 );

		m_D3DLight.Specular.r = colorSpecular.m_R;
		m_D3DLight.Specular.g = colorSpecular.m_G;
		m_D3DLight.Specular.b = colorSpecular.m_B;
		m_D3DLight.Specular.a = colorSpecular.m_A;
	}

	// Set diffuse color
	MapilVoid D3DDirectionalLight::SetDiffuseColor( const ColorARGB < MapilUChar >& color )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DPointLight" ),
				TSTR( "SetDiffuseColor" ),
				TSTR( "The light isn't created yet." ),
				-1 );

		m_D3DLight.Diffuse.r = color.m_R / 255.0f;
		m_D3DLight.Diffuse.g = color.m_G / 255.0f;
		m_D3DLight.Diffuse.b = color.m_B / 255.0f;
		m_D3DLight.Diffuse.a = color.m_A / 255.0f;
	}

	// Set ambient color
	MapilVoid D3DDirectionalLight::SetAmbientColor( const ColorARGB < MapilUChar >& color )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DPointLight" ),
				TSTR( "SetAmbientColor" ),
				TSTR( "The light isn't created yet." ),
				-1 );

		m_D3DLight.Ambient.r = color.m_R / 255.0f;
		m_D3DLight.Ambient.g = color.m_G / 255.0f;
		m_D3DLight.Ambient.b = color.m_B / 255.0f;
		m_D3DLight.Ambient.a = color.m_A / 255.0f;
	}

	// Set specular color
	MapilVoid D3DDirectionalLight::SetSpecularColor( const ColorARGB < MapilUChar >& color )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DPointLight" ),
				TSTR( "SetSpecularColor" ),
				TSTR( "The light isn't created yet." ),
				-1 );

		m_D3DLight.Specular.r = color.m_R / 255.0f;
		m_D3DLight.Specular.g = color.m_G / 255.0f;
		m_D3DLight.Specular.b = color.m_B / 255.0f;
		m_D3DLight.Specular.a = color.m_A / 255.0f;
	}

	// Set attenuation of light
	MapilVoid D3DDirectionalLight::SetAttenuation( MapilFloat32 attenuation0, MapilFloat32 attenuation1, MapilFloat32 attenuation2 )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DDirectionalLight" ),
				TSTR( "SetAttenuation" ),
				TSTR( "The light isn't created yet." ),
				-1 );
		m_D3DLight.Attenuation0 = attenuation0;
		m_D3DLight.Attenuation1 = attenuation1;
		m_D3DLight.Attenuation2 = attenuation2;
	}
	
	// Set position.
	MapilVoid D3DDirectionalLight::SetDirection( const Vector3 < MapilFloat32 >& vDir )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DDirectionalLight" ),
				TSTR( "SetPosition" ),
				TSTR( "The light isn't created yet." ),
				-1 );

		D3DXVECTOR3 vDXDir( vDir.m_X, vDir.m_Y, vDir.m_Z );
		D3DXVec3Normalize( static_cast < D3DXVECTOR3* > ( &m_D3DLight.Direction ), &vDXDir );		//Normalize
	}
}

#endif	// API_DIRECT3D