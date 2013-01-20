/**
*	@file	ConstNums.h
*	@brief	This file includes constant numbers used in graphics devices.
*			Supported graphics devices are Direct Input and Win32API.
*	@date	2011.6.17 (Fri) 9:8
*/

#ifndef INCLUDED_MAPIL_GRAPHICS_CONSTNUMS_H
#define INCLUDED_MAPIL_GRAPHICS_CONSTNUMS_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	/**
	*	@brief Method to transform the image to be drawn.
	*/
	enum ImageTransformationMethod
	{
		IMAGE_TRANSFORMATION_METHOD_NONE						= 0,		///< No transformation
		IMAGE_TRANSFORMATION_METHOD_MOVE						= 1,		///< Move
		IMAGE_TRANSFORMATION_METHOD_SCALE						= 2,		///< Scale
		IMAGE_TRANSFORMATION_METHOD_ROTATE						= 3,		///< Rotate
		IMAGE_TRANSFORMATION_METHOD_MOVE_SCALE					= 4,		///< Move - Scale
		IMAGE_TRANSFORMATION_METHOD_SCALE_MOVE					= 5,		///< Scale - Move
		IMAGE_TRANSFORMATION_METHOD_MOVE_SCALE_ROTATE			= 6,		///< Move - Scale - Rotate
		IMAGE_TRANSFORMATION_METHOD_MOVE_ROTATE_SCALE			= 7,		///< Move - Rotate - Scale
		IMAGE_TRANSFORMATION_METHOD_SCALE_MOVE_ROTATE			= 8,		///< Scale - Move - Rotate
		IMAGE_TRANSFORMATION_METHOD_SCALE_ROTATE_MOVE			= 9,		///< Scale - Rotate - Move
		IMAGE_TRANSFORMATION_METHOD_ROTATE_MOVE_SCALE			= 10,		///< Rotate - Move - Scale
		IMAGE_TRANSFORMATION_METHOD_ROTATE_SCALE_MOVE			= 11,		///< Rotate - Scale - Move
		IMAGE_TRANSFORMATION_METHOD_CENTER						= 12,		///< Center
		IMAGE_TRANSFORMATION_METHOD_CENTER_MOVE					= 13,		///< Center - Move
		IMAGE_TRANSFORMATION_METHOD_CENTER_SCALE				= 14,		///< Center - Scale
		IMAGE_TRANSFORMATION_METHOD_CENTER_ROTATE				= 15,		///< Center - Rotate
		IMAGE_TRANSFORMATION_METHOD_CENTER_MOVE_SCALE			= 16,		///< Center - Move - Scale
		IMAGE_TRANSFORMATION_METHOD_CENTER_SCALE_MOVE			= 17,		///< Center - Scale - Move
		IMAGE_TRANSFORMATION_METHOD_CENTER_MOVE_SCALE_ROTATE	= 18,		///< Center - Move - Scale - Rotate
		IMAGE_TRANSFORMATION_METHOD_CENTER_MOVE_ROTATE_SCALE	= 19,		///< Center - Move - Rotate - Scale
		IMAGE_TRANSFORMATION_METHOD_CENTER_SCALE_MOVE_ROTATE	= 20,		///< Center - Scale - Move - Rotate
		IMAGE_TRANSFORMATION_METHOD_CENTER_SCALE_ROTATE_MOVE	= 21,		///< Cetner - Scale - Rotate - Move
		IMAGE_TRANSFORMATION_METHOD_CENTER_ROTATE_MOVE_SCALE	= 22,		///< Cetner - Rotate - Move - Scale
		IMAGE_TRANSFORMATION_METHOD_CENTER_ROTATE_SCALE_MOVE	= 23,		///< Center - Rotate - Scale - Move
	};

	/**
	*	@brief Method to transform the model to be drawn.
	*/
	enum ModelTransformationMethod
	{
		MODEL_TRANSFORMATION_METHOD_NONE					= 0,		///< No transformation
		MODEL_TRANSFORMATION_METHOD_MOVE					= 1,		///< Move
		MODEL_TRANSFORMATION_METHOD_SCALE					= 2,		///< Scale
		MODEL_TRANSFORMATION_METHOD_ROTATEX					= 3,		///< Rotate X
		MODEL_TRANSFORMATION_METHOD_ROTATEY					= 4,		///< Rotate Y
		MODEL_TRANSFORMATION_METHOD_ROTATEZ					= 5,		///< Rotate Z
		MODEL_TRANSFORMATION_METHOD_ROTATEXY				= 6,		///< Rotate (X¨Y)
		MODEL_TRANSFORMATION_METHOD_ROTATEYX				= 7,		///< Rotate (Y¨X)
		MODEL_TRANSFORMATION_METHOD_ROTATEYZ				= 8,		///< Rotate (Y¨Z)
		MODEL_TRANSFORMATION_METHOD_ROTATEZY				= 9,		///< Rotate (Z¨Y)
		MODEL_TRANSFORMATION_METHOD_ROTATEZX				= 10,		///< Rotate (Z¨X)
		MODEL_TRANSFORMATION_METHOD_ROTATEXZ				= 11,		///< Rotate (X¨Z)
		MODEL_TRANSFORMATION_METHOD_ROTATEXYZ				= 12,		///< Rotate (X¨Y¨Z)
		MODEL_TRANSFORMATION_METHOD_ROTATEXZY				= 13,		///< Rotate (X¨Z¨Y)
		MODEL_TRANSFORMATION_METHOD_ROTATEYXZ				= 14,		///< Rotate (Y¨X¨Z)
		MODEL_TRANSFORMATION_METHOD_ROTATEYZX				= 15,		///< Rotate (Y¨Z¨X)
		MODEL_TRANSFORMATION_METHOD_ROTATEZXY				= 16,		///< Rotate (Z¨X¨Y)
		MODEL_TRANSFORMATION_METHOD_ROTATEZYX				= 17,		///< Rotate (Z¨Y¨X)
		MODEL_TRANSFORMATION_METHOD_MOVE_SCALE				= 18,		///< Move ¨ Scale
		MODEL_TRANSFORMATION_METHOD_SCALE_MOVE				= 19,		///< Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_MOVE_ROTATEX			= 20,
		MODEL_TRANSFORMATION_METHOD_ROTATEX_SCALE_MOVE		= 21,		///< Rotate X ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEY_SCALE_MOVE		= 22,		///< Rotate Y ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEZ_SCALE_MOVE		= 23,		///< Rotate Z ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEXY_SCALE_MOVE		= 24,		///< Rotate (X¨Y) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEYX_SCALE_MOVE		= 25,		///< Rotate (Y¨X) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEYZ_SCALE_MOVE		= 26,		///< Rotate (Y¨Z) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEZY_SCALE_MOVE		= 27,		///< Rotate (Z¨Y) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEZX_SCALE_MOVE		= 28,		///< Rotate (Z¨X) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEXZ_SCALE_MOVE		= 29,		///< Rotate (X¨Z) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEXYZ_SCALE_MOVE	= 30,		///< Rotate (X¨Y¨Z) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEXZY_SCALE_MOVE	= 31,		///< Rotate (X¨Z¨Y) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEYXZ_SCALE_MOVE	= 32,		///< Rotate (Y¨X¨Z) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEYZX_SCALE_MOVE	= 33,		///< Rotate (Y¨Z¨X) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEZXY_SCALE_MOVE	= 34,		///< Rotate (Z¨X¨Y) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_ROTATEZYX_SCALE_MOVE	= 35,		///< Rotate (Z¨Y¨X) ¨ Scale ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEX_MOVE		= 36,		///< Scale ¨ Rotate X ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEY_MOVE		= 37,		///< Scale ¨ Rotate Y ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEZ_MOVE		= 38,		///< Scale ¨ Rotate Z ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEXY_MOVE		= 39,		///< Scale ¨ Rotate (X¨Y) ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEYX_MOVE		= 40,		///< Scale ¨ Rotate (Y¨X) ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEYZ_MOVE		= 41,		///< Scale ¨ Rotate (Y¨Z) ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEZY_MOVE		= 42,		///< Scale ¨ Rotate (Z¨Y) ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEZX_MOVE		= 43,		///< Scale ¨ Rotate (Z¨X) ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEXZ_MOVE		= 44,		///< Scale ¨ Rotate (X¨Z) ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEXYZ_MOVE	= 45,		///< Scale ¨ Rotate (X¨Y¨Z) ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEXZY_MOVE	= 46,		///< Scale ¨ Rotate (X¨Z¨Y) ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEYXZ_MOVE	= 47,		///< Scale ¨ Rotate (Y¨X¨Z) ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEYZX_MOVE	= 48,		///< Scale ¨ Rotate (Y¨Z¨X) ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEZXY_MOVE	= 49,		///< Scale ¨ Rotate (Z¨X¨Y) ¨ Move
		MODEL_TRANSFORMATION_METHOD_SCALE_ROTATEZYX_MOVE	= 50,		///< Scale ¨ Rotate (Z¨Y¨X) ¨ Move
	};

	/**
	*	@brief The mode of culling.
	*/
	enum CullMode
	{
		CULL_MODE_DISABLED			= 0,				///< Disabled.
		CULL_MODE_CLOCKWISE			= 1,				///< Clockwise.
		CULL_MODE_COUNTERCLOCKWISE	= 2,				///< Counterclockwise.
		CULL_MODE_BOTH				= 3,				///< Both.
	};

	/**
	*	@brief The mode of alpha blend.
	*/
	enum AlphaBlendMode
	{
		ALPHA_BLEND_MODE_DISABLED				= 0,	///< Disabled.
		ALPHA_BLEND_MODE_NO_TRANSPARENT			= 1,	///< No transparent.
		ALPHA_BLEND_MODE_SEMI_TRANSPARENT		= 2,	///< Semi transparent.
		ALPHA_BLEND_MODE_ADD					= 3,	///< Addition.
		ALPHA_BLEND_MODE_ADD_SEMI_TRANSPARENT	= 4,	///< Addition and semi transparent.
		ALPHA_BLEND_MODE_SUBTRACT_1				= 5,	///< Subtraction 1.
		ALPHA_BLEND_MODE_MULTIPLY_1				= 6,	///< Multiplication 1.
		ALPHA_BLEND_MODE_MULTIPLY_2				= 7,	///< Multiplication 2.
		ALPHA_BLEND_MODE_SCREEN					= 8,	///< Screen.
		ALPHA_BLEND_MODE_REVERSE_1				= 9,	///< Reverse 1.
		ALPHA_BLEND_MODE_SUBTRACT_2				= 10,	///< Subtraction 2.
		ALPHA_BLEND_MODE_REVERSE_2				= 11,	///< Reverse 2.
		ALPHA_BLEND_MODE_TOTAL,
	};

	/**
	*	@brief The mode for drawing texture.
	*/
	enum TextureMode
	{
		TEXTURE_MODE_2D				= 0,				///< 2D.
	};

	/**
	*	@brief Fog mode.
	*/
	enum FogMode
	{
		FOG_MODE_LINEAR				= 0,
		FOG_MODE_EXP				= 1,
		FOG_MODE_EXP2				= 2,
	};
}

#endif	// INCLUDED_MAPIL_GRAPHICS_CONSTNUMS_H
