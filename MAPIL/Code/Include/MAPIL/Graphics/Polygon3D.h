/**
*	@file	Polygon3D.h
*	@brief	
*	@date	2011.8.18 (Thu) 15:56
*/

#ifndef INCLUDED_MAPIL_POLYGON3D_H
#define INCLUDED_MAPIL_POLYGON3D_H

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Math/Matrix.hpp"

namespace MAPIL
{
	class Polygon3D : public Graphics
	{
	public:
		Polygon3D( SharedPointer < GraphicsDevice > pDev );
		virtual ~Polygon3D();
	//	virtual MapilVoid Draw( const Matrix4x4 < MapilFloat32 >& mat ) = 0;
	};
}

#endif