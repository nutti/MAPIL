/**
*	@file	D3DModel.cpp
*	@brief	Implementation of D3DModel.h.
*	@date	2011.8.25 (Thu) 18:51
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_9_0_C )

#include "../../Include/MAPIL/IO/Archiver.h"
#include "../../Include/MAPIL/Graphics/D3DModel.h"
#include "../../Include/MAPIL/Graphics/D3DTexture.h"
#include "../../Include/MAPIL/IO/MQOFile.h"
#include "../../Include/MAPIL/IO/XFile.h"
#include "../../Include/MAPIL/IO/FileFormatAnalyzer.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Util/String.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DModel::D3DModel( SharedPointer < GraphicsDevice > pDev ) :	Model( pDev ),
																	m_pD3DMesh( NULL ),
																	m_pMaterial( NULL ),
																	m_pD3DTexture( NULL ),
																	m_NumMaterial( 0 ),

																	m_pVertex( NULL ),
																	m_pIndex( NULL ),
																	m_pVertexDecl( NULL ),
																	m_pTexture( NULL )
	{
	}

	D3DModel::~D3DModel()
	{
		for( DWORD i = 0; i < m_NumMaterial; ++i ){
			SafeRelease( m_pD3DTexture[ i ] );
		}
		SafeDeleteArray( m_pMaterial );
		SafeDeleteArray( m_pD3DTexture );
		m_NumMaterial = 0;
		SafeRelease( m_pD3DMesh );
		m_IsUsed = MapilFalse;

		SafeRelease( m_pVertexDecl );
		SafeRelease( m_pIndex );
		SafeRelease( m_pVertex );
		SafeDelete( m_pTexture );
	}

	/*MapilVoid D3DModel::Create( const MapilTChar* pFileName )
	{
		Assert( !m_IsUsed, CURRENT_POSITION,TSTR( "The model was already created." ), -1 );

		MapilChar name[ 1024 ];
		ConvertToMultiByte( pFileName, -1, name, 1024 );

		ModelData* pModelData = new ModelData();

		// Analyze file format.
		FileFormatAnalyzer ffa;
		ffa.Open( name );
		ffa.Analyze();
		ModelFile* pModelFile = NULL;
		if( ffa.GetFileFmt() == FILE_FORMAT_X ){
			pModelFile = new XFile();
		}
		else if( ffa.GetFileFmt() == FILE_FORMAT_MQO ){
			pModelFile = new MQOFile();
		}
		else{
			throw MapilException( CURRENT_POSITION, TSTR( "Invalid file format." ), -1 );
		}

		// Load model file.
		pModelFile->Load( name );
		pModelFile->CopyToModelData( pModelData );
		SafeDelete( pModelFile );

		//Vertex elements of mesh
		D3DVERTEXELEMENT9 elements[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION, 0 },	//Position
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },	//Normal
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //Texture coordinate
			D3DDECL_END()
		};

		// Create vertex declaration
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexDeclaration( elements, &m_pVertexDecl ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create vertex declaration." ), -1 );
		}

		VertexFormat vertexFmt;

		int i = sizeof( vertexFmt );

		// Create vertex buffer.
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexBuffer(	sizeof( vertexFmt ) * pModelData->m_Model[ 0 ].m_Vertices.size() / 3,
																		0,
																		0,
																		D3DPOOL_MANAGED,
																		&m_pVertex,
																		NULL ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create vertex buffer." ), -2 );
		}

		// Create index buffer.
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateIndexBuffer(	sizeof( WORD ) * pModelData->m_Model[ 0 ].m_Indices.size(),
																		0,
																		D3DFMT_INDEX16,
																		D3DPOOL_MANAGED,
																		&m_pIndex,
																		NULL ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create index buffer." ), -3 );
		}

		// Write to vertex buffer
		VertexFormat* pBuf;
		if( m_pVertex->Lock( 0, 0, reinterpret_cast < LPVOID* > ( &pBuf ), 0 ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to lock vertex buffer." ), -4 );
		}
		for( MapilInt32 i = 0; i < pModelData->m_Model[ 0 ].m_Vertices.size() / 3; ++i ){
			pBuf[ i ].m_Vertex[ 0 ] = pModelData->m_Model[ 0 ].m_Vertices[ i * 3 ];
			pBuf[ i ].m_Vertex[ 1 ] = pModelData->m_Model[ 0 ].m_Vertices[ i * 3 + 1 ];
			pBuf[ i ].m_Vertex[ 2 ] = pModelData->m_Model[ 0 ].m_Vertices[ i * 3 + 2 ];
			pBuf[ i ].m_Normal[ 0 ] = pModelData->m_Model[ 0 ].m_Normals[ i * 3 ];
			pBuf[ i ].m_Normal[ 1 ] = pModelData->m_Model[ 0 ].m_Normals[ i * 3 + 1 ];
			pBuf[ i ].m_Normal[ 2 ] = pModelData->m_Model[ 0 ].m_Normals[ i * 3 + 2 ];
			pBuf[ i ].m_TexCoord[ 0 ] = pModelData->m_Model[ 0 ].m_TexCoords[ i * 2 ];
			pBuf[ i ].m_TexCoord[ 1 ] = pModelData->m_Model[ 0 ].m_TexCoords[ i * 2 + 1 ];
		}
		m_pVertex->Unlock();

		// Write to index buffer.
		WORD* pIdxBuf;
		if( m_pIndex->Lock( 0, 0, reinterpret_cast < LPVOID* > ( &pIdxBuf ), 0 ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to lock index buffer." ), -5 );
		}
		for( MapilInt32 i = 0; i < pModelData->m_Model[ 0 ].m_Indices.size(); ++i ){
			pIdxBuf[ i ] = pModelData->m_Model[ 0 ].m_Indices[ i ];
		}
		m_pIndex->Unlock();

		// !!!!! temporary
		for( MapilInt32 i = 0; i < pModelData->m_Model[ 0 ].m_Material.size(); ++i ){
			if( ::strcmp( "", pModelData->m_Model[ 0 ].m_Material[ i ].m_TexFileName ) ){
#ifdef CHAR_CODE_UNICODE
				//Change Multi-byte character into Unicode character
				WCHAR textureFileName[ MAX_PATH ];
				MultiByteToWideChar( CP_ACP, 0, pModelData->m_Model[ 0 ].m_Material[ i ].m_TexFileName, -1, textureFileName, MAX_PATH );
				textureFileName[ MAX_PATH - 1 ] = 0;
				m_pTexture = new D3DTexture( m_pDev );
				m_pTexture->Create( textureFileName );
				m_pMaterial = new ::D3DMATERIAL9[ 1 ];
				D3DCOLORVALUE color;
				color.a = pModelData->m_Model[ 0 ].m_Material[ i ].m_Ambient[ 0 ];
				color.r = pModelData->m_Model[ 0 ].m_Material[ i ].m_Ambient[ 1 ];
				color.g = pModelData->m_Model[ 0 ].m_Material[ i ].m_Ambient[ 2 ];
				color.b = pModelData->m_Model[ 0 ].m_Material[ i ].m_Ambient[ 3 ];
				m_pMaterial->Ambient = color;
				color.a = pModelData->m_Model[ 0 ].m_Material[ i ].m_Diffuse[ 0 ];
				color.r = pModelData->m_Model[ 0 ].m_Material[ i ].m_Diffuse[ 1 ];
				color.g = pModelData->m_Model[ 0 ].m_Material[ i ].m_Diffuse[ 2 ];
				color.b = pModelData->m_Model[ 0 ].m_Material[ i ].m_Diffuse[ 3 ];
				m_pMaterial->Diffuse = color;
				color.a = pModelData->m_Model[ 0 ].m_Material[ i ].m_Emissive[ 0 ];
				color.r = pModelData->m_Model[ 0 ].m_Material[ i ].m_Emissive[ 1 ];
				color.g = pModelData->m_Model[ 0 ].m_Material[ i ].m_Emissive[ 2 ];
				color.b = pModelData->m_Model[ 0 ].m_Material[ i ].m_Emissive[ 3 ];
				m_pMaterial->Emissive = color;
				color.a = pModelData->m_Model[ 0 ].m_Material[ i ].m_Specular[ 0 ];
				color.r = pModelData->m_Model[ 0 ].m_Material[ i ].m_Specular[ 1 ];
				color.g = pModelData->m_Model[ 0 ].m_Material[ i ].m_Specular[ 2 ];
				color.b = pModelData->m_Model[ 0 ].m_Material[ i ].m_Specular[ 3 ];
				m_pMaterial->Specular = color;
				m_pMaterial->Power = pModelData->m_Model[ 0 ].m_Material[ i ].m_Power;
				//Load texture
				//if( FAILED( D3DXCreateTextureFromFile( m_pDev->GetDev().GetPointer(), textureFileName, &m_pD3DTexture[ i ] ) ) ){
				//	m_pD3DTexture[ i ] = NULL;
				//}
#endif
#ifdef CHAR_CODE_MULTIBYTE
				//Load texture
				if( FAILED( D3DXCreateTextureFromFile( m_pDev->GetDev().GetPointer(), pModelData->m_Model[ 0 ].m_Material[ i ].m_TexFileName, &m_pD3DTexture[ i ] ) ) ){
					m_pD3DTexture[ i ] = NULL;
				}
#endif
				break;
			}
		}

		

		m_VertexTotal = pModelData->m_Model[ 0 ].m_Vertices.size() / 3;
		m_IndexTotal = pModelData->m_Model[ 0 ].m_Indices.size() / 3;

		m_IsUsed = MapilTrue;

		SafeDelete( pModelData );
	}*/

	MapilVoid D3DModel::Create( const MapilTChar* pFileName )
	{
		Assert(	!m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DModel" ),
				TSTR( "Create" ),
				TSTR( "The model was already created." ),
				-1 );

		//Load mesh from X-file
		LPD3DXBUFFER pD3DMaterialBuf;			//Buffer which store material information
		LPD3DXBUFFER pD3DAdjacencyBuf;			//Buffer which store adjacency information
		if( FAILED( D3DXLoadMeshFromX(	pFileName,
										D3DXMESH_SYSTEMMEM,
										m_pDev->GetDev().GetPointer(),
										&pD3DAdjacencyBuf,
										&pD3DMaterialBuf,
										NULL,
										&m_NumMaterial,
										&m_pD3DMesh ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DModel" ),
									TSTR( "Create" ),
									TSTR( "Failed to load mesh from X-file." ),
									-1 );
		}

		//Vertex elements of mesh
		D3DVERTEXELEMENT9 vertexElements[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION, 0 },	//Position
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },	//Normal
			{ 0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //Texture coordinate
			D3DDECL_END()
		};

		//Change vertex data of X-file into object which suits on applications
		LPD3DXMESH pNewMesh;
		if( FAILED( m_pD3DMesh->CloneMesh( D3DXMESH_MANAGED, vertexElements, m_pDev->GetDev().GetPointer(), &pNewMesh ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DModel" ),
									TSTR( "Create" ),
									TSTR( "Failed to change vertex data of X-file into object which suits on applications." ),
									-2 );
		}
		SafeRelease( m_pD3DMesh );
		m_pD3DMesh = pNewMesh;
		//If X-file doesn't have normal data, normal vector will be calculated (adjacency information will be used)
		if( FAILED( D3DXComputeNormals( m_pD3DMesh, static_cast < DWORD* > ( pD3DAdjacencyBuf->GetBufferPointer() ) ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DModel" ),
									TSTR( "Create" ),
									TSTR( "Failed to calculate normals." ),
									-3 );
		}
		//Optimize mesh
		HRESULT hr = m_pD3DMesh->OptimizeInplace(	D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
													static_cast < DWORD* > ( pD3DAdjacencyBuf->GetBufferPointer() ),
													NULL,
													NULL,
													NULL );
		SafeRelease( pD3DAdjacencyBuf );
		if( FAILED( hr ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DModel" ),
									TSTR( "Create" ),
									TSTR( "Failed to optimize mesh." ),
									-4 );
		}
		
		//Hold array which material will be saved
		SafeDeleteArray( m_pMaterial );
		SafeDeleteArray( m_pD3DTexture );
		m_pMaterial = new D3DMATERIAL9[ m_NumMaterial ];
		m_pD3DTexture = new LPDIRECT3DTEXTURE9[ m_NumMaterial ];
		//Get pointer which has material information buffer
		D3DXMATERIAL* pD3DMaterial = static_cast < D3DXMATERIAL* > ( pD3DMaterialBuf->GetBufferPointer() );
		//Save material information
		for( DWORD i = 0; i < m_NumMaterial; i++ ){
			//Color of mesh
			m_pMaterial[ i ] = pD3DMaterial[ i ].MatD3D;
			//Ambient color is replaced with diffuse color because X-file doesn't have ambient color
			m_pMaterial[ i ].Ambient = m_pMaterial[ i ].Diffuse;
			//Texture
			if( !pD3DMaterial[ i ].pTextureFilename ){
				m_pD3DTexture[ i ] = NULL;
			}
			else{
#ifdef CHAR_CODE_UNICODE
				//Change Multi-byte character into Unicode character
				WCHAR textureFileName[ MAX_PATH ];
				MultiByteToWideChar( CP_ACP, 0, pD3DMaterial[ i ].pTextureFilename, -1, textureFileName, MAX_PATH );
				textureFileName[ MAX_PATH - 1 ] = 0;
				//Load texture
				if( FAILED( D3DXCreateTextureFromFile( m_pDev->GetDev().GetPointer(), textureFileName, &m_pD3DTexture[ i ] ) ) ){
					m_pD3DTexture[ i ] = NULL;
				}
#endif
#ifdef CHAR_CODE_MULTIBYTE
				//Load texture
				if( FAILED( D3DXCreateTextureFromFile( m_pDev->GetDev().GetPointer(), pD3DMaterial[ i ].pTextureFileName, &m_pD3DTexture[ i ] ) ) ){
					m_pD3DTexture[ i ] = NULL;
				}
#endif
			}
		}

		SafeRelease( pD3DMaterialBuf );

		m_IsUsed = MapilTrue;
	}
	
	MapilVoid D3DModel::Create( Archiver* pArchiver, const MapilTChar* pXFileName, const MapilTChar* pTextureFileName )
	{
		Assert(	!m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DModel" ),
				TSTR( "Create" ),
				TSTR( "The model was already created." ),
				-1 );

		MapilChar name[ 1024 ];
		ConvertToMultiByte( pXFileName, -1, name, 1024 );

		MapilInt32 size = pArchiver->GetContentsSize( name );
		MapilChar* pData = new MapilChar [ size ];
		pArchiver->Load( name, pData );

		//Load mesh from X-file
		LPD3DXBUFFER pD3DMaterialBuf;			//Buffer which store material information
		LPD3DXBUFFER pD3DAdjacencyBuf;			//Buffer which store adjacency information
		if( FAILED( D3DXLoadMeshFromXInMemory(	pData,
												size,
												D3DXMESH_SYSTEMMEM,
												m_pDev->GetDev().GetPointer(),
												&pD3DAdjacencyBuf,
												&pD3DMaterialBuf,
												NULL,
												&m_NumMaterial,
												&m_pD3DMesh ) ) ){
			SafeDeleteArray( pData );
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DModel" ),
									TSTR( "Create" ),
									TSTR( "Failed to load mesh from X-file." ),
									-1 );
		}

		SafeDeleteArray( pData );

		//Vertex elements of mesh
		D3DVERTEXELEMENT9 vertexElements[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION, 0 },	//Position
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },	//Normal
			{ 0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //Texture coordinate
			D3DDECL_END()
		};

		//Change vertex data of X-file into object which suits on applications
		LPD3DXMESH pNewMesh;
		if( FAILED( m_pD3DMesh->CloneMesh( D3DXMESH_MANAGED, vertexElements, m_pDev->GetDev().GetPointer(), &pNewMesh ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DModel" ),
									TSTR( "Create" ),
									TSTR( "Failed to change vertex data of X-file into object which suits on applications." ),
									-2 );
		}
		SafeRelease( m_pD3DMesh );
		m_pD3DMesh = pNewMesh;
		//If X-file doesn't have normal data, normal vector will be calculated (adjacency information will be used)
		if( FAILED( D3DXComputeNormals( m_pD3DMesh, static_cast < DWORD* > ( pD3DAdjacencyBuf->GetBufferPointer() ) ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DModel" ),
									TSTR( "Create" ),
									TSTR( "Failed to calculate normals." ),
									-3 );
		}
		//Optimize mesh
		HRESULT hr = m_pD3DMesh->OptimizeInplace(	D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
													static_cast < DWORD* > ( pD3DAdjacencyBuf->GetBufferPointer() ),
													NULL,
													NULL,
													NULL );
		SafeRelease( pD3DAdjacencyBuf );
		if( FAILED( hr ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DModel" ),
									TSTR( "Create" ),
									TSTR( "Failed to optimize mesh." ),
									-4 );
		}
		
		//Hold array which material will be saved
		SafeDeleteArray( m_pMaterial );
		SafeDeleteArray( m_pD3DTexture );
		m_pMaterial = new D3DMATERIAL9[ m_NumMaterial ];
		m_pD3DTexture = new LPDIRECT3DTEXTURE9[ m_NumMaterial ];
		//Get pointer which has material information buffer
		D3DXMATERIAL* pD3DMaterial = static_cast < D3DXMATERIAL* > ( pD3DMaterialBuf->GetBufferPointer() );
		//Save material information
		for( DWORD i = 0; i < m_NumMaterial; i++ ){
			//Color of mesh
			m_pMaterial[ i ] = pD3DMaterial[ i ].MatD3D;
			//Ambient color is replaced with diffuse color because X-file doesn't have ambient color
			m_pMaterial[ i ].Ambient = m_pMaterial[ i ].Diffuse;
			//Texture
			if( !pD3DMaterial[ i ].pTextureFilename ){
				m_pD3DTexture[ i ] = NULL;
			}
			else{
				MapilChar texName[ 1024 ];
				ConvertToMultiByte( pTextureFileName, -1, texName, 1024 );

				MapilInt32 size = pArchiver->GetContentsSize( texName );
				MapilChar* pData = new MapilChar [ size ];
				pArchiver->Load( texName, pData );

				// Load texture
				if( FAILED( ::D3DXCreateTextureFromFileInMemory(	m_pDev->GetDev().GetPointer(),
																	pData,
																	size,
																	&m_pD3DTexture[ i ] ) ) ){
					SafeDeleteArray( pData );
					m_pD3DTexture[ i ] = NULL;
				}
				SafeDeleteArray( pData );
			}
		}

		SafeRelease( pD3DMaterialBuf );

		m_IsUsed = MapilTrue;
	}

	MapilVoid D3DModel::Draw()
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DModel" ),
				TSTR( "Draw" ),
				TSTR( "The mesh isn't created yet." ),
				-1 );

		DrawModel();
	}

	MapilVoid D3DModel::Draw( const Matrix4x4 < MapilFloat32 >& mat )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DModel" ),
				TSTR( "Draw" ),
				TSTR( "The mesh isn't created yet." ),
				-1 );

		D3DXMATRIXA16 matWorld;
		for( MapilInt32 i = 0; i < 4; i++ ){
			for( MapilInt32 j = 0; j < 4; j++ ){
				matWorld.m[ i ][ j ] = mat.m_Elm[ i ][ j ];
			}
		}

		//World coordinate transformation
		m_pDev->GetDev().GetPointer()->SetTransform( D3DTS_WORLD, &matWorld );

		DrawModel();
	}

	MapilVoid D3DModel::DrawModel()
	{
		//Draw
		for( DWORD i = 0; i < m_NumMaterial; i++ ){
			m_pDev->GetDev().GetPointer()->SetMaterial( &m_pMaterial[ i ] );
			m_pDev->GetDev().GetPointer()->SetTexture( 0, m_pD3DTexture[ i ] );
			m_pD3DMesh->DrawSubset( i );
		}

		/*m_pDev->GetDev().GetPointer()->SetVertexDeclaration( m_pVertexDecl );
		m_pDev->GetDev().GetPointer()->SetStreamSource( 0, m_pVertex, 0, sizeof( VertexFormat ) );
		m_pDev->GetDev().GetPointer()->SetIndices( m_pIndex );
		m_pDev->GetDev().GetPointer()->SetMaterial( &m_pMaterial[ 0 ] );
		m_pDev->GetDev().GetPointer()->SetTexture( 0, reinterpret_cast < ::LPDIRECT3DTEXTURE9 > ( m_pTexture->Get() ) );
		m_pDev->GetDev().GetPointer()->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_VertexTotal, 0, m_IndexTotal );*/
	}

	MapilBool D3DModel::DetectCollision(	const Vector3 < MapilFloat32 >& vRayDir,
											const Vector3 < MapilFloat32 >& vRayOrig,
											Vector2 < MapilFloat32 >* pVCollisionPos,
											MapilFloat32* pDistance )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DModel" ),
				TSTR( "DetectCollision" ),
				TSTR( "The mesh isn't created yet." ),
				-1 );

		::D3DXVECTOR3 pos( vRayOrig.m_X, vRayOrig.m_Y, vRayOrig.m_Z );		// Position of the ray.
		::D3DXVECTOR3 dir( vRayDir.m_X, vRayDir.m_Y, vRayDir.m_Z );			// Direction of the ray.
		BOOL result = FALSE;												// Does collide?
		DWORD faceIndex = 0;												// Index of the face which ray hits.
		FLOAT collisionPosX = 0;											// X-coordinate of the position where ray hits.
		FLOAT collisionPosY = 0;											// Y-coordinate of the position where ray hits.
		FLOAT distance = 0;													// Distance between origin of the ray and where the ray hits.

		::D3DXIntersect(	m_pD3DMesh,
							&pos,
							&dir,
							&result,
							&faceIndex,
							&collisionPosX,
							&collisionPosY,
							&distance,
							NULL,
							NULL );

		pVCollisionPos->m_X = collisionPosX;
		pVCollisionPos->m_Y = collisionPosY;
		*pDistance = distance;

		return result ? MapilTrue : MapilFalse;					
	}

}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D