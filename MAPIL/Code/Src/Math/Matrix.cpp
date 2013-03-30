/**
*	@file	Matrix.cpp
*	@brief	Implementation of Matrix.hpp.
*	@date	2013.3.29 (Fri) 21:53
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Math/Matrix.hpp"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	// Create matrix from quaternion.
	MapilVoid CreateMatrixFromQuaternion( const Vector4 < MapilFloat32 >& in, Matrix4x4 < MapilFloat32 >* pOut )
	{
		MapilFloat32 sx = in.m_X * in.m_X;
		MapilFloat32 sy = in.m_Y * in.m_Y;
		MapilFloat32 sz = in.m_Z * in.m_Z;
		MapilFloat32 cx = in.m_Y * in.m_Z;
		MapilFloat32 cy = in.m_X * in.m_Z;
		MapilFloat32 cz = in.m_X * in.m_Y;
		MapilFloat32 wx = in.m_W * in.m_X;
		MapilFloat32 wy = in.m_W * in.m_Y;
		MapilFloat32 wz = in.m_W * in.m_Z;
		
		pOut->m_11 = 1.0f - 2.0f * ( sy + sz );
		pOut->m_12 = 2.0f * ( cz + wz );
		pOut->m_13 = 2.0f * ( cy - wy );
		pOut->m_21 = 2.0f * ( cz - wz );
		pOut->m_22 = 1.0f - 2.0f * ( sx + sz );
		pOut->m_23 = 2.0f * ( cx + wx );
		pOut->m_31 = 2.0f * ( cy + wy );
		pOut->m_32 = 2.0f * ( cx - wx );
		pOut->m_33 = 1.0f - 2.0f * ( sx + sy );
		pOut->m_41 = 0.0f;
		pOut->m_42 = 0.0f;
		pOut->m_43 = 0.0f;
	}
}