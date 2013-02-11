/**
*	@file	WinAPIMutex.h
*	@brief	
*	@date	2013.2.2(Sat) 9:19
*/

#ifndef INCLUDED_MAPIL_WINAPIMUTEX_H
#define INCLUDED_MAPIL_WINAPIMUTEX_H

#include "../CrossPlatform.h"

#if defined ( API_WIN32API )

#include <Windows.h>

#include "../Type.h"
#include "../Util/MapilObject.h"

namespace MAPIL
{
	class WinAPIMutex : public MapilObject
	{
	private:
		::HANDLE			m_Handle;
		static MapilInt32	m_MutexTotal;
	public:
		// Constructor.
		WinAPIMutex();
		~WinAPIMutex();
		MapilVoid Lock();
		MapilVoid Unlock();
	};
}

#endif	// API_WIN32API

#endif
