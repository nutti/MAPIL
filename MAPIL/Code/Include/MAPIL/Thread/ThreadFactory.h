/**
*	@file	ThreadFactory.h
*	@brief	
*	@date	2011.6.10(Fri) 20:25
*/

#ifndef INCLUDED_MAPIL_THREADFACTORY_H
#define INCLUDED_MAPIL_THREADFACTORY_H

#include "../Util/MapilObject.h"

namespace MAPIL
{

	class Thread;

	class ThreadFactory : public MapilObject
	{
	public:
		ThreadFactory();
		virtual ~ThreadFactory();
		virtual Thread* CreateThread() = 0;
	};
	
	class POSIXThreadFactory : public ThreadFactory
	{
	public:
		POSIXThreadFactory();
		~POSIXThreadFactory();
		Thread* CreateThread();
	};
}

#endif
