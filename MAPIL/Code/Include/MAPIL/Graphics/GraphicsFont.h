/**
*	@file	GraphicsFont.h
*	@brief	GraphicsFont class provides an easy way to create the font to be used
*			in the graphics modules. The users must call the Create method to
*			instantiate the GraphicsFont object at first. After instantiation,
*			the users can use this class as the argument of the other classes.
*	@date	2011.7.31 (Sun) 11:56
*/

#ifndef INCLUDED_MAPIL_GRAPHICSFONT_H
#define INCLUDED_MAPIL_GRAPHICSFONT_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Type.h"
#include "../Util/FontFormat.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class GraphicsFont : public Graphics
	{
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		GraphicsFont( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~GraphicsFont();
		/**
		*	@brief		Instantiate the GraphicsFont class.
		*	@param fmt	The FontFormat structure.
		*/
		virtual MapilVoid Create( const FontFormat& fmt ) = 0;
		virtual MapilVoid Draw( MapilTChar* pStr ) = 0;
		virtual MapilVoid Draw(	MapilInt32 posX, MapilInt32 posY,
								MapilFloat32 colR, MapilFloat32 colG, MapilFloat32 colB,
								MapilTChar* pStr, ... ) = 0;
		/**
		*	@brief	Get the font handler.
		*	@return	The font handler.
		*/
		virtual MapilInt32 Get() = 0;
	};
}

#endif	// INCLUDED_MAPIL_GRAPHICSFONT_H