/**
*	@file	ImageFile.h
*	@brief	
*	@date	2011.8.14 (Sun) 15:28
*/

#ifndef INCLUDED_MAPIL_PNGFILE_H
#define INCLUDED_MAPIL_PNGFILE_H

#include "../CrossPlatform.h"

#include "ImageFile.h"

#if defined ( LIB_LIBPNG )
#if defined ( LIB_ZLIB )
#include <png.h>
#endif
#endif


namespace MAPIL
{
	class PNGFile : public ImageFile
	{
	private:
		FileOpenMode			m_OpenMode;
		MapilUInt32				m_Width;
		MapilUInt32				m_Height;
		MapilInt32				m_Depth;
		MapilInt32				m_ColType;
		MapilInt32				m_InterlaceType;
		MapilUChar*				m_pData;
		MapilUInt32				m_DataSize;
		MapilInt32				m_Channel;
#if defined ( LIB_LIBPNG )
#if defined ( LIB_ZLIB )
		::png_structp			m_SP;
		::png_infop				m_IP;
		FILE*					m_pFile;
#endif
#endif
	public:
		PNGFile();
		~PNGFile();
		// Open file.
		MapilVoid Open( const MapilChar* pFileName, FileOpenMode mode );
		// Close file.
		MapilVoid Close();
		// Load.
		MapilVoid Load();
		// Get width.
		MapilUInt32 GetWidth() const;
		// Get height.
		MapilUInt32 GetHeight() const;
		// Get data size.
		MapilUInt32 GetDataSize() const;
		// Copy.
		MapilVoid Copy( MapilUChar* pOut ) const;
		// Get channel.
		MapilInt32 GetChannel() const;
	};
}

#endif