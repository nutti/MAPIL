/**
*	@file	CInterface.h
*	@brief	
*	@date	2012.6.30 (Sat) 9:42
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Util/CInterface.h"

#include "../../Include/MAPIL/GUI/GUIFactory.h"
#include "../../Include/MAPIL/Graphics/GraphicsFactory.h"
#include "../../Include/MAPIL/Input/WinAPIInputFactory.h"
#include "../../Include/MAPIL/Sound/ALSoundFactory.h"
#include "../../Include/MAPIL/Util/Singleton.hpp"
#include "../../Include/MAPIL/Util/String.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/Diag/Assertion.hpp"

#include "../../Include/MAPIL/Graphics/D3DGraphicsFactory.h"

#include <vector>
#include <string>

namespace MAPIL
{
	template < typename T >
	struct ResourceTag
	{
		T			m_Resource;
		MapilBool	m_IsUsed;
	};

	typedef ResourceTag < ICamera >				CameraTag;
	typedef ResourceTag < IGraphicsFont >		GraphicsFontTag;
	typedef ResourceTag < IPointSprite >		PointSpriteTag;
	typedef ResourceTag < ITexture >			TextureTag;
	typedef ResourceTag < IStaticBuffer >		StaticBufferTag;
	typedef ResourceTag < IStreamingBuffer >	StreamingBufferTag;

	typedef std::vector < CameraTag >			CameraList;
	typedef std::vector < GraphicsFontTag >		GraphicsFontList;
	typedef std::vector < PointSpriteTag >		PointSpriteList;
	typedef std::vector < TextureTag >			TextureList;
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
		ISprite				m_Sprite;
		IGraphicsFont		m_GraphicsFont;
		IKeyboard			m_Keyboard;

		// Local resources.
		CameraList				m_LocalCameraList;
		GraphicsFontList		m_LocalGraphicsFontList;
		PointSpriteList			m_LocalPointSpriteList;
		TextureList				m_LocalTextureList;
		StaticBufferList		m_LocalStaticBufferList;
		StreamingBufferList		m_LocalStreamingBufferList;
	};

	ResourceHolder::ResourceHolder() :	m_GUIAPI( GUI_API_NONE ),
										m_GUIDev(),
										m_pGUIFactory( NULL ),

										m_GraphicsAPI( GRAPHICS_API_NONE ),
										m_GraphicsDev(),
										m_pGraphicsFactory( NULL ),

										m_InputAPI( INPUT_API_NONE ),
										m_InputDev(),
										m_pInputFactory( NULL ),

										m_SoundAPI( SOUND_API_NONE ),
										m_SoundDev(),
										m_pSoundFactory( NULL ),

										m_LocalCameraList(),
										m_LocalGraphicsFontList(),
										m_LocalPointSpriteList(),
										m_LocalTextureList(),
										m_LocalStaticBufferList(),
										m_LocalStreamingBufferList()
	{
	}

	ResourceHolder::~ResourceHolder()
	{
		SafeDelete( m_pSoundFactory );
		SafeDelete( m_pInputFactory );
		SafeDelete( m_pGraphicsFactory );
		SafeDelete( m_pGUIFactory );
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
		// Setup API.
#if defined ( API_WIN32API )
		SetGUIAPI( GUI_API_WIN32API );
#endif
#if defined ( API_DIRECT3D )
		SetGraphicsAPI( GRAPHICS_API_DIRECT3D );
#endif
#if defined ( API_WIN32API )
		SetInputAPI( INPUT_API_WIN32API );
#endif
#if defined ( API_OPENAL )
		SetSoundAPI( SOUND_API_OPENAL );
#endif

		ResourceHolder* p = ResourceHolder::GetInst();
		// Create GUI factory.
		if( p->m_GUIAPI != GUI_API_NONE ){
			p->m_GUIDev = CreateGUIDevice( p->m_GUIAPI );
			p->m_pGUIFactory = CreateGUIFactory( p->m_GUIDev );
		}
		// Create Graphics factory.
		if( p->m_GraphicsAPI != GRAPHICS_API_NONE ){
			p->m_GraphicsDev = CreateGraphicsDevice( p->m_GraphicsAPI );
			p->m_pGraphicsFactory = CreateGraphicsFactory( p->m_GraphicsDev );
		}
		// Create Input factory.
		if( p->m_InputAPI != INPUT_API_NONE ){
			p->m_InputDev = CreateInputDevice( p->m_InputAPI );
			p->m_pInputFactory = new WinAPIInputFactory( p->m_InputDev );
		}
		// Create Sound factory.
		if( p->m_SoundAPI != SOUND_API_NONE ){
			p->m_SoundDev = CreateSoundDevice( p->m_SoundAPI );
			p->m_pSoundFactory = new ALSoundFactory( p->m_SoundDev );
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
		// Create canvas object.
		p->m_Canvas2D = p->m_pGraphicsFactory->CreateCanvas2D( TSTR( "Global Canvas 2D" ) );
		p->m_Canvas2D->Create();
		// Create sprite object.
		p->m_Sprite = p->m_pGraphicsFactory->CreateSprite( TSTR( "Global Sprite" ) );
		p->m_Sprite->Create();
		// Create graphics font object.
		p->m_GraphicsFont = p->m_pGraphicsFactory->CreateGraphicsFont( TSTR( "Global Graphics Font" ) );
		FontFormat fmt;
		ZeroObject( &fmt, sizeof( fmt ) );
		p->m_GraphicsFont->Create( fmt );

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

		return 0;
	}

	// Set GUI API.
	MapilVoid SetGUIAPI( MapilInt32 api )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		p->m_GUIAPI = api;
	}

	// Set Graphics API.
	MapilVoid SetGraphicsAPI( MapilInt32 api )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		p->m_GraphicsAPI = api;
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
		std::basic_string < MapilTChar > str = TSTR( "Local Texture " );
		MapilInt32 index = GetEmptyIndex( &p->m_LocalTextureList );
		str += index;
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

	// Create point sprite.
	MapilInt32 CreatePointSprite( MapilInt32 num, MapilInt32 texture )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pGraphicsFactory != NULL, CURRENT_POSITION, TSTR( "Graphics factory is not created yet." ), -1 );
		std::basic_string < MapilTChar > str = TSTR( "Local Texture " );
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

	// Create static buffer.
	MapilInt32 CreateStaticBuffer( const MapilChar* pFileName )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pSoundFactory != NULL, CURRENT_POSITION, TSTR( "Sound factory is not created yet." ), -1 );
		std::basic_string < MapilTChar > str = TSTR( "Local Static Buffer " );
		MapilInt32 index = GetEmptyIndex( &p->m_LocalStaticBufferList );
		str += index;
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

	// Create streaming buffer.
	MapilInt32 CreateStreamingBuffer( const MapilChar* pFileName )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert( p->m_pSoundFactory != NULL, CURRENT_POSITION, TSTR( "Sound factory is not created yet." ), -1 );
		std::basic_string < MapilTChar > str = TSTR( "Local Streaming Buffer " );
		MapilInt32 index = GetEmptyIndex( &p->m_LocalStreamingBufferList );
		str += index;
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

		const int STRING_COLOR = 0xFFFFFFFF;
		const int MAXIMUM_STRING_LENGTH = 1024;

		// Analyze the variable length argument.
		::va_list list;
		va_start( list, pStr );
		MapilChar str[ MAXIMUM_STRING_LENGTH ];
		::vsprintf_s( str, MAXIMUM_STRING_LENGTH, pStr, list );
		va_end( list );

		// Convert char to tchar.
		MapilTChar tstr[ MAXIMUM_STRING_LENGTH ];
		ConvertToTChar( pStr, MAXIMUM_STRING_LENGTH, tstr, MAXIMUM_STRING_LENGTH );

		p->m_Sprite->DrawString(	p->m_GraphicsFont,
									tstr,
									IMAGE_TRANSFORMATION_METHOD_CENTER_MOVE,
									Vector2 < MapilFloat32 > ( x, y ),
									STRING_COLOR );
	}

	// Draw texture ( with global sprite. )
	MapilVoid DrawTexture( MapilUInt32 index, MapilFloat32 x, MapilFloat32 y, MapilFloat32 angle )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalTextureList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );

		// Create transformation matrix.
		Matrix4x4 < MapilFloat32 > mat;
		Matrix4x4 < MapilFloat32 > offsetMat;	// Centering of the texture.
		Matrix4x4 < MapilFloat32 > rotMat;
		Matrix4x4 < MapilFloat32 > transMat;
		CreateTranslationMat(	&offsetMat,
								- p->m_LocalTextureList[ index ].m_Resource->GetSize().m_X * 1.0f / 2,
								- p->m_LocalTextureList[ index ].m_Resource->GetSize().m_Y * 1.0f / 2 );
		CreateRotationZMat( &rotMat, angle );
		CreateTranslationMat( &transMat, x, y );
		mat = offsetMat * rotMat * transMat;	// Centering -> Rotation -> Translation.
		p->m_Sprite->DrawTexture( p->m_LocalTextureList[ index ].m_Resource, mat );
	}

	// Play static buffer.
	MapilVoid PlayStaticBuffer( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStaticBufferList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
		p->m_LocalStaticBufferList[ index ].m_Resource->Play();
	}

	// Play streaming buffer.
	MapilVoid PlayStreamingBuffer( MapilUInt32 index )
	{
		ResourceHolder* p = ResourceHolder::GetInst();
		Assert(	p->m_LocalStreamingBufferList.size() > index,
				CURRENT_POSITION, TSTR( "Invalid index is inputted." ), -1 );
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
	MapilVoid EnableCamera(	MapilUInt32 index,
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
}
