/**
*	@file	D3DSkinMeshModel.cpp
*	@brief	
*	@date	2013.4.12 (Fri) 23:35
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_9_0_C )

#include <map>

#include "../../Include/MAPIL/Graphics/D3DSkinMeshModel.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Util/String.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DSkinMeshModel::Frame::Frame() : m_ID( 0xFFFFFFFF )
	{
		::D3DXMatrixIdentity( &m_OffsetMat );
	}

	D3DSkinMeshModel::MeshContainer::MeshContainer() : m_InflBoneTotal( 1 ), m_BoneGroupTotal( 0 ), m_pBoneCombTable( NULL )
	{
	}

	class AllocateHierarchy : public ID3DXAllocateHierarchy
	{
	private:
		MapilChar* StrCpy( const MapilChar* pName )
		{
			MapilChar* pNewStr = 0;
			if( pName == NULL || pName[ 0 ] == '\0' ){
				pNewStr = new MapilChar[ 1 ];
				pNewStr[ 0 ] = '\0';
			}
			else{
				MapilUInt32 len = ::strlen( pName );
				pNewStr = new MapilChar[ len + 1 ];
				::strcpy( pNewStr, pName );
			}
			return pNewStr;
		}
	public:
		AllocateHierarchy(){}
		~AllocateHierarchy(){}
		// Create frame.
		STDMETHOD (CreateFrame) ( THIS_ LPCSTR pName, LPD3DXFRAME* ppNewFrame )
		{
			D3DSkinMeshModel::Frame* pNewFrame = new D3DSkinMeshModel::Frame;
			pNewFrame->Name = StrCpy( pName );		// Frame name.
			pNewFrame->pFrameFirstChild = NULL;		// First child of this frame.
			pNewFrame->pFrameSibling = NULL;		// Sibling of this frame.
			pNewFrame->pMeshContainer = NULL;		// Mesh
			::D3DXMatrixIdentity( &pNewFrame->TransformationMatrix );	// Translation matrix.
			*ppNewFrame = pNewFrame;

			return D3D_OK;
		}
		// Destroy frame.
		STDMETHOD (DestroyFrame) ( THIS_ LPD3DXFRAME pFrame )
		{
			if( pFrame->pFrameFirstChild ){
				DestroyFrame( pFrame->pFrameFirstChild );
			}
			if( pFrame->pFrameSibling ){
				DestroyFrame( pFrame->pFrameSibling );
			}
			if( pFrame->pMeshContainer ){
				DestroyMeshContainer( pFrame->pMeshContainer );
			}

			SafeDeleteArray( pFrame->Name );
			SafeDelete( pFrame );

			return D3D_OK;
		}
		// Create mesh.
		STDMETHOD (CreateMeshContainer) (	THIS_ LPCSTR pName,
											CONST D3DXMESHDATA* pMesh,
											CONST D3DXMATERIAL* pMtrl,
											CONST D3DXEFFECTINSTANCE* pEffect,
											DWORD numMtrl,
											CONST DWORD* pAdj,
											LPD3DXSKININFO pSkin,
											LPD3DXMESHCONTAINER* ppNewMesh )
		{
			D3DSkinMeshModel::MeshContainer* pNewMesh = new D3DSkinMeshModel::MeshContainer;
			pNewMesh->Name = StrCpy( pName );

			pNewMesh->pAdjacency = new DWORD[ pMesh->pMesh->GetNumFaces() * 3 ];
			::memset( pNewMesh->pAdjacency, 0, pMesh->pMesh->GetNumFaces() * 3 * sizeof( DWORD ) );
			pNewMesh->MeshData.Type = pMesh->Type;

			// Covert to blended mesh.
			pSkin->ConvertToBlendedMesh(	pMesh->pMesh,
											0,
											pAdj,
											pNewMesh->pAdjacency,
											0,
											0,
											&pNewMesh->m_InflBoneTotal,
											&pNewMesh->m_BoneGroupTotal,
											&pNewMesh->m_pBoneCombTable,
											&pNewMesh->MeshData.pMesh );

			pNewMesh->NumMaterials = numMtrl;
			pNewMesh->pMaterials = new ::D3DXMATERIAL [ numMtrl ];
			for( MapilInt32 i = 0; i < pNewMesh->NumMaterials; ++i ){
				::memcpy( &pNewMesh->pMaterials[ i ].MatD3D, &pMtrl->MatD3D, sizeof( ::D3DMATERIAL9 ) );
				if( pMtrl->pTextureFilename != NULL && pMtrl->pTextureFilename[ 0 ] != '\0' ){
					MapilInt32 size = ::strlen( pMtrl->pTextureFilename );
					pNewMesh->pMaterials[ i ].pTextureFilename = new MapilChar [ size + 1 ];
					::strncpy( pNewMesh->pMaterials[ i ].pTextureFilename, pMtrl->pTextureFilename, size );
					pNewMesh->pMaterials[ i ].pTextureFilename[ size ] = '\0';
				}
				else{
					pNewMesh->pMaterials[ i ].pTextureFilename = NULL;
				}
			}
			//::memcpy( pNewMesh->pMaterials, pMtrl, numMtrl * sizeof( ::D3DXMATERIAL ) );

			pNewMesh->pEffects = 0;
			if( pEffect ){
				pNewMesh->pEffects = new ::D3DXEFFECTINSTANCE;
				pNewMesh->pEffects->pEffectFilename = StrCpy( pEffect->pEffectFilename );
				pNewMesh->pEffects->NumDefaults = pEffect->NumDefaults;
				pNewMesh->pEffects->pDefaults = new ::D3DXEFFECTDEFAULT[ pEffect->NumDefaults ];
				for( DWORD i = 0; i < pEffect->NumDefaults; ++i ){
					::D3DXEFFECTDEFAULT* pSrc = pEffect->pDefaults + i;
					::D3DXEFFECTDEFAULT* pDest = pNewMesh->pEffects->pDefaults + i;
					pDest->NumBytes = pSrc->NumBytes;
					pDest->Type = pSrc->Type;
					pDest->pParamName = StrCpy( pSrc->pParamName );
					pDest->pValue = new MapilChar[ pSrc->NumBytes ];
					::memcpy( pDest->pValue, pSrc->pValue, pSrc->NumBytes );
				}
			}

			pNewMesh->pSkinInfo = pSkin;
			pSkin->AddRef();

			*ppNewMesh = pNewMesh;

			return D3D_OK;
		}
		// Destroy mesh.
		STDMETHOD (DestroyMeshContainer) ( THIS_ LPD3DXMESHCONTAINER pMesh )
		{
			D3DSkinMeshModel::MeshContainer* pDelMesh = (D3DSkinMeshModel::MeshContainer*) pMesh;

			pDelMesh->MeshData.pMesh->Release();
			SafeDeleteArray( pDelMesh->Name );
			SafeDeleteArray( pDelMesh->pAdjacency );
			if( pDelMesh->pEffects ){
				for( DWORD i = 0; i < pDelMesh->pEffects->NumDefaults; ++i ){
					::D3DXEFFECTDEFAULT* p = pDelMesh->pEffects->pDefaults + i;
					SafeDeleteArray( p->pParamName );
					SafeDeleteArray( p->pValue );
				}
				SafeDeleteArray( pDelMesh->pEffects->pDefaults );
				SafeDeleteArray( pDelMesh->pEffects->pEffectFilename );
				SafeDelete( pDelMesh->pEffects );
			}
			for( MapilInt32 i = 0; i < pDelMesh->NumMaterials; ++i ){
				SafeDeleteArray( pDelMesh->pMaterials[ i ].pTextureFilename );
			}
			SafeDeleteArray( pDelMesh->pMaterials );

			if( pDelMesh->pSkinInfo ){
				pDelMesh->pSkinInfo->Release();
			}
			if( pDelMesh->m_pBoneCombTable ){
				pDelMesh->m_pBoneCombTable->Release();
			}

			SafeDelete( pDelMesh );

			return D3D_OK;
		}
	};


	D3DSkinMeshModel::D3DSkinMeshModel( SharedPointer < GraphicsDevice > pDev ) :	Model( pDev ),
																					m_pAlloc( NULL ),
																					m_pRootFrame( NULL ),
																					m_pAnimCtrl( NULL ),
																					m_pBoneComb( NULL ),
																					m_pMesh( NULL )

	{
	}

	D3DSkinMeshModel::~D3DSkinMeshModel()
	{
		m_pAlloc->DestroyFrame( m_pRootFrame );
		m_pAnimCtrl->Release();

		SafeDelete( m_pAlloc );
		SafeDelete( m_pTexture );
	}


	MapilVoid D3DSkinMeshModel::Create( const MapilTChar* pFileName )
	{
		m_pAlloc = new AllocateHierarchy;

		::D3DXLoadMeshHierarchyFromX(	pFileName,
										D3DXMESH_MANAGED,
										m_pDev->GetDev().GetPointer(),
										m_pAlloc,
										0,
										reinterpret_cast < ::D3DXFRAME** > ( &m_pRootFrame ),
										&m_pAnimCtrl );

		m_pMesh = GetMesh( m_pRootFrame );
		m_pBoneComb = reinterpret_cast < ::D3DXBONECOMBINATION* > ( m_pMesh->m_pBoneCombTable->GetBufferPointer() );

		for( MapilInt32 i = 0; i < m_pMesh->NumMaterials; ++i ){
			if( m_pMesh->pMaterials[ i ].pTextureFilename != NULL && m_pMesh->pMaterials[ i ].pTextureFilename[ 0 ] != '\0' ){
				m_pTexture = new D3DTexture( m_pDev );
				MapilInt32 size = ::strlen( m_pMesh->pMaterials[ i ].pTextureFilename ) + 1;
				MapilTChar* pBuf = new MapilTChar [ size + 1 ];
				ConvertToTChar( m_pMesh->pMaterials[ i ].pTextureFilename, -1, pBuf, sizeof( MapilTChar ) * ( size + 1 ) );
				m_pTexture->Create( pBuf );
				SafeDeleteArray( pBuf );
				break;
			}
		}
		
		// Setup bone ID and offset matrix on frame.
		SetFrameID( m_pRootFrame, m_pMesh->pSkinInfo );
	}
	

	MapilVoid D3DSkinMeshModel::Draw()
	{
		m_pAnimCtrl->AdvanceTime( 0.0001f, 0 );
		
		// Update combination matrix.
		std::map < DWORD, ::D3DXMATRIX > combMatMap;
		UpdateCombMat( combMatMap, m_pRootFrame );

		m_pDev->GetDev().GetPointer()->SetTexture( 0, reinterpret_cast < ::LPDIRECT3DTEXTURE9 > ( m_pTexture->Get() ) );

		if( m_pMesh->NumMaterials > 0 ){
			m_pDev->GetDev().GetPointer()->SetMaterial( &m_pMesh->pMaterials[ 0 ].MatD3D );
		}

		for( DWORD i = 0; i < m_pMesh->m_BoneGroupTotal; ++i ){
			DWORD boneTotal = 0;
			for( DWORD j = 0; j < m_pMesh->m_InflBoneTotal; ++j ){
				DWORD id = m_pBoneComb[ i ].BoneId[ j ];
				if( id != UINT_MAX ){
					m_pDev->GetDev().GetPointer()->SetTransform( D3DTS_WORLDMATRIX( j ), &combMatMap[ id ] );
					++boneTotal;
				}
			}
			m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_VERTEXBLEND, boneTotal - 1 );
			
			m_pMesh->MeshData.pMesh->DrawSubset( i );
		}
	}

	MapilVoid D3DSkinMeshModel::Draw( const Matrix4x4 < MapilFloat32 >& mat )
	{
	}

	MapilVoid D3DSkinMeshModel::DrawModel()
	{
	}

	D3DSkinMeshModel::MeshContainer* D3DSkinMeshModel::GetMesh( ::D3DXFRAME* pFrame )
	{
		if( pFrame->pMeshContainer ){
			return ( MeshContainer* ) pFrame->pMeshContainer;
		}
		if( pFrame->pFrameFirstChild ){
			D3DSkinMeshModel::MeshContainer* pMesh = GetMesh( pFrame->pFrameFirstChild );
			if( pMesh != NULL ){
				return pMesh;
			}
		}
		if( pFrame->pFrameSibling ){
			D3DSkinMeshModel::MeshContainer* pMesh = GetMesh( pFrame->pFrameSibling );
			if( pMesh != NULL ){
				return pMesh;
			}
		}

		return NULL;
	}

	MapilVoid D3DSkinMeshModel::SetFrameID( D3DSkinMeshModel::Frame* pFrame, ::ID3DXSkinInfo* pSkin )
	{
		// Setup maps between skin ID and bone name.
		std::map < std::string, DWORD > idMap;
		for( DWORD i = 0; i < pSkin->GetNumBones(); ++i ){
			idMap[ pSkin->GetBoneName( i ) ] = i;
		}

		// Setup relations between bone name and skin ID.
		struct FrameIDBuilder
		{
			static MapilVoid Create( std::map < std::string, DWORD > idMap, ::ID3DXSkinInfo* pSkin, D3DSkinMeshModel::Frame* pFrame )
			{
				if( idMap.find( pFrame->Name ) != idMap.end() ){
					pFrame->m_ID = idMap[ pFrame->Name ];
					pFrame->m_OffsetMat = *pSkin->GetBoneOffsetMatrix( pFrame->m_ID );
				}
				if( pFrame->pFrameFirstChild ){
					Create( idMap, pSkin, reinterpret_cast < D3DSkinMeshModel::Frame* > ( pFrame->pFrameFirstChild ) );
				}
				if( pFrame->pFrameSibling ){
					Create( idMap, pSkin, reinterpret_cast < D3DSkinMeshModel::Frame* > ( pFrame->pFrameSibling ) );
				}
			}
		};

		FrameIDBuilder::Create( idMap, pSkin, pFrame );
	}

	MapilVoid D3DSkinMeshModel::UpdateCombMat( std::map < DWORD, D3DXMATRIX >& combMatMap, D3DSkinMeshModel::Frame* pFrame )
	{
		// Update combination matrix.
		struct CombMatUpdater
		{
			static MapilVoid Update( std::map < DWORD, D3DXMATRIX >& combMatMap, D3DXMATRIX& parentBoneMat, D3DSkinMeshModel::Frame* pFrame )
			{
				::D3DXMATRIX& localBoneMat = pFrame->TransformationMatrix;
				::D3DXMATRIX boneMat = localBoneMat * parentBoneMat;		// Bone matrix = Local matrix * Parent bone matrix
				if( pFrame->m_ID != 0xFFFFFFFF ){
					combMatMap[ pFrame->m_ID ] = pFrame->m_OffsetMat * boneMat;		// Comb matrix = Offset matrix * Bone matrix
				}
				if( pFrame->pFrameFirstChild ){
					Update( combMatMap, boneMat, reinterpret_cast < D3DSkinMeshModel::Frame* > ( pFrame->pFrameFirstChild ) );
				}
				if( pFrame->pFrameSibling ){
					Update( combMatMap, parentBoneMat, reinterpret_cast < D3DSkinMeshModel::Frame* > ( pFrame->pFrameSibling ) );
				}
			}
		};

		::D3DXMATRIX mat;
		::D3DXMatrixIdentity( &mat );
		CombMatUpdater::Update( combMatMap, mat, pFrame );
	}
}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D