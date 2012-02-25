/**
*	@file	InputFactory.cpp
*	@brief	
*	@date	2011.7.23 (Sat) 20:24
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Input/InputFactory.h"

namespace MAPIL
{
	InputFactory::InputFactory( SharedPointer < InputDevice > pDev ) :	MapilObject(),
																		m_pDev( pDev )
	{
	}

	InputFactory::~InputFactory()
	{
	}

	MapilVoid InputFactory::Reflesh( MapilInt32 count )
	{
		for( MapilInt32 i = 0; i < count; ++i ){
			Reflesh();
		}
	}
}