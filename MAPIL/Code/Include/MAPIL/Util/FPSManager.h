/**
*	@file	FPSManager.h
*	@brief	
*	@date	2011.7.23 (Sat) 11:32
*/

#ifndef INCLUDED_MAPIL_FPSMANAGER_H
#define INCLUDED_MAPIL_FPSMANAGER_H

#include "../CrossPlatform.h"

#ifdef API_WIN32API
#include <Windows.h>
#endif

#include "../Type.h"

namespace MAPIL
{
	class FPSManager
	{

		MapilInt32				m_Precise;			//Precision (The bigger this number, the more precision can be gained)
		MapilInt32				m_FPS;				//FPS
#ifdef API_WIN32API
		DWORD								m_NowTime;			//Now time
		DWORD*								m_pPrevTime;		//History of time
#else
		MapilInt32				m_NowTime;			// Now time.
		MapilInt32*				m_pPrevTime;		// History of time.
#endif
		MapilInt32				m_TimePerFrame;		//Time which should be spent on 1 frame
		MapilInt32				m_NextTime;			//Next time which shift to next frame
		MapilDouble				m_NowFPS;			//Now FPS

		//Prohibit copy constructer
		FPSManager( const FPSManager& fm );
		//Prohibit copy with substitution
		FPSManager& operator=( const FPSManager& fm );

	public:
		
		//Constructer
		FPSManager();
		//Destructer
		~FPSManager();
		//Set FPS value
		MapilVoid SetFPS( MapilInt32 fps );
		//Set precise value
		MapilVoid SetPrecise( MapilInt32 precise );
		//Does time which should be spent on 1 frame, elapse?
		MapilBool DoesElapseNextTime();
		//Get now FPS
		MapilDouble GetNowFPS() const;
	};
}

#endif