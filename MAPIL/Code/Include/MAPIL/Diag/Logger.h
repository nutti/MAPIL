/**
*	@file	Loagger.h
*	@brief	
*	@date	2013.2.2(Sat) 09:07
*/

#ifndef INCLUDED_MAPIL_MAPIL_LOGGER_H
#define INCLUDED_MAPIL_MAPIL_LOGGER_H

#include "../CrossPlatform.h"

#include <string>
#include <sstream>
#include <queue>
#include <fstream>

#include "../Util/MapilObject.h"
#include "../Thread/WinAPIThread.h"
#include "../Thread/WinAPIMutex.h"

namespace MAPIL
{
	class Logger : public WinAPIThread
	{
	private:
		std::queue < std::basic_string < MapilTChar > >			m_LogQueue;
		WinAPIMutex							m_Mutex;
		std::basic_ofstream < MapilTChar >	m_Stream;
		MapilBool							m_HasTermSig;
	public:
		Logger( const std::basic_string < MapilTChar >& fileName );
		~Logger();
		MapilInt32 ThreadFunc();
		MapilVoid Write( const std::basic_string < MapilTChar >& itemName, const std::basic_string < MapilTChar >& log );
		MapilVoid Terminate();
	};
}

#endif
