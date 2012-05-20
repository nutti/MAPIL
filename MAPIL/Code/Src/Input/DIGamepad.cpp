/**
*	@file	DIGamepad.cpp
*	@brief	
*	@date	2012.5.20 (Sun) 15:21
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECTINPUT )

#include <Windows.h>

#include "../../Include/MAPIL/Input/DIGamepad.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Input/ConstNums.h"

namespace MAPIL
{
	DIGamepad::DIGamepad( SharedPointer < InputDevice > pDev ) :	Input( pDev ),
																	m_pGamepadDev( NULL ),
																	m_IsUsed( MapilFalse ),
																	m_pWnd(),
																	m_IsInputActive( MapilFalse )
	{
	}

	DIGamepad::~DIGamepad()
	{
		if( m_pGamepadDev ){
			m_pGamepadDev->Unacquire();
		}
		SafeRelease( m_pGamepadDev );
		m_IsUsed = MapilFalse;
		m_IsInputActive = MapilFalse;
	}

	MapilVoid DIGamepad::Create( SharedPointer < Window > pWnd )
	{
		Assert(	m_IsUsed,
				TSTR( "MAPIL" ),
				TSTR( "DIGamepad" ),
				TSTR( "Create" ),
				TSTR( "Gamepad isn't created yet." ),
				-1 );

		CallBackParam param;
		param.m_pDev = m_pDev->GetDev().GetPointer();
		param.m_pGamepadDev = m_pGamepadDev;

		m_pDev->GetDev().GetPointer()->EnumDevices(	DI8DEVCLASS_GAMECTRL,
													reinterpret_cast < ::LPDIENUMDEVICESCALLBACK > ( DIGamepad::GetJoystick ),
													&param,
													DIEDFL_ATTACHEDONLY );

		m_pGamepadDev = param.m_pGamepadDev;

		// Gamepad was not found.
		if( m_pGamepadDev == NULL ){
			return;
		}

		if( FAILED( m_pGamepadDev->SetDataFormat( &::c_dfDIJoystick ) ) ){
			throw MapilException(	TSTR( "MAPIL" ),
									TSTR( "DIGamepad" ),
									TSTR( "Create" ),
									TSTR( "Failed to configure data format." ),
									-1 );
		}

		::DIPROPRANGE diprop;
		ZeroObject( &diprop, sizeof( ::DIPROPRANGE ) );
		diprop.diph.dwSize			= sizeof( diprop );
		diprop.diph.dwHeaderSize	= sizeof( diprop.diph );
		diprop.diph.dwHow			= DIPH_BYOFFSET;
		diprop.lMin					= -1000;			// Minimum effective range.
		diprop.lMax					= 1000;				// Maximum effective range.
		// Set range. (X-axis)
		diprop.diph.dwObj			= DIJOFS_X;
		m_pGamepadDev->SetProperty( DIPROP_RANGE, &diprop.diph );
		// Set range. (Y-axis)
		diprop.diph.dwObj			= DIJOFS_Y;
		m_pGamepadDev->SetProperty( DIPROP_RANGE, &diprop.diph );

		// Set non-effective area.
		::DIPROPDWORD dipropdw;
		dipropdw.diph.dwSize		= sizeof( ::DIPROPDWORD );
		dipropdw.diph.dwHeaderSize	= sizeof( dipropdw.diph );
		dipropdw.diph.dwHow			= DIPH_BYOFFSET;
		dipropdw.dwData				= 2500;		// Non-effective area.
		// Set non-effective area. (X-axis)
		dipropdw.diph.dwObj			= DIJOFS_X;
		m_pGamepadDev->SetProperty( DIPROP_DEADZONE, &dipropdw.diph );
		// Set non-effective area. (Y-axis)
		dipropdw.diph.dwObj			= DIJOFS_Y;
		m_pGamepadDev->SetProperty( DIPROP_DEADZONE, &dipropdw.diph );

		// Start control
		m_pGamepadDev->Acquire();

		m_IsInputActive = MapilTrue;
		m_IsUsed = MapilTrue;
	}

	BOOL CALLBACK DIGamepad::GetJoystick( ::LPDIDEVICEINSTANCE pDIDev, LPVOID pParam )
	{
		HRESULT hr;

		CallBackParam* p = reinterpret_cast < CallBackParam* > ( pParam );

		hr = p->m_pDev->CreateDevice( pDIDev->guidInstance, &( p->m_pGamepadDev ), NULL );
		if( FAILED( hr ) ){
			return DIENUM_CONTINUE;		// Next gamepad should be searched.
		}

		return DIENUM_STOP;		// Device enumeration is finished.
	}
}

#endif	// API_WIN32API