/**
*	@file	Color.hpp
*	@brief	This file provides to the users the utility for color.
*	@date	2011.6.17 (Fri) 8:07
*/

#ifndef INCLUDED_MAPIL_COLOR_HPP
#define INCLUDED_MAPIL_COLOR_HPP

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../Type.h"

//-------------------------------------------------------------------
// Definitions and implementations.
//-------------------------------------------------------------------

namespace MAPIL
{
	/**
	*	@brief		Get value of RGB color. (char to unsigned int)
	*	@param r	Red.
	*	@param g	Green.
	*	@param b	Blue.
	*	@return		Value of ARGB color.
	*/
	inline MapilUInt32 GetColorRGBValue(  MapilUChar r, MapilUChar g, MapilUChar b )
	{
		return ( 0xFF << 24 ) | ( r << 16 ) | ( g << 8 ) | b;
	}

	/**
	*	@brief		Get value of RGB color. (float to unsigned int)
	*	@param r	Red.
	*	@param g	Green.
	*	@param b	Blue.
	*	@return		Value of ARGB color.
	*/
	inline MapilUInt32 GetColorRGBValue( MapilFloat32 r, MapilFloat32 g, MapilFloat32 b )
	{
		MapilUInt32 val = 0xFF000000;

		val |= ( static_cast < MapilUChar > ( r * 255 ) ) << 16;
		val |= ( static_cast < MapilUChar > ( g * 255 ) ) << 8;
		val |= ( static_cast < MapilUChar > ( b * 255 ) );

		return val;
	}

	/**
	*	@brief		Get value of ARGB color. (char to unsigned int)
	*	@param a	Alpha.
	*	@param r	Red.
	*	@param g	Green.
	*	@param b	Blue.
	*	@return		Value of ARGB color.
	*/
	inline MapilUInt32 GetColorARGBValue( MapilUChar a, MapilUChar r, MapilUChar g, MapilUChar b )
	{
		return ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | b;
	}

	/**
	*	@brief		Get value of ARGB color. (float to unsigned int)
	*	@param a	Alpha.
	*	@param r	Red.
	*	@param g	Green.
	*	@param b	Blue.
	*	@return		Value of ARGB color.
	*/
	inline MapilUInt32 GetColorARGBValue( MapilFloat32 a, MapilFloat32 r, MapilFloat32 g, MapilFloat32 b )
	{
		MapilUInt32 val = 0;

		val |= ( static_cast < MapilUChar > ( a * 255 ) ) << 24;
		val |= ( static_cast < MapilUChar > ( r * 255 ) ) << 16;
		val |= ( static_cast < MapilUChar > ( g * 255 ) ) << 8;
		val |= ( static_cast < MapilUChar > ( b * 255 ) );

		return val;
	}

	template < typename Type >
	class ColorRGB
	{
	public:
		Type				m_R;			///< Red.
		Type				m_G;			///< Green.
		Type				m_B;			///< Blue.
		/**
		*	@brief Constructor.
		*/
		ColorRGB();
		/**
		*	@brief			Constructor.
		*	@param colorR	Red.
		*	@param colorG	Green.
		*	@param colorB	Blue.
		*/
		ColorRGB( Type colorR, Type colorG, Type colorB );
		/**
		*	@brief			Copy constructor.
		*	@param color	ColorRGB object to be copied.
		*/
		ColorRGB( const ColorRGB < Type >& color );
		/**
		*	@brief Destructor.
		*/
		~ColorRGB();
		/**
		*	@brief			Substitute (Overload of = operator)
		*	@param color	ColorRGB object to be copied.
		*	@return			Copied ColorRGB object.
		*/
		ColorRGB& operator=( const ColorRGB < Type >& color );
		/**
		*	@brief			Equivalence (Overload of == operator)
		*	@param color	ColorRGB object to be compared.
		*	@return			True if color value is equivalent.
		*/
		MapilBool operator==( const ColorRGB < Type >& color );
	};

	//Constructer (1)
	template < typename Type >
	ColorRGB < Type > ::ColorRGB() : m_R( 0 ), m_G( 0 ), m_B( 0 )
	{
	}

	//Constructer (2)
	template < typename Type >
	ColorRGB < Type > ::ColorRGB( Type colorR, Type colorG, Type colorB ) : m_R( colorR ), m_G( colorG ), m_B( colorB )
	{
	}

	//Constructer (3)
	template < typename Type >
	ColorRGB < Type > ::ColorRGB( const ColorRGB < Type >& color ) : m_R( color.m_R ), m_G( color.m_G ), m_B( color.m_B )
	{
	}

	//Destructer
	template < typename Type >
	ColorRGB < Type > ::~ColorRGB()
	{
		m_R = 0;
		m_G = 0;
		m_B = 0;
	}

	//Substitute (Overload of = operator)
	template < typename Type >
	ColorRGB < Type >& ColorRGB < Type > ::operator=( const ColorRGB < Type >& color )
	{
		m_R = color.m_R;
		m_G = color.m_G;
		m_B = color.m_B;

		return *this;
	}

	//Equivalence (Overload of == operator)
	template < typename Type >
	MapilBool ColorRGB < Type > ::operator==( const ColorRGB < Type >& color )
	{
		return ( ( m_R == color.m_R ) && ( m_G == color.m_G ) && ( m_B == color.m_B ) );
	}

	template < typename Type >
	class ColorARGB
	{
	public:
		Type				m_A;			///< Alpha.
		Type				m_R;			///< Red.
		Type				m_G;			///< Green.
		Type				m_B;			///< Blue.
		/**
		*	@brief Constructor.
		*/
		ColorARGB();
		/**
		*	@brief			Constructor.
		*	@param colorA	Alpha.
		*	@param colorR	Red.
		*	@param colorG	Green.
		*	@param colorB	Blue.
		*/
		ColorARGB( Type colorA, Type colorR, Type colorG, Type colorB );
		/**
		*	@brief			Copy constructor.
		*	@param color	ColorARGB object to be copied.
		*/
		ColorARGB( const ColorARGB < Type >& color );
		/**
		*	@brief Destructor.
		*/
		~ColorARGB();
		/**
		*	@brief			Substitute (Overload of = operator)
		*	@param color	ColorARGB object to be copied.
		*	@return			Copied ColorARGB object.
		*/
		ColorARGB& operator=( const ColorARGB < Type >& color );
		/**
		*	@brief			Equivalence (Overload of == operator)
		*	@param color	ColorARGB object to be compared.
		*	@return			True if color value is equivalent.
		*/
		MapilBool operator==( const ColorARGB < Type >& color );
	};

	//Constructer (1)
	template < typename Type >
	ColorARGB < Type > ::ColorARGB() : m_A( 0 ), m_R( 0 ), m_G( 0 ), m_B( 0 )
	{
	}

	//Constructer (2)
	template < typename Type >
	ColorARGB < Type > ::ColorARGB( Type colorA, Type colorR, Type colorG, Type colorB ) : m_A( colorA ), m_R( colorR ), m_G( colorG ), m_B( colorB )
	{
	}

	//Constructer (3)
	template < typename Type >
	ColorARGB < Type > ::ColorARGB( const ColorARGB < Type >& color ) : m_A( color.m_A ), m_R( color.m_R ), m_G( color.m_G ), m_B( color.m_B )
	{
	}

	//Destructer
	template < typename Type >
	ColorARGB < Type > ::~ColorARGB()
	{
		m_A = 0;
		m_R = 0;
		m_G = 0;
		m_B = 0;
	}

	//Substitute (Overload of = operator)
	template < typename Type >
	ColorARGB < Type >& ColorARGB < Type > ::operator=( const ColorARGB < Type >& color )
	{
		m_A = color.m_A;
		m_R = color.m_R;
		m_G = color.m_G;
		m_B = color.m_B;

		return *this;
	}

	//Equivalence (Overload of == operator)
	template < typename Type >
	MapilBool ColorARGB < Type > ::operator==( const ColorARGB < Type >& color )
	{
		return ( ( m_A == color.m_A ) && ( m_R == color.m_R ) && ( m_G == color.m_G ) && ( m_B == color.m_B ) );
	}

}

#endif
