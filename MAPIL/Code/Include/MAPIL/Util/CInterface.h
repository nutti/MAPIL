/**
*	@file	CInterface.h
*	@brief	
*	@date	2012.6.30 (Sat) 9:41
*/

#ifndef INCLUDED_MAPIL_CINTERFACE_H
#define INCLUDED_MAPIL_CINTERFACE_H

#include "../CrossPlatform.h"

#include "../Type.h"

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
	// Create point sprite.
	MapilInt32 CreatePointSprite( MapilInt32 num, MapilInt32 texture );
	// Create static buffer.
	MapilInt32 CreateStaticBuffer( const MapilChar* pFileName );
	// Create streaming buffer.
	MapilInt32 CreateStreamingBuffer( const MapilChar* pFileName );
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
	// Draw texture ( with global sprite ).
	MapilVoid DrawTexture( MapilInt32 index, MapilFloat32 x, MapilFloat32 y, MapilFloat32 angle );
	// Play static buffer.
	MapilVoid PlayStaticBuffer( MapilUInt32 index );
	// Play streaming buffer.
	MapilVoid PlayStreamingBuffer( MapilUInt32 index );
	// Stop static buffer.
	MapilVoid StopStaticBuffer( MapilUInt32 index );
	// Stop streaming buffer.
	MapilVoid StopStreamingBuffer( MapilUInt32 index );

	// Reflesh resources.
	MapilVoid RefleshResources();

	// Enable camera.
	MapilVoid EnableCamera( MapilUInt32 index );
	// Set projection translation. ( Camera )
	MapilVoid SetCameraProjTrans( MapilUInt32 index, MapilFloat32 fovy, MapilFloat32 aspect, MapilFloat32 nearClip, MapilFloat32 farClip );
	// Set view translation. ( Camera )
	MapilVoid EnableCamera(	MapilUInt32 index,
							MapilFloat32 eyeX, MapilFloat32 eyeY, MapilFloat32 eyeZ,
							MapilFloat32 lookX, MapilFloat32 lookY, MapilFloat32 lookZ,
							MapilFloat32 upX, MapilFloat32 upY, MapilFloat32 upZ );
	
	
}

#endif