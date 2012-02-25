/**
*	@file	GTKSignalServer.cpp
*	@brief	
*	@date	2011.6.17(Fri) 16:21
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_GTK

#include "../../Include/MAPIL/GUI/GTKSignalServer.h"
#include "../../Include/MAPIL/GUI/ExposeSignal.h"

namespace MAPIL
{
	GTKSignalServer::GTKSignalServer() : SignalServer()
	{
	}
	
	GTKSignalServer::~GTKSignalServer()
	{
	}
	
	MapilVoid GTKSignalServer::HandleExpose( GtkWidget* pWidget, GdkEventExpose* pEvent, gpointer p )
	{
		ExposeSignal* pSig = static_cast < ExposeSignal* > ( p );
		pSig->Handle();
	}
	
	MapilVoid GTKSignalServer::HandleButtonPress( GtkWidget* pWidget, GdkEvent* pEvent, gpointer p )
	{
	}
	
	MapilVoid GTKSignalServer::HandleSizeAlloc( GtkWidget* pWidget, GtkAllocation* pAlloc )
	{
	}
}

#endif	// API_GTK
