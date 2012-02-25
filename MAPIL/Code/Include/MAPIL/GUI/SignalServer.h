/**
*	@file	SignalServer.h
*	@brief	
*	@date	2011.6.17(Fri) 16:16
*/

#ifndef INCLUDED_MAPIL_SIGNALSERVER_H
#define INCLUDED_MAPIL_SIGNALSERVER_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"

namespace MAPIL
{
	class SignalServer : public MapilObject
	{
	public:
		SignalServer();
		virtual ~SignalServer();
	};
}

#endif
