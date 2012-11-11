#ifndef INCLUDED_MAPIL_TCHAR_H
#define INCLUDED_MAPIL_TCHAR_H

#include "CrossPlatform.h"
#include <wchar.h>

namespace MAPIL
{

#if defined ( CHAR_CODE_UNICODE )
	#define TSTR( str ) L##str
	#define _vstprintf _vswprintf
	#define _vsctprintf _vscwprintf
	#define _tcscpy_s wcscpy_s
	#define _tcslen wcslen
	#define _stprintf swprintf
#endif

#if defined ( CHAR_CODE_MULTIBYTE )
	#define TSTR( str ) str

	#if defined ( OS_WIN_32BIT )
		#define _vstprintf _vsprintf
		#define _vsctprintf _vscprintf
	#else
		#define _vstprintf vsprintf
		#define _vsctprintf(fmt,ap) vsnprintf( NULL, 0, fmt, ap );
	#endif

	#define _tcscpy_s strcpy_s
	#define _tcslen strlen
	#define _stprintf sprintf
#endif

}

#endif
