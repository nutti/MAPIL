/**
*	@file	GLModel.cpp
*	@brief	Implementation of GLModel.h.
*	@date	2011.7.16 (Sat) 10:37
*/

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../../Include/MAPIL/CrossPlatform.h"

#if defined ( API_OPENGL )

#if defined ( API_WIN32API )
#include <Windows.h>
#endif

#if defined ( OS_WIN_32BIT )
#include <gl/GL.h>
#include <gl/GLU.h>
#elif defined ( OS_LINUX_32BIT )
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "../../Include/MAPIL/IO/Archiver.h"
#include "../../Include/MAPIL/Graphics/GLModel.h"
#include "../../Include/MAPIL/IO/MQOFile.h"
#include "../../Include/MAPIL/IO/XFile.h"
#include "../../Include/MAPIL/Util/Memory.hpp"
#include "../../Include/MAPIL/Util/String.h"
#include "../../Include/MAPIL/IO/FileFormatAnalyzer.h"
#include "../../Include/MAPIL/Diag/MapilException.h"
#include "../../Include/MAPIL/TChar.h"
#include "../../Include/MAPIL/Graphics/GraphicsDevice.h"
#include "../../Include/MAPIL/Graphics/GLTexture.h"

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GLModel::GLModel( SharedPointer < GraphicsDevice > pDev ) :	Model( pDev ),
																m_pModelData( NULL ),
																m_ppTextures( NULL )
	{
	}

	GLModel::~GLModel()
	{
		if( m_pModelData ){
			for( MapilInt32 i = 0; i < m_pModelData->m_Model[ 0 ].m_Material.size(); ++i ){
				SafeDelete( m_ppTextures[ i ] );
			}
			SafeDeleteArray( m_ppTextures );
		}
		SafeDelete( m_pModelData );
	}

	MapilVoid GLModel::Create( const MapilTChar* pFileName )
	{
		MapilChar name[ 1024 ];
		ConvertToMultiByte( pFileName, -1, name, 1024 );

		m_pModelData = new ModelData();

		// Analyze file format.
		FileFormatAnalyzer ffa;
		ffa.Open( name );
		ffa.Analyze();
		ModelFile* pModelFile = NULL;
		if( ffa.GetFileFmt() == FILE_FORMAT_X ){
			pModelFile = new XFile();
		}
		else if( ffa.GetFileFmt() == FILE_FORMAT_MQO ){
			pModelFile = new MQOFile();
		}
		else{
			throw MapilException( CURRENT_POSITION, TSTR( "Invalid file format." ), -1 );
		}

		// Load model file.
		pModelFile->Load( name );
		pModelFile->CopyToModelData( m_pModelData );
		/*
		// Create buffer object.
		::glGenBuffers( 4, m_Buffers );

		// Attach vertex data.
		::glBindBuffer( GL_ARRAY_BUFFER, m_Buffers[ 0 ] );
		::glBufferData(	GL_ARRAY_BUFFER,
						sizeof( MapilFloat32 ) * m_pModelData->m_Model[ 0 ].m_Vertices.size(),
						&m_pModelData->m_Model[ 0 ].m_Vertices[ 0 ],
						GL_STATIC_DRAW );

		// Attach normal data.
		::glBindBuffer( GL_ARRAY_BUFFER, m_Buffers[ 1 ] );
		::glBufferData(	GL_ARRAY_BUFFER,
						sizeof( MapilFloat32 ) * m_pModelData->m_Model[ 0 ].m_Normals.size(),
						&m_pModelData->m_Model[ 0 ].m_Normals[ 0 ],
						GL_STATIC_DRAW );

		// Attach texture data.
		::glBindBuffer( GL_ARRAY_BUFFER, m_Buffers[ 2 ] );
		::glBufferData(	GL_ARRAY_BUFFER,
						sizeof( MapilFloat32 ) * m_pModelData->m_Model[ 0 ].m_TexCoords.size(),
						&m_pModelData->m_Model[ 0 ].m_TexCoords[ 0 ],
						GL_STATIC_DRAW );

		// Attach index data.
		std::vector < MapilInt32 > indices;
		for( MapilInt32 i = 0; i < m_pModelData->m_Model[ 0 ].m_Face.size(); i++ ){
			for( MapilInt32 j = 0; j < m_pModelData->m_Model[ 0 ].m_Face[ i ].m_NumElm; ++j ){
				indices.push_back( m_pModelData->m_Model[ 0 ].m_Face[ i ].m_VertexIndices[ j ] );
			}
		}
		::glBindBuffer( GL_ARRAY_BUFFER, m_Buffers[ 3 ] );
		::glBufferData(	GL_ARRAY_BUFFER,
						sizeof( MapilInt32 ) * indices.size(),
						&indices[ 0 ],
						GL_STATIC_DRAW );*/

		


		// Create textures.
		m_ppTextures = new GLTexture* [ m_pModelData->m_Model[ 0 ].m_Material.size() ];
		for( MapilInt32 i = 0; i < m_pModelData->m_Model[ 0 ].m_Material.size(); ++i ){
			m_ppTextures[ i ] = NULL;
			if( strcmp( m_pModelData->m_Model[ 0 ].m_Material[ i ].m_TexFileName, "" ) ){
				TCHAR str[ 1024 ];
				ConvertToTChar(	m_pModelData->m_Model[ 0 ].m_Material[ i ].m_TexFileName,
								-1,
								str, 1024 );
				m_ppTextures[ i ] = new GLTexture( m_pDev );
				m_ppTextures[ i ]->Create( str );
			}
		}

		SafeDelete( pModelFile );
	}


	MapilVoid GLModel::Create( Archiver* pArchiver, const MapilTChar* pXFileName, const MapilTChar* pTextureFileName )
	{
	}

	MapilVoid GLModel::DrawModel()
	{
		MapilFloat32 doesMaterialExist = MapilFalse;

		for( MapilUInt32 i = 0; i < m_pModelData->m_Model.size(); i++ ){

			if( m_pModelData->m_Model[ i ].m_Material.size() > 0 ){
				doesMaterialExist = MapilTrue;
			}

			MapilFloat32 doesFaceExist = MapilFalse;
			MapilInt32 curMaterial = -1;
			MapilInt32 prevMaterial = -1;
					
			if( m_pModelData->m_Model[ i ].m_Face.size() > 0 ){
				doesFaceExist = MapilTrue;
			}

			MapilInt32 idx = 0;		// Index.

			for( MapilInt32 j = 0; j < m_pModelData->m_Model[ i ].m_Face.size(); j++ ){
				if( doesMaterialExist ){

					curMaterial = m_pModelData->m_Model[ i ].m_Face[ j ].m_MtrlNum;

					// Optimization.
					if( curMaterial != prevMaterial ){

						// Setup materials for .mqo file.
						if( m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Diffuse[ 1 ] == -1.0f ){
							glMaterialf( GL_FRONT_AND_BACK, GL_AMBIENT, m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Ambient[ 0 ] );
							glMaterialf( GL_FRONT_AND_BACK, GL_DIFFUSE, m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Diffuse[ 0 ] );
							glMaterialf( GL_FRONT_AND_BACK, GL_SPECULAR, m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Specular[ 0 ] );
							glMaterialf( GL_FRONT_AND_BACK, GL_EMISSION, m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Emissive[ 0 ] );
						}
						// Setup materials for .x file.
						else{
							GLfloat diffuse[] = {	m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Diffuse[ 1 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Diffuse[ 2 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Diffuse[ 3 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Diffuse[ 0 ] };
							GLfloat ambient[] = {	m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Ambient[ 1 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Ambient[ 2 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Ambient[ 3 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Ambient[ 0 ] };
							GLfloat specular[] = {	m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Specular[ 1 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Specular[ 2 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Specular[ 3 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Specular[ 0 ] };
							GLfloat emissive[] = {	m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Emissive[ 1 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Emissive[ 2 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Emissive[ 3 ],
													m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Emissive[ 0 ] };
							glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse );
							glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambient );
							glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular );
							glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emissive );
						}
						glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Power );
						
						// Setup texture.
						if( strcmp( m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_TexFileName, "" ) ){
							MapilInt32 handle = m_ppTextures[ curMaterial ]->Get();
							glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
							glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
							glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
							glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
							glBindTexture( GL_TEXTURE_2D, handle );
						}
						// Unset texture.
						else{
							glBindTexture( GL_TEXTURE_2D, 0 );
						}

						prevMaterial = curMaterial;
					}
				}

				MapilInt32 iter = 0;		// Iteration.
				// Triangle * 1.
				if( m_pModelData->m_Model[ i ].m_Face[ j ].m_NumElm == 3 ){
					iter = 1;
				}
				// Triangle * 2.
				else if( m_pModelData->m_Model[ i ].m_Face[ j ].m_NumElm == 4 ){
					iter = 2;
				}
				for( MapilInt32 k = 0; k < iter; ++k ){
					glBegin( GL_TRIANGLES );
					for( MapilInt32 id = 0; id < 3; ++id ){
						GLfloat v[ 3 ];
						v[ 0 ] = m_pModelData->m_Model[ i ].m_Vertices[ m_pModelData->m_Model[ i ].m_Indices[ idx ] * 3 ];
						v[ 1 ] = m_pModelData->m_Model[ i ].m_Vertices[ m_pModelData->m_Model[ i ].m_Indices[ idx ] * 3 + 1 ];
						v[ 2 ] = m_pModelData->m_Model[ i ].m_Vertices[ m_pModelData->m_Model[ i ].m_Indices[ idx ] * 3 + 2 ];
						GLfloat normal[] = {	m_pModelData->m_Model[ i ].m_Normals[ m_pModelData->m_Model[ i ].m_Indices[ idx ] * 3 ],
												m_pModelData->m_Model[ i ].m_Normals[ m_pModelData->m_Model[ i ].m_Indices[ idx ] * 3 + 1 ],
												m_pModelData->m_Model[ i ].m_Normals[ m_pModelData->m_Model[ i ].m_Indices[ idx ] * 3 + 2 ] };
						GLfloat texCoord[] = {	m_pModelData->m_Model[ i ].m_TexCoords[ m_pModelData->m_Model[ i ].m_Indices[ idx ] * 2 ],
												m_pModelData->m_Model[ i ].m_TexCoords[ m_pModelData->m_Model[ i ].m_Indices[ idx ] * 2 + 1 ] };

						// Need to call Texture -> Normal -> Vertex.
						glTexCoord2fv( texCoord );
						glNormal3fv( normal );
						glVertex3fv( v );

						
						idx += 1;
					}
					glEnd();
					
				}
			}
		}
	}

	MapilVoid GLModel::Draw()
	{
		DrawModel();
	}

	MapilVoid GLModel::Draw( const Matrix4x4 < MapilFloat32 >& mat )
	{
		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
		glMultMatrixf( mat.m_Elm1 );
		DrawModel();
		glPopMatrix();

		glFlush();
	}

	MapilBool GLModel::DetectCollision(	const Vector3 < MapilFloat32 >& vRayDir,
										const Vector3 < MapilFloat32 >& vRayOrig,
										Vector2 < MapilFloat32 >* pVCollisionPos,
										MapilFloat32* pDistance )
	{
		return MapilFalse;
	}

}

#endif	// API_OPENGL