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
#include "../../Include/MAPIL/Graphics/GLGraphicsFactory.h"

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
		GraphicsAPI api = pDev->GetGraphicsAPI();

		if( api == GRAPHICS_API_DIRECT3D ){
			//return SharedPointer < GraphicsFactory > ( new D3DGraphicsFactory( pDev ) );
			return new D3DGraphicsFactory( pDev );
		}
		else if( api == GRAPHICS_API_OPENGL ){
			return new GLGraphicsFactory( pDev );
		}
		else{
			return NULL;
		}

		return NULL;
	}
}
