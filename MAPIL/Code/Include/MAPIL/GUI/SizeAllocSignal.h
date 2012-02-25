/**
*	@file	SizeAllocSignal.h
*	@brief	
*	@date	2011.6.17(Fri) 23:1
*/

#ifndef INCLUDED_MAPIL_SIZEALLOCSIGNAL_H
#define INCLUDED_MAPIL_SIZEALLOCSIGNAL_H

#include "../CrossPlatform.h"

#include "Signal.h"
#include "../Type.h"

namespace MAPIL
{
	class SizeAllocSignal : public Signal
	{
	public:
		SizeAllocSignal();
		virtual ~SizeAllocSignal();
		virtual MapilVoid HandleSizeAlloc() = 0;
	};
}

#endif
