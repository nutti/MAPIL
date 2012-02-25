/**
*	@file	GLRectangle3D.h
*	@brief	GLRectangle3D class is derived class from Rectangle3D class. GLRectangle
*			is implemented for OpenGL. The users shouldn't call method from this class
*			directly.
*	@date	2011.8.18 (Thu) 16:37
*/

#ifndef INCLUDED_MAPIL_GLRECTANGLE3D_H
#define INCLUDED_MAPIL_GLRECTANGLE3D_H

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
#endif
#if defined ( OS_LINUX_32BIT )
#include <GL/gl.h>
#endif

#include "Rectangle3D.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GLRectangle3D : public Rectangle3D
	{
	private:
		Rectangle3DVertexFormat		m_Fmt;		///< Vertex format.
		SharedPointer < Texture >	m_pTex;		///< Texture.
		/**
		*	@brief		Draw without transformatoin.
		*/
		MapilVoid DrawVertex();
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		explicit GLRectangle3D( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLRectangle3D();
		/**
		*	@brief				Instantiate the GLRectangle3D object.
		*	@param fmt			The vertex format of the GLRectangle3D object.
		*	@param pTex			SharedPointer to the Texture object used in the GLRectangle3D object.
		*	@param manageMethod	Management method of the vertices.
		*/
		MapilVoid Create(	const Rectangle3DVertexFormat& fmt,
							SharedPointer < Texture > pTex,
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		/**
		*	@brief				Instantiate the GLRectangle3D object.
		*	@param fmt			The vertex format of the GLRectangle3D object.
		*	@param manageMethod	Management method of the vertices.
		*/
		MapilVoid Create(	const Rectangle3DVertexFormat& fmt,
							VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER );
		/**
		*	@brief		Update the GLRectangle3D object.
		*	@param fmt	The vertex format of the GLRectangle3D object.
		*	@param pTex	SharedPointer to the Texture object used in the GLRectangle3D object.
		*/
		MapilVoid Update(	const Rectangle3DVertexFormat& fmt,
							SharedPointer < Texture > pTex );
		/**
		*	@brief		Update the GLRectangle3D object.
		*	@param fmt	The vertex format of the GLRectangle3D object.
		*/
		MapilVoid Update( const Rectangle3DVertexFormat& fmt );
		/**
		*	@brief	Draw the GLRectangle3D object.
		*/
		MapilVoid Draw();
		/**
		*	@brief		Draw the GLRectangle3D object with transformation.
		*	@param mat	Transformation matrix.
		*/
		MapilVoid Draw( const Matrix4x4 < MapilFloat32 >& mat );
	};
}

#endif	// API_OPENGL

#endif	// INCLUDED_MAPIL_GLRECTANGLE3D_H