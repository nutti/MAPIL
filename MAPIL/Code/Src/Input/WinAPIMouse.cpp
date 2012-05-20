/**
*	@file	WinAPIMouse.cpp
*	@brief	
*	@date	2011.8.7 (Sun) 11:00
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_WIN32API

#include <Windows.h>

#include "../../Include/MAPIL/Input/WinAPIMouse.h"

namespace MAPIL
{
	WinAPIMouse::WinAPIMouse( SharedPointer < InputDevice > pDev ) : Mouse( pDev )
	{
	}

	WinAPIMouse::~WinAPIMouse()
	{
	}

	MapilVoid WinAPIMouse::Create( SharedPointer < Window > pWnd )
	{
	}

	MapilVoid WinAPIMouse::GetPos( Vector2 < MapilInt32 >* pPos )
	{
		POINT p;
		::GetCursorPos( &p );
		pPos->m_X = p.x;
		pPos->m_Y = p.y;
	}

	MapilVoid WinAPIMouse::SetPos( const Vector2 < MapilInt32 >& pos )
	{
		POINT p;
		p.x = pos.m_X;
		p.y = pos.m_Y;
		::SetCursorPos( p.x, p.y );
	}

	MapilBool WinAPIMouse::IsPushed( MapilInt32 button )
	{
		return ( GetKeyState( button ) & 0x80 ) ? MapilTrue : MapilFalse;
	}
}

#endif	// API_WIN32API