/**
*	@file	D3DGraphicsFactory.cpp
*	@brief	Implementation of D3DGraphicsFactory.h.
*	@date	2011.8.26 (Fri) 17:57
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_9_0_C )

#include "../../Include/MAPIL/Graphics/D3DGraphicsFactory.h"

#include "../../Include/MAPIL/TChar.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3DGraphicsFactory::D3DGraphicsFactory( SharedPointer < GraphicsDevice > pDev ) :	GraphicsFactory( pDev ),
																						m_CanvasRM( pDev ),
																						m_Canvas3DRM( pDev ),
																						m_SpriteRM( pDev ),
																						m_CameraRM( pDev ),
																						m_GraphicsCtrlRM( pDev ),
																						m_DirLightRM( pDev ),
																						m_PLightRM( pDev ),
																						m_ModelRM( pDev ),
																						m_GraphicsFontRM( pDev ),
																						m_TexRM( pDev ),
																						m_PSpriteRM( pDev ),
																						m_Rect3DRM( pDev ),
																						m_NPoly3DRM( pDev )
	{
		m_CanvasRM.Init();
		m_Canvas3DRM.Init();
		m_SpriteRM.Init();
		m_CameraRM.Init();
		m_GraphicsCtrlRM.Init();
		m_DirLightRM.Init();
		m_PLightRM.Init();
		m_ModelRM.Init();
		m_GraphicsFontRM.Init();
		m_TexRM.Init();
		m_PSpriteRM.Init();
		m_Rect3DRM.Init();
		m_NPoly3DRM.Init();
	}
	
	D3DGraphicsFactory::~D3DGraphicsFactory()
	{
	}
	
	ICanvas2D D3DGraphicsFactory::CreateCanvas2D( const MapilTChar* pKeyStr )
	{
		return m_CanvasRM.Create( pKeyStr );
	}

	ICanvas3D D3DGraphicsFactory::CreateCanvas3D( const MapilTChar* pKeyStr )
	{
		return m_Canvas3DRM.Create( pKeyStr );
	}

	ISprite D3DGraphicsFactory::CreateSprite( const MapilTChar* pKeyStr )
	{
		return m_SpriteRM.Create( pKeyStr );
	}
	
	ICamera D3DGraphicsFactory::CreateCamera( const MapilTChar* pKeyStr )
	{
		return m_CameraRM.Create( pKeyStr );
	}
	
	IGraphicsController D3DGraphicsFactory::CreateGraphicsController( const MapilTChar* pKeyStr )
	{
		IGraphicsController gctrl = m_GraphicsCtrlRM.Create( pKeyStr );
		gctrl->SetGraphicsFactory( this );

		return gctrl;
	}

	IDirectionalLight D3DGraphicsFactory::CreateDirectionalLight( const MapilTChar* pKeyStr )
	{
		return m_DirLightRM.Create( pKeyStr );
	}

	IPointLight D3DGraphicsFactory::CreatePointLight( const MapilTChar* pKeyStr )
	{
		return m_PLightRM.Create( pKeyStr );
	}

	IModel D3DGraphicsFactory::CreateModel( const MapilTChar* pKeyStr )
	{
		return m_ModelRM.Create( pKeyStr );
	}

	IGraphicsFont D3DGraphicsFactory::CreateGraphicsFont( const MapilTChar* pKeyStr )
	{
		return m_GraphicsFontRM.Create( pKeyStr );
	}

	ITexture D3DGraphicsFactory::CreateTexture( const MapilTChar* pKeyStr )
	{
		return m_TexRM.Create( pKeyStr );
	}

	MapilVoid D3DGraphicsFactory::CreateTextures( const MapilTChar* pKeyStr, ITexture* pTexture, MapilInt32 count )
	{
		for( MapilInt32 i = 0; i < count; ++i ){
			std::basic_string < MapilTChar > keyStr = pKeyStr;
			keyStr += TSTR( ":" );
			keyStr += i;
			pTexture[ i ] = CreateTexture( keyStr.c_str() );
		}
	}

	IPointSprite D3DGraphicsFactory::CreatePointSprite( const MapilTChar* pKeyStr )
	{
		return m_PSpriteRM.Create( pKeyStr );
	}

	IRectangle3D D3DGraphicsFactory::CreateRectangle3D( const MapilTChar* pKeyStr )
	{
		return m_Rect3DRM.Create( pKeyStr );
	}

	INSidedPolygon3D D3DGraphicsFactory::CreateNSidedPolygon3D( const MapilTChar* pKeyStr )
	{
		return m_NPoly3DRM.Create( pKeyStr );
	}

	MapilVoid D3DGraphicsFactory::Reflesh()
	{
		m_CanvasRM.Reflesh();
		m_SpriteRM.Reflesh();
		m_CameraRM.Reflesh();
		m_GraphicsCtrlRM.Reflesh();
		m_DirLightRM.Reflesh();
		m_PLightRM.Reflesh();
		m_ModelRM.Reflesh();
		m_GraphicsFontRM.Reflesh();
		m_TexRM.Reflesh();
		m_PSpriteRM.Reflesh();
		m_Rect3DRM.Reflesh();
	}

	MapilVoid D3DGraphicsFactory::LostAllResources()
	{
		m_SpriteRM.LostAllResources();
		m_GraphicsFontRM.LostAllResources();
		m_CanvasRM.LostAllResources();
	}

	MapilVoid D3DGraphicsFactory::RestoreAllResources()
	{
		m_SpriteRM.RestoreAllResources();
		m_GraphicsFontRM.RestoreAllResources();
		m_CanvasRM.RestoreAllResources();
	}
}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D