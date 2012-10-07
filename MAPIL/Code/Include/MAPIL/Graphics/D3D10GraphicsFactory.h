/**
*	@file	D3D10GraphicsFactory.h
*	@brief	
*	@date	2012.10.6 (Sat) 17:44
*/

#ifndef INCLUDED_MAPIL_D3D10GRAPHICSFACTORY_H
#define INCLUDED_MAPIL_D3D10GRAPHICSFACTORY_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )
#if ( DIRECT3D_VERSION == D3D_VER_10_0 )

#include "GraphicsFactory.h"
#include "GraphicsResourceManager.hpp"

#include "D3D10Rectangle3D.h"
#include "D3D10GraphicsController.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{

	class D3D10GraphicsController;
	class D3D10Rectangle3D;
	class D3D10GraphicsFactory : public GraphicsFactory
	{
	private:
		GraphicsResourceManager < D3D10GraphicsController >		m_GraphicsCtrlRM;	///< Resource manager for the D3D10GraphicsController object.
		GraphicsResourceManager < D3D10Rectangle3D >			m_Rectangle3DRM;
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		D3D10GraphicsFactory( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3D10GraphicsFactory();
		/**
		*	@brief			Create a D3D10Canvas2D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ICanvas2D CreateCanvas2D( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3D10Canvas3D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ICanvas3D CreateCanvas3D( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3D10Sprite object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ISprite CreateSprite( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3D10Camera object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ICamera CreateCamera( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3D10GraphicsController object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IGraphicsController CreateGraphicsController( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3D10DirectionalLight object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IDirectionalLight CreateDirectionalLight( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3D10PointLight object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IPointLight CreatePointLight( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3D10Model object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IModel CreateModel( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3D10GraphicsFont object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IGraphicsFont CreateGraphicsFont( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3D10Texture object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ITexture CreateTexture( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a Texture objects and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@param pTexture Texture array to be created.
		*	@param count	Creation count.
		*/
		MapilVoid CreateTextures( const MapilTChar* pKeyStr, ITexture* pTexture, MapilInt32 count );
		/**
		*	@brief			Create a D3D10PointSprite object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IPointSprite CreatePointSprite( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3D10Rectangle3D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IRectangle3D CreateRectangle3D( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3D10NSidedPolygon3D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		INSidedPolygon3D CreateNSidedPolygon3D( const MapilTChar* pKeyStr );
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*/
		MapilVoid Reflesh();
		MapilVoid LostAllResources();
		MapilVoid RestoreAllResources();
	};
}

#endif	// DIRECT3D_VERSION
#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DGRAPHICSFACTORY_H