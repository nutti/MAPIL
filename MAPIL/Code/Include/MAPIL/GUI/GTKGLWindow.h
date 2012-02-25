/**
*	@file	GTKGLWindow.h
*	@brief	
*	@date	2011.6.15(Wed) 8:13
*/

#ifndef INCLUDED_MAPIL_GTKGLWINDOW_H
#define INCLUDED_MAPIL_GTKGLWINDOW_H

#include "../CrossPlatform.h"


#ifdef API_GTK
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#ifdef API_OPENGL
#include <GL/gl.h>
#include <GL/glx.h>

#include "GTKWindow.h"
#include "ExposeSignal.h"

namespace MAPIL
{
	class GTKGLWindow : public GTKWindow
	{
	protected:
		GtkWidget*			m_pDrawArea;
		::Window			m_ID;
		Display*			m_pDisp;
		GLXContext			m_Context;
		ExposeSignal*		m_pSig;
		virtual MapilVoid Init();
		MapilVoid InitOpenGL( Display* pDisp, ::Window id );
	public:
		GTKGLWindow();
		virtual ~GTKGLWindow();
		MapilVoid Connect( ExposeSignal* pSig );
		Display* GetDisplay() const;
		::Window GetWndID() const;
		GLXContext GetContext() const;
		MapilInt32 ProcessMessage();
		static gint cb_expose( GtkWidget* widget, GdkEventExpose* event, gpointer data );
	};
}

#endif	// API_OPENGL
#endif	// API_GTK

#endif