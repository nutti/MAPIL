/**
*	@file	GLPointSprite.h
*	@brief	This class is derived from PointSprite class. GLPointSprite is
*			implemented for OpenGL. The users shouldn't call method from this
*			class directly.
*	@date	2011.8.7 (Sun) 21:11
*/

#ifndef INCLUDED_MAPIL_GLPOINTSPRITE_H
#define INCLUDED_MAPIL_GLPOINTSPRITE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_OPENGL )

#if defined ( API_WIN32API )
#include <Windows.h>
#endif
#if defined ( OS_WIN_32BIT )
#include <gl/GL.h>
#elif defined ( OS_LINUX_32BIT )
#include <GL/gl.h>
#endif

#include "PointSprite.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class GLPointSprite : public PointSprite
	{
	private:
		GLfloat							m_Size;			///< Point size.
		GLfloat*						m_pColor;		///< Color of the vertex.
		GLfloat*						m_pPos;			///< Position of the vertex. 
		MapilInt32						m_NumVertex;	///< Number of the vertex.
		MapilBool						m_IsUsed;		///< The flag shows that the object is already used.
		SharedPointer < Texture >		m_pTex;			///< Texture.
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		explicit GLPointSprite( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLPointSprite();
		/**
		*	@brief				Instantiate the GLPointSprite object.
		*	@param numVertex	Number of the vertex to be created.
		*	@param pTex			SharedPointer to the Texture object used in the GLPointSprite object.
		*	@param manageMethod	Management method of the vertices.
		*/
		MapilVoid Create(	MapilInt32 numVertex, SharedPointer < Texture > pTex,
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		/**
		*	@brief				Instantiate the GLPointSprite object.
		*	@param numVertex	Number of the vertex to be created.
		*	@param manageMethod	Management method of the vertices.
		*/
		MapilVoid Create(	MapilInt32 numVertex,
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		/**
		*	@brief			Update the vertex.
		*	@param index	Index of the vertex to be updated.
		*	@param vPos		Position of the vertex.
		*	@param size		Point size.
		*	@param color	Color of the vertex.
		*/
		MapilVoid Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
							MapilFloat32 size, const ColorARGB < MapilFloat32 >& color );
		/**
		*	@brief			Update the vertex.
		*	@param index	Index of the vertex to be updated.
		*	@param vPos		Position of the vertex.
		*	@param size		Point size.
		*	@param color	Color of the vertex.
		*/
		MapilVoid Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
							MapilFloat32 size, const ColorARGB < MapilUChar >& color );
		/**
		*	@brief			Update the vertex.
		*	@param index	Index of the vertex to be updated.
		*	@param vPos		Position of the vertex.
		*	@param size		Point size.
		*	@param color	Color of the vertex.
		*/
		MapilVoid Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
							MapilFloat32 size, MapilUInt32 color );
		/**
		*	@brief	Draw all the registered vertices.
		*/
		MapilVoid Draw();
	};
}

#endif	// API_OPENGL

#endif	// INCLUDED_MAPIL_GLPOINTSPRITE_H