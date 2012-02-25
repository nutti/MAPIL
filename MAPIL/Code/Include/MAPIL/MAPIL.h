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
#include "Graphics/GLGraphicsFactory.h"
#pragma comment( lib, "MAPIL.lib" )
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

#include "Graphics/D3DGraphicsFactory.h"
#include "Graphics/Canvas2DBatch.h"
#include "Graphics/SpriteBatch.h"
#pragma comment ( lib, "MAPIL.lib" )
#pragma comment ( lib, "d3d9.lib" )
#if defined ( DEBUG ) || defined ( _DEBUG )
#pragma comment ( lib, "d3dx9d.lib" )
#else
#pragma comment ( lib, "d3dx9.lib" )
#endif
#pragma comment ( lib, "dxerr.lib" )
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "Imm32.lib" )

// Input.
#include "Input/WinAPIInputFactory.h"

// Sound.
#include "Sound/ALSoundFactory.h"

// Math.
#include "Math/Transformation.hpp"
#include "Math/CollisionDetection.h"

// Util.
#include "Util\String.h"


#endif