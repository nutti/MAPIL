/**
*	@file	mapil_Exception.h
*	@brief	
*	@date	2011.6.9(Thu) 16:36
*/

#ifndef INCLUDED_MAPIL_MAPIL_EXCEPTION_H
#define INCLUDED_MAPIL_MAPIL_EXCEPTION_H

#include <string>

#include "Exception.h"

namespace MAPIL
{
	class MapilException : public Exception
	{
		std::basic_string < MapilTChar >		m_SpaceName;
		std::basic_string < MapilTChar >		m_ClassName;
		std::basic_string < MapilTChar >		m_FuncName;
		std::basic_string < MapilTChar >		m_ProblemDesc;
		MapilInt32									m_CodeNum;
		std::basic_string < MapilTChar >		m_Str;
	public:
		// Constructor. (1)
		MapilException(	const MapilTChar* pSpaceName,
							const MapilTChar* pClassName,
							const MapilTChar* pFuncName,
							const MapilTChar* pProblemDesc,
							MapilInt32 codeNum,
							MapilTChar* pStr, ... );
		// Constructor. (2)
		MapilException(	const MapilTChar* pSpaceName,
							const MapilTChar* pClassName,
							const MapilTChar* pFuncName,
							const MapilTChar* pProblemDesc,
							MapilInt32 codeNum );
		// Constructor. (3)
		MapilException( const MapilException& e );
		//Substitute (Overload of = operator)
		MapilException& operator=( const MapilException& e );
		// Destructor.
		~MapilException() throw(){}
		// Process.
		virtual MapilVoid Process();
		// Get space name.
		MapilTChar* GetSpaceName() const;
		// Get class name.
		MapilTChar* GetClassName() const;
		// Get function name.
		MapilTChar* GetFuncName() const;
		// Get problem description.
		MapilTChar* GetProblemDesc() const;
		// Get string.
		std::basic_string < MapilTChar > GetExceptionStr() const;
	};
}

#endif
