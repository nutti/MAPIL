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
