/**
*	@file	D3DCanvas2D.cpp
*	@brief	Implementation of D3DCanvas2D.
*	@date	2011.6.15 (Wed) 18:45
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "../../Include/MAPIL/Graphics/D3DCanvas2D.h"
#include "../../Include/MAPIL/Math/Vector.hpp"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	// Constructor.
	D3DCanvas2D::D3DCanvas2D( SharedPointer < GraphicsDevice > pDev ) :	Canvas2D( pDev ),
																		m_pD3DSurface( NULL )
	{
	}

	// Destructor.
	D3DCanvas2D::~D3DCanvas2D()
	{
		SafeRelease( m_pD3DSurface );
	}

	MapilVoid D3DCanvas2D::Create()
	{
		if( FAILED( m_pDev->GetDev().GetPointer()->GetBackBuffer(	0,
																	0,
																	D3DBACKBUFFER_TYPE_MONO,
																	&m_pD3DSurface ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DCanvas2D" ),
									TSTR( "Create" ),
									TSTR( "Failed to get back buffer." ),
									-1 );
		}
	}

	MapilVoid D3DCanvas2D::Begin()
	{
		if( m_pD3DSurface ){
			if( FAILED( m_pD3DSurface->GetDC( &m_HDC ) ) ){
				throw MapilException(	TSTR( "MMapil" ),
										TSTR( "D3DCanvas2D" ),
										TSTR( "Begin" ),
										TSTR( "Failed to get device context." ),
										-1 );
			}
		}
	}

	MapilVoid D3DCanvas2D::End()
	{
		if( m_pD3DSurface ){
			m_pD3DSurface->ReleaseDC( m_HDC );
		}
	}

	// Draw point.
	MapilVoid D3DCanvas2D::DrawPoint(	MapilInt32 x,
											MapilInt32 y,
											const ColorARGB < MapilFloat32 >& color,
											MapilFloat32 size )
	{
		DrawPoint( x, y, GetColorRGBValue( color.m_R, color.m_G, color.m_B ), size );
	}

	MapilVoid D3DCanvas2D::DrawPoint(	MapilInt32 x,
										MapilInt32 y,
										const ColorARGB < MapilUChar >& color,
										MapilFloat32 size )
	{
		DrawPoint( x, y, GetColorRGBValue( color.m_R, color.m_G, color.m_B ), size );
	}

	MapilVoid D3DCanvas2D::DrawPoint( MapilInt32 x, MapilInt32 y, MapilUInt32 color, MapilFloat32 size )
	{
		::SetPixelV( m_HDC, x, y, color );
	}

	// Draw line.
	MapilVoid D3DCanvas2D::DrawLine(	MapilInt32 startX,
										MapilInt32 startY,
										MapilInt32 endX,
										MapilInt32 endY,
										const ColorARGB < MapilFloat32 >& color,
										MapilInt32 width )
	{
		DrawLine( startX, startY, endX, endY, GetColorRGBValue( color.m_R, color.m_G, color.m_B ), width );
	}

	MapilVoid D3DCanvas2D::DrawLine(	MapilInt32 startX,
										MapilInt32 startY,
										MapilInt32 endX,
										MapilInt32 endY,
										const ColorARGB < MapilUChar >& color,
										MapilInt32 width )
	{
		DrawLine( startX, startY, endX, endY, GetColorRGBValue( color.m_R, color.m_G, color.m_B ), width );
	}

	MapilVoid D3DCanvas2D::DrawLine(	MapilInt32 startX, MapilInt32 startY, MapilInt32 endX, MapilInt32 endY,
										MapilUInt32 color, MapilInt32 width )
	{
		HPEN pen = ::CreatePen( PS_SOLID, width, color );

		SelectObject( m_HDC, pen );
		::MoveToEx( m_HDC, startX, startY, NULL );
		::LineTo( m_HDC, endX, endY );
		DeleteObject( pen );
	}

	// Draw line. ( 2 )
	MapilVoid D3DCanvas2D::DrawLine(	MapilInt32 startX,
										MapilInt32 startY,
										const ColorARGB < MapilFloat32 >& startColor,
										MapilInt32 endX,
										MapilInt32 endY,
										const ColorARGB < MapilFloat32 >& endColor,
										MapilInt32 width )
	{
	}

	// Draw recangle.
	MapilVoid D3DCanvas2D::DrawRect(	MapilInt32 x1,
										MapilInt32 y1,
										MapilInt32 x2,
										MapilInt32 y2,
										const ColorARGB < MapilFloat32 >& color,
										MapilInt32 width,
										MapilBool isFilled )
	{
		DrawRect( x1, y1, x2, y2, GetColorRGBValue( color.m_R, color.m_G, color.m_B ), width , isFilled );
	}

	MapilVoid D3DCanvas2D::DrawRect(	MapilInt32 x1,
										MapilInt32 y1,
										MapilInt32 x2,
										MapilInt32 y2,
										const ColorARGB < MapilUChar >& color,
										MapilInt32 width,
										MapilBool isFilled )
	{
		DrawRect( x1, y1, x2, y2, GetColorRGBValue( color.m_R, color.m_G, color.m_B ), width, isFilled );
	}

	MapilVoid D3DCanvas2D::DrawRect(	MapilInt32 x1,
										MapilInt32 y1,
										MapilInt32 x2,
										MapilInt32 y2,
										MapilUInt32 color,
										MapilInt32 width,
										MapilBool isFilled )
	{
		HPEN pen = ::CreatePen( PS_SOLID, width, color );
		HBRUSH brush;
		if( isFilled ){
			brush = ::CreateSolidBrush( color );
		}
		else{
			brush = static_cast < HBRUSH > ( ::GetStockObject( NULL_BRUSH ) );
		}
		SelectObject( m_HDC, pen );
		SelectObject( m_HDC, brush );
		::Rectangle( m_HDC, x1, y1, x2, y2 );
		DeleteObject( brush );
		DeleteObject( pen );
	}

	// Draw circle.
	MapilVoid D3DCanvas2D::DrawCircle(	MapilInt32 centerX,
										MapilInt32 centerY,
										MapilInt32 radius,
										const ColorARGB < MapilFloat32 >& color,
										MapilInt32 width,
										MapilBool isFilled )
	{
		DrawCircle( centerX, centerY, radius, GetColorRGBValue( color.m_R, color.m_G, color.m_B ), width, isFilled );
	}

	// Draw circle.
	MapilVoid D3DCanvas2D::DrawCircle(	MapilInt32 centerX,
										MapilInt32 centerY,
										MapilInt32 radius,
										const ColorARGB < MapilUChar >& color,
										MapilInt32 width,
										MapilBool isFilled )
	{
		DrawCircle( centerX, centerY, radius, GetColorRGBValue( color.m_R, color.m_G, color.m_B ), width, isFilled );
	}

	MapilVoid D3DCanvas2D::DrawCircle(	MapilInt32 centerX,
										MapilInt32 centerY,
										MapilInt32 radius,
										MapilUInt32 color,
										MapilInt32 width,
										MapilBool isFilled )
	{
		HPEN pen = ::CreatePen( PS_SOLID, width, color );
		HBRUSH brush;
		if( isFilled ){
			brush = ::CreateSolidBrush( color );
		}
		else{
			brush = static_cast < HBRUSH > ( ::GetStockObject( NULL_BRUSH ) );
		}
		SelectObject( m_HDC, pen );
		SelectObject( m_HDC, brush );
		::Ellipse( m_HDC, centerX - radius, centerY - radius, centerX + radius, centerY + radius );
		DeleteObject( brush );
		DeleteObject( pen );
	}

	MapilVoid D3DCanvas2D::Draw( const Line2D& line )
	{
		DrawLine( line.m_StartX, line.m_StartY, line.m_EndX, line.m_EndY, line.m_Col, line.m_Width );
	}

	MapilVoid D3DCanvas2D::Draw( const Rectangle2D& rect )
	{
		DrawRect( rect.m_X1, rect.m_Y1, rect.m_X2, rect.m_Y2, rect.m_Col, rect.m_Width, rect.m_IsFilled );
	}

	MapilVoid D3DCanvas2D::Draw( const Circle2D& c )
	{
		DrawCircle( c.m_CenterX, c.m_CenterY, c.m_Radius, c.m_Col, c.m_Width, c.m_IsFilled );
	}

	MapilVoid D3DCanvas2D::LostResource()
	{
		SafeRelease( m_pD3DSurface );
	}

	MapilVoid D3DCanvas2D::RestoreResource()
	{
		if( FAILED( m_pDev->GetDev().GetPointer()->GetBackBuffer(	0,
																	0,
																	D3DBACKBUFFER_TYPE_MONO,
																	&m_pD3DSurface ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DCanvas2D" ),
									TSTR( "Create" ),
									TSTR( "Failed to get back buffer." ),
									-1 );
		}
	}
}

#endif	// API_DIRECT3D
