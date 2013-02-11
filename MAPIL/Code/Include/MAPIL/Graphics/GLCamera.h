/**
*	@file	GLCamera.h
*	@brief	This class is derived from Camera class. GLCamera is implemented
*			for OpenGL. The users shouldn't call a method from this class
*			directly.
*	@date	2011.6.19 (Sun) 12:4
*/

#ifndef INCLUDED_MAPIL_GLCAMERA_H
#define INCLUDED_MAPIL_GLCAMERA_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

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

#include "Camera.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class GLCamera : public Camera
	{
	private:
		GLfloat		m_ViewMat[ 16 ];		///< View transformation matrix.
		GLfloat		m_ProjMat[ 16 ];		///< Projection transformation matrix.
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		GLCamera( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLCamera();
		/**
		*	@brief			Create Camera.
		*	@param vEye		The position of the camera.
		*	@param vLook	A point of view.
		*	@param vUp		Tilt of the camera.
		*	@param fovy		Fovy.
		*	@param aspect	Aspect ratio.
		*	@param nearClip	The nearest Z-Coordinate to be displayed.
		*	@param farClip	The farthest Z-Coordinate to be displayed.
		*/
		MapilVoid Create(	const Vector3 < MapilFloat32 >& vEye,
							const Vector3 < MapilFloat32 >& vLook,
							const Vector3 < MapilFloat32 >& vUp,
							MapilFloat32 fovy,
							MapilFloat32 aspect,
							MapilFloat32 nearClip,
							MapilFloat32 farClip );
		/**
		*	@brief			Create Camera.
		*	@param eyeX		The X-Coordinate of the camera to be positioned.
		*	@param eyeY		The Y-Coordinate of the camera to be positioned.
		*	@param eyeZ		The Z-Coordinate of the camera to be positioned.
		*	@param lookX	The X-Coordinate of the viewpoint.
		*	@param lookY	The Y-Coordinate of the viewpoint.
		*	@param lookZ	The Z-Coordinate of the viewpoint.
		*	@param upX		The X-Component of the tilt.
		*	@param upY		The Y-Component of the tilt.
		*	@param upZ		The Z-Component of the tilt.
		*	@param fovy		Fovy.
		*	@param aspect	Aspect ratio.
		*	@param nearClip	The nearest Z-Coordinate to be displayed.
		*	@param farClip	The farthest Z-Coordinate to be displayed.
		*/
		MapilVoid Create(	MapilFloat32 eyeX,
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
							MapilFloat32 farClip );
		/**
		*	@brief			Create Camera.
		*	@param vEye		The position of the camera.
		*	@param vLook	A point of view.
		*	@param vUp		Tilt of the camera.
		*	@param left		Left edge to be displayed.
		*	@param right	Right edge to be displayed.
		*	@param bottom	Bottom edge to be displayed.
		*	@param top		Top edge to be displayed.
		*	@param nearClip	The nearest Z-Coordinate to be displayed.
		*	@param farClip	The farthest Z-Coordinate to be displayed.
		*/
		MapilVoid Create(	const Vector3 < MapilFloat32 >& vEye,
							const Vector3 < MapilFloat32 >& vLook,
							const Vector3 < MapilFloat32 >& vUp,
							MapilFloat32 left,
							MapilFloat32 right,
							MapilFloat32 bottom,
							MapilFloat32 top,
							MapilFloat32 nearClip,
							MapilFloat32 farClip );
		/**
		*	@brief			Create Camera.
		*	@param eyeX		The X-Coordinate of the camera to be positioned.
		*	@param eyeY		The Y-Coordinate of the camera to be positioned.
		*	@param eyeZ		The Z-Coordinate of the camera to be positioned.
		*	@param lookX	The X-Coordinate of the viewpoint.
		*	@param lookY	The Y-Coordinate of the viewpoint.
		*	@param lookZ	The Z-Coordinate of the viewpoint.
		*	@param upX		The X-Component of the tilt.
		*	@param upY		The Y-Component of the tilt.
		*	@param upZ		The Z-Component of the tilt.
		*	@param left		Left edge to be displayed.
		*	@param right	Right edge to be displayed.
		*	@param bottom	Bottom edge to be displayed.
		*	@param top		Top edge to be displayed.
		*	@param nearClip	The nearest Z-Coordinate to be displayed.
		*	@param farClip	The farthest Z-Coordinate to be displayed.
		*/
		MapilVoid Create(	MapilFloat32 eyeX,
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
							MapilFloat32 farClip );
		/**
		*	@brief			Set view transformation matrix.
		*	@param eyeX		The X-Coordinate of the camera to be positioned.
		*	@param eyeY		The Y-Coordinate of the camera to be positioned.
		*	@param eyeZ		The Z-Coordinate of the camera to be positioned.
		*	@param lookX	The X-Coordinate of the viewpoint.
		*	@param lookY	The Y-Coordinate of the viewpoint.
		*	@param lookZ	The Z-Coordinate of the viewpoint.
		*	@param upX		The X-Component of the tilt.
		*	@param upY		The Y-Component of the tilt.
		*	@param upZ		The Z-Component of the tilt.
		*/
		MapilVoid SetViewTransMat(	MapilFloat32 eyeX,
										MapilFloat32 eyeY,
										MapilFloat32 eyeZ,
										MapilFloat32 lookX,
										MapilFloat32 lookY,
										MapilFloat32 lookZ,
										MapilFloat32 upX,
										MapilFloat32 upY,
										MapilFloat32 upZ );
		/**
		*	@brief			Set view transformation matrix.
		*	@param vEye		The position of the camera.
		*	@param vLook	A point of view.
		*	@param vUp		Tilt of the camera.
		*/
		MapilVoid SetViewTransMat(	const Vector3 < MapilFloat32 >& vEye,
										const Vector3 < MapilFloat32 >& vLook,
										const Vector3 < MapilFloat32 >& vUp );
		/**
		*	@brief			Set projection transformation matrix.
		*	@param fovy		Fovy.
		*	@param aspect	Aspect ratio.
		*	@param nearClip	The nearest Z-Coordinate to be displayed.
		*	@param farClip	The farthest Z-Coordinate to be displayed.
		*/
		MapilVoid SetProjectionTransMat(	MapilFloat32 fovy,
												MapilFloat32 aspect,
												MapilFloat32 nearClip,
												MapilFloat32 farClip );
		/**
		*	@brief			Set projection transformation matrix. ( Orthogonal projection. )
		*	@param left		Left edge to be displayed.
		*	@param right	Right edge to be displayed.
		*	@param bottom	Bottom edge to be displayed.
		*	@param top		Top edge to be displayed.
		*	@param nearClip	The nearest Z-Coordinate to be displayed.
		*	@param farClip	The farthest Z-Coordinate to be displayed.
		*/
		MapilVoid SetProjectionTransMat(	MapilFloat32 left,
												MapilFloat32 right,
												MapilFloat32 bottom,
												MapilFloat32 top,
												MapilFloat32 nearClip,
												MapilFloat32 farClip );
		Matrix4x4 < MapilFloat32 > GetInvViewTransMat() const;
		Matrix4x4 < MapilFloat32 > GetInvProjTransMat() const;
		/**
		*	@brief	Enable camera
		*/
		MapilVoid Enable();
	};
}

#endif	// API_OPENGL

#endif	// INCLUDED_MAPIL_GLCAMERA_H
