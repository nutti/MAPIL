/**
*	@file	ISocketFactory.cpp
*	@brief	
*	@date	2011.6.9(Thu) 21:48
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include <iostream>

#include "../../Include/MAPIL/IO/ISocketFactory.h"
#include "../../Include/MAPIL/IO/SocketFactory.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

namespace MAPIL
{
	ISocketFactory::ISocketFactory() : MapilObject(), m_pFactory( NULL )
	{
	}
	
	ISocketFactory::~ISocketFactory()
	{
		SafeDelete( m_pFactory );
	}
	
	MapilVoid ISocketFactory::Init( MapilInt32 type )
	{
		switch( type ){
			case 1:
				m_pFactory = new LinuxSocketFactory();
				break;
			default:
				break;
		}
	}
	
	ITCPClient ISocketFactory::CreateITCPClient()
	{
		ITCPClient client( m_pFactory->CreateTCPClient() );
		
		return client;
	}
	
	ITCPServer ISocketFactory::CreateITCPServer()
	{
		ITCPServer server( m_pFactory->CreateTCPServer() );
		
		return server;
	}
}
