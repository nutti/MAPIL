/**
*	@file	SpriteBatch.cpp
*	@brief	
*	@date	2011.9.21 (Wed) 11:05
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/SpriteBatch.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	SpriteBatch::SpriteBatch() : MapilObject(), m_TexList(), m_FontList(), m_Sprite()
	{
	}

	SpriteBatch::~SpriteBatch()
	{
	}

	MapilVoid SpriteBatch::Create( SharedPointer < Sprite > sprite )
	{
		m_Sprite = sprite;
	}

	MapilVoid SpriteBatch::Flush()
	{
		m_Sprite->Begin();
		while( !m_TexList.empty() ){
			m_Sprite->DrawTexture( m_TexList.front().m_pTex, m_TexList.front().m_Mat );
			m_TexList.pop();
		}
		while( !m_FontList.empty() ){
			m_Sprite->DrawString( m_FontList.front().m_pFont, m_FontList.front().m_pStr, m_FontList.front().m_Mat );
			m_FontList.pop();
		}
		m_Sprite->End();
	}

	// Draw texture.
	MapilVoid SpriteBatch::Add(	SharedPointer < Texture > pTexture,
								ImageTransformationMethod method,
								const Vector2 < MapilFloat32 >& v )
	{
	}

	MapilVoid SpriteBatch::Add(	SharedPointer < Texture > pTexture,
								const Matrix4x4 < MapilFloat32 >& mat )
	{
		TexNode node;
		node.m_Mat = mat;
		node.m_pTex = pTexture;
		m_TexList.push( node );
	}

	MapilVoid SpriteBatch::Add(	SharedPointer < GraphicsFont > pFont,
								const MapilTChar* pStr,
								const Vector2 < MapilFloat32 >& vPos )
	{
	}

	MapilVoid SpriteBatch::Add(	SharedPointer < GraphicsFont > pFont,
								const MapilTChar* pStr,
								const Matrix4x4 < MapilFloat32 >& mat )
	{
		FontNode node;
		node.m_Mat = mat;
		node.m_pFont = pFont;
		node.m_pStr = pStr;
		m_FontList.push( node );
	}
}
