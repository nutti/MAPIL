/**
*	@file	GTKGraphicsContext.h
*	@brief	
*	@date	2012.11.8 (Thu) 22:14
*/

#ifndef INCLUDED_MAPIL_GTKGRAPHICSCONTEXT_H
#define INCLUDED_MAPIL_GTKGRAPHICSCONTEXT_H

#include "../CrossPlatform.h"

#if defined ( API_GTK )

#include <gtk/gtk.h>
#include <gdk/gdkx.h>

	#if defined ( API_OPENGL )

	#include <GL/gl.h>
	#include <GL/glx.h>

	#include "GraphicsContext.h"
	#include "../Util/SharedPointer.hpp"
	#include "../Type.h"

namespace MAPIL
{
	class GTKGraphicsContext : public GraphicsContext 
	{
		GtkWidget*					m_pWnd;
		::Window					m_ID;
		Display*					m_pDisp;
		GLXContext					m_Context;
		ExposeSignal*				m_pSig;
		MapilInt32					m_Width;
		MapilInt32					m_Height;
	public:
		GTKGraphicsContext();
		~GTKGraphicsContext();
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
