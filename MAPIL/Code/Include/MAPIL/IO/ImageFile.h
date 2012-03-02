/**
*	@file	ImageFile.h
*	@brief	
*	@date	2011.7.17 (Sun) 11:32
*/

#ifndef INCLUDED_MAPIL_IMAGEFILE_H
#define INCLUDED_MAPIL_IMAGEFILE_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "File.h"

namespace MAPIL
{

	class ImageFile : public MapilObject
	{
	private:

	public:
		// Constructor.
		ImageFile();
		// Destructor.
		virtual ~ImageFile();
	};
}

#endif
