/**
*	@file	Shader.h
*	@brief	
*	@date	2012.10.6 (Sat) 22:22
*/

#ifndef INCLUDED_MAPIL_SHADER_H
#define INCLUDED_MAPIL_SHADER_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#include "Graphics.h"
#include "../Util/SharedPointer.hpp"


//-------------------------------------------------------------------
// Definitions.
//-------------------------------------------------------------------

namespace MAPIL
{
	class Shader : public Graphics
	{
	private:
	public:
		/**
		*	@brief		Constructor.
		*	@param pDev	SharedPointer to GraphicsDevice.
		*/
		explicit Shader( SharedPointer < GraphicsDevice > pDev );
		/**
		*	@brief Destructor.
		*/
		~Shader();
		virtual MapilVoid Create( const MapilTChar* pFileName, const MapilChar* pTechName ) = 0;
	};
}


#endif	// INCLUDED_MAPIL_SHADER_H