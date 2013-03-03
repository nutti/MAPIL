/**
*	@file	XAnimFile.h
*	@brief	
*	@date	2013.3.3(Sun) 15:36
*/

#ifndef INCLUDED_MAPIL_XANIMFILE_H
#define INCLUDED_MAPIL_XANIMFILE_H

#include "../CrossPlatform.h"

#if defined ( LIB_STL )
#include <vector>
#include <map>
#include <stack>
#endif

#include <fstream>

#include "ModelFile.h"
#include "../Util/Color.hpp"
#include "../Math/Vector.hpp"
#include "../Math/Matrix.hpp"
#include "../Type.h"

namespace MAPIL
{
	
	class XAnimFile
	{
	protected:
		struct Frame
		{
		public:
			struct Mesh
			{
			public:
				struct Material
				{
				public:
					struct MaterialColor
					{
					public:
						ColorARGB < MapilFloat32 >		m_Diffuse;
						ColorARGB < MapilFloat32 >		m_Specular;
						ColorARGB < MapilFloat32 >		m_Emissive;
						MapilFloat32					m_Power;
					};
					MaterialColor					m_MaterialColor;
					MapilChar						m_TextureFileName[ 260 ];
				};
				struct Face
				{
				public:
					MapilInt32						m_NumElement;
					MapilInt32						m_MaterialNum;
					MapilInt32						m_Index[ 4 ];
					MapilInt32						m_NormalNum[ 4 ];
				};
				MapilInt32											m_NumVertex;
				std::vector < Vector3 < MapilFloat32 > >			m_Vertex;
				MapilInt32											m_NumIndex;
				MapilInt32											m_NumNormal;
				std::vector < Vector3 < MapilFloat32 > >			m_Normal;
				std::vector < Face >								m_Face;
				MapilInt32											m_NumTextureCoord;
				std::vector < Vector2 < MapilFloat32 > >			m_TextureCoord;
				MapilInt32											m_NumMaterial;
				std::vector < Material >							m_Material;
				MapilInt32											m_NumVertexColor;
				std::vector < ColorARGB < MapilFloat32 > >			m_VertexColor;
			};
			
			Mesh											m_Mesh;
			Matrix4x4 < MapilFloat32 >						m_TransMat;
			Frame*											m_pFirstChild;
			Frame*											m_pSibling;
			std::basic_string < MapilChar >					m_FrameName;
			Matrix4x4 < MapilFloat32 >						m_CalcTransMat;
		};

		struct Anim
		{
		public:
			struct AnimationSet
			{
			public:
				struct Animation
				{
				public:
					struct Key
					{
					public:
						MapilInt32										m_TransType;
						MapilInt32										m_NumAnim;
						std::vector < MapilInt32 >						m_TransTime;
						std::vector < Vector4 < MapilFloat32 > >	m_TransVal;
					};	// Key
					std::vector < Key >								m_AnimKey;
					std::basic_string < MapilChar >		m_AnimName;
				};	// Animation
				std::map < std::basic_string < MapilChar >, Animation >		m_AnimMap;
			};	// AnimationSet
			std::map < std::basic_string < MapilChar >, AnimationSet >		m_AnimSetMap;
		};

		Frame											m_RootFrame;
		Anim											m_Anim;
		std::stack < Matrix4x4 < MapilFloat32 > >		m_MatStack;
	private:
		// Clear Frame structure.
		MapilVoid ClearFrame( Frame* pFrame );
		// Clear Anim structure.
		MapilVoid ClearAnim( Anim* pAnim );
		// Process "template" token.
		MapilVoid ProcessTemplateToken(	std::basic_ifstream < MapilChar >* pFIn,
													MapilChar* pToken,
													MapilInt32* pHierarchyNum );
		// Process "Frame" token.
		MapilVoid ProcessFrameToken(	std::basic_ifstream < MapilChar >* pFIn,
													MapilChar* pToken,
													MapilInt32* pHierarchyNum,
													Frame* pFrame );
		// Process "FrameTransformMatrix" token.
		MapilVoid ProcessFrameTransformMatrixToken(	std::basic_ifstream < MapilChar >* pFIn,
																MapilChar* pToken,
																MapilInt32* pHierarchyNum,
																Frame* pFrame );
		// Process "Mesh" token.
		MapilVoid ProcessMeshToken(	std::basic_ifstream < MapilChar >* pFIn,
												MapilChar* pToken,
												MapilInt32* pHierarchyNum,
												Frame* pFrame );
		// Process "MeshMaterialList" token.
		MapilVoid ProcessMeshMaterialListToken(	std::basic_ifstream < MapilChar >* pFIn,
															MapilChar* pToken,
															MapilInt32* pHierarchyNum,
															Frame* pFrame );
		// Process "Material" token.
		MapilVoid ProcessMaterialToken(	std::basic_ifstream < MapilChar >* pFIn,
													MapilChar* pToken,
													MapilInt32* pHierarchyNum,
													Frame* pFrame );
		// Process "MeshNormals" token.
		MapilVoid ProcessMeshNormalsToken(	std::basic_ifstream < MapilChar >* pFIn,
														MapilChar* pToken,
														MapilInt32* pHierarchyNum,
														Frame* pFrame );
		// Process "MeshTextureCoords" token.
		MapilVoid ProcessMeshTextureCoordsToken(	std::basic_ifstream < MapilChar >* pFIn,
																MapilChar* pToken,
																MapilInt32* pHierarchyNum,
																Frame* pFrame );
		// Process "AnimationSet" token.
		MapilVoid ProcessAnimationSetToken(	std::basic_ifstream < MapilChar >* pFIn,
														MapilChar* pToken,
														MapilInt32* pHierarchyNum );
		// Process "Animation" token.
		MapilVoid ProcessAnimationToken(	std::basic_ifstream < MapilChar >* pFIn,
														MapilChar* pToken,
														Anim::AnimationSet* pAnimSet,
														MapilInt32* pHierarchyNum );
		// Process "AnimationKey" token.
		MapilVoid ProcessAnimationKeyToken(	std::basic_ifstream < MapilChar >* pFIn,
														MapilChar* pToken,
														Anim::AnimationSet::Animation* pAnim,
														MapilInt32* pHierarchyNum );
		// Get token.
		MapilVoid GetToken(	std::basic_ifstream < MapilChar >* pFIn,
										MapilChar* pToken );
		// Calculate world matrix for each frame.
		MapilVoid CalcFWM( Frame* pFrame );
		// Update world matrix for each frame.
		MapilVoid UpdateFWM(	Frame* pFrame,
											const MapilChar* pTrackName,
											MapilFloat32 advanceTime, 
											MapilFloat32 nowTime );
		// Create lerp transformation matrix.
		MapilVoid CreateLerpTransMat(	Matrix4x4 < MapilFloat32 >* pMatOut,
													MapilFloat32 advanceTime,
													MapilFloat32 nowTime,
													const Anim::AnimationSet::Animation::Key& key );
		// Get transformation matrix.
		MapilVoid GetTransMat(	const MapilChar* pTrackName,
											const MapilChar* pFrameName,
											Matrix4x4 < MapilFloat32 >* pMatOut,
											MapilFloat32 advanceTime,
											MapilFloat32 nowTime );
		// Delete all frame.
		MapilVoid DeleteF( Frame* pFrame );
		// Delete each frame.
		MapilVoid DeleteFrame();
	public:
		// Constructor.
		XAnimFile();
		// Destructor.
		virtual ~XAnimFile();
		// Load.
		MapilVoid Load( const MapilChar* pFileName );
		// Calculate world matrix for all frame.
		MapilVoid CalcFrameWorldMat();
		// Update world matrix for all frame.
		MapilVoid UpdateFrameWorldMat(	const MapilChar* pTrackName,
													MapilFloat32 advanceTime, 
													MapilFloat32 nowTime );
	};
}

#endif
