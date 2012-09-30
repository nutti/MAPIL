/**
*	@file	PNGFile.cpp
*	@brief	
*	@date	2011.8.14 (Sun) 15:28
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include <iostream>

#include "../../Include/MAPIL/IO/PNGFile.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Util/Memory.hpp"


#if defined ( MAKE_MODE_DEBUG )
#pragma comment ( lib, "libpngd.lib" )
#pragma comment ( lib, "zlibd.lib" )
#elif defined ( MAKE_MODE_RELEASE )
#pragma comment ( lib, "libpng.lib" )
#pragma comment ( lib, "zlib.lib" )
#endif

#if defined ( OS_WIN_32BIT )
#pragma warning ( disable : 4996 )
#endif

namespace MAPIL
{
	PNGFile::PNGFile() :	ImageFile(),
							m_OpenMode( FILE_OPEN_NONE_MODE ),
							m_Height( 0 ),
							m_Width( 0 ),
							m_Depth( 0 ),
							m_ColType( 0 ),
							m_InterlaceType( 0 ),
							m_pData( NULL ),
							m_DataSize( 0 )
	{
	}

	PNGFile::~PNGFile()
	{
		Close();
		m_Width = 0;
		m_Height = 0;
		m_Depth = 0;
		m_ColType = 0;
		m_InterlaceType = 0;
		SafeDeleteArray( m_pData );
		m_DataSize = 0;
	}

	// Open file.
	MapilVoid PNGFile::Open( const MapilChar* pFileName, FileOpenMode mode )
	{
		if( mode == FILE_OPEN_READ_MODE ){
			if( !( m_SP = ::png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL ) ) ){
				return;
			}
			m_IP = ::png_create_info_struct( m_SP );
			m_pFile = fopen( pFileName, "rb" );
			if( !m_pFile ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "PNGFile" ),
										TSTR( "Open" ),
										TSTR( "Failed to open file." ),
										-1 );
			}
			::png_init_io( m_SP, m_pFile );
		}
	}

	// Close file.
	MapilVoid PNGFile::Close()
	{
		m_OpenMode = FILE_OPEN_NONE_MODE;
		::png_destroy_read_struct( &m_SP, &m_IP, NULL );
		fclose( m_pFile );
	}

	// Load.
	MapilVoid PNGFile::Load()
	{
		Assert(	m_OpenMode == FILE_OPEN_READ_MODE,
				TSTR( "Mapil" ),
				TSTR( "PNGFile" ),
				TSTR( "Load" ),
				TSTR( "Open mode isn't read mode" ),
				-1 );

		::png_read_info( m_SP, m_IP );
		::png_get_IHDR(	m_SP,
						m_IP,
						reinterpret_cast < png_uint_32* > ( &m_Width ),
						reinterpret_cast < png_uint_32* > ( &m_Height ),
						&m_Depth,
						&m_ColType,
						&m_InterlaceType,
						NULL,
						NULL );
		MapilInt32 rowByte = ::png_get_rowbytes( m_SP, m_IP );
		m_DataSize = m_Height * rowByte;
		m_Channel = rowByte / m_Width;		// ñ{ìñÇÕÅAm_IPÇ©ÇÁéÊìæÇµÇΩÇ¢Ç™Ç»Ç∫Ç©Ç≈Ç´Ç»Ç¢ÅB
		m_pData = new MapilUChar[ m_DataSize ];
		MapilUChar** ppRecv = new MapilUChar*[ m_Height ];
		for( MapilUInt32 i = 0; i < m_Height; ++i ){
			ppRecv[ i ] = &m_pData[ i * rowByte ];
		}
		::png_read_image( m_SP, ppRecv );
		::png_read_end( m_SP, m_IP );
		SafeDeleteArray( ppRecv );
	}

	// Get width.
	MapilUInt32 PNGFile::GetWidth() const
	{
		return m_Width;
	}

	// Get height.
	MapilUInt32 PNGFile::GetHeight() const
	{
		return m_Height;
	}

	// Get data size.
	MapilUInt32 PNGFile::GetDataSize() const
	{
		return m_DataSize;
	}

	// Copy.
	MapilVoid PNGFile::Copy( MapilUChar* pOut ) const
	{
		for( MapilUInt32 i = 0; i < m_DataSize; ++i ){
			pOut[ i ] = m_pData[ i ];
		}
	}

	// Get channel.
	MapilInt32 PNGFile::GetChannel() const
	{
		return m_Channel;
	}
}