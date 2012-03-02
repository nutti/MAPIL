/**
*	@file	Canvas2D.h
*	@brief	Canvas2D class provides an easy way to realize the method
*			to draw 2-dimension figures. The user must call the Create
*			method to instantiate the Canvas2D object at first. 
*			After instantiation, the user can draw figures between
*			Begin method and End method.
*	@date	2011.6.15 (Wed) 18:25
*/

#ifndef INCLUDED_MAPIL_CANVAS2D_H
#define INCLUDED_MAPIL_CANVAS2D_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Util/SharedPointer.hpp"
#include "Texture.h"
#include "../Util/Color.hpp"
#include "../Type.h"
#include "ConstNums.h"

#include "Line2D.h"
#include "Rectangle2D.h"
#include "Circle2D.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class Canvas2D : public Graphics
	{
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		Canvas2D( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~Canvas2D();
		/**
		*	@brief Instantiate the Canvas2D object.
		*/
		virtual MapilVoid Create() = 0;
		/**
		*	@brief Begin to draw 2-dimension figure.
		*/
		virtual MapilVoid Begin() = 0;
		/**
		*	@brief End to draw 2-dimension figure.
		*/
		virtual MapilVoid End() = 0;
		/**
		*	@brief			Draw a 2-dimension point.
		*	@param x		X-Coordinate for the center of the point.
		*	@param y		Y-Coordinate for the center of the point.
		*	@param color	Color for the point.
		*	@param size		Point size.
		*/
		virtual MapilVoid DrawPoint(	MapilInt32 x,
										MapilInt32 y,
										const ColorARGB < MapilFloat32 >& color,
										MapilFloat32 size ) = 0;
		/**
		*	@brief			Draw a 2-dimension line.
		*	@param startX	X-Coordinate for the beginning point of the line.
		*	@param startY	Y-Coordinate for the beginning point of the line.
		*	@param endX		X-Coordinate for the ending point of the line.
		*	@param endY		Y-Coordinate for the ending point of the line.
		*	@param color	Color for the line.
		*	@param width	Line width.
		*/
		virtual MapilVoid DrawLine(	MapilInt32 startX,
									MapilInt32 startY,
									MapilInt32 endX,
									MapilInt32 endY,
									const ColorARGB < MapilFloat32 >& color,
									MapilInt32 width ) = 0;
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
		virtual MapilVoid DrawLine(	MapilInt32 startX,
										MapilInt32 startY,
										const ColorARGB < MapilFloat32 >& startColor,
										MapilInt32 endX,
										MapilInt32 endY,
										const ColorARGB < MapilFloat32 >& endColor,
										MapilInt32 width ) = 0;
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
		virtual MapilVoid DrawRect(	MapilInt32 x1,
										MapilInt32 y1,
										MapilInt32 x2,
										MapilInt32 y2,
										const ColorARGB < MapilFloat32 >& color,
										MapilInt32 width,
										MapilBool isFilled = MapilTrue ) = 0;
		/**
		*	@brief				Draw a 2-dimension circle.
		*	@param centerX		X-Coordinate for the center of the rectangle.
		*	@param centerY		Y-Coordinate for the center of the rectangle.
		*	@param radius		Radius for the circle.
		*	@param color		Color for the circle.
		*	@param width		Line width of the circle.
		*	@param isFilled		Is the rectangle filled?
		*/
		virtual MapilVoid DrawCircle(	MapilInt32 centerX,
										MapilInt32 centerY,
										MapilInt32 radius,
										const ColorARGB < MapilFloat32 >& color,
										MapilInt32 width,
										MapilBool isFilled = MapilTrue ) = 0;
		/**
		*	@brief				Draw figure.
		*	@param line			Line2D class to be drawn.
		*/
		virtual MapilVoid Draw( const Line2D& line ) = 0;
		/**
		*	@brief				Draw figure.
		*	@param rect			Rectangle2D class to be drawn.
		*/
		virtual MapilVoid Draw( const Rectangle2D& rect ) = 0;
		/**
		*	@brief				Draw figure.
		*	@param c			Circle2D class to be drawn.
		*/
		virtual MapilVoid Draw( const Circle2D& c ) = 0;
	};
}

#endif	// INCLUDED_MAPIL_CANVAS2D_H
