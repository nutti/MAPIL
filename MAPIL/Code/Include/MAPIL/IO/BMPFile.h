/**
*	@file	BMPFile.h
*	@brief	BMPFile class can handle bitmap (.bmp) file easily.
*	@date	2011.7.17 (Sun) 11:35
*/

#ifndef INCLUDED_MAPIL_BMPFILE_H
#define INCLUDED_MAPIL_BMPFILE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include <fstream>

#include "ImageFile.h"
#include "../Util/Color.hpp"
#include "../Type.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{

	class BMPFile : public ImageFile
	{
	private:
		struct BMPFileHeader
		{
		public:
			MapilUShortInt32			m_Type;				///< If this value is 0x4D42, file is bitmap file.
			MapilULongInt32				m_Size;				///< Size of bitmap file.
			MapilUShortInt32			m_Reserved1;		///< Reserved data.
			MapilUShortInt32			m_Reserved2;		///< Reserved data.
			MapilULongInt32				m_BitPos;			///< Position of bits array.
		};

		struct BMPInfoHeader
		{
		public:
			MapilULongInt32				m_Size;					///< Size of BitMapInfoHeader structure.
			MapilLongInt32				m_Width;				///< Width of bitmap (pixel).
			MapilLongInt32				m_Height;				///< Height of bitmap (pixel).
			MapilUShortInt32			m_Planes;				///< Always 1.
			MapilUShortInt32			m_NumBitPerPixel;		///< Number of bit per pixel.
			MapilULongInt32				m_CompressionType;		///< Compression type.
			MapilULongInt32				m_ImageSize;			///< Number of byte of picture.
			MapilLongInt32				m_MeterPerPixelX;		///< Meter of direction of X per pixel.
			MapilLongInt32				m_MeterPerPixelY;		///< Meter of direction of Y per pixel.
			MapilULongInt32				m_NumColorUsed;			///< Number of color which is used.
			MapilULongInt32				m_NumColorImportant;	///< Number of color which is important.
		};

		std::basic_fstream < MapilChar >			m_Stream;			///< File stream.
		BMPFileHeader								m_FileHeader;		///< BitmapFileHeader structure.
		BMPInfoHeader								m_InfoHeader;		///< BitmapInfoHeader structure.
		ColorRGB < MapilUChar >*					m_pColorBuf;		///< Color data.
		FileOpenMode								m_OpenMode;			///< File open mode.
		/**
		*	@brief	Load bitmap file whose bit/pixel is 1.
		*/
		MapilVoid Load1BitBMP();
		/**
		*	@brief	Load bitmap file whose bit/pixel is 4.
		*/
		MapilVoid Load4BitBMP();
		/**
		*	@brief	Load bitmap file whose bit/pixel is 8.
		*/
		MapilVoid Load8BitBMP();
		/**
		*	@brief	Load bitmap file whose bit/pixel is 24.
		*/
		MapilVoid Load24BitBMP();
		/**
		*	@brief	Save bitmap file whose bit/pixel is 24.
		*/
		MapilVoid Save24BitBMP();
		/**
		*	@brief	Load bitmap file whose bit/pixel is 32.
		*/
		MapilVoid Load32BitBMP();

	public:
		/**
		*	@brief	Constructor.
		*/
		BMPFile();
		/**
		*	@brief	Destructor.
		*/
		virtual ~BMPFile();
		/**
		*	@brief	Copy constructor.
		*	@param	bf BMPFile class which will be copyed.
		*/
		BMPFile( const BMPFile& bf );
		/**
		*	@brief	Substitute. ( Overload of = operator. )
		*	@param	bf BMPFile class which will be substituted.
		*/
		BMPFile& operator=( const BMPFile& bf );
		/**
		*	@brief	Index operator. ( Overload of [] operator. )
		*	@param	index Index which will be accessed to raw data.
		*/
		ColorRGB < MapilUChar >& operator[]( MapilInt32 index );
		/**
		*	@brief	Brackets operator. ( Overload of () operator. )
		*	@param	x X-Coordinate of the image.
		*	@param	y Y-Coordinate of the image.
		*/
		ColorRGB < MapilUChar >& operator()( MapilInt32 x, MapilInt32 y );
		/**
		*	@brief	Open file.
		*	@param	pFileName Name of bitmap file.
		*	@param	mode The file open mode.
		*/
		MapilVoid Open( const MapilChar* pFileName, FileOpenMode mode );
		/**
		*	@brief	Close file.
		*/
		MapilVoid Close();
		/**
		*	@brief	Load.
		*	@param	pFileName Name of bitmap file.
		*/
		MapilVoid Load( const MapilChar* pFileName );
		/**
		*	@brief	Save.
		*	@param	pFileName Name of bitmap file.
		*	@param	numBitPerPixel The number of bit per pixel.
		*/
		MapilVoid Save( const MapilChar* pFileName, MapilInt32 numBitPerPixel = 24 );
		/**
		*	@brief	Get width.
		*	@return	The image width.
		*/
		MapilInt32 GetWidth() const;
		/**
		*	@brief	Get height.
		*	@return	The image height.
		*/
		MapilInt32 GetHeight() const;
		/**
		*	@brief	Get file size.
		*	@return	Size of the image.
		*/
		MapilInt32 GetFileSize() const;
		/**
		*	@brief	Get number of bit per pixel.
		*	@return	The number of bit per pixel.
		*/
		MapilInt32 GetNumBitPerPixel() const;
		/**
		*	@brief	Get pixel color.
		*	@param	x X-Coordinate of the image.
		*	@param	y Y-Coordinate of the image.
		*	@return	Pixel color.
		*/
		ColorRGB < MapilUChar > GetPixelColor( MapilInt32 x, MapilInt32 y ) const;
		/**
		*	@brief	Set width.
		*	@param	width The image width.
		*/
		MapilVoid SetWidth( MapilInt32 width );
		/**
		*	@brief	Set height.
		*	@param	height The image height.
		*/
		MapilVoid SetHeight( MapilInt32 height );
		/**
		*	@brief	Set pixel color.
		*	@param	x X-Coordinate of the image.
		*	@param	y Y-Coordinate of the image.
		*	@param	color Pixel color.
		*/
		MapilVoid SetPixelColor( MapilInt32 x, MapilInt32 y, const ColorRGB < MapilUChar > color );
	};
}

#endif	// INCLUDED_MAPIL_BMPFILE_H
