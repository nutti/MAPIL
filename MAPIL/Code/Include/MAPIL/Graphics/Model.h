/**
*	@file	Model.h
*	@brief	Model class allows the users to load modeling file and draw the models
*			in it. The users can instantiate the Model object by calling the Create
*			method. This class is a interface class. The users must call the method
*			which is implemented on the class derived from this class.
*	@date	2011.7.16(Sat) 10:30
*/

#ifndef INCLUDED_MAPIL_MODEL_H
#define INCLUDED_MAPIL_MODEL_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "../Type.h"
#include "Graphics.h"
#include "../Math/Matrix.hpp"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GraphicsDevice;
	class Archiver;
	class Model : public Graphics
	{
	private:
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		Model( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~Model();
		/**
		*	@brief				Instantiate the Model object.
		*	@param pFileName	Name of the modeling file to load.
		*/
		virtual MapilVoid Create( const MapilTChar* pFileName ) = 0;
		/**
		*	@brief						Instantiate the Model object.
		*	@param pArchiver			Archiver.
		*	@param pXFileName			Name of the modeling file to load.
		*	@param pTextureFileName		Name of the texture file to load.
		*/
		virtual MapilVoid Create( Archiver* pArchiver, const MapilTChar* pXFileName, const MapilTChar* pTextureFileName ) = 0;
		/**
		*	@brief	Draw the model with no transformation.
		*/
		virtual MapilVoid Draw() = 0;
		/**
		*	@brief		Draw the model with transformation.
		*	@param mat	Transformation matrix.
		*/
		virtual MapilVoid Draw( const Matrix4x4 < MapilFloat32 >& mat ) = 0;
		/**
		*	@brief					Detect collision.
		*	@param vRayDir			Direction of the ray.
		*	@param vRayOrig			Position of the ray.
		*	@param pVcollisionPos	Position where the ray hits.
		*	@param pDistance		Distance between vRayOrig and where the ray hits.
		*	@return					Does the ray collide with the polygon?
		*/
		virtual MapilBool DetectCollision(	const Vector3 < MapilFloat32 >& vRayDir,
											const Vector3 < MapilFloat32 >& vRayOrig,
											Vector2 < MapilFloat32 >* pVCollisionPos,
											MapilFloat32* pDistance ) = 0;
	};
}

#endif	// INCLUDED_MAPIL_MODEL_H