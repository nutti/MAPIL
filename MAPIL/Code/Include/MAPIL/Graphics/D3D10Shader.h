/**
*	@file	D3D10Shader.h
*	@brief	
*	@date	2012.10.6 (Sat) 22:17
*/

#ifndef INCLUDED_MAPIL_D3D10SHADER_H
#define INCLUDED_MAPIL_D3D10SHADER_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_10_0 )

#include <d3dx10.h>

#include "Shader.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class D3D10Shader : public Shader
	{
	private:
		MapilBool							m_IsUsed;				///< The flag shows that the object is already used.
		::D3D10_PASS_DESC					m_PassDesc;
		::ID3D10EffectTechnique*			m_pEffectTech;
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		explicit D3D10Shader( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3D10Shader();
		MapilVoid Create( const MapilTChar* pFileName, const MapilChar* pTechName );
	};
}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DSHADER_H