/**
*	@file	WinAPIGUIFactory.cpp
*	@brief	
*	@date	2011.7.10(Sun) 11:02
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_WIN32API )

#include "../../Include/MAPIL/GUI/WinAPIGUIFactory.h"
#include "../../Include/MAPIL/GUI/WinAPIWindow.h"

namespace MAPIL
{
	WinAPIGUIFactory::WinAPIGUIFactory( SharedPointer < GUIDevice > pDev ) : GUIFactory( pDev ), m_WndRM(), m_GCRM(), m_RBRM()
	{
		m_WndRM.Init();
		m_GCRM.Init();
		m_RBRM.Init();
	}

	WinAPIGUIFactory::~WinAPIGUIFactory()
	{
		m_WndRM.Init();
		m_GCRM.Init();
		m_RBRM.Init();
	}

	IWindow WinAPIGUIFactory::CreateWnd( const MapilTChar* pKeyStr )
	{
		return m_WndRM.Create( pKeyStr );
	}

	IGraphicsContext WinAPIGUIFactory::CreateGraphicsContext( const MapilTChar* pKeyStr )
	{
		return m_GCRM.Create( pKeyStr );
	}

	IRadioButton WinAPIGUIFactory::CreateRadioButton( const MapilTChar* pKeyStr )
	{
		return m_RBRM.Create( pKeyStr );
	}

	MapilVoid WinAPIGUIFactory::Reflesh()
	{
		m_WndRM.Reflesh();
		m_GCRM.Reflesh();
		m_RBRM.Reflesh();
	}
}

#endif