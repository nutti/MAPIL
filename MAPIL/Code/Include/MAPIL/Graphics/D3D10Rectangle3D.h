/**
*	@file	D3D10Rectangle3D.h
*	@brief	
*	@date	2012.10.6 (Sat) 21:20
*/

#ifndef INCLUDED_MAPIL_D3D10RECTANGLE3D_H
#define INCLUDED_MAPIL_D3D10RECTANGLE3D_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_10_0 )

#include <d3dx10.h>

#include "Rectangle3D.h"
#include "Texture.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class D3D10Rectangle3D : public Rectangle3D
	{
	private:
		struct VertexFormat
		{
		public:
			::D3DXVECTOR3		m_Pos;
			::D3DXVECTOR3		m_Color;
		};

		MapilBool							m_IsUsed;				///< The flag shows that the object is already used.
		SharedPointer < Texture >			m_pTexture;				///< Texture.
		VertexFormat						m_VertexFmt[ 4 ];		///< Vertex format.
		::ID3D10Buffer*						m_pBuffer;
		::D3D10_INPUT_ELEMENT_DESC			m_ElmDesc[ 2 ];

		::D3D10_PASS_DESC					m_PassDesc;
		::ID3D10EffectTechnique*			m_pEffectTech;

		/**
		*	@brief		Draw without transformatoin.
		*/
		MapilVoid DrawVertex();
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		explicit D3D10Rectangle3D( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3D10Rectangle3D();
		/**
		*	@brief				Instantiate the D3D10Rectangle3D object.
		*	@param fmt			The vertex format of the D3DRectangle3D object.
		*	@param pTex			SharedPointer to the Texture object used in the D3DRectangle3D object.
		*	@param manageMethod	Management method of the vertices.
		*/
		MapilVoid Create(	const Rectangle3DVertexFormat& fmt,
							SharedPointer < Texture > pTex,
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		MapilVoid Create(	const Rectangle3DVertexFormat& fmt,
							SharedPointer < Texture > pTex,
							const MapilTChar* pShaderFileName, const MapilChar* pTechName,
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		/**
		*	@brief				Instantiate the D3D10Rectangle3D object.
		*	@param fmt			The vertex format of the D3DRectangle3D object.
		*	@param manageMethod	Management method of the vertices.
		*/
		MapilVoid Create(	const Rectangle3DVertexFormat& fmt,
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		/**
		*	@brief		Update the D3D10Rectangle3D object.
		*	@param fmt	The vertex format of the D3DRectangle3D object.
		*	@param pTex	SharedPointer to the Texture object used in the D3DRectangle3D object.
		*/
		MapilVoid Update(	const Rectangle3DVertexFormat& fmt,
							SharedPointer < Texture > pTex );
		/**
		*	@brief		Update the D3D10Rectangle3D object.
		*	@param fmt	The vertex format of the D3DRectangle3D object.
		*/
		MapilVoid Update( const Rectangle3DVertexFormat& fmt );
		/**
		*	@brief	Draw the D3D10Rectangle3D object.
		*/
		MapilVoid Draw();
		/**
		*	@brief		Draw the D3D10Rectangle3D object with transformation.
		*	@param mat	Transformation matrix.
		*/
		MapilVoid Draw( const Matrix4x4 < MapilFloat32 >& mat );
	};
}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DRECTANGLE3D_H