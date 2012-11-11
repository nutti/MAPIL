/**
*	@file	GraphicsFactory.cpp
*	@brief	Implementation of GraphicsFactory.
*	@date	2011.6.18 (Sat) 15:51
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/GraphicsFactory.h"
#include "../../Include/MAPIL/Graphics/D3DGraphicsFactory.h"
#include "../../Include/MAPIL/Graphics/D3D10GraphicsFactory.h"
#include "../../Include/MAPIL/Graphics/GLGraphicsFactory.h"

#include "../../Include/MAPIL/Graphics/NSidedPolygon3D.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GraphicsFactory::GraphicsFactory( SharedPointer < GraphicsDevice > pDev ) : MapilObject(), m_pDev( pDev )
	{
	}
	
	GraphicsFactory::~GraphicsFactory()
	{
	}

	MapilVoid GraphicsFactory::Reflesh( MapilInt32 count )
	{
		for( MapilInt32 i = 0; i < count; ++i ){
			Reflesh();
		}
	}

	MapilVoid GraphicsFactory::LostAllResources()
	{
	}

	MapilVoid GraphicsFactory::RestoreAllResources()
	{
	}

	GraphicsFactory* CreateGraphicsFactory( SharedPointer < GraphicsDevice > pDev )
	{
		MapilInt32 api = pDev->GetGraphicsAPI();
		MapilInt32 version = pDev->GetGraphicsAPIVersion();

		if( api == GRAPHICS_API_DIRECT3D ){
#if defined ( API_DIRECT3D )
			if( version == D3D_VER_9_0_C ){
	#if ( DIRECT3D_VERSION == D3D_VER_9_0_C )
				return new D3DGraphicsFactory( pDev );
	#else
				return NULL;
	#endif
			}
			else if( version == D3D_VER_10_0 ){
	#if ( DIRECT3D_VERSION == D3D_VER_10_0 )
				return new D3D10GraphicsFactory( pDev );
	#else
				return NULL;
	#endif
			}
#else
			return NULL;
#endif
		}
		else if( api == GRAPHICS_API_OPENGL ){
#if defined ( API_OPENGL )
			return new GLGraphicsFactory( pDev );
#else
			return NULL;
#endif
		}
		else{
			return NULL;
		}

		return NULL;
	}

}
