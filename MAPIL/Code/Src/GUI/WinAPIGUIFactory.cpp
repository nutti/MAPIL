/**
*	@file	WinAPIGUIFactory.cpp
*	@brief	
*	@date	2011.7.10(Sun) 11:02
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_WIN32API

#include "../../Include/MAPIL/GUI/WinAPIGUIFactory.h"
#include "../../Include/MAPIL/GUI/WinAPIWindow.h"
//#include "../../Include/MAPIL/GUI/WinAPIGLContext.h"

namespace MAPIL
{
	WinAPIGUIFactory::WinAPIGUIFactory( SharedPointer < GUIDevice > pDev ) : GUIFactory( pDev ), m_WndRM(), m_GCRM()
//#if defined ( API_OPENGL )
//		, m_GLCRM()
//#endif
	{
		m_WndRM.Init();
		m_GCRM.Init();
//#if defined ( API_OPENGL )
//		m_GLCRM.Init();
//#endif
	}

	WinAPIGUIFactory::~WinAPIGUIFactory()
	{
		m_WndRM.Init();
		m_GCRM.Init();
//#if defined ( API_OPENGL )
//		m_GLCRM.Init();
//#endif
	}

	IWindow WinAPIGUIFactory::CreateWnd( const MapilTChar* pKeyStr )
	{
		return m_WndRM.Create( pKeyStr );
	}

	IGraphicsContext WinAPIGUIFactory::CreateGraphicsContext( const MapilTChar* pKeyStr )
	{
		return m_GCRM.Create( pKeyStr );
	}

	MapilVoid WinAPIGUIFactory::Reflesh()
	{
		m_WndRM.Reflesh();
		m_GCRM.Reflesh();
	}

//#if defined ( API_OPENGL )
//	IGLContext WinAPIGUIFactory::CreateGLContext( const MapilTChar* pKeyStr )
//	{
//		return m_GLCRM.Create( pKeyStr );
//	}
//#endif
}

#endif