/**
*	@file	GUIDevice.h
*	@brief	
*	@date	2011.10.23 (Sun) 16:55
*/

#ifndef INCLUDED_MAPIL_GUIDEVICE_H
#define INCLUDED_MAPIL_GUIDEVICE_H

#include "../CrossPlatform.h"

#include "../Util/Device.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	enum GUIAPI
	{
		GUI_API_UNKNOWN		= 0,
		GUI_API_WIN32API	= 1,
		GUI_API_GTK			= 2,
	};

	class GUIDevice : public Device
	{
	private:
		GUIAPI			m_GUIAPI;
	public:
		explicit GUIDevice( GUIAPI api );
		virtual ~GUIDevice();
		MapilVoid Create();
		GUIAPI GetGUIAPI() const;
	};

	typedef SharedPointer < GUIDevice >		IGUIDevice;

	IGUIDevice CreateGUIDevice( GUIAPI api );
}

#endif	// INCLUDED_MAPIL_GUIDEVICE_H