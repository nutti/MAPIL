/**
*	@file	Exception.h
*	@brief	Exception class is base class, and used for handling the
*			exceptions to be occurred at MAPIL.
*	@date	2011.6.7 (Tue) 18:22
*/

#ifndef INCLUDED_MAPIL_DIAG_EXCEPTION_H
#define INCLUDED_MAPIL_DIAG_EXCEPTION_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../Type.h"
#include "../Util/MapilObject.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class Exception : public MapilObject
	{
	public:
		/**
		*	@brief Constructor.
		*/
		Exception();
		/**
		*	@brief Destructor.
		*/
		virtual ~Exception() throw(){}
	};
}

#endif	// INCLUDED_MAPIL_DIAG_EXCEPTION_H
