/**
*	@file	Window.cpp
*	@brief	
*	@date	2011.6.15(Wed) 8:5
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/GUI/Window.h"

namespace MAPIL
{
	Window::Window() :	Widget(),
						m_ClassName(),
						m_WndName(),
						m_IsWndMode( MapilFalse )
	{
	}
	
	Window::~Window()
	{
		m_IsWndMode = MapilFalse;
	}
}
