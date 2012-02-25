/**
*	@file	Mouse.cpp
*	@brief	
*	@date	2011.8.7 (Sun) 10:56
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Input/Mouse.h"

namespace MAPIL
{
	Mouse::Mouse( SharedPointer < InputDevice > pDev ) : Input( pDev )
	{
	}

	Mouse::~Mouse()
	{
	}
}