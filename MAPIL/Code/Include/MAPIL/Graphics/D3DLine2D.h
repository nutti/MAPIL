/**
*	@file	D3DLine2D.h
*	@brief	
*	@date	2011.9.25 (Sun) 9:25
*/

#ifndef INCLUDED_MAPIL_D3DLINE2D_H
#define INCLUDED_MAPIL_D3DLINE2D_H

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "Line2D.h"
#include "../Util/Color.hpp"

namespace MAPIL
{
	class D3DLine2D : public Line2D
	{
		
	public:
		D3DLine2D( SharedPointer < GraphicsDevice > pDev );
		virtual ~D3DLine2D();
		MapilVoid Draw();
	};
}

#endif	// API_DIRETCT3D

#endif