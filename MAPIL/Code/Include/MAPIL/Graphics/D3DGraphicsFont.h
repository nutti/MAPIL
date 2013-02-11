/**
*	@file	D3DGraphicsFont.h
*	@brief	D3DGraphicsFont class is derived class from D3DGraphicsFont class.
*			D3DGraphicsFont is implemented for Direct3D. The users shouldn't
*			call method from this class directly.
*	@date	2011.8.25 (Thu) 21:37
*/

#ifndef INCLUDED_MAPIL_D3DGRAPHICSFONT_H
#define INCLUDED_MAPIL_D3DGRAPHICSFONT_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3dx9.h>

#include "GraphicsFont.h"
#include "../Type.h"
#include "../TChar.h"
#include "../Util/FontFormat.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class D3DGraphicsFont : public GraphicsFont
	{
	private:
		::LPD3DXFONT			m_pD3DFont;				///< Handler.
		//MapilBool				m_IsUsed;				///< Already used.
		MapilVoid DrawString( MapilTChar* pStr );
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		D3DGraphicsFont( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DGraphicsFont();
		/**
		*	@brief		Instantiate the D3DGraphicsFont class.
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
		MapilVoid LostResource();
		MapilVoid RestoreResource();
	};
}

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DGRAPHICSFONT_H
