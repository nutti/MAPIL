/**
*	@file	D3DModel.h
*	@brief	D3DModel class is derived class from Model class. D3DModel is
*			implemented for Direct3D. The users shouldn't call method from this
*			class directly.
*	@date	2011.8.25 (Thu) 18:50
*/

#ifndef INCLUDED_MAPIL_D3DMODEL_H
#define INCLUDED_MAPIL_D3DMODEL_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3dx9.h>

#include "Model.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	struct ModelData;
	class GraphicsDevice;
	class Archiver;
	class D3DTexture;
	class D3DModel : public Model
	{
	private:
		struct VertexFormat
		{
			MapilFloat32		m_Vertex[ 3 ];
			MapilFloat32		m_Normal[ 3 ];
			MapilFloat32		m_TexCoord[ 2 ];
		};

		::LPD3DXMESH				m_pD3DMesh;			///< Mesh handler.
		::D3DMATERIAL9*				m_pMaterial;		///< Material structure.
		::LPDIRECT3DTEXTURE9*		m_pD3DTexture;		///< Texture handler.
		DWORD						m_NumMaterial;		///< Number of the material.

		::LPDIRECT3DVERTEXBUFFER9			m_pVertex;				///< Vertex buffer.
		::LPDIRECT3DINDEXBUFFER9			m_pIndex;				///< Index buffer.
		::LPDIRECT3DVERTEXDECLARATION9		m_pVertexDecl;			///< Vertex declaration.
		D3DTexture*							m_pTexture;				///< Texture.
		MapilInt32							m_VertexTotal;			///< Number of vertex.
		MapilInt32							m_IndexTotal;			///< Number of index.
		//MapilBool					m_IsUsed;			///< The flag shows that the object is already used.
		/**
		*	@brief		Draw model with no transformation. This is called in Draw method.
		*/
		MapilVoid DrawModel();
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		D3DModel( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DModel();
		/**
		*	@brief				Instantiate the D3DModel object.
		*	@param pFileName	Name of the modeling file to load.
		*/
		MapilVoid Create( const MapilTChar* pFileName );
		/**
		*	@brief						Instantiate the D3DModel object.
		*	@param pArchiver			Archiver.
		*	@param pXFileName			Name of the modeling file to load.
		*	@param pTextureFileName		Name of the texture file to load.
		*/
		MapilVoid Create( Archiver* pArchiver, const MapilTChar* pXFileName, const MapilTChar* pTextureFileName );
		/**
		*	@brief	Draw the model with no transformation.
		*/
		MapilVoid Draw();
		/**
		*	@brief		Draw the model with transformation.
		*	@param mat	Transformation matrix.
		*/
		MapilVoid Draw( const Matrix4x4 < MapilFloat32 >& mat );
		/**
		*	@brief					Detect collision.
		*	@param vRayDir			Direction of the ray.
		*	@param vRayOrig			Position of the ray.
		*	@param pVcollisionPos	Position where the ray hits.
		*	@param pDistance		Distance between vRayOrig and where the ray hits.
		*	@return					Does the ray collide with the polygon?
		*/
		MapilBool DetectCollision(	const Vector3 < MapilFloat32 >& vRayDir,
									const Vector3 < MapilFloat32 >& vRayOrig,
									Vector2 < MapilFloat32 >* pVCollisionPos,
									MapilFloat32* pDistance );
	};
}

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DMODEL_H