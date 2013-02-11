/**
*	@file	D3DNSidedPolygon3D.h
*	@brief	
*	@date	2011.12.31 (Sat) 13:08
*/

#ifndef INCLUDED_MAPIL_D3DNSIDEDPOLYGON3D_H
#define INCLUDED_MAPIL_D3DNSIDEDPOLYGON3D_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3d9.h>

#include "NSidedPolygon3D.h"
#include "Texture.h"
#include "../Util/SharedPointer.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{

	class D3DNSidedPolygon3D : public NSidedPolygon3D
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
		//MapilBool							m_IsUsed;				///< The flag shows that the object is already used.
		SharedPointer < Texture >			m_pTexture;				///< Texture.
		VertexFormat*						m_pNonBufVertex;		///< Vertex buffer with no buffer.
		VertexManagementMethod				m_VertexManageMethod;	///< Management method of the vertices.
		MapilInt32							m_VertexTotal;			///< Number of the vertices.

		/**
		*	@brief		Draw without transformatoin.
		*/
		MapilVoid DrawVertex( MapilInt32 method, MapilInt32 count );
	public:
		explicit D3DNSidedPolygon3D( SharedPointer < GraphicsDevice > pDev );
		~D3DNSidedPolygon3D();
		MapilVoid Create(	MapilInt32 vertexTotal, const NSidedPolygon3DVertexFmt fmt[],
							SharedPointer < Texture > pTex, VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		MapilVoid Create(	MapilInt32 vertexTotal, const NSidedPolygon3DVertexFmt fmt[],
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		MapilVoid Update( MapilInt32 index, const NSidedPolygon3DVertexFmt& fmt );
		MapilVoid Draw( MapilInt32 method, MapilInt32 count );
	};
}

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_NSIDEDPOLYGON3D_H