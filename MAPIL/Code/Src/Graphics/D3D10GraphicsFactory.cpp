/**
*	@file	D3D10GraphicsFactory.cpp
*	@brief	Implementation of D3D10GraphicsFactory.h.
*	@date	2011.8.26 (Fri) 17:57
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_10_0 )

#include "../../Include/MAPIL/Graphics/D3D10GraphicsFactory.h"

#include "../../Include/MAPIL/TChar.h"

#include "../../Include/MAPIL/Graphics/Canvas2D.h"
#include "../../Include/MAPIL/Graphics/Canvas3D.h"
#include "../../Include/MAPIL/Graphics/Sprite.h"
#include "../../Include/MAPIL/Graphics/Camera.h"
#include "../../Include/MAPIL/Graphics/DirectionalLight.h"
#include "../../Include/MAPIL/Graphics/PointLight.h"
#include "../../Include/MAPIL/Graphics/Model.h"
#include "../../Include/MAPIL/Graphics/GraphicsFont.h"
#include "../../Include/MAPIL/Graphics/Texture.h"
#include "../../Include/MAPIL/Graphics/PointSprite.h"
#include "../../Include/MAPIL/Graphics/NSidedPolygon3D.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	D3D10GraphicsFactory::D3D10GraphicsFactory( SharedPointer < GraphicsDevice > pDev ) :	GraphicsFactory( pDev ),
																							m_GraphicsCtrlRM( pDev ),
																							m_Rectangle3DRM( pDev )
	{
		m_GraphicsCtrlRM.Init();
		m_Rectangle3DRM.Init();
	}
	
	D3D10GraphicsFactory::~D3D10GraphicsFactory()
	{
	}
	
	ICanvas2D D3D10GraphicsFactory::CreateCanvas2D( const MapilTChar* pKeyStr )
	{
		ICanvas2D canvas2D;
		return canvas2D;
	}

	ICanvas3D D3D10GraphicsFactory::CreateCanvas3D( const MapilTChar* pKeyStr )
	{
		ICanvas3D canvas3D;
		return canvas3D;
	}

	ISprite D3D10GraphicsFactory::CreateSprite( const MapilTChar* pKeyStr )
	{
		ISprite sprite;
		return sprite;
	}
	
	ICamera D3D10GraphicsFactory::CreateCamera( const MapilTChar* pKeyStr )
	{
		ICamera camera;
		return camera;
	}
	
	IGraphicsController D3D10GraphicsFactory::CreateGraphicsController( const MapilTChar* pKeyStr )
	{
		IGraphicsController gctrl = m_GraphicsCtrlRM.Create( pKeyStr );
		gctrl->SetGraphicsFactory( this );

		return gctrl;
	}

	IDirectionalLight D3D10GraphicsFactory::CreateDirectionalLight( const MapilTChar* pKeyStr )
	{
		IDirectionalLight dirLight;
		return dirLight;
	}

	IPointLight D3D10GraphicsFactory::CreatePointLight( const MapilTChar* pKeyStr )
	{
		IPointLight pointLight;
		return pointLight;
	}

	IModel D3D10GraphicsFactory::CreateModel( const MapilTChar* pKeyStr )
	{
		IModel model;
		return model;
	}

	IGraphicsFont D3D10GraphicsFactory::CreateGraphicsFont( const MapilTChar* pKeyStr )
	{
		IGraphicsFont font;
		return font;
	}

	ITexture D3D10GraphicsFactory::CreateTexture( const MapilTChar* pKeyStr )
	{
		ITexture texture;
		return texture;
	}

	MapilVoid D3D10GraphicsFactory::CreateTextures( const MapilTChar* pKeyStr, ITexture* pTexture, MapilInt32 count )
	{
	}

	IPointSprite D3D10GraphicsFactory::CreatePointSprite( const MapilTChar* pKeyStr )
	{
		IPointSprite sprite;
		return sprite;
	}

	IRectangle3D D3D10GraphicsFactory::CreateRectangle3D( const MapilTChar* pKeyStr )
	{
		return m_Rectangle3DRM.Create( pKeyStr );
	}

	INSidedPolygon3D D3D10GraphicsFactory::CreateNSidedPolygon3D( const MapilTChar* pKeyStr )
	{
		INSidedPolygon3D polygon3D;
		return polygon3D;
	}

	MapilVoid D3D10GraphicsFactory::Reflesh()
	{
	}

	MapilVoid D3D10GraphicsFactory::LostAllResources()
	{
	}

	MapilVoid D3D10GraphicsFactory::RestoreAllResources()
	{
	}
}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D