/**
*	@file	GUIFactory.cpp
*	@brief	
*	@date	2011.7.10(Sun) 10:58
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/GUI/GUIFactory.h"
#include "../../Include/MAPIL/GUI/WinAPIGUIFactory.h"

namespace MAPIL
{
	GUIFactory::GUIFactory( SharedPointer < GUIDevice > pDev ) : MapilObject(), m_pDev( pDev )
	{
	}

	GUIFactory::~GUIFactory()
	{
	}

	MapilVoid GUIFactory::Reflesh( MapilInt32 count )
	{
		for( MapilInt32 i = 0; i < count; ++i ){
			Reflesh();
		}
	}

	GUIFactory* CreateGUIFactory( SharedPointer < GUIDevice > pDev )
	{
		MapilInt32 api = pDev->GetGUIAPI();
		
		if( api == GUI_API_WIN32API ){
#if defined ( API_WIN32API )
			return new WinAPIGUIFactory( pDev );
#endif
		}
		else{
			return NULL;
		}

		return NULL;
	}
}
