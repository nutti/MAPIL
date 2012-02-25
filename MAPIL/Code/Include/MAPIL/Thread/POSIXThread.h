/**
*	@file	POSIXThread.h
*	@brief	
*	@date	2011.6.10(Fri) 20:7
*/

#ifndef INCLUDED_MAPIL_POSIXTHREAD_H
#define INCLUDED_MAPIL_POSIXTHREAD_H

#include "../CrossPlatform.h"

#ifdef API_POSIX

#include <pthread.h>


#include "Thread.h"

namespace MAPIL
{
	class POSIXThread : public Thread
	{
	private:
		pthread_t			m_ID;			// Thread ID.
	public:
		// Constructor.
		POSIXThread();
		// Destructor.
		virtual ~POSIXThread();
		// Create.
		MapilVoid Create();
		// Thread function.
		virtual MapilInt32 ThreadFunc();
	};
}

#endif	// API_POSIX

#endif
