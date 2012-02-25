/**
*	@file	D3DDPointLight.h
*	@brief	This class is derived from PointLight class. D3DPointLight is
*			implemented for Direct3D. The uses shouldn't call method from
*			this class directly.
*	@date	2011.8.24 (Wed) 21:02
*/

#ifndef INCLUDED_MAPIL_D3DPOINTLIGHT_H
#define INCLUDED_MAPIL_D3DPOINTLIGHT_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3dx9.h>

#include "PointLight.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class D3DPointLight : public PointLight
	{
		::D3DLIGHT9					m_D3DLight;			///< D3DLIGHT9 structure
		MapilBool					m_IsActive;			///< Flag which light is drawing now
		MapilBool					m_IsUsed;			///< Flag which light is being used now
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		explicit D3DPointLight( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DPointLight();
		/**
		*	@brief					Instantiate the D3DPointLight object.
		*	@param colorDiffuse		Diffuse component of the light.
		*	@param colorAmbient		Ambient component of the light.
		*	@param colorSpecular	Specular component of the light.
		*	@param vPos				Position of the light.
		*	@param attenuation0		Attenuation. ( 1/(attenuation0+attenuation1*d+attenuation2*d^2) )
		*	@param attenuation1		Attenuation.
		*	@param attenuation2		Attenuation.
		*/
		MapilVoid Create(	const ColorARGB < MapilFloat32 >& colorDiffuse,
							const ColorARGB < MapilFloat32 >& colorAmbient,
							const ColorARGB < MapilFloat32 >& colorSpecular,
							const Vector3 < MapilFloat32 >& vPos,
							MapilFloat32 attenuation0, MapilFloat32 attenuation1, MapilFloat32 attenuation2 );
		/**
		*	@brief	Enable light.
		*/
		MapilVoid Enable();
		/**
		*	@brief					Set diffuse component of the light.
		*	@param colorDiffuse		Diffuse component of the light.
		*/
		MapilVoid SetDiffuseColor( const ColorARGB < MapilFloat32 >& colorDiffuse );
		/**
		*	@brief					Set ambient component of the light.
		*	@param colorAmbient		Ambient component of the light.
		*/
		MapilVoid SetAmbientColor( const ColorARGB < MapilFloat32 >& colorAmbient );
		/**
		*	@brief					Set specular component of the light.
		*	@param colorSpecular	Specular component of the light.
		*/
		MapilVoid SetSpecularColor( const ColorARGB < MapilFloat32 >& colorSpecular );
		/**
		*	@brief			Set diffuse color of the light.
		*	@param color	Diffuse color of the light.
		*/
		MapilVoid SetDiffuseColor( const ColorARGB < MapilUChar >& color );
		/**
		*	@brief			Set ambient color of the light.
		*	@param color	Ambient color of the light.
		*/
		MapilVoid SetAmbientColor( const ColorARGB < MapilUChar >& color );
		/**
		*	@brief			Set specular color of the light.
		*	@param color	Specular color of the light.
		*/
		MapilVoid SetSpecularColor( const ColorARGB < MapilUChar >& color );
		/**
		*	@brief					Set attenuation of the light.
		*	@param attenuation0		Attenuation. ( 1/(attenuation0+attenuation1*d+attenuation2*d^2) )
		*	@param attenuation1		Attenuation.
		*	@param attenuation2		Attenuation.
		*/
		MapilVoid SetAttenuation( MapilFloat32 attenuation0, MapilFloat32 attenuation1, MapilFloat32 attenuation2 );
		/**
		*	@brief			Set position of the light.
		*	@param vPos		Position of the light.
		*/
		MapilVoid SetPosition( const Vector3 < MapilFloat32 >& vPos );
	};
}

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DPOINTLIGHT_H