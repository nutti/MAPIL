/**
*	@file	GLGraphicsFactory.cpp
*	@brief	
*	@date	2011.6.18(Sat) 15:57
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#include "../../Include/MAPIL/Graphics/GLGraphicsFactory.h"
#include "../../Include/MAPIL/Graphics/GLCanvas2D.h"
#include "../../Include/MAPIL/Graphics/GLCanvas3D.h"
#include "../../Include/MAPIL/Graphics/GLCamera.h"
#include "../../Include/MAPIL/Graphics/GLGraphicsController.h"
#include "../../Include/MAPIL/Graphics/GLDirectionalLight.h"
#include "../../Include/MAPIL/Graphics/GLPointLight.h"
#include "../../Include/MAPIL/Graphics/GLModel.h"
#include "../../Include/MAPIL/Graphics/GLGraphicsFont.h"
#include "../../Include/MAPIL/Graphics/GLTexture.h"

#include "../../Include/MAPIL/TChar.h"

namespace MAPIL
{
	GLGraphicsFactory::GLGraphicsFactory( SharedPointer < GraphicsDevice > pDev ) :	GraphicsFactory( pDev ),
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
																					m_Rect3DRM( pDev )
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
	}
	
	GLGraphicsFactory::~GLGraphicsFactory()
	{
	}
	
	ICanvas2D GLGraphicsFactory::CreateCanvas2D( const MapilTChar* pKeyStr )
	{
		return m_CanvasRM.Create( pKeyStr );
	}

	ICanvas3D GLGraphicsFactory::CreateCanvas3D( const MapilTChar* pKeyStr )
	{
		return m_Canvas3DRM.Create( pKeyStr );
	}
	
	ISprite GLGraphicsFactory::CreateSprite( const MapilTChar* pKeyStr )
	{
		return m_SpriteRM.Create( pKeyStr );
	}

	ICamera GLGraphicsFactory::CreateCamera( const MapilTChar* pKeyStr )
	{
		return m_CameraRM.Create( pKeyStr );
	}
	
	IGraphicsController GLGraphicsFactory::CreateGraphicsController( const MapilTChar* pKeyStr )
	{
		return m_GraphicsCtrlRM.Create( pKeyStr );
	}

	IDirectionalLight GLGraphicsFactory::CreateDirectionalLight( const MapilTChar* pKeyStr )
	{
		return m_DirLightRM.Create( pKeyStr );
	}

	IPointLight GLGraphicsFactory::CreatePointLight( const MapilTChar* pKeyStr )
	{
		return m_PLightRM.Create( pKeyStr );
	}

	IModel GLGraphicsFactory::CreateModel( const MapilTChar* pKeyStr )
	{
		return m_ModelRM.Create( pKeyStr );
	}

	IGraphicsFont GLGraphicsFactory::CreateGraphicsFont( const MapilTChar* pKeyStr )
	{
		return m_GraphicsFontRM.Create( pKeyStr );
	}

	ITexture GLGraphicsFactory::CreateTexture( const MapilTChar* pKeyStr )
	{
		return m_TexRM.Create( pKeyStr );
	}

	MapilVoid GLGraphicsFactory::CreateTextures( const MapilTChar* pKeyStr, ITexture* pTexture, MapilInt32 count )
	{
		for( MapilInt32 i = 0; i < count; ++i ){
			std::basic_string < MapilTChar > keyStr = pKeyStr;
			keyStr += TSTR( ":" );
			keyStr += i;
			pTexture[ i ] = CreateTexture( keyStr.c_str() );
		}
	}

	IPointSprite GLGraphicsFactory::CreatePointSprite( const MapilTChar* pKeyStr )
	{
		return m_PSpriteRM.Create( pKeyStr );
	}

	IRectangle3D GLGraphicsFactory::CreateRectangle3D( const MapilTChar* pKeyStr )
	{
		return m_Rect3DRM.Create( pKeyStr );
	}

	MapilVoid GLGraphicsFactory::Reflesh()
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

}

#endif	// API_OPENGL