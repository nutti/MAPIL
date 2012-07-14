/**
*	@file	MapilExceptoin.cpp
*	@brief	
*	@date	2011.6.9(Thu) 19:16
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include <cstdarg>
#include <stdlib.h>

#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Util/String.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

namespace MAPIL
{

	// Constructor.
	MapilException::MapilException(	const MapilTChar* pSpaceName,
										const MapilTChar* pClassName,
										const MapilTChar* pFuncName,
										const MapilTChar* pProblemDesc,
										MapilInt32 codeNum,
										MapilTChar* pStr, ... ) :	Exception(),
																		m_SpaceName( pSpaceName ),
																		m_ClassName( pClassName ),
																		m_FuncName( pFuncName ),
																		m_ProblemDesc( pProblemDesc ),
																		m_CodeNum( codeNum )
	{
		va_list list;
		MapilInt32 strLen;
		MapilTChar strTmp[ 1024 ];

		m_Str += TSTR( "Location : " );
		m_Str += m_SpaceName;
		m_Str += TSTR( "::" );
		m_Str += m_ClassName;
		m_Str += TSTR( "::" );
		m_Str += m_FuncName;
		m_Str += TSTR( "\n\nError : " );
		m_Str += m_ProblemDesc;
		m_Str += TSTR( "\n\nComment : " );

		va_start( list, pStr );
	//	strLen = _vsctprintf( pStr, list ) + 1;
		if( strLen > 1024 ){
			exit( 1 );
		}
	//	_vstprintf( strTmp, pStr, list );

		m_Str += strTmp;
	}

	// Constructor. (2)
	MapilException::MapilException(	const MapilTChar* pSpaceName,
										const MapilTChar* pClassName,
										const MapilTChar* pFuncName,
										const MapilTChar* pProblemDesc,
										MapilInt32 codeNum ) :	Exception(),
																m_SpaceName( pSpaceName ),
																m_ClassName( pClassName ),
																m_FuncName( pFuncName ),
																m_ProblemDesc( pProblemDesc ),
																m_CodeNum( codeNum )
	{
		m_Str += TSTR( "Location : " );
		m_Str += m_SpaceName;
		m_Str += TSTR( "::" );
		m_Str += m_ClassName;
		m_Str += TSTR( "::" );
		m_Str += m_FuncName;
		m_Str += TSTR( "\n\nError : " );
		m_Str += m_ProblemDesc;
		m_Str += TSTR( "\n\nComment : " );
	}

	// Constructor. (3)
	MapilException::MapilException( const MapilException& e ) :	m_SpaceName( e.m_SpaceName ),
																m_ClassName( e.m_ClassName ),
																m_FuncName( e.m_FuncName ),
																m_ProblemDesc( e.m_ProblemDesc ),
																m_CodeNum( e.m_CodeNum ),
																m_Str( e.m_Str )
	{
	}

	// Constructor. (4)
	MapilException::MapilException(	const MapilObject* pObj,
									const MapilTChar* pFuncName,
									const MapilTChar* pProblemDesc,
									MapilInt32 codeNum )
	{
		char str[ 1024 ];
		if( ::strlen( typeid( *pObj ).name() ) < 1024 ){
			::strcpy( str, typeid( *pObj ).name() );
		}
		char* p = str;
		p += 6;			// Skip class<space>.

		std::string spaceName( ::strtok( p, "::" ) );
		MapilTChar buf[ 1024 ];
		ConvertToTChar( spaceName.c_str(), ::strlen( spaceName.c_str() ), buf, 1024 );
		m_SpaceName = buf;
		std::string className( ::strtok( NULL, "::" ) );
		ConvertToTChar( className.c_str(), ::strlen( className.c_str() ), buf, 1024 );
		m_ClassName = buf;
	}

	// Constructor. (5)
	MapilException::MapilException(	const MapilTChar* pPosition,
									const MapilTChar* pProblemDesc,
									MapilInt32 codeNum )
	{
		m_Str += TSTR( "Location : " );
		m_Str += pPosition;
		m_Str += TSTR( "\n\nError : " );
		m_Str += pProblemDesc;
		m_Str += TSTR( "\n\n" );
	}

	// Constructor. (6)
	MapilException::MapilException(	const MapilChar* pPosition,
									const MapilTChar* pProblemDesc,
									MapilInt32 codeNum )
	{
		MapilTChar str[ 1024 ];
		ZeroObject( str, sizeof( str ) );
		ConvertToTChar( pPosition, strlen( pPosition ), str, 1024 );

		m_Str += TSTR( "\n-------------- MAPIL Exception Report -----------------\n" );
		m_Str += TSTR( "Location : " );
		m_Str += str;
		m_Str += TSTR( "\nError : " );
		m_Str += pProblemDesc;
		m_Str += TSTR( "\nReturn Code : " );
		_stprintf( str, TSTR( "%d" ), codeNum );
		m_Str += str;
		m_Str += TSTR( "\n-------------- MAPIL Exception Report End--------------\n\n" );
	}

	//Substitute (Overload of = operator)
	MapilException& MapilException::operator=( const MapilException& e )
	{
		m_SpaceName = e.m_SpaceName;
		m_ClassName = e.m_ClassName;
		m_FuncName = e.m_FuncName;
		m_ProblemDesc = e.m_ProblemDesc;
		m_CodeNum = e.m_CodeNum;
		m_Str = e.m_Str;

		return *this;
	}

	// Process.
	MapilVoid MapilException::Process()
	{
		//MessageBox( m_HWnd, m_Str.c_str(), TSTR( "Win32API Exception" ), MB_OK | MB_ICONERROR );
	}

	// Get string.
	std::basic_string < MapilTChar > MapilException::GetExceptionStr() const
	{
		return m_Str;
	}

}
