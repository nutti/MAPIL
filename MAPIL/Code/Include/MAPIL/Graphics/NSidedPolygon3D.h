/**
*	@file	NSidedPolygon3D.h
*	@brief	
*	@date	2011.12.31 (Sat) 13:08
*/

#ifndef INCLUDED_MAPIL_NSIDEDPOLYGON3D_H
#define INCLUDED_MAPIL_NSIDEDPOLYGON3D_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Polygon3D.h"
#include "Texture.h"
#include "../Util/SharedPointer.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	struct NSidedPolygon3DVertexFmt
	{
		union
		{
			struct
			{
				MapilFloat32		m_X;				///< X-coordinate of the vertex.
				MapilFloat32		m_Y;				///< Y-coordinate of the vertex.
				MapilFloat32		m_Z;				///< Z-coordinate of the vertex.
			} m_Pos;
			MapilFloat32			m_PosElm[ 3 ];		///< Coordinate of the vertex.
		};
		union
		{
			struct
			{
				MapilUChar			m_R;				///< Red of the vertex color.
				MapilUChar			m_G;				///< Green of the vertex color.
				MapilUChar			m_B;				///< Blue of the vertex color.
				MapilUChar			m_A;				///< Alpha of the vertex color.
			} m_Col;
			MapilUChar				m_ColElm[ 4 ];		///< Color of the vertex.
		};
		union
		{
			struct
			{
				MapilFloat32		m_U;				///< U-coordinate of the texture for the vertex.
				MapilFloat32		m_V;				///< V-coordinate of the texture for the vertex.
			} m_Tex;
			MapilFloat32		m_TexElm[ 2 ];			///< Coordinate of the texture for the vertex.
		};
	};

	enum PolygonRenderingMethod
	{
		POLYGON_RENDERING_METHOD_POINTLIST		= 0,
		POLYGON_RENDERING_METHOD_LINELIST		= 1,
		POLYGON_RENDERING_METHOD_LINESTRIP		= 2,
		POLYGON_RENDERING_METHOD_TRAIANGLELIST	= 3,
		POLYGON_RENDERING_METHOD_TRAIANGLESTRIP	= 4,
		POLYGON_RENDERING_METHOD_TRAIANGLEFAN	= 5,
	};

	class NSidedPolygon3D : public Polygon3D
	{
	public:
		explicit NSidedPolygon3D( SharedPointer < GraphicsDevice > pDev );
		virtual ~NSidedPolygon3D();
		virtual MapilVoid Create(	MapilInt32 vertexTotal, const NSidedPolygon3DVertexFmt fmt[],
									SharedPointer < Texture > pTex, VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER ) = 0;
		virtual MapilVoid Create(	MapilInt32 vertexTotal, const NSidedPolygon3DVertexFmt fmt[],
									VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER ) = 0;
		virtual MapilVoid Update( MapilInt32 index, const NSidedPolygon3DVertexFmt& fmt ) = 0;
		virtual MapilVoid Draw( MapilInt32 method, MapilInt32 count ) = 0;
	};
}

#endif	// INCLUDED_MAPIL_NSIDEDPOLYGON3D_H