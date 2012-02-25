/**
*	@file	i_socket.cpp
*	@brief	
*	@date	2011.6.9(Thu) 21:32
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/IO/ISocket.h"
#include "Socket.h"

#include <iostream>

namespace MAPIL
{
	ITCPClient::ITCPClient() : m_pClient()
	{
	}
	
	ITCPClient::ITCPClient( TCPClient* pClient ) : m_pClient( pClient )
	{
	}
	
	ITCPClient::ITCPClient( const ITCPClient& itp ) : m_pClient( itp.m_pClient )
	{
	}
	
	ITCPClient& ITCPClient::operator=( const ITCPClient& itp )
	{
		m_pClient = itp.m_pClient;

		return *this;
	}
	
	ITCPClient::~ITCPClient()
	{
	}
	
	// Initialize.
	MapilVoid ITCPClient::Init()
	{
		m_pClient->Init();
		
		std::cout << "hello" << std::endl;
	}
	
	// Connect to destination host.
	MapilVoid ITCPClient::Connect(	const MapilInt32 port,
										const MapilChar* dstHost )
	{
		m_pClient->Connect( port, dstHost );
		
		std::cout << "connect" << std::endl;
	}
	
	// Close socket.
	MapilVoid ITCPClient::Close()
	{
		m_pClient->Close();
	}
	
	// Send packet.
	MapilInt32 ITCPClient::Send( const MapilChar* pSendData, MapilInt32 dataSize )
	{
		return m_pClient->Send( pSendData, dataSize );
	}
	
	//Receive packet
	MapilInt32 ITCPClient::Receive(	MapilChar* pReceiveData,
										MapilInt32 dataSize,
										MapilInt32* pSize )
	{
		return m_pClient->Receive( pReceiveData, dataSize, pSize );
	}
	
	
	
	
	ITCPServer::ITCPServer() : m_pServer()
	{
	}
	
	ITCPServer::ITCPServer( TCPServer* pServer ) : m_pServer( pServer )
	{
	}
	
	ITCPServer::ITCPServer( const ITCPServer& its ) : m_pServer( its.m_pServer )
	{
	}
	
	ITCPServer& ITCPServer::operator=( const ITCPServer& its )
	{
		m_pServer = its.m_pServer;

		return *this;
	}
	
	ITCPServer::~ITCPServer()
	{
	}
	
	// Initialize.
	MapilVoid ITCPServer::Init()
	{
		m_pServer->Init();
	}
	
	// Close destination socket.
	MapilVoid ITCPServer::Close()
	{
		m_pServer->Close();
	}
	
	// Wait for request of TCP client.
	MapilVoid ITCPServer::Listen( MapilInt32 port )
	{
		m_pServer->Listen( port );
	}
	
	// Accept connection.
	MapilVoid ITCPServer::Accept()
	{
		m_pServer->Accept();
	}
	
	// Send packet.
	MapilVoid ITCPServer::Send( const MapilChar* pSendData, MapilInt32 dataSize )
	{
		m_pServer->Send( pSendData, dataSize );
	}
	
	// Receive packet.
	MapilVoid ITCPServer::Receive( MapilChar* pReceiveData, MapilInt32 dataSize )
	{
		m_pServer->Receive( pReceiveData, dataSize );
	}
	
}
