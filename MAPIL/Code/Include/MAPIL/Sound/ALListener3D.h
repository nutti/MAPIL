/**
*	@file	ALListener3D.h
*	@brief	
*	@date	2012.5.26 (Sat) 9:32
*/

#ifndef INCLUDED_MAPIL_ALLISTENER_H
#define INCLUDED_MAPIL_ALLISTENER_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_OPENAL )

#if defined ( OS_WIN_32BIT )
#include <al.h>
#include <alc.h>
#elif defined ( OS_LINUX_32BIT )
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include "Sound.h"
#include "../Math/Vector.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class ALListener3D : public Sound
	{
		MapilFloat32		m_Pos[ 3 ];		///< Position.
		MapilFloat32		m_Dir[ 3 ];		///< Direction.
		MapilFloat32		m_Up[ 3 ];		///< Up vector.
		MapilBool			m_IsUsed;
	private:
		ALListener3D( SharedPointer < SoundDevice > pDev );
		~ALListener3D();
		MapilVoid Create();
		MapilVoid SetPosition( const Vector3 < MapilFloat32 >& pos );
		MapilVoid SetDirection( const Vector3 < MapilFloat32 >& dir );
		MapilVoid SetUpVector( const Vector3 < MapilFloat32 >& up );
	};
}

#endif	// API_OPENAL

#endif	// INCLUDED_MAPIL_ALSTATICBUFFER_H
