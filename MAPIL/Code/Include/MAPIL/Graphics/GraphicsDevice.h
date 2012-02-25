/**
*	@file	GraphicsDevice.h
*	@brief	
*	@date	2011.6.15(Wed) 17:57
*/

#ifndef INCLUDED_MAPIL_GRAPHICSDEVICE_H
#define INCLUDED_MAPIL_GRAPHICSDEVICE_H

#include "../CrossPlatform.h"

#include "../Type.h"
#include "../Util/Device.h"
#include "../Util/Color.hpp"
#include "ConstNums.h"
#include "../Util/SharedPointer.hpp"

#if defined ( API_DIRECT3D )
#include <d3dx9.h>
#include "../Util/COMPointer.hpp"
#endif

#if defined ( API_WIN32API )
#include <Windows.h>
#include "../GUI/WinAPIGraphicsContext.h"
#endif

namespace MAPIL
{
	enum GraphicsAPI
	{
		GRAPHICS_API_UNKNOWN	= 0,
		GRAPHICS_API_DIRECT3D	= 1,
		GRAPHICS_API_OPENGL		= 2,
	};

	class GraphicsDevice : public Device
	{
#if defined ( API_DIRECT3D )
		friend class D3DGraphicsController;
		//SharedPointer < WinAPIGraphicsContext >		m_pWnd;
		COMPointer < ::IDirect3D9 >					m_pD3D;
		COMPointer < ::IDirect3DDevice9 >			m_pD3DDev;
		D3DPRESENT_PARAMETERS						m_D3DPPWnd;					//D3DPRESENT_PARAMETERS structure for window mode
		D3DPRESENT_PARAMETERS						m_D3DPPFull;				//D3DPRESENT_PARAMETERS structure for full screen mode
		D3DPRESENT_PARAMETERS						m_D3DPPNow;					//D3DPRESENT_PARAMETERS structure used now
		RECT										m_LastWndPos;				//Final window position
		//Initialize Direct 3D
		MapilVoid InitD3D();
		//Select proper device setting
		MapilVoid SelectDevSetting( UINT* pAdapter, D3DDEVTYPE* pDevType );
		//Select proper device ability
		MapilVoid SelectDevAbility( UINT adapter, D3DDEVTYPE* pDevType );
		//Check detail device ability
		virtual HRESULT CheckDevDetailAbility( const D3DCAPS9& caps );
		//Decide display setting
		MapilVoid DecideDispSetting( UINT adapter, D3DDEVTYPE devType, D3DDISPLAYMODE* pDispMode );
		//Select depth and stencil setting
		MapilVoid SelectDepthStencilSetting( UINT adapter, D3DDEVTYPE devType, D3DDISPLAYMODE dispMode );
		//Check rendering and texture setting
		MapilVoid CheckRenderingTextureSetting( UINT adapter, D3DDEVTYPE devType, D3DDISPLAYMODE dispMode );
		//Select full-scene and anti-aliasing setting
		MapilVoid SelectFullSceneAntiAliasingSetting( UINT adapter, D3DDEVTYPE devType );
		//Select display mode
		MapilVoid SelectDispMode( UINT adapter );
		//Create Direct 3D device object
		MapilVoid CreateD3DDev( UINT adapter, D3DDEVTYPE devType );
		//Initialize render state.
		MapilVoid InitRenderState();
#endif
#if defined ( API_OPENGL )
		friend class GLGraphicsController;
#if defined ( API_WIN32API )
		SharedPointer < WinAPIGraphicsContext >		m_pWnd;
		::HDC										m_HDC;
		MapilInt32									m_PixelFormat;
		::PIXELFORMATDESCRIPTOR						m_PFD;
		HGLRC										m_HRC;
#endif	// API_WIN32API
		MapilVoid InitOpenGL();
#endif	// API_OPENGL
		GraphicsAPI				m_GraphicsAPI;
	public:
		GraphicsDevice( GraphicsAPI api );
		virtual ~GraphicsDevice();
#if defined ( API_DIRECT3D )
		COMPointer < ::IDirect3D9 > GetD3D();
		COMPointer < ::IDirect3DDevice9 > GetDev();
		::D3DPRESENT_PARAMETERS GetD3DPP();
		MapilVoid ChangeWndMode( MapilInt32 mode );
#endif
		MapilVoid Create( SharedPointer < GraphicsContext > pWnd );
		GraphicsAPI GetGraphicsAPI() const;
		SharedPointer < GraphicsContext > GetContext();
	};

	typedef SharedPointer < GraphicsDevice >		IGraphicsDevice;

	

	IGraphicsDevice CreateGraphicsDevice( GraphicsAPI api );
}

#endif
