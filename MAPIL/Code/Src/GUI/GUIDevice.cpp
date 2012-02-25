/**
*	@file	GUIDevice.cpp
*	@brief	
*	@date	2011.10.23 (Wed) 17:03
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/GUI/GUIDevice.h"

namespace MAPIL
{
	GUIDevice::GUIDevice( GUIAPI api ) : m_GUIAPI( api )
	{
	}

	GUIDevice::~GUIDevice()
	{
	}

	MapilVoid GUIDevice::Create()
	{
	}

	GUIAPI GUIDevice::GetGUIAPI() const
	{
		return m_GUIAPI;
	}

	IGUIDevice CreateGUIDevice( GUIAPI api )
	{
		SharedPointer < GUIDevice > pGD( new GUIDevice( api ) );

		return pGD;
	}
}