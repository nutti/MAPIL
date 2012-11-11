/**
*	@file	InputFactory.cpp
*	@brief	
*	@date	2011.7.23 (Sat) 20:24
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Input/InputFactory.h"
#include "../../Include/MAPIL/Input/InputDevice.h"
#include "../../Include/MAPIL/Input/DIInputFactory.h"
#include "../../Include/MAPIL/Input/WinAPIInputFactory.h"

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

	InputFactory* CreateInputFactory( SharedPointer < InputDevice > pDev )
	{
		MapilInt32 api = pDev->GetInputAPI();

		if( api == INPUT_API_DIRECTINPUT ){
#if defined ( API_DIRECTINPUT )
			//return SharedPointer < GraphicsFactory > ( new D3DGraphicsFactory( pDev ) );
			return new DIInputFactory( pDev );
#endif
		}
		else if( api == INPUT_API_WIN32API ){
#if defined ( API_WIN32API )
			return new WinAPIInputFactory( pDev );
#endif
		}
		else{
			return NULL;
		}

		return NULL;
	}
}
