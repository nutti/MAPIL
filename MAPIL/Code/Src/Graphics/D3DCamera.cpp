/**
*	@file	D3DCamera.cpp
*	@brief	Implementation of D3DCamera.
*	@date	2011.8.24 (Wed) 21:25
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_9_0_C )

#include "../../Include/MAPIL/Graphics/D3DCamera.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DCamera::D3DCamera( SharedPointer < GraphicsDevice > pDev ) :	Camera( pDev ),
																	m_ViewMat(),
																	m_ProjMat()
	{
	}

	D3DCamera::~D3DCamera()
	{
		m_IsUsed = MapilFalse;
	}

	// Create. ( 1 )
	MapilVoid D3DCamera::Create(	const Vector3 < MapilFloat32 >& vEye,
									const Vector3 < MapilFloat32 >& vLook,
									const Vector3 < MapilFloat32 >& vUp,
									MapilFloat32 fovy,
									MapilFloat32 aspect,
									MapilFloat32 nearClip,
									MapilFloat32 farClip )
	{
		Assert( !m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DCamera" ),
				TSTR( "Create" ),
				TSTR( "The camera was already created." ),
				-1 );

		m_IsUsed = MapilTrue;

		SetViewTransMat( vEye, vLook, vUp );
		SetProjectionTransMat( fovy, aspect, nearClip, farClip );
	}

	// Create. ( 2 )
	MapilVoid D3DCamera::Create(	MapilFloat32 eyeX,
									MapilFloat32 eyeY,
									MapilFloat32 eyeZ,
									MapilFloat32 lookX,
									MapilFloat32 lookY,
									MapilFloat32 lookZ,
									MapilFloat32 upX,
									MapilFloat32 upY,
									MapilFloat32 upZ,
									MapilFloat32 fovy,
									MapilFloat32 aspect,
									MapilFloat32 nearClip,
									MapilFloat32 farClip )
	{
		Assert( !m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DCamera" ),
				TSTR( "Create" ),
				TSTR( "The camera was already created." ),
				-1 );

		m_IsUsed = MapilTrue;

		SetViewTransMat( eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ );
		SetProjectionTransMat( fovy, aspect, nearClip, farClip );
	}

	// Create. ( 3 )
	MapilVoid D3DCamera::Create(	const Vector3 < MapilFloat32 >& vEye,
						const Vector3 < MapilFloat32 >& vLook,
						const Vector3 < MapilFloat32 >& vUp,
						MapilFloat32 left,
						MapilFloat32 right,
						MapilFloat32 bottom,
						MapilFloat32 top,
						MapilFloat32 nearClip,
						MapilFloat32 farClip )
	{
		Assert( !m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DCamera" ),
				TSTR( "Create" ),
				TSTR( "The camera was already created." ),
				-1 );

		m_IsUsed = MapilTrue;

		SetViewTransMat( vEye, vLook, vUp );
		SetProjectionTransMat( left, right, bottom, top, nearClip, farClip );
	}

	// Create. ( 4 )
	MapilVoid D3DCamera::Create(	MapilFloat32 eyeX,
						MapilFloat32 eyeY,
						MapilFloat32 eyeZ,
						MapilFloat32 lookX,
						MapilFloat32 lookY,
						MapilFloat32 lookZ,
						MapilFloat32 upX,
						MapilFloat32 upY,
						MapilFloat32 upZ,
						MapilFloat32 left,
						MapilFloat32 right,
						MapilFloat32 bottom,
						MapilFloat32 top,
						MapilFloat32 nearClip,
						MapilFloat32 farClip )
	{
		Assert( !m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DCamera" ),
				TSTR( "Create" ),
				TSTR( "The camera was already created." ),
				-1 );

		m_IsUsed = MapilTrue;

		SetViewTransMat( eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ );
		SetProjectionTransMat( left, right, bottom, top, nearClip, farClip );
	}

	// Set view transformation matrix (1)
	MapilVoid D3DCamera::SetViewTransMat(	MapilFloat32 eyeX,
								MapilFloat32 eyeY,
								MapilFloat32 eyeZ,
								MapilFloat32 lookX,
								MapilFloat32 lookY,
								MapilFloat32 lookZ,
								MapilFloat32 upX,
								MapilFloat32 upY,
								MapilFloat32 upZ )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "Camera" ),
				TSTR( "SetViewTransMat" ),
				TSTR( "The camera isn't created yet." ),
				-1 );

		::D3DXVECTOR3 vEye( eyeX, eyeY, eyeZ );		//Position of camera
		::D3DXVECTOR3 vLook( lookX, lookY, lookZ );	//Look position of camera
		::D3DXVECTOR3 vUp( upX, upY, upZ );			//Up direction of camera

		//Create view transformation matrix
		::D3DXMatrixLookAtRH( &m_ViewMat, &vEye, &vLook, &vUp );
	}

	// Set view transformation matrix (2)
	MapilVoid D3DCamera::SetViewTransMat(	const Vector3 < MapilFloat32 >& vEye,
											const Vector3 < MapilFloat32 >& vLook,
											const Vector3 < MapilFloat32 >& vUp )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "Camera" ),
				TSTR( "SetViewTransMat" ),
				TSTR( "The camera isn't created yet." ),
				-1 );

		::D3DXVECTOR3 vE( vEye.m_X, vEye.m_Y, vEye.m_Z );		//Position of camera
		::D3DXVECTOR3 vL( vLook.m_X, vLook.m_Y, vLook.m_Z );	//Look position of camera
		::D3DXVECTOR3 vU( vUp.m_X, vUp.m_Y, vUp.m_Z );		//Up direction of camera

		//Create view transformation matrix
		::D3DXMatrixLookAtRH( &m_ViewMat, &vE, &vL, &vU );
	}

	// Set projection transformation matrix
	MapilVoid D3DCamera::SetProjectionTransMat(	MapilFloat32 fovy,
												MapilFloat32 aspect,
												MapilFloat32 nearClip,
												MapilFloat32 farClip )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "Camera" ),
				TSTR( "SetProjectionTransMat" ),
				TSTR( "The camera isn't created yet." ),
				-1 );

		//Create projection transformation matrix
		::D3DXMatrixPerspectiveFovRH( &m_ProjMat, fovy, aspect, nearClip, farClip );
	}

	// Set projection transformation matrix. ( Orthogonal projection. )
	MapilVoid D3DCamera::SetProjectionTransMat(	MapilFloat32 left,
										MapilFloat32 right,
										MapilFloat32 bottom,
										MapilFloat32 top,
										MapilFloat32 nearClip,
										MapilFloat32 farClip )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "Camera" ),
				TSTR( "SetProjectionTransMat" ),
				TSTR( "The camera isn't created yet." ),
				-1 );

		::D3DXMatrixOrthoOffCenterRH( &m_ProjMat, left, right, bottom, top, nearClip, farClip );
	}

	// Enable camera
	MapilVoid D3DCamera::Enable()
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "Camera" ),
				TSTR( "Enable" ),
				TSTR( "The camera isn't created yet." ),
				-1 );

		m_pDev->GetDev().GetPointer()->SetTransform( D3DTS_VIEW, &m_ViewMat );
		m_pDev->GetDev().GetPointer()->SetTransform( D3DTS_PROJECTION, &m_ProjMat );
	}

	Matrix4x4 < MapilFloat32 > D3DCamera::GetInvViewTransMat() const
	{
		::D3DXMATRIXA16 invMat;
		::D3DXMatrixInverse( &invMat, NULL, &m_ViewMat );

		Matrix4x4 < MapilFloat32 > mat;

		for( MapilInt32 i = 0; i < 4; ++i ){
			for( MapilInt32 j = 0; j < 4; ++j ){
				mat.m_Elm[ i ][ j ] = invMat.m[ i ][ j ];
			}
		}

		return mat;
	}

	Matrix4x4 < MapilFloat32 > D3DCamera::GetInvProjTransMat() const
	{
		::D3DXMATRIXA16 invMat;
		::D3DXMatrixInverse( &invMat, NULL, &m_ProjMat );

		Matrix4x4 < MapilFloat32 > mat;

		for( MapilInt32 i = 0; i < 4; ++i ){
			for( MapilInt32 j = 0; j < 4; ++j ){
				mat.m_Elm[ i ][ j ] = invMat.m[ i ][ j ];
			}
		}

		return mat;
	}
}

#endif	// DIRECT3D_VERSION
#endif