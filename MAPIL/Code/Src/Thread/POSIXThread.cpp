/**
*	@file	POSIXThread.cpp
*	@brief	
*	@date	2011.6.10(Fri) 20:11
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_POSIX

#include <stdlib.h>

#include "../../Include/MAPIL/Thread/POSIXThread.h"

namespace MAPIL
{

	// Constructor.
	POSIXThread::POSIXThread() : m_ID( 0 )
	{
	}

	// Destructor.
	POSIXThread::~POSIXThread()
	{
		m_ID = 0;
	}

	// Create.
	MapilVoid POSIXThread::Create()
	{
		if( pthread_create( &m_ID, NULL, ThreadControlFunc, this ) ){
			exit( 1 );
		}
	}

	// Thread function.
	MapilInt32 POSIXThread::ThreadFunc()
	{
		return 0;
	}
	
}

#endif	// API_POSIX