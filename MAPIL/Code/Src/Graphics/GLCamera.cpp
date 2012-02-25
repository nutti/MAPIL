/**
*	@file	GLCamera.cpp
*	@brief	Implementation of GLCamera.
*	@date	2011.6.19 (Sun) 12:4
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#if defined ( API_WIN32API )
#include <Windows.h>
#endif
#if defined ( OS_WIN_32BIT )
#include <gl/GL.h>
#include <gl/GLU.h>
#endif
#if defined ( OS_LINUX_32BIT )
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "../../Include/MAPIL/Graphics/GLCamera.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GLCamera::GLCamera( SharedPointer < GraphicsDevice > pDev ) : Camera( pDev )
	{
		ZeroObject( m_ViewMat, sizeof( m_ViewMat ) );
		ZeroObject( m_ProjMat, sizeof( m_ProjMat ) );
	}
	
	GLCamera::~GLCamera()
	{
		ZeroObject( m_ViewMat, sizeof( m_ViewMat ) );
		ZeroObject( m_ProjMat, sizeof( m_ProjMat ) );
	}
	
	MapilVoid GLCamera::Create(	const Vector3 < MapilFloat32 >& vEye,
								const Vector3 < MapilFloat32 >& vLook,
								const Vector3 < MapilFloat32 >& vUp,
								MapilFloat32 fovy,
								MapilFloat32 aspect,
								MapilFloat32 nearClip,
								MapilFloat32 farClip )
	{
		SetViewTransMat( vEye, vLook, vUp );
		SetProjectionTransMat( fovy, aspect, nearClip, farClip );
	}

	// Create. ( 2 )
	MapilVoid GLCamera::Create(	MapilFloat32 eyeX,
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
		SetViewTransMat( eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ );
		SetProjectionTransMat( fovy, aspect, nearClip, farClip );
	}

	// Create. ( 3 )
	MapilVoid GLCamera::Create(	const Vector3 < MapilFloat32 >& vEye,
								const Vector3 < MapilFloat32 >& vLook,
								const Vector3 < MapilFloat32 >& vUp,
								MapilFloat32 left,
								MapilFloat32 right,
								MapilFloat32 bottom,
								MapilFloat32 top,
								MapilFloat32 nearClip,
								MapilFloat32 farClip )
	{
		SetViewTransMat( vEye, vLook, vUp );
		SetProjectionTransMat( left, right, bottom, top, nearClip, farClip );
	}

	// Create. ( 4 )
	MapilVoid GLCamera::Create(	MapilFloat32 eyeX,
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
		SetViewTransMat( eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ );
		SetProjectionTransMat( left, right, bottom, top, nearClip, farClip );
	}

	// Set view transformation matrix (1)
	MapilVoid GLCamera::SetViewTransMat(	MapilFloat32 eyeX,
												MapilFloat32 eyeY,
												MapilFloat32 eyeZ,
												MapilFloat32 lookX,
												MapilFloat32 lookY,
												MapilFloat32 lookZ,
												MapilFloat32 upX,
												MapilFloat32 upY,
												MapilFloat32 upZ )
	{
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		gluLookAt( eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ );
		glGetFloatv( GL_MODELVIEW_MATRIX, m_ViewMat );
	}
	
	// Set view transformation matrix (2)
	MapilVoid GLCamera::SetViewTransMat(	const Vector3 < MapilFloat32 >& vEye,
											const Vector3 < MapilFloat32 >& vLook,
											const Vector3 < MapilFloat32 >& vUp )
	{
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		gluLookAt( vEye.m_X, vEye.m_Y, vEye.m_Z, vLook.m_X, vLook.m_Y, vLook.m_Z, vUp.m_X, vUp.m_Y, vUp.m_Z );
		glGetFloatv( GL_MODELVIEW_MATRIX, m_ViewMat );
	}
	
	// Set projection transformation matrix
	MapilVoid GLCamera::SetProjectionTransMat(	MapilFloat32 fovy,
												MapilFloat32 aspect,
												MapilFloat32 nearClip,
												MapilFloat32 farClip )
	{
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		MapilFloat32 theta = static_cast < MapilFloat32 > ( fovy * 180.0 / 3.1415926535 );
		gluPerspective( theta, aspect, nearClip, farClip );
		glGetFloatv( GL_PROJECTION_MATRIX, m_ProjMat );
	}
	
	// Set projection transformation matrix. ( Orthogonal projection. )
	MapilVoid GLCamera::SetProjectionTransMat(	MapilFloat32 left,
												MapilFloat32 right,
												MapilFloat32 bottom,
												MapilFloat32 top,
												MapilFloat32 nearClip,
												MapilFloat32 farClip )
	{
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho( left, right, bottom, top, nearClip, farClip );
		glGetFloatv( GL_PROJECTION_MATRIX, m_ProjMat );
	}
	
	// Enable camera
	MapilVoid GLCamera::Enable()
	{
		glMatrixMode( GL_MODELVIEW );
		glLoadMatrixf( m_ViewMat );
		glMatrixMode( GL_PROJECTION );
		glLoadMatrixf( m_ProjMat );
	}
}

#endif	// API_OPENGL
