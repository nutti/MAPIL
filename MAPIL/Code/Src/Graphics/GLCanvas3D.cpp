/**
*	@file	GLCanvas3D.cpp
*	@brief	Implementation of GLCanvas3D.
*	@date	2012.8.16 (Thu) 18:12
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#include "../../Include/MAPIL/Graphics/GLCanvas3D.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GLCanvas3D::GLCanvas3D( SharedPointer < GraphicsDevice > pDev ) :	Canvas3D( pDev )
	{
	}
	
	GLCanvas3D::~GLCanvas3D()
	{
	}


	MapilVoid GLCanvas3D::Create()
	{
	}

	MapilVoid GLCanvas3D::Begin()
	{
	}

	MapilVoid GLCanvas3D::End()
	{
	}

	MapilVoid GLCanvas3D::DrawPolygon( const Polygon3DVertexFormat* pFmt, MapilInt32 polygonTotal )
	{
	}

	MapilVoid GLCanvas3D::DrawPolygon(	const Polygon3DVertexFormat* pFmt,
										MapilInt32 polygonTotal,
										SharedPointer < Texture > texture )
	{
	}
}

#endif	// API_DIRECT3D