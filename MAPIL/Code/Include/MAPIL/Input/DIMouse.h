/**
*	@file	DIMouse.h
*	@brief	
*	@date	2012.5.19 (Sat) 8:28
*/

#ifndef INCLUDED_MAPIL_DIMOUSE_H
#define INCLUDED_MAPIL_DIMOUSE_H

#include "../CrossPlatform.h"

#if defined ( API_DIRECTINPUT )

#include "Mouse.h"
#include "../Util/SharedPointer.hpp"
#include "../GUI/WinAPIWindow.h"

namespace MAPIL
{
	class DIMouse : public Mouse
	{
		::LPDIRECTINPUTDEVICE8			m_pMouseDev;
		MapilBool						m_IsUsed;
		SharedPointer < WinAPIWindow >	m_pWnd;
		MapilBool						m_IsInputActive;
	public:
		DIMouse( SharedPointer < InputDevice > pDev );
		~DIMouse();
		MapilVoid Create( SharedPointer < Window > pWnd );
		MapilVoid GetPos( Vector2 < MapilInt32 >* pPos );
		MapilVoid SetPos( const Vector2 < MapilInt32 >& pos );
		MapilBool IsPushed( MapilInt32 button );
	};
}

#endif	// API_DIRECTINPUT

#endif