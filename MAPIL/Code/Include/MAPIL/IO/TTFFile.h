/**
*	@file	TTFFile.h
*	@brief	
*	@date	2011.8.7 (Sun) 11:23
*/

#ifndef INCLUDED_MAPIL_TTFFILE_H
#define INCLUDED_MAPIL_TTFFILE_H

#include "../CrossPlatform.h"

#include "FontFile.h"

#include <string>

namespace MAPIL
{

	class TTFFile : public FontFile
	{
	private:
		std::basic_string < MapilTChar >		m_FilePath;
	public:
		// Constructor.
		TTFFile();
		// Destructor.
		~TTFFile();
		// Open.
		MapilVoid Open( const MapilChar* pFileName, FileOpenMode mode );
		// Close.
		MapilVoid Close();
		// Load.
		MapilVoid Load( MapilTChar* pFilePath );
		// Destroy.
		MapilVoid Destroy();
	};
}

#endif
