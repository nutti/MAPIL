/**
*	@file	D3DSprite.h
*	@brief	D3DSprite class is derived from Sprite class. D3DSprite is implemented
*			for Direct3D. The users shouldn't call method from this class directly.
*	@date	2011.9.5 (Mon) 10:42
*/

#ifndef INCLUDED_MAPIL_D3DSPRITE_H
#define INCLUDED_MAPIL_D3DSPRITE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3dx9.h>

#include "Sprite.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class D3DSprite : public Sprite
	{
	private:
		::LPD3DXSPRITE			m_pD3DSprite;		///< Handler.
		MapilBool				m_IsUsed;			///< The flag shows that the object is already used.
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		D3DSprite( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DSprite();
		/**
		*	@brief		Instantiate the D3DSprite object.
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

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DSPRITE_H
