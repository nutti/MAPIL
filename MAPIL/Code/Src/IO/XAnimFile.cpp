/**
*	@file	XAnimFile.cpp
*	@brief	
*	@date	2013.3.3(Sun) 15:37
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include <string.h>
#include <stdlib.h>
#include <iterator>

#include "../../Include/MAPIL/IO/XAnimFile.h"

#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/TChar.h"

#if defined ( OS_WIN_32BIT )
#pragma warning ( disable : 4996 )
#endif

namespace MAPIL
{
	// Constructor.
	XAnimFile::XAnimFile() :	m_RootFrame(),
								m_Anim(),
								m_MatStack()
	{
		ClearFrame( &m_RootFrame );
		ClearAnim( &m_Anim );
		while( !m_MatStack.empty() ){
			m_MatStack.pop();
		}
	}

	// Destructor.
	XAnimFile::~XAnimFile()
	{
		while( !m_MatStack.empty() ){
			m_MatStack.pop();
		}
		DeleteFrame();
		ClearFrame( &m_RootFrame );
		ClearAnim( &m_Anim );
	}

	// Clear Frame structure.
	MapilVoid XAnimFile::ClearFrame( Frame* pFrame )
	{
		pFrame->m_FrameName.clear();

		pFrame->m_Mesh.m_Face.clear();
		pFrame->m_Mesh.m_Material.clear();
		pFrame->m_Mesh.m_Normal.clear();
		pFrame->m_Mesh.m_NumIndex = 0;
		pFrame->m_Mesh.m_NumMaterial = 0;
		pFrame->m_Mesh.m_NumNormal = 0;
		pFrame->m_Mesh.m_NumTextureCoord = 0;
		pFrame->m_Mesh.m_NumVertex = 0;
		pFrame->m_Mesh.m_NumVertexColor = 0;
		pFrame->m_Mesh.m_TextureCoord.clear();
		pFrame->m_Mesh.m_Vertex.clear();
		pFrame->m_Mesh.m_VertexColor.clear();

		pFrame->m_pFirstChild = NULL;
				
		pFrame->m_pSibling = NULL;
	}

	// Clear Anim structure.
	MapilVoid XAnimFile::ClearAnim( Anim* pAnim )
	{
		pAnim->m_AnimSetMap.clear();
	}

	// Get token.
	MapilVoid XAnimFile::GetToken(	std::basic_ifstream < MapilChar >* pFIn, MapilChar* pToken )
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

	// Process "template" token.
	MapilVoid XAnimFile::ProcessTemplateToken(	std::basic_ifstream < MapilChar >* pFIn,
												MapilChar* pToken,
												MapilInt32* pHierarchyNum )
	{
		MapilInt32 hierNum = *pHierarchyNum;

		while( 1 ){
			GetToken( pFIn, pToken );
			if( !strcmp( pToken, "{" ) ){
				( *pHierarchyNum )++;
				break;
			}
		}

		while( hierNum < *pHierarchyNum ){
			GetToken( pFIn, pToken );
			if( !strcmp( pToken, "{" ) ){
				( *pHierarchyNum )++;
			}
			else if( !strcmp( pToken, "}" ) ){
				( *pHierarchyNum )--;
			}
		}
	}

	// Process "Frame" token.
	MapilVoid XAnimFile::ProcessFrameToken(	std::basic_ifstream < MapilChar >* pFIn,
											MapilChar* pToken,
											MapilInt32* pHierarchyNum,
											Frame* pFrame )
	{
		MapilBool isFirstTime = MapilTrue;
		MapilInt32 hierNum = *pHierarchyNum;

		while( !pFIn->eof() && hierNum <= *pHierarchyNum && ( *pHierarchyNum != 0 || isFirstTime ) ){
			GetToken( pFIn, pToken );
			if( pFIn->eof() ){
				break;
			}
			if( !strcmp( pToken, "{" ) ){
				( *pHierarchyNum )++;
				isFirstTime = MapilFalse;
			}
			else if( !strcmp( pToken, "}" ) ){
				( *pHierarchyNum )--;
			}
			else if( !strcmp( pToken, "FrameTransformMatrix" ) ){
				ProcessFrameTransformMatrixToken( pFIn, pToken, pHierarchyNum, pFrame );
			}
			else if( !strcmp( pToken, "Frame" ) ){
				if( hierNum < *pHierarchyNum ){
					pFrame->m_pFirstChild = new Frame();
					ClearFrame( pFrame->m_pFirstChild );
					ProcessFrameToken( pFIn, pToken, pHierarchyNum, pFrame->m_pFirstChild );
				}
				else if( hierNum == *pHierarchyNum ){
					pFrame->m_pSibling = new Frame();
					ClearFrame( pFrame->m_pSibling );
					ProcessFrameToken( pFIn, pToken, pHierarchyNum, pFrame->m_pSibling );
				}
			}
			else if( !strcmp( pToken, "Mesh" ) ){
				ProcessMeshToken( pFIn, pToken, pHierarchyNum, pFrame );
			}
			else if( !strcmp( pToken, "AnimationSet" ) ){
				break;
			}
			else{
				// Get frame name.
				pFrame->m_FrameName = pToken;
			}
		}
	}

	// Process "FrameTransformMatrix" token.
	MapilVoid XAnimFile::ProcessFrameTransformMatrixToken(	std::basic_ifstream < MapilChar >* pFIn,
															MapilChar* pToken,
															MapilInt32* pHierarchyNum,
															Frame* pFrame )
	{
		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "{ isn't found." ), -1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get transform matrix information.
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_11 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_12 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_13 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_14 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_21 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_22 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_23 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_24 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_31 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_32 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_33 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_34 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_41 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_42 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_43 = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		pFrame->m_TransMat.m_44 = static_cast < MapilFloat32 > ( atof( pToken ) );

		// Check '}'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "}" ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "} isn't found." ), -2 );
		}
		else{
			( *pHierarchyNum )--;
		}
	}

	// Process "Mesh" token.
	MapilVoid XAnimFile::ProcessMeshToken(	std::basic_ifstream < MapilChar >* pFIn,
											MapilChar* pToken,
											MapilInt32* pHierarchyNum,
											Frame* pFrame )
	{
		MapilInt32 hierNum = *pHierarchyNum;

		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			GetToken( pFIn, pToken );
			if( strcmp( pToken, "{" ) ){
				throw MapilException( CURRENT_POSITION, TSTR( "{ isn't found." ), -1 );
			}
			else{
				( *pHierarchyNum )++;
			}
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get number of vertex.
		GetToken( pFIn, pToken );
		pFrame->m_Mesh.m_NumVertex = atoi( pToken );

		// Get vertex information.
		for( MapilInt32 i = 0; i < pFrame->m_Mesh.m_NumVertex; i++ ){
			Vector3 < MapilFloat32 > vertex;
			GetToken( pFIn, pToken );
			vertex.m_X = static_cast < MapilFloat32 > ( atof( pToken ) );
			GetToken( pFIn, pToken );
			vertex.m_Y = static_cast < MapilFloat32 > ( atof( pToken ) );
			GetToken( pFIn, pToken );
			vertex.m_Z = static_cast < MapilFloat32 > ( atof( pToken ) );
			pFrame->m_Mesh.m_Vertex.push_back( vertex );
		}

		// Get number of index.
		GetToken( pFIn, pToken );
		pFrame->m_Mesh.m_NumIndex = atoi( pToken );

		// Get index information.
		for( MapilInt32 i = 0; i < pFrame->m_Mesh.m_NumIndex; i++ ){
			Frame::Mesh::Face face;
			GetToken( pFIn, pToken );
			// If m_Tokens is '3', 4th component of m_Index[ j ] is -1.
			if( !strcmp( pToken, "3" ) ){
				for( MapilInt32 j = 0; j < 3; j++ ){
					GetToken( pFIn, pToken );
					face.m_Index[ j ] = atoi( pToken );
				}
				face.m_Index[ 3 ] = -1;
			}
			else if( !strcmp( pToken, "4" ) ){
				for( MapilInt32 j = 0; j < 4; j++ ){
					GetToken( pFIn, pToken );
					face.m_Index[ j ] = atoi( pToken );
				}
			}
			pFrame->m_Mesh.m_Face.push_back( face );
		}


		while( hierNum < *pHierarchyNum && !pFIn->eof() ){
			GetToken( pFIn, pToken );
			if( !strcmp( pToken, "{" ) ){
				( *pHierarchyNum )++;
			}
			else if( !strcmp( pToken, "}" ) ){
				( *pHierarchyNum )--;
			}
			else if( !strcmp( pToken, "MeshMaterialList" ) ){
				ProcessMeshMaterialListToken( pFIn, pToken, pHierarchyNum, pFrame );
			}
			else if( !strcmp( pToken, "MeshNormals" ) ){
				ProcessMeshNormalsToken( pFIn, pToken, pHierarchyNum, pFrame);
			}
			else if( !strcmp( pToken, "MeshTextureCoords" ) ){
				ProcessMeshTextureCoordsToken( pFIn, pToken, pHierarchyNum, pFrame );
			}
		}
	}

	// Process "MeshMaterialList" token.
	MapilVoid XAnimFile::ProcessMeshMaterialListToken(	std::basic_ifstream < MapilChar >* pFIn,
														MapilChar* pToken,
														MapilInt32* pHierarchyNum,
														Frame* pFrame )
	{
		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "{ isn't found." ), -1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get number of material.
		GetToken( pFIn, pToken );
		pFrame->m_Mesh.m_NumMaterial = atoi( pToken );
		GetToken( pFIn, pToken );
		if( pFrame->m_Mesh.m_NumIndex != atoi( pToken ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Number of index doesn't correspond to that of material." ), -2 );
		}

		// Get material number.
		for( MapilInt32 i = 0; i < pFrame->m_Mesh.m_NumIndex; i++ ){
			GetToken( pFIn, pToken );
			pFrame->m_Mesh.m_Face[ i ].m_MaterialNum = atoi( pToken );
		}

		for( MapilInt32 i = 0; i < pFrame->m_Mesh.m_NumMaterial; i++ ){
			GetToken( pFIn, pToken );
			if( !strcmp( pToken, "Material" ) ){
				ProcessMaterialToken( pFIn, pToken, pHierarchyNum, pFrame );
			}
			else{
				( *pHierarchyNum )--;
			}
		}

		// Check '}'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "}" ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "} isn't found." ), -3 );
		}
		else{
			( *pHierarchyNum )--;
		}
	}

	// Process "Material" token.
	MapilVoid XAnimFile::ProcessMaterialToken(	std::basic_ifstream < MapilChar >* pFIn,
												MapilChar* pToken,
												MapilInt32* pHierarchyNum,
												Frame* pFrame )
	{
		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "{ isn't found." ), -1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get material information.
		// Get diffuse color.
		Frame::Mesh::Material material;
		material.m_TextureFileName[ 0 ] = '\0';
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Diffuse.m_R = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Diffuse.m_G = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Diffuse.m_B = static_cast < MapilFloat32 > ( atof( pToken ) );
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Diffuse.m_A = static_cast < MapilFloat32 > ( atof( pToken ) );
		// Get power.
		GetToken( pFIn, pToken );
		material.m_MaterialColor.m_Power = static_cast < MapilFloat32 > ( atof( pToken ) );
		// Get specular color.
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

		GetToken( pFIn, pToken );
		if( !strcmp( pToken, "TextureFileName" ) ){
			// Skip '{'.
			GetToken( pFIn, pToken );
			if( strcmp( pToken, "{" ) ){
				throw MapilException( CURRENT_POSITION, TSTR( "{ isn't found." ), -2 );
			}
			else{
				( *pHierarchyNum )++;
			}
			// Get texture file name.
			GetToken( pFIn, pToken );
			strcpy( material.m_TextureFileName, pToken );

			// Check '}' twice.
			for( MapilInt32 i = 0; i < 2; i++ ){
				GetToken( pFIn, pToken );
				if( strcmp( pToken, "}" ) ){
					throw MapilException( CURRENT_POSITION, TSTR( "} isn't found." ), -3 );
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
			throw MapilException( CURRENT_POSITION, TSTR( "Unknown token is found." ), -4 );
		}

		pFrame->m_Mesh.m_Material.push_back( material );
	}

	// Process "MeshNormals" token.
	MapilVoid XAnimFile::ProcessMeshNormalsToken(	std::basic_ifstream < MapilChar >* pFIn,
													MapilChar* pToken,
													MapilInt32* pHierarchyNum,
													Frame* pFrame )
	{
		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "{ isn't found." ), -1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get number of normal.
		GetToken( pFIn, pToken );
		pFrame->m_Mesh.m_NumNormal = atoi( pToken );

		// Get normal information.
		for( MapilInt32 i = 0; i < pFrame->m_Mesh.m_NumNormal; i++ ){
			Vector3 < MapilFloat32 > normal;
			GetToken( pFIn, pToken );
			normal.m_X = static_cast < MapilFloat32 > ( atof( pToken ) );
			GetToken( pFIn, pToken );
			normal.m_Y = static_cast < MapilFloat32 > ( atof( pToken ) );
			GetToken( pFIn, pToken );
			normal.m_Z = static_cast < MapilFloat32 > ( atof( pToken ) );
			pFrame->m_Mesh.m_Normal.push_back( normal );
		}

		// Chech number of index.
		MapilInt32 num;
		GetToken( pFIn, pToken );
		num = atoi( pToken );
		if( num != pFrame->m_Mesh.m_NumIndex ){
			throw MapilException( CURRENT_POSITION, TSTR( "Number of index doesn't correspond to that of face." ), -2 );
		}

		for( MapilInt32 i = 0; i < pFrame->m_Mesh.m_NumIndex; i++ ){
			GetToken( pFIn, pToken );
			pFrame->m_Mesh.m_Face[ i ].m_NumElement = atoi( pToken );
			// If m_Tokens is '3', 4th component of m_NormalNum[ j ] is -1.
			if( pFrame->m_Mesh.m_Face[ i ].m_NumElement == 3 ){
				for( MapilInt32 j = 0; j < 3; j++ ){
					GetToken( pFIn, pToken );
					pFrame->m_Mesh.m_Face[ i ].m_NormalNum[ j ] = atoi( pToken );
				}
				pFrame->m_Mesh.m_Face[ i ].m_NormalNum[ 3 ] = -1;
			}
			else if( pFrame->m_Mesh.m_Face[ i ].m_NumElement == 4 ){
				for( MapilInt32 j = 0; j < 4; j++ ){
					GetToken( pFIn, pToken );
					pFrame->m_Mesh.m_Face[ i ].m_NormalNum[ j ] = atoi( pToken );
				}
			}
		}

		// Check '}'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "}" ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "} isn't found." ), -3 );
		}
		else{
			( *pHierarchyNum )--;
		}
	}

	// Process "MeshTextureCoords" token.
	MapilVoid XAnimFile::ProcessMeshTextureCoordsToken(	std::basic_ifstream < MapilChar >* pFIn,
														MapilChar* pToken,
														MapilInt32* pHierarchyNum,
														Frame* pFrame )
	{
		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException(	TSTR( "Nutti::Lib::FileIO" ),
													TSTR( "XAnimFile" ),
													TSTR( "ProcessMeshTextureCoordsToken" ),
													TSTR( "{ isn't found." ),
													-1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get number of texture coordinate.
		GetToken( pFIn, pToken );
		pFrame->m_Mesh.m_NumTextureCoord = atoi( pToken );

		// Get texture coordinate information.
		for( MapilInt32 i = 0; i < pFrame->m_Mesh.m_NumTextureCoord; i++ ){
			Vector2 < MapilFloat32 > texCoord;
			GetToken( pFIn, pToken );
			texCoord.m_X = static_cast < MapilFloat32 > ( atof( pToken ) );
			GetToken( pFIn, pToken );
			texCoord.m_Y = static_cast < MapilFloat32 > ( atof( pToken ) );
			pFrame->m_Mesh.m_TextureCoord.push_back( texCoord );
		}

		// Check '}'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "}" ) ){
			throw MapilException(	TSTR( "Nutti::Lib::FileIO" ),
													TSTR( "XAnimFile" ),
													TSTR( "ProcessMeshTextureCoordsToken" ),
													TSTR( "} isn't found." ),
													-2 );
		}
		else{
			( *pHierarchyNum )--;
		}
	}

	// Process "AnimationSet" token.
	MapilVoid XAnimFile::ProcessAnimationSetToken(	std::basic_ifstream < MapilChar >* pFIn,
																MapilChar* pToken,
																MapilInt32* pHierarchyNum )
	{
		MapilInt32 first = *pHierarchyNum;
		std::basic_string < MapilChar > animSetName;
		Anim::AnimationSet animSet;

		// Get animation set name.
		// 複数のアニメーションを読み込めるように修正すべき。
		GetToken( pFIn, pToken );
		animSetName = pToken;

		// Skip '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException(	TSTR( "Nutti::Lib::FileIO" ),
													TSTR( "XAnimFile" ),
													TSTR( "ProcessAnimationSetToken" ),
													TSTR( "{ isn't found." ),
													-1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		while( first < *pHierarchyNum ){
			GetToken( pFIn, pToken );
			if( !strcmp( pToken, "Animation" ) ){
				ProcessAnimationToken( pFIn, pToken, &animSet, pHierarchyNum );
			}
			else if( !strcmp( pToken, "}" ) ){
				( *pHierarchyNum )--;
			}
		}
				
		m_Anim.m_AnimSetMap.insert( std::map < std::basic_string < MapilChar >, Anim::AnimationSet > ::value_type( animSetName, animSet ) );
	}

	// Process "Animation" token.
	MapilVoid XAnimFile::ProcessAnimationToken(	std::basic_ifstream < MapilChar >* pFIn,
															MapilChar* pToken,
															Anim::AnimationSet* pAnimSet,
															MapilInt32* pHierarchyNum )
	{
		MapilInt32 first = *pHierarchyNum;
		Anim::AnimationSet::Animation anim;
		std::basic_string < MapilChar > meshName;

		// Get animation name.
		GetToken( pFIn, pToken );
		anim.m_AnimName = pToken;

		// Check '{' twice.
		for( MapilInt32 i = 0; i < 2; i++ ){
			GetToken( pFIn, pToken );
			if( strcmp( pToken, "{" ) ){
				throw MapilException(	TSTR( "Nutti::Lib::FileIO" ),
														TSTR( "XAnimFile" ),
														TSTR( "ProcessAnimationToken" ),
														TSTR( "{ isn't found." ),
														-1 );
			}
			else{
				( *pHierarchyNum )++;
			}
		}
				
		// Get mesh name.
		GetToken( pFIn, pToken );
		meshName = pToken;

		// Check '}'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "}" ) ){
			throw MapilException(	TSTR( "Nutti::Lib::FileIO" ),
													TSTR( "XAnimFile" ),
													TSTR( "ProcessAnimationToken" ),
													TSTR( "} isn't found." ),
													-2 );
		}
		else{
			( *pHierarchyNum )--;
		}

		// Get animation key.
		while( first < *pHierarchyNum ){
			GetToken( pFIn, pToken );
			if( !strcmp( pToken, "AnimationKey" ) ){
				ProcessAnimationKeyToken( pFIn, pToken, &anim, pHierarchyNum );
			}
			else if( !strcmp( pToken, "}" ) ){
				( *pHierarchyNum )--;
			}
			else if( !strcmp( pToken, "{" ) ){
				( *pHierarchyNum )++;
			}
			else{
				throw MapilException(	TSTR( "Nutti::Lib::FileIO" ),
														TSTR( "XAnimFile" ),
														TSTR( "ProcessAnimationToken" ),
														TSTR( "Unknown token is found." ),
														-3 );
			}
		}

		pAnimSet->m_AnimMap.insert( std::map < std::basic_string < MapilChar >, Anim::AnimationSet::Animation > ::value_type( meshName, anim ) );
	}

	// Process "AnimationKey" token.
	MapilVoid XAnimFile::ProcessAnimationKeyToken(	std::basic_ifstream < MapilChar >* pFIn,
																MapilChar* pToken,
																Anim::AnimationSet::Animation* pAnim,
																MapilInt32* pHierarchyNum )
	{
		Anim::AnimationSet::Animation::Key key;

		// Check '{'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "{" ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "{ isn't found." ), -1 );
		}
		else{
			( *pHierarchyNum )++;
		}

		// Get transformation type.
		GetToken( pFIn, pToken );
		key.m_TransType = atoi( pToken );
				
		// Get number of animation, and create transformation time buffer and transformation value buffer.
		GetToken( pFIn, pToken );
		key.m_NumAnim = atoi( pToken );

		// Get transformation information.
		for( MapilInt32 i = 0; i < key.m_NumAnim; i++ ){
			// Get transformation time.
			GetToken( pFIn, pToken );
			key.m_TransTime.push_back( atoi( pToken ) );
			// Get number of information.
			GetToken( pFIn, pToken );
			MapilInt32 num = atoi( pToken );
			// Get transformation value.
			if( num == 3 ){
				GetToken( pFIn, pToken );
				Vector4 < MapilFloat32 > transVal;
				transVal.m_X = static_cast < MapilFloat32 > ( atof( pToken ) );
				GetToken( pFIn, pToken );
				transVal.m_Y = static_cast < MapilFloat32 > ( atof( pToken ) );
				GetToken( pFIn, pToken );
				transVal.m_Z = static_cast < MapilFloat32 > ( atof( pToken ) );
				transVal.m_W = 0.0f;
				key.m_TransVal.push_back( transVal );
			}
			else if( num == 4 ){
				Vector4 < MapilFloat32 > transVal;
				GetToken( pFIn, pToken );
				transVal.m_X = static_cast < MapilFloat32 > ( atof( pToken ) );
				GetToken( pFIn, pToken );
				transVal.m_Y = static_cast < MapilFloat32 > ( atof( pToken ) );
				GetToken( pFIn, pToken );
				transVal.m_Z = static_cast < MapilFloat32 > ( atof( pToken ) );
				GetToken( pFIn, pToken );
				transVal.m_W = static_cast < MapilFloat32 > ( atof( pToken ) );
				key.m_TransVal.push_back( transVal );
			}
		}

		// Check '}'.
		GetToken( pFIn, pToken );
		if( strcmp( pToken, "}" ) ){
			throw MapilException(	TSTR( "Nutti::Lib::FileIO" ),
													TSTR( "XAnimFile" ),
													TSTR( "ProcessAnimationKeyToken" ),
													TSTR( "} isn't found." ),
													-2 );
		}
		else{
			( *pHierarchyNum )--;
		}

		pAnim->m_AnimKey.push_back( key );
	}

	// Load.
	MapilVoid XAnimFile::Load( const MapilChar* pFileName )
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
			else if( !strcmp( tokens, "template" ) ){
				ProcessTemplateToken( &fIn, tokens, &hierarchyNum );
			}
			else if( !strcmp( tokens, "Frame" ) ){
				ProcessFrameToken( &fIn, tokens, &hierarchyNum, &m_RootFrame );
			}
			else if( !strcmp( tokens, "AnimationSet" ) ){
				ProcessAnimationSetToken( &fIn, tokens, &hierarchyNum );
			}
		}

		fIn.close();
	}

	// Copy mesh.
	MapilVoid XAnimFile::CopyMeshToModelData( const Frame::Mesh& mesh, AnimModelData::Frame* pFrame )
	{
		for( MapilUInt32 j = 0; j < mesh.m_Material.size(); ++j ){
			ModelData::Model::Material mtrl;
			mtrl.m_Diffuse[ 0 ] = mesh.m_Material[ j ].m_MaterialColor.m_Diffuse.m_A;
			mtrl.m_Diffuse[ 1 ] = mesh.m_Material[ j ].m_MaterialColor.m_Diffuse.m_R;
			mtrl.m_Diffuse[ 2 ] = mesh.m_Material[ j ].m_MaterialColor.m_Diffuse.m_G;
			mtrl.m_Diffuse[ 3 ] = mesh.m_Material[ j ].m_MaterialColor.m_Diffuse.m_B;
			memcpy( mtrl.m_Ambient, mtrl.m_Diffuse, sizeof( mtrl.m_Ambient ) );
			mtrl.m_Specular[ 0 ] = mesh.m_Material[ j ].m_MaterialColor.m_Specular.m_A;
			mtrl.m_Specular[ 1 ] = mesh.m_Material[ j ].m_MaterialColor.m_Specular.m_R;
			mtrl.m_Specular[ 2 ] = mesh.m_Material[ j ].m_MaterialColor.m_Specular.m_G;
			mtrl.m_Specular[ 3 ] = mesh.m_Material[ j ].m_MaterialColor.m_Specular.m_B;
			mtrl.m_Emissive[ 0 ] = mesh.m_Material[ j ].m_MaterialColor.m_Emissive.m_A;
			mtrl.m_Emissive[ 1 ] = mesh.m_Material[ j ].m_MaterialColor.m_Emissive.m_R;
			mtrl.m_Emissive[ 2 ] = mesh.m_Material[ j ].m_MaterialColor.m_Emissive.m_G;
			mtrl.m_Emissive[ 3 ] = mesh.m_Material[ j ].m_MaterialColor.m_Emissive.m_B;
			mtrl.m_Power = mesh.m_Material[ j ].m_MaterialColor.m_Power;
			strcpy( mtrl.m_TexFileName, mesh.m_Material[ j ].m_TextureFileName );
			pFrame->m_Mesh.m_Material.push_back( mtrl );
		}
		for( MapilInt32 i = 0; i < mesh.m_Vertex.size(); ++i ){
			pFrame->m_Mesh.m_Vertices.push_back( mesh.m_Vertex[ i ].m_X );
			pFrame->m_Mesh.m_Vertices.push_back( mesh.m_Vertex[ i ].m_Y );
			pFrame->m_Mesh.m_Vertices.push_back( mesh.m_Vertex[ i ].m_Z );
		}
		// For normal.
		pFrame->m_Mesh.m_Normals.resize( mesh.m_NumVertex * 3 );
		for( MapilUInt32 nidx = 0; nidx < mesh.m_Face.size(); ++nidx ){
			for( MapilUInt32 elm = 0; elm < mesh.m_Face[ nidx ].m_NumElement; ++elm ){
				if( pFrame->m_Mesh.m_Normals.size() <= mesh.m_Face[ nidx ].m_Index[ elm ] * 3 ){
					exit( 0 );
				}
				if( mesh.m_Normal.size() <= mesh.m_Face[ nidx ].m_NormalNum[ elm ] ){
					exit( 0 );
				}
				pFrame->m_Mesh.m_Normals[ mesh.m_Face[ nidx ].m_Index[ elm ] * 3 + 0 ] = mesh.m_Normal[ mesh.m_Face[ nidx ].m_NormalNum[ elm ] ].m_X;
				pFrame->m_Mesh.m_Normals[ mesh.m_Face[ nidx ].m_Index[ elm ] * 3 + 1 ] = mesh.m_Normal[ mesh.m_Face[ nidx ].m_NormalNum[ elm ] ].m_Y;
				pFrame->m_Mesh.m_Normals[ mesh.m_Face[ nidx ].m_Index[ elm ] * 3 + 2 ] = mesh.m_Normal[ mesh.m_Face[ nidx ].m_NormalNum[ elm ] ].m_Z;
			}
		}
		
		for( MapilInt32 i = 0; i < mesh.m_TextureCoord.size(); ++i ){
			pFrame->m_Mesh.m_TexCoords.push_back( mesh.m_TextureCoord[ i ].m_X );
			pFrame->m_Mesh.m_TexCoords.push_back( mesh.m_TextureCoord[ i ].m_Y );
		}

		//std::copy( m_Mesh[ i ].m_VertexColor.begin(), m_Mesh[ i ].m_VertexColor.end(), std::back_inserter( model.m_VertexCols ) );
		for( MapilUInt32 j = 0; j < mesh.m_Face.size(); ++j ){
			ModelData::Model::Face face;
			face.m_NumElm = mesh.m_Face[ j ].m_NumElement;
			face.m_MtrlNum = mesh.m_Face[ j ].m_MaterialNum;
			if( face.m_NumElm == 3 ){
				pFrame->m_Mesh.m_Indices.push_back( mesh.m_Face[ j ].m_Index[ 0 ] );
				pFrame->m_Mesh.m_Indices.push_back( mesh.m_Face[ j ].m_Index[ 1 ] );
				pFrame->m_Mesh.m_Indices.push_back( mesh.m_Face[ j ].m_Index[ 2 ] );
			}
			// Quad -> Triangle.
			else{
				pFrame->m_Mesh.m_Indices.push_back( mesh.m_Face[ j ].m_Index[ 0 ] );
				pFrame->m_Mesh.m_Indices.push_back( mesh.m_Face[ j ].m_Index[ 1 ] );
				pFrame->m_Mesh.m_Indices.push_back( mesh.m_Face[ j ].m_Index[ 3 ] );
				pFrame->m_Mesh.m_Indices.push_back( mesh.m_Face[ j ].m_Index[ 1 ] );
				pFrame->m_Mesh.m_Indices.push_back( mesh.m_Face[ j ].m_Index[ 2 ] );
				pFrame->m_Mesh.m_Indices.push_back( mesh.m_Face[ j ].m_Index[ 3 ] );
				++pFrame->m_Mesh.m_FaceTotal;
			}
			pFrame->m_Mesh.m_Face.push_back( face );
			++pFrame->m_Mesh.m_FaceTotal;
		}
	}

	// Clear frame.
	MapilVoid XAnimFile::ClearModelDataFrame( AnimModelData::Frame* pFrame )
	{
		pFrame->m_Mesh.m_Face.clear();
		pFrame->m_Mesh.m_FaceTotal = 0;
		pFrame->m_Mesh.m_Indices.clear();
		pFrame->m_Mesh.m_Material.clear();
		pFrame->m_Mesh.m_Normals.clear();
		pFrame->m_Mesh.m_TexCoords.clear();
		pFrame->m_Mesh.m_VertexCols.clear();
		pFrame->m_Mesh.m_Vertices.clear();

		pFrame->m_Name.clear();
		pFrame->m_pFirstChild = NULL;
		pFrame->m_pSibling = NULL;
	}

	// Copy frame.
	MapilVoid XAnimFile::CopyFrameToModelData( const Frame& frame, AnimModelData::Frame* pFrame )
	{
		// Copy first child.
		if( frame.m_pFirstChild ){
			pFrame->m_pFirstChild = new AnimModelData::Frame;
			ClearModelDataFrame( pFrame->m_pFirstChild );
			CopyFrameToModelData( *frame.m_pFirstChild, pFrame->m_pFirstChild );
		}

		// Copy sibling
		if( frame.m_pSibling ){
			pFrame->m_pSibling = new AnimModelData::Frame;
			ClearModelDataFrame( pFrame->m_pSibling );
			CopyFrameToModelData( *frame.m_pSibling, pFrame->m_pSibling );
		}

		pFrame->m_Name = frame.m_FrameName;
		pFrame->m_TransMat = frame.m_TransMat;
		CopyMeshToModelData( frame.m_Mesh, pFrame );
	}

	// Copy to model data.
	MapilVoid XAnimFile::CopyToModelData( AnimModelData* pData )
	{
		// Copy all frames.
		ClearModelDataFrame( &pData->m_RootFame );
		CopyFrameToModelData( m_RootFrame, &pData->m_RootFame );

		// Copy all animations.
		typedef std::map < std::basic_string < MapilChar >, Anim::AnimationSet > ::iterator AnimSetIter;

		// Copy all animation set.
		for( AnimSetIter itSet = m_Anim.m_AnimSetMap.begin(); itSet != m_Anim.m_AnimSetMap.end(); ++itSet ){
			
			AnimModelData::Animation::AnimSet animSet;

			
			// Copy all animation item.
			typedef std::map < std::basic_string < MapilChar >, Anim::AnimationSet::Animation > ::iterator AnimationIter;
			for( AnimationIter itAnimation = itSet->second.m_AnimMap.begin(); itAnimation != itSet->second.m_AnimMap.end(); ++itAnimation ){
				std::basic_string < MapilChar > animationName = itAnimation->first;
				Anim::AnimationSet::Animation& anim = itAnimation->second;

				AnimModelData::Animation::AnimSet::AnimItem item;
				
				std::vector < AnimModelData::Animation::AnimSet::AnimItem::Key > keys;
				// Copy all animation keys.
				for( MapilInt32 i = 0; i < anim.m_AnimKey.size(); ++i ){
					AnimModelData::Animation::AnimSet::AnimItem::Key key;
					// Copy all list.
					for( MapilInt32 j = 0; j < anim.m_AnimKey[ i ].m_TransTime.size(); ++j ){
						AnimModelData::Animation::AnimSet::AnimItem::Key::Entry entry;
						entry.m_Time = anim.m_AnimKey[ i ].m_TransTime[ j ];
						entry.m_TransVal.m_Elm[ 0 ] = anim.m_AnimKey[ i ].m_TransVal[ j ].m_X;
						entry.m_TransVal.m_Elm[ 1 ] = anim.m_AnimKey[ i ].m_TransVal[ j ].m_Y;
						entry.m_TransVal.m_Elm[ 2 ] = anim.m_AnimKey[ i ].m_TransVal[ j ].m_Z;
						entry.m_TransVal.m_Elm[ 3 ] = anim.m_AnimKey[ i ].m_TransVal[ j ].m_W;
						key.m_Entries.push_back( entry );
						//key.m_Entries[ transTime ] = transVal;
					}
					key.m_Type = anim.m_AnimKey[ i ].m_TransType;
					keys.push_back( key );
				}
				item.m_Keys[ anim.m_AnimName ] = keys;

				animSet.m_AnimItems[ itAnimation->first ] = item;
			}

			pData->m_Animation.m_AnimSetList[ itSet->first ] = animSet;
		}
	}

	// Calculate world matrix each frame.
	MapilVoid XAnimFile::CalcFWM( Frame* pFrame )
	{
		pFrame->m_CalcTransMat = m_MatStack.top();
		pFrame->m_CalcTransMat.Mul( pFrame->m_TransMat );

		if( pFrame->m_pFirstChild ){
			m_MatStack.push( pFrame->m_CalcTransMat );
			CalcFWM( pFrame->m_pFirstChild );
			m_MatStack.pop();
		}

		if( pFrame->m_pSibling ){
			CalcFWM( pFrame->m_pSibling );
		}
	}

	// Calculate world matrix of all frame.
	MapilVoid XAnimFile::CalcFrameWorldMat()
	{
		Matrix4x4 < MapilFloat32 > mat;
		mat.m_11 = mat.m_22 = mat.m_33 = mat.m_44 = 1.0f;
		m_MatStack.push( mat );
		CalcFWM( &m_RootFrame );
		m_MatStack.pop();
	}

	// Update world matrix for each frame.
	MapilVoid XAnimFile::UpdateFWM(	Frame* pFrame,
												const MapilChar* pTrackName,
												MapilFloat32 advanceTime, 
												MapilFloat32 nowTime )
	{
		pFrame->m_CalcTransMat = m_MatStack.top();

		Matrix4x4 < MapilFloat32 > mat;
		GetTransMat( pTrackName, pFrame->m_FrameName.c_str(), &mat, advanceTime, nowTime );
		pFrame->m_CalcTransMat.Mul( mat );

		if( pFrame->m_pFirstChild ){
			m_MatStack.push( pFrame->m_CalcTransMat );
			UpdateFWM( pFrame->m_pFirstChild, pTrackName, advanceTime, nowTime );
			m_MatStack.pop();
		}

		if( pFrame->m_pSibling ){
			UpdateFWM( pFrame->m_pSibling, pTrackName, advanceTime, nowTime );
		}
	}

	// Update world matrix for all frame.
	MapilVoid XAnimFile::UpdateFrameWorldMat(	const MapilChar* pTrackName,
															MapilFloat32 advanceTime, 
															MapilFloat32 nowTime )
	{
		Matrix4x4 < MapilFloat32 > mat;
		mat.m_11 = mat.m_22 = mat.m_33 = mat.m_44 = 1.0f;
		m_MatStack.push( mat );
		UpdateFWM( &m_RootFrame, pTrackName, advanceTime, nowTime );
		m_MatStack.pop();
	}

	// Create lerp transformation matrix.
	MapilVoid XAnimFile::CreateLerpTransMat(	Matrix4x4 < MapilFloat32 >* pMatOut,
															MapilFloat32 advanceTime,
															MapilFloat32 nowTime,
															const Anim::AnimationSet::Animation::Key& key )
	{
		MapilFloat32 nextTime = nowTime + advanceTime;

		MapilInt32 sel = 0;		// Next key.

		while( !sel ){
			for( MapilUInt32 i = 1; i < key.m_TransTime.size(); i++ ){
				if( nextTime < key.m_TransTime[ i ] ){
					sel = i;
					break;
				}
			}
			if( !sel ){
				nextTime -= key.m_TransTime[ key.m_TransTime.size() - 1 ];
			}
		}

		MapilFloat32 rate = ( nextTime - key.m_TransTime[ sel - 1 ] ) / ( key.m_TransTime[ sel ] - key.m_TransTime[ sel -1 ] );

		pMatOut->m_41 = key.m_TransVal[ sel - 1 ].m_X * ( 1 - rate ) + key.m_TransVal[ sel ].m_X * rate;
		pMatOut->m_42 = key.m_TransVal[ sel - 1 ].m_Y * ( 1 - rate ) + key.m_TransVal[ sel ].m_Y * rate;
		pMatOut->m_43 = key.m_TransVal[ sel - 1 ].m_Z * ( 1 - rate ) + key.m_TransVal[ sel ].m_Z * rate;
	}

	// Get transformation matrix.
	MapilVoid XAnimFile::GetTransMat(	const MapilChar* pTrackName,
													const MapilChar* pFrameName,
													Matrix4x4 < MapilFloat32 >* pMatOut,
													MapilFloat32 advanceTime,
													MapilFloat32 nowTime )
	{
		// 今後バグになる可能性あり。
		if( !strcmp( pFrameName, "Frame_SCENE_ROOT" ) ){
			pMatOut->m_11 = pMatOut->m_22 = pMatOut->m_33 = pMatOut->m_44 = 1.0f;
			return;
		}

		std::map < std::basic_string < MapilChar >, Anim::AnimationSet > ::iterator it;
		it = m_Anim.m_AnimSetMap.find( pTrackName );
				
		std::map < std::basic_string < MapilChar >, Anim::AnimationSet::Animation > ::iterator itt;
		itt = it->second.m_AnimMap.find( pFrameName );

		MapilInt32 num;
		num = itt->second.m_AnimKey.size();


		//MapilInt32 interval = itt->second.m_AnimKey[ 0 ].m_TransTime[ 1 ] - itt->second.m_AnimKey[ 0 ].m_TransTime[ 0 ];
		//MapilInt32 numAnim = itt->second.m_AnimKey[ 0 ].m_NumAnim;
				

		Matrix4x4 < MapilFloat32 > mat;
		mat.m_11 = mat.m_22 = mat.m_33 = mat.m_44 = 1.0f;
		for( MapilInt32 i = 0; i < num; i++ ){
			Matrix4x4 < MapilFloat32 > matTmp;
			matTmp.m_11 = matTmp.m_22 = matTmp.m_33 = matTmp.m_44 = 1.0f;
			switch( itt->second.m_AnimKey[ i ].m_TransType ){
				case 0:
					break;
				case 1:
					//CreateLerpTransMat( &matTmp, time, itt->second.m_AnimKey[ i ] );
					break;
				case 2:
					CreateLerpTransMat( &matTmp, advanceTime, nowTime, itt->second.m_AnimKey[ i ] );
					break;
				case 3:
					break;
				default:
					break;
			}
			mat.Mul( matTmp );
		}

		*pMatOut = mat;
	}

	// Delete all frame.
	MapilVoid XAnimFile::DeleteF( Frame* pFrame )
	{
		if( pFrame->m_pFirstChild ){
			DeleteF( pFrame->m_pFirstChild );
		}

		if( pFrame->m_pSibling ){
			DeleteF( pFrame->m_pSibling );
		}
				
		SafeDelete( pFrame );
	}

	// Delete each frame.
	MapilVoid XAnimFile::DeleteFrame()
	{
		if( m_RootFrame.m_pFirstChild ){
			DeleteF( m_RootFrame.m_pFirstChild );
			m_RootFrame.m_pFirstChild = NULL;
		}
		if( m_RootFrame.m_pSibling ){
			DeleteF( m_RootFrame.m_pSibling );
			m_RootFrame.m_pSibling = NULL;
		}
	}

}