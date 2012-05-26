/**
*	@file	ALListener3D.cpp
*	@brief	Implementation of ALListener3D.
*	@date	2012.5.26 (Sat) 9:34
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENAL )

#include "../../Include/MAPIL/Sound/ALListener3D.h"
#include "../../Include/MAPIL/Sound/SoundDevice.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	ALListener3D::ALListener3D( SharedPointer < SoundDevice > pDev ) : Sound( pDev )
	{
		ZeroObject( m_Pos, sizeof( m_Pos ) );
		ZeroObject( m_Dir, sizeof( m_Dir ) );
		ZeroObject( m_Up, sizeof( m_Up ) );
	}

	ALListener3D::~ALListener3D()
	{
		ZeroObject( m_Pos, sizeof( m_Pos ) );
		ZeroObject( m_Dir, sizeof( m_Dir ) );
		ZeroObject( m_Up, sizeof( m_Up ) );
	}

	MapilVoid ALListener3D::Create()
	{
		Assert(	!m_IsUsed,
				TSTR( "MAPIL" ),
				TSTR( "ALListener3D" ),
				TSTR( "Create" ),
				TSTR( "Listener was already created." ),
				-1 );
	}

	MapilVoid ALListener3D::SetPosition( const Vector3 < MapilFloat32 >& pos )
	{
		Assert(	m_IsUsed,
				TSTR( "MAPIL" ),
				TSTR( "ALListener3D" ),
				TSTR( "SetPosition" ),
				TSTR( "Listener is not created yet." ),
				-1 );

		m_Pos[ 0 ] = pos.m_X;
		m_Pos[ 1 ] = pos.m_Y;
		m_Pos[ 2 ] = pos.m_Z;

		alListener3f( AL_POSITION, m_Pos[ 0 ], m_Pos[ 1 ], m_Pos[ 2 ] );
	}

	MapilVoid ALListener3D::SetDirection( const Vector3 < MapilFloat32 >& dir )
	{
		Assert(	m_IsUsed,
				TSTR( "MAPIL" ),
				TSTR( "ALListener3D" ),
				TSTR( "SetDirection" ),
				TSTR( "Listener is not created yet." ),
				-1 );

		m_Dir[ 0 ] = dir.m_X;
		m_Dir[ 1 ] = dir.m_Y;
		m_Dir[ 2 ] = dir.m_Z;

		MapilFloat32 v[ 6 ] = { m_Dir[ 0 ], m_Dir[ 1 ], m_Dir[ 2 ],
								m_Up[ 0 ], m_Up[ 1 ], m_Up[ 2 ] };

		alListenerfv( AL_ORIENTATION, v );
	}

	MapilVoid ALListener3D::SetUpVector( const Vector3 < MapilFloat32 >& up )
	{
		Assert(	m_IsUsed,
				TSTR( "MAPIL" ),
				TSTR( "ALListener3D" ),
				TSTR( "SetUpVector" ),
				TSTR( "Listener is not created yet." ),
				-1 );

		m_Up[ 0 ] = up.m_X;
		m_Up[ 1 ] = up.m_Y;
		m_Up[ 2 ] = up.m_Z;

		MapilFloat32 v[ 6 ] = { m_Dir[ 0 ], m_Dir[ 1 ], m_Dir[ 2 ],
								m_Up[ 0 ], m_Up[ 1 ], m_Up[ 2 ] };

		alListenerfv( AL_ORIENTATION, v );
	}

}

#endif	// API_OPENAL