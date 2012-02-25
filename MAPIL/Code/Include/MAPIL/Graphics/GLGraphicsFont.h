/**
*	@file	GLGraphicsFont.h
*	@brief	GLGraphicsFont class is derived class from GLGraphicsFont class.
*			GLGraphicsFont is implemented for OpenGL. The users shouldn't
*			call method from this class directly.
*	@date	2011.7.31 (Sun) 10:03
*/

#ifndef INCLUDED_MAPIL_GLGRAPHICSFONT_H
#define INCLUDED_MAPIL_GLGRAPHICSFONT_H

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
#endif
#if defined ( OS_LINUX_32BIT )
#include <GL/gl.h>
#endif

#include "GraphicsFont.h"
#include "../Type.h"
#include "../TChar.h"
#include "../Util/FontFormat.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
#if defined ( API_WIN32API )
	class GraphicsDevice;
	class GLGraphicsFont : public GraphicsFont
	{
	private:
		HFONT			m_HFont;			///< Handler.
		HDC				m_HDC;				///< Device context.
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		GLGraphicsFont( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLGraphicsFont();
		/**
		*	@brief		Instantiate the GLGraphicsFont class.
		*	@param fmt	The FontFormat structure.
		*/
		MapilVoid Create( const FontFormat& fmt );
		MapilVoid Draw( MapilTChar* pStr );
		MapilVoid Draw(	MapilInt32 posX, MapilInt32 posY,
						MapilFloat32 colR, MapilFloat32 colG, MapilFloat32 colB,
						MapilTChar* pStr, ... );
		/**
		*	@brief	Get the font handler.
		*	@return	The font handler.
		*/
		MapilInt32 Get();
	};
#else
	class GraphicsDevice;
	class GLGraphicsFont : public GraphicsFont
	{
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		GLGraphicsFont( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLGraphicsFont();
		/**
		*	@brief		Instantiate the GLGraphicsFont class.
		*	@param fmt	The FontFormat structure.
		*/
		MapilVoid Create( const FontFormat& fmt );
		MapilVoid Draw( MapilTChar* pStr );
		MapilVoid Draw(	MapilInt32 posX, MapilInt32 posY,
						MapilFloat32 colR, MapilFloat32 colG, MapilFloat32 colB,
						MapilTChar* pStr, ... );
	};
#endif
}

#endif	// API_OPENGL

#endif	// INCLUDED_MAPIL_GLGRAPHICSFONT_H
