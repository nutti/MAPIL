/**
*	@file	D3DAnimModel.h
*	@brief	
*	@date	2013.3.28 (Thu) 22:46
*/

#ifndef INCLUDED_MAPIL_D3DANIMMODEL_H
#define INCLUDED_MAPIL_D3DANIMMODEL_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3dx9.h>
#include <stack>

#include "Model.h"

#include "../IO/ModelFile.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	struct AnimModelData;
	class GraphicsDevice;
	//class Archiver;
	class D3DTexture;
	class D3DAnimModel : public Model
	{
	private:
		struct VertexFormat
		{
			MapilFloat32		m_Vertex[ 3 ];
			MapilFloat32		m_Normal[ 3 ];
			MapilFloat32		m_TexCoord[ 2 ];
		};

		struct Frame
		{
			struct Mesh
			{
				::LPDIRECT3DVERTEXBUFFER9			m_pVertex;				///< Vertex buffer.
				::LPDIRECT3DINDEXBUFFER9			m_pIndex;				///< Index buffer.
				::LPDIRECT3DVERTEXDECLARATION9		m_pVertexDecl;			///< Vertex declaration.
				D3DTexture*							m_pTexture;				///< Texture.
				MapilInt32							m_VertexTotal;			///< Number of vertex.
				MapilInt32							m_IndexTotal;			///< Number of index.
				::D3DMATERIAL9*						m_pMaterial;			///< Material structure.
				DWORD								m_NumMaterial;			///< Number of the material.
			};

			Mesh							m_Mesh;			///< Mesh.
			Matrix4x4 < MapilFloat32 >		m_TransMat;		///< Translation matrix.
			Frame*							m_pFirstChild;	///< First of child.
			Frame*							m_pSibling;		///< Sibling.
			std::basic_string < MapilChar >	m_Name;			///< Frame name.
			Matrix4x4 < MapilFloat32 >		m_CalcTransMat;	///< Calculated Matrix.
		};

		Frame						m_RootFrame;
		AnimModelData::Animation	m_Animation;
		std::stack < Matrix4x4 < MapilFloat32 > >		m_MatStack;

		/**
		*	@brief		Draw model with no transformation. This is called in Draw method.
		*/
		MapilVoid DrawModel();


		MapilVoid CreateModel( const AnimModelData::Frame& frame, Frame* pFrame );
		// Create frame.
		MapilVoid CreateFrame( const AnimModelData::Frame& frame, Frame* pFrame );
		// Clear frame.
		MapilVoid ClearFrame( Frame* pFrame );

		MapilVoid DrawFrame( const Frame& frame );

		MapilVoid DrawMesh( const Frame::Mesh& mesh );

		MapilVoid GetAnimTransMat(	const MapilChar* pTrackName,
									const MapilChar* pFrameName,
									Matrix4x4 < MapilFloat32 >* pMatOut,
									MapilFloat32 advanceTime,
									MapilFloat32 nowTime );
		// Create lerp translation matrix.
		MapilVoid CreateLerpTranslationMat(	Matrix4x4 < MapilFloat32 >* pMatOut,
											MapilFloat32 advanceTime,
											MapilFloat32 nowTime,
											const AnimModelData::Animation::AnimSet::AnimItem::Key& key );
		// Create lerp scaling matrix.
		MapilVoid CreateLerpScalingMat(	Matrix4x4 < MapilFloat32 >* pMatOut,
										MapilFloat32 advanceTime,
										MapilFloat32 nowTime,
										const AnimModelData::Animation::AnimSet::AnimItem::Key& key );
		// Create lerp rotation matrix.
		MapilVoid CreateLerpRotationMat(	Matrix4x4 < MapilFloat32 >* pMatOut,
											MapilFloat32 advanceTime,
											MapilFloat32 nowTime,
											const AnimModelData::Animation::AnimSet::AnimItem::Key& key );

		// Calculate world matrix for each frame.
		MapilVoid CalcFWM( Frame* pFrame );
		// Update world matrix for each frame.
		MapilVoid UpdateFWM(	Frame* pFrame,
								const MapilChar* pTrackName,
								MapilFloat32 advanceTime, 
								MapilFloat32 nowTime );
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		D3DAnimModel( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DAnimModel();
		/**
		*	@brief				Instantiate the D3DAnimModel object.
		*	@param pFileName	Name of the modeling file to load.
		*/
		MapilVoid Create( const MapilTChar* pFileName );
		MapilVoid Draw();

		MapilVoid Create( Archiver* pArchiver, const MapilTChar* pXFileName, const MapilTChar* pTextureFileName );
		MapilVoid Draw( const Matrix4x4 < MapilFloat32 >& mat );
		MapilBool DetectCollision(	const Vector3 < MapilFloat32 >& vRayDir,
											const Vector3 < MapilFloat32 >& vRayOrig,
											Vector2 < MapilFloat32 >* pVCollisionPos,
											MapilFloat32* pDistance );
		// Calculate world matrix of all frame.
		MapilVoid CalcFrameWorldMat();
		MapilVoid SetAnim( const MapilChar* pTrackName );
		// Update world matrix for all frame.
		MapilVoid UpdateFrameWorldMat(	const MapilChar* pTrackName,
										MapilFloat32 advanceTime, 
										MapilFloat32 nowTime );
	};
}

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DMODEL_H