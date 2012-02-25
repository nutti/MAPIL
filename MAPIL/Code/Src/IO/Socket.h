/**
*	@file	Socket.h
*	@brief	
*	@date	2011.06.07(Tue) 10:05
*/

#ifndef INCLUDED_MAPIL_SOCKET_H
#define INCLUDED_MAPIL_SOCKET_H

#include "IO.h"
#include "../../Include/MAPIL/Type.h"

namespace MAPIL
{
	class TCPClient : public IO
	{
	private:
		// Prohibit copy constructor.
		TCPClient( const TCPClient& tc );
		// Prohibit copy with substitution.
		TCPClient& operator=( const TCPClient& tc );
	public:
		// Constructor.
		TCPClient();
		// Destructor.
		virtual ~TCPClient();
		// Initialize.
		virtual MapilVoid Init() = 0;
		// Connect to destination host.
		virtual MapilVoid Connect(	const MapilInt32 port,
										const MapilChar* dstHost ) = 0;
		// Close socket.
		virtual MapilVoid Close() = 0;
		// Send packet.
		virtual MapilInt32 Send( const MapilChar* pSendData, MapilInt32 dataSize ) = 0;
		//Receive packet
		virtual MapilInt32 Receive(	MapilChar* pReceiveData,
										MapilInt32 dataSize,
										MapilInt32* pSize ) = 0;
	};

	class TCPServer : public IO
	{
	private:
		// Prohibit copy constructor.
		TCPServer( const TCPServer& ts );
		// Prohibit copy with substitution.
		TCPServer& operator=( const TCPServer& ts );
	public:
		// Constructor.
		TCPServer();
		// Destructor.
		virtual ~TCPServer();
		// Initialize.
		virtual MapilVoid Init() = 0;
		// Close destination socket.
		virtual MapilVoid Close() = 0;
		// Wait for request of TCP client.
		virtual MapilVoid Listen( MapilInt32 port ) = 0;
		// Accept connection.
		virtual MapilVoid Accept() = 0;
		// Send packet.
		virtual MapilVoid Send( const MapilChar* pSendData, MapilInt32 dataSize ) = 0;
		// Receive packet.
		virtual MapilVoid Receive( MapilChar* pReceiveData, MapilInt32 dataSize ) = 0;
	};

	class UDPClient : public IO
	{
	private:
		// Prohibit copy constructor.
		UDPClient( const UDPClient& uc );
		// Prohibit copy with substitution.
		UDPClient& operator=( const UDPClient& uc );
	public:
		// Constructor.
		UDPClient();
		// Destructor.
		virtual ~UDPClient();
	};

	class UDPServer : public IO
	{
	private:
		// Prohibit copy constructor.
		UDPServer( const UDPServer& us );
		// Prohibit copy with substitution.
		UDPServer& operator=( const UDPServer& us );
	public:
		// Constructor.
		UDPServer();
		// Destructor.
		virtual ~UDPServer();
	};
}

#endif
