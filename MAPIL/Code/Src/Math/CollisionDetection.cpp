/**
*	@file	CollisionDetection.cpp
*	@brief	Implementation of CollisionDetection.
*	@date	2011.12.31 (Sat) 12:17
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Math/CollisionDetection.h"
#include <math.h>

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	MapilBool DetectColision(	const Vector3 < MapilFloat32 >& vVertex0,
								const Vector3 < MapilFloat32 >& vVertex1,
								const Vector3 < MapilFloat32 >& vVertex2,
								const Vector3 < MapilFloat32 >& vRayOrig,
								const Vector3 < MapilFloat32 >& vRayDir,
								Vector2 < MapilFloat32 >* pVCollisionPos,
								MapilFloat32* pDistance )
	{
		// e1 = vVertex1 - vVertex0
		// e2 = vVertex2 - vVertex0
		Vector3 < MapilFloat32 > e1 = vVertex1;
		e1.Sub( vVertex0 );
		Vector3 < MapilFloat32 > e2 = vVertex2;
		e2.Sub( vVertex0 );

		// a = -e1
		Vector3 < MapilFloat32 > a = - e1;
		// b = -e2
		Vector3 < MapilFloat32 > b = - e2;
		// c = dir
		Vector3 < MapilFloat32 > c = vRayDir;
		// d = vVertex0 - vRayOrig
		Vector3 < MapilFloat32 > d = vVertex0;
		d.Sub( vRayOrig );

		// Calculate the denominator. det( a, b, c )
		MapilFloat32 denominator = CalcDeterminant( a, b, c );

		// Error.
		const MapilFloat32 EPSILON = 0.00001f;

		// If the denominator closes to 0, the ray does not collide.
		if( abs( denominator ) <= EPSILON ){
			return false;
		}

		MapilFloat32 invDenominator = 1.0f / denominator;

		// vVertex0 - vRayOrig = alpha * ( -e1 ) + beta * ( -e2 ) + gamma * ( vRayDir )
		// d = alpha * a + beta * b + gamma * c

		// alpha = det( d, b, c ) / det( a, b, c )
		MapilFloat32 alpha = CalcDeterminant( d, b, c ) * invDenominator;
		// beta = det( a, d, c ) / det( a, b, c )
		MapilFloat32 beta = CalcDeterminant( a, d, c ) * invDenominator;
		// gamma = det( a, b, d ) / det( a, b, c )
		MapilFloat32 gamma = CalcDeterminant( a, b, d ) * invDenominator;

		// Colision conditions.
		// 0 <= alpha <= 1
		// 0 <= beta <= 1
		// 0 <= alpha + beta <= 1
		// gamma >= 0

		// Not collision
		if( alpha > 1 || alpha < 0 ){
			return false;
		}
		if( beta > 1 || beta < 0 ){
			return false;
		}
		if( alpha + beta < 0 || alpha + beta > 1 ){
			return false;
		}
		if( gamma < 0 ){
			return false;
		}

		pVCollisionPos->m_X = alpha;
		pVCollisionPos->m_Y = beta;
		*pDistance = gamma;


		return true;
	}
}