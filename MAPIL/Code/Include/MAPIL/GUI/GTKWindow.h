/**
*	@file	GTKWindow.h
*	@brief	
*	@date	2011.6.15(Wed) 8:13
*/

#ifndef INCLUDED_MAPIL_GTKWINDOW_H
#define INCLUDED_MAPIL_GTKWINDOW_H

#include "../CrossPlatform.h"

#ifdef API_GTK

#include <gtk/gtk.h>

#include "Window.h"
#include "../Type.h"

namespace MAPIL
{

	class ExposeSignal;
	class GTKWindow : public Window
	{
	protected:
		GtkWidget*			m_pWnd;
		GtkWidget*			m_pVBox;
		virtual MapilVoid Init();
	public:
		GTKWindow();
		virtual ~GTKWindow();
		virtual MapilVoid Create( MapilInt32* argc, MapilChar** argv[], MapilInt32 height, MapilInt32 width );
		virtual MapilVoid Resize( MapilInt32 height, MapilInt32 width );
		virtual MapilVoid Add();
		virtual MapilInt32 ProcessMessage();
		virtual MapilVoid Run();
		virtual MapilVoid Show();
		virtual MapilVoid Connect( ExposeSignal* pSig );
		MapilVoid Connect( KeyboardSignal* pSig );
		MapilVoid SetWndMode( MapilInt32 mode );
		GtkWidget* GetVBox();
		MapilVoid ChangePosToClient(	const Vector2 < MapilInt32 >& in,
											Vector2 < MapilInt32 >* pOut );
		MapilVoid ChangePosToScreen(	const Vector2 < MapilInt32 >& in,
											Vector2 < MapilInt32 >* pOut );
	};
}

#endif	// API_GTK

#endif
