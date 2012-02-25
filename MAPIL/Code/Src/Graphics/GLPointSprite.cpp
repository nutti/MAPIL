/**
*	@file	GLPointSprite.cpp
*	@brief	Implementation of GLPointSprite.h
*	@date	2011.8.7 (Sun) 21:12
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

// This description must be above #include <gl/GL.h>
#if defined ( LIB_GLEW )
#if defined ( OS_WIN_32BIT )
#include <gl/glew.h>
#endif
#endif

#include "../../Include/MAPIL/Graphics/GLPointSprite.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Diag/Assertion.hpp"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GLPointSprite::GLPointSprite( SharedPointer < GraphicsDevice >  pDev ) :	PointSprite( pDev ),
																				m_Size( 0.0f ),
																				m_pColor( NULL ),
																				m_pPos( NULL ),
																				m_NumVertex( 0 ),
																				m_IsUsed( MapilFalse ),
																				m_pTex()
	{
	}

	GLPointSprite::~GLPointSprite()
	{
		m_Size = 0.0f;
		SafeDelete( m_pColor );
		SafeDelete( m_pPos );
		m_NumVertex = 0;
		m_IsUsed = MapilFalse;
	}

	MapilVoid GLPointSprite::Create(	MapilInt32 numVertex, SharedPointer < Texture > pTex,
										VertexManagementMethod manageMethod )
	{
		m_Size = 1.0f;
		m_pColor = new GLfloat[ numVertex * 4 ];
		m_pPos = new GLfloat[ numVertex * 3 ];
		m_NumVertex = numVertex;
		m_IsUsed = MapilTrue;
		m_pTex = pTex;
	}

	
	MapilVoid GLPointSprite::Create(	MapilInt32 numVertex,
										VertexManagementMethod manageMethod )
	{
		m_Size = 1.0f;
		m_pColor = new GLfloat[ numVertex * 4 ];
		m_pPos = new GLfloat[ numVertex * 3 ];
		m_NumVertex = numVertex;
		m_IsUsed = MapilTrue;
	}

	MapilVoid GLPointSprite::Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
										MapilFloat32 size, const ColorARGB < MapilFloat32 >& color )
	{
		Assert(	index < m_NumVertex && index >= 0,
				TSTR( "Mapil" ),
				TSTR( "GLPointSprite" ),
				TSTR( "Update" ),
				TSTR( "Index is over range." ),
				-1 );
		m_Size = size;
		m_pColor[ index * 4 ] = color.m_R;
		m_pColor[ index * 4 + 1 ] = color.m_G;
		m_pColor[ index * 4 + 2 ] = color.m_B;
		m_pColor[ index * 4 + 3 ] = color.m_A;
		m_pPos[ index * 3 ] = vPos.m_X;
		m_pPos[ index * 3 + 1 ] = vPos.m_Y;
		m_pPos[ index * 3 + 2 ] = vPos.m_Z;
	}

	MapilVoid GLPointSprite::Update(	MapilInt32 index, const Vector3 < MapilFloat32 >& vPos,
										MapilFloat32 size, const ColorARGB < MapilUChar >& color )
	{
		Assert(	index < m_NumVertex && index >= 0,
				TSTR( "Mapil" ),
				TSTR( "GLPointSprite" ),
				TSTR( "Update" ),
				TSTR( "Index is over range." ),
				-1 );
		m_Size = size;
		m_pColor[ index * 4 ] = color.m_R / 255.0f;
		m_pColor[ index * 4 + 1 ] = color.m_G / 255.0f;
		m_pColor[ index * 4 + 2 ] = color.m_B / 255.0f;
		m_pColor[ index * 4 + 3 ] = color.m_A / 255.0f;
		m_pPos[ index * 3 ] = vPos.m_X;
		m_pPos[ index * 3 + 1 ] = vPos.m_Y;
		m_pPos[ index * 3 + 2 ] = vPos.m_Z;
	}

	MapilVoid GLPointSprite::Draw()
	{
		if( m_pTex.GetPointer() ){
			glBindTexture( GL_TEXTURE_2D, m_pTex->Get() );
		}
		
		glEnable( GL_POINT_SPRITE );
		glEnable( GL_TEXTURE_2D );
		glTexEnvi( GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		// Set point size.
		// Point size must be set before glBegin( GL_POINTS )
		if( m_pTex.GetPointer() ){
			if( m_pTex->GetSize().m_X > m_pTex->GetSize().m_Y ){
				glPointSize( m_pTex->GetSize().m_X * m_Size );
			}
			else{
				glPointSize( m_pTex->GetSize().m_Y * m_Size );
			}
		}
		else{
			glPointSize( m_Size );
		}

		glBegin( GL_POINTS );
		for( MapilInt32 i = 0; i < m_NumVertex; ++i ){
			glColor4f( m_pColor[ i * 4 ], m_pColor[ i * 4 + 1 ], m_pColor[ i * 4 + 2 ], m_pColor[ i * 4 + 3 ] );
			// 頂点座標は、-1.0f～1.0fの間で指定すること。
			glVertex3f( m_pPos[ i * 3 ], m_pPos[ i * 3 + 1 ], m_pPos[ i * 3 + 2 ] );
		}
		glEnd();

		glDisable( GL_TEXTURE_2D );
		glTexEnvi( GL_POINT_SPRITE, GL_COORD_REPLACE, GL_FALSE );
		glDisable( GL_POINT_SPRITE );
		
		
	}
}

#endif	// API_OPENGL