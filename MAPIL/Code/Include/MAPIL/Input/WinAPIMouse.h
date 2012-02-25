/**
*	@file	WinAPIMouse.h
*	@brief	
*	@date	2011.8.7 (Sun) 10:58
*/

#ifndef INCLUDED_MAPIL_WINAPIMOUSE_H
#define INCLUDED_MAPIL_WINAPIMOUSE_H

#include "../CrossPlatform.h"

#ifdef API_WIN32API

#include "Mouse.h"
#include "../Math/Vector.hpp"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	class WinAPIMouse : public Mouse
	{
	public:
		WinAPIMouse( SharedPointer < InputDevice > pDev );
		~WinAPIMouse();
		MapilVoid GetPos( Vector2 < MapilInt32 >* pPos );
		MapilVoid SetPos( const Vector2 < MapilInt32 >& pos );
		MapilBool IsPushed( MapilInt32 button );
	};
}

#endif	// API_WIN32API

#endif