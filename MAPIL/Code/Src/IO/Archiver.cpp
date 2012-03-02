/**
*	@file	Archiver.cpp
*	@brief	Implementation of Archiver.h.
*	@date	2012.2.4 (Sat) 9:07
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include <fstream>

#include "../../Include/MAPIL/IO/Archiver.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Util/String.h"
#include "../../Include/MAPIL/Math/Transformation.hpp"

#if defined ( OS_WIN_32BIT )
#pragma warning ( disable : 4996 )
#endif

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{

	Archiver::Archiver() :	m_ArchiveName(),
							m_FileName(),
							m_FileSize(),
							m_FilePos(),
							m_FileTotal( 0 )
	{
	}

	Archiver::~Archiver()
	{
		Close();
	}

	MapilInt32 Archiver::LoadInt( std::basic_ifstream < MapilChar >* pStream )
	{
		MapilChar str[ 4 ];
		pStream->read( str, sizeof( MapilChar ) * 4 );

		return TransformCharIntoInt32( str, BYTE_ORDER_LITTLE );
	}

	MapilVoid Archiver::SaveInt( std::basic_ofstream < MapilChar >* pStream, MapilInt32 data )
	{
		MapilChar str[ 4 ];
		TransformInt32IntoChar( data, str, BYTE_ORDER_LITTLE );
		pStream->write( str, sizeof( MapilChar ) * 4 );
	}

	MapilInt32 Archiver::GetDataSize( std::basic_ifstream < MapilChar >* pStream )
	{
		MapilInt32 size = 0;
		MapilInt32 begin = 0;
		MapilInt32 end = 0;
		pStream->seekg( 0, std::ios::beg );
		begin = static_cast < MapilInt32 > ( pStream->tellg() );
		pStream->seekg( 0, std::ios::end );
		end = static_cast < MapilInt32 > ( pStream->tellg() );
		size = end - begin;
		pStream->seekg( 0, std::ios::beg );

		return size;
	}

	MapilVoid Archiver::Open( const MapilChar* pFileName, FileOpenMode mode )
	{
		m_ArchiveName = pFileName;

		if( mode == FILE_OPEN_READ_MODE ){
			std::basic_ifstream < MapilChar > fIn( pFileName, std::ios::binary | std::ios::in );

			// Get position where information of files is existed, and move to this position.
			fIn.seekg( -4, std::ios::end );
			MapilUInt32 infoPos = LoadInt( &fIn );
			fIn.seekg( infoPos, std::ios::beg );

			// Get number of file.
			m_FileTotal = LoadInt( &fIn );

			// Get information of files.
			for( MapilInt32 i = 0; i < m_FileTotal; ++i ){
				// Get position of file.
				m_FilePos.push_back( LoadInt( &fIn ) );
				// Get length of file name.
				MapilInt32 fileNameLen = LoadInt( &fIn );
				// Get file name.
				MapilChar* pFileNameBuf = NULL;
				pFileNameBuf = new MapilChar [ fileNameLen + 1 ];
				fIn.read( pFileNameBuf,  fileNameLen );
				pFileNameBuf[ fileNameLen ] = '\0';
				m_FileName.push_back( pFileNameBuf );
				// Get file size
				m_FileSize.push_back( LoadInt( &fIn ) );
			}

			fIn.close();
		}
	}

	MapilVoid Archiver::Load( const MapilChar* pFileName, MapilChar* pData )
	{
		std::basic_string < MapilChar > search = pFileName;

		for( MapilInt32 i = 0; i < m_FileTotal; ++i ){
			if( m_FileName[ i ] == search ){
				std::basic_ifstream < MapilChar > fIn( m_ArchiveName.c_str(), std::ifstream::binary );
				fIn.seekg( m_FilePos[ i ], std::ifstream::beg );
				fIn.read( pData, m_FileSize[ i ] );
				fIn.close();
				break;
			}
		}
	}

	MapilVoid Archiver::Load(	const MapilChar* pFileName,
								MapilChar* pData,
								MapilInt32 offset,
								MapilInt32 size,
								MapilInt32* pReadSize )
	{
		std::basic_string < MapilChar > search = pFileName;

		for( MapilInt32 i = 0; i < m_FileTotal; ++i ){
			if( m_FileName[ i ] == search ){
				std::basic_ifstream < MapilChar > fIn( m_ArchiveName.c_str(), std::ifstream::binary );
				fIn.seekg( m_FilePos[ i ] + offset, std::ifstream::beg );
				if( offset + size > m_FileSize[ i ] ){
					MapilInt32 surplus = m_FileSize[ i ] - ( offset + size );
					*pReadSize = static_cast < MapilInt32 > ( fIn.read( pData, surplus ).gcount() );
					fIn.close();
					break;
				}
				else if( offset < 0 ){
					fIn.close();
					return;
				}
				*pReadSize = static_cast < MapilInt32 > ( fIn.read( pData, size ).gcount() );
				fIn.close();
				break;
			}
		}
	}

	MapilVoid Archiver::Save( const MapilChar* pFileName )
	{
		Open( pFileName, FILE_OPEN_WRITE_MODE );

		std::basic_ofstream < MapilChar > fOut( m_ArchiveName, std::ios::binary | std::ios::out );
		MapilInt32 offset = 0;

		for( MapilInt32 i = 0; i < m_FileTotal; ++i ){
			std::basic_ifstream < MapilChar > fIn( m_FileName[ i ], std::ios::binary | std::ios::in );
			m_FileSize.push_back( GetDataSize( &fIn ) );
			m_FilePos.push_back( offset );
			offset += m_FileSize[ i ];
			MapilChar* pData = new MapilChar [ m_FileSize[ i ] ];
			fIn.read( pData, m_FileSize[ i ] );
			// Copy data.
			fOut.write( pData, m_FileSize[ i ] );
			SafeDeleteArray( pData );
			fIn.close();
		}

		// Setup the file information.
		SaveInt( &fOut, m_FileTotal );
		for( MapilInt32 i = 0; i < m_FileTotal; ++i ){
			SaveInt( &fOut, m_FilePos[ i ] );
			SaveInt( &fOut, strlen( m_FileName[ i ] ) );
			fOut.write( m_FileName[ i ], strlen( m_FileName[ i ] ) );
			SaveInt( &fOut, m_FileSize[ i ] );
		}
		SaveInt( &fOut, offset );

		fOut.close();
	}

	MapilVoid Archiver::SetContents( const MapilChar* pFileName )
	{
		MapilInt32 strLen = strlen( pFileName );
		MapilChar* pStr = new MapilChar [ strLen + 1 ];
		strcpy( pStr, pFileName );
		m_FileName.push_back( pStr );
		++m_FileTotal;
	}

	MapilInt32 Archiver::GetContentsSize( const MapilChar* pFileName )
	{
		for( MapilInt32 i = 0; i < m_FileTotal; ++i ){
			if( !strcmp( m_FileName[ i ], pFileName ) ){
				return m_FileSize[ i ];
			}
		}

		return 0;
	}

	MapilVoid Archiver::Close()
	{
		for( MapilInt32 i = 0; i < m_FileTotal; ++i ){
			MapilChar* pStr = m_FileName[ i ];
			SafeDeleteArray( pStr );
		}
		m_FileName.clear();
		m_FilePos.clear();
		m_FileSize.clear();
		m_FileTotal = 0;
	}

}
