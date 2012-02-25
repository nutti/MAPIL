/**
*	@file	ThreadFactory.cpp
*	@brief	
*	@date	2011.6.10(Fri) 20:33
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_POSIX

#include "../../Include/MAPIL/Thread/ThreadFactory.h"
#include "../../Include/MAPIL/Thread/POSIXThread.h"

namespace MAPIL
{
	ThreadFactory::ThreadFactory() : MapilObject()
	{
	}
	
	ThreadFactory::~ThreadFactory()
	{
	}
	
	POSIXThreadFactory::POSIXThreadFactory() : ThreadFactory()
	{
	}
	
	POSIXThreadFactory::~POSIXThreadFactory()
	{
	}
	
	Thread* POSIXThreadFactory::CreateThread()
	{
		POSIXThread* pThread = new POSIXThread();
		
		return pThread;
	}
}

#endif	// API_POSIX