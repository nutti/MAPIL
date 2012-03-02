/**
*	@file	PointSprite.cpp
*	@brief	
*	@date	2011.8.13 (Sat) 11:34
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/IO/FileFormatAnalyzer.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Util/Memory.hpp"


namespace MAPIL
{
	FileFormatAnalyzer::FileFormatAnalyzer() :	MapilObject(),
												m_FIn(),
												m_Fmt( FILE_FORMAT_UNKNOWN )
	{
	}

	FileFormatAnalyzer::~FileFormatAnalyzer()
	{
		m_Fmt = FILE_FORMAT_UNKNOWN;
		Close();
	}

	MapilVoid FileFormatAnalyzer::Open( const MapilChar* pFileName, FileOpenMode mode )
	{
		Assert(	mode == FILE_OPEN_READ_MODE,
				TSTR( "Mapil" ),
				TSTR( "FileFormatAnalyzer" ),
				TSTR( "Open" ),
				TSTR( "FileOpenMode isn't correct." ),
				-1 );
		
		m_FIn.open( pFileName, std::ios::binary | std::ios::in );
	}

	MapilVoid FileFormatAnalyzer::Analyze()
	{
		MapilChar str[ 200 ];
		m_FIn.read( str, sizeof( str ) );

		if( !strncmp( str, "RIFF", 4 ) ){
			if( !strncmp( str + 8, "WAVE", 4 ) ){
				m_Fmt = FILE_FORMAT_WAV;
			}
		}
		else if( !strncmp( str, "BM", 2 ) ){
			m_Fmt = FILE_FORMAT_BMP;
		}
		else if( !strncmp( str, "Metasequoia Document", 20 ) ){
			m_Fmt = FILE_FORMAT_MQO;
		}
		else if( !strncmp( str, "xof", 3 ) ){
			m_Fmt = FILE_FORMAT_X;
		}
		else{
			m_Fmt = FILE_FORMAT_UNKNOWN;
		}
	}

	FileFormat FileFormatAnalyzer::GetFileFmt() const
	{
		return m_Fmt;
	}

	MapilVoid FileFormatAnalyzer::Close()
	{
		m_FIn.close();
	}
}