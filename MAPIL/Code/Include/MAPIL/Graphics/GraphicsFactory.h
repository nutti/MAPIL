/**
*	@file	GraphicsFactory.h
*	@brief	GraphicsFactory class provides the method for the user to create
*			the resources. Each resource is managed by the string. Therefore
*			created resources don't have the same objects. Moreover, this class
*			provides the easy way for the user to create the object in the
*			various platform.
*	@date	2011.6.18 (Sat) 15:50
*/

#ifndef INCLUDED_MAPIL_GRAPHICSFACTORY_H
#define INCLUDED_MAPIL_GRAPHICSFACTORY_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "../Util/MapilObject.h"
#include "GraphicsDevice.h"
#include "../Util/SharedPointer.hpp"

#include <vector>

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class Canvas2D;
	class Canvas3D;
	class Sprite;
	class Camera;
	class GraphicsController;
	class DirectionalLight;
	class PointLight;
	class Model;
	class GraphicsFont;
	class Texture;
	class PointSprite;
	class Rectangle3D;
	class NSidedPolygon3D;
	class SkinMeshModel;

	typedef SharedPointer < Canvas2D >					ICanvas2D;				///< Interface of the Canvas2D class.
	typedef SharedPointer < Canvas3D >					ICanvas3D;				///< Interface of the Canvas3D class.
	typedef SharedPointer < Sprite >					ISprite;				///< Interface of the Sprite class.
	typedef SharedPointer < Camera >					ICamera;				///< Interface of the Camera class.
	typedef SharedPointer < GraphicsController >		IGraphicsController;	///< Interface of the GraphicsController class.
	typedef SharedPointer < DirectionalLight >			IDirectionalLight;		///< Interface of the DirectionalLight class.
	typedef SharedPointer < PointLight >				IPointLight;			///< Interface of the PointLight class.
	typedef SharedPointer < Model >						IModel;					///< Interface of the Model class.
	typedef SharedPointer < GraphicsFont >				IGraphicsFont;			///< Interface of the GraphicsFont class.
	typedef SharedPointer < Texture >					ITexture;				///< Interface of the Texture class.
	typedef SharedPointer < PointSprite >				IPointSprite;			///< Interface of the PointSrpite class.
	typedef SharedPointer < Rectangle3D >				IRectangle3D;			///< Interface of the Rectangle3D class.
	typedef SharedPointer < NSidedPolygon3D >			INSidedPolygon3D;			///< Interface of the NSidedPolygon class.
	typedef SharedPointer < SkinMeshModel >				ISkinMeshModel;			///< Interface of the SkinMeshModel class.

	class GraphicsFactory : public MapilObject
	{
	protected:
		SharedPointer < GraphicsDevice >		m_pDev;			///< Graphics device.
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		GraphicsFactory( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		virtual ~GraphicsFactory();
		/**
		*	@brief			Create a Canvas2D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual ICanvas2D CreateCanvas2D( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a Canvas3D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual ICanvas3D CreateCanvas3D( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a Sprite object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual ISprite CreateSprite( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a Camera object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual ICamera CreateCamera( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a GraphicsController object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual IGraphicsController CreateGraphicsController( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a DirectionalLight object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual IDirectionalLight CreateDirectionalLight( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a PointLight object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual IPointLight CreatePointLight( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a Model object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual IModel CreateModel( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a GraphicsFont object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual IGraphicsFont CreateGraphicsFont( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a Texture object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual ITexture CreateTexture( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a Texture objects and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@param pTexture Texture array to be created.
		*	@param count	Creation count.
		*/
		virtual MapilVoid CreateTextures( const MapilTChar* pKeyStr, ITexture* pTexture, MapilInt32 count ) = 0;
		/**
		*	@brief			Create a PointSprite object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual IPointSprite CreatePointSprite( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a Rectangle3D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual IRectangle3D CreateRectangle3D( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief			Create a NSidedPolygon3D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		virtual INSidedPolygon3D CreateNSidedPolygon3D( const MapilTChar* pKeyStr ) = 0;
		virtual ISkinMeshModel CreateSkinMeshModel( const MapilTChar* pKeyStr ) = 0;
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*/
		virtual MapilVoid Reflesh() = 0;
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*	@param Reflesh count.
		*/
		MapilVoid Reflesh( MapilInt32 count );
		virtual MapilVoid LostAllResources();
		virtual MapilVoid RestoreAllResources();
	};

	typedef SharedPointer < GraphicsFactory >			IGraphicsFactory;	///< Interface of the GraphicsFactory class.
	
	/**
	*	@brief		Create a GraphicsFactory object.
	*	@param pDev	SharedPointer to the GraphicsDevice object.
	*	@return		Pointer to the created object.
	*/
	GraphicsFactory* CreateGraphicsFactory( SharedPointer < GraphicsDevice > pDev );
}

#endif	// INCLUDED_MAPIL_GRAPHICSFACTORY_H
