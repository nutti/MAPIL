/**
*	@file	SoundFile.h
*	@brief	
*	@date	2011.6.25(Sat) 11:22
*/

#ifndef INCLUDED_MAPIL_SOUNDFILE_H
#define INCLUDED_MAPIL_SOUNDFILE_H

#include "../CrossPlatform.h"

#include "../Type.h"
#include "File.h"

namespace MAPIL
{
	class SoundFile : public File
	{
	public:
		// Constructor.
		SoundFile();
		// Destructor.
		virtual ~SoundFile();
		// Open.
		virtual MapilVoid Open(	const MapilChar* pFileName,
									FileOpenMode mode ) = 0;
		// Close.
		virtual MapilVoid Close() = 0;
		// Load header.
		virtual MapilVoid LoadHeader() = 0;
		// Load. ( 1 )
		virtual MapilVoid Load() = 0;
		// Load. ( 2 )
		virtual MapilVoid Load(	MapilInt32 begPos,
									MapilInt32 endPos,
									MapilChar* pOutData,
									MapilInt32* pReadSize,
									MapilInt32 readSize ) = 0;
		// Save header.
		virtual MapilVoid SaveHeader() = 0;
		// Save. ( 1 )
		virtual MapilVoid Save() = 0;
		// Save. ( 2 )
		virtual MapilVoid Save(	MapilChar* pOutData,
									MapilInt32 writeSize ) = 0;
		// Get position of data.
		virtual MapilInt32 GetDataPos() const = 0;
		// Get file size.
		virtual MapilInt32 GetFileSize() const = 0;
		// Get format ID.
		virtual MapilShortInt32 GetFmtID() const = 0;
		// Get number of channel.
		virtual MapilShortInt32 GetNumChannel() const = 0;
		// Get sampling rate.
		virtual MapilInt32 GetSampleRate() const = 0;
		// Get data speed.
		virtual MapilInt32 GetDataSpeed() const = 0;
		// Get block size.
		virtual MapilShortInt32 GetBlockSize() const = 0;
		// Get bit per sample.
		virtual MapilShortInt32 GetBitPerSample() const = 0;
	};
}

#endif
