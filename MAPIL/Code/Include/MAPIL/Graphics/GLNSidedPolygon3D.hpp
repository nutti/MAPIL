/**
*	@file	GLNSidedPolygon3D.hpp
*	@brief	
*	@date	2011.8.18 (Thu) 16:23
*/

#ifndef INCLUDED_MAPIL_GLNSIDEDPOLYGON3D_HPP
#define INCLUDED_MAPIL_GLNSIDEDPOLYGON3D_HPP

#include "../CrossPlatform.h"

#ifdef API_OPENGL

#include "NSidedPolygon3D.hpp"

namespace MAPIL
{
	template < MapilUInt32 numSide >
	class GLNSidedPolygon3D : public NSidedPolygon3D < numSide >
	{
		NSidedPolygon3DVertexFormat		m_Fmt;
	public:
		GLNSidedPolygon3D( GraphicsDevice* pDev );
		~GLNSidedPolygon3D();
	};
}

#endif	// API_OPENGL

#endif