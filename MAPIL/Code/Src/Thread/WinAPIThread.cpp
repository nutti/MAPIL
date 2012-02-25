/**
*	@file	WinAPIThread.cpp
*	@brief	
*	@date	2011.7.20 (Wed) 7:32
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_WIN32API

#include "../../Include/MAPIL/Thread/WinAPIThread.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"

namespace MAPIL
{
	// Constructor.
	WinAPIThread::WinAPIThread() : Thread(), m_Handle( NULL ), m_ID( 0 )
	{
	}

	// Destructor.
	WinAPIThread::~WinAPIThread()
	{
		if( m_Handle ){
			WaitForSingleObject( m_Handle, INFINITE );
			CloseHandle( m_Handle );
			m_Handle = NULL;
		}
	}
	
	// Create.
	MapilVoid WinAPIThread::Create()
	{
		m_Handle = CreateThread( NULL, 0, reinterpret_cast < LPTHREAD_START_ROUTINE > ( ThreadControlFunc ), this, 0, &m_ID );

		if( !m_Handle ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "Thread" ),
									TSTR( "Create" ),
									TSTR( "Creation of thread failed." ),
									-1 );
		}
	}

	// Thread function.
	MapilInt32 WinAPIThread::ThreadFunc()
	{
		return 0;
	}

}

#endif	// API_WIN32API
