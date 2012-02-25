/**
*	@file	D3DLine2D.cpp
*	@brief	
*	@date	2011.9.25 (Sun) 9:26
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "../../Include/MAPIL/Graphics/D3DLine2D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	D3DLine2D::D3DLine2D( SharedPointer < GraphicsDevice > pDev ) : Line2D( pDev )
	{
	}

	D3DLine2D::~D3DLine2D()
	{
	}

	MapilVoid D3DLine2D::Draw()
	{
		//HPEN pen = ::CreatePen( PS_SOLID, m_Width, RGB(	static_cast < MapilInt32 > ( m_Col.m_R * 255 ),
		//												static_cast < MapilInt32 > ( m_Col.m_G * 255 ),
		//												static_cast < MapilInt32 > ( m_Col.m_B * 255 ) ) );
		
		//SelectObject( m_HDC, pen );
		//::MoveToEx( m_HDC, m_StartX, m_StartY, NULL );
		//::LineTo( m_HDC, m_EndX, m_EndY );
		//DeleteObject( pen );
	}
}

#endif	// API_DIRECT3D