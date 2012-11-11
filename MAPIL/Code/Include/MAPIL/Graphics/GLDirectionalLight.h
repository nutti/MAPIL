/**
*	@file	GLDirectionalLight.h
*	@brief	This class is derived from DirectionalLight class. GLDirevtionalLight
*			is implemented for OpenGL. The users shouldn't call method from this
*			class directly.
*	@date	2011.7.16 (Sat) 16:25
*/

#ifndef INCLUDED_MAPIL_GLDIRECTIONALLIGHT_H
#define INCLUDED_MAPIL_GLDIRECTIONALLIGHT_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_OPENGL )

#if defined ( API_WIN32API )
#include <Windows.h>
#endif
#if defined ( OS_WIN_32BIT )
#include <gl/GL.h>
#elif defined ( OS_LINUX_32BIT ) || defined ( OS_MAC_64BIT )
#include <GL/gl.h>
#endif

#include "DirectionalLight.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class GLDirectionalLight : public DirectionalLight
	{
		GLenum			m_LightNum;			///< Light number.
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		GLDirectionalLight( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLDirectionalLight();
		/**
		*	@brief					Instantiate the GLDirectionalLight class.
		*	@param colorDiffuse		Diffuse component of the light.
		*	@param colorAmbient		Ambient component of the light.
		*	@param colorSpecular	Specular component of the light.
		*	@param vDir				Direction of the light.
		*	@param attenuation0		Attenuation. ( 1/(attenuation0+attenuation1*d+attenuation2*d^2) )
		*	@param attenuation1		Attenuation.
		*	@param attenuation2		Attenuation.
		*/
		MapilVoid Create(	const ColorARGB < MapilFloat32 >& colorDiffuse,
							const ColorARGB < MapilFloat32 >& colorAmbient,
							const ColorARGB < MapilFloat32 >& colorSpecular,
							const Vector3 < MapilFloat32 >& vDir,
							MapilFloat32 attenuation0,
							MapilFloat32 attenuation1,
							MapilFloat32 attenuation2 );
		/**
		*	@brief			Enable lighting.
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
		*	@brief			Set direction of the light.
		*	@param vDir		Direction of the light.
		*/
		MapilVoid SetDirection( const Vector3 < MapilFloat32 >& vDir );
	};
}

#endif	// API_OPENGL

#endif	// INCLUDED_MAPIL_GLDIRECTIONALLIGHT_H
