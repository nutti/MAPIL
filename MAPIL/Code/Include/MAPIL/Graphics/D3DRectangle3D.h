/**
*	@file	D3DRectangle3D.h
*	@brief	D3DRectangle3D class is derived from Rectangle3D class. D3DRectnagle
*			is implemented for Direct3D. The users shouldn't call method from this class
*			directly.
*	@date	2011.8.25 (Thu) 20:46
*/

#ifndef INCLUDED_MAPIL_D3DRECTANGLE3D_H
#define INCLUDED_MAPIL_D3DRECTANGLE3D_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3dx9.h>

#include "Rectangle3D.h"
#include "Texture.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class D3DRectangle3D : public Rectangle3D
	{
	private:
		struct VertexFormat
		{
		public:
			MapilFloat32			m_X;		///< X-coordinate of the vertex.
			MapilFloat32			m_Y;		///< Y-coordinate of the vertex.
			MapilFloat32			m_Z;		///< Z-coordinate of the vertex.
			DWORD					m_Col;		///< Color of the vertex.
			MapilFloat32			m_U;		///< U-coordinate of the texture for the vertex.
			MapilFloat32			m_V;		///< V-coordinate of the texture for the vertex.
		};

		::LPDIRECT3DVERTEXBUFFER9			m_pVertex;				///< Vertex buffer.
		::LPDIRECT3DVERTEXDECLARATION9		m_pVertexDecl;			///< Vertex declaration.
		MapilBool							m_IsUsed;				///< The flag shows that the object is already used.
		SharedPointer < Texture >			m_pTexture;				///< Texture.
		VertexFormat*						m_pNonBufVertex;		///< Vertex buffer with no buffer.
		VertexManagementMethod				m_VertexManageMethod;	///< Management method of the vertices.
		/**
		*	@brief		Draw without transformatoin.
		*/
		MapilVoid DrawVertex();
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		explicit D3DRectangle3D( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DRectangle3D();
		/**
		*	@brief				Instantiate the D3DRectangle3D object.
		*	@param fmt			The vertex format of the D3DRectangle3D object.
		*	@param pTex			SharedPointer to the Texture object used in the D3DRectangle3D object.
		*	@param manageMethod	Management method of the vertices.
		*/
		MapilVoid Create(	const Rectangle3DVertexFormat& fmt,
							SharedPointer < Texture > pTex,
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		/**
		*	@brief				Instantiate the D3DRectangle3D object.
		*	@param fmt			The vertex format of the D3DRectangle3D object.
		*	@param manageMethod	Management method of the vertices.
		*/
		MapilVoid Create(	const Rectangle3DVertexFormat& fmt,
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		/**
		*	@brief		Update the D3DRectangle3D object.
		*	@param fmt	The vertex format of the D3DRectangle3D object.
		*	@param pTex	SharedPointer to the Texture object used in the D3DRectangle3D object.
		*/
		MapilVoid Update(	const Rectangle3DVertexFormat& fmt,
							SharedPointer < Texture > pTex );
		/**
		*	@brief		Update the D3DRectangle3D object.
		*	@param fmt	The vertex format of the D3DRectangle3D object.
		*/
		MapilVoid Update( const Rectangle3DVertexFormat& fmt );
		/**
		*	@brief	Draw the D3DRectangle3D object.
		*/
		MapilVoid Draw();
		/**
		*	@brief		Draw the D3DRectangle3D object with transformation.
		*	@param mat	Transformation matrix.
		*/
		MapilVoid Draw( const Matrix4x4 < MapilFloat32 >& mat );
	};
}

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DRECTANGLE3D_H