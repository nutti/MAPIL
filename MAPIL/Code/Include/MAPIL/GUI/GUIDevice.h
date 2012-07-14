/**
*	@file	GUIDevice.h
*	@brief	
*	@date	2011.10.23 (Sun) 16:55
*/

#ifndef INCLUDED_MAPIL_GUIDEVICE_H
#define INCLUDED_MAPIL_GUIDEVICE_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	enum GUIAPI
	{
		GUI_API_NONE		= 0,
		GUI_API_WIN32API	= 1,
		GUI_API_GTK			= 2,
		GUI_API_UNKNOWN		= 3,
	};

	class GUIDevice : public MapilObject
	{
	private:
		MapilInt32			m_GUIAPI;
	public:
		explicit GUIDevice( MapilInt32 api );
		virtual ~GUIDevice();
		MapilVoid Create();
		MapilInt32 GetGUIAPI() const;
	};

	typedef SharedPointer < GUIDevice >		IGUIDevice;

	IGUIDevice CreateGUIDevice( MapilInt32 api );
}

#endif	// INCLUDED_MAPIL_GUIDEVICE_H