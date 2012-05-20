/**
*	@file	DIMouse.cpp
*	@brief	
*	@date	2012.5.19 (Sat) 8:28
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECTINPUT )

#include <Windows.h>

#include "../../Include/MAPIL/Input/DIMouse.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Input/ConstNums.h"

namespace MAPIL
{
	DIMouse::DIMouse( SharedPointer < InputDevice > pDev ) :	Mouse( pDev ),
																m_pMouseDev( NULL ),
																m_IsUsed( MapilFalse ),
																m_pWnd(),
																m_IsInputActive( MapilFalse )
	{
	}

	DIMouse::~DIMouse()
	{
		if( m_pMouseDev ){
			m_pMouseDev->Unacquire();
		}
		SafeRelease( m_pMouseDev );
		m_IsUsed = MapilFalse;
		m_IsInputActive = MapilFalse;
	}

	MapilVoid DIMouse::Create( SharedPointer < Window > pWnd )
	{
		Assert(	!m_IsUsed,
				TSTR( "MAPIL" ),
				TSTR( "DIMouse" ),
				TSTR( "Create" ),
				TSTR( "Mouse was already created." ),
				-1 );

		m_pWnd.DownCast( pWnd );

		// Craete mouse device.
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateDevice(	::GUID_SysMouse,
																	&m_pMouseDev,
																	NULL ) ) ){
			throw MapilException(	TSTR( "MAPIL" ),
									TSTR( "DIMouse" ),
									TSTR( "Create" ),
									TSTR( "Failed to create mouse device." ),
									-1 );
		}

		// Set data format.
		if( FAILED( m_pMouseDev->SetDataFormat( &c_dfDIMouse2 ) ) ){
			throw MapilException(	TSTR( "MAPIL" ),
									TSTR( "DIMouse" ),
									TSTR( "Create" ),
									TSTR( "Failed to set data format." ),
									-2 );
		}

		// Set mode.
		if( FAILED( m_pMouseDev->SetCooperativeLevel(	m_pWnd->GetHWnd(),
														DISCL_NONEXCLUSIVE | DISCL_FOREGROUND ) ) ){
			throw MapilException(	TSTR( "MAPIL" ),
									TSTR( "DIMouse" ),
									TSTR( "Create" ),
									TSTR( "Failed to set mode." ),
									-3 );
		}

		// Set mode of axis. ( Relative value )
		::DIPROPDWORD diprop;
		diprop.diph.dwSize			= sizeof( diprop );
		diprop.diph.dwHeaderSize	= sizeof( diprop.diph );
		diprop.diph.dwObj			= 0;
		diprop.diph.dwHow			= DIPH_DEVICE;
		diprop.dwData				= DIPROPAXISMODE_REL;		// Relative value mode.
		if( FAILED( m_pMouseDev->SetProperty( DIPROP_AXISMODE, &diprop.diph ) ) ){
			throw MapilException(	TSTR( "MAPIL" ),
									TSTR( "DIMouse" ),
									TSTR( "Create" ),
									TSTR( "Failed to set mode of axis." ),
									-4 );
		}

		// Start control.
		m_pMouseDev->Acquire();

		m_IsInputActive = MapilTrue;
		m_IsUsed = MapilTrue;
	}

	MapilVoid DIMouse::GetPos( Vector2 < MapilInt32 >* pPos )
	{
		Assert(	m_IsUsed,
				TSTR( "MAPIL" ),
				TSTR( "DIMouse" ),
				TSTR( "GetPos" ),
				TSTR( "Mouse isn't created yet." ),
				-1 );

		// Get position of mouse cursor.
		POINT p;
		if( !::GetCursorPos( &p ) ){
			throw MapilException(	TSTR( "MAPIL" ),
									TSTR( "DIMouse" ),
									TSTR( "GetPos" ),
									TSTR( "Failed to get position of mouse cursor." ),
									-1 );
		}

		pPos->m_X = p.x;
		pPos->m_Y = p.y;
	}

	MapilVoid DIMouse::SetPos( const Vector2 < MapilInt32 >& pos )
	{
		Assert(	m_IsUsed,
				TSTR( "MAPIL" ),
				TSTR( "DIMouse" ),
				TSTR( "SetPos" ),
				TSTR( "Mouse isn't created yet." ),
				-1 );

		POINT p;
		p.x = pos.m_X;
		p.y = pos.m_Y;
		::SetCursorPos( p.x, p.y );
	}

	MapilBool DIMouse::IsPushed( MapilInt32 button )
	{
		const MapilInt32 BUTTON_PUSHED_FLAG = 0x80;

		Assert(	m_IsUsed,
				TSTR( "MAPIL" ),
				TSTR( "DIMouse" ),
				TSTR( "IsPushed" ),
				TSTR( "Mouse isn't created yet." ),
				-1 );

		MapilInt32 index;
		index = button;
		if( button == MOUSE_BUTTON_LEFT ){
			index = 0;
		}
		else if( button == MOUSE_BUTTON_RIGHT ){
			index = 1;
		}
		else if( button == MOUSE_BUTTON_CENTER ){
			index = 2;
		}

		if( m_pMouseDev ){
			::DIMOUSESTATE2 diMouseState;
			HRESULT hr = m_pMouseDev->GetDeviceState( sizeof( ::DIMOUSESTATE2 ), &diMouseState );
			if( SUCCEEDED( hr ) ){
				if( diMouseState.rgbButtons[ index ] & BUTTON_PUSHED_FLAG ){
					return MapilTrue;
				}
			}
			else if( !m_pWnd->IsActive() && m_IsInputActive ){
				m_IsInputActive = MapilFalse;
			}
			else if( m_pWnd->IsActive() && !m_IsInputActive ){
				m_pMouseDev->Acquire();
				m_IsInputActive = MapilTrue;
			}
			else if( m_pWnd->IsActive() && ( hr == DIERR_INPUTLOST ) ){
				m_pMouseDev->Acquire();
				throw MapilException(	TSTR( "MAPIL" ),
										TSTR( "DIMouse" ),
										TSTR( "IsPushed" ),
										TSTR( "Failed to create mouse state." ),
										-1 );
			}
		}

		return MapilFalse;
	}
}

#endif	// API_WIN32API