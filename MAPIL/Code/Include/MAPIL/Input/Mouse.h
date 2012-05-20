/**
*	@file	Mouse.h
*	@brief	
*	@date	2011.8.7 (Sun) 10:53
*/

#ifndef INCLUDED_MAPIL_MOUSE_H
#define INCLUDED_MAPIL_MOUSE_H

#include "../CrossPlatform.h"

#include "Input.h"
#include "../Math/Vector.hpp"
#include "../Util/SharedPointer.hpp"
#include "../GUI/Window.h"

namespace MAPIL
{
	class Mouse : public Input
	{
	public:
		Mouse( SharedPointer < InputDevice > pDev );
		virtual ~Mouse();
		virtual MapilVoid Create( SharedPointer < Window > pWnd ) = 0;
		virtual MapilVoid GetPos( Vector2 < MapilInt32 >* pPos ) = 0;
		virtual MapilVoid SetPos( const Vector2 < MapilInt32 >& pos ) = 0;
		virtual MapilBool IsPushed( MapilInt32 button ) = 0;
	};
}

#endif