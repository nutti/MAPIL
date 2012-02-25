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

	class GraphicsDevice;
	class Graphics : public MapilObject
	{
	protected:
		SharedPointer < GraphicsDevice >		m_pDev;
		//GraphicsDevice*		m_pDev;
	public:
		Graphics( GraphicsDevice* pDev );
		Graphics( SharedPointer < GraphicsDevice > pDev );
		virtual ~Graphics();
		virtual MapilVoid LostResource();
		virtual MapilVoid RestoreResource();
	};
}

#endif
