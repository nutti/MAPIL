/**
*	@file	FontFormat.h
*	@brief	
*	@date	2011.7.31 (Sun) 11:47
*/

#ifndef INCLUDED_MAPIL_FONTFORMAT_H
#define INCLUDED_MAPIL_FONTFORMAT_H

#include "../CrossPlatform.h"

#include "../Type.h"
#include "../TChar.h"

namespace MAPIL
{
	struct FontFormat
	{
	public:
		MapilInt32				m_Height;			// Height of font.
		MapilInt32				m_Width;			// Width of font.
		MapilInt32				m_SlopeEntire;		// Slope. ( Entire )
		MapilInt32				m_Slope;			// Slope.
		MapilInt32				m_Thickness;		// Thickness of font.
		MapilBool				m_IsItalic;			// Italic.
		MapilBool				m_HasUnderline;		// Underline.
		MapilBool				m_HasStrikeOut;		// Strikeout.
		MapilULong				m_CharSet;			// Set of character.
		MapilULong				m_Precision;		// Precision.
		MapilULong				m_ClipPrecision;	// Precision of clipping.
		MapilULong				m_Quality;			// Quality.
		MapilULong				m_PitchAndFamily;	// Pitch and family.
		MapilTChar*				m_FontFaceName;		// Name of font face.
	};
}

#endif