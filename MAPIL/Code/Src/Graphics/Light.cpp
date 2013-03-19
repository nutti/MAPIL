/**
*	@file	Light.cpp
*	@brief	
*	@date	2011.7.16 (Sat) 16:20
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Graphics/Light.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

namespace MAPIL
{
	// Constructor.
	Light::Light( SharedPointer < GraphicsDevice > pDev ) :	Graphics( pDev ),
															MAX_LIGHT_INDEX( 8 )
	{
	}

	// Destructor.
	Light::~Light()
	{
	}

	// Attach light index.
	MapilInt32 Light::AttachLightIndex()
	{
		for( MapilInt32 i = 0; i < MAX_LIGHT_INDEX; ++i ){
			if( !m_UsedMap[ i ] ){
				m_UsedMap[ i ] = MapilTrue;
				return i;
			}
		}

		return -1;
	}

	// Release light index.
	MapilVoid Light::ReleaseLightIndex( MapilInt32 index )
	{
		if( index >= 0 && index < MAX_LIGHT_INDEX ){
			m_UsedMap[ index ] = MapilFalse;
		}
	}

	MapilBool Light::m_UsedMap[ 8 ] = {	MapilFalse, MapilFalse, MapilFalse, MapilFalse,
										MapilFalse, MapilFalse, MapilFalse, MapilFalse };
}