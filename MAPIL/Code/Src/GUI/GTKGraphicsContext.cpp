/**
*	@file	GTKGraphicsContext.cpp
*	@brief	
*	@date	2012.11.8 (Thu) 22:14
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_GTK )

#if defined ( API_OPENGL )

#include "../../Include/MAPIL/GUI/GTKGraphicsContext.h"
#include "../../Include/MAPIL/GUI/GTKWindow.h"
#include "../../Include/MAPIL/GUI/GTKSignalServer.h"

#include <stdlib.h>

namespace MAPIL
{
	GTKGraphicsContext::GTKGraphicsContext() :	GraphicsContext(),
										m_pWnd( NULL ),
										m_Width( 0 ),
										m_Height( 0 )
	{
	}
	
	GTKGraphicsContext::~GTKGraphicsContext()
	{
	}
	
	MapilVoid GTKGraphicsContext::Create(	MapilInt32* argc,
										MapilChar** argv[],
										MapilInt32 height,
										MapilInt32 width )
	{
	}
	
	MapilVoid GTKGraphicsContext::Create(	MapilInt32* argc,
										MapilChar** argv[],
										MapilInt32 height,
										MapilInt32 width,
										SharedPointer < Window > pParent )
	{
		SharedPointer < GTKWindow > wnd;
		if( !wnd.DownCast( pParent ) ){
			return;
		}
		
		m_Width = width;
		m_Height = height;
	
		// Create widget.
		m_pWnd = gtk_drawing_area_new();
		gtk_widget_set_size_request( m_pWnd, m_Width, m_Height );
		gtk_box_pack_start( GTK_BOX( wnd->GetVBox() ), m_pWnd, TRUE, TRUE, 0 );
		gtk_widget_add_events( m_pWnd, GDK_BUTTON_PRESS_MASK );
		
		gtk_widget_show_all( m_pWnd );
		
		Display* pDisp = GDK_WINDOW_XDISPLAY( m_pWnd->window );
		::Window id = GDK_WINDOW_XWINDOW( m_pWnd->window );
	
		// Initialize OpenGL.
		MapilInt32 attrs[] = {	GLX_DOUBLEBUFFER,
									GLX_RGBA,
									GLX_RED_SIZE, 8,
									GLX_GREEN_SIZE, 8,
									GLX_BLUE_SIZE, 8,
									GLX_ALPHA_SIZE, 8,
									GLX_DOUBLEBUFFER,
									GLX_DEPTH_SIZE, 16,
									None };
		
		XVisualInfo* pInfo = glXChooseVisual(	pDisp,
													DefaultScreen( pDisp ),
													attrs );
													
		XSetWindowAttributes wndAttr;
		wndAttr.colormap = XCreateColormap(	pDisp,
													id,
													pInfo->visual,
													AllocNone );
		wndAttr.background_pixel = 0;
		wndAttr.border_pixel = 0;
		
		wndAttr.event_mask = StructureNotifyMask | ExposureMask;

		MapilUInt32 mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;		

		m_ID = XCreateWindow(	pDisp,
									id,
									0,
									0,
									m_Width,
									m_Height,
									0,
									pInfo->depth,
									InputOutput,
									pInfo->visual,
									mask,
									&wndAttr );
									
		XMapSubwindows( pDisp, id );
		
		m_Context = glXCreateContext(	pDisp,
											pInfo,
											None,
											True );
											
		m_pDisp = pDisp;
		
		glXMakeCurrent( m_pDisp, m_ID, m_Context );
	}
	
	MapilVoid GTKGraphicsContext::Resize( MapilInt32 height, MapilInt32 width )
	{
		m_Width = width;
		m_Height = height;
		
		gtk_window_resize( GTK_WINDOW( m_pWnd ), m_Height, m_Width );
	}
	
	MapilVoid GTKGraphicsContext::Add()
	{
	}
	
	MapilInt32 GTKGraphicsContext::ProcessMessage()
	{
		while( gtk_events_pending() ){
			gtk_main_iteration();
		}
		
		return 0;
	}
	
	MapilVoid GTKGraphicsContext::Run()
	{
		gtk_main();
	}

	MapilVoid GTKGraphicsContext::Show()
	{
		gtk_widget_show_all( m_pWnd );
	}
	
	MapilVoid GTKGraphicsContext::Connect( ExposeSignal* pSig )
	{
		m_pSig = pSig;
		
		g_signal_connect_after(	G_OBJECT( m_pWnd ),
									"expose_event",
									G_CALLBACK( GTKSignalServer::HandleExpose ),
									pSig );
	}
	
	MapilVoid GTKGraphicsContext::Swap()
	{
		glXSwapBuffers( m_pDisp, m_ID );
		glXMakeCurrent( m_pDisp, m_ID, m_Context );
	}
}

#endif	// API_OPENGL

#endif	// API_GTK
