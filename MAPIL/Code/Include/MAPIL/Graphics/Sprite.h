/**
*	@file	Sprite.h
*	@brief	Sprite class provides the easy way to draw textures and strings for the user.
*			The user must call the Create method to instantiate the Sprite object at first.
*			After instantiation, the user can draw the materials between Begin method and
*			End method.
*	@date	2011.9.5 (Mon) 10:37
*/

#ifndef INCLUDED_MAPIL_SPRITE_H
#define INCLUDED_MAPIL_SPRITE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Util/SharedPointer.hpp"
#include "Texture.h"
#include "GraphicsFont.h"
#include "../Math/Matrix.hpp"
#include "../Type.h"
#include "ConstNums.h"

#include "GraphicsController.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class Sprite : public Graphics
	{
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		Sprite( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~Sprite();
		/**
		*	@brief Instantiate the Sprite object.
		*/
		virtual MapilVoid Create( SharedPointer < GraphicsController > pCtrl ) = 0;
		/**
		*	@brief Begin to draw.
		*/
		virtual MapilVoid Begin() = 0;
		/**
		*	@brief End to draw.
		*/
		virtual MapilVoid End() = 0;
		/**
		*	@brief			Draw texture.
		*	@param pTexture	SharedPointer to the Texture object to be drawn.
		*	@param method	A method of transformation.
		*	@param v		2-dimension vector.
		*/
		virtual MapilVoid DrawTexture(	SharedPointer < Texture > pTexture,
										ImageTransformationMethod method,
										const Vector2 < MapilFloat32 >& v ) = 0;
		/**
		*	@brief			Draw texture.
		*	@param pTexture	SharedPointer to the Texture object to be drawn.
		*	@param mat		Transformation matrix.
		*/
		virtual MapilVoid DrawTexture(	SharedPointer < Texture > pTexture,
										const Matrix4x4 < MapilFloat32 >& mat ) = 0;
		/**
		*	@brief			Draw texture.
		*	@param pTexture	SharedPointer to the Texture object to be drawn.
		*	@param mat		Transformation matrix.
		*	@param color	Texture color.
		*/
		virtual MapilVoid DrawTexture(	SharedPointer < Texture > pTexture,
										const Matrix4x4 < MapilFloat32 >& mat,
										MapilUInt32 color ) = 0;
		virtual MapilVoid DrawTexture(	SharedPointer < Texture > pTexture,
										MapilFloat32 x, MapilFloat32 y,
										MapilBool centerize = MapilTrue, MapilUInt32 color = 0xFFFFFFFF ) = 0;
		virtual MapilVoid DrawScaledTexture(	SharedPointer < Texture > pTexture,
												MapilFloat32 x, MapilFloat32 y, MapilFloat32 sx, MapilFloat32 sy,
												MapilBool centerize = MapilTrue, MapilUInt32 color = 0xFFFFFFFF ) = 0;
		virtual MapilVoid DrawRotateTexture(	SharedPointer < Texture > pTexture,
												MapilFloat32 x, MapilFloat32 y, MapilFloat32 angle,
												MapilBool centerize = MapilTrue, MapilUInt32 color = 0xFFFFFFFF ) = 0;
		virtual MapilVoid DrawClipedTexture(	SharedPointer < Texture > pTexture,
												MapilFloat32 x, MapilFloat32 y,
												MapilFloat32 texCoordX, MapilFloat32 texCoordY,
												MapilBool centerize = MapilTrue, MapilUInt32 color = 0xFFFFFFFF ) = 0;
		virtual MapilVoid DrawClipedTexture(	SharedPointer < Texture > pTexture,
												MapilFloat32 x, MapilFloat32 y,
												MapilFloat32 sx, MapilFloat32 sy,
												MapilFloat32 angle,
												MapilFloat32 cx1, MapilFloat32 cy1,
												MapilFloat32 cx2, MapilFloat32 cy2,
												MapilBool centerize = MapilTrue, MapilUInt32 color = 0xFFFFFFFF ) = 0;
		virtual MapilVoid SetAlphaBlendMode( MapilInt32 mode ) = 0;
		/**
		*	@brief			Draw string.
		*	@param pFont	SharedPointer to the GraphicsFont object to be drawn.
		*	@param pStr		A string to be drawn.
		*	@param vPos		2-dimension vector.
		*/
		virtual MapilVoid DrawString(	SharedPointer < GraphicsFont > pFont,
										const MapilTChar* pStr,
										ImageTransformationMethod method,
										const Vector2 < MapilFloat32 >& v,
										MapilUInt32 color ) = 0;
		/**
		*	@brief			Draw string.
		*	@param pFont	SharedPointer to the GraphicsFont object to be drawn.
		*	@param pStr		A string to be drawn.
		*	@param mat		Transformation matrix.
		*/
		virtual MapilVoid DrawString(	SharedPointer < GraphicsFont > pFont,
										const MapilTChar* pStr,
										const Matrix4x4 < MapilFloat32 >& mat ) = 0;

		virtual MapilVoid LostResource() = 0;
		virtual MapilVoid RestoreResource() = 0;
	};
}

#endif	// INCLUDED_MAPIL_SPRITE_H
