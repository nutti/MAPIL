/**
*	@file	Texture.h
*	@brief	Texture class provides the easy way to attach the texture. The users can
*			split the texture loaded. The user must call the Create method to
*			instantiate the Texture object at first.
*	@date	2011.7.17 (Sun) 12:06
*/

#ifndef INCLUDED_MAPIL_TEXTURE_H
#define INCLUDED_MAPIL_TEXTURE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Type.h"
#include "../Math/Vector.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class Archiver;
	class Texture : public Graphics
	{
	protected:
		Vector2 < MapilInt32 >		m_TexSize;			///< Size of the original texture.
		Vector2 < MapilInt32 >*		m_pSizeList;		///< Size list of the textures split.
		Vector2 < MapilInt32 >*		m_pBeginPosList;	///< Begin position list of the textures split.
		MapilInt32					m_SplitTotal;		///< The split total.
		MapilInt32					m_SplitIndex;		///< Index of the texture which is active.
	public:
		/**
		*	@brief Constructor.
		*	@param pDev SharedPointer to GraphicsDevice.
		*/
		Texture( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~Texture();
		/**
		*	@brief				Instantiate the Texture object.
		*	@param pFileName	File name to be loaded.
		*/
		virtual MapilVoid Create( const MapilTChar* pFileName ) = 0;
		/**
		*	@brief				Instantiate the Texture object.
		*	@param pArchiver	Archiver.
		*	@param pFileName	File name to be loaded.
		*/
		virtual MapilVoid Create( Archiver* pArchiver, const MapilTChar* pFileName ) = 0;
		/**
		*	@brief			Split the texture already loaded.
		*	@param column	The number of the column to be split.
		*	@param row		The number of the row to be split.
		*	@param width	Width of the texture.
		*	@param height	Height of the texture.
		*/
		virtual MapilVoid Split( MapilInt32 column, MapilInt32 row, MapilInt32 width, MapilInt32 height ){};
		/**
		*	@brief			Set the index of the active texture.
		*	@param index	The index of the texture.
		*/
		virtual MapilVoid SetSplitIndex( MapilInt32 index );
		/**
		*	@brief	Get the texture instance which is active.
		*	@return	The texture instance.
		*/
		virtual MapilInt32 Get() = 0;
		/**
		*	@brief	Get the orignal texture size.
		*	@return	The size of the texture.
		*/
		virtual Vector2 < MapilInt32 > GetSize() = 0;
		/**
		*	@brief	Get the texture size which is active.
		*	@return	The size of the texture.
		*/
		virtual Vector2 < MapilInt32 > GetSplitSize() const;
		/**
		*	@brief	Get the texture left-top position which is active.
		*	@return	The size of the texture.
		*/
		virtual Vector2 < MapilInt32 > GetSplitBeginPos() const;
		/**
		*	@brief	Is the texture already split?
		*	@return	True if the texture is split.
		*/
		virtual MapilBool IsSplit() const;
	};
}

#endif	// INCLUDED_MAPIL_TEXTURE_H