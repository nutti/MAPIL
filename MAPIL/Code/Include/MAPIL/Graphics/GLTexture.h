/**
*	@file	GLTexture.h
*	@brief	GLTexture class is derived from Texture class. GLTexture is implemented
*			for OpenGL. The users shouldn't call method from this class directly.
*	@date	2011.7.17 (Sun) 12:12
*/

#ifndef INCLUDED_MAPIL_GLTEXTURE_H
#define INCLUDED_MAPIL_GLTEXTURE_H

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
#elif defined ( OS_LINUX_32BIT )
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "Texture.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class GLTexture : public Texture
	{
	private:
		friend class GLCanvas2D;
		GLuint					m_TexName;			///< Original texture handle.
		GLubyte*				m_pData;			///< Original texture data.
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		GLTexture( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLTexture();
		/**
		*	@brief				Instantiate the GLTexture object.
		*	@param pFileName	File name to be loaded.
		*/
		MapilVoid Create( const MapilTChar* pFileName );
		/**
		*	@brief				Instantiate the GLTexture object.
		*	@param pArchiver	Archiver.
		*	@param pFileName	File name to be loaded.
		*/
		MapilVoid Create( Archiver* pArchiver, const MapilTChar* pFileName );
		/**
		*	@brief	Get the texture instance which is active.
		*	@return	The texture instance.
		*/
		MapilInt32 Get();
		/**
		*	@brief	Get the orignal texture size.
		*	@return	The size of the texture.
		*/
		Vector2 < MapilInt32 > GetSize();
	};
}

#endif	// API_OPENGL

#endif	// INCLUDED_MAPIL_GLTEXTURE_H