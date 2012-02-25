/**
*	@file	SocketFactory.cpp
*	@brief	
*	@date	2011.06.07(Tue) 10:46
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/IO/SocketFactory.h"

#ifdef OS_LINUX_32BIT
#include "LinuxSocket.h"
#endif

namespace MAPIL
{
	SocketFactory::SocketFactory() : MapilObject()
	{
	}
	
	SocketFactory::~SocketFactory()
	{
	}

#ifdef OS_LINUX_32BIT

	LinuxSocketFactory::LinuxSocketFactory() : SocketFactory()
	{
	}

	LinuxSocketFactory::~LinuxSocketFactory()
	{
	}

	TCPClient* LinuxSocketFactory::CreateTCPClient()
	{
		LinuxTCPClient* pClient = new LinuxTCPClient();
		
		return pClient;
	}

	TCPServer* LinuxSocketFactory::CreateTCPServer()
	{
		LinuxTCPServer* pServer = new LinuxTCPServer();
		
		return pServer;
	}

	UDPClient* LinuxSocketFactory::CreateUDPClient()
	{
		LinuxUDPClient* pClient = new LinuxUDPClient();
		
		return pClient;
	}

	UDPServer* LinuxSocketFactory::CreateUDPServer()
	{
		LinuxUDPServer* pServer = new LinuxUDPServer();
		
		return pServer;
	}

#endif	// OS_LINUX_32BIT
}
