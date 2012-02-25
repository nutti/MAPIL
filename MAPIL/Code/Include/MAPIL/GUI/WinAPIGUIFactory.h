/**
*	@file	WinAPIGUIFactory.h
*	@brief	
*	@date	2011.7.10(Sun) 11:00
*/

#ifndef INCLUDED_MAPIL_WINAPIGUIFACTORY_H
#define INCLUDED_MAPIL_WINAPIGUIFACTORY_H

#include "../CrossPlatform.h"

#ifdef API_WIN32API

#include "GUIFactory.h"
#include "GUIResourceManager.hpp"
#include "WinAPIWindow.h"
#include "WinAPIGraphicsContext.h"

namespace MAPIL
{
	//class WinAPIWindow;
	//class WinAPIGLContext;
	class WinAPIGUIFactory : public GUIFactory
	{
		GUIResourceManager < WinAPIWindow >					m_WndRM;
		GUIResourceManager < WinAPIGraphicsContext >		m_GCRM;
//#if defined ( API_OPENGL )
//		GUIResourceManager < WinAPIGLContext >		m_GLCRM;
//#endif
	public:
		WinAPIGUIFactory( SharedPointer < GUIDevice > pDev );
		~WinAPIGUIFactory();
		IWindow CreateWnd( const MapilTChar* pKeyStr );
		IGraphicsContext CreateGraphicsContext( const MapilTChar* pKeyStr );
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*/
		MapilVoid Reflesh();
//#if defined ( API_OPENGL )
//		IGLContext CreateGLContext( const MapilTChar* pKeyStr );
//#endif
	};
}

#endif	// API_WIN32API

#endif