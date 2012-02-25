/**
*	@file	Signal.h
*	@brief	
*	@date	2011.6.17(Fri) 14:49
*/

#ifndef INCLUDED_MAPIL_SIGNAL_H
#define INCLUDED_MAPIL_SIGNAL_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"

namespace MAPIL
{
	class Signal : public MapilObject
	{
	public:
		Signal();
		virtual ~Signal();
	};
}

#endif
