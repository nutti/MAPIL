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
#include "../../Include/MAPIL/Graphics/D3DAnimModel.h"
#include "../../Include/MAPIL/Graphics/D3DTexture.h"
#include "../../Include/MAPIL/IO/XAnimFile.h"
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
	D3DAnimModel::D3DAnimModel( SharedPointer < GraphicsDevice > pDev ) :	Model( pDev )
	{
		ClearFrame( &m_RootFrame );
	}

	D3DAnimModel::~D3DAnimModel()
	{
		ClearFrame( &m_RootFrame );
	}

	// Create frame.
	MapilVoid D3DAnimModel::CreateFrame( const AnimModelData::Frame& frame, Frame* pFrame )
	{
		// Create first child.
		if( frame.m_pFirstChild ){
			pFrame->m_pFirstChild = new Frame;
			ClearFrame( pFrame->m_pFirstChild );
			CreateFrame( *frame.m_pFirstChild, pFrame->m_pFirstChild );
		}

		// Create sibling
		if( frame.m_pSibling ){
			pFrame->m_pSibling = new Frame;
			ClearFrame( pFrame->m_pSibling );
			CreateFrame( *frame.m_pSibling, pFrame->m_pSibling );
		}

		pFrame->m_Name = frame.m_Name;
		pFrame->m_TransMat = frame.m_TransMat;
		CreateModel( frame, pFrame );
	}

	// Clear frame.
	MapilVoid D3DAnimModel::ClearFrame( Frame* pFrame )
	{
		pFrame->m_Mesh.m_IndexTotal = 0;
		pFrame->m_Mesh.m_NumMaterial = 0;
		pFrame->m_Mesh.m_pIndex = NULL;
		pFrame->m_Mesh.m_pMaterial = NULL;
		pFrame->m_Mesh.m_pTexture = NULL;
		pFrame->m_Mesh.m_pVertex = NULL;
		pFrame->m_Mesh.m_pVertexDecl = NULL;
		pFrame->m_Mesh.m_VertexTotal = 0;

		pFrame->m_Name.clear();
		pFrame->m_pFirstChild = NULL;
		pFrame->m_pSibling = NULL;
	}

	MapilVoid D3DAnimModel::CreateModel( const AnimModelData::Frame& frame, Frame* pFrame )
	{
		if( frame.m_Mesh.m_Vertices.size() <= 0 ){
			return;
		}

		//Vertex elements of mesh
		D3DVERTEXELEMENT9 elements[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION, 0 },	//Position
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },	//Normal
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //Texture coordinate
			D3DDECL_END()
		};

		// Create vertex declaration
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexDeclaration( elements, &pFrame->m_Mesh.m_pVertexDecl ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create vertex declaration." ), -1 );
		}

		VertexFormat vertexFmt;

		// Create vertex buffer.
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateVertexBuffer(	sizeof( vertexFmt ) * frame.m_Mesh.m_Vertices.size() / 3,
																		0,
																		0,
																		D3DPOOL_MANAGED,
																		&pFrame->m_Mesh.m_pVertex,
																		NULL ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create vertex buffer." ), -2 );
		}

		// Create index buffer.
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateIndexBuffer(	sizeof( WORD ) * frame.m_Mesh.m_Indices.size(),
																		0,
																		D3DFMT_INDEX16,
																		D3DPOOL_MANAGED,
																		&pFrame->m_Mesh.m_pIndex,
																		NULL ) ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to create index buffer." ), -3 );
		}

		// Write to vertex buffer
		VertexFormat* pBuf;
		if( pFrame->m_Mesh.m_pVertex->Lock( 0, 0, reinterpret_cast < LPVOID* > ( &pBuf ), 0 ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to lock vertex buffer." ), -4 );
		}
		for( MapilInt32 i = 0; i < frame.m_Mesh.m_Vertices.size() / 3; ++i ){
			pBuf[ i ].m_Vertex[ 0 ] = frame.m_Mesh.m_Vertices[ i * 3 ];
			pBuf[ i ].m_Vertex[ 1 ] = frame.m_Mesh.m_Vertices[ i * 3 + 1 ];
			pBuf[ i ].m_Vertex[ 2 ] = frame.m_Mesh.m_Vertices[ i * 3 + 2 ];
		}
		for( MapilInt32 i = 0; i < frame.m_Mesh.m_Normals.size() / 3; ++i ){
			pBuf[ i ].m_Normal[ 0 ] = frame.m_Mesh.m_Normals[ i * 3 ];
			pBuf[ i ].m_Normal[ 1 ] = frame.m_Mesh.m_Normals[ i * 3 + 1 ];
			pBuf[ i ].m_Normal[ 2 ] = frame.m_Mesh.m_Normals[ i * 3 + 2 ];
		}
		for( MapilInt32 i = 0; i < frame.m_Mesh.m_TexCoords.size() / 2; ++i ){
			pBuf[ i ].m_TexCoord[ 0 ] = frame.m_Mesh.m_TexCoords[ i * 2 ];
			pBuf[ i ].m_TexCoord[ 1 ] = frame.m_Mesh.m_TexCoords[ i * 2 + 1 ];
		}
		pFrame->m_Mesh.m_pVertex->Unlock();

		// Write to index buffer.
		WORD* pIdxBuf;
		if( pFrame->m_Mesh.m_pIndex->Lock( 0, 0, reinterpret_cast < LPVOID* > ( &pIdxBuf ), 0 ) ){
			throw MapilException( CURRENT_POSITION, TSTR( "Failed to lock index buffer." ), -5 );
		}
		for( MapilInt32 i = 0; i < frame.m_Mesh.m_Indices.size(); ++i ){
			pIdxBuf[ i ] = frame.m_Mesh.m_Indices[ i ];
		}
		pFrame->m_Mesh.m_pIndex->Unlock();

		// !!!!! temporary
		MapilInt32 material = -1;
		for( MapilInt32 i = 0; i < frame.m_Mesh.m_Material.size(); ++i ){
			if( ::strcmp( "", frame.m_Mesh.m_Material[ i ].m_TexFileName ) ){
#ifdef CHAR_CODE_UNICODE
				//Change Multi-byte character into Unicode character
				WCHAR textureFileName[ MAX_PATH ];
				MultiByteToWideChar( CP_ACP, 0, frame.m_Mesh.m_Material[ i ].m_TexFileName, -1, textureFileName, MAX_PATH );
				textureFileName[ MAX_PATH - 1 ] = 0;
				pFrame->m_Mesh.m_pTexture = new D3DTexture( m_pDev );
				pFrame->m_Mesh.m_pTexture->Create( textureFileName );
				material = i;
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

		if( material == -1 && frame.m_Mesh.m_Material.size() >= 1 ){
			material = 0;
		}

		if( material != -1 ){
			pFrame->m_Mesh.m_pMaterial = new ::D3DMATERIAL9[ 1 ];
			D3DCOLORVALUE color;
			color.a = frame.m_Mesh.m_Material[ material ].m_Ambient[ 0 ];
			color.r = frame.m_Mesh.m_Material[ material ].m_Ambient[ 1 ];
			color.g = frame.m_Mesh.m_Material[ material ].m_Ambient[ 2 ];
			color.b = frame.m_Mesh.m_Material[ material ].m_Ambient[ 3 ];
			pFrame->m_Mesh.m_pMaterial->Ambient = color;
			color.a = frame.m_Mesh.m_Material[ material ].m_Diffuse[ 0 ];
			color.r = frame.m_Mesh.m_Material[ material ].m_Diffuse[ 1 ];
			color.g = frame.m_Mesh.m_Material[ material ].m_Diffuse[ 2 ];
			color.b = frame.m_Mesh.m_Material[ material ].m_Diffuse[ 3 ];
			pFrame->m_Mesh.m_pMaterial->Diffuse = color;
			color.a = frame.m_Mesh.m_Material[ material ].m_Emissive[ 0 ];
			color.r = frame.m_Mesh.m_Material[ material ].m_Emissive[ 1 ];
			color.g = frame.m_Mesh.m_Material[ material ].m_Emissive[ 2 ];
			color.b = frame.m_Mesh.m_Material[ material ].m_Emissive[ 3 ];
			pFrame->m_Mesh.m_pMaterial->Emissive = color;
			color.a = frame.m_Mesh.m_Material[ material ].m_Specular[ 0 ];
			color.r = frame.m_Mesh.m_Material[ material ].m_Specular[ 1 ];
			color.g = frame.m_Mesh.m_Material[ material ].m_Specular[ 2 ];
			color.b = frame.m_Mesh.m_Material[ material ].m_Specular[ 3 ];
			pFrame->m_Mesh.m_pMaterial->Specular = color;
			pFrame->m_Mesh.m_pMaterial->Power = frame.m_Mesh.m_Material[ material ].m_Power;
		}

		

		pFrame->m_Mesh.m_VertexTotal = frame.m_Mesh.m_Vertices.size() / 3;
		pFrame->m_Mesh.m_IndexTotal = frame.m_Mesh.m_Indices.size() / 3;

		
	}

	MapilVoid D3DAnimModel::Create( const MapilTChar* pFileName )
	{
		Assert( !m_IsUsed, CURRENT_POSITION,TSTR( "The model was already created." ), -1 );

		MapilChar name[ 1024 ];
		ConvertToMultiByte( pFileName, -1, name, 1024 );

		AnimModelData* pModelData = new AnimModelData();

		// Analyze file format.
		XAnimFile* pModelFile = new XAnimFile;
		pModelFile->Load( name );
		pModelFile->CopyToModelData( pModelData );
		SafeDelete( pModelFile );

		// Create all frames.
		CreateFrame( pModelData->m_RootFame, &m_RootFrame );

		// Create animation structure.
		m_Animation = pModelData->m_Animation;

		m_IsUsed = MapilTrue;

		SafeDelete( pModelData );
	}

	
	MapilVoid D3DAnimModel::Create( Archiver* pArchiver, const MapilTChar* pXFileName, const MapilTChar* pTextureFileName )
	{
	}

	MapilVoid D3DAnimModel::DrawFrame( const Frame& frame )
	{
		// Draw first child.
		if( frame.m_pFirstChild ){
			DrawFrame( *frame.m_pFirstChild );
		}

		// Draw sibling
		if( frame.m_pSibling ){
			DrawFrame( *frame.m_pSibling );
		}

		DrawMesh( frame.m_Mesh );
	}

	MapilVoid D3DAnimModel::DrawMesh( const Frame::Mesh& mesh )
	{
		if( mesh.m_pVertex == NULL ){
			return;
		}

		m_pDev->GetDev().GetPointer()->SetVertexDeclaration( mesh.m_pVertexDecl );
		m_pDev->GetDev().GetPointer()->SetStreamSource( 0, mesh.m_pVertex, 0, sizeof( VertexFormat ) );
		m_pDev->GetDev().GetPointer()->SetIndices( mesh.m_pIndex );
		if( mesh.m_pMaterial ){
			m_pDev->GetDev().GetPointer()->SetMaterial( &mesh.m_pMaterial[ 0 ] );
		}
		if( mesh.m_pTexture ){
			m_pDev->GetDev().GetPointer()->SetTexture( 0, reinterpret_cast < ::LPDIRECT3DTEXTURE9 > ( mesh.m_pTexture->Get() ) );
		}
		m_pDev->GetDev().GetPointer()->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, mesh.m_VertexTotal, 0, mesh.m_IndexTotal );
	}

	MapilVoid D3DAnimModel::Draw()
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The mesh isn't created yet." ), -1 );

		DrawModel();
	}

	MapilVoid D3DAnimModel::Draw( const Matrix4x4 < MapilFloat32 >& mat )
	{
		Assert(	m_IsUsed, CURRENT_POSITION, TSTR( "The mesh isn't created yet." ), -1 );

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

	MapilVoid D3DAnimModel::DrawModel()
	{
		DrawFrame( m_RootFrame );
	}

	MapilBool D3DAnimModel::DetectCollision(	const Vector3 < MapilFloat32 >& vRayDir,
											const Vector3 < MapilFloat32 >& vRayOrig,
											Vector2 < MapilFloat32 >* pVCollisionPos,
											MapilFloat32* pDistance )
	{
		return MapilFalse;
	}

}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D