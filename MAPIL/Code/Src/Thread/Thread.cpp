/**
*	@file	Thread.cpp
*	@brief	
*	@date	2011.6.10(Fri) 20:3
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Thread/Thread.h"

namespace MAPIL
{
	// Constructor.
	Thread::Thread() : MapilObject()
	{
	}

	// Destructor.
	Thread::~Thread()
	{
	}
	
	// Function which controls thread.
	MapilVoid* Thread::ThreadControlFunc( MapilVoid* p )
	{
		static_cast < Thread* > ( p )->ThreadFunc();
		
		return NULL;
	}
}
