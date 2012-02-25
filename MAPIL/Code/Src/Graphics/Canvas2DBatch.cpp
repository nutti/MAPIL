/**
*	@file	Canvas2DBatch.cpp
*	@brief	Implementation of Canvas2DBatch.
*	@date	2011.9.25 (Sun) 9:34
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Canvas2DBatch.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	Canvas2DBatch::Canvas2DBatch() :	MapilObject(),
										m_LineList(),
										m_RectList(),
										m_CircleList(),
										m_Canvas()
	{
	}

	Canvas2DBatch::~Canvas2DBatch()
	{
	}

	MapilVoid Canvas2DBatch::Create( SharedPointer < Canvas2D > canvas )
	{
		m_Canvas = canvas;
	}

	MapilVoid Canvas2DBatch::Flush()
	{
		m_Canvas->Begin();
		while( !m_LineList.empty() ){
			m_Canvas->Draw( m_LineList.front() );
			m_LineList.pop();
		}
		while( !m_RectList.empty() ){
			m_Canvas->Draw( m_RectList.front() );
			m_RectList.pop();
		}
		while( !m_CircleList.empty() ){
			m_Canvas->Draw( m_CircleList.front() );
			m_CircleList.pop();
		}
		m_Canvas->End();
	}

	// Draw texture.
	MapilVoid Canvas2DBatch::Add( const Line2D& line )
	{
		m_LineList.push( line );
	}

	MapilVoid Canvas2DBatch::Add( const Rectangle2D& rect )
	{
		m_RectList.push( rect );
	}

	MapilVoid Canvas2DBatch::Add( const Circle2D& c )
	{
		m_CircleList.push( c );
	}
}
