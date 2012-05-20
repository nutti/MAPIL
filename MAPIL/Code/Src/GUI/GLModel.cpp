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

//-------------------------------------------------------------------
// Implementation.
//-------------------------------------------------------------------

namespace MAPIL
{
	GLModel::GLModel( SharedPointer < GraphicsDevice > pDev ) : Model( pDev ), m_pModelData( NULL )
	{
	}

	GLModel::~GLModel()
	{
		SafeDelete( m_pModelData );
	}

	MapilVoid GLModel::Create( const MapilTChar* pFileName )
	{
		MapilChar name[ 1024 ];
		ConvertToMultiByte( pFileName, -1, name, 1024 );

		m_pModelData = new ModelData();

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
			throw MapilException(	TSTR( "Mapil" ),
									TSTR( "GLModel" ),
									TSTR( "Create" ),
									TSTR( "Invalid file format." ),
									-1 );
		}

		pModelFile->Load( name );
		pModelFile->CopyToModelData( m_pModelData );

		SafeDelete( pModelFile );
	}


	MapilVoid GLModel::Create( Archiver* pArchiver, const MapilTChar* pXFileName, const MapilTChar* pTextureFileName )
	{
	}

	MapilVoid GLModel::DrawModel()
	{
		MapilFloat32 doesMaterialExist = MapilFalse;

		if( m_pModelData->m_Model[ 0 ].m_Material.size() > 0 ){
			doesMaterialExist = MapilTrue;
		}

		for( MapilUInt32 i = 0; i < m_pModelData->m_Model[ 0 ].m_Object.size() ; i++ ){
			MapilFloat32 doesFaceExist = MapilFalse;
			MapilInt32 curMaterial = -1;
			MapilInt32 prevMaterial = -1;
					
			if( m_pModelData->m_Model[ 0 ].m_Object[ i ].m_NumFace > 0 ){
				doesFaceExist = MapilTrue;
			}

			for( MapilInt32 j = 0; j < m_pModelData->m_Model[ 0 ].m_Object[ i ].m_NumFace; j++ ){
				if( doesMaterialExist ){
					curMaterial = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_MtrlNum;
					if( curMaterial != prevMaterial ){
						//GLfloat color[] = {	m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Color[ 0 ],
						//					m_pModelData->m_Material[ curMaterial ].m_Color[ 1 ],
						//					m_pModelData->m_Material[ curMaterial ].m_Color[ 2 ],
						//					m_pModelData->m_Material[ curMaterial ].m_Color[ 3 ] };
						//glColor4fv( color );
						if( m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Diffuse[ 1 ] == -1.0f ){
							glMaterialf( GL_FRONT_AND_BACK, GL_AMBIENT, m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Ambient[ 0 ] );
							glMaterialf( GL_FRONT_AND_BACK, GL_DIFFUSE, m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Diffuse[ 0 ] );
							glMaterialf( GL_FRONT_AND_BACK, GL_SPECULAR, m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Specular[ 0 ] );
							glMaterialf( GL_FRONT_AND_BACK, GL_EMISSION, m_pModelData->m_Model[ 0 ].m_Material[ curMaterial ].m_Emissive[ 0 ] );
						}
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
						prevMaterial = curMaterial;
					}
				}
				if( m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_NumElm == 3 ){
					glBegin( GL_TRIANGLES );
				}
				else{
					glBegin( GL_QUADS );
				}
				for( MapilInt32 k = 0; k < m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_NumElm; ++k ){
					GLfloat v[ 3 ];
					if( m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_NumElm == 3 ){
						v[ 0 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ k ] * 3 ];
						v[ 1 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ k ] * 3 + 1 ];
						v[ 2 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ k ] * 3 + 2 ];
					}
					else{
						if( k == 0 ){
							v[ 0 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 3 ] * 3 ];
							v[ 1 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 3 ] * 3 + 1 ];
							v[ 2 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 3 ] * 3 + 2 ];
						}
						else if( k == 1 ){
							v[ 0 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 0 ] * 3 ];
							v[ 1 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 0 ] * 3 + 1 ];
							v[ 2 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 0 ] * 3 + 2 ];
						}
						else if( k == 2 ){
							v[ 0 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 1 ] * 3 ];
							v[ 1 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 1 ] * 3 + 1 ];
							v[ 2 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 1 ] * 3 + 2 ];
						}
						else if( k == 3 ){
							v[ 0 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 2 ] * 3 ];
							v[ 1 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 2 ] * 3 + 1 ];
							v[ 2 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 2 ] * 3 + 2 ];
						}
						//if( k == 0 ){
						//	v[ 0 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 2 ] * 3 ];
						//	v[ 1 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 2 ] * 3 + 1 ];
						//	v[ 2 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 2 ] * 3 + 2 ];
						//}
						//else if( k == 1 ){
						//	v[ 0 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 0 ] * 3 ];
						//	v[ 1 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 0 ] * 3 + 1 ];
						//	v[ 2 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 0 ] * 3 + 2 ];
						//}
						//else if( k == 2 ){
						//	v[ 0 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 2 ] * 3 ];
						//	v[ 1 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 2 ] * 3 + 1 ];
						//	v[ 2 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 2 ] * 3 + 2 ];
						//}
						//else if( k == 3 ){
						//	v[ 0 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 1 ] * 3 ];
						//	v[ 1 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 1 ] * 3 + 1 ];
						//	v[ 2 ] = m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Vertex[ m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Index[ 1 ] * 3 + 2 ];
						//}
					}

					glVertex3fv( v );
					// ‚±‚±‚ª‚¿‚å‚Á‚Æ‚¨‚©‚µ‚¢B
					if( m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Normal ){
						GLfloat normal[] = {	m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Normal[ k * 3 + 0 ],
												m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Normal[ k * 3 + 1 ],
												m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_Normal[ k * 3 + 2 ] };
						glNormal3fv( normal );
					}
				//	if( doesTextureExist ){
				//		GLfloat texCoord[] = {	m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_TexCoord[ k * 2 + 0 ],
				//								m_pModelData->m_Model[ 0 ].m_Object[ i ].m_Face[ j ].m_TexCoord[ k * 2 + 1 ] };
				//		glTexCoord2fv( texCoord );
				//	}
				}
				glEnd();
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