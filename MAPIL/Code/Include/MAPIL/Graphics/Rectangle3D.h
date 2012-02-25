/**
*	@file	Rectangle3D.h
*	@brief	Rectangle3D class allows the user to handle the 3D-based rectangle.
*			The user can set the vertices freely. Rectangle3D can attach the
*			texture. Therefore, the users can implement the bill-board by using
*			this class. However, it is more difficult to use this class than the
*			other class in graphics module.
*	@date	2011.8.18 (Thu) 16:28
*/

#ifndef INCLUDED_MAPIL_RECTANGLE3D_H
#define INCLUDED_MAPIL_RECTANGLE3D_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Polygon3D.h"
#include "Texture.h"
#include "../Util/SharedPointer.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{

	struct Rectangle3DVertexFormat
	{
		union
		{
			struct
			{
				MapilFloat32		m_X;				///< X-coordinate of the vertex.
				MapilFloat32		m_Y;				///< Y-coordinate of the vertex.
				MapilFloat32		m_Z;				///< Z-coordinate of the vertex.
			} m_Pos[ 4 ];
			MapilFloat32			m_PosElm[ 12 ];		///< Coordinate of the vertex.
		};
		union
		{
			struct
			{
				MapilUChar			m_R;				///< Red of the vertex color.
				MapilUChar			m_G;				///< Green of the vertex color.
				MapilUChar			m_B;				///< Blue of the vertex color.
				MapilUChar			m_A;				///< Alpha of the vertex color.
			} m_Col[ 4 ];
			MapilUChar				m_ColElm[ 16 ];		///< Color of the vertex.
		};
		union
		{
			struct
			{
				MapilFloat32		m_U;				///< U-coordinate of the texture for the vertex.
				MapilFloat32		m_V;				///< V-coordinate of the texture for the vertex.
			} m_Tex[ 4 ];
			MapilFloat32		m_TexElm[ 8 ];			///< Coordinate of the texture for the vertex.
		};
	};

	class Rectangle3D : public Polygon3D
	{
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		explicit Rectangle3D( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~Rectangle3D();
		/**
		*	@brief				Instantiate the Rectangle3D object.
		*	@param fmt			The vertex format of the Rectangle3D object.
		*	@param pTex			SharedPointer to the Texture object used in the Rectangle3D object.
		*	@param manageMethod	Management method of the vertices.
		*/
		virtual MapilVoid Create(	const Rectangle3DVertexFormat& fmt,
									SharedPointer < Texture > pTex,
									VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER ) = 0;
		/**
		*	@brief				Instantiate the Rectangle3D object.
		*	@param fmt			The vertex format of the Rectangle3D object.
		*	@param manageMethod	Management method of the vertices.
		*/
		virtual MapilVoid Create(	const Rectangle3DVertexFormat& fmt,
									VertexManagementMethod manageMethod = VERTEX_MANAGEMENT_BUFFER ) = 0;
		/**
		*	@brief		Update the Rectangle3D object.
		*	@param fmt	The vertex format of the Rectangle3D object.
		*	@param pTex	SharedPointer to the Texture object used in the Rectangle3D object.
		*/
		virtual MapilVoid Update(	const Rectangle3DVertexFormat& fmt,
									SharedPointer < Texture > pTex ) = 0;
		/**
		*	@brief		Update the Rectangle3D object.
		*	@param fmt	The vertex format of the Rectangle3D object.
		*/
		virtual MapilVoid Update( const Rectangle3DVertexFormat& fmt ) = 0;
		/**
		*	@brief	Draw the Rectangle3D object.
		*/
		virtual MapilVoid Draw() = 0;
		/**
		*	@brief		Draw the Rectangle3D object with transformation.
		*	@param mat	Transformation matrix.
		*/
		virtual MapilVoid Draw( const Matrix4x4 < MapilFloat32 >& mat ) = 0;
	};
}

#endif	// INCLUDED_MAPIL_RECTANGLE3D_H