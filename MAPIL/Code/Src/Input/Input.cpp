/**
*	@file	Input.cpp
*	@brief	
*	@date	2011.7.23 (Sat) 20:02
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Input/Input.h"

namespace MAPIL
{
	Input::Input( SharedPointer < InputDevice > pDev ) : MapilObject(), m_pDev( pDev )
	{
	}

	Input::~Input()
	{
	}
}