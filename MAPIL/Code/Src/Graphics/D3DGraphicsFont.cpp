/**
*	@file	D3DGraphicsFont.cpp
*	@brief	Implementation of D3DGraphicsFont.
*	@date	2011.8.25 (Thu) 21:40
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "../../Include/MAPIL/Graphics/D3DGraphicsFont.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DGraphicsFont::D3DGraphicsFont( SharedPointer < GraphicsDevice > pDev ) :	GraphicsFont( pDev ),
																				m_pD3DFont( NULL ),
																				m_IsUsed( MapilFalse )
	{
	}

	D3DGraphicsFont::~D3DGraphicsFont()
	{
		SafeRelease( m_pD3DFont );
		m_IsUsed = MapilFalse;
	}

	MapilVoid D3DGraphicsFont::Create( const FontFormat& fmt )
	{
		Assert(	!m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DGraphicsFont" ),
				TSTR( "Create" ),
				TSTR( "The font was already created." ),
				-1 );

		//Create font
		if( FAILED( D3DXCreateFont(	m_pDev->GetDev().GetPointer(),
									fmt.m_Height,					//Height
									fmt.m_Width,					//Width
									fmt.m_Thickness,				//Bold
									1,								//Mipmap level
									fmt.m_IsItalic,					//Italic
									fmt.m_CharSet,					//Character set
									fmt.m_Precision,				//Output precision
									fmt.m_Quality,					//Quality
									fmt.m_PitchAndFamily,			//Pitch
									fmt.m_FontFaceName,				//Font name
									&m_pD3DFont ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DGraphicsFont" ),
									TSTR( "Create" ),
									TSTR( "Failed to create font." ),
									-1 );
		}

		m_IsUsed = MapilTrue;
	}

	MapilVoid D3DGraphicsFont::DrawString( MapilTChar* pStr )
	{
	}

	MapilVoid D3DGraphicsFont::Draw( MapilTChar* pStr )
	{
	}

	MapilVoid D3DGraphicsFont::Draw(	MapilInt32 posX, MapilInt32 posY,
										MapilFloat32 colR, MapilFloat32 colG, MapilFloat32 colB,
										MapilTChar* pStr, ... )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "D3DGraphicsFont" ),
				TSTR( "Draw" ),
				TSTR( "The font isn't created yet." ),
				-1 );

		//World coordinate transformation
		D3DXMATRIXA16 matWorld;
		D3DXMatrixTranslation( &matWorld, posX, posY, 0.0f );
		m_pDev->GetDev().GetPointer()->SetTransform( D3DTS_WORLD, &matWorld );
		//if( FAILED( m_pD3DFont->DrawText(	m_
	}

	MapilInt32 D3DGraphicsFont::Get()
	{
		return reinterpret_cast < MapilInt32 > ( m_pD3DFont );
	}

	MapilVoid D3DGraphicsFont::LostResource()
	{
		if( m_pD3DFont ){
			m_pD3DFont->OnLostDevice();
		}
	}

	MapilVoid D3DGraphicsFont::RestoreResource()
	{
		if( m_pD3DFont ){
			m_pD3DFont->OnResetDevice();
		}
	}
}

#endif	// API_DIRECT3D