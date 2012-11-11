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
#elif defined ( __APPLE__ )
#define OS_MAC_64BIT
#else
#define OS_LINUX_32BIT				// Linux (32bit)
#endif

// API.
#if defined ( OS_WIN_32BIT )
#define API_WIN32API					// Win32API.
#define API_DIRECT3D					// Direct 3D.
#define API_DIRECT2D					// Direct 2D. (Not supported.)
#define API_DIRECTINPUT					// Direct Input. 
//#define API_DIRECTSOUND					// Direct Sound. (Not supported.)
#else
#define API_GTK							// GTK.
#define API_POSIX						// POSIX.
//#define API_ALSA						// ALSA.
#endif

// Sound API.
#if defined ( OS_WIN_32BIT )
#define API_DIRECTSOUND				// Direct Sound. (Not supported.)
#define API_OPENAL					// OpenAL.
#else
#define API_OPENAL					// OpenAL.
//#define API_ALSA					// ALSA.
#endif


// Version of Direct 3D.
#if defined ( API_DIRECT3D )
#define D3D_VER_UNKNOWN			0xFFFFFFFF	// Unknown
#define D3D_VER_9_0_C			0x0903		// 9.0c
#define D3D_VER_10_0			0x1000		// 10.0
//#define DIRECT3D_VERSION		D3D_VER_10_0
#define DIRECT3D_VERSION		D3D_VER_9_0_C
#endif

#define API_OPENGL						// OpenGL.

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

// Use C interface.
#define USE_C_INTERFACE

}

#endif	// INCLUDED_MAPIL_CROSSPLATFORM_H
