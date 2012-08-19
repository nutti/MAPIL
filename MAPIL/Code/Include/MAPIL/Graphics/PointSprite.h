/**
*	@file	PointSprite.h
*	@brief	PointSprite class provides the method which draws the small
*			objects faced on the window for the user. This class realizes
*			the effects, for example smoke, flame.
*	@date	2011.8.7 (Sun) 20:55
*/

#ifndef INCLUDED_MAPIL_POINTSPRITE_H
#define INCLUDED_MAPIL_POINTSPRITE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "Texture.h"
#include "../Util/SharedPointer.hpp"
#include "../Util/Color.hpp"
#include "../Math/Vector.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class PointSprite : public Graphics
	{
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		explicit PointSprite( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~PointSprite();
		/**
		*	@brief				Instantiate the PointSprite object.
		*	@param numVertex	Number of the vertex to be created.
		*	@param pTex			SharedPointer to the Texture object used in the PointSprite object.
		*	@param manageMethod	Management method of the vertices.
		*/
		virtual MapilVoid Create(	MapilInt32 numVertex,
									SharedPointer < Texture > pTex,
									VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER ) = 0;
		/**
		*	@brief				Instantiate the PointSprite object.
		*	@param numVertex	Number of the vertex to be created.
		*	@param manageMethod	Management method of the vertices.
		*/
		virtual MapilVoid Create(	MapilInt32 numVertex,
									VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER ) = 0;
		/**
		*	@brief			Update the vertex.
		*	@param index	Index of the vertex to be updated.
		*	@param vPos		Position of the vertex.
		*	@param size		Point size.
		*	@param color	Color of the vertex.
		*/
		virtual MapilVoid Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
									MapilFloat32 size, const ColorARGB < MapilFloat32 >& color ) = 0;
		/**
		*	@brief			Update the vertex.
		*	@param index	Index of the vertex to be updated.
		*	@param vPos		Position of the vertex.
		*	@param size		Point size.
		*	@param color	Color of the vertex.
		*/
		virtual MapilVoid Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
									MapilFloat32 size, const ColorARGB < MapilUChar >& color ) = 0;
		/**
		*	@brief			Update the vertex.
		*	@param index	Index of the vertex to be updated.
		*	@param vPos		Position of the vertex.
		*	@param size		Point size.
		*	@param color	Color of the vertex.
		*/
		virtual MapilVoid Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
									MapilFloat32 size, MapilUInt32 color ) = 0;
		/**
		*	@brief	Draw all the registered vertices.
		*/
		virtual MapilVoid Draw() = 0;
	};
}

#endif	// INCLUDED_MAPIL_POINTSPRITE_H