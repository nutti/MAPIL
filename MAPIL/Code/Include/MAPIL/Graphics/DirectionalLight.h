/**
*	@file	DirectionalLight.h
*	@brief	DirectionalLight class is used for lighting. Directional light
*			will realize the light like the sun. Maximum number of light is
*			limited by the devices. If the users exceed this limitation, no
*			effect will be shown.
*	@date	2011.7.16 (Sat) 16:16
*/

#ifndef INCLUDED_MAPIL_DIRECTIONALLIGHT_H
#define INCLUDED_MAPIL_DIRECTIONALLIGHT_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Light.h"
#include "../Math/Vector.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class DirectionalLight : public Light
	{
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to the GraphicsDevice object.
		*/
		DirectionalLight( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~DirectionalLight();
		/**
		*	@brief					Instantiate the DirectionalLight class.
		*	@param colorDiffuse		Diffuse component of the light.
		*	@param colorAmbient		Ambient component of the light.
		*	@param colorSpecular	Specular component of the light.
		*	@param vDir				Direction of the light.
		*	@param attenuation0		Attenuation. ( 1/(attenuation0+attenuation1*d+attenuation2*d^2) )
		*	@param attenuation1		Attenuation.
		*	@param attenuation2		Attenuation.
		*/
		virtual MapilVoid Create(	const ColorARGB < MapilFloat32 >& colorDiffuse,
									const ColorARGB < MapilFloat32 >& colorAmbient,
									const ColorARGB < MapilFloat32 >& colorSpecular,
									const Vector3 < MapilFloat32 >& vDir,
									MapilFloat32 attenuation0,
									MapilFloat32 attenuation1,
									MapilFloat32 attenuation2 ) = 0;
		/**
		*	@brief			Set direction of the light.
		*	@param vDir		Direction of the light.
		*/
		virtual MapilVoid SetDirection( const Vector3 < MapilFloat32 >& vDir ) = 0;
	};
}

#endif	// INCLUDED_MAPIL_DIRECTIONALLIGHT_H