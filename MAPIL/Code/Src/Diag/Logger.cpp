/**
*	@file	Logger.cpp
*	@brief	
*	@date	2013.2.2(Sat) 09:07
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Diag/Logger.h"
#include "../../Include/MAPIL/Util/CPU.h"

namespace MAPIL
{
	Logger::Logger( const std::basic_string < MapilTChar >& fileName )
	{
		m_Stream.open( fileName, std::ios::out );
		m_HasTermSig = false;
	}

	Logger::~Logger()
	{
		while( !m_LogQueue.empty() ){
			m_Stream << m_LogQueue.front().c_str() << std::endl;
			m_LogQueue.pop();
		}

		m_Stream.close();
	}

	MapilInt32 Logger::ThreadFunc()
	{
		while( !m_HasTermSig ){
			m_Mutex.Lock();
			if( !m_LogQueue.empty() ){
				m_Stream << m_LogQueue.front().c_str() << std::endl;
				m_LogQueue.pop();
			}
			m_Mutex.Unlock();
			Idle();
		}

		return 0;
	}

	MapilVoid Logger::Write( const std::basic_string < MapilTChar >& itemName, const std::basic_string < MapilTChar >& log )
	{
		std::basic_ostringstream < MapilTChar > oss;

		oss << TSTR( "[" ) << itemName << TSTR( "] " ) << log;

		m_Mutex.Lock();
		m_LogQueue.push( oss.str() );
		m_Mutex.Unlock();
	}
	
	MapilVoid Logger::Terminate()
	{
		m_HasTermSig = true;
	}
}
