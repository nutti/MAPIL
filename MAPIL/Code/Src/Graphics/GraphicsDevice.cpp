/**
*	@file	GraphicsDevice.cpp
*	@brief	
*	@date	2011.6.15(Wed) 17:57
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#ifdef API_OPENGL

#ifdef API_WIN32API
#include <Windows.h>
#endif
#ifdef OS_WIN_32BIT
#include <gl/GL.h>
#endif
#ifdef OS_LINUX_32BIT
#include <GL/gl.h>
#endif

#endif

#if defined ( API_DIRECT3D )
#include <d3dx9.h>
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#endif

#if defined ( API_WIN32API )
#include "../../Include/MAPIL/GUI/WinAPIGraphicsContext.h"
#endif

#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	GraphicsDevice::GraphicsDevice( GraphicsAPI api ) :	Device(),
														m_GraphicsAPI( api )
#if defined ( API_DIRECT3D )
		,
		m_pWnd(),
		m_pD3D( NULL ),
		m_pD3DDev( NULL )
#endif
#if defined ( API_OPENGL )
#if defined ( API_WIN32API )
		,
		m_HDC( NULL )
#endif	// API_WIN32API
#endif	// API_OPENGL
	{
#if defined ( API_DIRECT3D )
		if( m_GraphicsAPI == GRAPHICS_API_DIRECT3D ){
			ZeroObject( &m_D3DPPWnd, sizeof( m_D3DPPWnd ) );
			ZeroObject( &m_D3DPPFull, sizeof( m_D3DPPFull ) );
			ZeroObject( &m_D3DPPNow, sizeof( m_D3DPPNow ) );
		}
#endif
#if defined ( API_OPENGL )
#if defined ( API_WIN32API )
		if( m_GraphicsAPI == GRAPHICS_API_OPENGL ){
			ZeroObject( &m_PFD, sizeof( m_PFD ) );
		}
#endif	// API_WIN32API
#endif	// API_OPENGL
	}
	
	GraphicsDevice::~GraphicsDevice()
	{
#if defined ( API_DIRECT3D )
		if( m_GraphicsAPI == GRAPHICS_API_DIRECT3D ){
			ZeroObject( &m_D3DPPWnd, sizeof( m_D3DPPWnd ) );
			ZeroObject( &m_D3DPPFull, sizeof( m_D3DPPFull ) );
			ZeroObject( &m_D3DPPNow, sizeof( m_D3DPPNow ) );
		}
#endif
#if defined ( API_OPENGL )
#if defined ( API_WIN32API )
		if( m_GraphicsAPI == GRAPHICS_API_OPENGL ){
			wglMakeCurrent( m_HDC, 0 );
			wglDeleteContext( m_HRC );
			ZeroObject( &m_PFD, sizeof( m_PFD ) );
		}
#endif	// API_WIN32API
#endif	// API_OPENGL
		m_GraphicsAPI = GRAPHICS_API_UNKNOWN;
	}


	MapilVoid GraphicsDevice::Create( SharedPointer < GraphicsContext > pWnd )
	{
#if defined ( API_DIRECT3D )
		if( m_GraphicsAPI == GRAPHICS_API_DIRECT3D ){
			m_pWnd.DownCast( pWnd );
			SharedPointer < WinAPIWindow > parent;
			parent.DownCast( m_pWnd->GetParentWnd() );
			HWND hWnd = parent->GetHWnd();
			SetWindowLong( hWnd, GWL_STYLE, GetWindowLong( hWnd, GWL_STYLE ) | WS_CLIPCHILDREN );
			InitD3D();
		}
#endif
#if defined ( API_OPENGL )
		if( m_GraphicsAPI == GRAPHICS_API_OPENGL ){
			m_pWnd.DownCast( pWnd );
			InitOpenGL();
		}
#endif
	}

	GraphicsAPI GraphicsDevice::GetGraphicsAPI() const
	{
		return m_GraphicsAPI;
	}

	SharedPointer < GraphicsContext > GraphicsDevice::GetContext()
	{
		return m_pWnd;
	}

	::D3DPRESENT_PARAMETERS GraphicsDevice::GetD3DPP()
	{
		return m_D3DPPNow;
	}

	MapilVoid GraphicsDevice::ChangeWndMode( MapilInt32 mode )
	{
		// Window mode
		if( mode == 0 ){
			m_D3DPPNow = m_D3DPPWnd;
		}
		else if( mode == 1 ){
			m_D3DPPNow = m_D3DPPFull;
		}
	}

#if defined ( API_OPENGL )
	MapilVoid GraphicsDevice::InitOpenGL()
	{
		m_PFD.nSize			= sizeof( PIXELFORMATDESCRIPTOR );		// Size of PIXELFORMATDESCRIPTOR structure.
		m_PFD.nVersion		= 1;									// Version of OpenGL.
		m_PFD.dwFlags		=	PFD_DRAW_TO_WINDOW |				// Draw directly in window.
								PFD_SUPPORT_OPENGL |				// Support OpenGL.
								PFD_DOUBLEBUFFER;					// Use double buffer.
		m_PFD.iPixelType	= PFD_TYPE_RGBA;						// Display pixel with RGBA color.
		m_PFD.dwLayerMask	= PFD_MAIN_PLANE;						// Layer type. Windows must set this value.
		m_PFD.cColorBits	= 32;									// Display by 32bits RGBA.
		m_PFD.cDepthBits	= 16;									// Maintain the distance from the aspect by 16bits.

		m_HDC = GetDC( m_pWnd->GetHWnd() );
		m_PixelFormat = ChoosePixelFormat( m_HDC, &m_PFD );
		SetPixelFormat( m_HDC, m_PixelFormat, &m_PFD );

		m_HRC = wglCreateContext( m_HDC );
		wglMakeCurrent( m_HDC, m_HRC );
	}
#endif


#if defined ( API_DIRECT3D )
	COMPointer < ::IDirect3D9 > GraphicsDevice::GetD3D()
	{
		return m_pD3D;
	}

	COMPointer < ::IDirect3DDevice9 > GraphicsDevice::GetDev()
	{
		return m_pD3DDev;
	}

	//Initialize Direct 3D
	MapilVoid GraphicsDevice::InitD3D()
	{
		//Create Direct 3D object
		IDirect3D9* pD3D = NULL;
		if( !( pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GraphicsDevice" ),
									TSTR( "InitD3D" ),
									TSTR( "Creation of Direct 3D object failed.\n" ),
									-1 );
		}

		COMPointer < IDirect3D9 > p( pD3D );
		m_pD3D = p;

		//Select proper device setting
		UINT adapter;
		D3DDEVTYPE devType;
		SelectDevSetting( &adapter, &devType );

		//Create Direct 3D device object
		CreateD3DDev( adapter, devType );
	}

	//Select proper device setting
	MapilVoid GraphicsDevice::SelectDevSetting( UINT* pAdapter, D3DDEVTYPE* pDevType )
	{
		*pAdapter = D3DADAPTER_DEFAULT;			//Primary display adapter

		//Select proper device ability
		SelectDevAbility( *pAdapter, pDevType );

		D3DDISPLAYMODE dispMode;
		//Decide display setting
		DecideDispSetting( *pAdapter, *pDevType, &dispMode );

		//Select depth and stencil setting
		SelectDepthStencilSetting( *pAdapter, *pDevType, dispMode );

		//Check rendering and texture setting
		CheckRenderingTextureSetting( *pAdapter, *pDevType, dispMode );

		//Select full-scene and anti-aliasing setting
		SelectFullSceneAntiAliasingSetting( *pAdapter, *pDevType );

		//Select display mode
		SelectDispMode( *pAdapter );
	}

	//Select proper device ability
	MapilVoid GraphicsDevice::SelectDevAbility( UINT adapter, D3DDEVTYPE* pDevType )
	{
		D3DCAPS9 caps;			//Structure which store device ability

		//Check HAL device
		*pDevType = D3DDEVTYPE_HAL;
		if( FAILED( m_pD3D.GetPointer()->GetDeviceCaps( adapter, *pDevType, &caps ) ) || FAILED( CheckDevDetailAbility( caps ) ) ){
			//Check REF device
			if( FAILED( m_pD3D.GetPointer()->GetDeviceCaps( adapter, *pDevType, &caps ) ) || FAILED( CheckDevDetailAbility( caps ) ) ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "GraphicsDevice" ),
										TSTR( "SelectDevAbility" ),
										TSTR( "Selection proper device ability failed.\n" ),
										-1 );
			}
		}
	}

	//Check detail device ability
	HRESULT GraphicsDevice::CheckDevDetailAbility( const D3DCAPS9& caps )
	{
		//Check number of vertex stream
		if( caps.MaxStreams < 3 ){
			return E_FAIL;
		}
		//Check number of primitive
		if( caps.MaxPrimitiveCount < 0xffff ){
			return E_FAIL;
		}

		return S_OK;
	}

	//Decide display setting
	MapilVoid GraphicsDevice::DecideDispSetting( UINT adapter, D3DDEVTYPE devType, D3DDISPLAYMODE* pDispMode )
	{
		//Display format list that becomes candidate
		D3DFORMAT dispFmts[] = { D3DFMT_X8R8G8B8, D3DFMT_X1R5G5B5, D3DFMT_R5G6B5 };

		//Get display mode
		if( FAILED( m_pD3D.GetPointer()->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, pDispMode ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GraphicsDevice" ),
									TSTR( "DecideDispSetting" ),
									TSTR( "Failed to get display mode." ),
									-1 );
		}

		//Decide display setting of window mode
		m_D3DPPWnd.BackBufferCount			= 1;								//Number of back buffer
		m_D3DPPWnd.SwapEffect				= D3DSWAPEFFECT_DISCARD;			//Discard back buffer after swap
		m_D3DPPWnd.hDeviceWindow			= m_pWnd->GetHWnd();
		m_D3DPPWnd.Windowed					= TRUE;								//Window mode
		m_D3DPPWnd.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;
		m_D3DPPWnd.Flags					= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
		//Select display format
		MapilBool result = MapilFalse;
		for( MapilInt32 i = 0; i < ( sizeof( dispFmts ) / sizeof( dispFmts[ 0 ] ) ); i++ ){
			if( SUCCEEDED( m_pD3D.GetPointer()->CheckDeviceType( adapter, devType, pDispMode->Format, dispFmts[ i ], TRUE ) ) ){
				m_D3DPPWnd.BackBufferFormat = dispFmts[ i ];
				result = MapilTrue;
				break;
			}
		}
		//Case that display format was not selected
		if( !result ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GraphicsDevice" ),
									TSTR( "DecideDispSetting" ),
									TSTR( "Failed to select display format. ( Window mode. )" ),
									-2 );
		}

		SharedPointer < WinAPIWindow > pWindow;
		pWindow.DownCast( m_pWnd->GetParentWnd() );

		//Decide display setting of full screen mode
		m_D3DPPFull.BackBufferCount			= 1;
		m_D3DPPFull.SwapEffect				= D3DSWAPEFFECT_DISCARD;
		m_D3DPPFull.hDeviceWindow			= //pWindow->GetHWnd();
												m_pWnd->GetHWnd();
		m_D3DPPFull.Windowed				= TRUE;							//Full screen mode
		m_D3DPPFull.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;
		m_D3DPPFull.Flags					= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
		//Select display format
		result = MapilFalse;
		for( MapilInt32 i = 0; i < ( sizeof( dispFmts ) / sizeof( dispFmts[ 0 ] ) ); i++ ){
			if( SUCCEEDED( m_pD3D.GetPointer()->CheckDeviceType( adapter, devType, dispFmts[ i ], dispFmts[ i ], FALSE ) ) ){
				m_D3DPPFull.BackBufferFormat = dispFmts[ i ];
				result = MapilTrue;
				break;
			}
		}
		//Case that display format was not selected
		if( !result ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GraphicsDevice" ),
									TSTR( "DecideDispSetting" ),
									TSTR( "Failed to select display format. ( Full screen mode. )" ),
									-3 );
		}
	}

	//Select depth and stencil setting
	MapilVoid GraphicsDevice::SelectDepthStencilSetting( UINT adapter, D3DDEVTYPE devType, D3DDISPLAYMODE dispMode )
	{
		//Depth and stencil format list that becomes candidate
		D3DFORMAT depthStencilFmt = D3DFMT_D24S8;

		//Select depth and stencil setting of window mode
		if( FAILED( m_pD3D.GetPointer()->CheckDeviceFormat(	adapter,
															devType,
															dispMode.Format,
															D3DUSAGE_DEPTHSTENCIL,
															D3DRTYPE_SURFACE,
															depthStencilFmt ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GraphicsDevice" ),
									TSTR( "SelectDepthStencilSetting" ),
									TSTR( "Failed to select depth and stencil setting. ( Window mode. )" ),
									-1 );
		}
		if( FAILED( m_pD3D.GetPointer()->CheckDepthStencilMatch(	adapter,
																	devType,
																	dispMode.Format,
																	m_D3DPPWnd.BackBufferFormat,
																	depthStencilFmt ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GraphicsDevice" ),
									TSTR( "SelectDepthStencilSetting" ),
									TSTR( "Failed to select depth and stencil setting. ( Window mode. )" ),
									-2 );
		}
		m_D3DPPWnd.EnableAutoDepthStencil = TRUE;
		m_D3DPPWnd.AutoDepthStencilFormat = depthStencilFmt;

		//Select depth and stencil setting of full screen mode
		if( FAILED( m_pD3D.GetPointer()->CheckDeviceFormat(	adapter,
															devType,
															m_D3DPPFull.BackBufferFormat,
															D3DUSAGE_DEPTHSTENCIL,
															D3DRTYPE_SURFACE,
															depthStencilFmt ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GraphicsDevice" ),
									TSTR( "SelectDepthStencilSetting" ),
									TSTR( "Failed to select depth and stencil setting. ( Full screen mode. )" ),
									-3 );
		}
		if( FAILED( m_pD3D.GetPointer()->CheckDepthStencilMatch(	adapter,
																	devType,
																	m_D3DPPFull.BackBufferFormat,
																	m_D3DPPFull.BackBufferFormat,
																	depthStencilFmt ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GraphicsDevice" ),
									TSTR( "SelectDepthStencilSetting" ),
									TSTR( "Failed to select depth and stencil setting. ( Full screen mode. )" ),
									-4 );
		}
		m_D3DPPFull.EnableAutoDepthStencil = TRUE;
		m_D3DPPFull.AutoDepthStencilFormat = depthStencilFmt;
	}

	//Check rendering and texture setting
	MapilVoid GraphicsDevice::CheckRenderingTextureSetting( UINT adapter, D3DDEVTYPE devType, D3DDISPLAYMODE dispMode )
	{
		//Depth and stencil format list that becomes candidate
		D3DFORMAT depthStencilFmt = D3DFMT_D24S8;
		//Rendering and texture format list that becomes candidate
		D3DFORMAT renderingTextureFmts[] = { D3DFMT_X8R8G8B8, D3DFMT_X1R5G5B5, D3DFMT_R5G6B5 };

		//Check rendering and texture setting of window mode
		MapilBool result = MapilFalse;
		for( MapilInt32 i = 0; i < ( sizeof( renderingTextureFmts ) / sizeof( renderingTextureFmts[ 0 ] ) ); i++ ){
			if( SUCCEEDED( m_pD3D.GetPointer()->CheckDeviceFormat(	adapter,
																	devType,
																	dispMode.Format,
																	D3DUSAGE_RENDERTARGET,
																	D3DRTYPE_TEXTURE,
																	renderingTextureFmts[ i ] ) ) ){
				if( SUCCEEDED( m_pD3D.GetPointer()->CheckDepthStencilMatch(	adapter,
																			devType,
																			dispMode.Format,
																			renderingTextureFmts[ i ],
																			depthStencilFmt ) ) ){
					result = MapilTrue;
				}
			}
		}
		//Case that display format was not selected
		if( !result ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GraphicsDevice" ),
									TSTR( "CheckRenderingTextureSetting" ),
									TSTR( "Failed to select display format. ( Window mode. )" ),
									-1 );
		}

		//Check rendering and texture setting of full screen mode
		result = MapilFalse;
		for( MapilInt32 i = 0; i < ( sizeof( renderingTextureFmts ) / sizeof( renderingTextureFmts[ 0 ] ) ); i++ ){
			if( SUCCEEDED( m_pD3D.GetPointer()->CheckDeviceFormat(	adapter,
																	devType,
																	m_D3DPPFull.BackBufferFormat,
																	D3DUSAGE_RENDERTARGET,
																	D3DRTYPE_TEXTURE,
																	renderingTextureFmts[ i ] ) ) ){
				if( SUCCEEDED( m_pD3D.GetPointer()->CheckDepthStencilMatch(	adapter,
																			devType,
																			m_D3DPPFull.BackBufferFormat,
																			renderingTextureFmts[ i ],
																			depthStencilFmt ) ) ){
					result = MapilTrue;
				}
			}
		}
		//Case that display format was not selected
		if( !result ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GraphicsDevice" ),
									TSTR( "CheckRenderingTextureSetting" ),
									TSTR( "Failed to select display format. ( Full screen mode. )" ),
									-2 );
		}
	}

	//Select full-scene and anti-aliasing setting
	MapilVoid GraphicsDevice::SelectFullSceneAntiAliasingSetting( UINT adapter, D3DDEVTYPE devType )
	{
		//Multisample list that becomes candidate
		D3DMULTISAMPLE_TYPE multiSampleTypes[] = {	D3DMULTISAMPLE_4_SAMPLES,
													D3DMULTISAMPLE_3_SAMPLES,
													D3DMULTISAMPLE_2_SAMPLES,
													D3DMULTISAMPLE_NONE };

		DWORD quality;

		//Select full-scene and and anti-aliasing setting of window mode
		for( MapilInt32 i = 0; i < ( sizeof( multiSampleTypes ) / sizeof( multiSampleTypes[ 0 ] ) ); i++ ){
			if( SUCCEEDED( m_pD3D.GetPointer()->CheckDeviceMultiSampleType(	adapter,
																			devType,
																			m_D3DPPWnd.BackBufferFormat,
																			TRUE,
																			multiSampleTypes[ i ],
																			&quality ) ) ){
				if( m_D3DPPWnd.EnableAutoDepthStencil ){
					if( SUCCEEDED( m_pD3D.GetPointer()->CheckDeviceMultiSampleType(	adapter,
																					devType,
																					m_D3DPPWnd.AutoDepthStencilFormat,
																					TRUE,
																					multiSampleTypes[ i ],
																					NULL ) ) ){
						m_D3DPPWnd.MultiSampleType = multiSampleTypes[ i ];
						m_D3DPPWnd.MultiSampleQuality = quality -1;
						break;
					}
				}
				else{
					m_D3DPPWnd.MultiSampleType = multiSampleTypes[ i ];
					m_D3DPPWnd.MultiSampleQuality = quality - 1;
					break;
				}
			}
		}

		//Select full-scene and anti-aliasing setting of full screen mode
		for( MapilInt32 i = 0; i < ( sizeof( multiSampleTypes ) / sizeof( multiSampleTypes[ 0 ] ) ); i++ ){
			if( SUCCEEDED( m_pD3D.GetPointer()->CheckDeviceMultiSampleType(	adapter,
																			devType,
																			m_D3DPPFull.BackBufferFormat,
																			FALSE,
																			multiSampleTypes[ i ],
																			&quality ) ) ){
				if( m_D3DPPWnd.EnableAutoDepthStencil ){
					if( SUCCEEDED( m_pD3D.GetPointer()->CheckDeviceMultiSampleType(	adapter,
																					devType,
																					m_D3DPPFull.AutoDepthStencilFormat,
																					FALSE,
																					multiSampleTypes[ i ],
																					NULL ) ) ){
						m_D3DPPFull.MultiSampleType = multiSampleTypes[ i ];
						m_D3DPPFull.MultiSampleQuality = quality - 1;
						break;
					}
				}
				else{
					m_D3DPPFull.MultiSampleType = multiSampleTypes[ i ];
					m_D3DPPFull.MultiSampleQuality = quality - 1;
					break;
				}
			}
		}
	}

	//Select display mode
	MapilVoid GraphicsDevice::SelectDispMode( UINT adapter )
	{
		//Check of window mode isn't necessary, so only check of full screen mode is done
		D3DDISPLAYMODE dispMode = { 0, 0, 0, D3DFMT_UNKNOWN };
		MapilInt32 level = 100000000;		//Big value is substituted so as to compare correctly
		MapilInt32 num = m_pD3D.GetPointer()->GetAdapterModeCount( adapter, m_D3DPPFull.BackBufferFormat );
		for( MapilInt32 i = 0; i < num; i++ ){
			D3DDISPLAYMODE dispModeBuf;
			m_pD3D.GetPointer()->EnumAdapterModes( adapter, m_D3DPPFull.BackBufferFormat, i, &dispModeBuf );
			//Select proper mode
			MapilInt32 buf = abs( static_cast < int > ( m_pWnd->GetWidth() - dispModeBuf.Width ) ) + abs( static_cast < int > ( m_pWnd->GetHeight() - dispModeBuf.Height ) );
			if( buf < level ){
				dispMode = dispModeBuf;
				level = buf;
			}
		}
		if( dispMode.Format == D3DFMT_UNKNOWN ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GraphicsDevice" ),
									TSTR( "SelectDispMode" ),
									TSTR( "Failed to select display mode." ),
									-2 );
		}
		m_D3DPPFull.BackBufferWidth = dispMode.Width;
		m_D3DPPFull.BackBufferHeight = dispMode.Height;
	}

	//Create Direct 3D device object
	MapilVoid GraphicsDevice::CreateD3DDev( UINT adapter, D3DDEVTYPE devType )
	{
		//Select D3DPRESENT_PARAMETERS structure
		m_D3DPPNow = ( m_pWnd->IsWndMode() ? m_D3DPPWnd : m_D3DPPFull );

		//Create device
		if( FAILED( m_pD3D.GetPointer()->CreateDevice(	adapter,
														devType,
														m_pWnd->GetHWnd(),
														D3DCREATE_HARDWARE_VERTEXPROCESSING,
														&m_D3DPPNow,
														m_pD3DDev.GetPointerOfPointerWithChange() ) ) ){
			if( FAILED( m_pD3D.GetPointer()->CreateDevice(	adapter,
															devType,
															m_pWnd->GetHWnd(),
															D3DCREATE_SOFTWARE_VERTEXPROCESSING,
															&m_D3DPPNow,
															m_pD3DDev.GetPointerOfPointerWithChange() ) ) ){
				throw MapilException(	TSTR( "Mapil" ),
										TSTR( "GraphicsDevice" ),
										TSTR( "CreateD3DDev" ),
										TSTR( "Failed to create Direct 3D device object." ),
										-1 );
			}
		}

		InitRenderState();
	}

	//Initialize render state.
	MapilVoid GraphicsDevice::InitRenderState()
	{
		m_pD3DDev.GetPointer()->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
		m_pD3DDev.GetPointer()->SetRenderState( D3DRS_LIGHTING, FALSE );
		m_pD3DDev.GetPointer()->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
		m_pD3DDev.GetPointer()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
	}

#endif

	IGraphicsDevice CreateGraphicsDevice( GraphicsAPI api )
	{
		SharedPointer < GraphicsDevice > pGD( new GraphicsDevice( api ) );

		return pGD;
	}

}
