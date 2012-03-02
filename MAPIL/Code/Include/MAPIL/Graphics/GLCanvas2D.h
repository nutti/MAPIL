/**
*	@file	GLCanvas2D.h
*	@brief	This class is derived from Canvas2D class. GLCanvas2D is implemented
*			for OpenGL. The users shouldn't call method from this class directly.
*	@date	2011.6.15 (Wed) 18:46
*/

#ifndef INCLUDED_MAPIL_GLCANVAS2D_H
#define INCLUDED_MAPIL_GLCANVAS2D_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#if defined ( API_OPENGL )

#include "../CrossPlatform.h"

#include "Canvas2D.h"
#include "GLTexture.h"
#include "../Util/Color.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class GLCanvas2D : public Canvas2D
	{
	private:
		GLfloat		m_ViewMat[ 16 ];				///< View transformation matrix.
		GLfloat		m_ProjMat[ 16 ];				///< Projection transformation matrix.
		/**
		*	@brief		Prohibit copy constructor.
		*	@param c	GLCanvas2D object to be copied.
		*/
		GLCanvas2D( const GLCanvas2D& c );
		/**
		*	@brief		Prohibit copy with substitution.
		*	@param c	GLCanvas2D object to be copied.
		*	@return		Copied GLCanvas2D object.
		*/
		GLCanvas2D& operator=( const GLCanvas2D& c );
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		GLCanvas2D( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLCanvas2D();
		/**
		*	@brief Instantiate the GLCanvas2D class.
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
	};
}

#endif	// API_OPENGL

#endif	// INCLUDED_MAPIL_GLCANVAS2D_H