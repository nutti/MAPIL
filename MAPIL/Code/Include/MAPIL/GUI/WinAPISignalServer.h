/**
*	@file	WinAPISignalServer.h
*	@brief	
*	@date	2011.7.10(Sun) 10:44
*/

#ifndef INCLUDED_MAPIL_WINAPISIGNALSERVER_H
#define INCLUDED_MAPIL_WINAPISIGNALSERVER_H

#include "../CrossPlatform.h"

#ifdef API_WIN32API

#include <Windows.h>

#include "SignalServer.h"
#include "../Type.h"

namespace MAPIL
{
	class WinAPISignalServer : public SignalServer
	{
	public:
		WinAPISignalServer();
		virtual ~WinAPISignalServer();
		static LRESULT CALLBACK MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	};
}

#endif	// API_WIN32API

#endif