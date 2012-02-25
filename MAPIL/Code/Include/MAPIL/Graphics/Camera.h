/**
*	@file	Camera.h
*	@brief	Camera class provides the easy way to realize the 3D space
*			for the user. Two projection methods are available. This
*			class is a interface class. The users must call the method
*			which is implemented on the class derived from this class.
*	@date	2011.6.19 (Sun) 11:59
*/

#ifndef INCLUDED_MAPIL_CAMERA_H
#define INCLUDED_MAPIL_CAMERA_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Type.h"
#include "../Math/Vector.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class Camera : public Graphics
	{
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		Camera( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~Camera();
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
		virtual MapilVoid Create(	const Vector3 < MapilFloat32 >& vEye,
									const Vector3 < MapilFloat32 >& vLook,
									const Vector3 < MapilFloat32 >& vUp,
									MapilFloat32 fovy,
									MapilFloat32 aspect,
									MapilFloat32 nearClip,
									MapilFloat32 farClip ) = 0;
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
		virtual MapilVoid Create(	MapilFloat32 eyeX,
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
									MapilFloat32 farClip ) = 0;
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
		virtual MapilVoid Create(	const Vector3 < MapilFloat32 >& vEye,
									const Vector3 < MapilFloat32 >& vLook,
									const Vector3 < MapilFloat32 >& vUp,
									MapilFloat32 left,
									MapilFloat32 right,
									MapilFloat32 bottom,
									MapilFloat32 top,
									MapilFloat32 nearClip,
									MapilFloat32 farClip ) = 0;
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
		virtual MapilVoid Create(	MapilFloat32 eyeX,
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
									MapilFloat32 farClip ) = 0;
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
		virtual MapilVoid SetViewTransMat(	MapilFloat32 eyeX,
												MapilFloat32 eyeY,
												MapilFloat32 eyeZ,
												MapilFloat32 lookX,
												MapilFloat32 lookY,
												MapilFloat32 lookZ,
												MapilFloat32 upX,
												MapilFloat32 upY,
												MapilFloat32 upZ ) = 0;
		/**
		*	@brief			Set view transformation matrix.
		*	@param vEye		The position of the camera.
		*	@param vLook	A point of view.
		*	@param vUp		Tilt of the camera.
		*/
		virtual MapilVoid SetViewTransMat(	const Vector3 < MapilFloat32 >& vEye,
											const Vector3 < MapilFloat32 >& vLook,
											const Vector3 < MapilFloat32 >& vUp ) = 0;
		/**
		*	@brief			Set projection transformation matrix.
		*	@param fovy		Fovy.
		*	@param aspect	Aspect ratio.
		*	@param nearClip	The nearest Z-Coordinate to be displayed.
		*	@param farClip	The farthest Z-Coordinate to be displayed.
		*/
		virtual MapilVoid SetProjectionTransMat(	MapilFloat32 fovy,
													MapilFloat32 aspect,
													MapilFloat32 nearClip,
													MapilFloat32 farClip ) = 0;
		/**
		*	@brief			Set projection transformation matrix. ( Orthogonal projection. )
		*	@param left		Left edge to be displayed.
		*	@param right	Right edge to be displayed.
		*	@param bottom	Bottom edge to be displayed.
		*	@param top		Top edge to be displayed.
		*	@param nearClip	The nearest Z-Coordinate to be displayed.
		*	@param farClip	The farthest Z-Coordinate to be displayed.
		*/
		virtual MapilVoid SetProjectionTransMat(	MapilFloat32 left,
													MapilFloat32 right,
													MapilFloat32 bottom,
													MapilFloat32 top,
													MapilFloat32 nearClip,
													MapilFloat32 farClip ) = 0;
		/**
		*	@brief	Enable camera
		*/
		virtual MapilVoid Enable() = 0;
	};
}

#endif	// INCLUDED_MAPIL_CAMERA_H
