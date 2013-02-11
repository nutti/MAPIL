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
		Assert(	!m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "DIGamepad" ),
				TSTR( "Create" ),
				TSTR( "Keyboard was already created." ),
				-1 );

		CallBackParam param;
		param.m_pDev = m_pDev->GetDev().GetPointer();
		param.m_pGamepadDev = m_pGamepadDev;

		m_pDev->GetDev().GetPointer()->EnumDevices(	DI8DEVCLASS_GAMECTRL,
													reinterpret_cast < ::LPDIENUMDEVICESCALLBACK > ( DIGamepad::GetGamepad ),
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

	//BOOL CALLBACK GetGamepads( ::LPDIDEVICEINSTANCE pDIDev, LPVOID pParam )
	//{
	//	HRESULT hr;
	//	hr = p->m_pDev->CreateDevice( pDIDev->guidInstance, &g_lpDIJoypad2[g_dijoycount++], NULL );
	//	return DIENUM_CONTINUE;
	//}

	BOOL CALLBACK DIGamepad::GetGamepad( ::LPDIDEVICEINSTANCE pDIDev, LPVOID pParam )
	{
		HRESULT hr;

		CallBackParam* p = reinterpret_cast < CallBackParam* > ( pParam );

		hr = p->m_pDev->CreateDevice( pDIDev->guidInstance, &( p->m_pGamepadDev ), NULL );
		if( FAILED( hr ) ){
			return DIENUM_CONTINUE;		// Next gamepad should be searched.
		}

		return DIENUM_STOP;		// Device enumeration is finished.
	}

	MapilBool DIGamepad::IsPushed( MapilInt32 button )
	{
		::HRESULT hr;
		::DIJOYSTATE state;

		hr = m_pGamepadDev->Poll();
		if( FAILED( hr ) ){
			hr = m_pGamepadDev->Acquire();
			while( hr == DIERR_INPUTLOST ){
				hr = m_pGamepadDev->Acquire();
			}
		}

		// Get gamepad state.
		hr = m_pGamepadDev->GetDeviceState( sizeof( ::DIJOYSTATE ), &state );
		if( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED ){
			hr = m_pGamepadDev->Acquire();
			while( hr == DIERR_INPUTLOST ){
				hr = m_pGamepadDev->Acquire();
			}
		}

		switch( button ){
			case GAMEPAD_BUTTON_UP:
				return state.lY < 0 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_DOWN:
				return state.lY > 0 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_LEFT:
				return state.lX < 0 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_RIGHT:
				return state.lX > 0 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_A:
				return state.rgbButtons[ 0 ] & 0x80 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_B:
				return state.rgbButtons[ 1 ] & 0x80 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_C:
				return state.rgbButtons[ 2 ] & 0x80 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_X:
				return state.rgbButtons[ 3 ] & 0x80 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_Y:
				return state.rgbButtons[ 4 ] & 0x80 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_Z:
				return state.rgbButtons[ 5 ] & 0x80 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_L:
				return state.rgbButtons[ 6 ] & 0x80 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_R:
				return state.rgbButtons[ 7 ] & 0x80 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_START:
				return state.rgbButtons[ 8 ] & 0x80 ? MapilTrue : MapilFalse;
			case GAMEPAD_BUTTON_M:
				return state.rgbButtons[ 9 ] & 0x80 ? MapilTrue : MapilFalse;
			default:
				break;
		}

		return MapilFalse;
	}
}

#endif	// API_WIN32API