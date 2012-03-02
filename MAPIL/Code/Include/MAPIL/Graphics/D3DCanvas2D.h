/**
*	@file	D3DCanvas2D.h
*	@brief	This class is derived from Canvas2D class. GLCanvas2D is implemented
*			for OpenGL. The users shouldn't call method from this class directly.
*	@date	2011.9.5 (Mon) 11:55
*/

#ifndef INCLUDED_MAPIL_D3DCANVAS2D_H
#define INCLUDED_MAPIL_D3DCANVAS2D_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3dx9.h>

#include "Canvas2D.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class D3DCanvas2D : public Canvas2D
	{
	private:
		::LPDIRECT3DSURFACE9		m_pD3DSurface;			///< D3D Surface.
		::HDC						m_HDC;					///< Device context.
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		D3DCanvas2D( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DCanvas2D();
		/**
		*	@brief Instantiate the D3DCanvas2D class.
		*/
		MapilVoid Create();
		/**
		*	@brief Begin to draw 2-dimension figure.
		*/
		MapilVoid Begin();
		/**
		*	@brief End to draw 2-dimension figure.
		*/
		MapilVoid End();
		/**
		*	@brief			Draw a 2-dimension point.
		*	@param x		X-Coordinate for the center of the point.
		*	@param y		Y-Coordinate for the center of the point.
		*	@param color	Color for the point.
		*	@param size		Point size.
		*/
		MapilVoid DrawPoint(	MapilInt32 x,
								MapilInt32 y,
								const ColorARGB < MapilFloat32 >& color,
								MapilFloat32 size );
		/**
		*	@brief			Draw a 2-dimension point.
		*	@param x		X-Coordinate for the center of the point.
		*	@param y		Y-Coordinate for the center of the point.
		*	@param color	Color for the point.
		*	@param size		Point size.
		*/
		MapilVoid DrawPoint(	MapilInt32 x,
								MapilInt32 y,
								const ColorARGB < MapilUChar >& color,
								MapilFloat32 size );
		/**
		*	@brief			Draw a 2-dimension point.
		*	@param x		X-Coordinate for the center of the point.
		*	@param y		Y-Coordinate for the center of the point.
		*	@param color	Color for the point.
		*	@param size		Point size.
		*/
		MapilVoid DrawPoint( MapilInt32 x, MapilInt32 y, MapilUInt32 color, MapilFloat32 size );
		/**
		*	@brief			Draw a 2-dimension line.
		*	@param startX	X-Coordinate for the beginning point of the line.
		*	@param startY	Y-Coordinate for the beginning point of the line.
		*	@param endX		X-Coordinate for the ending point of the line.
		*	@param endY		Y-Coordinate for the ending point of the line.
		*	@param color	Color for the line.
		*	@param width	Line width.
		*/
		MapilVoid DrawLine(	MapilInt32 startX,
							MapilInt32 startY,
							MapilInt32 endX,
							MapilInt32 endY,
							const ColorARGB < MapilFloat32 >& color,
							MapilInt32 width );
		/**
		*	@brief			Draw a 2-dimension line.
		*	@param startX	X-Coordinate for the beginning point of the line.
		*	@param startY	Y-Coordinate for the beginning point of the line.
		*	@param endX		X-Coordinate for the ending point of the line.
		*	@param endY		Y-Coordinate for the ending point of the line.
		*	@param color	Color for the line.
		*	@param width	Line width.
		*/
		MapilVoid DrawLine(	MapilInt32 startX,
							MapilInt32 startY,
							MapilInt32 endX,
							MapilInt32 endY,
							const ColorARGB < MapilUChar >& color,
							MapilInt32 width );
		/**
		*	@brief			Draw a 2-dimension line.
		*	@param startX	X-Coordinate for the beginning point of the line.
		*	@param startY	Y-Coordinate for the beginning point of the line.
		*	@param endX		X-Coordinate for the ending point of the line.
		*	@param endY		Y-Coordinate for the ending point of the line.
		*	@param color	Color for the line.
		*	@param width	Line width.
		*/
		MapilVoid DrawLine(	MapilInt32 startX, MapilInt32 startY, MapilInt32 endX, MapilInt32 endY,
							MapilUInt32 color, MapilInt32 width );
		/**
		*	@brief				Draw a 2-dimension line.
		*	@param startX		X-Coordinate for the beginning point of the line.
		*	@param startY		Y-Coordinate for the beginning point of the line.
		*	@param startColor	Color for the beginning point of the line.
		*	@param endX			X-Coordinate for the ending point of the line.
		*	@param endY			Y-Coordinate for the ending point of the line.
		*	@param endColor		Color for the beginning point of the line.
		*	@param width		Line width.
		*/
		MapilVoid DrawLine(	MapilInt32 startX,
							MapilInt32 startY,
							const ColorARGB < MapilFloat32 >& startColor,
							MapilInt32 endX,
							MapilInt32 endY,
							const ColorARGB < MapilFloat32 >& endColor,
							MapilInt32 width );
		/**
		*	@brief			Draw a 2-dimension rectangle.
		*	@param x1		X-Coordinate for the left-top point of the rectangle.
		*	@param y1		Y-Coordinate for the left-top point of the rectangle.
		*	@param x2		X-Coordinate for the right-bottom point of the rectangle.
		*	@param y2		Y-Coordinate for the right-bottom point of the rectangle.
		*	@param color	Color for the rectangle.
		*	@param width	Line width of the rectangle.
		*	@param isFilled	Is the rectangle filled?
		*/
		MapilVoid DrawRect(	MapilInt32 x1,
							MapilInt32 y1,
							MapilInt32 x2,
							MapilInt32 y2,
							const ColorARGB < MapilFloat32 >& color,
							MapilInt32 width,
							MapilBool isFilled = MapilTrue );
		/**
		*	@brief			Draw a 2-dimension rectangle.
		*	@param x1		X-Coordinate for the left-top point of the rectangle.
		*	@param y1		Y-Coordinate for the left-top point of the rectangle.
		*	@param x2		X-Coordinate for the right-bottom point of the rectangle.
		*	@param y2		Y-Coordinate for the right-bottom point of the rectangle.
		*	@param color	Color for the rectangle.
		*	@param width	Line width of the rectangle.
		*	@param isFilled	Is the rectangle filled?
		*/
		MapilVoid DrawRect(	MapilInt32 x1,
							MapilInt32 y1,
							MapilInt32 x2,
							MapilInt32 y2,
							const ColorARGB < MapilUChar >& color,
							MapilInt32 width,
							MapilBool isFilled = MapilTrue );
		/**
		*	@brief			Draw a 2-dimension rectangle.
		*	@param x1		X-Coordinate for the left-top point of the rectangle.
		*	@param y1		Y-Coordinate for the left-top point of the rectangle.
		*	@param x2		X-Coordinate for the right-bottom point of the rectangle.
		*	@param y2		Y-Coordinate for the right-bottom point of the rectangle.
		*	@param color	Color for the rectangle.
		*	@param width	Line width of the rectangle.
		*	@param isFilled	Is the rectangle filled?
		*/
		MapilVoid DrawRect(	MapilInt32 x1,
							MapilInt32 y1,
							MapilInt32 x2,
							MapilInt32 y2,
							MapilUInt32 color,
							MapilInt32 width,
							MapilBool isFilled = MapilTrue );
		/**
		*	@brief				Draw a 2-dimension circle.
		*	@param centerX		X-Coordinate for the center of the rectangle.
		*	@param centerY		Y-Coordinate for the center of the rectangle.
		*	@param radius		Radius for the circle.
		*	@param color		Color for the circle.
		*	@param width		Line width of the circle.
		*	@param isFilled		Is the rectangle filled?
		*/
		MapilVoid DrawCircle(	MapilInt32 centerX,
								MapilInt32 centerY,
								MapilInt32 radius,
								const ColorARGB < MapilFloat32 >& color,
								MapilInt32 width,
								MapilBool isFilled = MapilTrue );
		/**
		*	@brief				Draw a 2-dimension circle.
		*	@param centerX		X-Coordinate for the center of the rectangle.
		*	@param centerY		Y-Coordinate for the center of the rectangle.
		*	@param radius		Radius for the circle.
		*	@param color		Color for the circle.
		*	@param width		Line width of the circle.
		*	@param isFilled		Is the rectangle filled?
		*/
		MapilVoid DrawCircle(	MapilInt32 centerX,
								MapilInt32 centerY,
								MapilInt32 radius,
								const ColorARGB < MapilUChar >& color,
								MapilInt32 width,
								MapilBool isFilled = MapilTrue );
		/**
		*	@brief				Draw a 2-dimension circle.
		*	@param centerX		X-Coordinate for the center of the rectangle.
		*	@param centerY		Y-Coordinate for the center of the rectangle.
		*	@param radius		Radius for the circle.
		*	@param color		Color for the circle.
		*	@param width		Line width of the circle.
		*	@param isFilled		Is the rectangle filled?
		*/
		MapilVoid DrawCircle(	MapilInt32 centerX,
								MapilInt32 centerY,
								MapilInt32 radius,
								MapilUInt32 color,
								MapilInt32 width,
								MapilBool isFilled = MapilTrue );
		/**
		*	@brief				Draw figure.
		*	@param line			Line2D object to be drawn.
		*/
		MapilVoid Draw( const Line2D& line );
		/**
		*	@brief				Draw figure.
		*	@param rect			Rectangle2D object to be drawn.
		*/
		MapilVoid Draw( const Rectangle2D& rect );
		/**
		*	@brief				Draw figure.
		*	@param c			Circle2D object to be drawn.
		*/
		MapilVoid Draw( const Circle2D& c );
		MapilVoid LostResource();
		MapilVoid RestoreResource();
	};
}

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DCANVAS2D_H