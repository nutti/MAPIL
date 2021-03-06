/**
*	@file	D3DCamera.h
*	@brief	This class is derived from Camera class. D3DCamera is implemented
*			for Direct3D. The users shouldn't call a method from this class
*			directly.
*	@date	2011.8.24 (Wed) 21:22
*/

#ifndef INCLUDED_MAPIL_D3DCAMERA_H
#define INCLUDED_MAPIL_D3DCAMERA_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "Camera.h"
#include "../Type.h"
#include "../Math/Vector.hpp"

#include <d3dx9.h>

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class D3DCamera : public Camera
	{
		::D3DXMATRIXA16						m_ViewMat;		///< View transformation matrix.
		::D3DXMATRIXA16						m_ProjMat;		///< Projection transformation matrix.
		//MapilBool							m_IsUsed;		///< Flag which camera is being used now.
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		D3DCamera( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DCamera();
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

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DCAMERA_H
