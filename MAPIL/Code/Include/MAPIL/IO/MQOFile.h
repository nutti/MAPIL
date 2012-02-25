/**
*	@file	MQOFile.h
*	@brief	
*	@date	2011.7.16(Sat) 10:27
*/

#ifndef INCLUDED_MAPIL_MQOFILE_H
#define INCLUDED_MAPIL_MQOFILE_H

#include "../CrossPlatform.h"

#include <fstream>

#include "ModelFile.h"
#include "../Type.h"

namespace MAPIL
{

	class MQOFile : public ModelFile
	{
	private:
		// Process "Scene" token.
		MapilVoid ProcessSceneToken(	std::basic_ifstream < MapilChar >* pFIn,
										MapilChar* pToken,
										MapilInt32* pHierarchyNum );
		// Process "Material" token.
		MapilVoid ProcessMaterialToken(	std::basic_ifstream < MapilChar >* pFIn,
										MapilChar* pToken,
										MapilInt32* pHierarchyNum );
		// Process "Object" token.
		MapilVoid ProcessObjectToken(	std::basic_ifstream < MapilChar >* pFIn,
										MapilChar* pToken,
										MapilInt32* pHierarchyNum );
		// Get token.
		MapilVoid GetToken(	std::basic_ifstream < MapilChar >* pFIn,
							MapilChar* pToken );
	protected:
		struct Material
		{
		public:
			MapilFloat32		m_Color[ 4 ];
			MapilFloat32		m_Diffuse;
			MapilFloat32		m_Ambient;
			MapilFloat32		m_Specular;
			MapilFloat32		m_Emissive;
			MapilFloat32		m_Power;
			MapilChar			m_TextureFileName[ 260 ];
		};
		struct Object
		{
		public:
			struct Face
			{
			public:
				MapilInt32						m_NumElement;
				MapilInt32						m_MaterialNum;
				MapilInt32						m_Index[ 4 ];
				MapilFloat32					m_TextureCoord[ 8 ];
			};
			MapilInt32							m_NumVertex;
			std::vector < MapilFloat32 >		m_Vertex;
			MapilInt32							m_NumFace;
			std::vector < Face >				m_Face;
		};

		std::vector < Object >				m_Object;
		MapilInt32							m_NumMaterial;
		std::vector < Material >			m_Material;
	public:
		// Constructor.
		MQOFile();
		// Destructor.
		~MQOFile();
		// Copy constructor.
		MQOFile( const MQOFile& mf );
		// Substitute. ( Overload of = operator. )
		MQOFile& operator=( const MQOFile& mf );
		// Load mesh from x-file.
		MapilVoid Load( const MapilChar* pFileName );
		// Copy to model data.
		MapilVoid CopyToModelData( ModelData* pData );

		MapilVoid Open( const MapilChar* pFileName, FileOpenMode mode );
		MapilVoid Close();
	};
}

#endif
