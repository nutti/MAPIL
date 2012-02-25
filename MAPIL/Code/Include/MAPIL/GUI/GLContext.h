/**
*	@file	GLContext.h
*	@brief	
*	@date	2011.7.10(Sun) 11:55
*/

#ifndef INCLUDED_MAPIL_GLCONTEXT_H
#define INCLUDED_MAPIL_GLCONTEXT_H

#include "../CrossPlatform.h"

#ifdef API_OPENGL

#include "Control.h"
#include "../Util/SharedPointer.hpp"
#include "../Type.h"

namespace MAPIL
{
	class ExposeSignal;
	class Window;
	class GLContext : public Control
	{
	public:
		GLContext();
		virtual ~GLContext();
		virtual MapilVoid Create(	MapilInt32* argc,
									MapilChar** argv[],
									MapilInt32 height,
									MapilInt32 width ) = 0;
		virtual MapilVoid Create(	MapilInt32* argc,
									MapilChar** argv[],
									MapilInt32 height,
									MapilInt32 width,
									SharedPointer < Window > pParent ) = 0;
		virtual MapilVoid Resize( MapilInt32 height, MapilInt32 width ) = 0;
		virtual MapilVoid Add() = 0;
		virtual MapilInt32 ProcessMessage() = 0;
		virtual MapilVoid Run() = 0;
		virtual MapilVoid Show() = 0;
		virtual MapilVoid Connect( ExposeSignal* pSig ) = 0;
		virtual MapilVoid Swap() = 0;
	};
}

#endif	// API_OPENGL

#endif