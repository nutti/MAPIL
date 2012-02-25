/**
*	@file	Type.h
*	@brief	This file defines original types.
*		If you use these types, you can make multi-platform applications.
*	@date	2011.5.25 13:53
*/

#ifndef INCLUDED_MAPIL_TYPE_H
#define INCLUDED_MAPIL_TYPE_H

namespace MAPIL
{

#ifndef NULL
#define NULL 0
#endif

#define	MapilBool		bool
#define	MapilTrue		1
#define	MapilFalse		0

	typedef	void				MapilVoid;
	typedef	short int			MapilShortInt32;
	typedef long int			MapilLongInt32;
	typedef	int					MapilInt32;
	typedef unsigned int		MapilUInt32;
	typedef unsigned short int	MapilUShortInt32;
	typedef unsigned long int	MapilULongInt32;
	typedef unsigned long		MapilULong;
	typedef	float				MapilFloat32;
	typedef	double				MapilDouble;
	typedef	char				MapilChar;
	typedef	unsigned char		MapilUChar;
	typedef	wchar_t				MapilWChar;

	typedef	MapilWChar			MapilTChar;

}

#endif
