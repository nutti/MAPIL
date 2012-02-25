/**
*	@file	GraphicsController.h
*	@brief	GraphicsController class is used for configuring the graphics devices.
*			For example, the users can change alpha blend mode. If the users begin
*			rendering, BeginRendering method must be called. When the users finish
*			rendering, call EndRendering method.
*	@date	2011.6.21 (Tue) 16:50
*/

#ifndef INCLUDED_MAPIL_GRAPHICSCONTROLLER_H
#define INCLUDED_MAPIL_GRAPHICSCONTROLLER_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "ConstNums.h"
#include "../Util/Color.hpp"
#include "../Type.h"
#include "../Util/SharedPointer.hpp"
#include "../GUI/GraphicsContext.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class GraphicsFactory;
	class GraphicsController : public Graphics
	{
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		GraphicsController( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~GraphicsController();
		/**
		*	@brief		Instantiate the GraphicsController class.
		*	@param pGC	SharedPointer to the GraphicsContext object.
		*/
		virtual MapilVoid Create( SharedPointer < GraphicsContext > pGC ) = 0;
		/**
		*	@brief		Begin rendering.
		*/
		virtual MapilVoid BeginRendering() = 0;
		/**
		*	@brief		End rendering.
		*/
		virtual MapilVoid EndRendering() = 0;
		/**
		*	@brief			Set viewport.
		*	@param x		X-coordinate for the left-top point of the rectangle.
		*	@param y		Y-coordinate for the left-top point of the rectangle.
		*	@param width	Width of the rectangle.
		*	@param height	Height of the rectangle.
		*/
		virtual MapilVoid SetViewport(	MapilInt32 x,
											MapilInt32 y,
											MapilInt32 width,
											MapilInt32 height ) = 0;
		/**
		*	@brief			Enable z-buffering.
		*	@param status	Enable z-buffering if status is true.
		*/
		virtual MapilVoid EnableZBuffer( MapilBool status ) = 0;
		/**
		*	@brief			Enable lighting.
		*	@param status	Enable lighting if status is true.
		*/
		virtual MapilVoid EnableLight( MapilBool status ) = 0;
		/**
		*	@brief			Enable blending.
		*	@param status	Enable blending if status is true.
		*/
		virtual MapilVoid EnableBlend( MapilBool status ) = 0;
		/**
		*	@brief			Enable fog.
		*	@param status	Enable fog if status is true.
		*/
		virtual MapilVoid EnableFog( MapilBool status ) = 0;
		/**
		*	@brief			Set alpha blend mode.
		*	@param mode		Alpha blend mode to be set.
		*/
		virtual MapilVoid SetAlphaBlendMode( AlphaBlendMode mode ) = 0;
		/**
		*	@brief			Set culling mode.
		*	@param mode		Culling mode to be set.
		*/
		virtual MapilVoid SetCullMode( CullMode mode ) = 0;
		/**
		*	@brief			Set texture mode.
		*	@param mode		Texture mode to be set.
		*/
		virtual MapilVoid SetTextureMode( TextureMode mode ) = 0;
		/**
		*	@brief			Set fog parameter.
		*	@param col		Color of the fog.
		*	@param mode		Fog mode.
		*	@param begin	Start edge of the fog.
		*	@param end		End edge of the fog.
		*/
		virtual MapilVoid SetFogParam(	const ColorARGB < MapilFloat32 >& color,
										MapilInt32 mode,
										MapilFloat32 begin,
										MapilFloat32 end,
										MapilFloat32 density ) = 0;
		/**
		*	@brief			Set fog parameter.
		*	@param col		Color of the fog.
		*	@param mode		Fog mode.
		*	@param begin	Start edge of the fog.
		*	@param end		End edge of the fog.
		*/
		virtual MapilVoid SetFogParam(	const ColorARGB < MapilUChar >& color,
										MapilInt32 mode,
										MapilFloat32 begin,
										MapilFloat32 end,
										MapilFloat32 density ) = 0;
		/**
		*	@brief			Set fog parameter.
		*	@param col		Color of the fog.
		*	@param mode		Fog mode.
		*	@param begin	Start edge of the fog.
		*	@param end		End edge of the fog.
		*/
		virtual MapilVoid SetFogParam(	MapilUInt32 color,
										MapilInt32 mode,
										MapilFloat32 begin,
										MapilFloat32 end,
										MapilFloat32 density ) = 0;
		/**
		*	@brief			Enable VSYNC.
		*	@param status	Enable VSYNC if status is true.
		*/
		virtual MapilVoid EnableVSync( MapilBool status ) = 0;
		/**
		*	@brief				Capture the screen.
		*	@param pFileName	The file name.
		*/
		virtual MapilVoid CaptureScreen( const MapilTChar* pFileName ) = 0;
		/**
		*	@brief		Set the window mode.
		*	@param mode	The window mode.
		*/
		virtual MapilVoid SetWndMode( MapilInt32 mode ) = 0;
		/**
		*	@brief				Set the graphics factory.
		*	@param pFactory		Graphics factory.
		*/
		virtual MapilVoid SetGraphicsFactory( GraphicsFactory* pFactory ) = 0;
	};
}

#endif	// INCLUDED_MAPIL_GRAPHICSCONTROLLER_H
