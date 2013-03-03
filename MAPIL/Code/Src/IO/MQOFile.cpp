/**
*	@file	MQOFile.cpp
*	@brief	
*	@date	2011.7.16(Sat) 10:18
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

#include "../../Include/MAPIL/IO/MQOFile.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/TChar.h"

#if defined ( OS_WIN_32BIT )
#pragma warning ( disable : 4996 )
#endif

namespace MAPIL
{
			
	// Constructor.
	MQOFile::MQOFile() :	m_Object(),
							m_NumMaterial( 0 ),
							m_Material()
	{
		m_Object.clear();
		m_Material.clear();
	}

	// Destructor.
	MQOFile::~MQOFile()
	{
		m_Object.clear();
		m_Material.clear();
		m_NumMaterial = 0;
	}

	// Copy constructor.
	MQOFile::MQOFile( const MQOFile& mf ) :	m_Object( mf.m_Object ),
											m_NumMaterial( mf.m_NumMaterial ),
											m_Material( mf.m_Material )
	{
	}

	// Substitute. ( Overload of = operator. )
	MQOFile& MQOFile::operator=( const MQOFile& mf )
	{
		m_Object		= mf.m_Object;
		m_NumMaterial	= mf.m_NumMaterial;
		m_Material		= mf.m_Material;

		return *this;
	}

	// Process "Scene" token.
	MapilVoid MQOFile::ProcessSceneToken(	std::basic_ifstream < MapilChar >* pFIn,
														MapilChar* pToken,
														MapilInt32* pHierarchyNum )
	{
		MapilInt32 prevHier = *pHierarchyNum;

		// Skip '{'
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "{ isn't found." ), -1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		while( prevHier < *pHierarchyNum ){
			GetToken( pFIn, pToken );
			if( !strcmp( pToken, "{" ) ){
				( *pHierarchyNum )++;
			}
			else if( !strcmp( pToken, "}" ) ){
				( *pHierarchyNum )--;
			}
		}
	}

	// Process "Material" token.
	MapilVoid MQOFile::ProcessMaterialToken(	std::basic_ifstream < MapilChar >* pFIn,
															MapilChar* pToken,
															MapilInt32* pHierarchyNum )
	{
		// Get number of material.
		GetToken( pFIn, pToken );
		m_NumMaterial = atoi( pToken );

		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "{ isn't found." ), -1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		Material mat;


		// Skip material name and line feed.
		GetToken( pFIn, pToken );
		GetToken( pFIn, pToken );
		while( strcmp( pToken, "}" ) && !pFIn->eof() ){
			// Check "col" token.
			if( !strcmp( pToken, "col" ) ){
				// Get color.
				for( MapilInt32 j = 0; j < 4; j++ ){
					GetToken( pFIn, pToken );
					mat.m_Color[ j ] = static_cast < MapilFloat32 > ( atof( pToken ) );
				}
			}
			// Check "dif" token.
			else if( !strcmp( pToken, "dif" ) ){
				// Get diffuse.
				GetToken( pFIn, pToken );
				mat.m_Diffuse = static_cast < MapilFloat32 > ( atof( pToken ) );
			}
			// Check "amb" token.
			else if( !strcmp( pToken, "amb" ) ){
				// Get ambient.
				GetToken( pFIn, pToken );
				mat.m_Ambient = static_cast < MapilFloat32 > ( atof( pToken ) );
			}
			// Check "emi" token.
			else if( !strcmp( pToken, "emi" ) ){
				// Get emissive.
				GetToken( pFIn, pToken );
				mat.m_Emissive = static_cast < MapilFloat32 > ( atof( pToken ) );
			}
			// Check "spc" token.
			else if( !strcmp( pToken, "spc" ) ){
				// Get specular.
				GetToken( pFIn, pToken );
				mat.m_Specular = static_cast < MapilFloat32 > ( atof( pToken ) );
			}
			// Check "power" token.
			else if( !strcmp( pToken, "power" ) ){
				// Get power.
				GetToken( pFIn, pToken );
				mat.m_Power = static_cast < MapilFloat32 > ( atof( pToken ) );
			}
			// Check "tex" token.
			else if( !strcmp( pToken, "tex" ) ){
				// Get texture file name.
				GetToken( pFIn, pToken );
				strcpy( mat.m_TextureFileName, pToken );
				//pFIn->seekg( -1, std::ios::cur );
				//ZeroObject( mat.m_TextureFileName, sizeof( mat.m_TextureFileName ) );
			}
			else if( !strcmp( pToken, "\n" ) ){
				m_Material.push_back( mat );
			}
				
			GetToken( pFIn, pToken );
		}

		( *pHierarchyNum )--;

		if( pFIn->eof() || m_Material.size() != m_NumMaterial ){
			throw MapilException( CURRENT_POSITION, TSTR( "Invalid Format." ), -9 );
		}
	}

	// Process "Object" token.
	MapilVoid MQOFile::ProcessObjectToken(	std::basic_ifstream < MapilChar >* pFIn,
														MapilChar* pToken,
														MapilInt32* pHierarchyNum )
	{
		Object obj;

		// Get object name.
		GetToken( pFIn, pToken );

		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "MQOFile" ),
									TSTR( "ProcessObjectToken" ),
									TSTR( "{ isn't found." ),
									-1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		while( strcmp( pToken, "vertex" ) ){
			// Get token.
			GetToken( pFIn, pToken );
			if( pFIn->eof() ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "MQOFile" ),
										TSTR( "ProcessObjectToken" ),
										TSTR( "\"vertex\" token isn't found." ),
										-2 );
			}
		}

		// Get number of vertex.
		GetToken( pFIn, pToken );
		obj.m_NumVertex = static_cast < MapilInt32 > ( atoi( pToken ) );

		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "MQOFile" ),
									TSTR( "ProcessObjectToken" ),
									TSTR( "{ isn't found." ),
									-3 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Skip line feed.
		GetToken( pFIn, pToken );

		MapilFloat32 buf;

		for( MapilInt32 i = 0; i < obj.m_NumVertex; i++ ){
			for( MapilInt32 j = 0; j < 3; j++ ){
				GetToken( pFIn, pToken );
				buf = static_cast < MapilFloat32 > ( atof( pToken ) );
				obj.m_Vertex.push_back( buf );
			}

			// Skip line feed.
			GetToken( pFIn, pToken );
		}
				
		// Chech '}' token.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "}" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "MQOFile" ),
									TSTR( "ProcessObjectToken" ),
									TSTR( "} isn't found." ),
									-4 );
		}
		else{
			( *pHierarchyNum )--;
		}

		// Skip line feed.
		GetToken( pFIn, pToken );

		// Check "face" token.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "face" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "MQOFile" ),
									TSTR( "ProcessObjectToken" ),
									TSTR( "\"face\" token isn't found." ),
									-5 );
		}

		// Get number of face.
		GetToken( pFIn, pToken );
		obj.m_NumFace = atoi( pToken );

		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "MQOFile" ),
									TSTR( "ProcessObjectToken" ),
									TSTR( "{ isn't found." ),
									-6 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Skip line feed.
		GetToken( pFIn, pToken );
				

		bool first = true;
		
		GetToken( pFIn, pToken );
		Object::Face face;
		while( !pFIn->eof() && strcmp( pToken, "}" ) ){
			// Get number of element.
			if( first ){
				face.m_NumElement = atoi( pToken );
				first = false;
			}
			else if( !strcmp( pToken, "V" ) ){
				// Get index.
				for( MapilInt32 j = 0; j < 4; j++ ){
					if( j < face.m_NumElement ){
						GetToken( pFIn, pToken );
						face.m_Index[ j ] = atoi( pToken );	
					}
					else{
						face.m_Index[ j ] = -1;
					}
				}
			}
			// Check "M" token.
			else if( !strcmp( pToken, "M" ) ){
				// Get material number.
				GetToken( pFIn, pToken );
				face.m_MaterialNum = atoi( pToken );
			}
			// Check "UV" token.
			else if( !strcmp( pToken, "UV" ) ){
				// Get texture coordinate.
				for( MapilInt32 j = 0; j < 8; j++ ){
					if( j < face.m_NumElement * 2 ){
						GetToken( pFIn, pToken );
						face.m_TextureCoord[ j ] = static_cast < MapilFloat32 > ( atof( pToken ) );
					}
					else{
						face.m_TextureCoord[ j ] = -1;
					}						
				}
			}
			else if( !strcmp( pToken, "\n" ) ){
				obj.m_Face.push_back( face );
				first = true;
			}
			GetToken( pFIn, pToken );
		}

		( *pHierarchyNum )--;

		if( pFIn->eof() || obj.m_NumFace != obj.m_Face.size() ){
			throw MapilException( CURRENT_POSITION, TSTR( "Invalid Format." ), -9 );
		}

		// Skip line feed.
		GetToken( pFIn, pToken );

		m_Object.push_back( obj );
	}

	// Get token.
	MapilInt32 MQOFile::GetToken(	std::basic_ifstream < MapilChar >* pFIn,
												MapilChar* pToken )
	{
		MapilChar data;

		pFIn->get( data );
		while( !pFIn->eof() && ( data == ' ' || data == '\t' /*|| data == '\n'*/ || data == '\r' || data == ';' || data == ',' || data == '\"' || data == '(' || data == ')' ) ){
			pFIn->get( data );
		}
		if( data == '\n' ){
			pToken[ 0 ] = data;
			pToken[ 1 ] = '\0';
			return 1;
		}

		MapilInt32 count = 0;
		pToken[ count ] = data;
		while( !pFIn->eof() && data != ' ' && data != '\t' /*&& data != '\n'*/ && data != '\r' && data != ';' && data != ',' && data != '{' && data != '}' && data != '\"' && data != '(' && data != ')' ){
			pFIn->get( data );
			if( pFIn->eof() || data == ' ' || data == '\t' || data == '\n' || data == '\r' || data == ';' || data == ',' || data == '{' || data == '}' || data == '\"' || data == '(' || data == ')' ){
				pFIn->seekg( -1, std::ios::cur );
				break;
			}
			count++;
			pToken[ count ] = data;
		}

		pToken[ count + 1 ] = '\0';

		return 0;
	}

	// Load mesh from x-file.
	MapilVoid MQOFile::Load( const MapilChar* pFileName )
	{
		std::basic_ifstream < MapilChar > fIn;
		fIn.open( pFileName, std::ios::in | std::ios::binary );
				
		MapilChar tokens[ 1000 ];
		MapilInt32 hierarchyNum = 0;

		ZeroObject( &tokens, sizeof( tokens ) );

		while( !fIn.eof() ){
			// Get token.
			GetToken( &fIn, tokens );

			if( fIn.eof() ){
				break;
			}
			if( !strcmp( tokens, "{" ) ){
				hierarchyNum++;
			}
			else if( !strcmp( tokens, "}" ) ){
				hierarchyNum--;
			}
			else if( !strcmp( tokens, "Scene" ) ){
				ProcessSceneToken( &fIn, tokens, &hierarchyNum );
			}
			else if( !strcmp( tokens, "Material" ) ){
				ProcessMaterialToken( &fIn, tokens, &hierarchyNum );
			}
			else if( !strcmp( tokens, "Object" ) ){
				ProcessObjectToken( &fIn, tokens, &hierarchyNum );
			}
		}

		fIn.close();
	}

	// Copy to model data.
	MapilVoid MQOFile::CopyToModelData( ModelData* pData )
	{
		ModelData::Model model;
		
		// Copy material to ModelData.
		for( MapilUInt32 i = 0; i < m_Material.size(); ++i ){
			ModelData::Model::Material mtrl;
			mtrl.m_Diffuse[ 0 ] = m_Material[ i ].m_Diffuse;
			mtrl.m_Diffuse[ 1 ] = mtrl.m_Diffuse[ 2 ] = mtrl.m_Diffuse[ 3 ] = -1.0f;
			mtrl.m_Ambient[ 0 ] = m_Material[ i ].m_Ambient;
			mtrl.m_Ambient[ 1 ] = mtrl.m_Ambient[ 2 ] = mtrl.m_Ambient[ 3 ] = -1.0f;
			mtrl.m_Specular[ 0 ] = m_Material[ i ].m_Specular;
			mtrl.m_Specular[ 1 ] = mtrl.m_Specular[ 2 ] = mtrl.m_Specular[ 3 ] = -1.0f;
			mtrl.m_Emissive[ 0 ] = m_Material[ i ].m_Emissive;
			mtrl.m_Emissive[ 1 ] = mtrl.m_Emissive[ 2 ] = mtrl.m_Emissive[ 3 ] = -1.0f;
			mtrl.m_Power = m_Material[ i ].m_Power;
			strcpy( mtrl.m_TexFileName, m_Material[ i ].m_TextureFileName );
			model.m_Material.push_back( mtrl );
		}

		// Copy object to ModelData.
		for( MapilUInt32 i = 0; i < m_Object.size(); ++i ){
			ModelData::Model::Object obj;
			obj.m_NumVertex = m_Object[ i ].m_NumVertex;
			for( MapilUInt32 j = 0; j < m_Object[ i ].m_Vertex.size(); ++j ){
				obj.m_Vertex.push_back( m_Object[ i ].m_Vertex[ j ] );
			}
			obj.m_NumFace = m_Object[ i ].m_NumFace;
			for( MapilUInt32 j = 0; j < m_Object[ i ].m_Face.size(); ++j ){
				ModelData::Model::Object::Face face;
				face.m_NumElm = m_Object[ i ].m_Face[ j ].m_NumElement;
				face.m_MtrlNum = m_Object[ i ].m_Face[ j ].m_MaterialNum;
				memcpy( face.m_Index, m_Object[ i ].m_Face[ j ].m_Index, sizeof( face.m_Index ) );
				memcpy( face.m_TexCoord, m_Object[ i ].m_Face[ j ].m_TextureCoord, sizeof( face.m_TexCoord ) );
				for( MapilInt32 index = 0; index < sizeof( face.m_Normal ) / sizeof( face.m_Normal[ 0 ] ); ++index ){
					face.m_Normal[ index ] = -1.0f;
				}
				memcpy( face.m_VertexCol, m_Material[ m_Object[ i ].m_Face[ j ].m_MaterialNum ].m_Color, sizeof( face.m_VertexCol ) );
				obj.m_Face.push_back( face );
			}
			model.m_Object.push_back( obj );
		}

		pData->m_Model.push_back( model );

		//for( MapilUInt32 i = 0; i < m_Object.size(); ++i ){
		//	ModelData::Object obj;
		//	obj.m_NumVertex = m_Object[ i ].m_NumVertex;
		//	for( MapilInt32 j = 0; j < m_Object[ i ].m_Vertex.size(); ++j ){
		//		obj.m_Vertex.push_back( m_Object[ i ].m_Vertex[ j ] );
		//	}
		//	obj.m_NumFace = m_Object[ i ].m_NumFace;
		//	for( MapilUInt32 j = 0; j < m_Object[ i ].m_Face.size(); ++j ){
		//		ModelData::Object::Face face;
		//		face.m_NumElement = m_Object[ i ].m_Face[ j ].m_NumElement;
		//		face.m_MaterialNum = m_Object[ i ].m_Face[ j ].m_MaterialNum;
		//		memcpy( face.m_Index, m_Object[ i ].m_Face[ j ].m_Index, sizeof( face.m_Index ) );
		//		memcpy( face.m_TextureCoord, m_Object[ i ].m_Face[ j ].m_TextureCoord, sizeof( face.m_TextureCoord ) );
		//		obj.m_Face.push_back( face );
		//	}
		//	pData->m_Object.push_back( obj );
		//}
	}

	MapilVoid MQOFile::Open( const MapilChar* pFileName, FileOpenMode mode )
	{
		// This function will be revised.
	}

	MapilVoid MQOFile::Close()
	{
		// This function will be revised.
	}
}