/**
*	@file	InputDevice.cpp
*	@brief	
*	@date	2011.7.23 (Sat) 19:57
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Input/InputDevice.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"

namespace MAPIL
{
	InputDevice::InputDevice( MapilInt32 api ) :	m_API( api )
#if defined ( API_DIRECTINPUT )
													,
													m_DI( NULL ),
													m_HWnd( NULL ),
													m_HInst( NULL )
#endif
	{
	}

	InputDevice::~InputDevice()
	{
		Destroy();
		m_API = INPUT_API_UNKNOWN;
#if defined ( API_DIRECTINPUT )
		m_HWnd = NULL;
		m_HInst = NULL;
#endif
	}

	MapilVoid InputDevice::Create()
	{
		if( m_API == INPUT_API_DIRECTINPUT ){
#if defined ( API_DIRECTINPUT )
			m_HInst = GetModuleHandle( NULL );

			if( FAILED( ::DirectInput8Create(	m_HInst,
											DIRECTINPUT_VERSION,
											::IID_IDirectInput8,
											reinterpret_cast < MapilVoid** > ( m_DI.GetPointerOfPointerWithChange() ),
											NULL ) ) ){
				throw MapilException(	TSTR( "MAPIL" ),
									TSTR( "InputDevice" ),
									TSTR( "Create" ),
									TSTR( "Failed to create Direct Input." ),
									-1 );
			}
#endif	// API_DIRECTINPUT
		}
	}

	MapilVoid InputDevice::Destroy()
	{
	}

#if defined ( API_WIN32API ) && defined ( API_DIRECTINPUT )
	COMPointer < IDirectInput8 > InputDevice::GetDev()
	{
		return m_DI;
	}
#endif

	MapilInt32 InputDevice::GetInputAPI() const
	{
		return m_API;
	}

	IInputDevice CreateInputDevice( MapilInt32 api )
	{
		SharedPointer < InputDevice > pID( new InputDevice( api ) );

		return pID;
	}

	
}
