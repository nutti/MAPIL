/**
*	@file	DIInputFactory.cpp
*	@brief	
*	@date	2012.5.20 (Sun) 9:05
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_WIN32API )
#if defined ( API_DIRECTINPUT )

#include "../../Include/MAPIL/Input/DIInputFactory.h"

namespace MAPIL
{
	DIInputFactory::DIInputFactory( SharedPointer < InputDevice > pDev ) :	InputFactory( pDev ),
																			m_KeyboardRM( pDev ),
																			m_MouseRM( pDev )
	{
		m_KeyboardRM.Init();
		m_MouseRM.Init();
	}

	DIInputFactory::~DIInputFactory()
	{
	}

	IKeyboard DIInputFactory::CreateKeyboard( const MapilTChar* pKeyStr )
	{
		return m_KeyboardRM.Create( pKeyStr );
	}

	IMouse DIInputFactory::CreateMouse( const MapilTChar* pKeyStr )
	{
		return m_MouseRM.Create( pKeyStr );
	}

	MapilVoid DIInputFactory::Reflesh()
	{
		m_KeyboardRM.Reflesh();
		m_MouseRM.Reflesh();
	}
}

#endif	// API_DIRECTINPUT
#endif	// API_WIN32API
