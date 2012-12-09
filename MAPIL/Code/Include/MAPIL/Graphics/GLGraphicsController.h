/**
*	@file	GLGraphicsController.h
*	@brief	GLGraphicsController class is derived from GraphicsController
*			class. GLGraphicsController is implemented for OpenGL. The
*			users shouldn't call method from this class directly.
*	@date	2011.6.21 (Tue) 17:08
*/

#ifndef INCLUDED_MAPIL_GLGRAPHICSCONTROLLER_H
#define INCLUDED_MAPIL_GLGRAPHICSCONTROLLER_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_OPENGL )

#include "GraphicsController.h"
#include "ConstNums.h"
#include "../Util/Color.hpp"
#include "../Type.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class GLGraphicsController : public GraphicsController
	{
		SharedPointer < GraphicsContext >		m_pGC;		///< Graphics context.
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		GLGraphicsController( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~GLGraphicsController();
		/**
		*	@brief		Instantiate the GLGraphicsController class.
		*	@param pGC	SharedPointer to the GraphicsContext object.
		*/
		MapilVoid Create( SharedPointer < GraphicsContext > pGC );
		/**
		*	@brief		Begin rendering.
		*/
		MapilVoid BeginRendering();
		/**
		*	@brief		End rendering.
		*/
		MapilVoid EndRendering();
		/**
		*	@brief			Set viewport.
		*	@param x		X-coordinate for the left-top point of the rectangle.
		*	@param y		Y-coordinate for the left-top point of the rectangle.
		*	@param width	Width of the rectangle.
		*	@param height	Height of the rectangle.
		*/
		MapilVoid SetViewport(	MapilInt32 x,
									MapilInt32 y,
									MapilInt32 width,
									MapilInt32 height );
		/**
		*	@brief			Enable z-buffering.
		*	@param status	Enable z-buffering if status is true.
		*/
		MapilVoid EnableZBuffer( MapilBool status );
		/**
		*	@brief			Enable lighting.
		*	@param status	Enable lighting if status is true.
		*/
		MapilVoid EnableLight( MapilBool status );
		/**
		*	@brief			Enable blending.
		*	@param status	Enable blending if status is true.
		*/
		MapilVoid EnableBlend( MapilBool status );
		/**
		*	@brief			Enable fog.
		*	@param status	Enable fog if status is true.
		*/
		MapilVoid EnableFog( MapilBool status );
		/**
		*	@brief			Set alpha blend mode.
		*	@param mode		Alpha blend mode to be set.
		*/
		MapilVoid SetAlphaBlendMode( MapilInt32 mode );
		/**
		*	@brief			Set culling mode.
		*	@param mode		Culling mode to be set.
		*/
		MapilVoid SetCullMode( MapilInt32 mode );
		/**
		*	@brief			Set texture mode.
		*	@param mode		Texture mode to be set.
		*/
		MapilVoid SetTextureMode( MapilInt32 mode );
		/**
		*	@brief			Set fog parameter.
		*	@param col		Color of the fog.
		*	@param mode		Fog mode.
		*	@param begin	Start edge of the fog.
		*	@param end		End edge of the fog.
		*/
		MapilVoid SetFogParam(	const ColorARGB < MapilFloat32 >& color,
								MapilInt32 mode,
								MapilFloat32 begin,
								MapilFloat32 end,
								MapilFloat32 density );
		/**
		*	@brief			Set fog parameter.
		*	@param col		Color of the fog.
		*	@param mode		Fog mode.
		*	@param begin	Start edge of the fog.
		*	@param end		End edge of the fog.
		*/
		MapilVoid SetFogParam(	const ColorARGB < MapilUChar >& color,
								MapilInt32 mode,
								MapilFloat32 begin,
								MapilFloat32 end,
								MapilFloat32 density );
		/**
		*	@brief			Set fog parameter.
		*	@param col		Color of the fog.
		*	@param mode		Fog mode.
		*	@param begin	Start edge of the fog.
		*	@param end		End edge of the fog.
		*/
		MapilVoid SetFogParam(	MapilUInt32 color,
								MapilInt32 mode,
								MapilFloat32 begin,
								MapilFloat32 end,
								MapilFloat32 density );
		/**
		*	@brief			Enable VSYNC.
		*	@param status	Enable VSYNC if status is true.
		*/
		MapilVoid EnableVSync( MapilBool status );
		/**
		*	@brief				Capture the screen.
		*	@param pFileName	The file name.
		*/
		MapilVoid CaptureScreen( const MapilTChar* pFileName );
		/**
		*	@brief		Set the window mode.
		*	@param mode	The window mode.
		*/
		MapilVoid SetWndMode( MapilInt32 mode );
		/**
		*	@brief				Set the graphics factory.
		*	@param pFactory		Graphics factory.
		*/
		MapilVoid SetGraphicsFactory( GraphicsFactory* pFactory );

		MapilInt32 GetAlphaBlendMode() const;
	};
}

#endif	// API_OPENGL

#endif	// INCLUDED_MAPIL_GLGRAPHICSCONTROLLER_H
