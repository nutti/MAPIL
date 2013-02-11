/**
*	@file	WinAPIMutex.cpp
*	@brief	
*	@date	2013.2.2 (Sat) 9:18
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_WIN32API )


#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Thread/WinAPIMutex.h"

namespace MAPIL
{
	WinAPIMutex::WinAPIMutex()
	{
		MapilTChar tstr[ 1024 ];
		_stprintf( tstr, TSTR( "%d" ), m_MutexTotal );

		m_Handle = ::CreateMutex( NULL, FALSE, tstr );
		++m_MutexTotal;
	}

	WinAPIMutex::~WinAPIMutex()
	{
		::CloseHandle( m_Handle );
	}

	MapilVoid WinAPIMutex::Lock()
	{
		::WaitForSingleObject( m_Handle, INFINITE );
	}

	MapilVoid WinAPIMutex::Unlock()
	{
		::ReleaseMutex( m_Handle );
	}

	MapilInt32 WinAPIMutex::m_MutexTotal = 0;

}

#endif	// API_WIN32API
