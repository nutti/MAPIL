/**
*	@file	Widget.cpp
*	@brief	
*	@date	2011.7.20 (Wed) 21:15
*/

#include "../../Include/MAPIL/GUI/Widget.h"

namespace MAPIL
{
	Widget::Widget() : MapilObject(), m_Width( 0 ), m_Height( 0 )
	{
	}
	
	Widget::~Widget()
	{
		m_Width = 0;
		m_Height = 0;
	}
	
	MapilInt32 Widget::GetWidth() const
	{
		return m_Width;
	}
	
	MapilInt32 Widget::GetHeight() const
	{
		return m_Height;
	}
}
