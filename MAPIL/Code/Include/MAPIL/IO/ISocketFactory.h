/**
*	@file	ISocketFactory.h
*	@brief	
*	@date	2011.6.9(Thu) 21:44
*/

#ifndef INCLUDED_MAPIL_IO_ISOCKETFACTORY_H
#define INCLUDED_MAPIL_IO_ISOCKETFACTORY_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "../IO/ISocket.h"
#include "../Type.h"

namespace MAPIL
{
	
	class SocketFactory;
	class ISocketFactory : public MapilObject
	{
	private:
		SocketFactory*		m_pFactory;
	public:
		ISocketFactory();
		~ISocketFactory();
		MapilVoid Init( MapilInt32 type );
		ITCPClient CreateITCPClient();
		ITCPServer CreateITCPServer();
	};
}

#endif
