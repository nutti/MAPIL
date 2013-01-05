/**
*	@file	WAVFile.h
*	@brief	
*	@date	2011.6.25(Sat) 11:29
*/

#ifndef INCLUDED_MAPIL_WAVFILE_H
#define INCLUDED_MAPIL_WAVFILE_H

#include "../CrossPlatform.h"

#include <fstream>

#include "SoundFile.h"

namespace MAPIL
{

	struct WAVFileHeader
	{
	public:
		MapilChar			m_RIFFHeader[ 4 ];			// RIFF header.
		MapilInt32			m_FileSize;					// File size.
		MapilChar			m_WAVEHeader[ 4 ];			// WAVE header.
		MapilChar			m_FMTHeader[ 4 ];				// fmt chunk.
		MapilInt32			m_FMTSize;						// fmt chunk size.
		MapilShortInt32		m_FmtID;						// Format ID.
		MapilShortInt32		m_NumChannel;					// Number of channel.
		MapilInt32			m_SampleRate;					// Sampling rate.
		MapilInt32			m_BytePerSec;					// Data speed (Byte/sec).
		MapilShortInt32		m_BlockSize;					// Block size.
		MapilShortInt32		m_BitPerSample;				// Bit per sample (Bit/sample).
		MapilChar			m_DATAHeader[ 4 ];			// Data header.
		MapilInt32			m_DataSize;					// Data size.
	};
	
	class WAVFile : public SoundFile
	{
	private:
		std::basic_fstream < MapilChar >		m_Stream;		// File stream.
		WAVFileHeader							m_Header;		// Header of wave file.
		MapilChar*								m_pWavData;		// Data.
		MapilChar*								m_pInfo;		// Information.
		MapilInt32								m_InfoSize;		// Information size.
		FileOpenMode							m_OpenMode;		// Open mode.
		MapilInt32								m_FileSize;		// File size.

		MapilInt32 GetChunkPos( const MapilChar* pChunkName );
	public:
		// Constructor.
		WAVFile();
		// Destructor.
		~WAVFile();
		// Copy constructor.
		WAVFile( const WAVFile& wf );
		// Substitute. ( Overload of = operator. )
		WAVFile& operator=( const WAVFile& wf );
		// Open.
		MapilVoid Open(	const MapilChar* pFileName,
							FileOpenMode mode );
		// Close.
		MapilVoid Close();
		// Get size.
		MapilInt32 GetSize();
		// Load header.
		MapilVoid LoadHeader();
		// Load infomation data.
		MapilVoid LoadInfo();
		// Load. ( 1 )
		MapilVoid Load();
		// Load. ( 2 )
		MapilVoid Load(	MapilInt32 begPos,
							MapilInt32 endPos,
							MapilChar* pOutData,
							MapilInt32* pReadSize,
							MapilInt32 readSize );
		// Save header.
		MapilVoid SaveHeader();
		// Save. ( 1 )
		MapilVoid Save();
		// Save. ( 2 )
		MapilVoid Save(	MapilChar* pOutData,
							MapilInt32 writeSize );
		// Get position of information data.
		MapilInt32 GetInfoPos() const;
		// Get position of data.
		MapilInt32 GetDataPos() const;
		// Get wave file header.
		WAVFileHeader GetWAVFileHeader() const;
		// Set wave file header.
		MapilVoid SetWAVFileHeader( const WAVFileHeader& header );
		// Get file size.
		MapilInt32 GetFileSize() const;
		// Get format ID.
		MapilShortInt32 GetFmtID() const;
		// Get number of channel.
		MapilShortInt32 GetNumChannel() const;
		// Get sampling rate.
		MapilInt32 GetSampleRate() const;
		// Get data speed.
		MapilInt32 GetDataSpeed() const;
		// Get block size.
		MapilShortInt32 GetBlockSize() const;
		// Get bit per sample.
		MapilShortInt32 GetBitPerSample() const;
	};

	MapilVoid GetWAVFileHeader( const MapilChar* pData, WAVFileHeader* pHeader );

	MapilInt32 GetWAVFileChunkPos( const MapilChar* pChunkName, const MapilChar* pData, MapilInt32 size );
}

#endif
