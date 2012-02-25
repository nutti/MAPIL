/**
*	@file	socket.h
*	@brief	
*	@date	2011.6.9(Thu) 21:22
*/

#ifndef INCLUDED_MAPIL_IO_ISOCKET_H
#define INCLUDED_MAPIL_IO_ISOCKET_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "../Type.h"
#include "../Util/SharedPointer.hpp"

namespace MAPIL
{
	
	class TCPClient;
	class ITCPClient : public MapilObject
	{
	public:
		SharedPointer < TCPClient >		m_pClient;
	public:
		ITCPClient();
		ITCPClient( TCPClient* pClient );
		ITCPClient( const ITCPClient& itp );
		ITCPClient& operator=( const ITCPClient& itp );
		~ITCPClient();
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
	
	class TCPServer;
	class ITCPServer : public MapilObject
	{
	private:
		SharedPointer < TCPServer >		m_pServer;
	public:
		ITCPServer();
		ITCPServer( TCPServer* pServer );
		ITCPServer( const ITCPServer& its );
		ITCPServer& operator=( const ITCPServer& its );
		~ITCPServer();
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

}

#endif
