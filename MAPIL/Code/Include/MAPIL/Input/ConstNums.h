/**
*	@file	ConstNums.h
*	@brief	This file includes constant numbers used in input devices.
*			Supported input devices are Direct Input and Win32API.
*	@date	2011.7.23 (Sat) 21:02
*/

#ifndef INCLUDED_MAPIL_INPUT_CONSTNUMS_H
#define INCLUDED_MAPIL_INPUT_CONSTNUMS_H

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
	*	@brief Key codes for the keyboard.
	*/
	enum KeyboardKey
	{
		KEYBOARD_KEY_CANCEL			= 0x03,		///< Ctrl-Break.
		KEYBOARD_KEY_BACK			= 0x08,		///< Backspace.
		KEYBOARD_KEY_TAB			= 0x09,		///< Tab.
		KEYBOARD_KEY_CLEAR			= 0x0C,
		KEYBOARD_KEY_RETURN			= 0x0D,		///< Enter.
		KEYBOARD_KEY_SHIFT			= 0x10,		///< Shift.
		KEYBOARD_KEY_CONTROL		= 0x11,		///< Ctrl.
		KEYBOARD_KEY_MENU			= 0x12,		///< Menu.
		KEYBOARD_KEY_PAUSE			= 0x13,		///< Pause.
		KEYBOARD_KEY_CAPITAL		= 0x14,		///< Caps Lock.
		KEYBOARD_KEY_KANA			= 0x15,
		KEYBOARD_KEY_JINJA			= 0x17,
		KEYBOARD_KEY_FINAL			= 0x18,
		KEYBOARD_KEY_HANJA			= 0x19,
		KEYBOARD_KEY_ESCAPE			= 0x1B,		///< Esc.
		KEYBOARD_KEY_CONVERT		= 0x1C,
		KEYBOARD_KEY_NONCONVERT		= 0x1D,
		KEYBOARD_KEY_ACCEPT			= 0x1E,
		KEYBOARD_KEY_MODECHANGE		= 0x1F,
		KEYBOARD_KEY_SPACE			= 0x20,		///< Space.
		KEYBOARD_KEY_PRIOR			= 0x21,		///< Page Up.
		KEYBOARD_KEY_NEXT			= 0x22,		///< Page Down.
		KEYBOARD_KEY_END			= 0x23,		///< End.
		KEYBOARD_KEY_HOME			= 0x24,		///< Home.
		KEYBOARD_KEY_LEFT			= 0x25,		///< Left.
		KEYBOARD_KEY_UP				= 0x26,		///< Up.
		KEYBOARD_KEY_RIGHT			= 0x27,		///< Right.
		KEYBOARD_KEY_DOWN			= 0x28,		///< Down.
		KEYBOARD_KEY_SELECT			= 0x29,
		KEYBOARD_KEY_PRINT			= 0x2A,
		KEYBOARD_KEY_EXECUTE		= 0x2B,
		KEYBOARD_KEY_SNAPSHOT		= 0x2C,		///< Print Screen.
		KEYBOARD_KEY_INSERT			= 0x2D,		///< Insert.
		KEYBOARD_KEY_DELETE			= 0x2E,		///< Delete.
		KEYBOARD_KEY_HELP			= 0x2F,
		KEYBOARD_KEY_0				= 0x30,		///< 0.
		KEYBOARD_KEY_1				= 0x31,		///< 1.
		KEYBOARD_KEY_2				= 0x32,		///< 2.
		KEYBOARD_KEY_3				= 0x33,		///< 3.
		KEYBOARD_KEY_4				= 0x34,		///< 4.
		KEYBOARD_KEY_5				= 0x35,		///< 5.
		KEYBOARD_KEY_6				= 0x36,		///< 6.
		KEYBOARD_KEY_7				= 0x37,		///< 7.
		KEYBOARD_KEY_8				= 0x38,		///< 8.
		KEYBOARD_KEY_9				= 0x39,		///< 9.
		KEYBOARD_KEY_A				= 0x41,		///< A.
		KEYBOARD_KEY_B				= 0x42,		///< B.
		KEYBOARD_KEY_C				= 0x43,		///< C.
		KEYBOARD_KEY_D				= 0x44,		///< D.
		KEYBOARD_KEY_E				= 0x45,		///< E.
		KEYBOARD_KEY_F				= 0x46,		///< F.
		KEYBOARD_KEY_G				= 0x47,		///< G.
		KEYBOARD_KEY_H				= 0x48,		///< H.
		KEYBOARD_KEY_I				= 0x49,		///< I.
		KEYBOARD_KEY_J				= 0x4A,		///< J.
		KEYBOARD_KEY_K				= 0x4B,		///< K.
		KEYBOARD_KEY_L				= 0x4C,		///< L.
		KEYBOARD_KEY_M				= 0x4D,		///< M.
		KEYBOARD_KEY_N				= 0x4E,		///< N.
		KEYBOARD_KEY_O				= 0x4F,		///< O.
		KEYBOARD_KEY_P				= 0x50,		///< P.
		KEYBOARD_KEY_Q				= 0x51,		///< Q.
		KEYBOARD_KEY_R				= 0x52,		///< R.
		KEYBOARD_KEY_S				= 0x53,		///< S.
		KEYBOARD_KEY_T				= 0x54,		///< T.
		KEYBOARD_KEY_U				= 0x55,		///< U.
		KEYBOARD_KEY_V				= 0x56,		///< V.
		KEYBOARD_KEY_W				= 0x57,		///< W.
		KEYBOARD_KEY_X				= 0x58,		///< X.
		KEYBOARD_KEY_Y				= 0x59,		///< Y.
		KEYBOARD_KEY_Z				= 0x5A,		///< Z.
		KEYBOARD_KEY_LWIN			= 0x5B,		///< Left Windows key.
		KEYBOARD_KEY_RWIN			= 0x5C,		///< Right Windows key.
		KEYBOARD_KEY_APPS			= 0x5D,		///< Application key.
		KEYBOARD_KEY_NUMPAD0		= 0x60,		///< 0. ( Num Lock on. )
		KEYBOARD_KEY_NUMPAD1		= 0x61,		///< 1. ( Num Lock on. )
		KEYBOARD_KEY_NUMPAD2		= 0x62,		///< 2. ( Num Lock on. )
		KEYBOARD_KEY_NUMPAD3		= 0x63,		///< 3. ( Num Lock on. )
		KEYBOARD_KEY_NUMPAD4		= 0x64,		///< 4. ( Num Lock on. )
		KEYBOARD_KEY_NUMPAD5		= 0x65,		///< 5. ( Num Lock on. )
		KEYBOARD_KEY_NUMPAD6		= 0x66,		///< 6. ( Num Lock on. )
		KEYBOARD_KEY_NUMPAD7		= 0x67,		///< 7. ( Num Lock on. )
		KEYBOARD_KEY_NUMPAD8		= 0x68,		///< 8. ( Num Lock on. )
		KEYBOARD_KEY_NUMPAD9		= 0x69,		///< 9. ( Num Lock on. )
		KEYBOARD_KEY_MULTIPLY		= 0x6A,		///< *.
		KEYBOARD_KEY_ADD			= 0x6B,		///< +.
		KEYBOARD_KEY_SEPARATOR		= 0x6C,
		KEYBOARD_KEY_SUBTRACT		= 0x6D,		///< -.
		KEYBOARD_KEY_DECIMAL		= 0x6E,		///< ..
		KEYBOARD_KEY_DIVIDE			= 0x6F,		///< /.
		KEYBOARD_KEY_F1				= 0x70,		///< F1.
		KEYBOARD_KEY_F2				= 0x71,		///< F2.
		KEYBOARD_KEY_F3				= 0x72,		///< F3.
		KEYBOARD_KEY_F4				= 0x73,		///< F4.
		KEYBOARD_KEY_F5				= 0x74,		///< F5.
		KEYBOARD_KEY_F6				= 0x75,		///< F6.
		KEYBOARD_KEY_F7				= 0x76,		///< F7.
		KEYBOARD_KEY_F8				= 0x77,		///< F8.
		KEYBOARD_KEY_F9				= 0x78,		///< F9.
		KEYBOARD_KEY_F10			= 0x79,		///< F10.
		KEYBOARD_KEY_F11			= 0x7A,		///< F11.
		KEYBOARD_KEY_F12			= 0x7B,		///< F12.
		KEYBOARD_KEY_F13			= 0x7C,		///< F13.
		KEYBOARD_KEY_F14			= 0x7D,		///< F14.
		KEYBOARD_KEY_F15			= 0x7E,		///< F15.
		KEYBOARD_KEY_F16			= 0x7F,		///< F16.
		KEYBOARD_KEY_F17			= 0x80,		///< F17.
		KEYBOARD_KEY_F18			= 0x81,		///< F18.
		KEYBOARD_KEY_F19			= 0x82,		///< F19.
		KEYBOARD_KEY_F20			= 0x83,		///< F20.
		KEYBOARD_KEY_F21			= 0x84,		///< F21.
		KEYBOARD_KEY_F22			= 0x85,		///< F22.
		KEYBOARD_KEY_F23			= 0x86,		///< F23.
		KEYBOARD_KEY_F24			= 0x87,		///< F24.
		KEYBOARD_KEY_NUMLOCK		= 0x90,		///< Num Lock.
		KEYBOARD_KEY_SCROLL			= 0x91,		///< Scroll.
		KEYBOARD_KEY_LSHIFT			= 0xA0,		///< Left Shift key.
		KEYBOARD_KEY_RSHIFT			= 0xA1,		///< Right Shift key.
		KEYBOARD_KEY_LCONTROL		= 0xA2,		///< Left Ctrl key.
		KEYBOARD_KEY_RCONTROL		= 0xA3,		///< Right Ctrl key.
		KEYBOARD_KEY_LMENU			= 0xA4,		///< Left Alt key.
		KEYBOARD_KEY_RMENU			= 0xA5,		///< Right Alt key.
		KEYBOARD_KEY_PROCESSKEY		= 0xE5,
		KEYBOARD_KEY_ATTN			= 0xF6,
		KEYBOARD_KEY_CRSEL			= 0xF7,
		KEYBOARD_KEY_EXSEL			= 0xF8,
		KEYBOARD_KEY_EREOF			= 0xF9,
		KEYBOARD_KEY_PLAY			= 0xFA,
		KEYBOARD_KEY_ZOOM			= 0xFB,
		KEYBOARD_KEY_NONAME			= 0xFC,
		KEYBOARD_KEY_PA1			= 0xFD,
		KEYBOARD_KEY_OME_CLEAR		= 0xFE,
	};

	/**
	*	@brief Mouse codes for the mouse.
	*/
	enum MouseButton
	{
		MOUSE_BUTTON_LEFT			= 0x01,			///< Left.
		MOUSE_BUTTON_RIGHT			= 0x02,			///< Right.
		MOUSE_BUTTON_CENTER			= 0x04,			///< Center.
	};
}

#endif	// INCLUDED_MAPIL_INPUT_CONSTNUMS_H