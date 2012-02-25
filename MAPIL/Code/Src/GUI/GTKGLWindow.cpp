/**
*	@file	GTKGLWindow.cpp
*	@brief	
*	@date	2011.6.15(Wed) 8:12
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_GTK
#ifdef API_OPENGL

#include "../../Include/MAPIL/GUI/GTKGLWindow.h"
#include "../../Include/MAPIL/GUI/GTKSignalServer.h"

namespace MAPIL
{
	GTKGLWindow::GTKGLWindow() : GTKWindow(), m_pDrawArea( NULL )
	{
	}
	
	GTKGLWindow::~GTKGLWindow()
	{
	}
	
	MapilVoid GTKGLWindow::Init()
	{
		m_pDrawArea = gtk_drawing_area_new();
		gtk_widget_set_size_request( m_pDrawArea, m_Width, m_Height );
		gtk_box_pack_start( GTK_BOX( m_pVBox ), m_pDrawArea, TRUE, TRUE, 0 );
		gtk_widget_add_events( m_pDrawArea, GDK_BUTTON_PRESS_MASK );
		
		gtk_widget_show_all( m_pWnd );
		
		InitOpenGL(	GDK_WINDOW_XDISPLAY( m_pDrawArea->window ),
						GDK_WINDOW_XWINDOW( m_pDrawArea->window ) );
		
		g_signal_connect_after(	G_OBJECT( m_pWnd ),
									"destroy",
									G_CALLBACK( gtk_main_quit ),
									NULL );
	}
	
	MapilVoid GTKGLWindow::InitOpenGL( Display* pDisp, ::Window id )
	{
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
	
	MapilVoid GTKGLWindow::Connect( ExposeSignal* pSig )
	{
		m_pSig = pSig;

		g_signal_connect_after(	G_OBJECT( m_pWnd ),
									"expose_event",
									G_CALLBACK( GTKSignalServer::HandleExpose ),
									pSig );
	}
	
	Display* GTKGLWindow::GetDisplay() const
	{
		return m_pDisp;
	}
	
	::Window GTKGLWindow::GetWndID() const
	{
		return m_ID;
	}
	
	GLXContext GTKGLWindow::GetContext() const
	{
		return m_Context;
	}
	
	MapilInt32 GTKGLWindow::ProcessMessage()
	{
		while( gtk_events_pending() ){
			gtk_main_iteration();
		}
		
		return 0;
	}
	
	gint GTKGLWindow::cb_expose( GtkWidget* widget, GdkEventExpose* event, gpointer data )
	{
		GTKGLWindow* win = ( GTKGLWindow* )( data );
	
		glXMakeCurrent( win->m_pDisp, win->m_ID, win->m_Context);
		glViewport( 0,
			      0,
			      win->GetWidth(),
			      win->GetHeight());

	  // テスト用に緑色で塗りつぶします
	  glClearColor(0, 1, 0, 0);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	  glFlush();
	  glXSwapBuffers(win->m_pDisp, win->m_ID);


	  return 0;
	}
}

#endif	// API_OPENGL
#endif	// API_GTK