/**
*	@file	FPSManager.cpp
*	@brief	
*	@date	2011.7.23 (Sat) 11:35
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_WIN32API
#include <Windows.h>
#include <MMSystem.h>
#endif

#include "../../Include/MAPIL/Util/FPSManager.h"
#include "../../Include/MAPIL/Util/Memory.hpp"

#ifdef API_WIN32API
#pragma comment( lib, "winmm.lib" )
#endif

namespace MAPIL
{
	//Constructer
	FPSManager::FPSManager() :	m_Precise( 100 ),
								m_FPS( 60 ),
								m_NowTime( 0 ),
								m_pPrevTime( NULL ),
								m_TimePerFrame( 0 ),
								m_NextTime( 0 ),
								m_NowFPS( 0 )
	{
		//Memory is reserved in consideration of precision
#ifdef API_WIN32API
		m_pPrevTime = new DWORD[ m_Precise ];
#endif

		//Initialize
		for( MapilInt32 i = 0; i < m_Precise; i++ ){
#ifdef API_WIN32API
			m_pPrevTime[ i ] = timeGetTime();
#endif
		}

		//Time which should be spent on 1 frame
		m_TimePerFrame = static_cast < MapilInt32 > ( 1000.0f * m_Precise / m_FPS );
		m_NextTime = m_TimePerFrame;
	}

	//Destructer
	FPSManager::~FPSManager()
	{
		m_Precise = 0;
		m_FPS = 0;
		m_NowTime = 0;
		SafeDelete( m_pPrevTime );
		m_TimePerFrame = 0;
		m_NextTime = 0;
		m_NowFPS = 0;
	}

	//Set FPS value
	MapilVoid FPSManager::SetFPS( MapilInt32 fps )
	{
		m_FPS = fps;
	}

	//Set precise value
	MapilVoid FPSManager::SetPrecise( MapilInt32 precise )
	{
		//Initialize
		SafeDeleteArray( m_pPrevTime );
		m_NowTime = 0;
		m_TimePerFrame = 0;
		m_NextTime = 0;

		m_Precise = precise;

		//Memory is reserved in consideration of precision
#ifdef API_WIN32API
		m_pPrevTime = new DWORD[ m_Precise ];
#endif
		//Initialize
		for( MapilInt32 i = 0; i < m_Precise; i++ ){
#ifdef API_WIN32API
			m_pPrevTime[ i ] = timeGetTime();
#endif
		}
		//Time which should be spent on 1 frame
		m_TimePerFrame = static_cast < MapilInt32 > ( 1000.0f * m_Precise / m_FPS );
		m_NextTime = m_TimePerFrame;
	}

	//Does time which should be spent on 1 frame, elapse?
	MapilBool FPSManager::DoesElapseNextTime()
	{
#ifdef API_WIN32API
		timeBeginPeriod( 1 );		//Precision is set as 1 millisecond
		//Get now time
		m_NowTime = timeGetTime();
		timeEndPeriod( 1 );			//Precision is unset
#endif

		//Calculate elapsed time
		MapilInt32 elapsedTime = ( m_NowTime - m_pPrevTime[ m_Precise - 1 ] ) * m_Precise;
		//When time elapsed which should be spent on 1 frame
		if( elapsedTime >= m_NextTime ){
			//Calculate time which should be spent on next frame
			m_NextTime = m_TimePerFrame - ( elapsedTime - m_NextTime );
			//Procedure when elapsed time is negative value
			if( m_NextTime < 0 ){
				m_NextTime = m_TimePerFrame;
			}
			//Calculate now FPS
			m_NowFPS = 1000.0 * m_Precise / ( m_NowTime - m_pPrevTime[ 0 ] );
			//Update history of time
			for( MapilInt32 i = 0; i < ( m_Precise - 1 ); i++ ){
				m_pPrevTime[ i ] = m_pPrevTime[ i + 1 ];
			}
			m_pPrevTime[ m_Precise - 1 ] = m_NowTime;
			
			return MapilTrue;
		}

		return MapilFalse;
	}

	//Get now FPS
	MapilDouble FPSManager::GetNowFPS() const
	{
		return m_NowFPS;
	}
}