/**
*	@file	Canvas3D.h
*	@brief	
*	@date	2012.8.16 (Thu) 9:57
*/

#ifndef INCLUDED_MAPIL_CANVAS3D_H
#define INCLUDED_MAPIL_CANVAS3D_H

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


//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{

	class GraphicsDevice;
	class Canvas3D : public Graphics
	{
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		Canvas3D( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~Canvas3D();
		/**
		*	@brief Instantiate the Canvas3D object.
		*/
		virtual MapilVoid Create() = 0;
		/**
		*	@brief Begin to draw 3-dimension objects.
		*/
		virtual MapilVoid Begin() = 0;
		/**
		*	@brief End to draw 3-dimension objects.
		*/
		virtual MapilVoid End() = 0;
		virtual MapilVoid DrawPolygon( const Polygon3DVertexFormat* pFmt, MapilInt32 polygonTotal ) = 0;
		virtual MapilVoid DrawPolygon(	const Polygon3DVertexFormat* pFmt,
										MapilInt32 polygonTotal,
										SharedPointer < Texture > texture ) = 0;
	};
}

#endif	// INCLUDED_MAPIL_CANVAS2D_H
