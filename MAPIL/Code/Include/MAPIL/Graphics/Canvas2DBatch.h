/**
*	@file	Canvas2DBatch.h
*	@brief	Canvas2DBatch can draw lots of 2-dimension figure at once. This class
*			decreases the overhead when the user transforms the 2-dimension
*			environment to the 3-dimension environment frequently.
*	@date	2011.9.25 (Sun) 9:31
*/

#ifndef INCLUDED_MAPIL_CANVAS2DBATCH_H
#define INCLUDED_MAPIL_CANVAS2DBATCH_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Util/SharedPointer.hpp"
#include "Canvas2D.h"

#include <queue>

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class Canvas2DBatch : public MapilObject
	{
		std::queue < Line2D >				m_LineList;			///< Buffer of the Line2D object to be drawn.
		std::queue < Rectangle2D >			m_RectList;			///< Buffer of the Rectangle2D object to be drawn.
		std::queue < Circle2D >				m_CircleList;		///< Buffer of the Circle2D object to be drawn.
		SharedPointer < Canvas2D >			m_Canvas;			///< Instantiated Canvas object.
	public:
		/**
		*	@brief Constructor.
		*/
		Canvas2DBatch();
		/**
		*	@brief Destructor.
		*/
		~Canvas2DBatch();
		/**
		*	@brief			Instantiate the Canvas2DBatch class.
			@param canvas	SharedPointer to the instantiated Canvas2D object.
		*/
		MapilVoid Create( SharedPointer < Canvas2D > canvas );
		/**
		*	@brief canvas	Draw all buffered figures.
		*/
		MapilVoid Flush();
		/**
		*	@brief line		Line2D object to be drawn.
		*/
		MapilVoid Add( const Line2D& line );
		/**
		*	@brief line		Rectangle2D object to be drawn.
		*/
		MapilVoid Add( const Rectangle2D& rect );
		/**
		*	@brief line		Circle2D object to be drawn.
		*/
		MapilVoid Add( const Circle2D& c );
	};
}

#endif	// INCLUDED_MAPIL_CANVAS2DBATCH_H
