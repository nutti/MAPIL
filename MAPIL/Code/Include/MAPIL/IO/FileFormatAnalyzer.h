/**
*	@file	FileFormatAnalyzer.h
*	@brief	
*	@date	2011.8.13 (Sat) 11:32
*/

#ifndef INCLUDED_MAPIL_FILEFORMATANALYZER_H
#define INCLUDED_MAPIL_FILEFORMATANALYZER_H

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "File.h"

#include <fstream>

namespace MAPIL
{
	enum FileFormat
	{
		FILE_FORMAT_UNKNOWN = 0,
		FILE_FORMAT_BMP		= 1,
		FILE_FORMAT_WAV		= 11,
		FILE_FORMAT_X		= 22,
		FILE_FORMAT_MQO		= 23,
	};

	class FileFormatAnalyzer : public MapilObject
	{
	private:
		std::basic_fstream < MapilChar >		m_FIn;
		FileFormat								m_Fmt;
		
		MapilChar GetNextChar();
		MapilChar* GetNextStr( MapilInt32 len );
	public:
		FileFormatAnalyzer();
		~FileFormatAnalyzer();
		MapilVoid Open( const MapilChar* pFileName, FileOpenMode mode = FILE_OPEN_READ_MODE );
		MapilVoid Analyze();
		FileFormat GetFileFmt() const;
		MapilVoid Close();
	};
}

#endif