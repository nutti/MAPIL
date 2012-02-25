/**
*	@file	LinuxSocket.h
*	@brief	
*	@date	2011.06.07(Tue) 10:30
*/

#ifndef INCLUDED_MAPIL_LINUX_SOCKET_H
#define INCLUDED_MAPIL_LINUX_SOCKET_H

#ifdef OS_LINUX_32BIT

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "Socket.h"

namespace MAPIL
{
	class LinuxTCPClient : public TCPClient
	{
	private:
		sockaddr_in	m_DstAddr;		// sockaddr_in structure of destination host.
		MapilInt32		m_Port;		// Port number.
		MapilInt32		m_DstSocket;	// Socket of destination host.
	public:
		LinuxTCPClient();
		~LinuxTCPClient();
		// Initialize.
		MapilVoid Init();
		// Connect to destination host.
		MapilVoid Connect(	const MapilInt32 port,
								const MapilChar* dstHost );
		// Close socket.
		MapilVoid Close();
		// Send packet.
		MapilInt32 Send( const MapilChar* pSendData, MapilInt32 dataSize );
		//Receive packet
		MapilInt32 Receive(	MapilChar* pReceiveData,
								MapilInt32 dataSize,
								MapilInt32* pSize );
	};



	class LinuxTCPServer : public TCPServer
	{
	private:
		sockaddr_in		m_SrcAddr;		// sockaddr_in structure of source host.
		sockaddr_in		m_DstAddr;		// sockaddr_in structure of destination host.
		MapilInt32			m_Port;		// Port number.
		MapilInt32			m_SrcSocket;	// Socket of source host.
		MapilInt32			m_DstSocket;	// Socket of destination host.
	public:
		LinuxTCPServer();
		~LinuxTCPServer();
		// Initialize.
		MapilVoid Init();
		// Close destination socket.
		MapilVoid Close();
		// Wait for request of TCP client.
		MapilVoid Listen( MapilInt32 port );
		// Accept connection.
		MapilVoid Accept();
		// Send packet.
		MapilVoid Send( const MapilChar* pSendData, MapilInt32 dataSize );
		// Receive packet.
		MapilVoid Receive( MapilChar* pReceiveData, MapilInt32 dataSize );
	};



	class LinuxUDPClient : public UDPClient
	{
	private:
		sockaddr_in	m_DstAddr;		// sockaddr_in structure of destination host.
		MapilInt32		m_Port;		// Port number.
		MapilInt32		m_DstSocket;	// Socket of destination host.
	public:
		LinuxUDPClient();
		~LinuxUDPClient();
		// Initialize.
		MapilVoid Init();
		// Connect to destination host.
		MapilVoid Connect(	const MapilInt32 port,
								const MapilChar* dstHost );
		// Close socket.
		MapilVoid Close();
		// Send packet.
		MapilInt32 Send( const MapilChar* pSendData, MapilInt32 dataSize );
	};



	class LinuxUDPServer : public UDPServer
	{
	private:
		sockaddr_in		m_SrcAddr;		// sockaddr_in structure of source host.
		sockaddr_in		m_DstAddr;		// sockaddr_in structure of destination host.
		MapilInt32			m_Port;		// Port number.
		MapilInt32			m_SrcSocket;	// Socket of source host.
		MapilInt32			m_DstSocket;	// Socket of destination host.
	public:
		LinuxUDPServer();
		~LinuxUDPServer();
		// Initialize.
		MapilVoid Init();
		// Close destination socket.
		MapilVoid Close();
		// Connect to source host.
		MapilVoid Bind( MapilInt32 port );
		// Send packet.
		MapilVoid Send( const MapilChar* pSendData, MapilInt32 dataSize );
		// Receive packet.
		MapilVoid Receive( MapilChar* pReceiveData, MapilInt32 dataSize );
	};


}

#endif	// OS_LINUX_32BIT

#endif