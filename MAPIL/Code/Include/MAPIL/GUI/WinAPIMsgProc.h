/**
*	@file	WinAPIMsgProc.h
*	@brief	
*	@date	2011.7.10(Sun) 15:39
*/

#ifndef INCLUDED_MAPIL_WINAPIMSGPROC_H
#define INCLUDED_MAPIL_WINAPIMSGPROC_H

#include "../CrossPlatform.h"

#ifdef API_WIN32API

#include <Windows.h>

#include "../Util/MapilObject.h"
#include "../Type.h"

namespace MAPIL
{
	class ExposeSignal;
	class KeyboardSignal;
	class WinAPIMsgProc : public MapilObject
	{
	protected:
		HWND				m_HWnd;
		ExposeSignal*		m_pExposeSig;
		KeyboardSignal*		m_pKeyboardSig;
	public:
		WinAPIMsgProc();
		virtual ~WinAPIMsgProc();
		MapilVoid SetPtr( HWND hWnd );
		virtual LRESULT WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
		HWND GetHWnd();
		//MapilVoid Connect( ExposeSignal* pSig );
	};
}

#endif	// API_WIN32API

#endif