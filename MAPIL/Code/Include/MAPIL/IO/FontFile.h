/**
*	@file	FontFile.h
*	@brief	
*	@date	2011.8.7 (Sun) 11:18
*/

#ifndef INCLUDED_MAPIL_FONTFILE_H
#define INCLUDED_MAPIL_FONTFILE_H

#include "../CrossPlatform.h"

#include "File.h"

namespace MAPIL
{

	class FontFile : public File
	{
	private:

	public:
		// Constructor.
		FontFile();
		// Destructor.
		virtual ~FontFile();
		// Load.
		virtual MapilVoid Load( MapilTChar* pFilePath ) = 0;
		// Destroy.
		virtual MapilVoid Destroy() = 0;
	};
}

#endif
