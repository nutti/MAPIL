/**
*	@file	CrossPlatform.h
*	@brief	This file switches the modules to be included to MAPIL. If the user
*			wants to exclude the module, comment out the relevant #define directive.
*			On the other hand, uncomment out the directive if the user wants to
*			include the modules. Some modules need other modules. All files related
*			to MAPIL include this file first.
*	@date	2011.6.7 (Tue) 18:19
*/

#ifndef INCLUDED_MAPIL_CROSSPLATFORM_H
#define INCLUDED_MAPIL_CROSSPLATFORM_H

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{



// Operating system.
#if defined ( WIN32 )
#define OS_WIN_32BIT					// Windows (32bit)
#else
#define OS_LINUX_32BIT				// Linux (32bit)
#endif

// API.
#if defined ( OS_WIN_32BIT )
#define API_WIN32API					// Win32API.
#define API_DIRECT3D					// Direct 3D.
#define API_DIRECT2D					// Direct 2D. (Not supported.)
#define API_DIRECTINPUT					// Direct Input. (Not supported.)
#define API_DIRECTSOUND					// Direct Sound. (Not supported.)
#else
#define API_GTK							// GTK.
#define API_POSIX						// POSIX.
#define API_ALSA						// ALSA.
#endif

// Version of Direct 3D.
#if defined ( API_DIRECT3D )
#define VERSION_DIRECT3D	0x0903		// 9.0c
#endif

#define API_OPENGL						// OpenGL.
#define API_OPENAL						// OpenAL.

// Character code.
#if defined ( UNICODE )
#define CHAR_CODE_UNICODE				// Unicode.
#else
#define CHAR_CODE_MULTIBYTE			// Multi-byte.
#endif

// Library.
#define LIB_STL							// STL.
//#define LIB_BOOST						// Boost.
#define LIB_GLEW						// Glew.
#define LIB_LIBPNG						// Libpng.
#define LIB_ZLIB						// Zlib.

// Debug mode.
#if defined ( OS_WIN_32BIT )
#if defined ( _DEBUG )
#define MAKE_MODE_DEBUG
#else
#define MAKE_MODE_RELEASE
#endif
#else
#define MAKE_MODE_DEBUG
//#define MAKE_MODE_RELEASE
#endif

}

#endif	// INCLUDED_MAPIL_CROSSPLATFORM_H
