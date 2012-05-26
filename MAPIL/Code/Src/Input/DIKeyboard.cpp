/**
*	@file	DIKeyboard.cpp
*	@brief	
*	@date	2012.3.7 (Wed) 15:09
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECTINPUT )

#include <Windows.h>

#include "../../Include/MAPIL/Input/DIKeyboard.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"

namespace MAPIL
{
	DIKeyboard::DIKeyboard( SharedPointer < InputDevice > pDev ) :	Keyboard( pDev ),
																	m_pKeyboardDev( NULL ),
																	m_IsUsed( MapilFalse ),
																	m_pWnd(),
																	m_IsInputActive( MapilFalse )
	{
	}

	DIKeyboard::~DIKeyboard()
	{
		if( m_pKeyboardDev ){
			m_pKeyboardDev->Unacquire();
		}
		SafeRelease( m_pKeyboardDev );
		m_IsUsed = MapilFalse;
		m_IsInputActive = MapilFalse;
	}

	MapilVoid DIKeyboard::Create( SharedPointer < Window > pWnd )
	{
		Assert(	!m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "DIKeyboard" ),
				TSTR( "Create" ),
				TSTR( "Keyboard was already created." ),
				-1 );

		m_pWnd.DownCast( pWnd );

		// Create keyboard device.
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateDevice( ::GUID_SysKeyboard, &m_pKeyboardDev, NULL ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "DIKeyboard" ),
									TSTR( "Create" ),
									TSTR( "Failed to create keyboard device." ),
									-1 );
		}

		// Set data format.
		if( FAILED( m_pKeyboardDev->SetDataFormat( &::c_dfDIKeyboard ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "DIKeyboard" ),
									TSTR( "Create" ),
									TSTR( "Failed to set data format." ),
									-2 );
		}

		// Set mode
		if( FAILED( m_pKeyboardDev->SetCooperativeLevel( m_pWnd->GetHWnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "DIKeyboard" ),
									TSTR( "Create" ),
									TSTR( "Failed to set mode." ),
									-3 );
		}

		m_pKeyboardDev->Acquire();

		m_IsInputActive = MapilTrue;

		m_IsUsed = MapilTrue;
	}

	MapilVoid DIKeyboard::GetKeyMap( MapilUChar* pOut )
	{
		Assert(	m_IsUsed,
				TSTR( "Mapil" ),
				TSTR( "DIKeyboard" ),
				TSTR( "GetKeyMap" ),
				TSTR( "Keyboad is not created yet." ),
				-1 );

		HRESULT hr;
		if( m_pKeyboardDev ){
			hr = m_pKeyboardDev->GetDeviceState( sizeof( MapilUChar ) * 256, pOut );
			if( !m_pWnd->IsActive() && m_IsInputActive ){
				m_IsInputActive = MapilFalse;
			}
			else if( m_pWnd->IsActive() && !m_IsInputActive ){
				m_pKeyboardDev->Acquire();
				m_IsInputActive = MapilTrue;
			}
			else if( m_pWnd->IsActive() && ( hr == DIERR_INPUTLOST ) ){
				m_pKeyboardDev->Acquire();
				throw MapilException(	TSTR( "MAPIL" ),
										TSTR( "DIKeyboard" ),
										TSTR( "GetKeyMap" ),
										TSTR( "Failed to create keyboard state." ),
										-1 );
			}
		}
	}

	MapilBool DIKeyboard::IsPushed( MapilInt32 key )
	{
		MapilUChar keyMap[ 256 ];

		GetKeyMap( keyMap );

		return keyMap[ key ] & 0x80 ? MapilTrue : MapilFalse;
	}
}

#endif	// API_WIN32API