/**
*	@file	GLCanvas3D.h
*	@brief	
*	@date	2012.8.16 (Thu) 18:12
*/

#ifndef INCLUDED_MAPIL_GLCANVAS3D_H
#define INCLUDED_MAPIL_GLCANVAS3D_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_OPENGL )

#include "Canvas3D.h"


//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{

	class GLCanvas3D : public Canvas3D
	{
	private:
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		GLCanvas3D( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLCanvas3D();
		/**
		*	@brief Instantiate the Canvas3D object.
		*/
		MapilVoid Create();
		/**
		*	@brief Begin to draw 3-dimension objects.
		*/
		MapilVoid Begin();
		/**
		*	@brief End to draw 3-dimension objects.
		*/
		MapilVoid End();
		MapilVoid DrawPolygon(	const Polygon3DVertexFormat* pFmt,
								MapilInt32 polygonTotal );
		MapilVoid DrawPolygon(	const Polygon3DVertexFormat* pFmt,
								MapilInt32 polygonTotal,
								SharedPointer < Texture > texture );
	};
}

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_CANVAS2D_H
