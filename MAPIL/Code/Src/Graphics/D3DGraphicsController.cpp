/**
*	@file	D3DGraphicsController.cpp
*	@brief	Implementation of D3DGraphicsController.
*	@date	2011.8.26 (Fri) 22:23
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "../../Include/MAPIL/Graphics/D3DGraphicsController.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Math/Transformation.hpp"
#include "../../Include/MAPIL/Graphics/GraphicsFactory.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DGraphicsController::D3DGraphicsController( SharedPointer < GraphicsDevice > pDev ) :	GraphicsController( pDev ),
																							m_DoesDevLost( MapilFalse ),
																						//	m_DoesDispChangeNext( MapilFalse ),
																							m_IsZBufferEnable( MapilFalse ),
																							m_IsLightEnable( MapilFalse ),
																							m_IsAlphaBlendEnable( MapilFalse ),
																							m_IsFogEnable( MapilFalse ),
																							m_AlphaBlendMode( ALPHA_BLEND_MODE_DISABLED ),
																							m_CullMode( CULL_MODE_DISABLED ),
																							m_pGC(),
																							m_pGraphicsFactory( NULL )
	{
	}

	D3DGraphicsController::~D3DGraphicsController()
	{
		m_DoesDevLost = MapilFalse;
		m_IsZBufferEnable = MapilFalse;
		m_IsLightEnable = MapilFalse;
		m_IsAlphaBlendEnable = MapilFalse;
		m_IsFogEnable = MapilFalse;
		m_AlphaBlendMode = ALPHA_BLEND_MODE_DISABLED;
		m_CullMode = CULL_MODE_DISABLED;
		m_pGraphicsFactory = NULL;
	}

	MapilVoid D3DGraphicsController::Create( SharedPointer < GraphicsContext > pGC )
	{
		m_pGC = pGC;
	}

	MapilBool D3DGraphicsController::RestoreLostDev()
	{
		if( !m_pDev->m_pD3D.GetPointer() || !m_pDev->GetDev().GetPointer() ){
			OutputDebugString( TSTR( "-----test:0\n" ) );
			return MapilFalse;
		}
		SharedPointer < WinAPIWindow > pWnd;
		pWnd.DownCast( m_pDev->m_pWnd->GetParentWnd() );

		if( !pWnd->IsActive() ){
			return MapilTrue;
		}

		//Procedure when lost device
		if( m_DoesDevLost ){
			Sleep( 100 );		//Wait 100 milli seconds
			//Check device status
			HRESULT hr = m_pDev->GetDev().GetPointer()->TestCooperativeLevel();
			if( FAILED( hr ) ){
				if( hr == D3DERR_DEVICELOST ){
					return MapilTrue;			//Device lost now
				}
				if( hr != D3DERR_DEVICENOTRESET ){
					return MapilFalse;			//Unexpected error occured(Termination procedure)
				}
				LostResource();
				//Restoration procedure
				hr = m_pDev->GetDev().GetPointer()->Reset( &m_pDev->m_D3DPPNow );
				if( FAILED( hr ) ){
					if( hr == D3DERR_DEVICELOST ){
						return MapilTrue;		//Device lost now
					}
					else if( hr == D3DERR_DRIVERINTERNALERROR ){
						return MapilFalse;			//Restoration of device failed
					}
					else if( hr == D3DERR_INVALIDCALL ){
						return MapilFalse;			//Restoration of device failed
					}
					else if( hr == D3DERR_OUTOFVIDEOMEMORY ){
						return MapilFalse;			//Restoration of device failed
					}
					else if( hr == E_OUTOFMEMORY ){
						return MapilFalse;			//Restoration of device failed
					}
					return MapilFalse;			//Restoration of device failed
				}
				RestoreResource();
				RestoreRenderState();
			}
			m_DoesDevLost = MapilFalse;
		}

		return MapilTrue;
	}

	MapilVoid D3DGraphicsController::LostResource()
	{
		m_pGraphicsFactory->LostAllResources();
	}

	MapilVoid D3DGraphicsController::RestoreResource()
	{
		m_pGraphicsFactory->RestoreAllResources();
	}

	MapilVoid D3DGraphicsController::RestoreRenderState()
	{
		EnableZBuffer( m_IsZBufferEnable );
		EnableLight( m_IsLightEnable );
		EnableBlend( m_IsAlphaBlendEnable );
		EnableFog( m_IsFogEnable );
		SetCullMode( m_CullMode );
		SetAlphaBlendMode( m_AlphaBlendMode );
	}

	// Begin rendering
	MapilVoid D3DGraphicsController::BeginRendering()
	{
		//Change display mode
		//if( m_DoesDispChangeNext ){
			//ChangeDispMode();
	//	}

		//Check lost device
		if( !RestoreLostDev() ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DGraphicsController" ),
									TSTR( "BeginRendering" ),
									TSTR( "Failed to restore lost device." ),
									-1 );
		}

		//Clear background
		m_pDev->GetDev().GetPointer()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );

		if( FAILED( m_pDev->GetDev().GetPointer()->BeginScene() ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DGraphicsController" ),
									TSTR( "BeginRendering" ),
									TSTR( "Failed to begin scene." ),
									-2 );
		}
	}

	// End rendering
	MapilVoid D3DGraphicsController::EndRendering()
	{
		//Finish rendering
		if( FAILED( m_pDev->GetDev().GetPointer()->EndScene() ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DGraphicsController" ),
									TSTR( "EndRendering" ),
									TSTR( "Failed to end scene." ),
									-1 );
		}

		HRESULT hr = m_pDev->GetDev().GetPointer()->Present( NULL, NULL, NULL, NULL );

		if( hr == D3DERR_DEVICELOST ){
			m_DoesDevLost = MapilTrue;
		}
		else if( FAILED( hr ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DGraphicsController" ),
									TSTR( "EndRendering" ),
									TSTR( "Failed to present." ),
									-2 );
		}
	}

	// Set viewport
	MapilVoid D3DGraphicsController::SetViewport(	MapilInt32 x,
													MapilInt32 y,
													MapilInt32 width,
													MapilInt32 height )
	{
		D3DVIEWPORT9 vp;
		vp.X		= 0;
		vp.Y		= 0;
		vp.Width	= m_pDev->m_D3DPPNow.BackBufferWidth;
		vp.Height	= m_pDev->m_D3DPPNow.BackBufferHeight;
		vp.MinZ		= 0.0f;
		vp.MaxZ		= 1.0f;

		if( FAILED( m_pDev->GetDev().GetPointer()->SetViewport( &vp ) ) ){
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "D3DGraphicsController" ),
									TSTR( "SetViewport" ),
									TSTR( "Failed to set view port." ),
									-1 );
		}
	}

	// Enable z buffer
	MapilVoid D3DGraphicsController::EnableZBuffer( MapilBool status )
	{
		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_ZENABLE, status ? D3DZB_TRUE : D3DZB_FALSE );
		m_IsZBufferEnable = status;
	}

	// Enable light
	MapilVoid D3DGraphicsController::EnableLight( MapilBool status )
	{
		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_LIGHTING, status ? TRUE : FALSE );
		m_IsLightEnable = status;
	}

	// Enable blend
	MapilVoid D3DGraphicsController::EnableBlend( MapilBool status )
	{
		m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_ALPHABLENDENABLE, status ? TRUE : FALSE );
		m_IsAlphaBlendEnable = status;
	}

	// Enable fog.
	MapilVoid D3DGraphicsController::EnableFog( MapilBool status )
	{
		m_pDev->GetDev().GetPointer()->SetRenderState( ::D3DRS_FOGENABLE, status ? TRUE : FALSE );
		m_IsFogEnable = status;
	}

	// Set alpha blend mode
	MapilVoid D3DGraphicsController::SetAlphaBlendMode( MapilInt32 mode )
	{
		switch( mode ){
			case ALPHA_BLEND_MODE_NO_TRANSPARENT:			//No transparent (SRC*RGBA(1,1,1,1)+DEST*RGBA(0,0,0,0))
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO );
				break;
			case ALPHA_BLEND_MODE_SEMI_TRANSPARENT:			//Semi transparent (SRC*RGBA(a,a,a,a)+DEST*RGBA(1-a,1-a,1-a,1-a))
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
				break;
			case ALPHA_BLEND_MODE_ADD:						//Addition (SRC*RGBA(1,1,1,1)+DEST*RGBA(1,1,1,1))
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
				break;
			case ALPHA_BLEND_MODE_ADD_SEMI_TRANSPARENT:		//Addition and semi transparent (SRC*RGBA(a,a,a,a)+DEST*RGBA(1,1,1,1))
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
				break;
			case ALPHA_BLEND_MODE_SUBTRACT:					//Subtraction (DEST*(1-SRC)-SRC*RGBA(0,0,0,0))
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR );
				break;
			case ALPHA_BLEND_MODE_MULTIPLY_1:				//Multiplication 1 (SRC*RGBA(0,0,0,0)+DEST*SRC)
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR );
				break;
			case ALPHA_BLEND_MODE_MULTIPLY_2:				//Multiplication 2 (SRC*DEST+DEST*SRC)
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR );
				break;
			case ALPHA_BLEND_MODE_SCREEN:					//Screen (SRC*(1-DEST)+DEST*RGBA(1,1,1,1))
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
				break;
			case ALPHA_BLEND_MODE_REVERSE:					//Reverse (SRC*(1-DEST)+DEST*(1-SRC))
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR );
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR );
				break;
			default:
				break;
		}

		m_AlphaBlendMode = mode;
	}

	// Set cull mode
	MapilVoid D3DGraphicsController::SetCullMode( MapilInt32 mode )
	{
		switch( mode ){
			case CULL_MODE_DISABLED:			//Disabled
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
				break;
			case CULL_MODE_CLOCKWISE:			//Clockwise
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
				break;
			case CULL_MODE_COUNTERCLOCKWISE:	//Counterclockwise
				m_pDev->GetDev().GetPointer()->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
				break;
			default:
				break;
		}

		m_CullMode = mode;
	}

	// Set texture mode
	MapilVoid D3DGraphicsController::SetTextureMode( MapilInt32 mode )
	{
	}

	// Set fog parameter.
	MapilVoid D3DGraphicsController::SetFogParam(	const ColorARGB < MapilFloat32 >& color,
													MapilInt32 mode,
													MapilFloat32 begin,
													MapilFloat32 end,
													MapilFloat32 density )
	{
		SetFogParam(	GetColorARGBValue( color.m_A, color.m_R, color.m_G, color.m_B ), mode,
						begin, end, density );
	}

	MapilVoid D3DGraphicsController::SetFogParam(	const ColorARGB < MapilUChar >& color,
													MapilInt32 mode,
													MapilFloat32 begin,
													MapilFloat32 end,
													MapilFloat32 density )
	{
		SetFogParam( GetColorARGBValue( color.m_A, color.m_R, color.m_G, color.m_B ), mode, begin, end, density );
	}

	MapilVoid D3DGraphicsController::SetFogParam(	MapilUInt32 color,
													MapilInt32 mode,
													MapilFloat32 begin,
													MapilFloat32 end,
													MapilFloat32 density )
	{
		m_pDev->GetDev().GetPointer()->SetRenderState(	::D3DRS_FOGCOLOR, color );
		m_pDev->GetDev().GetPointer()->SetRenderState( ::D3DRS_FOGSTART, TransformFloatIntoDWORD( begin ) );
		m_pDev->GetDev().GetPointer()->SetRenderState( ::D3DRS_FOGEND, TransformFloatIntoDWORD( end ) );
		m_pDev->GetDev().GetPointer()->SetRenderState( ::D3DRS_FOGDENSITY, TransformFloatIntoDWORD( density ) );
		
		switch( mode ){
			case FOG_MODE_LINEAR:
				m_pDev->GetDev().GetPointer()->SetRenderState( ::D3DRS_FOGVERTEXMODE, ::D3DFOG_LINEAR );
				break;
			case FOG_MODE_EXP:
				m_pDev->GetDev().GetPointer()->SetRenderState( ::D3DRS_FOGVERTEXMODE, ::D3DFOG_EXP );
				break;
			case FOG_MODE_EXP2:
				m_pDev->GetDev().GetPointer()->SetRenderState( ::D3DRS_FOGVERTEXMODE, ::D3DFOG_EXP2 );
				break;
			default:
				m_pDev->GetDev().GetPointer()->SetRenderState( ::D3DRS_FOGVERTEXMODE, ::D3DFOG_NONE );
				m_pDev->GetDev().GetPointer()->SetRenderState( ::D3DRS_FOGTABLEMODE, ::D3DFOG_NONE );
				break;
		}
	}

	// Set vsync.
	MapilVoid D3DGraphicsController::EnableVSync( MapilBool status )
	{
	}


	MapilVoid D3DGraphicsController::CaptureScreen( const MapilTChar* pFileName )
	{
		::D3DDISPLAYMODE dispMode;

		if( FAILED( m_pDev->GetD3D().GetPointer()->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &dispMode ) ) ){
			throw MapilException(	TSTR( "MAPIL" ),
									TSTR( "D3DGraphicsController" ),
									TSTR( "CaptureScreen" ),
									TSTR( "Failed to get display mode." ),
									-1 );
		}

		// Create surface which will be used in capture
		::LPDIRECT3DSURFACE9 pSurface;
		if( FAILED( m_pDev->GetDev().GetPointer()->CreateOffscreenPlainSurface(	dispMode.Width,
																				dispMode.Height,
																				D3DFMT_A8R8G8B8,		//32bit format
																				D3DPOOL_SCRATCH,
																				&pSurface,
																				NULL ) ) ){
			throw MapilException(	TSTR( "MAPIL" ),
									TSTR( "D3DManager" ),
									TSTR( "ScreenCapture" ),
									TSTR( "Failed to create surface." ),
									-2 );
		}
		//Capture
		if( FAILED( m_pDev->GetDev().GetPointer()->GetFrontBufferData( 0, pSurface ) ) ){
			SafeRelease( pSurface );
		}
		//Save picture
		RECT rect;
		SharedPointer < WinAPIGraphicsContext > pContext;
		pContext.DownCast( m_pDev->GetContext() );
		::D3DPRESENT_PARAMETERS d3dpp = m_pDev->GetD3DPP();
		//Window mode
		if( d3dpp.Windowed ){
			//Get left-top position on screen coordinate
			POINT point = { 0, 0 };				//Client coordinate
			ClientToScreen( pContext->GetHWnd(), &point );		//Change client coordinate into screen coordinate
			rect.left = point.x;
			rect.top = point.y;
			//Get right-bottom position in screen coordinate
			point.x = d3dpp.BackBufferWidth;
			point.y = d3dpp.BackBufferHeight;
			ClientToScreen( pContext->GetHWnd(), &point );
			rect.right = point.x;
			rect.bottom = point.y;
			//Save surface to file
			HRESULT hr = D3DXSaveSurfaceToFile(	pFileName,		//File name
												D3DXIFF_BMP,	//BMP format
												pSurface,		//Surface which will be saved
												NULL,			//Palette
												&rect );		//Region which will be saved
			SafeRelease( pSurface );
			if( FAILED( hr ) ){
				throw MapilException(	TSTR( "MAPIL" ),
										TSTR( "D3DManager" ),
										TSTR( "ScreenCapture" ),
										TSTR( "Failed to save picture. ( Window mode. )" ),
										-3 );
			}
		}
		//Full screen mode
		else{
			//Save surface to file
			HRESULT hr = D3DXSaveSurfaceToFile(	pFileName,
												D3DXIFF_BMP,
												pSurface,
												NULL,
												NULL );			//Region which will be saved, is whole
			SafeRelease( pSurface );
			if( FAILED( hr ) ){
				throw MapilException(	TSTR( "MAPIL" ),
										TSTR( "D3DManager" ),
										TSTR( "ScreenCapture" ),
										TSTR( "Failed to save picture. ( Full screen mode. )" ),
										-4 );
			}
		}
	}

	MapilVoid D3DGraphicsController::SetWndMode( MapilInt32 mode )
	{
		::HWND hWnd;
		SharedPointer < WinAPIWindow > pWnd;
		pWnd.DownCast( m_pDev->GetContext()->GetParentWnd() );
		hWnd = pWnd->GetHWnd();
		if( mode == 0 || mode == 1 ){
			pWnd->SetWndMode( mode );
		}
		//// DirectX full screen mode.
		//else if( mode == 2 ){
		//	LostResource();
		//	m_pDev->ChangeWndMode( mode );
		//	if( mode == 1 ){
		//		GetWindowRect( hWnd, &m_LastWndPos );
		//	}

		//	::D3DPRESENT_PARAMETERS d3dPP = m_pDev->GetD3DPP();

		//	HRESULT hr = m_pDev->GetDev().GetPointer()->Reset( &d3dPP );
		//	if( FAILED( hr ) ){
		//		//Device is lost
		//		if( hr == D3DERR_DEVICELOST ){
		//			m_DoesDevLost = MapilTrue;
		//		}
		//		//Unexpected error
		//		else{
		//			if( hr == D3DERR_DRIVERINTERNALERROR ){
		//				OutputDebugString( TSTR( "-----test:2-1\n" ) );
		//			}
		//			else if( hr == D3DERR_INVALIDCALL ){
		//				OutputDebugString( TSTR( "-----test:2-2\n" ) );
		//			}
		//			else if( hr == D3DERR_OUTOFVIDEOMEMORY ){
		//				OutputDebugString( TSTR( "-----test:2-3\n" ) );
		//			}
		//			else if( hr == E_OUTOFMEMORY ){
		//				OutputDebugString( TSTR( "-----test:2-4\n" ) );
		//			}
		//			throw MapilException(	TSTR( "MAPIL" ),
		//									TSTR( "D3DManager" ),
		//									TSTR( "ChangeDispMode" ),
		//									TSTR( "Unexpected error has occurred." ),
		//									-1 );
		//		}
		//	}
		//	//Restore resource
		//	RestoreResource();

		//	//Change into window mode
		//	if( mode == 0 ){
		//		//Change window style
		//		SetWindowLong( hWnd, GWL_STYLE, WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_CAPTION );
		//		//Set window position
		//		SetWindowPos(	hWnd,
		//						HWND_NOTOPMOST,
		//						m_LastWndPos.left,
		//						m_LastWndPos.top,
		//						m_LastWndPos.right - m_LastWndPos.left,
		//						m_LastWndPos.bottom - m_LastWndPos.top,
		//						SWP_SHOWWINDOW );
		//	}
		//	//Change into full screen mode
		//	else if( mode == 1 ){
		//		SetWindowLong( hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE );
		//	}
		//}

		//m_DoesDispChangeNext = MapilFalse;
	}

	MapilVoid D3DGraphicsController::SetGraphicsFactory( GraphicsFactory* pFactory )
	{
		m_pGraphicsFactory = pFactory;
	}
}

#endif	// API_DIRECT3D