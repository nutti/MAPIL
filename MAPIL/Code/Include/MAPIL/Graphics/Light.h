/**
*	@file	Light.h
*	@brief	
*	@date	2011.7.16 (Sat) 16:07
*/

#ifndef INCLUDED_MAPIL_LIGHT_H
#define INCLUDED_MAPIL_LIGHT_H

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Util/Color.hpp"
#include "../Type.h"

namespace MAPIL
{
	class GraphicsDevice;
	class Light : public Graphics
	{
	protected:
		const MapilInt32			MAX_LIGHT_INDEX;
		static MapilBool			m_UsedMap[ 8 ];		// Light used map.

		// Attach light index.
		MapilInt32 AttachLightIndex();
		// Release light index.
		MapilVoid ReleaseLightIndex( MapilInt32 index );
	public:
		// Constructor
		Light( SharedPointer < GraphicsDevice > pDev );
		// Destructor
		virtual ~Light();
		// Enagle light
		virtual MapilVoid Enable() = 0;
		// Set diffuse color
		virtual MapilVoid SetDiffuseColor( const ColorARGB < MapilFloat32 >& colorDiffuse ) = 0;
		// Set ambient color
		virtual MapilVoid SetAmbientColor( const ColorARGB < MapilFloat32 >& colorAmbient ) = 0;
		// Set specular color
		virtual MapilVoid SetSpecularColor( const ColorARGB < MapilFloat32 >& colorSpecular ) = 0;
		// Set diffuse color
		virtual MapilVoid SetDiffuseColor( const ColorARGB < MapilUChar >& color ) = 0;
		// Set ambient color
		virtual MapilVoid SetAmbientColor( const ColorARGB < MapilUChar >& color ) = 0;
		// Set specular color
		virtual MapilVoid SetSpecularColor( const ColorARGB < MapilUChar >& color ) = 0;
		// Set attenuation of light
		virtual MapilVoid SetAttenuation( MapilFloat32 attenuation0, MapilFloat32 attenuation1, MapilFloat32 attenuation2 ) = 0;
	};
}

#endif