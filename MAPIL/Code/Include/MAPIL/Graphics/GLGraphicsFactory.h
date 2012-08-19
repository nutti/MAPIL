/**
*	@file	GLGraphicsFactory.h
*	@brief	GLGraphicsFactory class is derived class from GraphicsFactory class.
*			GLGraphicsFactory is implemented for OpenGL. The users shouldn't
*			call method from this class directly.
*	@date	2011.6.18 (Sat) 15:57
*/

#ifndef INCLUDED_MAPIL_GLGRAPHICSFACTORY_H
#define INCLUDED_MAPIL_GLGRAPHICSFACTORY_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#if defined ( API_OPENGL )

#include "GraphicsFactory.h"
#include "GraphicsResourceManager.hpp"
#include "GLCanvas2D.h"
#include "GLCanvas3D.h"
#include "GLCamera.h"
#include "GLGraphicsController.h"
#include "GLDirectionalLight.h"
#include "GLPointLight.h"
#include "GLModel.h"
#include "GLGraphicsFont.h"
#include "GLTexture.h"
#include "GLPointSprite.h"
#include "GLRectangle3D.h"
#include "GLSprite.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class GLGraphicsFactory : public GraphicsFactory
	{
	private:
		GraphicsResourceManager < GLCanvas2D >				m_CanvasRM;			///< Resource manager for the GLCanvas2D object.
		GraphicsResourceManager < GLCanvas3D >				m_Canvas3DRM;		///< Resource manager for the GLCanvas3D object.
		GraphicsResourceManager < GLSprite >				m_SpriteRM;			///< Resource manager for the GLSprite object.
		GraphicsResourceManager < GLCamera >				m_CameraRM;			///< Resource manager for the GLCamera object.
		GraphicsResourceManager < GLGraphicsController >	m_GraphicsCtrlRM;	///< Resource manager for the GLGraphicsController object.
		GraphicsResourceManager < GLDirectionalLight >		m_DirLightRM;		///< Resource manager for the GLDirectionalLight object.
		GraphicsResourceManager < GLPointLight >			m_PLightRM;			///< Resource manager for the GLPointLight object.
		GraphicsResourceManager < GLModel >					m_ModelRM;			///< Resource manager for the GLModel object.
		GraphicsResourceManager < GLGraphicsFont >			m_GraphicsFontRM;	///< Resource manager for the GLGraphicsFont object.
		GraphicsResourceManager < GLTexture >				m_TexRM;			///< Resource manager for the GLTexture object.
		GraphicsResourceManager < GLPointSprite >			m_PSpriteRM;		///< Resource manager for the GLPointSprite object.
		GraphicsResourceManager < GLRectangle3D >			m_Rect3DRM;			///< Resource manager for the GLRectangle3D object.
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to the GraphicsDevice object.
		*/
		GLGraphicsFactory( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~GLGraphicsFactory();
		/**
		*	@brief			Create a GLCanvas2D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ICanvas2D CreateCanvas2D( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a GLCanvas3D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ICanvas3D CreateCanvas3D( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a GLSprite object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ISprite CreateSprite( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a GLCamera object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		ICamera CreateCamera( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a GLGraphicsController object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IGraphicsController CreateGraphicsController( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a GLDirectionalLight object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IDirectionalLight CreateDirectionalLight( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a GLPointLight object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IPointLight CreatePointLight( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a GLModel object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IModel CreateModel( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a GLGraphicsFont object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IGraphicsFont CreateGraphicsFont( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a GLTexture object and return the interface of the created object.
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
		*	@brief			Create a GLPointSprite object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IPointSprite CreatePointSprite( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a GLRectangle3D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		IRectangle3D CreateRectangle3D( const MapilTChar* pKeyStr );
		/**
		*	@brief			Create a GLNSidedPolygon3D object and return the interface of the created object.
		*	@param pKeyStr	String for searching the created object.
		*	@return			The interface of the created object.
		*/
		INSidedPolygon3D CreateNSidedPolygon3D( const MapilTChar* pKeyStr ){ return INSidedPolygon3D(); }
		/**
		*	@brief Delete all the objects whose reference count is 0.
		*/
		MapilVoid Reflesh();
	};
}

#endif	// API_OPENGL

#endif	// INCLUDED_MAPIL_GLGRAPHICSFACTORY_H