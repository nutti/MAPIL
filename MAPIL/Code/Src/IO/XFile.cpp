/**
*	@file	XFile.cpp
*	@brief	
*	@date	2011.7.17(Sun) 10:47
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include <string.h>
#include <stdlib.h>
#include <iterator>
#include <algorithm>

#include "../../Include/MAPIL/IO/XFile.h"

#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/TChar.h"

#if defined ( OS_WIN_32BIT )
#pragma warning ( disable : 4996 )
#endif

namespace MAPIL
{
	// Constructor.
	XFile::XFile() :	m_Mesh()
	{
		m_Mesh.clear();
	}

	// Destrcutor.
	XFile::~XFile()
	{
		m_Mesh.clear();
	}

	// Process "template" token.
	MapilVoid XFile::ProcessTemplateToken(	std::basic_ifstream < MapilChar >* pFIn,
											MapilChar* pToken,
											MapilInt32* pHierarchyNum )
	{
		MapilInt32 first = *pHierarchyNum;

		// At first '{' must be found. If this procedure isn't here, first is always 0.
		while( 1 ){
			GetToken( pFIn, pToken );
			if( !strcmp( "{", pToken ) ){
				( *pHierarchyNum )++;
				break;
			}
		}

		// Skip "template" contents.
		while( *pHierarchyNum > first ){
			GetToken( pFIn, pToken );
			if( !strcmp( "{", pToken ) ){
				( *pHierarchyNum )++;
			}
			else if( !strcmp( "}", pToken ) ){
				( *pHierarchyNum )--;
			}
		}

		if( first != *pHierarchyNum ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessTemplateToken" ),
									TSTR( "Number of { doesn't correspond to that of }." ),
									-1 );
		}
	}

	// Process "Mesh" token.
	MapilVoid XFile::ProcessMeshToken(	std::basic_ifstream < MapilChar >* pFIn,
													MapilChar* pToken,
													MapilInt32* pHierarchyNum )
	{
		Mesh mesh;
		mesh.m_Face.clear();
		mesh.m_Material.clear();
		mesh.m_Normal.clear();
		mesh.m_NumIndex = 0;
		mesh.m_NumMaterial = 0;
		mesh.m_NumNormal = 0;
		mesh.m_NumTextureCoord = 0;
		mesh.m_NumVertex = 0;
		mesh.m_NumVertexColor = 0;
		mesh.m_TextureCoord.clear();
		mesh.m_Vertex.clear();
		mesh.m_VertexColor.clear();

		MapilInt32 first = *pHierarchyNum;

		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "{ isn't found." ), -1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get number of vertex.
		GetToken( pFIn, pToken );
		mesh.m_NumVertex = atoi( pToken );
				
		// Get vertex information.
		for( MapilInt32 i = 0; i < mesh.m_NumVertex; i++ ){
			MapilFloat32 val;
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			mesh.m_Vertex.push_back( val );
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			mesh.m_Vertex.push_back( val );
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			mesh.m_Vertex.push_back( val );
		}

		// Get number of index.
		GetToken( pFIn, pToken );
		mesh.m_NumIndex = atoi( pToken );

		// Get index information.
		for( MapilInt32 i = 0; i < mesh.m_NumIndex; i++ ){
			Mesh::Face face;
			GetToken( pFIn, pToken );
			face.m_NumElement = atoi( pToken );
			// If m_Tokens is '3', 4th component of m_Index[ i ] is -1.
			if( face.m_NumElement == 3 ){
				for( MapilInt32 j = 0; j < 3; j++ ){
					GetToken( pFIn, pToken );
					face.m_Index[ j ] = atoi( pToken );
				}
				face.m_Index[ 3 ] = -1;
			}
			else if( face.m_NumElement == 4 ){
				for( MapilInt32 j = 0; j < 4; j++ ){
					GetToken( pFIn, pToken );
					face.m_Index[ j ] = atoi( pToken );
				}
			}
			mesh.m_Face.push_back( face );
		}

		while( first < *pHierarchyNum ){
			GetToken( pFIn, pToken );
			if( !strcmp( pToken, "{" ) ){
				( *pHierarchyNum )++;
			}
			else if( !strcmp( pToken, "}" ) ){
				( *pHierarchyNum )--;
			}
			else if( !strcmp( pToken, "MeshMaterialList" ) ){
				ProcessMeshMaterialListToken( pFIn, pToken, pHierarchyNum, &mesh );
			}
			else if( !strcmp( pToken, "MeshNormals" ) ){
				ProcessMeshNormalsToken( pFIn, pToken, pHierarchyNum, &mesh );
			}
			else if( !strcmp( pToken, "MeshTextureCoords" ) ){
				ProcessMeshTextureCoordsToken( pFIn, pToken, pHierarchyNum, &mesh );
			}
			else if( !strcmp( pToken, "MeshVertexColors" ) ){
				ProcessMeshVertexColorsToken( pFIn, pToken, pHierarchyNum, &mesh );
			}
		}
				
		m_Mesh.push_back( mesh );
	}

	// Process "MeshMaterialList" token.
	MapilVoid XFile::ProcessMeshMaterialListToken(	std::basic_ifstream < MapilChar >* pFIn,
													MapilChar* pToken,
													MapilInt32* pHierarchyNum,
													Mesh* pMesh )
	{
		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessMeshMaterialListToken" ),
									TSTR( "{ isn't found." ),
									-1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get number of material.
		GetToken( pFIn, pToken );
		pMesh->m_NumMaterial = atoi( pToken );
		GetToken( pFIn, pToken );
		if( pMesh->m_NumIndex != atoi( pToken ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessMeshMaterialListToken" ),
									TSTR( "It doesn't correspond to number of index." ),
									-2 );
		}

		// Get material number
		for( MapilInt32 i = 0; i < pMesh->m_NumIndex; i++ ){
			GetToken( pFIn, pToken );
			pMesh->m_Face[ i ].m_MaterialNum = atoi( pToken );
		}

		MapilInt32 count = 0;
		for( MapilInt32 i = 0; i < pMesh->m_NumMaterial; i++ ){
			GetToken( pFIn, pToken );
			if( !strcmp( pToken, "Material" ) ){
				ProcessMaterialToken( pFIn, pToken, pHierarchyNum, pMesh, &count );
				count++;
			}
			else{
				( *pHierarchyNum )--;
			}
		}

		// Check '}'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "}" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessMeshMaterialListToken" ),
									TSTR( "} isn't found." ),
									-3 );
		}
		else{
			( *pHierarchyNum )--;
		}
	}

	// Process "Material" token.
	MapilVoid XFile::ProcessMaterialToken(	std::basic_ifstream < MapilChar >* pFIn,
											MapilChar* pToken,
											MapilInt32* pHierarchyNum,
											Mesh* pMesh,
											MapilInt32* pCount )
	{
		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessMaterialToken" ),
									TSTR( "{ isn't found." ),
									-1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get material information.
		// Get diffuse color.
		// Because x-file doesn't contain ambient color, ambient color is replaced by diffuse color.
		Mesh::Material material;
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Diffuse.m_R = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Diffuse.m_G = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Diffuse.m_B = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Diffuse.m_A = static_cast < MapilFloat32 > ( atof( pToken ) );
		//Get power.
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Power = static_cast < MapilFloat32 > ( atof( pToken ) );
		//Get specular color.
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Specular.m_R = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Specular.m_G = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Specular.m_B = static_cast < MapilFloat32 > ( atof( pToken ) );
		material.m_MaterialColor.m_Specular.m_A = 1.0f;
		// Get emissive color.
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Emissive.m_R = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Emissive.m_G = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Emissive.m_B = static_cast < MapilFloat32 > ( atof( pToken ) );
		material.m_MaterialColor.m_Emissive.m_A = 1.0f;

		ZeroObject( &material.m_TextureFileName, sizeof( material.m_TextureFileName ) );
		pMesh->m_Material.push_back( material );

		GetToken( pFIn, pToken );
		if( !strcmp( pToken, "TextureFilename" ) ){
			// Skip '{'
			GetToken( pFIn, pToken );
			if( strcmp( pToken, "{" ) ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "XFile" ),
										TSTR( "ProcessMaterialToken" ),
										TSTR( "{ isn't found." ),
										-2 );
			}
			else{
				( *pHierarchyNum )++;
			}
			// Get texture file name.
			GetToken( pFIn, pToken );
			strcpy( pMesh->m_Material[ *pCount ].m_TextureFileName, pToken );
					
			// Check '}' twice.
			for( MapilInt32 i = 0; i < 2; i++ ){
				GetToken( pFIn, pToken );
				if( strcmp( pToken, "}" ) ){
					throw MapilException(	TSTR( "Mapil" ),
											TSTR( "XFile" ),
											TSTR( "ProcessMaterialToken" ),
											TSTR( "} isn't found." ),
											-3 );
				}
				else{
					( *pHierarchyNum )--;
				}
			}
		}
		else if( !strcmp( pToken, "}" ) ){
			( *pHierarchyNum )--;
		}
		else{
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessMaterialToken" ),
									TSTR( "Unknown token is found." ),
									-4 );
		}
	}

	// Process "MeshNormals" token.
	MapilVoid XFile::ProcessMeshNormalsToken(	std::basic_ifstream < MapilChar >* pFIn,
												MapilChar* pToken,
												MapilInt32* pHierarchyNum,
												Mesh* pMesh )
	{
		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessMeshNormalsToken" ),
									TSTR( "{ isn't found." ),
									-1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get number of normal.
		GetToken( pFIn, pToken );
		pMesh->m_NumNormal = atoi( pToken );

		// Get normal information.
		for( MapilInt32 i = 0; i < pMesh->m_NumNormal; i++ ){
			MapilFloat32 val;
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			pMesh->m_Normal.push_back( val );
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			pMesh->m_Normal.push_back( val );
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			pMesh->m_Normal.push_back( val );
		}

		// Check number of index.
		MapilInt32 num;
		GetToken( pFIn, pToken );
		num = atoi( pToken );
		if( num != pMesh->m_NumIndex ){
			throw MapilException( CURRENT_POSITION, TSTR( "Number of index doesn't correspond to that of face." ), -2 );
		}

		for( MapilInt32 i = 0; i < pMesh->m_NumIndex; i++ ){
			GetToken( pFIn, pToken );
			// If m_Tokens is '3', 4th component of m_NormalNum[ i ] is -1.
			// This value is used later.
			if( !strcmp( "3", pToken ) ){
				for( MapilInt32 j = 0; j < 3; j++ ){
					GetToken( pFIn, pToken );
					pMesh->m_Face[ i ].m_NormalNum[ j ] = atoi( pToken );
				}
				pMesh->m_Face[ i ].m_NormalNum[ 3 ] = -1;
			}
			else if( !strcmp( "4", pToken ) ){
				for( MapilInt32 j = 0; j < 4; j++ ){
					GetToken( pFIn, pToken );
					pMesh->m_Face[ i ].m_NormalNum[ j ] = atoi( pToken );
				}
			}
		}

		// Check '}'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "}" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessMeshNormalsToken" ),
									TSTR( "} isn't found." ),
									-3 );
		}
		else{
			( *pHierarchyNum )--;
		}
	}

	// Process "MeshTextureCoords" token.
	MapilVoid XFile::ProcessMeshTextureCoordsToken(	std::basic_ifstream < MapilChar >* pFIn,
																MapilChar* pToken,
																MapilInt32* pHierarchyNum,
																Mesh* pMesh )
	{
		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessMeshTextureCoordsToken" ),
									TSTR( "{ isn't found." ),
									-1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get number of texture coordinate, and create texture coordinate buffer.
		GetToken( pFIn, pToken );
		pMesh->m_NumTextureCoord = atoi( pToken );

		// Get texture coordinate information.
		for( MapilInt32 i = 0; i < pMesh->m_NumTextureCoord; i++ ){
			MapilFloat32 val;
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			pMesh->m_TextureCoord.push_back( val );
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			pMesh->m_TextureCoord.push_back( val );
		}

		// Chech '}'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "}" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessMeshTextureCoordsToken" ),
									TSTR( "} isn't found." ),
									-2 );
		}
		else{
			( *pHierarchyNum )--;
		}
	}

	// Process "MeshVertexColors" token.
	MapilVoid XFile::ProcessMeshVertexColorsToken(	std::basic_ifstream < MapilChar >* pFIn,
													MapilChar* pToken,
													MapilInt32* pHierarchyNum,
													Mesh* pMesh )
	{
		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessMeshVertexColorsToken" ),
									TSTR( "{ isn't found." ),
									-1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get number of vertex color.
		GetToken( pFIn, pToken );
		pMesh->m_NumVertexColor = atoi( pToken );

		// Get vertex color information.
		for( MapilInt32 i = 0; i < pMesh->m_NumVertexColor; i++ ){
			MapilFloat32 val;
			// Skip number.
			GetToken( pFIn, pToken );
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			pMesh->m_VertexColor.push_back( val );
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			pMesh->m_VertexColor.push_back( val );
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			pMesh->m_VertexColor.push_back( val );
			GetToken( pFIn, pToken );
			val = static_cast < MapilFloat32 > ( atof( pToken ) );
			pMesh->m_VertexColor.push_back( val );
		}

		// Check '}'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "}" ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "XFile" ),
									TSTR( "ProcessMeshVertexColorsToken" ),
									TSTR( "} isn't found." ),
									-2 );
		}
		else{
			( *pHierarchyNum )--;
		}
	}

	// Get token.
	MapilVoid XFile::GetToken(	std::basic_ifstream < MapilChar >* pFIn,
								MapilChar* pToken )
	{
		MapilChar data;

		pFIn->get( data );
		while( !pFIn->eof() && ( data == ' ' || data == '\t' || data == '\n' || data == '\r' || data == ';' || data == ',' || data == '\"' ) ){
			pFIn->get( data );
		}

		MapilInt32 count = 0;
		pToken[ count ] = data;
		while( !pFIn->eof() && data != ' ' && data != '\t' && data != '\n' && data != '\r' && data != ';' && data != ',' && data != '{' && data != '}' && data != '\"' ){
			pFIn->get( data );
			if( pFIn->eof() || data == ' ' || data == '\t' || data == '\n' || data == '\r' || data == ';' || data == ',' || data == '{' || data == '}' || data == '\"' ){
				pFIn->seekg( -1, std::ios::cur );
				break;
			}
			count++;
			pToken[ count ] = data;
		}
		pToken[ count + 1 ] = '\0';
	}

	// Load mesh from x-file.
	MapilVoid XFile::Load( const MapilChar* pFileName )
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
			else if( !strcmp( tokens, "Header" ) ){
			}
			else if( !strcmp( tokens, "template" ) ){
				ProcessTemplateToken( &fIn, tokens, &hierarchyNum );
			}
			else if( !strcmp( tokens, "Mesh" ) ){
				ProcessMeshToken( &fIn, tokens, &hierarchyNum );
			}
		}

		fIn.close();
	}

	// Copy to model data.
	MapilVoid XFile::CopyToModelData( ModelData* pData )
	{

		for( MapilUInt32 i = 0; i < m_Mesh.size(); ++i ){
			ModelData::Model model;
			for( MapilUInt32 j = 0; j < m_Mesh[ i ].m_Material.size(); ++j ){
				ModelData::Model::Material mtrl;
				mtrl.m_Diffuse[ 0 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Diffuse.m_A;
				mtrl.m_Diffuse[ 1 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Diffuse.m_R;
				mtrl.m_Diffuse[ 2 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Diffuse.m_G;
				mtrl.m_Diffuse[ 3 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Diffuse.m_B;
				memcpy( mtrl.m_Ambient, mtrl.m_Diffuse, sizeof( mtrl.m_Ambient ) );
				mtrl.m_Specular[ 0 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Specular.m_A;
				mtrl.m_Specular[ 1 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Specular.m_R;
				mtrl.m_Specular[ 2 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Specular.m_G;
				mtrl.m_Specular[ 3 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Specular.m_B;
				mtrl.m_Emissive[ 0 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Emissive.m_A;
				mtrl.m_Emissive[ 1 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Emissive.m_R;
				mtrl.m_Emissive[ 2 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Emissive.m_G;
				mtrl.m_Emissive[ 3 ] = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Emissive.m_B;
				mtrl.m_Power = m_Mesh[ i ].m_Material[ j ].m_MaterialColor.m_Power;
				strcpy( mtrl.m_TexFileName, m_Mesh[ i ].m_Material[ j ].m_TextureFileName );
				model.m_Material.push_back( mtrl );
			}
			std::copy( m_Mesh[ i ].m_Vertex.begin(), m_Mesh[ i ].m_Vertex.end(), std::back_inserter( model.m_Vertices ) );
			std::copy( m_Mesh[ i ].m_Normal.begin(), m_Mesh[ i ].m_Normal.end(), std::back_inserter( model.m_Normals ) );
			std::copy( m_Mesh[ i ].m_TextureCoord.begin(), m_Mesh[ i ].m_TextureCoord.end(), std::back_inserter( model.m_TexCoords ) );
			std::copy( m_Mesh[ i ].m_VertexColor.begin(), m_Mesh[ i ].m_VertexColor.end(), std::back_inserter( model.m_VertexCols ) );
			for( MapilUInt32 j = 0; j < m_Mesh[ i ].m_Face.size(); ++j ){
				ModelData::Model::Face face;
				face.m_NumElm = m_Mesh[ i ].m_Face[ j ].m_NumElement;
				face.m_MtrlNum = m_Mesh[ i ].m_Face[ j ].m_MaterialNum;
				memcpy( face.m_VertexIndices, m_Mesh[ i ].m_Face[ j ].m_Index, sizeof( face.m_VertexIndices ) );
				memcpy( face.m_NormalIndices, m_Mesh[ i ].m_Face[ j ].m_NormalNum, sizeof( face.m_NormalIndices ) );
				memcpy( face.m_TexCoordIndices, m_Mesh[ i ].m_Face[ j ].m_Index, sizeof( face.m_TexCoordIndices ) );
				memcpy( face.m_VertexColIndices, m_Mesh[ i ].m_Face[ j ].m_Index, sizeof( face.m_VertexColIndices ) );
				model.m_Face.push_back( face );
			}
			pData->m_Model.push_back( model );
		}
	}

	MapilVoid XFile::Open( const MapilChar* pFileName, FileOpenMode mode )
	{
	}

	MapilVoid XFile::Close()
	{
	}

}