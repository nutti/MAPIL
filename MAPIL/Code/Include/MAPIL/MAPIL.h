/**
*	@file	MAPIL.h
*	@brief	
*	@date	2011.8.31 (Wed) 6:45
*/

#ifndef INCLUDED_MAPIL_MAPIL_H
#define INCLUDED_MAPIL_MAPIL_H

#include "CrossPlatform.h"

// Exception.
#include "Diag/MapilException.h"

// GUI.
#include "GUI/GUIFactory.h"

// Graphics.
#if defined ( API_OPENGL )
#include "Graphics/GLGraphicsFactory.h"
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#endif

#if defined ( API_DIRECT3D )
#include "Graphics/D3DGraphicsFactory.h"
#pragma comment ( lib, "d3d9.lib" )
#if defined ( DEBUG ) || defined ( _DEBUG )
#pragma comment ( lib, "d3dx9d.lib" )
#else
#pragma comment ( lib, "d3dx9.lib" )
#endif
#pragma comment ( lib, "Imm32.lib" )
#endif

#include "Graphics/Canvas2DBatch.h"
#include "Graphics/SpriteBatch.h"

#pragma comment ( lib, "dxerr.lib" )
#pragma comment ( lib, "dxguid.lib" )


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
#endif

// Math.
#include "Math/Transformation.hpp"
#include "Math/CollisionDetection.h"

// Util.
#include "Util\String.h"

// C-interfaces
#include "Util\CInterface.h"

#pragma comment( lib, "MAPIL.lib" )

#endif