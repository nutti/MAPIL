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
#include <vector>
#include <map>
#include <list>

#include "Sprite.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{

	class SpriteCore
	{
	private:
		struct SpriteData
		{
			::D3DXMATRIX	m_TransMat;
			FLOAT			m_UVLeft;
			FLOAT			m_UVTop;
			FLOAT			m_UVWidth;
			FLOAT			m_UVHeight;
			FLOAT			m_Alpha;
		};
		struct SpriteBatch
		{
			std::vector < SpriteData >		m_SpriteData;
			MapilInt32						m_SpriteTotal;
		};
		typedef std::map < ::LPDIRECT3DTEXTURE9, std::vector < SpriteData > >	DrawSpriteList;

		SharedPointer < GraphicsDevice >		m_Dev;
		DrawSpriteList							m_DrawList;
		::LPDIRECT3DVERTEXDECLARATION9			m_pVertexDecl;
		::IDirect3DVertexBuffer9*				m_pVertexBuf;
		::ID3DXEffect*							m_pEffect;
		MapilUInt32								m_WndWidth;
		MapilUInt32								m_WndHeight;
	public:
		SpriteCore( SharedPointer < GraphicsDevice > dev );
		~SpriteCore();
		MapilVoid Begin();
		MapilVoid End();
		MapilVoid Commit( SharedPointer < Texture > texture, const ::D3DXMATRIX& worldMat );
		MapilVoid Flush();
	};


	class GraphicsDevice;
	//class SpriteCore;
	class D3DSprite : public Sprite
	{
	private:
		::LPD3DXSPRITE							m_pD3DSprite;		///< Handler.
		MapilBool								m_IsUsed;			///< The flag shows that the object is already used.
		SharedPointer < GraphicsController >	m_pGraphicsCtrl;
		MapilInt32								m_PrevAlphaBlendMode;
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
		MapilVoid Create( SharedPointer < GraphicsController > pCtrl );
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
		MapilVoid SetAlphaBlendMode( MapilInt32 mode );
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
