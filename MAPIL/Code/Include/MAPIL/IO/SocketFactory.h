/**
*	@file	SocketFactory.h
*	@brief	
*	@date	2011.06.07(Tue) 10:40
*/

#ifndef INCLUDED_MAPIL_SOCKET_FACTORY_H
#define INCLUDED_MAPIL_SOCKET_FACTORY_H

#include "../Type.h"
#include "../Util/MapilObject.h"

namespace MAPIL
{
	class TCPClient;
	class TCPServer;
	class UDPClient;
	class UDPServer;

	class SocketFactory : public MapilObject
	{
	public:
		SocketFactory();
		~SocketFactory();
		virtual TCPClient* CreateTCPClient() = 0;
		virtual TCPServer* CreateTCPServer() = 0;
		virtual UDPClient* CreateUDPClient() = 0;
		virtual UDPServer* CreateUDPServer() = 0;
	};

	class LinuxSocketFactory : public SocketFactory
	{
	public:
		LinuxSocketFactory();
		~LinuxSocketFactory();
		TCPClient* CreateTCPClient();
		TCPServer* CreateTCPServer();
		UDPClient* CreateUDPClient();
		UDPServer* CreateUDPServer();
	};
}

#endif
