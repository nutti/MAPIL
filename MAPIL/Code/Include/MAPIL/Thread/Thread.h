/**
*	@file	Thread.h
*	@brief	
*	@date	2011.6.10(Fri) 19:58
*/

#ifndef INCLUDED_MAPIL_THREAD_H
#define INCLUDED_MAPIL_THREAD_H

#include "../Type.h"
#include "../Util/MapilObject.h"

namespace MAPIL
{
	class Thread : public MapilObject
	{
	protected:
		// Function which controls thread.
		static MapilVoid* ThreadControlFunc( MapilVoid* p );
	public:
		// Constructor.
		Thread();
		// Destructor.
		virtual ~Thread();
		// Create.
		virtual MapilVoid Create() = 0;
		// Thread function.
		virtual MapilInt32 ThreadFunc() = 0;
	};
}

#endif
