/**
*	@file	ModelFile.h
*	@brief	
*	@date	2011.7.15(Fri) 23:13
*/

#ifndef INCLUDED_MAPIL_MODELFILE_H
#define INCLUDED_MAPIL_MODELFILE_H

#include "../CrossPlatform.h"

#include "File.h"

#ifdef LIB_STL
#include <vector>
#endif

namespace MAPIL
{

	struct ModelData
	{
		struct Model
		{
			struct Material
			{
				MapilFloat32		m_Diffuse[ 4 ];
				MapilFloat32		m_Ambient[ 4 ];
				MapilFloat32		m_Specular[ 4 ];
				MapilFloat32		m_Emissive[ 4 ];
				MapilFloat32		m_Power;
				MapilChar			m_TexFileName[ 260 ];
			};
			struct Object
			{
				struct Face
				{
					MapilInt32		m_NumElm;
					MapilInt32		m_MtrlNum;
					MapilInt32		m_Index[ 4 ];
					MapilFloat32	m_TexCoord[ 8 ];
					MapilFloat32	m_Normal[ 12 ];
					MapilFloat32	m_VertexCol[ 16 ];
				};
				MapilInt32						m_NumVertex;
				std::vector < MapilFloat32 >	m_Vertex;
				MapilInt32						m_NumFace;
				std::vector < Face >			m_Face;
			};
			std::vector < Material >		m_Material;
			std::vector < Object >			m_Object;
		};
		std::vector < Model >		m_Model;
	};

	class ModelFile : public File
	{
	private:

	public:
		// Constructor.
		ModelFile();
		// Destructor.
		virtual ~ModelFile();
		virtual MapilVoid Load( const MapilChar* pFileName ) = 0;
		virtual MapilVoid CopyToModelData( ModelData* pData ) = 0;
	};
}

#endif
