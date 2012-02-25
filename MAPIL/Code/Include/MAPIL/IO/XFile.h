/**
*	@file	XFile.h
*	@brief	
*	@date	2011.7.17(Sun) 10:33
*/

#ifndef INCLUDED_MAPIL_XFILE_H
#define INCLUDED_MAPIL_XFILE_H

#include "../CrossPlatform.h"

#ifdef LIB_STL
#include <vector>
#endif

#include <fstream>

#include "ModelFile.h"
#include "../Util/Color.hpp"
#include "../Math/Vector.hpp"
#include "../Type.h"

namespace MAPIL
{
	
	class XFile : public ModelFile
	{
	private:
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
			MapilInt32												m_NumVertex;
			std::vector < Vector3 < MapilFloat32 > >				m_Vertex;
			MapilInt32												m_NumIndex;
			MapilInt32												m_NumNormal;
			std::vector < Vector3 < MapilFloat32 > >				m_Normal;
			std::vector < Face >									m_Face;
			MapilInt32												m_NumTextureCoord;
			std::vector < Vector2 < MapilFloat32 > >				m_TextureCoord;
			MapilInt32												m_NumMaterial;
			std::vector < Material >								m_Material;
			MapilInt32												m_NumVertexColor;
			std::vector < ColorARGB < MapilFloat32 > >				m_VertexColor;
		};

		// Process "template" token.
		MapilVoid ProcessTemplateToken(	std::basic_ifstream < MapilChar >* pFIn,
												MapilChar* pToken,
												MapilInt32* pHierarchyNum );
		// Process "Mesh" token.
		MapilVoid ProcessMeshToken(	std::basic_ifstream < MapilChar >* pFIn,
									MapilChar* pToken,
									MapilInt32* pHierarchyNum );
		// Process "MeshMaterialList" token.
		MapilVoid ProcessMeshMaterialListToken(	std::basic_ifstream < MapilChar >* pFIn,
												MapilChar* pToken,
												MapilInt32* pHierarchyNum,
												Mesh* pMesh );
		// Process "Material" token.
		MapilVoid ProcessMaterialToken(	std::basic_ifstream < MapilChar >* pFIn,
										MapilChar* pToken,
										MapilInt32* pHierarchyNum,
										Mesh* pMesh,
										MapilInt32* pCount );
		// Process "MeshNormals" token.
		MapilVoid ProcessMeshNormalsToken(	std::basic_ifstream < MapilChar >* pFIn,
											MapilChar* pToken,
											MapilInt32* pHierarchyNum,
											Mesh* pMesh );
		// Process "MeshTextureCoords" token.
		MapilVoid ProcessMeshTextureCoordsToken(	std::basic_ifstream < MapilChar >* pFIn,
													MapilChar* pToken,
													MapilInt32* pHierarchyNum,
													Mesh* pMesh );
		// Process "MeshVertexColors" token.
		MapilVoid ProcessMeshVertexColorsToken(	std::basic_ifstream < MapilChar >* pFIn,
												MapilChar* pToken,
												MapilInt32* pHierarchyNum,
												Mesh* pMesh );
		// Search token.
		MapilVoid GetToken(	std::basic_ifstream < MapilChar >* pFIn,
							MapilChar* pToken );

		std::vector < Mesh >					m_Mesh;
	public:
		// Constructor.
		XFile();
		// Destructor.
		~XFile();
		// Load mesh from x-file.
		MapilVoid Load( const MapilChar* pFileName );
		// Copy to model data.
		MapilVoid CopyToModelData( ModelData* pData );

		MapilVoid Open( const MapilChar* pFileName, FileOpenMode mode );
		MapilVoid Close();
	};
}

#endif
