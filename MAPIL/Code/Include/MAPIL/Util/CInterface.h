/**
*	@file	CInterface.h
*	@brief	
*	@date	2012.6.30 (Sat) 9:41
*/

#ifndef INCLUDED_MAPIL_CINTERFACE_H
#define INCLUDED_MAPIL_CINTERFACE_H

#include "../CrossPlatform.h"

#include "../Type.h"
#include "../Math/Matrix.hpp"
#include "../Graphics/Rectangle3D.h"

namespace MAPIL
{
	struct FontFormat;

	// Initialize MAPIL.
	MapilInt32 InitMAPIL( const MapilChar* pWndName, MapilInt32 width, MapilInt32 height );
	// Set GUI API.
	MapilVoid SetGUIAPI( MapilInt32 api );
	// Set Graphics API.
	MapilVoid SetGraphicsAPI( MapilInt32 api );
	// Set Input API.
	MapilVoid SetInputAPI( MapilInt32 api );
	// Set Sound API.
	MapilVoid SetSoundAPI( MapilInt32 api );
	// Set Icon.
	MapilVoid SetIcon( const MapilChar* pFileName );
	// Craete camera.
	MapilInt32 CreateCamera();
	// Create graphics font.
	MapilInt32 CreateGraphicsFont( const FontFormat& fmt );
	// Create texture.
	MapilInt32 CreateTexture( const MapilChar* pFileName );
	// Create texture from archive file.
	MapilInt32 CreateTexture( MapilUInt32 archiveHandle, const MapilChar* pFilePath );
	// Create texture. ( With split. )
	MapilVoid CreateSplitedTexture(	MapilInt32* pIndex,
									const MapilChar* pFileName,
									MapilInt32 column,
									MapilInt32 row,
									MapilInt32 width,
									MapilInt32 height );
	// Create texture from archive file.
	MapilVoid CreateSplitedTexture(	MapilInt32* pIndex,
									MapilUInt32 archiveHandle,
									const MapilChar* pFilePath,
									MapilInt32 column,
									MapilInt32 row,
									MapilInt32 width,
									MapilInt32 height );
	// Create point sprite.
	MapilInt32 CreatePointSprite( MapilInt32 num, MapilInt32 texture );
	// Create static buffer.
	MapilInt32 CreateStaticBuffer( const MapilChar* pFileName );
	// Create static buffer from archive file.
	MapilUInt32 CreateStaticBuffer( MapilUInt32 archiveHandle, const MapilChar* pFilePath );
	// Create streaming buffer.
	MapilInt32 CreateStreamingBuffer( const MapilChar* pFileName );
	// Create streaming buffer from archive file.
	MapilUInt32 CreateStreamingBuffer( MapilUInt32 archiveHandle, const MapilChar* pFilePath );
	// Delete camera.
	MapilVoid DeleteCamera( MapilUInt32 index );
	// Delete graphics font.
	MapilVoid DeleteGraphicsFont( MapilUInt32 index );
	// Delete texture.
	MapilVoid DeleteTexture( MapilUInt32 index );
	// Delete point sprite.
	MapilVoid DeletePointSprite( MapilUInt32 index );
	// Delete static buffer.
	MapilVoid DeleteStaticBuffer( MapilUInt32 index );
	// Delete streaming buffer.
	MapilVoid DeleteStreamingBuffer( MapilUInt32 index );
	// Get keyboard state.
	MapilVoid GetKeyboardState( MapilUChar* pOut );
	// Begin rendering.
	MapilVoid BeginRendering();
	// End rendering.
	MapilVoid EndRendering();
	// Begin rendering 2D Graphics.
	MapilVoid BeginRendering2DGraphics();
	// End rendering 2D Graphics.
	MapilVoid EndRendering2DGraphics();
	// Enable blending.
	MapilVoid EnableBlending();
	// Disable blending.
	MapilVoid DisableBlending();
	// Enable lighting.
	MapilVoid EnableLighting();
	// Disable lighting.
	MapilVoid DisableLighting();
	// Enable z-buffering.
	MapilVoid EnableZBuffering();
	// Disable z-buffering.
	MapilVoid DisableZBuffering();
	// Enable fog.
	MapilVoid EnableFog();
	// Disable fog.
	MapilVoid DisableFog();
	// Set fog parameter.
	MapilVoid SetFogParam( MapilUInt32 color, MapilInt32 mode, MapilFloat32 begin, MapilFloat32 end, MapilFloat32 density );
	// Set texture mode.
	MapilVoid SetTextureMode( MapilInt32 mode );
	// Set cull mode.
	MapilVoid SetCullingMode( MapilInt32 mode );
	// Set alphablend mode.
	MapilVoid SetAlphaBlendingMode( MapilInt32 mode );
	// Set view port.
	MapilVoid SetViewPort( MapilInt32 x, MapilInt32 y, MapilInt32 width, MapilInt32 height );
	// Draw string ( with global sprite and global font ).
	MapilVoid DrawString( MapilFloat32 x, MapilFloat32 y, const MapilChar* pStr, ... );
	// Draw color string ( with gloval sprite and global font ).
	MapilVoid DrawString( MapilFloat32 x, MapilFloat32 y, MapilUInt32 color, const MapilChar* pStr, ... );
	// Draw texture ( with global sprite ).
	MapilVoid DrawTexture( MapilUInt32 index, MapilFloat32 x, MapilFloat32 y, MapilFloat32 angle );
	// Draw texture ( with global sprite ).
	MapilVoid DrawTexture( MapilUInt32 index, MapilFloat32 x, MapilFloat32 y, MapilFloat32 angle, MapilUInt32 color );
	// Draw texture ( with global sprite ).
	MapilVoid DrawTexture(	MapilUInt32 index,
							MapilFloat32 posX, MapilFloat32 posY,
							MapilFloat32 scaleX, MapilFloat32 scaleY,
							MapilFloat32 angle );
	// Draw texture ( with global sprite ).
	MapilVoid DrawTexture(	MapilUInt32 index,
							MapilFloat32 posX, MapilFloat32 posY,
							MapilFloat32 scaleX, MapilFloat32 scaleY,
							MapilFloat32 angle, MapilUInt32 color );
	// Draw texture without centering. ( with global sprite ).
	MapilVoid DrawTextureNonCentering(	MapilUInt32 index,
										MapilFloat32 posX, MapilFloat32 posY,
										MapilFloat32 scaleX, MapilFloat32 scaleY,
										MapilFloat32 angle );
	// Draw polygon 3D. (without resource holding.)
	MapilVoid DrawPolygon3D( const Polygon3DVertexFormat* pFmt, MapilInt32 polygonTotal );
	// Draw polygon 3D. (without resource holding.)
	MapilVoid DrawPolygon3D( const Polygon3DVertexFormat* pFmt, MapilInt32 polygonTotal, MapilUInt32 textureID );

	// Set master volume.
	MapilVoid SetMasterVolume( MapilUInt32 volume );
	// Set static buffer volume.
	MapilVoid SetStaticBufferVolume( MapilUInt32 index, MapilUInt32 volume );
	// Set streaming buffer volume.
	MapilVoid SetStreamingBufferVolume( MapilUInt32 index, MapilUInt32 volume );
	// Play static buffer.
	MapilVoid PlayStaticBuffer( MapilUInt32 index );
	// Play streaming buffer.
	MapilVoid PlayStreamingBuffer( MapilUInt32 index );
	// Stop static buffer.
	MapilVoid StopStaticBuffer( MapilUInt32 index );
	// Stop streaming buffer.
	MapilVoid StopStreamingBuffer( MapilUInt32 index );
	// Pause static buffer.
	MapilVoid PauseStaticBuffer( MapilUInt32 index );
	// Pause streaming buffer.
	MapilVoid PauseStreamingBuffer( MapilUInt32 index );
	// Is static buffer pausing?
	MapilBool IsStaticBufferPausing( MapilUInt32 index );
	// Is static buffer stopping?
	MapilBool IsStaticBufferStopping( MapilUInt32 index );
	// Is streaming buffer pausing?
	MapilBool IsStreamingBufferPausing( MapilUInt32 index );
	// Is streaming buffer stopping?
	MapilBool IsStreamingBufferStopping( MapilUInt32 index );

	// Reflesh resources.
	MapilVoid RefleshResources();
	// Enable camera.
	MapilVoid EnableCamera( MapilUInt32 index );
	// Set projection translation. ( Camera )
	MapilVoid SetCameraProjTrans( MapilUInt32 index, MapilFloat32 fovy, MapilFloat32 aspect, MapilFloat32 nearClip, MapilFloat32 farClip );
	// Set view translation. ( Camera )
	MapilVoid SetCameraViewTrans(	MapilUInt32 index,
									MapilFloat32 eyeX, MapilFloat32 eyeY, MapilFloat32 eyeZ,
									MapilFloat32 lookX, MapilFloat32 lookY, MapilFloat32 lookZ,
									MapilFloat32 upX, MapilFloat32 upY, MapilFloat32 upZ );
	// Enable camera.
	MapilVoid EnableCamera();
	// Set projection translation. ( Camera )
	MapilVoid SetCameraProjTrans( MapilFloat32 fovy, MapilFloat32 aspect, MapilFloat32 nearClip, MapilFloat32 farClip );
	// Set view translation. ( Camera )
	MapilVoid SetCameraViewTrans(	MapilFloat32 eyeX, MapilFloat32 eyeY, MapilFloat32 eyeZ,
									MapilFloat32 lookX, MapilFloat32 lookY, MapilFloat32 lookZ,
									MapilFloat32 upX, MapilFloat32 upY, MapilFloat32 upZ );
	// Process message.
	MapilInt32 ProcessMessage();
	// Draw point sprite.
	MapilVoid DrawPointSprite( MapilUInt32 index );
	// Capture screen shot.
	MapilVoid CaptureScreen( const MapilChar* pFileName );

	// Update point sprite.
	MapilVoid UpdatePointSprite( MapilUInt32 id, MapilUInt32 index, const Vector3 < MapilFloat32 >& vPos, MapilFloat32 size, MapilInt32 color );

	// Create local model.
	MapilUInt32 CreateModel( const MapilChar* pFileName );
	// Draw model.
	MapilVoid DrawModel( MapilUInt32 id, const Matrix4x4 < MapilFloat32 >& mat );
	// Create local rectangle 3D.
	MapilUInt32 CreateRectangle3D();
	// Update rectangle 3D.
	MapilVoid UpdateRectangle3D( MapilUInt32 id, const Rectangle3DVertexFormat& fmt, MapilUInt32 texID );
	// Draw rectangle 3D.
	MapilVoid DrawRectangle3D( MapilUInt32 id );

	// Draw texture with batch drawing. (with global sprite)
	MapilVoid PostTextureBatchWork(	MapilUInt32 id,
									MapilFloat32 posX, MapilFloat32 posY,
									MapilFloat32 scaleX, MapilFloat32 scaleY,
									MapilFloat32 angle, MapilUInt32 color );
	// Perform all batch works. (with global sprite)
	MapilVoid DoAllBatchWorks();

	// Open archive file.
	MapilUInt32 OpenArchiveFile( const MapilChar* pFileName, MapilInt32 mode );
	// Get contents size on archive file.
	MapilUInt32 GetContentsSizeOnArchiveFile( MapilUInt32 archiveHandle, const MapilChar* pFilePath );
	// Load data from archive file.
	MapilVoid LoadDataFromArchiveFile( MapilUInt32 archiveHandle, const MapilChar* pFilePath, MapilChar* pData );
	
}

#endif