/**
*	@file	Assertion.hpp
*	@brief	Assertion.hpp provides utility for the users when the users
*			when the susers debug the programs.
*	@date	2011.6.13 (Mon) 12:16
*/

#ifndef INCLUDED_MAPIL_ASSERTION_HPP
#define INCLUDED_MAPIL_ASSERTION_HPP

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include <string>
#include <stdlib.h>

#include "../Type.h"
#include "../Util/Memory.hpp"
#include "../TChar.h"

//-------------------------------------------------------------------
// Function definition.
//-------------------------------------------------------------------

namespace MAPIL
{
	/**
	*	@brief	Assert parameter and exit the program when 
	*			the param is false.
	*	@param	param The sentence which will be asserted.
	*	@param	exitNum The exit code.
	*/
	inline MapilVoid Assert( MapilInt32 param, MapilInt32 exitNum )
	{
#ifdef MAKE_MODE_DEBUG
		if( !( param ) ){
			exit( exitNum );
		}
#endif
#ifdef MAKE_MODE_RELEASE
#endif
	}

	/**
	*	@brief	Assert parameter and exit the program when 
	*			the param is false.
	*	@param	param The sentence which will be asserted.
	*	@param	exitNum The exit code.
	*/
	inline MapilVoid Assert(	MapilInt32 param,
								const MapilTChar* pSpaceName,
								const MapilTChar* pClassName,
								const MapilTChar* pMethodName,
								const MapilTChar* pProblemDesc,
								MapilInt32 exitNum )
	{
#ifdef MAKE_MODE_DEBUG
		if( !( param ) ){
			std::basic_string < MapilTChar > strDebug;
			strDebug += TSTR( "Location : " );
			strDebug += pSpaceName;
			strDebug += TSTR( "::" );
			strDebug += pClassName;
			strDebug += TSTR( "::" );
			strDebug += pMethodName;
			strDebug += TSTR( "\n\nError : " );
			strDebug += pProblemDesc;
#if defined ( OS_WIN_32BIT )
			OutputDebugString( strDebug.c_str() );
#endif
			exit( exitNum );
		}
#endif
#ifdef MAKE_MODE_RELEASE
#endif
	}

	/**
	*	@brief	Assert parameter and exit the program when 
	*			the param is false.
	*	@param	param The sentence which will be asserted.
	*	@param	exitNum The exit code.
	*/
	inline MapilVoid Assert(	MapilInt32 param,
								const MapilChar* pPosition,
								const MapilTChar* pProblemDesc,
								MapilInt32 exitNum )
	{
#ifdef MAKE_MODE_DEBUG
		if( !( param ) ){
			MapilTChar str[ 1024 ];
			ZeroObject( str, sizeof( str ) );
			ConvertToTChar( pPosition, strlen( pPosition ), str, 1024 );

			m_Str += TSTR( "\n-------------- MAPIL Assertion Report -----------------\n" );
			m_Str += TSTR( "Location : " );
			m_Str += str;
			m_Str += TSTR( "\nProblem : " );
			m_Str += pProblemDesc;
			m_Str += TSTR( "\nReturn Code : " );
			_stprintf( str, TSTR( "%d" ), codeNum );
			m_Str += str;
			m_Str += TSTR( "\n-------------- MAPIL Assertion Report End--------------\n\n" );
#if defined ( OS_WIN_32BIT )
			OutputDebugString( strDebug.c_str() );
#endif
			exit( exitNum );
		}
#endif
#ifdef MAKE_MODE_RELEASE
#endif

	}
}

#endif	// INCLUDED_MAPIL_ASSERTION_HPP
