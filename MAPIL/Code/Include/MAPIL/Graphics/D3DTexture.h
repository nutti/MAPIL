/**
*	@file	D3DTexture.h
*	@brief	D3DTexture class is derived from Texture class. D3DTexture is implemented
*			for Direct3D. The users shouldn't call method from this class directly.
*	@date	2011.8.25 (Thu) 18:13
*/

#ifndef INCLUDED_MAPIL_D3DTEXTURE_H
#define INCLUDED_MAPIL_D3DTEXTURE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include <d3dx9.h>

#include "Texture.h"
#include "../Math/Vector.hpp"
#include "../Util/COMPointer.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class Archiver;
	class D3DTexture : public Texture
	{
	private:
		::LPDIRECT3DTEXTURE9			m_pD3DTexture;		///< Original texture handle.
		::LPDIRECT3DTEXTURE9*			m_ppD3DTexture;		///< Texture handle split.
		//MapilBool						m_IsUsed;			///< The flag shows that the object is already used.
		
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		D3DTexture( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DTexture();
		/**
		*	@brief				Instantiate the D3DTexture object.
		*	@param pFileName	File name to be loaded.
		*/
		MapilVoid Create( const MapilTChar* pFileName );
		/**
		*	@brief				Instantiate the D3DTexture object.
		*	@param pArchiver	Archiver.
		*	@param pFileName	File name to be loaded.
		*/
		MapilVoid Create( Archiver* pArchiver, const MapilTChar* pFileName );
		/**
		*	@brief			Split the texture already loaded.
		*	@param column	The number of the column to be split.
		*	@param row		The number of the row to be split.
		*	@param width	Width of the texture.
		*	@param height	Height of the texture.
		*/
		MapilVoid Split( MapilInt32 column, MapilInt32 row, MapilInt32 width, MapilInt32 height );
		/**
		*	@brief				Split the texture and copy to new texture object.
		*	@param pTextuere	Target texture object to be copied.
		*	@param column		The number of the column to be split.
		*	@param row			The number of the row to be split.
		*	@param width		Width of the texture.
		*	@param height		Height of the texture.
		*/
		MapilVoid SplitCopy(	SharedPointer < Texture >* pTexture,
								MapilInt32 column,
								MapilInt32 row,
								MapilInt32 width,
								MapilInt32 height );
		/**
		*	@brief	Get the texture instance which is active.
		*	@return	The texture instance.
		*/
		MapilInt32 Get();
		/**
		*	@brief	Get the orignal texture size.
		*	@return	The size of the texture.
		*/
		Vector2 < MapilInt32 > GetSize();
	};
}

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DTEXTURE_H