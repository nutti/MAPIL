/**
*	@file	GLCanvas2D.cpp
*	@brief	Implementation of GLCanvas2D.
*	@date	2011.6.15 (Wed) 18:45
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#include <math.h>

#if defined ( API_WIN32API )
#include <Windows.h>
#endif
#if defined ( OS_WIN_32BIT )
#include <gl/GL.h>
#endif
#if defined ( OS_LINUX_32BIT )
#include <GL/gl.h>
#endif

#include "../../Include/MAPIL/Graphics/GLCanvas2D.h"
#include "../../Include/MAPIL/Math/Vector.hpp"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	// Constructor.
	GLCanvas2D::GLCanvas2D( SharedPointer < GraphicsDevice > pDev ) : Canvas2D( pDev )
	{
	}

	// Destructor.
	GLCanvas2D::~GLCanvas2D()
	{
	}

	MapilVoid GLCanvas2D::Create()
	{
	}

	MapilVoid GLCanvas2D::Begin()
	{
		glGetFloatv( GL_MODELVIEW_MATRIX, m_ViewMat );
		glGetFloatv( GL_PROJECTION_MATRIX, m_ProjMat );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho( 0, 640, 480, 0, -1, 1 );
	}

	MapilVoid GLCanvas2D::End()
	{
		glMatrixMode( GL_MODELVIEW );
		glLoadMatrixf( m_ViewMat );
		glMatrixMode( GL_PROJECTION );
		glLoadMatrixf( m_ProjMat );
	}

	// Draw point.
	MapilVoid GLCanvas2D::DrawPoint(	MapilInt32 x,
											MapilInt32 y,
											const ColorARGB < MapilFloat32 >& color,
											MapilFloat32 size )
	{
		glPointSize( size );
		glBegin( GL_POINTS );
		glColor4f( color.m_R, color.m_G, color.m_B, color.m_A );
		glVertex2i( x, y );
		glEnd();
	}

	// Draw line.
	MapilVoid GLCanvas2D::DrawLine(	MapilInt32 startX,
										MapilInt32 startY,
										MapilInt32 endX,
										MapilInt32 endY,
										const ColorARGB < MapilFloat32 >& color,
										MapilFloat32 width )
	{
		glLineWidth( width );
		glBegin( GL_LINES );
		glColor4f( color.m_R, color.m_G, color.m_B, color.m_A );
		glVertex2i( startX, startY );
		glColor4f( color.m_G, color.m_R, color.m_B, color.m_A );
		glVertex2i( endX, endY );
		glEnd();
	}

	// Draw line. ( 2 )
	MapilVoid GLCanvas2D::DrawLine(	MapilInt32 startX,
										MapilInt32 startY,
										const ColorARGB < MapilFloat32 >& startColor,
										MapilInt32 endX,
										MapilInt32 endY,
										const ColorARGB < MapilFloat32 >& endColor,
										MapilFloat32 width )
	{
		glLineWidth( width );
		glBegin( GL_LINES );
		glColor4f( startColor.m_R, startColor.m_G, startColor.m_B, startColor.m_A );
		glVertex2i( startX, startY );
		glColor4f( endColor.m_R, endColor.m_G, endColor.m_B, endColor.m_A );
		glVertex2i( endX, endY );
		glEnd();
	}

	// Draw recangle.
	MapilVoid GLCanvas2D::DrawRect(	MapilInt32 x1,
										MapilInt32 y1,
										MapilInt32 x2,
										MapilInt32 y2,
										const ColorARGB < MapilFloat32 >& color,
										MapilFloat32 width,
										MapilBool isFilled )
	{
		if( isFilled ){
			glBegin( GL_QUADS );
		}
		else{
			glLineWidth( width );
			glBegin( GL_LINE_LOOP );
		}
		glColor4f( color.m_R, color.m_G, color.m_B, color.m_A );
		glVertex2i( x1, y1 );
		glVertex2i( x1, y2 );
		glVertex2i( x2, y2 );
		glVertex2i( x2, y1 );
		glEnd();
	}

	// Draw circle.
	MapilVoid GLCanvas2D::DrawCircle(	MapilInt32 centerX,
											MapilInt32 centerY,
											MapilFloat32 radius,
											const ColorARGB < MapilFloat32 >& color,
											MapilFloat32 width,
											MapilBool isFilled )
	{
		const MapilDouble pi = 3.1415;
		for( MapilDouble angle1 = 0.0; angle1 < 360.0; angle1 += 1.0 ){
			MapilDouble angle2 = angle1 + 1.0;
			MapilDouble theta1 = angle1 * pi / 180.0;
			MapilDouble theta2 = angle2 * pi / 180.0;

			MapilFloat32 x1 = static_cast < MapilFloat32 > ( radius * cos( theta1 ) + centerX );
			MapilFloat32 y1 = static_cast < MapilFloat32 > ( radius * sin( theta1 ) + centerY );
			MapilFloat32 x2 = static_cast < MapilFloat32 > ( radius * cos( theta2 ) + centerX );
			MapilFloat32 y2 = static_cast < MapilFloat32 > ( radius * sin( theta2 ) + centerY );

			if( isFilled ){
				glBegin( GL_TRIANGLES );
			}
			else{
				glLineWidth( width );
				glBegin( GL_LINES );
			}
			glColor4f( color.m_R, color.m_G, color.m_B, color.m_A );
			glVertex2f( static_cast < MapilFloat32 > ( centerX ), static_cast < MapilFloat32 > ( centerY ) );
			glVertex2f( x1, y1 );
			glVertex2f( x2, y2 );
			glEnd();
		}
	}

	MapilVoid GLCanvas2D::Draw( const Line2D& line )
	{
		DrawLine( line.m_StartX, line.m_StartY, line.m_EndX, line.m_EndY, line.m_Col, line.m_Width );
	}

	MapilVoid GLCanvas2D::Draw( const Rectangle2D& rect )
	{
		DrawRect( rect.m_X1, rect.m_Y1, rect.m_X2, rect.m_Y2, rect.m_Col, rect.m_Width, rect.m_IsFilled );
	}

	MapilVoid GLCanvas2D::Draw( const Circle2D& c )
	{
		DrawCircle( c.m_CenterX, c.m_CenterY, c.m_Radius, c.m_Col, c.m_Width, c.m_IsFilled );
	}
}

#endif	// API_OPENGL
