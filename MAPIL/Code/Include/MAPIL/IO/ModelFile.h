/**
*	@file	ModelFile.h
*	@brief	
*	@date	2011.7.15(Fri) 23:13
*/

#ifndef INCLUDED_MAPIL_MODELFILE_H
#define INCLUDED_MAPIL_MODELFILE_H

#include "../CrossPlatform.h"

#include "File.h"
#include "../Util/MapilObject.h"

#if defined ( LIB_STL )
#include <vector>
#include <map>
#endif

#include "../Math/Matrix.hpp"

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
			struct Face
			{
				MapilInt32		m_NumElm;
				MapilInt32		m_MtrlNum;
			};

			std::vector < MapilFloat32 >	m_Vertices;
			std::vector < MapilFloat32 >	m_TexCoords;
			std::vector < MapilFloat32 >	m_Normals;
			std::vector < MapilFloat32 >	m_VertexCols;
			std::vector < MapilInt32 >		m_Indices;
			std::vector < Face >			m_Face;
			MapilInt32						m_FaceTotal;

			std::vector < Material >		m_Material;
		};
		std::vector < Model >		m_Model;
	};

	struct AnimModelData
	{
		struct Frame
		{
			ModelData::Model				m_Mesh;			///< Mesh.
			Matrix4x4 < MapilFloat32 >		m_TransMat;		///< Translation matrix.
			Frame*							m_pFirstChild;	///< First of child.
			Frame*							m_pSibling;		///< Sibling.
			std::basic_string < MapilChar >	m_Name;			///< Frame name.
		};
		struct Animation
		{
			// Animation set.
			struct AnimSet
			{
				// Animation item.
				struct AnimItem
				{
					// Animation key.
					struct Key
					{
						MapilInt32					m_Type;			///< Animation type.
						// Translation value.
						struct TransValue
						{
							MapilFloat32			m_Elm[ 4 ];
						};
						std::map < MapilInt32, TransValue >		m_Entries;		///< Entries.
					};
					std::map < std::basic_string < MapilChar >, std::vector < Key > >	m_Keys;		///< Keys
				};
				std::map < std::basic_string < MapilChar >, AnimItem >	m_AnimItems;	///< Animation items.
			};
			std::map < std::basic_string < MapilChar >, AnimSet >	m_AnimSetList;	///< Animation set list.
		};

		Frame		m_RootFame;		// Root frame.
		Animation	m_Animation;	// Animation data.
	};

	class ModelFile : public MapilObject
	{
	private:

	public:
		// Constructor.
		ModelFile();
		// Destructor.
		virtual ~ModelFile();
		/**
		*	@brief				Open the file.
		*	@param pFileName	File name to be opened.
		*	@param mode			Open mode.
		*/
		virtual MapilVoid Open( const MapilChar* pFileName, FileOpenMode mode ) = 0;
		/**
		*	@brief Close the file.
		*/
		virtual MapilVoid Close() = 0;
		virtual MapilVoid Load( const MapilChar* pFileName ) = 0;
		virtual MapilVoid CopyToModelData( ModelData* pData ) = 0;
	};
}

#endif
