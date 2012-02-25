/**
*	@file	GTKWindow.cpp
*	@brief	
*	@date	2011.6.15(Wed) 8:12
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_GTK

#include "../../Include/MAPIL/GUI/GTKWindow.h"

namespace MAPIL
{
	GTKWindow::GTKWindow() : Window(), m_pWnd( NULL ), m_pVBox( NULL )
	{
	}
	
	GTKWindow::~GTKWindow()
	{
	}
	
	MapilVoid GTKWindow::Init()
	{
	}
	
	MapilVoid GTKWindow::Create( MapilInt32* argc, MapilChar** argv[], MapilInt32 height, MapilInt32 width )
	{
		m_Width = width;
		m_Height = height;
		
		// Initialize GTK.
		gtk_init( argc, argv );
		gtk_set_locale();
		
		// Create root window.
		m_pWnd = gtk_window_new( GTK_WINDOW_TOPLEVEL );
		gtk_window_resize( GTK_WINDOW( m_pWnd ), m_Height, m_Width );
		
		// Create vertical packing box.
		m_pVBox = gtk_vbox_new( FALSE, 2 );
		gtk_container_add( GTK_CONTAINER( m_pWnd ), m_pVBox );
		
		GtkWidget* menubar = gtk_drawing_area_new();
		gtk_box_pack_start( GTK_BOX( m_pVBox ), menubar, FALSE, FALSE, 0 );
		
		gtk_widget_show_all( m_pWnd );
		
		Init();
	}
	
	MapilVoid GTKWindow::Resize( MapilInt32 height, MapilInt32 width )
	{
		m_Width = width;
		m_Height = height;
	
		gtk_window_resize( GTK_WINDOW( m_pWnd ), m_Height, m_Width );
	}
	
	MapilVoid GTKWindow::Add()
	{
	}
	
	MapilInt32 GTKWindow::ProcessMessage()
	{
	}
	
	MapilVoid GTKWindow::Run()
	{
		gtk_main();
	}
	
	MapilVoid GTKWindow::Show()
	{
		gtk_widget_show_all( m_pWnd );
	}
	
	MapilVoid GTKWindow::Connect( ExposeSignal* pSig )
	{
	}
	
	MapilVoid GTKWindow::Connect( KeyboardSignal* pSig )
	{
	}
	
	MapilVoid GTKWindow::SetWndMode( MapilInt32 mode )
	{
	}
	
	GtkWidget* GTKWindow::GetVBox()
	{
		return m_pVBox;
	}
	
	MapilVoid GTKWindow::ChangePosToClient(	const Vector2 < MapilInt32 >& in,
													Vector2 < MapilInt32 >* pOut )
	{
	}
	
	MapilVoid GTKWindow::ChangePosToScreen(	const Vector2 < MapilInt32 >& in,
													Vector2 < MapilInt32 >* pOut )
	{
	}
}

#endif	// API_GTK
