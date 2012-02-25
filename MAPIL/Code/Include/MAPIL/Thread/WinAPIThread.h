/**
*	@file	WinAPIThread.h
*	@brief	
*	@date	2011.7.20(Wed) 7:31
*/

#ifndef INCLUDED_MAPIL_WINAPITHREAD_H
#define INCLUDED_MAPIL_WINAPITHREAD_H

#include "../CrossPlatform.h"

#ifdef API_WIN32API

#include <Windows.h>

#include "../Type.h"
#include "../Thread/Thread.h"

namespace MAPIL
{
	class WinAPIThread : public Thread
	{
	private:
		HANDLE			m_Handle;
		DWORD			m_ID;
	public:
		// Constructor.
		WinAPIThread();
		// Destructor.
		virtual ~WinAPIThread();
		// Create.
		MapilVoid Create();
		// Thread function.
		virtual MapilInt32 ThreadFunc();
	};
}

#endif	// API_WIN32API

#endif
