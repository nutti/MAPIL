/**
*	@file	D3DSkinMeshModel.h
*	@brief	
*	@date	2013.4.12 (Fri) 23:35
*/

#ifndef INCLUDED_MAPIL_D3DSKINMESHMODEL_H
#define INCLUDED_MAPIL_D3DSKINMESHMODEL_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3dx9.h>
#include <map>

#include "SkinMeshModel.h"
#include "D3DTexture.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{

	class AllocateHierarchy;
	class D3DSkinMeshModel : public SkinMeshModel
	{
	public:

		// Bone information.
		struct Frame : public D3DXFRAME
		{
			MapilInt32			m_ID;			///< Frame ID.
			::D3DXMATRIXA16		m_OffsetMat;	///< Bone offset matrix.
			Frame();
		};

		// Optimized mesh container.
		struct MeshContainer : public D3DXMESHCONTAINER
		{
			DWORD				m_InflBoneTotal;		///< Influence bone total.
			DWORD				m_BoneGroupTotal;		///< Bone group total.
			ID3DXBuffer*		m_pBoneCombTable;		///< Index array.
			MeshContainer();
		};

	private:
		AllocateHierarchy*					m_pAlloc;
		Frame*								m_pRootFrame;
		::ID3DXAnimationController*			m_pAnimCtrl;
		::D3DXBONECOMBINATION*				m_pBoneComb;
		MeshContainer*						m_pMesh;
		D3DTexture*							m_pTexture;

		MapilVoid DrawModel( const Matrix4x4 < MapilFloat32 >& mat );
		MeshContainer* GetMesh( ::D3DXFRAME* pFrame );
		MapilVoid SetFrameID( Frame* pFrame, ::ID3DXSkinInfo* pSkin );
		MapilVoid UpdateCombMat(	const Matrix4x4 < MapilFloat32 >& worldMat,
									std::map < DWORD, D3DXMATRIX >& combMatMap,
									D3DSkinMeshModel::Frame* pFrame );
	public:
		D3DSkinMeshModel( SharedPointer < GraphicsDevice > pDev );
		~D3DSkinMeshModel();
		MapilVoid Create( const MapilTChar* pFileName );
		MapilVoid Create( Archiver* pArchiver, const MapilTChar* pXFileName, const MapilTChar* pTextureFileName );
		MapilVoid Draw();
		MapilVoid Draw( const Matrix4x4 < MapilFloat32 >& mat );
		MapilVoid Draw( MapilDouble time );
		MapilVoid Draw( MapilDouble time, const Matrix4x4 < MapilFloat32 >& mat );
		MapilBool DetectCollision(	const Vector3 < MapilFloat32 >& vRayDir,
									const Vector3 < MapilFloat32 >& vRayOrig,
									Vector2 < MapilFloat32 >* pVCollisionPos,
									MapilFloat32* pDistance ){ return MapilFalse; }
	};
}

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DSKINMODEL_H