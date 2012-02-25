/**
*	@file	GTKSignalServer.h
*	@brief	
*	@date	2011.6.17(Fri) 16:21
*/

#ifndef INCLUDED_MAPIL_GTKSIGNALSERVER_H
#define INCLUDED_MAPIL_GTKSIGNALSERVER_H

#include "../CrossPlatform.h"

#ifdef API_GTK

#include <gtk/gtk.h>

#include "SignalServer.h"
#include "../Type.h"

namespace MAPIL
{
	class GTKSignalServer : public SignalServer
	{
	public:
		GTKSignalServer();
		virtual ~GTKSignalServer();
		static MapilVoid HandleExpose( GtkWidget* pWidget, GdkEventExpose* pEvent, gpointer p );
		static MapilVoid HandleButtonPress( GtkWidget* pWidget, GdkEvent* pEvent, gpointer p );
		static MapilVoid HandleSizeAlloc( GtkWidget* pWidget, GtkAllocation* pAlloc );
	};
}

#endif	// API_GTK

#endif