/**
*	@file	D3DCanvas3D.h
*	@brief	
*	@date	2012.8.16 (Thu) 10:05
*/

#ifndef INCLUDED_MAPIL_D3DCANVAS3D_H
#define INCLUDED_MAPIL_D3DCANVAS3D_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3d9.h>

#include "Canvas3D.h"


//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	enum Polygon3DRenderMethod
	{
		POLYGON_3D_RENDER_METHOD_TRIANGLE_STRIP		= 0,
	};

	class D3DCanvas3D : public Canvas3D
	{
	private:
		::LPDIRECT3DVERTEXDECLARATION9		m_pVertexDecl;			///< Vertex declaration.
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		D3DCanvas3D( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DCanvas3D();
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
