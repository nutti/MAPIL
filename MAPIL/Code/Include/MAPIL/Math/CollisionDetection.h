/**
*	@file	CollisionDetection.hpp
*	@brief	
*	@date	2011.12.31 (Sat) 12:09
*/

#ifndef INCLUDED_MAPIL_COLLISIONDETECTION_H
#define INCLUDED_MAPIL_COLLISIONDETECTION_H

#include "../CrossPlatform.h"

#include "../Math/Vector.hpp"

#include "../Type.h"

namespace MAPIL
{
	MapilBool DetectColision(	const Vector3 < MapilFloat32 >& vVertex0,
								const Vector3 < MapilFloat32 >& vVertex1,
								const Vector3 < MapilFloat32 >& vVertex2,
								const Vector3 < MapilFloat32 >& vRayOrig,
								const Vector3 < MapilFloat32 >& vRayDir,
								Vector2 < MapilFloat32 >* pVCollisionPos,
								MapilFloat32* pDistance );
}

#endif	// INCLUDED_MAPIL_COLLISIONDETECTION_H