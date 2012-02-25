/**
*	@file	File.h
*	@brief	File class is the base class which handles the file.
*	@date	2011.6.25 (Sat) 11:15
*/

#ifndef INCLUDED_MAPIL_FILE_H
#define INCLUDED_MAPIL_FILE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "../Type.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	enum FileOpenMode
	{
		FILE_OPEN_NONE_MODE		= 0,	///< No operation mode.
		FILE_OPEN_READ_MODE		= 1,	///< Read mode.
		FILE_OPEN_WRITE_MODE	= 2,	///< Write mode.
	};

	class File
	{
	public:
		/**
		*	@brief Constructor.
		*/
		File();
		/**
		*	@brief Destructor.
		*/
		virtual ~File();
		/**
		*	@brief				Open the file.
		*	@param pFileName	File name to be opened.
		*	@param mode			Open mode.
		*/
		virtual MapilVoid Open( const MapilChar* pFileName, FileOpenMode mode ) = 0;
		/**
		*	@brief Close the file.
		*/
		virtual MapilVoid Close() = 0;
	};
}

#endif	// INCLUDED_MAPIL_FILE_H
