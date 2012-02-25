/**
*	@file	WinAPIInputFactory.cpp
*	@brief	
*	@date	2011.7.23 (Sat) 20:31
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_WIN32API

#include "../../Include/MAPIL/Input/WinAPIInputFactory.h"

namespace MAPIL
{
	WinAPIInputFactory::WinAPIInputFactory( SharedPointer < InputDevice > pDev ) :	InputFactory( pDev ),
																					m_KeyboardRM( pDev ),
																					m_MouseRM( pDev )
	{
		m_KeyboardRM.Init();
		m_MouseRM.Init();
	}

	WinAPIInputFactory::~WinAPIInputFactory()
	{
	}

	IKeyboard WinAPIInputFactory::CreateKeyboard( const MapilTChar* pKeyStr )
	{
		return m_KeyboardRM.Create( pKeyStr );
	}

	IMouse WinAPIInputFactory::CreateMouse( const MapilTChar* pKeyStr )
	{
		return m_MouseRM.Create( pKeyStr );
	}

	MapilVoid WinAPIInputFactory::Reflesh()
	{
		m_KeyboardRM.Reflesh();
		m_MouseRM.Reflesh();
	}
}

#endif	// API_WIN32API
