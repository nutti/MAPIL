/**
*	@file	WAVFile.cpp
*	@brief	
*	@date	2011.7.3(Sun) 11:46
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/IO/WAVFile.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/TChar.h"

#include <iostream>

namespace MAPIL
{
	// Constructor.
	WAVFile::WAVFile() :	m_Header(),
							m_pWavData( NULL ),
							m_pInfo( NULL ),
							m_InfoSize( 0 ),
							m_Stream(),
							m_OpenMode( FILE_OPEN_NONE_MODE ),
							m_FileSize( 0 )
	{
		ZeroObject( &m_Header, sizeof( m_Header ) );
	}

	// Destrcutor.
	WAVFile::~WAVFile()
	{
		m_Stream.close();
		ZeroObject( &m_Header, sizeof( m_Header ) );
		SafeDeleteArray( m_pWavData );
		SafeDeleteArray( m_pInfo );
		m_InfoSize = 0;
		m_OpenMode = FILE_OPEN_NONE_MODE;
		m_FileSize = 0;
	}

	// Copy constructor.
	WAVFile::WAVFile( const WAVFile& wf )
	{
		m_Header = wf.m_Header;
		m_pWavData = new MapilChar[ m_Header.m_FileSize - 44 ];
		for( MapilInt32 i = 0; i < m_Header.m_FileSize - 44; i++ ){
			m_pWavData[ i ] = wf.m_pWavData[ i ];
		}
		m_InfoSize = wf.m_InfoSize;
		m_pInfo = new MapilChar[ m_InfoSize ];
		for( MapilInt32 i = 0; i < m_InfoSize; i++ ){
			m_pInfo[ i ] = wf.m_pInfo[ i ];
		}
		m_OpenMode = FILE_OPEN_NONE_MODE;
		m_FileSize = wf.m_FileSize;
	}

	// Substitute. ( Overload of = operator. )
	WAVFile& WAVFile::operator=( const WAVFile& wf )
	{
		m_Header = wf.m_Header;
		m_pWavData = new MapilChar[ m_Header.m_FileSize - 44 ];
		for( MapilInt32 i = 0; i < m_Header.m_FileSize - 44; i++ ){
			m_pWavData[ i ] = wf.m_pWavData[ i ];
		}
		m_InfoSize = wf.m_InfoSize;
		m_pInfo = new MapilChar[ m_InfoSize ];
		for( MapilInt32 i = 0; i < m_InfoSize; i++ ){
			m_pInfo[ i ] = wf.m_pInfo[ i ];
		}
		m_OpenMode = FILE_OPEN_NONE_MODE;

		m_FileSize = wf.m_FileSize;

		return *this;
	}

	// Open.
	MapilVoid WAVFile::Open(	const MapilChar* pFileName,
								FileOpenMode mode )
	{
		m_Stream.close();
		if( mode == FILE_OPEN_READ_MODE ){
			// Open file.
			m_Stream.open( pFileName, std::ios::binary | std::ios::in );
			if( !m_Stream ){
				throw MapilException(	TSTR( "Mapil" ),
											TSTR( "WAVFile" ),
											TSTR( "Open" ),
											TSTR( "Failed to open file." ),
											-1 );
			}
			m_OpenMode = FILE_OPEN_READ_MODE;
		}
		else if( mode == FILE_OPEN_WRITE_MODE ){
			// Open file.
			m_Stream.open( pFileName, std::ios::binary | std::ios::out );
			if( !m_Stream ){
				throw MapilException(	TSTR( "Mapil" ),
											TSTR( "WAVFile" ),
											TSTR( "Open" ),
											TSTR( "Failed to open file." ),
											-2 );
			}
			m_OpenMode = FILE_OPEN_WRITE_MODE;
		}

		MapilInt32 begin = 0;
		MapilInt32 end = 0;
		m_Stream.seekg( 0, std::ios::beg );
		begin = static_cast < MapilInt32 > ( m_Stream.tellg() );
		m_Stream.seekg( 0, std::ios::end );
		end = static_cast < MapilInt32 > ( m_Stream.tellg() );
		m_FileSize = end - begin;
		m_Stream.seekg( 0, std::ios::beg );
	}

	// Close.
	MapilVoid WAVFile::Close()
	{
		m_Stream.close();
		m_OpenMode = FILE_OPEN_NONE_MODE;
		m_FileSize = 0;
	}

	// Get size.
	MapilInt32 WAVFile::GetSize()
	{
		return m_FileSize;
	}

	// Load header.
	MapilVoid WAVFile::LoadHeader()
	{
		Assert(	m_OpenMode == FILE_OPEN_READ_MODE,
					TSTR( "Mapil" ),
					TSTR( "WAVFile" ),
					TSTR( "LoadHeader" ),
					TSTR( "Open mode isn't read mode." ),
					-1 );

		// Get WAVFileHeader information.
		m_Stream.read( m_Header.m_RIFFHeader, sizeof( m_Header.m_RIFFHeader ) );
		if( m_Header.m_RIFFHeader[ 0 ] != 'R' || m_Header.m_RIFFHeader[ 1 ] != 'I' || m_Header.m_RIFFHeader[ 2 ] != 'F' || m_Header.m_RIFFHeader[ 3 ] != 'F' ){
			throw MapilException(	TSTR( "Mapil" ),
										TSTR( "WAVFile" ),
										TSTR( "LoadHeader" ),
										TSTR( "This isn't wave file. ( \"RIFF\" isn't been found. )" ),
										-1 );
		}
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_Header.m_FileSize ), sizeof( m_Header.m_FileSize ) );
		m_Stream.read( m_Header.m_WAVEHeader, sizeof( m_Header.m_WAVEHeader ) );
		if( m_Header.m_WAVEHeader[ 0 ] != 'W' || m_Header.m_WAVEHeader[ 1 ] != 'A' || m_Header.m_WAVEHeader[ 2 ] != 'V' || m_Header.m_WAVEHeader[ 3 ] != 'E' ){
			throw MapilException(	TSTR( "Mapil" ),
										TSTR( "WAVFile" ),
										TSTR( "LoadHeader" ),
										TSTR( "This isn't wave file. ( \"WAVE\" isn't been found. )" ),
										-2 );
		}
		m_Stream.read( m_Header.m_FMTHeader, sizeof( m_Header.m_FMTHeader ) );
		if( m_Header.m_FMTHeader[ 0 ] != 'f' || m_Header.m_FMTHeader[ 1 ] != 'm' || m_Header.m_FMTHeader[ 2 ] != 't' ){
			throw MapilException(	TSTR( "Mapil" ),
										TSTR( "WAVFile" ),
										TSTR( "LoadHeader" ),
										TSTR( "This isn't wave file. ( \"fmt\" isn't been found. )" ),
										-3 );
		}
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_Header.m_FMTSize ), sizeof( m_Header.m_FMTSize ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_Header.m_FmtID ), sizeof( m_Header.m_FmtID ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_Header.m_NumChannel ), sizeof( m_Header.m_NumChannel ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_Header.m_SampleRate ), sizeof( m_Header.m_SampleRate ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_Header.m_BytePerSec ), sizeof( m_Header.m_BytePerSec ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_Header.m_BlockSize ), sizeof( m_Header.m_BlockSize ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_Header.m_BitPerSample ), sizeof( m_Header.m_BitPerSample ) );
		m_Stream.read( m_Header.m_DATAHeader, sizeof( m_Header.m_DATAHeader ) );
		if( m_Header.m_DATAHeader[ 0 ] != 'd' || m_Header.m_DATAHeader[ 1 ] != 'a' || m_Header.m_DATAHeader[ 2 ] != 't' || m_Header.m_DATAHeader[ 3 ] != 'a' ){
			throw MapilException(	TSTR( "Mapil" ),
										TSTR( "WAVFile" ),
										TSTR( "LoadHeader" ),
										TSTR( "This isn't wave file. ( \"data\" isn't been found. )" ),
										-4 );
		}
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_Header.m_DataSize ), sizeof( m_Header.m_DataSize ) );
	}

	// Load infomation data.
	MapilVoid WAVFile::LoadInfo()
	{
		Assert(	m_OpenMode == FILE_OPEN_READ_MODE,
					TSTR( "Mapil" ),
					TSTR( "WAVFile" ),
					TSTR( "LoadInfo" ),
					TSTR( "Open mode isn't read mode." ),
					-1 );

		// Get LIST position.
		MapilInt32 infoPos = 0;
		MapilBool doesDetect = MapilFalse;
		m_Stream.seekg( 0, std::ios::end );
		infoPos = static_cast < MapilInt32 > ( m_Stream.tellg() );
		--infoPos;
		while( 1 ){
			m_Stream.seekg( infoPos, std::ios::beg );
			MapilChar c = 0;
			m_Stream.read( &c, sizeof( c ) );
			if( c == 'T' ){
				m_Stream.seekg( -4, std::ios::cur );
				MapilChar str[ 5 ];
				m_Stream.read( str, sizeof( str ) - 1 );
				str[ 4 ] = '\0';
				if( !strcmp( str, "LIST" ) ){
					infoPos -= 4;
					break;
				}
			}
			--infoPos;
			if( infoPos <= 0 ){
				break;
			}
		}

		// Get information data.
		if( infoPos > 0 ){
			m_InfoSize = m_FileSize - infoPos - 1;
		}
		else{
			m_InfoSize = 0;
		}
		if( m_InfoSize > 0 ){
			m_pInfo = new MapilChar[ m_InfoSize + 1 ];
			memset( m_pInfo, 'a', m_InfoSize );
			m_Stream.seekg( m_Header.m_FileSize + 8, std::ios::beg );
			m_Stream.read( m_pInfo, sizeof( MapilChar ) * ( m_InfoSize ) );
			m_pInfo[ m_InfoSize ] = 0;
		}
		m_Stream.clear();
	}
	
	// Load. ( 1 )
	MapilVoid WAVFile::Load()
	{
		Assert(	m_OpenMode == FILE_OPEN_READ_MODE,
					TSTR( "Mapil" ),
					TSTR( "WAVFile" ),
					TSTR( "Load" ),
					TSTR( "Open mode isn't read mode." ),
					-1 );

		// Get WAVFileHeader information.
		LoadHeader();

		// Get wave data.
		m_pWavData = new MapilChar[ m_Header.m_FileSize - 44 ];
		m_Stream.read( m_pWavData, sizeof( MapilChar ) * ( m_Header.m_FileSize - 44 ) );

		// Get information data.
		LoadInfo();
	}

	// Load. ( 2 )
	MapilVoid WAVFile::Load(	MapilInt32 begPos,
											MapilInt32 endPos,
											MapilChar* pOutData,
											MapilInt32* pReadSize,
											MapilInt32 readSize )
	{
		Assert(	m_OpenMode == FILE_OPEN_READ_MODE,
					TSTR( "Mapil" ),
					TSTR( "WAVFile" ),
					TSTR( "Load" ),
					TSTR( "Open mode isn't read mode." ),
					-1 );

		MapilInt32 size = endPos - begPos;
		size = ( size >= readSize ? readSize : size );
		m_Stream.seekg( begPos, std::ios::beg );
		*pReadSize = static_cast < MapilInt32 > ( m_Stream.read( pOutData, sizeof( MapilChar ) * size ).gcount() );
	}

	// Save header.
	MapilVoid WAVFile::SaveHeader()
	{
		Assert(	m_OpenMode == FILE_OPEN_WRITE_MODE,
					TSTR( "Mapil" ),
					TSTR( "WAVFile" ),
					TSTR( "SaveHeader" ),
					TSTR( "Open mode isn't write mode." ),
					-1 );

		// Write WAVFileHeader information.
		m_Stream.write( m_Header.m_RIFFHeader, sizeof( m_Header.m_RIFFHeader ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_Header.m_FileSize ), sizeof( m_Header.m_FileSize ) );
		m_Stream.write( m_Header.m_WAVEHeader, sizeof( m_Header.m_WAVEHeader ) );
		m_Stream.write( m_Header.m_FMTHeader, sizeof( m_Header.m_FMTHeader ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_Header.m_FMTSize ), sizeof( m_Header.m_FMTSize ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_Header.m_FmtID ), sizeof( m_Header.m_FmtID ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_Header.m_NumChannel ), sizeof( m_Header.m_NumChannel ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_Header.m_SampleRate ), sizeof( m_Header.m_SampleRate ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_Header.m_BytePerSec ), sizeof( m_Header.m_BytePerSec ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_Header.m_BlockSize ), sizeof( m_Header.m_BlockSize ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_Header.m_BitPerSample ), sizeof( m_Header.m_BitPerSample ) );
		m_Stream.write( m_Header.m_DATAHeader, sizeof( m_Header.m_DATAHeader ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_Header.m_DataSize ), sizeof( m_Header.m_DataSize ) );
	}

	// Save. ( 1 )
	MapilVoid WAVFile::Save()
	{
		Assert(	m_OpenMode == FILE_OPEN_WRITE_MODE,
					TSTR( "Mapil" ),
					TSTR( "WAVFile" ),
					TSTR( "Save" ),
					TSTR( "Open mode isn't write mode." ),
					-1 );

		// Write WAVFileHeader information.
		SaveHeader();

		// Save wave data.
		m_Stream.write( m_pWavData, sizeof( MapilChar ) * ( m_Header.m_FileSize - 44 ) );

		// Save information data.
		m_Stream.write( m_pInfo, sizeof( MapilChar ) * ( m_InfoSize ) );
	}

	// Save. ( 2 )
	MapilVoid WAVFile::Save(	MapilChar* pOutData,
											MapilInt32 writeSize )
	{
		m_Stream.write( pOutData, writeSize );
	}

	// Get position of information data.
	MapilInt32 WAVFile::GetInfoPos() const
	{
		return m_FileSize - m_InfoSize;
	}

	// Get position of data.
	MapilInt32 WAVFile::GetDataPos() const
	{
		return 44;
	}

	// Get wave file header.
	WAVFileHeader WAVFile::GetWAVFileHeader() const
	{
		return m_Header;
	}

	// Set wave file header.
	MapilVoid WAVFile::SetWAVFileHeader( const WAVFileHeader& header )
	{
		m_Header = header;
	}

	// Get file size.
	MapilInt32 WAVFile::GetFileSize() const
	{
		return m_Header.m_FileSize;
	}

	// Get format ID.
	MapilShortInt32 WAVFile::GetFmtID() const
	{
		return m_Header.m_FmtID;
	}

	// Get number of channel.
	MapilShortInt32 WAVFile::GetNumChannel() const
	{
		return m_Header.m_NumChannel;
	}

	// Get sampling rate.
	MapilInt32 WAVFile::GetSampleRate() const
	{
		return m_Header.m_SampleRate;
	}

	// Get data speed.
	MapilInt32 WAVFile::GetDataSpeed() const
	{
		return m_Header.m_BytePerSec;
	}

	// Get block size.
	MapilShortInt32 WAVFile::GetBlockSize() const
	{
		return m_Header.m_BlockSize;
	}

	// Get bit per sample.
	MapilShortInt32 WAVFile::GetBitPerSample() const
	{
		return m_Header.m_BitPerSample;
	}

	static MapilVoid LoadDataFromMemory( const MapilChar** pIn, MapilVoid* pOut, MapilInt32 size )
	{
		memcpy( pOut, *pIn, size );
		*pIn += size;
	}

	MapilVoid GetWAVFileHeader( const MapilChar* pData, WAVFileHeader* pHeader )
	{
		const MapilChar** p = &pData;

		// Get WAVFileHeader information.
		LoadDataFromMemory( p, pHeader->m_RIFFHeader, sizeof( pHeader->m_RIFFHeader ) );

		if(	pHeader->m_RIFFHeader[ 0 ] != 'R' ||
			pHeader->m_RIFFHeader[ 1 ] != 'I' ||
			pHeader->m_RIFFHeader[ 2 ] != 'F' ||
			pHeader->m_RIFFHeader[ 3 ] != 'F' ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "" ),
									TSTR( "GetWAVFileHeader" ),
									TSTR( "This isn't wave data. ( \"RIFF\" isn't been found. )" ),
									-1 );
		}
	
		LoadDataFromMemory( p, &pHeader->m_FileSize, sizeof( pHeader->m_FileSize ) );
		LoadDataFromMemory( p, pHeader->m_WAVEHeader, sizeof( pHeader->m_WAVEHeader ) );
		if( pHeader->m_WAVEHeader[ 0 ] != 'W' ||
			pHeader->m_WAVEHeader[ 1 ] != 'A' ||
			pHeader->m_WAVEHeader[ 2 ] != 'V' ||
			pHeader->m_WAVEHeader[ 3 ] != 'E' ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "" ),
									TSTR( "GetWAVFileHeader" ),
									TSTR( "This isn't wave data. ( \"WAVE\" isn't been found. )" ),
									-2 );
		}

		LoadDataFromMemory( p, pHeader->m_FMTHeader, sizeof( pHeader->m_FMTHeader ) );
		if(	pHeader->m_FMTHeader[ 0 ] != 'f' ||
			pHeader->m_FMTHeader[ 1 ] != 'm' ||
			pHeader->m_FMTHeader[ 2 ] != 't' ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "" ),
									TSTR( "GetWAVFileHeader" ),
									TSTR( "This isn't wave data. ( \"fmt\" isn't been found. )" ),
									-3 );
		}
		LoadDataFromMemory( p, &pHeader->m_FMTSize, sizeof( pHeader->m_FMTSize ) );
		LoadDataFromMemory( p, &pHeader->m_FmtID, sizeof( pHeader->m_FmtID ) );
		LoadDataFromMemory( p, &pHeader->m_NumChannel, sizeof( pHeader->m_NumChannel ) );
		LoadDataFromMemory( p, &pHeader->m_SampleRate, sizeof( pHeader->m_SampleRate ) );
		LoadDataFromMemory( p, &pHeader->m_BytePerSec, sizeof( pHeader->m_BytePerSec ) );
		LoadDataFromMemory( p, &pHeader->m_BlockSize, sizeof( pHeader->m_BlockSize ) );
		LoadDataFromMemory( p, &pHeader->m_BitPerSample, sizeof( pHeader->m_BitPerSample ) );
		LoadDataFromMemory( p, pHeader->m_DATAHeader, sizeof( pHeader->m_DATAHeader ) );
		if(	pHeader->m_DATAHeader[ 0 ] != 'd' ||
			pHeader->m_DATAHeader[ 1 ] != 'a' ||
			pHeader->m_DATAHeader[ 2 ] != 't' ||
			pHeader->m_DATAHeader[ 3 ] != 'a' ){
			throw MapilException(	TSTR( "Mapil" ),
										TSTR( "" ),
										TSTR( "GetWAVFileHeader" ),
										TSTR( "This isn't wave data. ( \"data\" isn't been found. )" ),
										-4 );
		}
		LoadDataFromMemory( p, &pHeader->m_DataSize, sizeof( pHeader->m_DataSize ) );
	}

	MapilInt32 GetWAVFileInfo( const MapilChar* pData, MapilInt32 size )
	{
		const MapilChar* p = pData + size;

		while( p >= pData ){
			if( *p == 'T' ){
				if( !::strncmp( p - 3, "LIST", 4 ) ){
					return p - pData - 3;
				}
			}
			--p;
		}

		return -1;
	}

}
