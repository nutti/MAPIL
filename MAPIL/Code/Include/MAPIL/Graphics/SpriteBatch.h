/**
*	@file	SpriteBatch.h
*	@brief	
*	@date	2011.9.21 (Wed) 11:01
*/

#ifndef INCLUDED_MAPIL_SPRITEBATCH_H
#define INCLUDED_MAPIL_SPRITEBATCH_H

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Util/SharedPointer.hpp"
#include "Sprite.h"

#include <queue>

namespace MAPIL
{
	class SpriteBatch : public MapilObject
	{
		struct TexNode
		{
			SharedPointer < Texture >		m_pTex;
			Matrix4x4 < MapilFloat32 >		m_Mat;
		};
		struct FontNode
		{
			SharedPointer < GraphicsFont >	m_pFont;
			const MapilTChar*				m_pStr;
			Matrix4x4 < MapilFloat32 >		m_Mat;
		};
		std::queue < TexNode >				m_TexList;
		std::queue < FontNode >				m_FontList;
		SharedPointer < Sprite >			m_Sprite;
	public:
		SpriteBatch();
		~SpriteBatch();
		MapilVoid Create( SharedPointer < Sprite > sprite );
		MapilVoid Flush();
		// Draw texture.
		MapilVoid Add(	SharedPointer < Texture > pTexture,
						ImageTransformationMethod method,
						const Vector2 < MapilFloat32 >& v );
		MapilVoid Add(	SharedPointer < Texture > pTexture,
						const Matrix4x4 < MapilFloat32 >& mat );
		MapilVoid Add(	SharedPointer < GraphicsFont > pFont,
						const MapilTChar* pStr,
						const Vector2 < MapilFloat32 >& vPos );
		MapilVoid Add(	SharedPointer < GraphicsFont > pFont,
						const MapilTChar* pStr,
						const Matrix4x4 < MapilFloat32 >& mat );
	};
}

#endif
