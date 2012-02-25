/**
*	@file	GUIFactory.h
*	@brief	
*	@date	2011.7.10(Sun) 10:55
*/

#ifndef INCLUDED_MAPIL_GUIFACTORY_H
#define INCLUDED_MAPIL_GUIFACTORY_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "../Util/SharedPointer.hpp"
#include "../TChar.h"
#include "GUIDevice.h"

namespace MAPIL
{
	class Window;
	class GraphicsContext;
	//class GLContext;

	typedef SharedPointer < Window >			IWindow;
	typedef SharedPointer < GraphicsContext >	IGraphicsContext;
	//typedef SharedPointer < GLContext >			IGLContext;

	class GUIFactory : public MapilObject
	{
	private:
		SharedPointer < GUIDevice > 			m_pDev;
	public:
		GUIFactory( SharedPointer < GUIDevice > pDev );
		virtual ~GUIFactory();
		virtual IWindow CreateWnd( const MapilTChar* pKeyStr ) = 0;
		virtual IGraphicsContext CreateGraphicsContext( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*/
		virtual MapilVoid Reflesh() = 0;
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*	@param Reflesh count.
		*/
		MapilVoid Reflesh( MapilInt32 count );
//#if defined ( API_OPENGL )
//		virtual IGLContext CreateGLContext( const MapilTChar* pKeyStr ) = 0;
//#endif
	};

	GUIFactory* CreateGUIFactory( SharedPointer < GUIDevice > pDev );
}

#endif