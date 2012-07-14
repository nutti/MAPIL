/**
*	@file	Keyboard.cpp
*	@brief	
*	@date	2011.7.23 (Sat) 20:10
*/

#include "../../Include/MAPIL/CrossPlatform.h"

#include "../../Include/MAPIL/Input/Keyboard.h"

namespace MAPIL
{
	Keyboard::Keyboard( SharedPointer < InputDevice > pDev ) : Input( pDev )
	{
	}

	Keyboard::~Keyboard()
	{
	}

	MapilInt32 GetKeyboardKeyNum( MapilInt32 api, KeyboardKey key )
	{
		if( api == INPUT_API_WIN32API ){
			MapilUChar table[ 256 ] = {	0x00, 0x00, 0x00, 0x03,				// Ctrl-Break.
										0x00, 0x00, 0x00, 0x00, 0x08,		// Backspace.
										0x09,								// Tab.
										0x00, 0x00, 0x0C,
										0x0D,								// Enter.
										0x00, 0x00, 0x10,					// Shift.
										0x11,								// Ctrl.
										0x12,								// Menu.
										0x13,								// Pause.
										0x14,								// Caps Lock.
										0x15,
										0x00, 0x17,
										0x18,
										0x19,
										0x00, 0x1B,							// Esc.
										0x1C,
										0x1D,
										0x1E,
										0x1F,
										0x20,		// Space.
										0x21,		// Page Up.
										0x22,		// Page Down.
										0x23,		// End.
										0x24,		// Home.
										0x25,		// Left.
										0x26,		// Up.
										0x27,		// Right.
										0x28,		// Down.
										0x29,
										0x2A,
										0x2B,
										0x2C,		// Print Screen.
										0x2D,		// Insert.
										0x2E,		// Delete.
										0x2F,
										0x30,		// 0.
										0x31,		// 1.
										0x32,		// 2.
										0x33,		// 3.
										0x34,		// 4.
										0x35,		// 5.
										0x36,		// 6.
										0x37,		// 7.
										0x38,		// 8.
										0x39,		// 9.
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41,		// A.
										0x42,		// B.
										0x43,		// C.
										0x44,		// D.
										0x45,		// E.
										0x46,		// F.
										0x47,		// G.
										0x48,		// H.
										0x49,		// I.
										0x4A,		// J.
										0x4B,		// K.
										0x4C,		// L.
										0x4D,		// M.
										0x4E,		// N.
										0x4F,		// O.
										0x50,		// P.
										0x51,		// Q.
										0x52,		// R.
										0x53,		// S.
										0x54,		// T.
										0x55,		// U.
										0x56,		// V.
										0x57,		// W.
										0x58,		// X.
										0x59,		// Y.
										0x5A,		// Z.
										0x5B,		// Left Windows key.
										0x5C,		// Right Windows key.
										0x5D,		// Application key.
										0x00, 0x00, 0x60,		// 0. ( Num Lock on. )
										0x61,		// 1. ( Num Lock on. )
										0x62,		// 2. ( Num Lock on. )
										0x63,		// 3. ( Num Lock on. )
										0x64,		// 4. ( Num Lock on. )
										0x65,		// 5. ( Num Lock on. )
										0x66,		// 6. ( Num Lock on. )
										0x67,		// 7. ( Num Lock on. )
										0x68,		// 8. ( Num Lock on. )
										0x69,		// 9. ( Num Lock on. )
										0x6A,		// *.
										0x6B,		// +.
										0x6C,
										0x6D,		// -.
										0x6E,		// ..
										0x6F,		// /.
										0x70,		// F1.
										0x71,		// F1.
										0x72,		// F1.
										0x73,		// F1.
										0x74,		// F1.
										0x75,		// F1.
										0x76,		// F1.
										0x77,		// F1.
										0x78,		// F1.
										0x79,		// F1.
										0x7A,		// F1.
										0x7B,		// F1.
										0x7C,		// F1.
										0x7D,		// F1.
										0x7E,		// F1.
										0x7F,		// F1.
										0x80,		// F1.
										0x81,		// F1.
										0x82,		// F1.
										0x83,		// F1.
										0x84,		// F1.
										0x85,		// F1.
										0x86,		// F1.
										0x87,		// F1.
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90,		// Num Lock.
										0x91,		// Scroll.
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0xA0,		// Left Shift key.
										0xA1,		// Right Shift key.
										0xA2,		// Left Ctrl key.
										0xA3,		// Right Ctrl key.
										0xA4,		// Left Alt key.
										0xA5,		// Right Alt key.
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0xE5,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0xF6,
										0xF7,
										0xF8,
										0xF9,
										0xFA,
										0xFB,
										0xFC,
										0xFD,
										0xFE,
										0x00 };
			return table[ key ];
		}
		else if( api == INPUT_API_DIRECTINPUT ){
			MapilUChar table[ 256 ] = {	0x00, 0x00, 0x00, /***/0xFF,				// Ctrl-Break.
										0x00, 0x00, 0x00, 0x00, 0x0E,		// Backspace.
										0x0F,								// Tab.
										0x00, 0x00, /***/0xFF,
										0x1C,								// Enter.
										0x00, 0x00, /***/0xFF,					// Shift.
										/***/0xFF,								// Ctrl.
										/***/0xFF,								// Menu.
										0xC5,								// Pause.
										/***/0xFF,								// Caps Lock.
										/***/0xFF,
										0x00, /***/0xFF,
										/***/0xFF,
										/***/0xFF,
										0x00, 0x01,							// Esc.
										/***/0xFF,
										/***/0xFF,
										/***/0xFF,
										/***/0xFF,
										0x39,		// Space.
										0xC9,		// Page Up.
										0xD1,		// Page Down.
										0xCF,		// End.
										0xC7,		// Home.
										0xCB,		// Left.
										0xC8,		// Up.
										0xCD,		// Right.
										0xD0,		// Down.
										/***/0xFF,
										/***/0xFF,
										/***/0xFF,
										/***/0xFF,		// Print Screen.
										0xD2,		// Insert.
										0xD3,		// Delete.
										/***/0xFF,
										0x0B,		// 0.
										0x02,		// 1.
										0x03,		// 2.
										0x04,		// 3.
										0x05,		// 4.
										0x06,		// 5.
										0x07,		// 6.
										0x08,		// 7.
										0x09,		// 8.
										0x0A,		// 9.
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E,		// A.
										0x30,		// B.
										0x2E,		// C.
										0x20,		// D.
										0x12,		// E.
										0x21,		// F.
										0x22,		// G.
										0x23,		// H.
										0x17,		// I.
										0x24,		// J.
										0x25,		// K.
										0x26,		// L.
										0x32,		// M.
										0x31,		// N.
										0x18,		// O.
										0x19,		// P.
										0x10,		// Q.
										0x13,		// R.
										0x1F,		// S.
										0x14,		// T.
										0x16,		// U.
										0x2F,		// V.
										0x11,		// W.
										0x2D,		// X.
										0x15,		// Y.
										0x2C,		// Z.
										0xDB,		// Left Windows key.
										0xDC,		// Right Windows key.
										0xDD,		// Application key.
										0x00, 0x00, 0x52,		// 0. ( Num Lock on. )
										0x4F,		// 1. ( Num Lock on. )
										0x50,		// 2. ( Num Lock on. )
										0x51,		// 3. ( Num Lock on. )
										0x4B,		// 4. ( Num Lock on. )
										0x4C,		// 5. ( Num Lock on. )
										0x4D,		// 6. ( Num Lock on. )
										0x47,		// 7. ( Num Lock on. )
										0x48,		// 8. ( Num Lock on. )
										0x49,		// 9. ( Num Lock on. )
										/***/0xFF,		// *.
										/***/0xFF,		// +.
										/***/0xFF,
										0x0C,		// -.
										0x34,		// ..
										0x35,		// /.
										0x3B,		// F1.
										0x3C,		// F2.
										0x3D,		// F3.
										0x3E,		// F4.
										0x3F,		// F5.
										0x40,		// F6.
										0x41,		// F7.
										0x42,		// F8.
										0x43,		// F9.
										0x44,		// F10.
										0x57,		// F11.
										0x58,		// F12.
										0x64,		// F13.
										0x65,		// F14.
										0x66,		// F15.
										/***/0xFF,		// F16.
										/***/0xFF,		// F17.
										/***/0xFF,		// F18.
										/***/0xFF,		// F19.
										/***/0xFF,		// F20.
										/***/0xFF,		// F21.
										/***/0xFF,		// F22.
										/***/0xFF,		// F23.
										/***/0xFF,		// F24.
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45,		// Num Lock.
										0x46,		// Scroll.
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x2A,		// Left Shift key.
										0x36,		// Right Shift key.
										0x1D,		// Left Ctrl key.
										0x9D,		// Right Ctrl key.
										0x38,		// Left Alt key.
										0xB8,		// Right Alt key.
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										/***/0xFF,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										/***/0xFF,
										/***/0xFF,
										/***/0xFF,
										/***/0xFF,
										/***/0xFF,
										/***/0xFF,
										/***/0xFF,
										/***/0xFF,
										/***/0xFF,
										0x00 };
										// Unsupported list. 0xFF is not supported.(/***/mark)
										// EQUAL, LEFTBRACKET, RIGHTBRACKET, SEMICOLON, APOSTROPHE, GRAVE
										// BACKSLASH, COMMA, NUMPADMULTIPLY, CAPITAL, NUMPADSUBTRACT
										// NUMPADADD, NUMPADDECIMAL, OEM102, KANA, ABNTC1, CONVERT, YEN
										// ABNTC2, NUMPADEQUAL, PREVTRACK, AT, COLON, UNDERLINE
										// KANJI, STOP, AX, UNLABELED, NEXTTRACK, NUMPADENTER, MUTE
										// CALCULATOR, PLAYPAUSE, MEDIASTOP, VOLUMEDOWN, VOLUMEUP, WEBHOME
										// NUMPADCOMMA, NUMPADDIVIDE, SYSRQ, POWER, SLEEP, WAKE, WEBSEARCH
										// WEBFAVORITES, WEBREFRESH, WEBSTOP, WEBFORWARD, WEBBACK, MYCOMPUTER
										// MAPIL, MEDIASELECT
			return table[ key ];
		}
		else{
			return 0;
		}
	}

	MapilInt32 GetKeyboardKeyNum( SharedPointer < InputDevice > pDev, KeyboardKey key )
	{
		return GetKeyboardKeyNum( pDev->GetInputAPI(), key );
	}

	MapilBool IsKeyPushed( MapilInt32 key )
	{
		return ( key & 0x80 ) ? MapilTrue : MapilFalse;
	}
}