/**
*	@file	LinuxSocket.cpp
*	@brief	
*	@date	2011.6.7(Tue) 18:29
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef OS_LINUX_32BIT

#include "LinuxSocket.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"

#include <iostream>

namespace MAPIL
{
	LinuxTCPClient::LinuxTCPClient() : TCPClient(), m_Port( 0 )
	{
		ZeroObject( &m_DstAddr, sizeof( m_DstAddr ) );
	}

	LinuxTCPClient::~LinuxTCPClient()
	{
		ZeroObject( &m_DstAddr, sizeof( m_DstAddr ) );
		m_DstSocket = 0;
		m_Port = 0;
	}
	
	// Initialize.
	MapilVoid LinuxTCPClient::Init()
	{
	
	}
	
	// Connect to destination host.
	MapilVoid LinuxTCPClient::Connect(	const MapilInt32 port,
											const MapilChar* dstHost )
	{
		// Create socket of destination host.
		m_DstSocket = socket( AF_INET, SOCK_STREAM, 0 );
	//	if( m_DstSocket == INVALID_SOCKET ){
	//		throw MapilException(	TSTR( "Mapil" ),
	//									TSTR( "LinuxTCPClient" ),
	//									TSTR( "CreateSocket." ),
	//									TSTR( "Failed to create socket of destination host." ),
	//									-1 );
	//	}
		
		// Set SOCKADDR_IN structure.
		m_DstAddr.sin_port = htons( port );
		m_DstAddr.sin_family = AF_INET;
		m_DstAddr.sin_addr.s_addr = inet_addr( dstHost );

		// If dstHost isn't binary value.
//		if( m_DstAddr.sin_addr.s_addr == 0xffffffff ){
//			hostent* pHost;
//			pHost = gethostbyname( dstHost );
//			if( !pHost ){
//				if( WSAGetLastError() == WSAHOST_NOT_FOUND ){
//					throw Diagnostics::NuttiLibException(	TSTR( "Nutti::Lib::WinSockAPI" ),
//															TSTR( "WS2Client" ),
//															TSTR( "Connect" ),
//															TSTR( "The host wasn't found." ),
//															-1 );
//				}
//			}
//			unsigned int** ppAddr = reinterpret_cast < unsigned int** > ( pHost->h_addr_list );
			// The gethostbyname function may return several IP address.
//			while( *ppAddr != NULL ){
//				m_DstAddr.sin_addr.s_addr = *( *ppAddr );
				// Connect to destination host.
//				if( !connect( m_DstSocket, reinterpret_cast < sockaddr* > ( &m_DstAddr ), sizeof( m_DstAddr ) ) ){
//					break;
//				}
//				ppAddr++;
//			}
			// If failed to connect.
//			if( *ppAddr == NULL ){
//				throw MapilException(	TSTR( "Mapil" ),
//											TSTR( "LinuxTCPClient" ),
//											TSTR( "Connect" ),
//											TSTR( "Failed to connect." ),
//											-2 );
//			}
//		}
//		else{
			// Connect to destination host.
//			if( connect( m_DstSocket, reinterpret_cast < sockaddr* >( &m_DstAddr ), sizeof( m_DstAddr ) ) ){
//				throw MapilException(	TSTR( "Mapil" ),
//											TSTR( "LinuxTCPClient" ),
//											TSTR( "Connect" ),
//											TSTR( "Failed to connect." ),
//											-3 );
//			}
//		}
		connect( m_DstSocket, reinterpret_cast < sockaddr* >( &m_DstAddr ), sizeof( m_DstAddr ) );
	}
	
	// Close socket.
	MapilVoid LinuxTCPClient::Close()
	{
	}
	
	// Send packet.
	MapilInt32 LinuxTCPClient::Send( const MapilChar* pSendData, MapilInt32 dataSize )
	{
		MapilInt32 numSend;

		// Send packet.
		numSend = send( m_DstSocket, pSendData, dataSize, 0 );
		if( numSend < 0 ){
			return -1;
		}

		return 0;
	}
	
	//Receive packet
	MapilInt32 LinuxTCPClient::Receive(	MapilChar* pReceiveData,
												MapilInt32 dataSize,
												MapilInt32* pSize )
	{
		MapilInt32 numReceive;

		//Receive packet
		numReceive = recv( m_DstSocket, pReceiveData, dataSize, 0 );
		if( numReceive < 0 ){
			pReceiveData = NULL;
			//closesocket( m_DstSocket );
			return -1;
		}
		else{
			*pSize = numReceive;
		}

		return 0;
	}

	LinuxTCPServer::LinuxTCPServer() :	TCPServer(),
											m_Port( 0 ),
											m_SrcSocket( 0 ),
											m_DstSocket( 0 )
	{
		ZeroObject( &m_SrcAddr, sizeof( m_SrcAddr ) );
		ZeroObject( &m_DstAddr, sizeof( m_DstAddr ) );
	}

	LinuxTCPServer::~LinuxTCPServer()
	{
		ZeroObject( &m_SrcAddr, sizeof( m_SrcAddr ) );
		ZeroObject( &m_DstAddr, sizeof( m_DstAddr ) );
		m_SrcSocket = 0;
		m_DstSocket = 0;
		m_Port = 0;
	}
	
	// Initialize.
	MapilVoid LinuxTCPServer::Init()
	{
	}
	
	// Close destination socket.
	MapilVoid LinuxTCPServer::Close()
	{
		close( m_DstSocket );
	}
	
	// Wait for request of TCP client.
	MapilVoid LinuxTCPServer::Listen( MapilInt32 port )
	{
		// Create socket of source host.
		m_SrcSocket = socket( AF_INET, SOCK_STREAM, 0 );
	//	if( m_SrcSocket == INVALID_SOCKET ){
	//		throw MapilException(	TSTR( "Mapil" ),
	//									TSTR( "LinuxTCPServer" ),
	//									TSTR( "Listen" ),
	//									TSTR( "Failed to create socket of source host." ),
	//									-1 );
	//	}

		// Set SOCKADDR_IN structure.
		m_SrcAddr.sin_port				= htons( port );
		m_SrcAddr.sin_family				= AF_INET;
		m_SrcAddr.sin_addr.s_addr		= htonl( INADDR_ANY );

		// Bind of socket.
//		if( bind( m_SrcSocket, reinterpret_cast < sockaddr* > ( &m_SrcAddr ), sizeof( m_SrcAddr ) ) ){
//			throw MapilException(	TSTR( "Mapil" ),
//										TSTR( "LinuxTCPServer" ),
//										TSTR( "Listen" ),
//										TSTR( "Failed to bind." ),
//										-2 );
//		}
		bind( m_SrcSocket, reinterpret_cast < sockaddr* > ( &m_SrcAddr ), sizeof( m_SrcAddr ) );

		// Permit connection.
//		if( listen( m_SrcSocket, 5 ) ){
//			throw MapilException(	TSTR( "Mapil" ),
//										TSTR( "LinuxTCPServer" ),
//										TSTR( "Listen" ),
//										TSTR( "Failed to permit connection." ),
//										-3 );
//		}
		listen( m_SrcSocket, 5 );
	}
	
	// Accept connection.
	MapilVoid LinuxTCPServer::Accept()
	{
		// Accept connection.
		socklen_t dstAddrSize = sizeof( m_DstAddr );
		m_DstSocket = accept( m_SrcSocket, reinterpret_cast < sockaddr* > ( &m_DstAddr ), &dstAddrSize );
	//	if( m_DstSocket == INVALID_SOCKET ){
	//		throw MapilException(	TSTR( "Mapil" ),
	//									TSTR( "LinuxTCPServer" ),
	//									TSTR( "Accept" ),
	//									TSTR( "Failed to create socket of destination host." ),
	//									-1 );
	//	}
	}
	
	// Send packet.
	MapilVoid LinuxTCPServer::Send( const MapilChar* pSendData, MapilInt32 dataSize )
	{
		// Send packet.
		send( m_DstSocket, pSendData, dataSize, 0 );
	}
	
	// Receive packet.
	MapilVoid LinuxTCPServer::Receive( MapilChar* pReceiveData, MapilInt32 dataSize )
	{
		// Receive packet.
		recv( m_DstSocket, pReceiveData, dataSize, 0 );
	}

	LinuxUDPClient::LinuxUDPClient() : UDPClient()
	{
	}

	LinuxUDPClient::~LinuxUDPClient()
	{
	}

	LinuxUDPServer::LinuxUDPServer() : UDPServer()
	{
	}


	LinuxUDPServer::~LinuxUDPServer()
	{
	}
}

#endif // OS_LINUX_32
