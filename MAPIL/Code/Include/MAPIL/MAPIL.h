/**
*	@file	MAPIL.h
*	@brief	
*	@date	2011.8.31 (Wed) 6:45
*/

#ifndef INCLUDED_MAPIL_MAPIL_H
#define INCLUDED_MAPIL_MAPIL_H

#include "CrossPlatform.h"

// Diag.
#include "Diag/MapilException.h"
#include "Diag/Assertion.hpp"
#include "Diag/Logger.h"

// GUI.
#include "GUI/GUIFactory.h"
#include "GUI/KeyboardSignal.h"

// Graphics.
#if defined ( API_OPENGL )
#include "Graphics/GLGraphicsFactory.h"
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#endif

#if defined ( API_DIRECT3D )
#include "Graphics/D3DGraphicsFactory.h"
#pragma comment ( lib, "d3d9.lib" )
#if defined ( MAKE_MODE_DEBUG )
#pragma comment ( lib, "d3dx9d.lib" )
#pragma comment ( lib, "dxerr.lib" )
#elif defined ( MAKE_MODE_RELEASE )
#pragma comment ( lib, "d3dx9.lib" )
#endif
#pragma comment ( lib, "Imm32.lib" )
#pragma comment ( lib, "dxguid.lib" )

#if ( DIRECT3D_VERSION == 0x1000 )
#pragma comment ( lib, "d3d10.lib" )
#if defined ( MAKE_MODE_DEBUG )
#pragma comment ( lib, "d3dx10d.lib" )
#elif defined ( MAKE_MODE_RELEASE )
#pragma comment ( lib, "d3dx10.lib" )
#endif
#endif

#endif

#include "Graphics/Canvas2DBatch.h"
#include "Graphics/SpriteBatch.h"



// Input.
#if defined ( API_WIN32API )
#include "Input/WinAPIInputFactory.h"
#endif
#if defined ( API_DIRECTINPUT )
#include "Input/DIInputFactory.h"
#pragma comment ( lib, "dinput8.lib" )
#endif

// Sound.
#if defined ( API_OPENAL )
#include "Sound/ALSoundFactory.h"
#pragma comment ( lib, "OpenAL32.lib" )
#endif

// Math.
#include "Math/Transformation.hpp"
#include "Math/CollisionDetection.h"

// Util.
#include "Util/String.h"
#include "Util/FPSManager.h"
#include "Util/Allocator.hpp"
#include "Util/HeapAllocator.hpp"

// Algorithm.
#include "Algorithm/LZ.h"
#include "Algorithm/Caesar.h"
#include "Algorithm/XOR.h"

// C-interfaces
#include "Util/CInterface.h"

#if defined ( MAKE_MODE_DEBUG )
#pragma comment( lib, "MAPILd.lib" )
#elif defined ( MAKE_MODE_RELEASE )
#pragma comment( lib, "MAPIL.lib" )
#endif

#endif