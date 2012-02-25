/**
*	@file	NSidedPolygon3D.hpp
*	@brief	
*	@date	2011.8.18 (Thu) 16:08
*/

#ifndef INCLUDED_MAPIL_NSIDEDPOLYGON3D_HPP
#define INCLUDED_MAPIL_NSIDEDPOLYGON3D_HPP

#include "../CrossPlatform.h"

#include "Polygon3D.h"
#include "Texture.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	template < MapilUInt32 numSide >
	struct NSidedPolygon3DVertexFormat
	{
		MapilFloat		m_PosX[ numSide ];
		MapilFloat		m_PosY[ numSide ];
		MapilFloat		m_PosZ[ numSide ];
		MapilFloat		m_ColA[ numSide ];
		MapilFloat		m_ColR[ numSide ];
		MapilFloat		m_ColG[ numSide ];
		MapilFloat		m_ColB[ numSide ];
		MapilFloat		m_TexU[ numSide ];
		MapilFloat		m_TexV[ numSide ];
	};

	template < MapilUInt32 numSide >
	class NSidedPolygon3D : public Polygon3D
	{
	public:
		NSidedPolygon3D( GraphicsDevice* pDev );
		virtual ~NSidedPolygon3D();
		virtual MapilVoid Create(	const NSidedPolygon3DVertexFormat < numSide >& fmt,
									SharedPointer < Texture > pTex ) = 0;
		virtual MapilVoid Update(	const NSidedPolygon3DVertexFormat < numSide >& fmt,
									SharedPointer < Texture > pTex ) = 0;
		virtual MapilVoid Draw() = 0;
	};

	template < MapilUInt32 numSide >
	NSidedPolygon3D < numSide > ::NSidedPolygon3D( GraphicsDevice* pDev ) : Polygon3D( pDev )
	{
	}

	template < MapilUInt32 numSide >
	NSidedPolygon3D < numSide > ::~NSidedPolygon3D()
	{
	}
}

#endif