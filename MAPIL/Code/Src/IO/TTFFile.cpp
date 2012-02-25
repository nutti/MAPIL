/**
*	@file	TTFFile.cpp
*	@brief	
*	@date	2011.8.7 (Sun) 11:25
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/IO/TTFFile.h"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Diag/MapilException.h"

#ifdef API_WIN32API
#include <Windows.h>
#endif

namespace MAPIL
{
	// Constructor.
	TTFFile::TTFFile() :	FontFile(),
							m_FilePath()
	{
	}

	// Destructor.
	TTFFile::~TTFFile()
	{
		Destroy();
	}

	// Open.
	MapilVoid TTFFile::Open( const MapilChar* pFileName, FileOpenMode mode )
	{
	}

	// Close.
	MapilVoid TTFFile::Close()
	{
	}

	// Load.
	MapilVoid TTFFile::Load( MapilTChar* pFilePath )
	{
#ifdef OS_WIN_32BIT
		m_FilePath = pFilePath;
		if( AddFontResourceEx( m_FilePath.c_str(), FR_PRIVATE, NULL ) <= 0 ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "TTFFile" ),
									TSTR( "Load" ),
									TSTR( "Failed to load the font file." ),
									-1 );
		}
#endif
	}

	// Destroy.
	MapilVoid TTFFile::Destroy()
	{
#ifdef OS_WIN_32BIT
		if( !RemoveFontResourceEx( m_FilePath.c_str(), FR_PRIVATE, NULL ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "Font" ),
									TSTR( "Delete" ),
									TSTR( "Failed to delete the font." ),
									-1 );
		}
#endif
	}
}
