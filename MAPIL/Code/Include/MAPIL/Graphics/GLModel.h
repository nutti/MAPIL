/**
*	@file	GLModel.h
*	@brief	GLModel class is derived class from Model class. GLModel is
*			implemented for OpenGL. The users shouldn't call the method
*			from this class directly.
*	@date	2011.7.16 (Sat) 10:35
*/

#ifndef INCLUDED_MAPIL_GLMODEL_H
#define INCLUDED_MAPIL_GLMODEL_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_OPENGL )

#include "Model.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	struct ModelData;
	class GraphicsDevice;
	class Archiver;
	class GLModel : public Model
	{
	private:
		ModelData*		m_pModelData;		///< Model data.
		/**
		*	@brief		Draw model with no transformation. This is called in Draw method.
		*/
		MapilVoid DrawModel();
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		GLModel( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLModel();
		/**
		*	@brief				Instantiate the GLModel object.
		*	@param pFileName	Name of the modeling file to load.
		*/
		MapilVoid Create( const MapilTChar* pFileName );
		/**
		*	@brief						Instantiate the GLModel object.
		*	@param pArchiver			Archiver.
		*	@param pXFileName			Name of the modeling file to load.
		*	@param pTextureFileName		Name of the texture file to load.
		*/
		MapilVoid Create( Archiver* pArchiver, const MapilTChar* pXFileName, const MapilTChar* pTextureFileName );
		/**
		*	@brief	Draw the model with no transformation.
		*/
		MapilVoid Draw();
		/**
		*	@brief		Draw the model with transformation.
		*	@param mat	Transformation matrix.
		*/
		MapilVoid Draw( const Matrix4x4 < MapilFloat32 >& mat );
	};
}

#endif	// API_OPENGL

#endif	// INCLUDED_MAPIL_GLMODEL_H