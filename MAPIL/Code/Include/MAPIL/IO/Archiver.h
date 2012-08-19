/**
*	@file	Archiver.h
*	@brief	Archiver class provides to handle the archive file.
*	@date	2012.2.4 (Sat) 9:07
*/

#ifndef INCLUDED_MAPIL_ARCHIVER_H
#define INCLUDED_MAPIL_ARCHIVER_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include <string>
#include <vector>

#include "../Util/MapilObject.h"
#include "File.h"

#include "../Type.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{

	class Archiver : public MapilObject
	{
	private:
		std::basic_string < MapilChar >						m_ArchiveName;	///< Archive file name.
		std::vector < MapilChar* >							m_FileName;	///< File name.
		std::vector < MapilInt32 >							m_FileSize;	///< File size.
		std::vector < MapilInt32 >							m_FilePos;		///< File position.
		MapilInt32											m_FileTotal;	///< Number of file.
		
		Archiver( const Archiver& a );
		Archiver& operator=( const Archiver& a );
		MapilInt32 LoadInt( std::basic_ifstream < MapilChar >* pStream );
		MapilVoid SaveInt( std::basic_ofstream < MapilChar >* pStream, MapilInt32 data );
		MapilInt32 GetDataSize( std::basic_ifstream < MapilChar >* pStream );
	public:
		/**
		*	@brief Constructor.
		*/
		Archiver();
		/**
		*	@brief Destructor.
		*/
		~Archiver();
		/**
		*	@brief				Open the file.
		*	@param pFileName	File name to be opened.
		*	@param mode			Open mode.
		*/
		MapilVoid Open( const MapilChar* pFileName, MapilInt32 mode );
		/**
		*	@brief				Load.
		*	@param pFileName	File name to load.
		*	@param pData		Loaded data.
		*/
		MapilVoid Load( const MapilChar* pFileName, MapilChar* pData );
		/**
		*	@brief				Load.
		*	@param pFileName	File name to load.
		*	@param pData		Loaded data.
		*	@param beginPos		Begin position of the loading.
		*	@param endPos		End position of the loading.
		*	@param pReadSize	Loaded size.
		*/
		MapilVoid Load(	const MapilChar* pFileName,
						MapilChar* pData,
						MapilInt32 offset,
						MapilInt32 size,
						MapilInt32* pReadSize );
		/**
		*	@brief				Save.
		*	@param pFileName	File name to save.
		*/
		MapilVoid Save( const MapilChar* pFileName );
		/**
		*	@brief				Set the contents.
		*	@param pFileName	File name to save.
		*/
		MapilVoid SetContents( const MapilChar* pFileName );
		/**
		*	@brief				Set the contents.
		*	@param	pFileName	File name to save.
		*	@return				Sizez of the contents.
		*/
		MapilInt32 GetContentsSize( const MapilChar* pFileName );
		/**
		*	@brief Close the file.
		*/
		MapilVoid Close();
		const MapilChar* GetArchiveFileName() const;
	};
}

#endif	// INCLUDED_MAPIL_ARCHIVR_H
