/**
*	@file	Console.cpp
*	@brief	
*	@date	2011.7.23 (Sat) 10:59
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_WIN32API )

#include "../../Include/MAPIL/IO/Console.h"

namespace MAPIL
{
	// Constructor.
	Console::Console() : MapilObject(), m_pFile( NULL )
	{
	}

	// Destructor.
	Console::~Console()
	{
		Close();
	}

	// Open.
	MapilVoid Console::Open()
	{
		AllocConsole();
		freopen_s( &m_pFile, "CON", "w", stdout );
	}

	// Close.
	MapilVoid Console::Close()
	{
		if( m_pFile ){
			fclose( m_pFile );
		}
		FreeConsole();
	}
}

#endif	// API_WIN32API