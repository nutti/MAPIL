/**
*	@file	D3DPointSprite.h
*	@brief	This class is derived from PointSprite class. D3DPointSprite is
*			implemented for Direct3D. The users shouldn't call method from
*			this class directly.
*	@date	2011.8.31 (Wed) 8:06
*/

#ifndef INCLUDED_MAPIL_D3DPOINTSPRITE_H
#define INCLUDED_MAPIL_D3DPOINTSPRITE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3dx9.h>

#include "PointSprite.h"
#include "../Util/SharedPointer.hpp"
#include "../Util/COMPointer.hpp"
#include "../Math/Vector.hpp"
#include "../Util/Color.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class D3DPointSprite : public PointSprite
	{
		struct VertexFormat
		{
		public:
			MapilFloat32			m_X;		///< X-coordinate of the vertex.
			MapilFloat32			m_Y;		///< Y-coordinate of the vertex.
			MapilFloat32			m_Z;		///< Z-coordinate of the vertex.
			MapilFloat32			m_PSize;	///< Point size.
			DWORD					m_Col;		///< Color of the vertex.
			MapilFloat32			m_U;		///< U-coordinate of the texture for the vertex.
			MapilFloat32			m_V;		///< V-coordinate of the texture for the vertex.
		};
	private:
		::LPDIRECT3DVERTEXBUFFER9			m_pVertexBuf;			///< Vertex buffer.
		::LPDIRECT3DVERTEXDECLARATION9		m_pVertexDecl;			///< Vertex declaration.
		MapilInt32							m_NumVertex;			///< Number of the vertex.
		SharedPointer < Texture >			m_pTex;					///< Texture.
		VertexFormat*						m_pNonBufVertex;		///< Vertex buffer with no buffer.
		VertexManagementMethod				m_VertexManageMethod;	///< Management method of the vertices.
		
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		explicit D3DPointSprite( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DPointSprite();
		/**
		*	@brief				Instantiate the D3DPointSprite object.
		*	@param numVertex	Number of the vertex to be created.
		*	@param pTex			SharedPointer to the Texture object used in the PointSprite object.
		*	@param manageMethod	Management method of the vertices.
		*/
		MapilVoid Create(	MapilInt32 numVertex, SharedPointer < Texture > pTex,
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		/**
		*	@brief				Instantiate the D3DPointSprite object.
		*	@param numVertex	Number of the vertex to be created.
		*	@param manageMethod	Management method of the vertices.
		*/
		MapilVoid Create(	MapilInt32 numVertex,
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		/**
		*	@brief			Update the vertex.
		*	@param index	Index of the vertex to be updated.
		*	@param vPos		Position of the vertex.
		*	@param size		Point size.
		*	@param color	Color of the vertex.
		*/
		MapilVoid Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
							MapilFloat32 size, const ColorARGB < MapilFloat32 >& color );
		/**
		*	@brief			Update the vertex.
		*	@param index	Index of the vertex to be updated.
		*	@param vPos		Position of the vertex.
		*	@param size		Point size.
		*	@param color	Color of the vertex.
		*/
		MapilVoid Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
							MapilFloat32 size, const ColorARGB < MapilUChar >& color );
		/**
		*	@brief			Update the vertex.
		*	@param index	Index of the vertex to be updated.
		*	@param vPos		Position of the vertex.
		*	@param size		Point size.
		*	@param color	Color of the vertex.
		*/
		MapilVoid Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
							MapilFloat32 size, MapilUInt32 color );
		/**
		*	@brief	Draw all the registered vertices.
		*/
		MapilVoid Draw();
	};
}

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DPOINTSPRITE_H