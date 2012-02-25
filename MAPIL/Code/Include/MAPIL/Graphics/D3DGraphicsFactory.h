/**
*	@file	D3DGraphicsFactory.h
*	@brief	D3DGraphicsFactory class is derived class from GraphicsFactory class.
*			D3DGraphicsFactory is implemented for Direct3D. The users shouldn't
*			call method from this class directly.
*	@date	2011.8.26 (Fri) 17:57
*/

#ifndef INCLUDED_MAPIL_D3DGRAPHICSFACTORY_H
#define INCLUDED_MAPIL_D3DGRAPHICSFACTORY_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_DIRECT3D )

#include "GraphicsFactory.h"
#include "GraphicsResourceManager.hpp"
#include "D3DGraphicsController.h"
#include "D3DCamera.h"
#include "D3DDirectionalLight.h"
#include "D3DPointLight.h"
#include "D3DModel.h"
#include "D3DGraphicsFont.h"
#include "D3DTexture.h"
#include "D3DPointSprite.h"
#include "D3DRectangle3D.h"
#include "D3DNSidedPolygon3D.h"
#include "D3DCanvas2D.h"
#include "D3DSprite.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{

	class D3DGraphicsFactory : public GraphicsFactory
	{
	private:
		GraphicsResourceManager < D3DCanvas2D >				m_CanvasRM;			///< Resource manager for the D3DCanvas object.
		GraphicsResourceManager < D3DSprite >				m_SpriteRM;			///< Resource manager for the D3DSprite object.
		GraphicsResourceManager < D3DCamera >				m_CameraRM;			///< Resource manager for the D3DCamera object.
		GraphicsResourceManager < D3DGraphicsController >	m_GraphicsCtrlRM;	///< Resource manager for the D3DGraphicsController object.
		GraphicsResourceManager < D3DDirectionalLight >		m_DirLightRM;		///< Resource manager for the D3DDirectionalLight object.
		GraphicsResourceManager < D3DPointLight >			m_PLightRM;			///< Resource manager for the D3DPointLight object.
		GraphicsResourceManager < D3DModel >				m_ModelRM;			///< Resource manager for the D3DModel object.
		GraphicsResourceManager < D3DGraphicsFont >			m_GraphicsFontRM;	///< Resource manager for the D3DGraphicsFont object.
		GraphicsResourceManager < D3DTexture >				m_TexRM;			///< Resource manager for the D3DTexture object.
		GraphicsResourceManager < D3DPointSprite >			m_PSpriteRM;		///< Resource manager for the D3DPointSprite object.
		GraphicsResourceManager < D3DRectangle3D >			m_Rect3DRM;			///< Resource manager for the D3DRectangle3D object.
		GraphicsResourceManager < D3DNSidedPolygon3D >		m_NPoly3DRM;		///< Resource manager for the D3DNSidedPolygon3D object.
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		D3DGraphicsFactory( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~D3DGraphicsFactory();
		/**
		*	@brief			Create a D3DCanvas2D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ICanvas2D CreateCanvas2D( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3DSprite object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ISprite CreateSprite( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3DCamera object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ICamera CreateCamera( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3DGraphicsController object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IGraphicsController CreateGraphicsController( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3DDirectionalLight object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IDirectionalLight CreateDirectionalLight( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3DPointLight object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IPointLight CreatePointLight( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3DModel object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IModel CreateModel( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3DGraphicsFont object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IGraphicsFont CreateGraphicsFont( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3DTexture object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ITexture CreateTexture( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3DPointSprite object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IPointSprite CreatePointSprite( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3DRectangle3D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IRectangle3D CreateRectangle3D( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a D3DNSidedPolygon3D object and return the interface of the created object.
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

#endif	// API_DIRECT3D

#endif	// INCLUDED_MAPIL_D3DGRAPHICSFACTORY_H