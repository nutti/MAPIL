/**
*	@file	GLSprite.h
*	@brief	GLSprite class is derived from Sprite class. GLSprite is implemented
*			for OpenGL. The users shouldn't call method from this class directly.
*	@date	2011.9.5 (Mon) 11:47
*/

#ifndef INCLUDED_MAPIL_GLSPRITE_H
#define INCLUDED_MAPIL_GLSPRITE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_OPENGL )

#include "Sprite.h"

#if defined ( API_WIN32API )
#include <Windows.h>
#endif
#if defined ( OS_WIN_32BIT )
#include <gl/GL.h>
#include <gl/GLU.h>
#elif defined ( OS_LINUX_32BIT ) || defined ( OS_MAC_64BIT )
#include <GL/gl.h>
#include <GL/glu.h>
#endif

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class GLSprite : public Sprite
	{
	private:
		GLfloat							m_ViewMat[ 16 ];				///< View transformation matrix.
		GLfloat							m_ProjMat[ 16 ];				///< Projection transformation matrix.
		SharedPointer < Texture >		m_pPrevTexture;					///< Previous texture.
		/**
		*	@brief			Draw texture.
		*	@param pTexture	SharedPointer to the Texture object to be drawn.
		*/
		MapilVoid DrawTexture(	SharedPointer < Texture > pTexture );
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		GLSprite( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLSprite();
		/**
		*	@brief		Instantiate the GLSprite object.
		*/
		MapilVoid Create();
		/**
		*	@brief Begin to draw.
		*/
		MapilVoid Begin();
		/**
		*	@brief End to draw.
		*/
		MapilVoid End();
		/**
		*	@brief			Draw texture.
		*	@param pTexture	SharedPointer to the Texture object to be drawn.
		*	@param method	A method of transformation.
		*	@param v		2-dimension vector.
		*/
		MapilVoid DrawTexture(	SharedPointer < Texture > pTexture,
								ImageTransformationMethod method,
								const Vector2 < MapilFloat32 >& v );
		/**
		*	@brief			Draw texture.
		*	@param pTexture	SharedPointer to the Texture object to be drawn.
		*	@param mat		Transformation matrix.
		*/
		MapilVoid DrawTexture(	SharedPointer < Texture > pTexture,
								const Matrix4x4 < MapilFloat32 >& mat );
		/**
		*	@brief			Draw texture.
		*	@param pTexture	SharedPointer to the Texture object to be drawn.
		*	@param mat		Transformation matrix.
		*	@param color	Texture color.
		*/
		MapilVoid DrawTexture(	SharedPointer < Texture > pTexture,
								const Matrix4x4 < MapilFloat32 >& mat,
								MapilUInt32 color );
		MapilVoid DrawTexture(	SharedPointer < Texture > pTexture,
								MapilFloat32 x, MapilFloat32 y,
								MapilBool centerize = MapilTrue, MapilUInt32 color = 0xFFFFFFFF );
		MapilVoid DrawScaledTexture(	SharedPointer < Texture > pTexture,
										MapilFloat32 x, MapilFloat32 y, MapilFloat32 sx, MapilFloat32 sy,
										MapilBool centerize = MapilTrue, MapilUInt32 color = 0xFFFFFFFF );
		MapilVoid DrawRotateTexture(	SharedPointer < Texture > pTexture,
										MapilFloat32 x, MapilFloat32 y, MapilFloat32 angle,
										MapilBool centerize = MapilTrue, MapilUInt32 color = 0xFFFFFFFF );
		/**
		*	@brief			Draw string.
		*	@param pFont	SharedPointer to the GraphicsFont object to be drawn.
		*	@param pStr		A string to be drawn.
		*	@param vPos		2-dimension vector.
		*/
		MapilVoid DrawString(	SharedPointer < GraphicsFont > pFont,
								const MapilTChar* pStr,
								ImageTransformationMethod method,
								const Vector2 < MapilFloat32 >& v,
								MapilUInt32 color );
		/**
		*	@brief			Draw string.
		*	@param pFont	SharedPointer to the GraphicsFont object to be drawn.
		*	@param pStr		A string to be drawn.
		*	@param mat		Transformation matrix.
		*/
		MapilVoid DrawString(	SharedPointer < GraphicsFont > pFont,
								const MapilTChar* pStr,
								const Matrix4x4 < MapilFloat32 >& mat );

		MapilVoid LostResource();
		MapilVoid RestoreResource();
	};
}

#endif	// API_OPENGL

#endif	// INCLUDED_MAPIL_GLSPRITE_H
