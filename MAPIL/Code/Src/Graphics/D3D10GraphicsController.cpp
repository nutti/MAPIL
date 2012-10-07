/**
*	@file	D3D10GraphicsController.cpp
*	@brief	Implementation of D3D10GraphicsController.
*	@date	2012.10.6 (Sat) 10:11
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_10_0 )

#include "../../Include/MAPIL/Graphics/D3D10GraphicsController.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Graphics/GraphicsFactory.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3D10GraphicsController::D3D10GraphicsController( SharedPointer < GraphicsDevice > pDev ) :	GraphicsController( pDev ),
																								m_pGC(),
																								m_pGraphicsFactory( NULL )
	{
	}

	D3D10GraphicsController::~D3D10GraphicsController()
	{
		m_pGraphicsFactory = NULL;
	}

	MapilVoid D3D10GraphicsController::Create( SharedPointer < GraphicsContext > pGC )
	{
		m_pGC = pGC;
	}

	// Begin rendering
	MapilVoid D3D10GraphicsController::BeginRendering()
	{
		MapilFloat32 color[ 4 ] = { 0.0f, 0.0f, 0.0f, 0.0f };

		m_pDev->GetDev().GetPointer()->ClearRenderTargetView(	m_pDev->GetRenderTargetView().GetPointer(),
																color );
	}

	// End rendering
	MapilVoid D3D10GraphicsController::EndRendering()
	{
		m_pDev->GetSwapChain().GetPointer()->Present( 0, 0 );
	}

	// Set viewport
	MapilVoid D3D10GraphicsController::SetViewport(	MapilInt32 x,
													MapilInt32 y,
													MapilInt32 width,
													MapilInt32 height )
	{

	}

	// Enable z buffer
	MapilVoid D3D10GraphicsController::EnableZBuffer( MapilBool status )
	{
	}

	// Enable light
	MapilVoid D3D10GraphicsController::EnableLight( MapilBool status )
	{
	}

	// Enable blend
	MapilVoid D3D10GraphicsController::EnableBlend( MapilBool status )
	{
	}

	// Enable fog.
	MapilVoid D3D10GraphicsController::EnableFog( MapilBool status )
	{
	}

	// Set alpha blend mode
	MapilVoid D3D10GraphicsController::SetAlphaBlendMode( MapilInt32 mode )
	{
	}

	// Set cull mode
	MapilVoid D3D10GraphicsController::SetCullMode( MapilInt32 mode )
	{
	}

	// Set texture mode
	MapilVoid D3D10GraphicsController::SetTextureMode( MapilInt32 mode )
	{
	}

	// Set fog parameter.
	MapilVoid D3D10GraphicsController::SetFogParam(	const ColorARGB < MapilFloat32 >& color,
													MapilInt32 mode,
													MapilFloat32 begin,
													MapilFloat32 end,
													MapilFloat32 density )
	{
	}

	MapilVoid D3D10GraphicsController::SetFogParam(	const ColorARGB < MapilUChar >& color,
													MapilInt32 mode,
													MapilFloat32 begin,
													MapilFloat32 end,
													MapilFloat32 density )
	{
	}

	MapilVoid D3D10GraphicsController::SetFogParam(	MapilUInt32 color,
													MapilInt32 mode,
													MapilFloat32 begin,
													MapilFloat32 end,
													MapilFloat32 density )
	{
	}

	// Set vsync.
	MapilVoid D3D10GraphicsController::EnableVSync( MapilBool status )
	{
	}


	MapilVoid D3D10GraphicsController::CaptureScreen( const MapilTChar* pFileName )
	{
	}

	MapilVoid D3D10GraphicsController::SetWndMode( MapilInt32 mode )
	{
	}

	MapilVoid D3D10GraphicsController::SetGraphicsFactory( GraphicsFactory* pFactory )
	{
	}
}

#endif	// DIRECT3D_VERSION

#endif	// API_DIRECT3D