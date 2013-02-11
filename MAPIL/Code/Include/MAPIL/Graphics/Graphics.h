/**
*	@file	Graphics.h
*	@brief	
*	@date	2011.6.15(Wed) 18:2
*/

#ifndef INCLUDED_MAPIL_GRAPHICS_H
#define INCLUDED_MAPIL_GRAPHICS_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	enum VertexManagementMethod
	{
		VERTEX_MANAGEMENT_NONE		= 0,		///< Not use any vertex management.
		VERTEX_MANAGEMENT_BUFFER	= 1,		///< Use the vertex buffer.
	};

	struct Polygon3DVertexFormat
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
			MapilUInt32				m_Color;
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

	class GraphicsDevice;
	class Graphics : public MapilObject
	{
	protected:
		SharedPointer < GraphicsDevice >		m_pDev;
		//GraphicsDevice*		m_pDev;
		MapilBool								m_IsUsed;
	public:
		Graphics( GraphicsDevice* pDev );
		Graphics( SharedPointer < GraphicsDevice > pDev );
		virtual ~Graphics();
		virtual MapilVoid LostResource();
		virtual MapilVoid RestoreResource();
		MapilBool IsValid() const;
	};
}

#endif
