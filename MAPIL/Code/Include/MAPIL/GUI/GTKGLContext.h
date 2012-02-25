/**
*	@file	GTKGLContext.h
*	@brief	
*	@date	2011.8.20 (Sat) 12:10
*/

#ifndef INCLUDED_MAPIL_GTKGLCONTEXT_H
#define INCLUDED_MAPIL_GTKGLCONTEXT_H

#include "../CrossPlatform.h"

#ifdef API_GTK

#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#ifdef API_OPENGL

#include <GL/gl.h>
#include <GL/glx.h>

#include "GLContext.h"
#include "../Util/SharedPointer.hpp"
#include "../Type.h"

namespace MAPIL
{
	class GTKGLContext : public GLContext
	{
		GtkWidget*					m_pWnd;
		::Window					m_ID;
		Display*					m_pDisp;
		GLXContext					m_Context;
		ExposeSignal*				m_pSig;
		MapilInt32					m_Width;
		MapilInt32					m_Height;
	public:
		GTKGLContext();
		~GTKGLContext();
		MapilVoid Create(	MapilInt32* argc,
							MapilChar** argv[],
							MapilInt32 height,
							MapilInt32 width );
		MapilVoid Create(	MapilInt32* argc,
							MapilChar** argv[],
							MapilInt32 height,
							MapilInt32 width,
							SharedPointer < Window > pParent );
		MapilVoid Resize( MapilInt32 height, MapilInt32 width );
		MapilVoid Add();
		MapilInt32 ProcessMessage();
		MapilVoid Run();
		MapilVoid Show();
		MapilVoid Connect( ExposeSignal* pSig );
		MapilVoid Swap();
	};
}

#endif	// API_OPENGL

#endif	// API_GTK

#endif
