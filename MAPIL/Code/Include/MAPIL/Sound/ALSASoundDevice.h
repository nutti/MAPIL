/**
*	@file	ALSASoundDevice.h
*	@brief	ALSASoundDevice class is needed when the user
*			uses class related to ALSA. This class will be
*			contained to SoundDevice class.
*	@date	2011.6.25 (Sat) 10:43
*/

#ifndef INCLUDED_MAPIL_ALSASOUNDDEVICE_H
#define INCLUDED_MAPIL_ALSASOUNDDEVICE_H

//-------------------------------------------------------------------
// Includes.
//-------------------------------------------------------------------

#include "../CrossPlatform.h"

#ifdef API_ALSA

#include <alsa/asoundlib.h>

#include "../Util/MapilObject.h"
#include "../Type.h"

//-------------------------------------------------------------------
// Class definition.
//-------------------------------------------------------------------

namespace MAPIL
{

	/**
	*	@brief Format of PCM deivce.
	*/
	enum PCMDeviceFormat
	{
		PCM_DEV_FMT_NONE				= 0,		///< Unknown format.
		PCM_DEV_FMT_USIGNED_8BIT		= 1,		///< Unsigned 8bit.
		PCM_DEV_FMT_SIGNED_8BIT			= 2,		///< Signed 8bit.
		PCM_DEV_FMT_USIGNED_16BIT_LE	= 3,		///< Unsigned 16bit. ( Little endian. )
		PCM_DEV_FMT_USIGNED_16BIT_BE	= 4,		///< Unsigned 16bit. ( Big endian. )
		PCM_DEV_FMT_SIGNED_16BIT_LE		= 5,		///< Signed 16bit. ( Little endian. )
		PCM_DEV_FMT_SIGNED_16BIT_BE		= 6,		///< Signed 16bit. ( Big endian. )
	};
	
	/**
	*	@brief Open mode of PCM deivce.
	*/
	enum PCMDeviceOpenMode
	{
		PCM_DEV_OPEN_NONE_MODE			= 0,		///< Unknown mode.
		PCM_DEV_OPEN_WRITE_MODE			= 1,		///< Writing mode.
		PCM_DEV_OPEN_READ_MODE			= 2,		///< Reading mode.
	};
	
	struct PCMDevConf
	{
	public:
		PCMDeviceFormat		m_Fmt;				///< Format.
		MapilUInt32			m_Freq;				///< Frequency.
		MapilUInt32			m_Channel;			///< Channel.
	};

	class ALSASoundDevice : public MapilObject
	{
	private:
		snd_pcm_t*					m_pHandle;		///< Handle.
		PCMDeviceOpenMode			m_Mode;			///< Open mode of PCM device.
		snd_pcm_hw_params_t*		m_pParam;		///< Parameter.
	public:
		/**
		*	@brief Constructor.
		*/
		ALSASoundDevice();
		/**
		*	@brief Destructor.
		*/
		~ALSASoundDevice();
		/**
		*	@brief Open device.
		*	@param mode Open mode of PCM device.
		*/
		MapilVoid Open( PCMDeviceOpenMode mode );
		/**
		*	@brief Set parameter of PCM deive.
		*	@param pConf Parameter which will be configured.
		*/
		MapilVoid SetParam( PCMDevConf* pConf );
		/**
		*	@brief Close PCM device.
		*/
		MapilVoid Close();
		/**
		*	@brief Write data to PCM device.
		*	@param pData Written data.
		*	@param dataSize Size of written data.
		*/
		MapilVoid Write(	const MapilChar* pData,
							MapilInt32 dataSize );
		/**
		*	@brief Write data to PCM device.
		*	@param pData Written data.
		*	@param dataSize Size of written data.
		*/
		MapilVoid Write(	const MapilShortInt32* pData,
							MapilInt32 dataSize );
		/**
		*	@brief Read data from PCM device.
		*	@param pData Read data.
		*	@param dataSize Size of read data.
		*/
		MapilVoid Read(	MapilChar* pData,
							MapilInt32 dataSize );
	};
}

#endif	// API_ALSA

#endif	// INCLUDED_MAPIL_ALSASOUNDDEVICE_H