/**
*	@file	ButtonPushedSignal.cpp
*	@brief	Implementation of ButtonPushedSignal.h.
*	@date	2012.10.28 (Sun) 14:35
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/GUI/ButtonPushedSignal.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	ButtonPushedSignal::ButtonPushedSignal() : Signal(), m_ID( -1 )
	{
	}
	
	ButtonPushedSignal::~ButtonPushedSignal()
	{
	}

	MapilVoid ButtonPushedSignal::SetID( int id )
	{
		m_ID = id;
	}

	MapilInt32 ButtonPushedSignal::GetID() const
	{
		return m_ID;
	}
}
