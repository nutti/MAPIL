/**
*	@file	CPU.h
*	@brief	
*	@date	2012.11.11 (Sun) 8:23
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( OS_WIN_32BIT )
#include <Windows.h>
#elif defined ( OS_LINUX_32BIT ) || defined ( OS_MAC_64BIT )
#include <unistd.h>
#endif

#include "../../Include/MAPIL/Util/CPU.h"

namespace MAPIL
{
	MapilVoid Idle()
	{
#if defined ( OS_WIN_32BIT )
		Sleep( 1 );
#elif defined ( OS_LINUX_32BIT ) || defined ( OS_MAC_64BIT )
		usleep( 1 );
#endif
	}
}
