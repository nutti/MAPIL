/**
*	@file	GLDirectionalLight.cpp
*	@brief	Implementation of GLDirectionalLight.
*	@date	2011.7.16 (Sat) 16:29
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#include "../../Include/MAPIL/Graphics/GLDirectionalLight.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GLDirectionalLight::GLDirectionalLight( SharedPointer < GraphicsDevice > pDev ) :	DirectionalLight( pDev ),
																						m_LightNum( GL_LIGHT0 )
	{
	}

	GLDirectionalLight::~GLDirectionalLight()
	{
	}

	// Create.
	MapilVoid GLDirectionalLight::Create(	const ColorARGB < MapilFloat32 >& colorDiffuse,
											const ColorARGB < MapilFloat32 >& colorAmbient,
											const ColorARGB < MapilFloat32 >& colorSpecular,
											const Vector3 < MapilFloat32 >& vDir,
											MapilFloat32 attenuation0, MapilFloat32 attenuation1, MapilFloat32 attenuation2 )
	{
		SetDiffuseColor( colorDiffuse );
		SetAmbientColor( colorAmbient );
		SetSpecularColor( colorSpecular );
		SetDirection( vDir );
		SetAttenuation( attenuation0, attenuation1, attenuation2 );
	}

	// Enagle light
	MapilVoid GLDirectionalLight::Enable()
	{
		glEnable( m_LightNum );
	}
		
	// Set diffuse color
	MapilVoid GLDirectionalLight::SetDiffuseColor( const ColorARGB < MapilFloat32 >& colorDiffuse )
	{
		GLfloat color[] = { colorDiffuse.m_R, colorDiffuse.m_G, colorDiffuse.m_B, colorDiffuse.m_A };
		glLightfv( m_LightNum, GL_DIFFUSE, color );
	}

	// Set ambient color
	MapilVoid GLDirectionalLight::SetAmbientColor( const ColorARGB < MapilFloat32 >& colorAmbient )
	{
		GLfloat color[] = { colorAmbient.m_R, colorAmbient.m_G, colorAmbient.m_B, colorAmbient.m_A };
		glLightfv( m_LightNum, GL_AMBIENT, color );
	}

	// Set specular color
	MapilVoid GLDirectionalLight::SetSpecularColor( const ColorARGB < MapilFloat32 >& colorSpecular )
	{
		GLfloat color[] = { colorSpecular.m_R, colorSpecular.m_G, colorSpecular.m_B, colorSpecular.m_A };
		glLightfv( m_LightNum, GL_SPECULAR, color );
	}

	// Set diffuse color
	MapilVoid GLDirectionalLight::SetDiffuseColor( const ColorARGB < MapilUChar >& color )
	{
		GLint val[] = { color.m_R, color.m_G, color.m_B, color.m_A };
		glLightiv( m_LightNum, GL_DIFFUSE, val );
	}

	// Set ambient color
	MapilVoid GLDirectionalLight::SetAmbientColor( const ColorARGB < MapilUChar >& color )
	{
		GLint val[] = { color.m_R, color.m_G, color.m_B, color.m_A };
		glLightiv( m_LightNum, GL_AMBIENT, val );
	}

	// Set specular color
	MapilVoid GLDirectionalLight::SetSpecularColor( const ColorARGB < MapilUChar >& color )
	{
		GLint val[] = { color.m_R, color.m_G, color.m_B, color.m_A };
		glLightiv( m_LightNum, GL_SPECULAR, val );
	}

	// Set attenuation of light
	MapilVoid GLDirectionalLight::SetAttenuation( MapilFloat32 attenuation0, MapilFloat32 attenuation1, MapilFloat32 attenuation2 )
	{
		glLightf( m_LightNum, GL_CONSTANT_ATTENUATION, attenuation0 );
		glLightf( m_LightNum, GL_LINEAR_ATTENUATION, attenuation1 );
		glLightf( m_LightNum, GL_QUADRATIC_ATTENUATION, attenuation2 );
	}

	// Set position.
	MapilVoid GLDirectionalLight::SetDirection( const Vector3 < MapilFloat32 >& vDir )
	{
		GLfloat v[] = { vDir.m_X, vDir.m_Y, vDir.m_Z, 0.0f };
		glLightfv( m_LightNum, GL_POSITION, v );
	}

}

#endif	// API_OPENGL