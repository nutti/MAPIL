/**
*	@file	PointLight.h
*	@brief	PointLight class is used for lighting. Point light will
*			realize the light like an electric bulb. Maximum number
*			of light is limited by the devices. If the users exceeds
*			this limitation. no effect will occur.
*	@date	2011.7.16 (Sat) 18:36
*/

#ifndef INCLUDED_MAPIL_POINTLIGHT_H
#define INCLUDED_MAPIL_POINTLIGHT_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Light.h"
#include "../Math/Vector.hpp"
#include "GraphicsDevice.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class PointLight : public Light
	{
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		explicit PointLight( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~PointLight();
		/**
		*	@brief					Instantiate the PointLight object.
		*	@param colorDiffuse		Diffuse component of the light.
		*	@param colorAmbient		Ambient component of the light.
		*	@param colorSpecular	Specular component of the light.
		*	@param vPos				Position of the light.
		*	@param attenuation0		Attenuation. ( 1/(attenuation0+attenuation1*d+attenuation2*d^2) )
		*	@param attenuation1		Attenuation.
		*	@param attenuation2		Attenuation.
		*/
		virtual MapilVoid Create(	const ColorARGB < MapilFloat32 >& colorDiffuse,
									const ColorARGB < MapilFloat32 >& colorAmbient,
									const ColorARGB < MapilFloat32 >& colorSpecular,
									const Vector3 < MapilFloat32 >& vPos,
									MapilFloat32 attenuation0, MapilFloat32 attenuation1, MapilFloat32 attenuation2 ) = 0;
		/**
		*	@brief			Set position of the light.
		*	@param vPos		Position of the light.
		*/
		virtual MapilVoid SetPosition( const Vector3 < MapilFloat32 >& vPos ) = 0;
	};
}

#endif