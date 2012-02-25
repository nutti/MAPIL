/**
*	@file	BMPFile.cpp
*	@brief	
*	@date	2011.7.17 (Sun) 11:39
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include <iostream>

#include "../../Include/MAPIL/IO/BMPFile.h"

#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/TChar.h"

namespace MAPIL
{
	//Constructor
	BMPFile::BMPFile() : m_Stream(), m_pColorBuf( NULL ), m_OpenMode( FILE_OPEN_NONE_MODE )
	{
		ZeroObject( &m_FileHeader, sizeof( m_FileHeader ) );
		ZeroObject( &m_InfoHeader, sizeof( m_InfoHeader ) );
	}

	//Destructor
	BMPFile::~BMPFile()
	{
		m_Stream.close();
		ZeroObject( &m_FileHeader, sizeof( m_FileHeader ) );
		ZeroObject( &m_InfoHeader, sizeof( m_InfoHeader ) );
		SafeDeleteArray( m_pColorBuf );
		m_OpenMode = FILE_OPEN_NONE_MODE;
	}

	// Copy constructor.
	BMPFile::BMPFile( const BMPFile& bf )
	{
		m_FileHeader = bf.m_FileHeader;
		m_InfoHeader = bf.m_InfoHeader;
		m_pColorBuf = new ColorRGB < MapilUChar > [ m_InfoHeader.m_Width * m_InfoHeader.m_Height ];
		for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				m_pColorBuf[ i * m_InfoHeader.m_Width + j ] = bf.m_pColorBuf[ i * m_InfoHeader.m_Width + j ];
			}
		}
		m_OpenMode = FILE_OPEN_NONE_MODE;
	}

	// Substitute. ( Overload of = operator. )
	BMPFile& BMPFile::operator=( const BMPFile& bf )
	{
		m_FileHeader = bf.m_FileHeader;
		m_InfoHeader = bf.m_InfoHeader;
		m_pColorBuf = new ColorRGB < MapilUChar > [ m_InfoHeader.m_Width * m_InfoHeader.m_Height ];
		for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				m_pColorBuf[ i * m_InfoHeader.m_Width + j ] = bf.m_pColorBuf[ i * m_InfoHeader.m_Width + j ];
			}
		}
		m_OpenMode = FILE_OPEN_NONE_MODE;

		return *this;
	}

	// Index operator. ( Overload of [] operator. )
	ColorRGB < MapilUChar >& BMPFile::operator[]( MapilInt32 index )
	{
		Assert(	index >= 0 && index < m_InfoHeader.m_Width * m_InfoHeader.m_Height,
				TSTR( "Mapil" ),
				TSTR( "BMPFile" ),
				TSTR( "operator[]" ),
				TSTR( "Substituted index is out of range." ),
				-1 );

		return m_pColorBuf[ index ];
	}

	// Brackets operator. ( Overload of [] operator. )
	ColorRGB < MapilUChar >& BMPFile::operator()( MapilInt32 x, MapilInt32 y )
	{
		Assert(	x >= 0 && x < m_InfoHeader.m_Width && y >= 0 && y < m_InfoHeader.m_Height,
				TSTR( "Mapil" ),
				TSTR( "BMPFile" ),
				TSTR( "operator()" ),
				TSTR( "Substituted value is out of range." ),
				-1 );

		return m_pColorBuf[ x + y * m_InfoHeader.m_Width ];
	}

	// Open file.
	MapilVoid BMPFile::Open( const MapilChar* pFileName, FileOpenMode mode )
	{
		m_Stream.close();
		if( mode == FILE_OPEN_READ_MODE ){
			// Open file.
			m_Stream.open( pFileName, std::ios::binary | std::ios::in );
			if( !m_Stream ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "BMPFile" ),
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
										TSTR( "BMPFile" ),
										TSTR( "Open" ),
										TSTR( "Failed to open file." ),
										-2 );
			}
			m_OpenMode = FILE_OPEN_WRITE_MODE;
		}
	}

	// Close file.
	MapilVoid BMPFile::Close()
	{
	}

	// Load bitmap file whose bit/pixel is 32.
	MapilVoid BMPFile::Load32BitBMP()
	{
		for( MapilInt32 i = m_InfoHeader.m_Height - 1; i >= 0; i-- ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				m_Stream.read( reinterpret_cast < MapilChar* > ( &m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_B ), sizeof( MapilUChar ) );
				m_Stream.read( reinterpret_cast < MapilChar* > ( &m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_G ), sizeof( MapilUChar ) );
				m_Stream.read( reinterpret_cast < MapilChar* > ( &m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_R ), sizeof( MapilUChar ) );
				MapilChar reserved = 0;
				m_Stream.read( &reserved, sizeof( MapilChar ) );
			}
		}
	}

	// Load bitmap file whose bit/pixel is 24.
	MapilVoid BMPFile::Load24BitBMP()
	{
		MapilUChar discardData;

		// If width isn't multiples of 4, bitmap file sets value 0 to be multiples of 4.
		MapilInt32 surplus;
		surplus = 4 - ( ( m_InfoHeader.m_Width * ( m_InfoHeader.m_NumBitPerPixel / 8 ) ) % 4 );
		// The pixel data begin from left-bottom on bitmap file.
		for( MapilInt32 i = m_InfoHeader.m_Height - 1; i >= 0; i-- ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				m_Stream.read( reinterpret_cast < MapilChar* > ( &m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_B ), sizeof( MapilUChar ) );
				m_Stream.read( reinterpret_cast < MapilChar* > ( &m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_G ), sizeof( MapilUChar ) );
				m_Stream.read( reinterpret_cast < MapilChar* > ( &m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_R ), sizeof( MapilUChar ) );
			}
			if( surplus != 4 ){
				for( MapilInt32 j = 0; j < surplus; j++ ){
					m_Stream.read( reinterpret_cast < MapilChar* > ( &discardData ), sizeof( MapilUChar ) );
				}
			}
		}
	}

	// Load bitmap file whose bit/pixel is 8.
	MapilVoid BMPFile::Load8BitBMP()
	{
		MapilInt32 numPalette = 1 << m_InfoHeader.m_NumBitPerPixel;		// Number of palette.
		ColorRGB < MapilUChar >* pPalette = NULL;		// Palette data.
		MapilUChar* pPaletteNum = NULL;							// Palette number data.

		// Get palette information.
		pPalette = new ColorRGB < MapilUChar > [ numPalette ];
		for( MapilInt32 i = 0; i < numPalette; i++ ){
			MapilChar discard;
			m_Stream.read( reinterpret_cast < MapilChar* > ( &pPalette[ i ].m_B ), sizeof( MapilUChar ) );
			m_Stream.read( reinterpret_cast < MapilChar* > ( &pPalette[ i ].m_G ), sizeof( MapilUChar ) );
			m_Stream.read( reinterpret_cast < MapilChar* > ( &pPalette[ i ].m_R ), sizeof( MapilUChar ) );
			m_Stream.read( reinterpret_cast < MapilChar* > ( &discard ), sizeof( MapilUChar ) );
		}

		for( MapilInt32 i = 0; i < numPalette; i++ ){
			std::cout << static_cast < int > ( pPalette[ i ].m_R ) << "," << static_cast < int > ( pPalette[ i ].m_G ) << "," << static_cast < int > ( pPalette[ i ].m_B ) << std::endl;
		}

		// Get palette number information.
		pPaletteNum = new MapilUChar[ m_InfoHeader.m_Width * m_InfoHeader.m_Height ];
		MapilUChar discardData = 0;
		// If width isn't multiples of 4, bitmap file sets value 0 to be multiples of 4.
		MapilInt32 surplus;
		surplus = 4 - ( ( m_InfoHeader.m_Width * ( m_InfoHeader.m_NumBitPerPixel / 8 ) ) % 4 );
		// The pixel data begin from left-bottom on bitmap file.
		for( MapilInt32 i = m_InfoHeader.m_Height - 1; i >= 0; i-- ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				m_Stream.read( reinterpret_cast < MapilChar* > ( &pPaletteNum[ i * m_InfoHeader.m_Width + j ] ), sizeof( MapilUChar ) );
			}
			if( surplus != 4 ){
				for( MapilInt32 j = 0; j < surplus; j++ ){
					m_Stream.read( reinterpret_cast < MapilChar* > ( &discardData ), sizeof( MapilUChar ) );
				}
			}
		}

		for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				std::cout << /*static_cast < int >*/ ( pPaletteNum[ i * m_InfoHeader.m_Width + j ] )/* << ","*/;
			}
			std::cout << std::endl;
		}

		// Convert palette number into pixel data.
		for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_R = pPalette[ pPaletteNum[ i * m_InfoHeader.m_Width + j ] ].m_R;
				m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_G = pPalette[ pPaletteNum[ i * m_InfoHeader.m_Width + j ] ].m_G;
				m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_B = pPalette[ pPaletteNum[ i * m_InfoHeader.m_Width + j ] ].m_B;
			}
		}

		SafeDeleteArray( pPalette );
		SafeDeleteArray( pPaletteNum );
	}

	// Load bitmap file whose bit/pixel is 4.
	MapilVoid BMPFile::Load4BitBMP()
	{
		MapilInt32 numPalette = 1 << m_InfoHeader.m_NumBitPerPixel;		// Number of palette.
		ColorRGB < MapilUChar >* pPalette = NULL;		// Palette data.
		MapilUChar* pPaletteNum = NULL;							// Palette number data.

		// Get palette information.
		pPalette = new ColorRGB < MapilUChar > [ numPalette ];
		for( MapilInt32 i = 0; i < numPalette; i++ ){
			MapilChar discard;
			m_Stream.read( reinterpret_cast < MapilChar* > ( &pPalette[ i ].m_B ), sizeof( MapilUChar ) );
			m_Stream.read( reinterpret_cast < MapilChar* > ( &pPalette[ i ].m_G ), sizeof( MapilUChar ) );
			m_Stream.read( reinterpret_cast < MapilChar* > ( &pPalette[ i ].m_R ), sizeof( MapilUChar ) );
			m_Stream.read( reinterpret_cast < MapilChar* > ( &discard ), sizeof( MapilUChar ) );
		}

		for( MapilInt32 i = 0; i < numPalette; i++ ){
			std::cout << static_cast < int > ( pPalette[ i ].m_R ) << "," << static_cast < int > ( pPalette[ i ].m_G ) << "," << static_cast < int > ( pPalette[ i ].m_B ) << std::endl;
		}

		// Get palette number information.
		pPaletteNum = new MapilUChar[ ( m_InfoHeader.m_Width + m_InfoHeader.m_Width % 2 ) * m_InfoHeader.m_Height ];

		MapilUChar discardData = 0;
		// If width isn't multiples of 4, bitmap file sets value 0 to be multiples of 4.
		MapilInt32 surplus;
		surplus = 4 - ( ( m_InfoHeader.m_Width / 2 ) ) % 4;
		for( MapilInt32 i = m_InfoHeader.m_Height - 1; i >= 0; i-- ){
			for( MapilInt32 j = 0; j < ( ( m_InfoHeader.m_Width + 1 ) / 2 ); j++ ){
				MapilUChar buf;
				m_Stream.read( reinterpret_cast < MapilChar* > ( &buf ), sizeof( MapilUChar ) );
				pPaletteNum[ i * m_InfoHeader.m_Width + j * 2 ] = ( buf & 0xF0 ) >> 4;
				pPaletteNum[ i * m_InfoHeader.m_Width + j * 2 + 1 ] = buf & 0x0F;
			}
			if( surplus != 4 ){
				for( MapilInt32 j = 0; j < surplus; j++ ){
					m_Stream.read( reinterpret_cast < MapilChar* > ( &discardData ), sizeof( MapilUChar ) );
				}
			}
		}

		for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				std::cout << /*static_cast < int >*/ ( pPaletteNum[ i * m_InfoHeader.m_Width + j ] ) ;//<< ",";
			}
			std::cout << std::endl;
		}

		// Convert palette number into pixel data.
		for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_R = pPalette[ pPaletteNum[ i * m_InfoHeader.m_Width + j ] ].m_R;
				m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_G = pPalette[ pPaletteNum[ i * m_InfoHeader.m_Width + j ] ].m_G;
				m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_B = pPalette[ pPaletteNum[ i * m_InfoHeader.m_Width + j ] ].m_B;
			}
		}

		SafeDeleteArray( pPalette );
		SafeDeleteArray( pPaletteNum );
	}

	// Load bitmap file whose bit/pixel is 1.
	MapilVoid BMPFile::Load1BitBMP()
	{
		MapilInt32 numPalette = 1 << m_InfoHeader.m_NumBitPerPixel;		// Number of palette.
		ColorRGB < MapilUChar >* pPalette = NULL;		// Palette data.
		MapilUChar* pPaletteNum = NULL;							// Palette number data.

		// Get palette information.
		pPalette = new ColorRGB < MapilUChar > [ numPalette ];
		for( MapilInt32 i = 0; i < numPalette; i++ ){
			MapilChar discard;
			m_Stream.read( reinterpret_cast < MapilChar* > ( &pPalette[ i ].m_B ), sizeof( MapilUChar ) );
			m_Stream.read( reinterpret_cast < MapilChar* > ( &pPalette[ i ].m_G ), sizeof( MapilUChar ) );
			m_Stream.read( reinterpret_cast < MapilChar* > ( &pPalette[ i ].m_R ), sizeof( MapilUChar ) );
			m_Stream.read( reinterpret_cast < MapilChar* > ( &discard ), sizeof( MapilUChar ) );
		}

		for( MapilInt32 i = 0; i < numPalette; i++ ){
			std::cout << static_cast < int > ( pPalette[ i ].m_R ) << "," << static_cast < int > ( pPalette[ i ].m_G ) << "," << static_cast < int > ( pPalette[ i ].m_B ) << std::endl;
		}

		// Get palette number information.
		pPaletteNum = new MapilUChar[ ( m_InfoHeader.m_Width + m_InfoHeader.m_Width % 2 ) * m_InfoHeader.m_Height ];

		MapilUChar discardData = 0;
		// If width isn't multiples of 4, bitmap file sets value 0 to be multiples of 4.
		MapilInt32 surplus;
		surplus = 4 - ( ( m_InfoHeader.m_Width / 8 ) ) % 4;
		for( MapilInt32 i = m_InfoHeader.m_Height - 1; i >= 0; i-- ){
			for( MapilInt32 j = 0; j < ( ( m_InfoHeader.m_Width + 7 ) / 8 ); j++ ){
				MapilUChar buf;
				m_Stream.read( reinterpret_cast < MapilChar* > ( &buf ), sizeof( MapilUChar ) );
				for( MapilInt32 k = 0; k < 8; k++ ){
					pPaletteNum[ i * m_InfoHeader.m_Width + j * 8 + k ] = ( buf >> ( 7 - k ) ) & 0x01;
				}
			}
			if( surplus != 4 ){
				for( MapilInt32 j = 0; j < surplus; j++ ){
					m_Stream.read( reinterpret_cast < MapilChar* > ( &discardData ), sizeof( MapilUChar ) );
				}
			}
		}

		for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				std::cout << /*static_cast < int >*/ ( pPaletteNum[ i * m_InfoHeader.m_Width + j ] ) ;//<< ",";
			}
			std::cout << std::endl;
		}

		// Convert palette number into pixel data.
		for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_R = pPalette[ pPaletteNum[ i * m_InfoHeader.m_Width + j ] ].m_R;
				m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_G = pPalette[ pPaletteNum[ i * m_InfoHeader.m_Width + j ] ].m_G;
				m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_B = pPalette[ pPaletteNum[ i * m_InfoHeader.m_Width + j ] ].m_B;
			}
		}

		SafeDeleteArray( pPalette );
		SafeDeleteArray( pPaletteNum );
	}

	// Save bitmap file whose bit/pixel is 24.
	MapilVoid BMPFile::Save24BitBMP()
	{
		MapilUChar discardData = 0;

		// If width isn't multiples of 4, bitmap file sets value 0 to be multiples of 4.
		MapilInt32 surplus;
		surplus = 4 - ( ( m_InfoHeader.m_Width * ( m_InfoHeader.m_NumBitPerPixel / 8 ) ) % 4 );
		// The pixel data begin from left-bottom on bitmap file.
		for( MapilInt32 i = m_InfoHeader.m_Height - 1; i >= 0; i-- ){
			for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
				m_Stream.write( reinterpret_cast < MapilChar* > ( &m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_B ), sizeof( MapilUChar ) );
				m_Stream.write( reinterpret_cast < MapilChar* > ( &m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_G ), sizeof( MapilUChar ) );
				m_Stream.write( reinterpret_cast < MapilChar* > ( &m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_R ), sizeof( MapilUChar ) );
			}
			if( surplus != 4 ){
				for( MapilInt32 j = 0; j < surplus; j++ ){
					m_Stream.write( reinterpret_cast < MapilChar* > ( &discardData ), sizeof( MapilUChar ) );
				}
			}
		}
	}

	//Save
	MapilVoid BMPFile::Save( const MapilChar* pFileName, MapilInt32 numBitPerPixel )
	{
		Assert(	m_OpenMode == FILE_OPEN_WRITE_MODE,
								TSTR( "Mapil" ),
								TSTR( "BMPFile" ),
								TSTR( "Save" ),
								TSTR( "Open mode isn't write mode" ),
								-1 );

		// Create bitmap file size.
		MapilULongInt32 size;
		switch( numBitPerPixel ){
			case 24:{
				size = 0x36;
				size += m_InfoHeader.m_Height * ( m_InfoHeader.m_Width * 3 + 4 - ( ( m_InfoHeader.m_Width * 3 ) % 4 ) );
				break;
			}
			default:
				break;
		}

		m_FileHeader.m_Type					= 0x4D42;
		m_FileHeader.m_Size					= size;
		m_FileHeader.m_Reserved1			= 0;
		m_FileHeader.m_Reserved2			= 0;

		m_InfoHeader.m_Size					= 40;
		m_InfoHeader.m_Planes				= 1;
		m_InfoHeader.m_NumBitPerPixel		= numBitPerPixel;
				
		if( numBitPerPixel == 24 ){
			m_FileHeader.m_BitPos			= 54;
		}
		else{
			m_FileHeader.m_BitPos			= 54 + ( 1 << m_InfoHeader.m_NumBitPerPixel ) * 4;
		}

		m_InfoHeader.m_CompressionType		= 0;
		m_InfoHeader.m_ImageSize			= m_FileHeader.m_Size - m_FileHeader.m_BitPos;
		m_InfoHeader.m_MeterPerPixelX		= 0;
		m_InfoHeader.m_MeterPerPixelY		= 0;
		m_InfoHeader.m_NumColorUsed			= 0;
		m_InfoHeader.m_NumColorImportant	= 0;

		// Write BMPFileHeader.
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_FileHeader.m_Type ), sizeof( m_FileHeader.m_Type ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_FileHeader.m_Size ), sizeof( m_FileHeader.m_Size ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_FileHeader.m_Reserved1 ), sizeof( m_FileHeader.m_Reserved1 ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_FileHeader.m_Reserved2 ), sizeof( m_FileHeader.m_Reserved2 ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_FileHeader.m_BitPos ), sizeof( m_FileHeader.m_BitPos ) );

		// Write BitmapInfoHeader.
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_Size ), sizeof( m_InfoHeader.m_Size ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_Width ), sizeof( m_InfoHeader.m_Width ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_Height ), sizeof( m_InfoHeader.m_Height ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_Planes ), sizeof( m_InfoHeader.m_Planes ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_NumBitPerPixel ), sizeof( m_InfoHeader.m_NumBitPerPixel ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_CompressionType ), sizeof( m_InfoHeader.m_CompressionType ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_ImageSize ), sizeof( m_InfoHeader.m_ImageSize ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_MeterPerPixelX ), sizeof( m_InfoHeader.m_MeterPerPixelX ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_MeterPerPixelY ), sizeof( m_InfoHeader.m_MeterPerPixelY ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_NumColorUsed ), sizeof( m_InfoHeader.m_NumColorUsed ) );
		m_Stream.write( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_NumColorImportant ), sizeof( m_InfoHeader.m_NumColorImportant ) );

		// Write pixel information.
		switch( m_InfoHeader.m_NumBitPerPixel ){
			case 24:
				Save24BitBMP();
				break;
			default:
				break;
		}
	}

	//Load
	MapilVoid BMPFile::Load( const MapilChar* pFileName )
	{
		Assert(	m_OpenMode == FILE_OPEN_READ_MODE,
				TSTR( "Mapil" ),
				TSTR( "BMPFile" ),
				TSTR( "Save" ),
				TSTR( "Open mode isn't read mode" ),
				-1 );

		// Read BMPFileHeader.
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_FileHeader.m_Type ), sizeof( m_FileHeader.m_Type ) );
		if( m_FileHeader.m_Type != 0x4D42 ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "BMPFile" ),
									TSTR( "Load" ),
									TSTR( "This isn't bitmap file." ),
									-2 );
		}
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_FileHeader.m_Size ), sizeof( m_FileHeader.m_Size ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_FileHeader.m_Reserved1 ), sizeof( m_FileHeader.m_Reserved1 ) );
		if( m_FileHeader.m_Reserved1 != 0 ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "BMPFile" ),
									TSTR( "Load" ),
									TSTR( "Reserved value is bad." ),
									-3 );
		}
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_FileHeader.m_Reserved2 ), sizeof( m_FileHeader.m_Reserved2 ) );
		if( m_FileHeader.m_Reserved2 != 0 ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "BMPFile" ),
									TSTR( "Load" ),
									TSTR( "Reserved value is bad." ),
									-4 );
		}
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_FileHeader.m_BitPos ), sizeof( m_FileHeader.m_BitPos ) );
				
		// Read BitmapInfoHeader.
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_Size ), sizeof( m_InfoHeader.m_Size ) );
		if( m_InfoHeader.m_Size != 40 ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "BMPFile" ),
									TSTR( "Load" ),
									TSTR( "Size of BitmapInfoHeader isn't correct." ),
									-5 );
		}
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_Width ), sizeof( m_InfoHeader.m_Width ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_Height ), sizeof( m_InfoHeader.m_Height ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_Planes ), sizeof( m_InfoHeader.m_Planes ) );
		if( m_InfoHeader.m_Planes != 1 ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "BMPFile" ),
									TSTR( "Load" ),
									TSTR( "Planes value isn't 1." ),
									-6 );
		}
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_NumBitPerPixel ), sizeof( m_InfoHeader.m_NumBitPerPixel ) );
		if( ( m_FileHeader.m_BitPos != 54 + ( 1 << m_InfoHeader.m_NumBitPerPixel ) * 4 )
			&& ( m_InfoHeader.m_NumBitPerPixel != 24 && m_InfoHeader.m_NumBitPerPixel != 32 )){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "BMPFile" ),
									TSTR( "Load" ),
									TSTR( "Bit position value isn't correct." ),
									-7 );
		}
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_CompressionType ), sizeof( m_InfoHeader.m_CompressionType ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_ImageSize ), sizeof( m_InfoHeader.m_ImageSize ) );
		if( m_InfoHeader.m_ImageSize != ( m_FileHeader.m_Size - m_FileHeader.m_BitPos ) && m_InfoHeader.m_ImageSize != 0 ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "BMPFile" ),
									TSTR( "Load" ),
									TSTR( "Image size isn't correct." ),
									-8 );
		}
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_MeterPerPixelX ), sizeof( m_InfoHeader.m_MeterPerPixelX ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_MeterPerPixelY ), sizeof( m_InfoHeader.m_MeterPerPixelY ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_NumColorUsed ), sizeof( m_InfoHeader.m_NumColorUsed ) );
		m_Stream.read( reinterpret_cast < MapilChar* > ( &m_InfoHeader.m_NumColorImportant ), sizeof( m_InfoHeader.m_NumColorImportant ) );

		// Create pixel buffer.
		m_pColorBuf = new ColorRGB < MapilUChar > [ m_InfoHeader.m_Width * m_InfoHeader.m_Height ];

		// Read pixel information.
		switch( m_InfoHeader.m_NumBitPerPixel ){
			case 1:
				Load1BitBMP();
				break;
			case 4:
				Load4BitBMP();
				break;
			case 8:
				Load8BitBMP();
				break;
			case 24:
				Load24BitBMP();
				break;
			case 32:
				Load32BitBMP();
				break;
			default:
				break;
		}
	}

	//Get width
	MapilInt32 BMPFile::GetWidth() const
	{
		return m_InfoHeader.m_Width;
	}

	//Get height
	MapilInt32 BMPFile::GetHeight() const
	{
		return m_InfoHeader.m_Height;
	}

	// Get file size.
	MapilInt32 BMPFile::GetFileSize() const
	{
		return m_FileHeader.m_Size;
	}

	// Get number of bit per pixel
	MapilInt32 BMPFile::GetNumBitPerPixel() const
	{
		return m_InfoHeader.m_NumBitPerPixel;
	}

	// Get pixel color.
	ColorRGB < MapilUChar > BMPFile::GetPixelColor( MapilInt32 x, MapilInt32 y ) const
	{
		return m_pColorBuf[ x + y * m_InfoHeader.m_Width ];
	}

	// Set width.
	MapilVoid BMPFile::SetWidth( MapilInt32 width )
	{
		ColorRGB < MapilUChar >* pColor = m_pColorBuf;

		if( width < m_InfoHeader.m_Width ){
			m_pColorBuf = new ColorRGB < MapilUChar > [ m_InfoHeader.m_Height * width ];
			for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
				for( MapilInt32 j = 0; j < width; j++ ){
					m_pColorBuf[ i * width + j ] = pColor[ i * width + j ];
				}
			}
			SafeDeleteArray( pColor );
		}
		else if( width >= m_InfoHeader.m_Width ){
			m_pColorBuf = new ColorRGB < MapilUChar > [ m_InfoHeader.m_Height * width ];
			for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
				for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
					m_pColorBuf[ i * width + j ] = pColor[ i * width + j ];
				}
			}
			for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
				for( MapilInt32 j = m_InfoHeader.m_Width; j < width; j++ ){
					m_pColorBuf[ i * width * j ].m_R = 0;
					m_pColorBuf[ i * width * j ].m_G = 0;
					m_pColorBuf[ i * width * j ].m_B = 0;
				}
			}
			SafeDeleteArray( pColor );
		}

		m_InfoHeader.m_Width = width;
	}

	// Set height.
	MapilVoid BMPFile::SetHeight( MapilInt32 height )
	{
		ColorRGB < MapilUChar >* pColor = m_pColorBuf;

		if( height < m_InfoHeader.m_Height ){
			m_pColorBuf = new ColorRGB < MapilUChar > [ height * m_InfoHeader.m_Width ];
			for( MapilInt32 i = 0; i < height; i++ ){
				for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
					m_pColorBuf[ i * m_InfoHeader.m_Width + j ] = pColor[ i * m_InfoHeader.m_Width + j ];
				}
			}
			SafeDeleteArray( pColor );
		}
		else if( height >= m_InfoHeader.m_Height ){
			m_pColorBuf = new ColorRGB < MapilUChar > [ height * m_InfoHeader.m_Width ];
			for( MapilInt32 i = 0; i < m_InfoHeader.m_Height; i++ ){
				for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
					m_pColorBuf[ i * m_InfoHeader.m_Width + j ] = pColor[ i * m_InfoHeader.m_Width + j ];
				}
			}
			for( MapilInt32 i = m_InfoHeader.m_Height; i < height; i++ ){
				for( MapilInt32 j = 0; j < m_InfoHeader.m_Width; j++ ){
					m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_R = 0;
					m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_G = 0;
					m_pColorBuf[ i * m_InfoHeader.m_Width + j ].m_B = 0;
				}
			}
			SafeDeleteArray( pColor );
		}

		m_InfoHeader.m_Height = height;
	}

	// Set pixel color.
	MapilVoid BMPFile::SetPixelColor( MapilInt32 x, MapilInt32 y, const ColorRGB < MapilUChar > color )
	{
		m_pColorBuf[ x * m_InfoHeader.m_Width + y ] = color;
	}
}