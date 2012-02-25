/**
*	@file	Console.h
*	@brief	The users can output character as if the user develop the CUI applications,
*			even if the users develop GUI applications.
*	@date	2011.7.23 (Sat) 10:53
*/

#ifndef INCLUDED_MAPIL_CONSOLE_H
#define INCLUDED_MAPIL_CONSOLE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_WIN32API )

#include <Windows.h>
#include <stdio.h>

#include "../../../Src/IO/IO.h"
#include "../Type.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class Console : public IO
	{
	private:
		FILE*			m_pFile;			// File descriptor.
		/**
		*	@brief		Prohibit copy constructor.
		*	@param c	Console object to be copied.
		*/
		Console( const Console& c );
		/**
		*	@brief		Prohibit copy with substitution.
		*	@param c	Console object to be copied.
		*	@return		Copied Console object.
		*/
		Console& operator=( const Console& c );
	public:
		/**
		*	@brief Constructor.
		*/
		Console();
		/**
		*	@brief Destructor.
		*/
		~Console();
		/**
		*	@brief Enable writing on the console.
		*/
		MapilVoid Open();
		/**
		*	@brief Disable writing on the console.
		*/
		MapilVoid Close();
	};
}

#endif	// API_WIN32API

#endif	// INCLUDED_MAPIL_CONSOLE_H