/**
*	@file	SkinMeshModel.h
*	@brief	
*	@date	2013.8.24 (Sat) 13:58
*/

#ifndef INCLUDED_MAPIL_SKINMESHMODEL_H
#define INCLUDED_MAPIL_SKINMESHMODEL_H

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
	class SkinMeshModel : public Graphics
	{
	private:
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		SkinMeshModel( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~SkinMeshModel();
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
		virtual MapilVoid Draw( MapilDouble time ) = 0;
		virtual MapilVoid Draw( MapilDouble time, const Matrix4x4 < MapilFloat32 >& mat ) = 0;
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