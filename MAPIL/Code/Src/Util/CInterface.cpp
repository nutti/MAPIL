/**
*	@file	CInterface.h
*	@brief	
*	@date	2012.6.30 (Sat) 9:42
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( USE_C_INTERFACE )

#include "../../Include/MAPIL/Util/CInterface.h"

#include "../../Include/MAPIL/GUI/GUIFactory.h"

#include "../../Include/MAPIL/Graphics/GraphicsFactory.h"
#include "../../Include/MAPIL/Graphics/GraphicsController.h"
#include "../../Include/MAPIL/Graphics/Camera.h"
#include "../../Include/MAPIL/Graphics/DirectionalLight.h"
#include "../../Include/MAPIL/Graphics/PointLight.h"
#include "../../Include/MAPIL/Graphics/Model.h"
#include "../../Include/MAPIL/Graphics/GraphicsFont.h"
#include "../../Include/MAPIL/Graphics/Texture.h"
#include "../../Include/MAPIL/Graphics/PointSprite.h"
#include "../../Include/MAPIL/Graphics/Rectangle3D.h"
#include "../../Include/MAPIL/Graphics/NSidedPolygon3D.h"
#include "../../Include/MAPIL/Graphics/Canvas2D.h"
#include "../../Include/MAPIL/Graphics/Canvas3D.h"
#include "../../Include/MAPIL/Graphics/Sprite.h"

#include "../../Include/MAPIL/Input/InputFactory.h"
#include "../../Include/MAPIL/Input/Keyboard.h"
#include "../../Include/MAPIL/Input/Mouse.h"

#include "../../Include/MAPIL/Sound/SoundFactory.h"
#include "../../Include/MAPIL/Sound/StaticBuffer.h"
#include "../../Include/MAPIL/Sound/StreamingBuffer.h"

#include "../../Include/MAPIL/Util/Singleton.hpp"
#include "../../Include/MAPIL/Util/String.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/IO/Archiver.h"

#include <vector>
#include <list>
#include <string>

namespace MAPIL
{
	template < typename T >
	struct ResourceTag
	{
		T			m_Resource;
		MapilBool	m_IsUsed;
	};

	// Batch work of texture.
	struct TextureBatchWork
	{
		MapilUInt32					m_ID;
		Matrix4x4 < MapilFloat32 >	m_TransMat;
		MapilUInt32					m_Color;
	};

	// Batch work of string.
	struct StringBatchWork
	{
		std::basic_string < MapilTChar >	m_Str;
		Matrix4x4 < MapilFloat32 >			m_TransMat;
		MapilUInt32							m_Color;
	};

	typedef std::list < TextureBatchWork >		TextureBatch;
	typedef std::list < StringBatchWork >		StringBatch;

	typedef ResourceTag < IRectangle3D >		Rectangle3DTag;
	typedef ResourceTag < IModel >				ModelTag;
	typedef ResourceTag < ICamera >				CameraTag;
	typedef ResourceTag < IGraphicsFont >		GraphicsFontTag;
	typedef ResourceTag < IPointSprite >		PointSpriteTag;
	typedef ResourceTag < ITexture >			TextureTag;
	typedef ResourceTag < IDirectionalLight >	DirectionalLightTag;
	typedef ResourceTag < IPointLight >			PointLightTag;
	typedef ResourceTag < IStaticBuffer >		StaticBufferTag;
	typedef ResourceTag < IStreamingBuffer >	StreamingBufferTag;

	typedef std::vector < Rectangle3DTag >		Rectangle3DList;
	typedef std::vector < ModelTag >			ModelList;
	typedef std::vector < CameraTag >			CameraList;
	typedef std::vector < GraphicsFontTag >		GraphicsFontList;
	typedef std::vector < PointSpriteTag >		PointSpriteList;
	typedef std::vector < TextureTag >			TextureList;
	typedef std::vector < DirectionalLightTag >	DirectionalLightList;
	typedef std::vector < PointLightTag >		PointLightList;
	typedef std::vector < StaticBufferTag >		StaticBufferList;
	typedef std::vector < StreamingBufferTag >	StreamingBufferList;

	class ResourceHolder : public Singleton < ResourceHolder > 
	{
	private:
		ResourceHolder();
		~ResourceHolder();
	public:
		friend class Singleton < ResourceHolder >;

		MapilInt32			m_GUIAPI;
		IGUIDevice			m_GUIDev;
		GUIFactory*			m_pGUIFactory;

		MapilInt32			m_GraphicsAPI;
		MapilInt32			m_GraphicsAPIVersion;
		IGraphicsDevice		m_GraphicsDev;
		GraphicsFactory*	m_pGraphicsFactory;

		MapilInt32			m_InputAPI;
		IInputDevice		m_InputDev;
		InputFactory*		m_pInputFactory;

		MapilInt32			m_SoundAPI;
		ISoundDevice		m_SoundDev;
		SoundFactory*		m_pSoundFactory;

		// Global resources.
		IWindow 			m_MainWnd;
		IGraphicsContext	m_GC;
		IGraphicsController	m_GraphicsCtrl;
		ICanvas2D			m_Canvas2D;
		ICanvas3D			m_Canvas3D;
		ISprite				m_Sprite;
		ICamera				m_Camera;
		IGraphicsFont		m_GraphicsFont;
		IKeyboard			m_Keyboard;

		// Local resources.
		Rectangle3DList			m_LocalRectangle3DList;
		ModelList				m_LocalModelList;
		CameraList				m_LocalCameraList;
		GraphicsFontList		m_LocalGraphicsFontList;
		PointSpriteList			m_LocalPointSpriteList;
		TextureList				m_LocalTextureList;
		DirectionalLightList	m_LocalDirectionalLightList;
		PointLightList			m_LocalPointLightList;
		StaticBufferList		m_LocalStaticBufferList;
		StreamingBufferList		m_LocalStreamingBufferList;

		// Batch
		TextureBatch			m_TextureBatch;
		StringBatch				m_StringBatch;

		// Archiver.
		std::vector < Archiver* >	m_ArchiverList;
	};

	ResourceHolder::ResourceHolder() :	m_GUIAPI( GUI_API_NONE ),
										m_GUIDev(),
										m_pGUIFactory( NULL ),

										m_GraphicsAPI( GRAPHICS_API_NONE ),
#if defined ( API_DIRECT3D )
										m_GraphicsAPIVersion( D3D_VER_UNKNOWN ),
#elif defined ( API_OPENGL )
										m_GraphicsAPIVersion( 0 ),
#endif
										m_GraphicsDev(),
										m_pGraphicsFactory( NULL ),

										m_InputAPI( INPUT_API_NONE ),
										m_InputDev(),
										m_pInputFactory( NULL ),

										m_SoundAPI( SOUND_API_NONE ),
										m_SoundDev(),
										m_pSoundFactory( NULL ),

										m_LocalRectangle3DList(),
										m_LocalModelList(),
										m_LocalCameraList(),
										m_LocalGraphicsFontList(),
										m_LocalPointSpriteList(),
										m_LocalTextureList(),
										m_LocalDirectionalLightList(),
										m_LocalPointLightList(),
										m_LocalStaticBufferList(),
										m_LocalStreamingBufferList(),

										m_TextureBatch(),
										m_StringBatch()
	{
	}

	ResourceHolder::~ResourceHolder()
	{
		SafeDelete( m_pSoundFactory );
		SafeDelete( m_pInputFactory );
		SafeDelete( m_pGraphicsFactory );
		SafeDelete( m_pGUIFactory );

		for( MapilUInt32 i = 0; i < m_ArchiverList.size(); ++i ){
			SafeDelete( m_ArchiverList[ i ] );
		}
	}

	static MapilTChar* ToTSTR( const MapilChar* pStr )
	{
		static MapilTChar str[ 1024 ];

		ZeroObject( str, sizeof( str ) );
		ConvertToTChar( pStr, ::strlen( pStr ), str, 1024 );

		return str;
	}

	static MapilVoid SetupFactories()
	{
		ResourceHolder* p = ResourceHolder::GetInst();

		// Setup API.
		if( p->m_GUIAPI == GUI_API_NONE ){
#if defined ( API_WIN32API )
			SetGUIAPI( GUI_API_WIN32API );
#elif defined ( API_GTK )
			SetGUIAPI( GUI_API_GTK );
#endif
		}

		if( p->m_GraphicsAPI == GRAPHICS_API_NONE ){
#if defined ( API_DIRECT3D )
			if( p->m_GraphicsAPIVersion == D3D_VER_UNKNOWN ){
				SetGraphicsAPI( GRAPHICS_API_DIRECT3D, D3D_VER_9_0_C );
			}
			else{
				SetGraphicsAPI( GRAPHICS_API_DIRECT3D );
			}
#elif defined ( API_OPENGL )
			SetGraphicsAPI( GRAPHICS_API_OPENGL, 0 );
#endif
		}

		if( p->m_InputAPI == INPUT_API_NONE ){
#if defined ( API_DIRECTINPUT )
			SetInputAPI( INPUT_API_DIRECTINPUT );
#elif defined ( API_WIN32API )
			SetInputAPI( INPUT_API_WIN32API );
#endif
		}

		if( p->m_SoundAPI == INPUT_API_NONE ){
#if defined ( API_OPENAL )
			SetSoundAPI( SOUND_API_OPENAL );
#endif
		}

		// Create GUI factory.
		if( p->m_GUIAPI != GUI_API_NONE ){
			p->m_GUIDev = CreateGUIDevice( p->m_GUIAPI );
			p->m_pGUIFactory = CreateGUIFactory( p->m_GUIDev );
		}
		// Create Graphics factory.
		if( p->m_GraphicsAPI != GRAPHICS_API_NONE ){
			p->m_GraphicsDev = CreateGraphicsDevice( p->m_GraphicsAPI, p->m_GraphicsAPIVersion );
			p->m_pGraphicsFactory = CreateGraphicsFactory( p->m_GraphicsDev );
		}
		// Create Input factory.
		if( p->m_InputAPI != INPUT_API_NONE ){
			p->m_InputDev = CreateInputDevice( p->m_InputAPI );
			p->m_pInputFactory = CreateInputFactory( p->m_InputDev );
		}
		// Create Sound factory.
		if( p->m_SoundAPI != SOUND_API_NONE ){
			p->m_SoundDev = CreateSoundDevice( p->m_SoundAPI );
			p->m_pSoundFactory = CreateSoundFactory( p->m_SoundDev );
		}
	}

	static MapilInt32 SetupGraphics()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		if( p->m_pGraphicsFactory == NULL ){
			return -1;
		}
		// Create graphics device.
		p->m_GraphicsDev->Create( p->m_GC );
		// Craete graphics controller.
		p->m_GraphicsCtrl = p->m_pGraphicsFactory->CreateGraphicsController( TSTR( "Global Graphics Ctrl" ) );
		p->m_GraphicsCtrl->Create( p->m_GC );
		if( p->m_GraphicsAPI == GRAPHICS_API_DIRECT3D ){
#if defined ( API_DIRECT3D )
			if( p->m_GraphicsAPIVersion == D3D_VER_9_0_C ){
				// Create canvas 2D object.
				p->m_Canvas2D = p->m_pGraphicsFactory->CreateCanvas2D( TSTR( "Global Canvas 2D" ) );
				p->m_Canvas2D->Create();
				// Create canvas 3D object.
				p->m_Canvas3D = p->m_pGraphicsFactory->CreateCanvas3D( TSTR( "Global Canvas 3D" ) );
				p->m_Canvas3D->Create();
				// Create camera object.
				p->m_Camera = p->m_pGraphicsFactory->CreateCamera( TSTR( "Global Camera" ) );
				p->m_Camera->Create(	0.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 0.0f, 0.0f );
				// Create sprite object.
				p->m_Sprite = p->m_pGraphicsFactory->CreateSprite( TSTR( "Global Sprite" ) );
				p->m_Sprite->Create( p->m_GraphicsCtrl );
				// Create graphics font object.
				p->m_GraphicsFont = p->m_pGraphicsFactory->CreateGraphicsFont( TSTR( "Global Graphics Font" ) );
				FontFormat fmt;
				ZeroObject( &fmt, sizeof( fmt ) );
				p->m_GraphicsFont->Create( fmt );
			}
#endif	// API_DIRECT3D
		}

		return 0;
	}

	static MapilInt32 SetupGUI( const MapilChar* pWndName, MapilInt32 width, MapilInt32 height )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		if( p->m_pGUIFactory == NULL ){
			return -1;
		}
		
		// Create window.
		MapilTChar* pStr = ToTSTR( pWndName );
		std::string gcName = pWndName;
		gcName += " Graphics Context";
		p->m_MainWnd = p->m_pGUIFactory->CreateWnd( pStr );
		p->m_MainWnd->Create( pStr, width, height );
		// Create graphics context.
		pStr = ToTSTR( gcName.c_str() );
		p->m_GC = p->m_pGUIFactory->CreateGraphicsContext( pStr );
		p->m_GC->Create( pStr, width, height, p->m_MainWnd );
		
		return 0;
	}

	static MapilInt32 SetupInput()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		if( p->m_pInputFactory == NULL ){
			return -1;
		}
		p->m_InputDev->Create();
		p->m_Keyboard = p->m_pInputFactory->CreateKeyboard( TSTR( "Global Keyboard" ) );
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_Keyboard->Create( p->m_MainWnd );
		return 0;
	}

	static MapilInt32 SetupSound()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		if( p->m_pSoundFactory == NULL ){
			return -1;
		}
		p->m_SoundDev->Create();
		return 0;
	}

	MapilInt32 InitMAPIL( const MapilChar* pWndName, MapilInt32 width, MapilInt32 height )
	{
		SetupFactories();
		SetupGUI( pWndName, width, height );
		SetupGraphics();
		SetupInput();
		SetupSound();

		return 0;
	}

	// Set GUI API.
	MapilVoid SetGUIAPI( MapilInt32 api )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		p->m_GUIAPI = api;
	}

	// Set Graphics API.
	MapilVoid SetGraphicsAPI( MapilInt32 api, MapilInt32 version )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		p->m_GraphicsAPI = api;
		p->m_GraphicsAPIVersion = version;
	}

	// Set Input API.
	MapilVoid SetInputAPI( MapilInt32 api )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		p->m_InputAPI = api;
	}

	// Set Sound API.
	MapilVoid SetSoundAPI( MapilInt32 api )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		p->m_SoundAPI = api;
	}

	// Set Icon.
	MapilVoid SetIcon( const MapilChar* pFileName )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		p->m_MainWnd->SetIcon( ToTSTR( pFileName ) );
	}

	template < typename T >
	MapilUInt32 GetEmptyIndex( T* pList )
	{
		MapilUInt32 size = pList->size();;
		for( MapilUInt32 i = 0; i < size; ++i ){
			if( ( *pList )[ i ].m_IsUsed == MapilFalse ){
				return i;
			}
		}
		return size;
	}

	// Craete camera.
	MapilInt32 CreateCamera()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		std::basic_string < MapilTChar > str = TSTR( "Local Camera " );
		MapilUInt32 index = GetEmptyIndex( &p->m_LocalCameraList );
		str += index;
		CameraTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pGraphicsFactory->CreateCamera( str.c_str() );
		tag.m_Resource->Create(	0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f, 0.0f );
		if( index == p->m_LocalCameraList.size() ){
			p->m_LocalCameraList.push_back( tag );
		}
		else{
			p->m_LocalCameraList[ index ] = tag;
		}

		return index;
	}

	// Create grahpics font.
	MapilInt32 CreateGraphicsFont( const FontFormat& fmt )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		std::basic_string < MapilTChar > str = TSTR( "Local Graphics Font " );
		MapilUInt32 index = GetEmptyIndex( &p->m_LocalGraphicsFontList );
		str += index;
		GraphicsFontTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pGraphicsFactory->CreateGraphicsFont( str.c_str() );
		tag.m_Resource->Create( fmt );
		if( index == p->m_LocalGraphicsFontList.size() ){
			p->m_LocalGraphicsFontList.push_back( tag );
		}
		else{
			p->m_LocalGraphicsFontList[ index ] = tag;
		}

		return index;
	}

	// Create texture.
	MapilInt32 CreateTexture( const MapilChar* pFileName )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		MapilTChar tstr[ 1024 ];
		ConvertToTChar( pFileName, -1, tstr, 1024 );
		std::basic_string < MapilTChar > str = tstr;
		MapilInt32 index = GetEmptyIndex( &p->m_LocalTextureList );
		TextureTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pGraphicsFactory->CreateTexture( str.c_str() );
		tag.m_Resource->Create( str.c_str() );
		if( index == p->m_LocalTextureList.size() ){
			p->m_LocalTextureList.push_back( tag );
		}
		else{
			p->m_LocalTextureList[ index ] = tag;
		}

		return index;
	}

	// Create texture from archive file.
	MapilInt32 CreateTexture( MapilUInt32 archiveHandle, const MapilChar* pFilePath )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		Assert( p->m_ArchiverList.size() > archiveHandle, CURRENT_POSITION, TSTR( "Invalid index is input." ), -1 );
		MapilTChar tstr[ 1024 ];
		ConvertToTChar( pFilePath, -1, tstr, 1024 );
		std::basic_string < MapilTChar > str = tstr;
		MapilInt32 index = GetEmptyIndex( &p->m_LocalTextureList );
		TextureTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pGraphicsFactory->CreateTexture( str.c_str() );
		tag.m_Resource->Create( p->m_ArchiverList[ archiveHandle ], str.c_str() );
		if( index == p->m_LocalTextureList.size() ){
			p->m_LocalTextureList.push_back( tag );
		}
		else{
			p->m_LocalTextureList[ index ] = tag;
		}

		return index;
	}

	// Create texture. ( With split. )
	MapilVoid CreateSplitedTexture(	MapilInt32* pIndex,
									const MapilChar* pFileName,
									MapilInt32 column,
									MapilInt32 row,
									MapilInt32 width,
									MapilInt32 height )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		MapilTChar tstr[ 1024 ];
		ConvertToTChar( pFileName, -1, tstr, 1024 );
		std::basic_string < MapilTChar > str = tstr;

		// Splited textures.
		ITexture* pTexture = new ITexture [ column * row ];
		p->m_pGraphicsFactory->CreateTextures( str.c_str(), pTexture, row * column );
		// Base texture.
		ITexture base;
		base = p->m_pGraphicsFactory->CreateTexture( str.c_str() );
		base->Create( str.c_str() );
		// Split the base texture.
		base->SplitCopy( pTexture, column, row, width, height );

		for( MapilInt32 i = 0; i < row * column; ++i ){
			MapilInt32 index = GetEmptyIndex( &p->m_LocalTextureList );
			TextureTag tag;
			tag.m_IsUsed = MapilTrue;
			tag.m_Resource = pTexture[ i ];
			if( index == p->m_LocalTextureList.size() ){
				p->m_LocalTextureList.push_back( tag );
			}
			else{
				p->m_LocalTextureList[ index ] = tag;
			}
			pIndex[ i ] = index;
		}

		SafeDeleteArray( pTexture );
	}

	// Create texture from archive file.
	MapilVoid CreateSplitedTexture(	MapilInt32* pIndex,
									MapilUInt32 archiveHandle,
									const MapilChar* pFilePath,
									MapilInt32 column,
									MapilInt32 row,
									MapilInt32 width,
									MapilInt32 height )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		Assert( p->m_ArchiverList.size() > archiveHandle, CURRENT_POSITION, TSTR( "Invalid index is input." ), -1 );
		MapilTChar tstr[ 1024 ];
		ConvertToTChar( pFilePath, -1, tstr, 1024 );
		std::basic_string < MapilTChar > str = tstr;

		// Splited textures.
		ITexture* pTexture = new ITexture [ column * row ];
		p->m_pGraphicsFactory->CreateTextures( str.c_str(), pTexture, row * column );
		// Base texture.
		ITexture base;
		base = p->m_pGraphicsFactory->CreateTexture( str.c_str() );
		base->Create( p->m_ArchiverList[ archiveHandle ], str.c_str() );
		// Split the base texture.
		base->SplitCopy( pTexture, column, row, width, height );

		for( MapilInt32 i = 0; i < row * column; ++i ){
			MapilInt32 index = GetEmptyIndex( &p->m_LocalTextureList );
			TextureTag tag;
			tag.m_IsUsed = MapilTrue;
			tag.m_Resource = pTexture[ i ];
			if( index == p->m_LocalTextureList.size() ){
				p->m_LocalTextureList.push_back( tag );
			}
			else{
				p->m_LocalTextureList[ index ] = tag;
			}
			pIndex[ i ] = index;
		}

		SafeDeleteArray( pTexture );
	}

	// Create point sprite.
	MapilInt32 CreatePointSprite( MapilInt32 num, MapilInt32 texture )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		std::basic_string < MapilTChar > str = TSTR( "Local Point Sprite " );
		MapilInt32 index = GetEmptyIndex( &p->m_LocalPointSpriteList );
		str += index;
		PointSpriteTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource= p->m_pGraphicsFactory->CreatePointSprite( str.c_str() );
		tag.m_Resource->Create( num, p->m_LocalTextureList[ texture ].m_Resource, VERTEX_MANAGEMENT_NONE );
		if( index == p->m_LocalPointSpriteList.size() ){
			p->m_LocalPointSpriteList.push_back( tag );
		}
		else{
			p->m_LocalPointSpriteList[ index ] = tag;
		}

		return index;
	}

	// Create directional light.
	MapilInt32 CreateDirectionalLight()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		std::basic_string < MapilTChar > str = TSTR( "Local Directional Light " );
		MapilUInt32 index = GetEmptyIndex( &p->m_LocalCameraList );
		str += index;
		DirectionalLightTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pGraphicsFactory->CreateDirectionalLight( str.c_str() );
		tag.m_Resource->Create(	MAPIL::ColorARGB < MapilFloat32 > ( 0.0f, 0.0f, 0.0f, 0.0f ),
								MAPIL::ColorARGB < MapilFloat32 > ( 0.0f, 0.0f, 0.0f, 0.0f ),
								MAPIL::ColorARGB < MapilFloat32 > ( 0.0f, 0.0f, 0.0f, 0.0f ),
								MAPIL::Vector3 < MapilFloat32 > ( 0.0f, 0.0f, 0.0f ),
								0.0f, 1.0f, 0.0f );
		if( index == p->m_LocalDirectionalLightList.size() ){
			p->m_LocalDirectionalLightList.push_back( tag );
		}
		else{
			p->m_LocalDirectionalLightList[ index ] = tag;
		}

		return index;
	}

	// Create point light.
	MapilInt32 CreatePointLight()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		std::basic_string < MapilTChar > str = TSTR( "Local Point Light " );
		MapilUInt32 index = GetEmptyIndex( &p->m_LocalCameraList );
		str += index;
		PointLightTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pGraphicsFactory->CreatePointLight( str.c_str() );
		tag.m_Resource->Create(	MAPIL::ColorARGB < MapilFloat32 > ( 0.0f, 0.0f, 0.0f, 0.0f ),
								MAPIL::ColorARGB < MapilFloat32 > ( 0.0f, 0.0f, 0.0f, 0.0f ),
								MAPIL::ColorARGB < MapilFloat32 > ( 0.0f, 0.0f, 0.0f, 0.0f ),
								MAPIL::Vector3 < MapilFloat32 > ( 0.0f, 0.0f, 0.0f ),
								0.0f, 1.0f, 0.0f );
		if( index == p->m_LocalPointLightList.size() ){
			p->m_LocalPointLightList.push_back( tag );
		}
		else{
			p->m_LocalPointLightList[ index ] = tag;
		}

		return index;
	}

	// Create spot light.
	MapilInt32 CreateSpotLight()
	{
		return -1;
	}

	// Create static buffer.
	MapilInt32 CreateStaticBuffer( const MapilChar* pFileName )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pSoundFactory != NULL, CURRENT_POSITION, TSTR( "Sound factory is not created yet." ), -1 );
		MapilTChar tstr[ 1024 ];
		ConvertToTChar( pFileName, -1, tstr, 1024 );
		std::basic_string < MapilTChar > str = tstr;
		MapilInt32 index = GetEmptyIndex( &p->m_LocalStaticBufferList );
		StaticBufferTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pSoundFactory->CreateStaticBuffer( str.c_str() );
		tag.m_Resource->Create( str.c_str() );
		if( index ==p->m_LocalStaticBufferList.size() ){
			p->m_LocalStaticBufferList.push_back( tag );
		}
		else{
			p->m_LocalStaticBufferList[ index ] = tag;
		}

		return index;
	}

	// Create static buffer from archive file.
	MapilUInt32 CreateStaticBuffer( MapilUInt32 archiveHandle, const MapilChar* pFilePath )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pSoundFactory != NULL, CURRENT_POSITION, TSTR( "Sound factory is not created yet." ), -1 );
		Assert( p->m_ArchiverList.size() > archiveHandle, CURRENT_POSITION, TSTR( "Invalid index is input." ), -1 );
		MapilTChar tstr[ 1024 ];
		ConvertToTChar( pFilePath, -1, tstr, 1024 );
		std::basic_string < MapilTChar > str = tstr;
		MapilInt32 index = GetEmptyIndex( &p->m_LocalStaticBufferList );
		StaticBufferTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pSoundFactory->CreateStaticBuffer( str.c_str() );
		tag.m_Resource->Create( p->m_ArchiverList[ archiveHandle ], str.c_str() );
		if( index == p->m_LocalStaticBufferList.size() ){
			p->m_LocalStaticBufferList.push_back( tag );
		}
		else{
			p->m_LocalStaticBufferList[ index ] = tag;
		}

		return index;
	}

	// Create streaming buffer.
	MapilInt32 CreateStreamingBuffer( const MapilChar* pFileName )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pSoundFactory != NULL, CURRENT_POSITION, TSTR( "Sound factory is not created yet." ), -1 );
		MapilTChar tstr[ 1024 ];
		ConvertToTChar( pFileName, -1, tstr, 1024 );
		std::basic_string < MapilTChar > str = tstr;
		MapilInt32 index = GetEmptyIndex( &p->m_LocalStreamingBufferList );
		StreamingBufferTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pSoundFactory->CreateStreamingBuffer( str.c_str() );
		tag.m_Resource->Create( str.c_str() );
		if( index == p->m_LocalStreamingBufferList.size() ){
			p->m_LocalStreamingBufferList.push_back( tag );
		}
		else{
			p->m_LocalStreamingBufferList[ index ] = tag;
		}

		return index;
	}

	// Create streaming buffer from archive file.
	MapilUInt32 CreateStreamingBuffer( MapilUInt32 archiveHandle, const MapilChar* pFilePath )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pSoundFactory != NULL, CURRENT_POSITION, TSTR( "Sound factory is not created yet." ), -1 );
		Assert( p->m_ArchiverList.size() > archiveHandle, CURRENT_POSITION, TSTR( "Invalid index is input." ), -1 );
		MapilTChar tstr[ 1024 ];
		ConvertToTChar( pFilePath, -1, tstr, 1024 );
		std::basic_string < MapilTChar > str = tstr;
		MapilInt32 index = GetEmptyIndex( &p->m_LocalStreamingBufferList );
		StreamingBufferTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pSoundFactory->CreateStreamingBuffer( str.c_str() );
		MapilTChar arName[ 1024 ];
		ConvertToTChar( p->m_ArchiverList[ archiveHandle ]->GetArchiveFileName(), -1, arName, 1024 );
		tag.m_Resource->Create( arName, str.c_str() );
		if( index == p->m_LocalStreamingBufferList.size() ){
			p->m_LocalStreamingBufferList.push_back( tag );
		}
		else{
			p->m_LocalStreamingBufferList[ index ] = tag;
		}

		return index;
	}

	template < typename T >
	MapilVoid DeleteResource( std::vector < ResourceTag < SharedPointer < T > > >* pList, MapilUInt32 index, const MapilChar* pPosition )
	{
		Assert(	pList->size() > index,
				pPosition, TSTR( "Invalid index is inputted." ), -1 );
		ResourceTag < SharedPointer < T > > tag;
		SharedPointer < T > sp;
		tag.m_Resource = sp;
		tag.m_IsUsed = MapilFalse;
		( *pList )[ index ] = tag;
	}

	// Delete camera.
	MapilVoid DeleteCamera( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		DeleteResource( &p->m_LocalCameraList, index, CURRENT_POSITION );
	}

	// Delete graphics font.
	MapilVoid DeleteGraphicsFont( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		DeleteResource( &p->m_LocalGraphicsFontList, index, CURRENT_POSITION );
	}

	// Delete texture.
	MapilVoid DeleteTexture( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		DeleteResource( &p->m_LocalTextureList, index, CURRENT_POSITION );
	}

	// Delete point sprite.
	MapilVoid DeletePointSprite( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		DeleteResource( &p->m_LocalPointSpriteList, index, CURRENT_POSITION );
	}

	// Delete directional light.
	MapilVoid DeleteDirectionalLight( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		DeleteResource( &p->m_LocalDirectionalLightList, index, CURRENT_POSITION );
	}

	// Delete point light.
	MapilVoid DeletePointLight( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		DeleteResource( &p->m_LocalPointLightList, index, CURRENT_POSITION );
	}

	// Delete spot light.
	MapilVoid DeleteSpotLight( MapilUInt32 index )
	{
	}

	// Delete static buffer.
	MapilVoid DeleteStaticBuffer( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		DeleteResource( &p->m_LocalStaticBufferList, index, CURRENT_POSITION );
	}

	// Delete streaming buffer.
	MapilVoid DeleteStreamingBuffer( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		DeleteResource( &p->m_LocalStreamingBufferList, index, CURRENT_POSITION );
	}

	// Delete model.
	MapilVoid DeleteModel( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		DeleteResource( &p->m_LocalModelList, index, CURRENT_POSITION );
	}

	// Get keyboard state.
	MapilVoid GetKeyboardState( MapilUChar* pOut )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pInputFactory != NULL, CURRENT_POSITION, TSTR( "Input factory is not created yet." ), -1 );
		p->m_Keyboard->GetKeyMap( pOut );
	}

	// Begin rendering.
	MapilVoid BeginRendering()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->BeginRendering();
	}

	// End rendering.
	MapilVoid EndRendering()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->EndRendering();
	}

	// Begin rendering 2D Graphics.
	MapilVoid BeginRendering2DGraphics()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_Sprite->Begin();
	}

	// End rendering 2D Graphics.
	MapilVoid EndRendering2DGraphics()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_Sprite->End();
	}

	// Begin rendering 3D Graphics.
	MapilVoid BeginRendering3DGraphics()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_Canvas3D.GetPointer() != NULL, CURRENT_POSITION, TSTR( "Global canvas3D is not created yet." ), -1 );
		p->m_Canvas3D->Begin();
	}

	// End rendering 3D Graphics.
	MapilVoid EndRendering3DGraphics()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_Canvas3D.GetPointer() != NULL, CURRENT_POSITION, TSTR( "Global canvas3D is not created yet." ), -1 );
		p->m_Canvas3D->End();
	}

	// Enable blending.
	MapilVoid EnableBlending()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->EnableBlend( MapilTrue );
	}

	// Disable blending.
	MapilVoid DisableBlending()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->EnableBlend( MapilFalse );
	}

	// Enable lighting.
	MapilVoid EnableLighting()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->EnableLight( MapilTrue );
	}

	// Disable lighting.
	MapilVoid DisableLighting()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->EnableLight( MapilFalse );
	}

	// Enable z-bufffering.
	MapilVoid EnableZBuffering()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->EnableZBuffer( MapilTrue );
	}

	// Disable z-bufffering.
	MapilVoid DisableZBuffering()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->EnableZBuffer( MapilFalse );
	}

	// Enable fog.
	MapilVoid EnableFog()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->EnableFog( MapilTrue );
	}

	// Disable fog.
	MapilVoid DisableFog()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->EnableFog( MapilFalse );
	}

	// Set fog parameter.
	MapilVoid SetFogParam( MapilUInt32 color, MapilInt32 mode, MapilFloat32 begin, MapilFloat32 end, MapilFloat32 density )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->SetFogParam( color, mode, begin, end, density );
	}

	// Set texture mode.
	MapilVoid SetTextureMode( MapilInt32 mode )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->SetTextureMode( mode );
	}

	// Set cull mode.
	MapilVoid SetCullingMode( MapilInt32 mode )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->SetCullMode( mode );
	}

	// Set alphablend mode.
	MapilVoid SetAlphaBlendingMode( MapilInt32 mode )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->SetAlphaBlendMode( mode );
	}

	// Set sprite alpha blend mode.
	MapilVoid Set2DAlphaBlendingMode( MapilInt32 mode )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_Sprite->SetAlphaBlendMode( mode );
	}

	// Set view port.
	MapilVoid SetViewPort( MapilInt32 x, MapilInt32 y, MapilInt32 width, MapilInt32 height )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		p->m_GraphicsCtrl->SetViewport( x, y, width, height );
	}

	// Draw string ( with global sprite and global font. )
	MapilVoid DrawString( MapilFloat32 x, MapilFloat32 y, const MapilChar* pStr, ... )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );

		const MapilInt32 STRING_COLOR = 0xFFFFFFFF;
		const MapilInt32 MAXIMUM_STRING_LENGTH = 1024;

		// Analyze the variable length argument.
		::va_list list;
		va_start( list, pStr );
		MapilChar str[ MAXIMUM_STRING_LENGTH ];
		MapilInt32 strLen = _vscprintf( pStr, list ) + 1;
		if( strLen > 1024 ){
			va_end( list );
			return;
		}
		::vsprintf( str, pStr, list );
		va_end( list );

		// Convert char to tchar.
		MapilTChar tstr[ MAXIMUM_STRING_LENGTH ];
		ConvertToTChar( str, -1, tstr, MAXIMUM_STRING_LENGTH );

		p->m_Sprite->DrawString(	p->m_GraphicsFont,
									tstr,
									IMAGE_TRANSFORMATION_METHOD_CENTER_MOVE,
									Vector2 < MapilFloat32 > ( x, y ),
									STRING_COLOR );
	}

	// Draw color string ( with gloval sprite and global font ).
	MapilVoid DrawString( MapilFloat32 x, MapilFloat32 y, MapilUInt32 color, const MapilChar* pStr, ... )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );

		const int MAXIMUM_STRING_LENGTH = 1024;

		// Analyze the variable length argument.
		::va_list list;
		va_start( list, pStr );
		MapilChar str[ MAXIMUM_STRING_LENGTH ];
		MapilInt32 strLen = _vscprintf( pStr, list ) + 1;
		if( strLen > 1024 ){
			va_end( list );
			return;
		}
		vsprintf( str, pStr, list );
		va_end( list );

		// Convert char to tchar.
		MapilTChar tstr[ MAXIMUM_STRING_LENGTH ];
		ConvertToTChar( str, -1, tstr, MAXIMUM_STRING_LENGTH );

		p->m_Sprite->DrawString(	p->m_GraphicsFont,
									tstr,
									IMAGE_TRANSFORMATION_METHOD_CENTER_MOVE,
									Vector2 < MapilFloat32 > ( x, y ),
									color );
	}

	// Draw texture ( with global sprite ).
	MapilVoid DrawTexture( MapilUInt32 index, MapilFloat32 x, MapilFloat32 y, MapilBool centerize, MapilUInt32 color )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalTextureList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), index );

		// Create transformation matrix.
		//Matrix4x4 < MapilFloat32 > mat;
		//if( centerize ){
		//	CreateTranslationMat(	&mat,
		//							- p->m_LocalTextureList[ index ].m_Resource->GetSize().m_X * 1.0f / 2 + x,
		//							- p->m_LocalTextureList[ index ].m_Resource->GetSize().m_Y * 1.0f / 2 + y );
		//}
		//else{
		//	CreateTranslationMat( &mat, x, y );
		//}
		//p->m_Sprite->DrawTexture( p->m_LocalTextureList[ index ].m_Resource, mat, color );
		p->m_Sprite->DrawTexture( p->m_LocalTextureList[ index ].m_Resource, x, y, centerize, color );
	}

	// Draw texture ( with global sprite ).
	MapilVoid DrawTexture( MapilUInt32 index, MapilFloat32 x, MapilFloat32 y, MapilFloat32 angle, MapilBool centerize, MapilUInt32 color )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalTextureList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), index );

		// Create transformation matrix.
		Matrix4x4 < MapilFloat32 > mat;
		Matrix4x4 < MapilFloat32 > rotMat;
		Matrix4x4 < MapilFloat32 > transMat;
		CreateRotationZMat( &rotMat, angle );
		CreateTranslationMat( &transMat, x, y );
		if( centerize ){
			Matrix4x4 < MapilFloat32 > offsetMat;	// Centering of the texture.
			CreateTranslationMat(	&offsetMat,
									- p->m_LocalTextureList[ index ].m_Resource->GetSize().m_X * 1.0f / 2,
									- p->m_LocalTextureList[ index ].m_Resource->GetSize().m_Y * 1.0f / 2 );
			mat = offsetMat * rotMat * transMat;	// Centering -> Rotation -> Translation.
		}
		else{
			mat = rotMat * transMat;	// Rotation -> Translation.
		}
		p->m_Sprite->DrawTexture( p->m_LocalTextureList[ index ].m_Resource, mat, color );
	}

	// Draw texture ( with global sprite ).
	MapilVoid DrawTexture(	MapilUInt32 index,
							MapilFloat32 posX, MapilFloat32 posY,
							MapilFloat32 scaleX, MapilFloat32 scaleY,
							MapilBool centerize, MapilUInt32 color )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalTextureList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), index );

		// Create transformation matrix.
		Matrix4x4 < MapilFloat32 > mat;
		Matrix4x4 < MapilFloat32 > scaleMat;
		Matrix4x4 < MapilFloat32 > transMat;
		CreateScalingMat( &scaleMat, scaleX, scaleY );
		CreateTranslationMat( &transMat, posX, posY );
		if( centerize ){
			Matrix4x4 < MapilFloat32 > offsetMat;	// Centering of the texture.
			CreateTranslationMat(	&offsetMat,
									- p->m_LocalTextureList[ index ].m_Resource->GetSize().m_X * 1.0f / 2,
									- p->m_LocalTextureList[ index ].m_Resource->GetSize().m_Y * 1.0f / 2 );
			mat = offsetMat * scaleMat * transMat;	// Centering -> Scaling -> Translation.
		}
		else{
			mat = scaleMat * transMat;	// Scaling -> Translation.
		}
		p->m_Sprite->DrawTexture( p->m_LocalTextureList[ index ].m_Resource, mat, color );
	}

	// Draw texture ( with global sprite ).
	MapilVoid DrawTexture(	MapilUInt32 index,
							MapilFloat32 posX, MapilFloat32 posY,
							MapilFloat32 scaleX, MapilFloat32 scaleY,
							MapilFloat32 angle, MapilBool centerize, MapilUInt32 color )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalTextureList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), index + 50 );

		// Create transformation matrix.
		Matrix4x4 < MapilFloat32 > mat;
		Matrix4x4 < MapilFloat32 > rotMat;
		Matrix4x4 < MapilFloat32 > scaleMat;
		Matrix4x4 < MapilFloat32 > transMat;
		CreateRotationZMat( &rotMat, angle );
		CreateScalingMat( &scaleMat, scaleX, scaleY );
		CreateTranslationMat( &transMat, posX, posY );
		if( centerize ){
			Matrix4x4 < MapilFloat32 > offsetMat;	// Centering of the texture.
			CreateTranslationMat(	&offsetMat,
									- p->m_LocalTextureList[ index ].m_Resource->GetSize().m_X * 1.0f / 2,
									- p->m_LocalTextureList[ index ].m_Resource->GetSize().m_Y * 1.0f / 2 );
			mat = offsetMat * scaleMat * rotMat * transMat;	// Centering -> Scaling -> Rotation -> Translation.
		}
		else{
			mat = scaleMat * rotMat * transMat;	// Scaling -> Rotation -> Translation.
		}
		p->m_Sprite->DrawTexture( p->m_LocalTextureList[ index ].m_Resource, mat, color );
	}

	// Draw polygon 3D. (without resource holding.)
	MapilVoid DrawPolygon3D( const Polygon3DVertexFormat* pFmt, MapilInt32 polygonTotal )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_Canvas3D.GetPointer() != NULL, CURRENT_POSITION,
				TSTR( "Global canvas3D is not created yet." ), -1 );
		p->m_Canvas3D->DrawPolygon( pFmt, polygonTotal );
	}

	// Draw polygon 3D. (without resource holding.)
	MapilVoid DrawPolygon3D( const Polygon3DVertexFormat* pFmt, MapilInt32 polygonTotal, MapilUInt32 textureID )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_Canvas3D.GetPointer() != NULL, CURRENT_POSITION,
				TSTR( "Global canvas3D is not created yet." ), -1 );
		Assert(	p->m_LocalTextureList.size() > textureID, CURRENT_POSITION,
				TSTR( "Invalid index is inputted." ), -2 );
		p->m_Canvas3D->DrawPolygon( pFmt, polygonTotal, p->m_LocalTextureList[ textureID ].m_Resource );
	}

	// Set diffuse color for directional light.
	MapilVoid SetDirLightDifColor( MapilUInt32 index, MapilUInt32 color )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalDirectionalLightList.size() > index, CURRENT_POSITION,
				TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalDirectionalLightList[ index ].m_Resource->SetDiffuseColor( MAPIL::ColorARGB < MapilUChar > (	( color >> 24 ) & 0xFF,
																												( color >> 16 ) & 0xFF,
																												( color >> 8 ) & 0xFF,
																												color & 0xFF ) );
	}

	// Set ambient color for directional light.
	MapilVoid SetDirLightAmbColor( MapilUInt32 index, MapilUInt32 color )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalDirectionalLightList.size() > index, CURRENT_POSITION,
				TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalDirectionalLightList[ index ].m_Resource->SetAmbientColor( MAPIL::ColorARGB < MapilUChar > (	( color >> 24 ) & 0xFF,
																												( color >> 16 ) & 0xFF,
																												( color >> 8 ) & 0xFF,
																												color & 0xFF ) );
	}

	// Set specular color for directional light.
	MapilVoid SetDirLightSpcColor( MapilUInt32 index, MapilUInt32 color )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalDirectionalLightList.size() > index, CURRENT_POSITION,
				TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalDirectionalLightList[ index ].m_Resource->SetSpecularColor( MAPIL::ColorARGB < MapilUChar > (	( color >> 24 ) & 0xFF,
																												( color >> 16 ) & 0xFF,
																												( color >> 8 ) & 0xFF,
																												color & 0xFF ) );
	}

	// Set attenuation for directional light.
	MapilVoid SetDirLightAttenuation( MapilUInt32 index, MapilFloat32 atten0, MapilFloat32 atten1, MapilFloat32 atten2 )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalDirectionalLightList.size() > index, CURRENT_POSITION,
				TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalDirectionalLightList[ index ].m_Resource->SetAttenuation( atten0, atten1, atten2 );
	}

	// Set direction for directional light.
	MapilVoid SetDirLightDirection( MapilUInt32 index, MapilFloat32 x, MapilFloat32 y, MapilFloat32 z )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalDirectionalLightList.size() > index, CURRENT_POSITION,
				TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalDirectionalLightList[ index ].m_Resource->SetDirection( MAPIL::Vector3 < MapilFloat32 > ( x, y, z ) );
	}

	// Enable directional light.
	MapilVoid EnableDirLight( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalDirectionalLightList.size() > index, CURRENT_POSITION,
				TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalDirectionalLightList[ index ].m_Resource->Enable();
	}


	// Set master volume.
	MapilVoid SetMasterVolume( MapilUInt32 volume )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_pSoundFactory != NULL, CURRENT_POSITION, TSTR( "Sound factory is not created yet." ), -1 );
		p->m_SoundDev->SetVolume( volume );
	}

	// Set static buffer volume.
	MapilVoid SetStaticBufferVolume( MapilUInt32 index, MapilUInt32 volume )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStaticBufferList.size() > index, CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalStaticBufferList[ index ].m_Resource->SetVolume( volume );
	}

	// Set streaming buffer volume.
	MapilVoid SetStreamingBufferVolume( MapilUInt32 index, MapilUInt32 volume )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStreamingBufferList.size() > index, CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalStreamingBufferList[ index ].m_Resource->SetVolume( volume );
	}

	// Play static buffer.
	MapilVoid PlayStaticBuffer( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStaticBufferList.size() > index, CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalStaticBufferList[ index ].m_Resource->Play();
	}

	// Play streaming buffer.
	MapilVoid PlayStreamingBuffer( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		if( p->m_LocalStreamingBufferList.size() <= index ){
			return;
		}
		//Assert(	p->m_LocalStreamingBufferList.size() > index,
		//		CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalStreamingBufferList[ index ].m_Resource->Play();
	}

	// Stop static buffer.
	MapilVoid StopStaticBuffer( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStaticBufferList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalStaticBufferList[ index ].m_Resource->Stop();
	}

	// Stop streaming buffer.
	MapilVoid StopStreamingBuffer( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStreamingBufferList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalStreamingBufferList[ index ].m_Resource->Stop();
	}

	// Pause static buffer.
	MapilVoid PauseStaticBuffer( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStaticBufferList.size() > index, CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalStaticBufferList[ index ].m_Resource->Pause();
	}

	// Pause streaming buffer.
	MapilVoid PauseStreamingBuffer( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStreamingBufferList.size() > index, CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalStreamingBufferList[ index ].m_Resource->Pause();
	}

	// Is static buffer pausing?
	MapilBool IsStaticBufferPausing( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStaticBufferList.size() > index, CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		return p->m_LocalStaticBufferList[ index ].m_Resource->IsPausing();
	}

	// Is static buffer stopping?
	MapilBool IsStaticBufferStopping( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStaticBufferList.size() > index, CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		return p->m_LocalStaticBufferList[ index ].m_Resource->IsStopping();
	}

	// Is streaming buffer pausing?
	MapilBool IsStreamingBufferPausing( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStreamingBufferList.size() > index, CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		return p->m_LocalStreamingBufferList[ index ].m_Resource->IsPausing();
	}

	// Is streaming buffer stopping?
	MapilBool IsStreamingBufferStopping( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStreamingBufferList.size() > index, CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		return p->m_LocalStreamingBufferList[ index ].m_Resource->IsStopping();
	}

	// Reflesh resources.
	MapilVoid RefleshResources()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		if( p->m_pSoundFactory ){
			p->m_pSoundFactory->Reflesh( 2 );
		}
		if( p->m_pInputFactory ){
			p->m_pInputFactory->Reflesh( 2 );
		}
		if( p->m_pGraphicsFactory ){
			p->m_pGraphicsFactory->Reflesh( 2 );
		}
		if( p->m_pGUIFactory ){
			p->m_pGUIFactory->Reflesh( 2 );
		}
	}

	// Enable camera.
	MapilVoid EnableCamera( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalCameraList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalCameraList[ index ].m_Resource->Enable();
	}

	// Set projection translation. ( Camera )
	MapilVoid SetCameraProjTrans( MapilUInt32 index, MapilFloat32 fovy, MapilFloat32 aspect, MapilFloat32 nearClip, MapilFloat32 farClip )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalCameraList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalCameraList[ index ].m_Resource->SetProjectionTransMat( fovy, aspect, nearClip, farClip );
	}


	// Set view translation. ( Camera )
	MapilVoid SetCameraViewTrans(	MapilUInt32 index,
									MapilFloat32 eyeX, MapilFloat32 eyeY, MapilFloat32 eyeZ,
									MapilFloat32 lookX, MapilFloat32 lookY, MapilFloat32 lookZ,
									MapilFloat32 upX, MapilFloat32 upY, MapilFloat32 upZ )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalCameraList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalCameraList[ index ].m_Resource->SetViewTransMat(	eyeX, eyeY, eyeZ,
																	lookX, lookY, lookZ,
																	upX, upY, upZ);
	}

	// Enable camera.
	MapilVoid EnableCamera()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGUIFactory != NULL, CURRENT_POSITION, TSTR( "GUI factory is not created yet." ), -1 );
		p->m_Camera->Enable();
	}

	// Set projection translation. ( Camera )
	MapilVoid SetCameraProjTrans( MapilFloat32 fovy, MapilFloat32 aspect, MapilFloat32 nearClip, MapilFloat32 farClip )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGUIFactory != NULL, CURRENT_POSITION, TSTR( "GUI factory is not created yet." ), -1 );
		p->m_Camera->SetProjectionTransMat( fovy, aspect, nearClip, farClip );
	}

	// Set view translation. ( Camera )
	MapilVoid SetCameraViewTrans(	MapilFloat32 eyeX, MapilFloat32 eyeY, MapilFloat32 eyeZ,
									MapilFloat32 lookX, MapilFloat32 lookY, MapilFloat32 lookZ,
									MapilFloat32 upX, MapilFloat32 upY, MapilFloat32 upZ )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGUIFactory != NULL, CURRENT_POSITION, TSTR( "GUI factory is not created yet." ), -1 );
		p->m_Camera->SetViewTransMat(	eyeX, eyeY, eyeZ,
										lookX, lookY, lookZ,
										upX, upY, upZ );
	}

	// Process message.
	MapilInt32 ProcessMessage()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGUIFactory != NULL, CURRENT_POSITION, TSTR( "GUI factory is not created yet." ), -1 );
		return p->m_MainWnd->ProcessMessage();
	}

	// Draw point sprite.
	MapilVoid DrawPointSprite( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalPointSpriteList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalPointSpriteList[ index ].m_Resource->Draw();
	}

	// Capture screen shot.
	MapilVoid CaptureScreen( const MapilChar* pFileName )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		MapilTChar tstr[ 1024 ];
		ConvertToTChar( pFileName, -1, tstr, 1024 );
		p->m_GraphicsCtrl->CaptureScreen( tstr );
	}

	// Update point sprite.
	MapilVoid UpdatePointSprite( MapilUInt32 id, MapilUInt32 index, const Vector3 < MapilFloat32 >& vPos, MapilFloat32 size, MapilInt32 color )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalPointSpriteList.size() > id,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalPointSpriteList[ id ].m_Resource->Update( index, vPos, size, color );
	}

	// Create model.
	MapilUInt32 CreateModel( const MapilChar* pFileName )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		MapilTChar tstr[ 1024 ];
		ConvertToTChar( pFileName, -1, tstr, 1024 );
		std::basic_string < MapilTChar > str = tstr;
		MapilUInt32 index = GetEmptyIndex( &p->m_LocalModelList );
		ModelTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pGraphicsFactory->CreateModel( str.c_str() );
		tag.m_Resource->Create( str.c_str() );
		if( index == p->m_LocalModelList.size() ){
			p->m_LocalModelList.push_back( tag );
		}
		else{
			p->m_LocalModelList[ index ] = tag;
		}

		return index;
	}

	// Create model (From archiver).
	MapilUInt32 CreateModel( MapilUInt32 archiveHandle, const MapilChar* pXFilePath, const MapilChar* pTexFilePath )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		Assert( p->m_ArchiverList.size() > archiveHandle, CURRENT_POSITION, TSTR( "Invalid archive index is input." ), -1 );
		MapilTChar tstr[ 1024 ];
		ConvertToTChar( pXFilePath, -1, tstr, 1024 );
		std::basic_string < MapilTChar > str = tstr;
		ConvertToTChar( pTexFilePath, -1, tstr, 1024 );
		MapilInt32 index = GetEmptyIndex( &p->m_LocalModelList );
		ModelTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pGraphicsFactory->CreateModel( str.c_str() );
		tag.m_Resource->Create( p->m_ArchiverList[ archiveHandle ], str.c_str(), tstr );
		if( index == p->m_LocalModelList.size() ){
			p->m_LocalModelList.push_back( tag );
		}
		else{
			p->m_LocalModelList[ index ] = tag;
		}

		return index;
	}

	// Draw model.
	MapilVoid DrawModel( MapilUInt32 id, const Matrix4x4 < MapilFloat32 >& mat )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalModelList.size() > id, CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalModelList[ id ].m_Resource->Draw( mat );
	}

	// Draw texture with batch drawing. ( with global sprite )
	MapilVoid PostTextureBatchWork(	MapilUInt32 id,
									MapilFloat32 posX, MapilFloat32 posY,
									MapilFloat32 scaleX, MapilFloat32 scaleY,
									MapilFloat32 angle, MapilUInt32 color )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalTextureList.size() > id, CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		TextureBatchWork work;
		work.m_ID = id;
		// Create transformation matrix.
		Matrix4x4 < MapilFloat32 > offsetMat;	// Centering of the texture.
		Matrix4x4 < MapilFloat32 > rotMat;
		Matrix4x4 < MapilFloat32 > scaleMat;
		Matrix4x4 < MapilFloat32 > transMat;
		CreateTranslationMat(	&offsetMat,
								- p->m_LocalTextureList[ id ].m_Resource->GetSize().m_X * 1.0f / 2,
								- p->m_LocalTextureList[ id ].m_Resource->GetSize().m_Y * 1.0f / 2 );
		CreateRotationZMat( &rotMat, angle );
		CreateScalingMat( &scaleMat, scaleX, scaleY );
		CreateTranslationMat( &transMat, posX, posY );
		work.m_TransMat = offsetMat * scaleMat * rotMat * transMat;	// Centering -> Scaling -> Rotation -> Translation.
		work.m_Color = color;
		p->m_TextureBatch.push_back( work );
	}

	// Perform all batch works. (with global sprite)
	MapilVoid DoAllBatchWorks()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		BeginRendering();
		for( TextureBatch::iterator it = p->m_TextureBatch.begin(); it != p->m_TextureBatch.end(); ++it ){
			p->m_Sprite->DrawTexture( p->m_LocalTextureList[ it->m_ID ].m_Resource, it->m_TransMat, it->m_Color );
		}
		for( StringBatch::iterator it = p->m_StringBatch.begin(); it != p->m_StringBatch.end(); ++it ){
			p->m_Sprite->DrawString( p->m_GraphicsFont, it->m_Str.c_str(), it->m_TransMat );
		}
		EndRendering();
	}

	// Draw string with batch drawing. ( with global sprite )
	MapilVoid PostStringBatchWork(	MapilFloat32 posX, MapilFloat32 posY,
									MapilFloat32 scaleX, MapilFloat32 scaleY,
									MapilFloat32 angle, MapilUInt32 color,
									const MapilChar* pStr, ... )
	{
		ResourceHolder* p = ResourceHolder::GetInst();

		// Set up strings.
		const int MAXIMUM_STRING_LENGTH = 1024;
		// Analyze the variable length argument.
		::va_list list;
		va_start( list, pStr );
		MapilChar str[ MAXIMUM_STRING_LENGTH ];
		MapilInt32 strLen = _vscprintf( pStr, list ) + 1;
		if( strLen > 1024 ){
			va_end( list );
			return;
		}
		vsprintf( str, pStr, list );
		va_end( list );
		// Convert char to tchar.
		MapilTChar tstr[ MAXIMUM_STRING_LENGTH ];
		ConvertToTChar( str, -1, tstr, MAXIMUM_STRING_LENGTH );

		StringBatchWork work;
		work.m_Str = tstr;
		// Create transformation matrix.
		Matrix4x4 < MapilFloat32 > rotMat;
		Matrix4x4 < MapilFloat32 > scaleMat;
		Matrix4x4 < MapilFloat32 > transMat;
		CreateRotationZMat( &rotMat, angle );
		CreateScalingMat( &scaleMat, scaleX, scaleY );
		CreateTranslationMat( &transMat, posX, posY );
		work.m_TransMat = scaleMat * rotMat * transMat;	// Scaling -> Rotation -> Translation.
		work.m_Color = color;
		p->m_StringBatch.push_back( work );
	}

	// Create local rectangle 3D.
	MapilUInt32 CreateRectangle3D()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		std::basic_string < MapilTChar > str = TSTR( "Local Rectangle3D " );
		MapilUInt32 index = GetEmptyIndex( &p->m_LocalRectangle3DList );
		str += index;
		Rectangle3DTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pGraphicsFactory->CreateRectangle3D( str.c_str() );
		if( index == p->m_LocalModelList.size() ){
			p->m_LocalRectangle3DList.push_back( tag );
		}
		else{
			p->m_LocalRectangle3DList[ index ] = tag;
		}

		return index;
	}

	// Create local rectangle 3D.
	MapilUInt32 CreateRectangle3D(	const Rectangle3DVertexFormat& fmt,
									MapilUInt32 texID,
									const MapilTChar* pShaderFileName, const MapilChar* pTechName )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		std::basic_string < MapilTChar > str = TSTR( "Local Rectangle3D " );
		MapilUInt32 index = GetEmptyIndex( &p->m_LocalRectangle3DList );
		str += index;
		Rectangle3DTag tag;
		tag.m_IsUsed = MapilTrue;
		tag.m_Resource = p->m_pGraphicsFactory->CreateRectangle3D( str.c_str() );
		tag.m_Resource->Create( fmt, SharedPointer < Texture > (), pShaderFileName, pTechName );
		if( index == p->m_LocalModelList.size() ){
			p->m_LocalRectangle3DList.push_back( tag );
		}
		else{
			p->m_LocalRectangle3DList[ index ] = tag;
		}

		return index;
	}

	// Update rectangle 3D.
	MapilVoid UpdateRectangle3D( MapilUInt32 id, const Rectangle3DVertexFormat& fmt, MapilInt32 texID )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalRectangle3DList.size() > id,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalRectangle3DList[ id ].m_Resource->Update( fmt, p->m_LocalTextureList[ texID ].m_Resource );
	}

	// Draw rectangle 3D.
	MapilVoid DrawRectangle3D( MapilUInt32 id )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalRectangle3DList.size() > id,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalRectangle3DList[ id ].m_Resource->Draw();
	}

	// Open archive file.
	MapilUInt32 OpenArchiveFile( const MapilChar* pFileName, MapilInt32 mode )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Archiver* pAr = new Archiver;
		pAr->Open( pFileName, mode );
		MapilUInt32 index = p->m_ArchiverList.size();
		p->m_ArchiverList.push_back( pAr );
		return index;
	}

	// Get contents size on archive file.
	MapilUInt32 GetContentsSizeOnArchiveFile( MapilUInt32 archiveHandle, const MapilChar* pFilePath )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_ArchiverList.size() > archiveHandle, CURRENT_POSITION, TSTR( "Invalid index is input." ), -1 );
		return p->m_ArchiverList[ archiveHandle ]->GetContentsSize( pFilePath );
	}

	// Load data from archive file.
	MapilVoid LoadDataFromArchiveFile( MapilUInt32 archiveHandle, const MapilChar* pFilePath, MapilChar* pData )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_ArchiverList.size() > archiveHandle, CURRENT_POSITION, TSTR( "Invalid index is input." ), -1 );
		p->m_ArchiverList[ archiveHandle ]->Load( pFilePath, pData );
	}
	
	// Change window mode.
	MapilVoid ChangeWindowMode( MapilInt32 mode )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGUIFactory != NULL, CURRENT_POSITION, TSTR( "GUI factory is not created yet." ), -1 );
		p->m_MainWnd->SetWndMode( mode );
	}

	// Is keyboard key pushed?
	MapilBool IsKeyboardKeyPushed( MapilUInt32 key )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pInputFactory != NULL, CURRENT_POSITION, TSTR( "Input factory is not created yet." ), -1 );
		return p->m_Keyboard->IsPushed( key );
	}

	// Get keyboard key code.
	MapilInt32 GetKeyboardKeyCode( MapilInt32 key )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		return GetKeyboardKeyNum( p->m_InputAPI, key );
	}

	// Update keyboard.
	MapilVoid UpdateKeyboard()
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pInputFactory != NULL, CURRENT_POSITION, TSTR( "Input factory is not created yet." ), -1 );
		p->m_Keyboard->Update();
	}
}

#endif	// USE_C_INTERFACE
