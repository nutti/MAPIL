#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([MAPIL], [0.0], [nutti.metro@gmail.com])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([Src])
AC_CONFIG_HEADERS(config.h)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB(pthread, pthread_create )

#AC_CHECK_HEADERS([AL/al.h AL/alc.h], , AC_MSG_ERROR([Can't find OpenAL headers for sound.]))
#AC_CHECK_LIB([openal], [alGenSources], , AC_MSG_ERROR([Can't find OpenAL library for sound.]))


PKG_CHECK_MODULES( OPENAL, openal, [], AC_MSG_WARN([Warning: could not find OpenAL via pkg-config.] ) )
AC_ARG_WITH( openal-cflags, [ --with -openal-cflags=PATH Specify OpenAL cflags], OPENAL_CFLAGS="$withval" )
AC_ARG_WITH( openal-libs, [ --with-openal-libs=PATH Specify OpenAL libs], OPENAL_LIBS="$withval" )
AC_SUBST(OPENAL_CFLAGS)
AC_SUBST(OPENAL_LIBS)

AM_PATH_GTK_2_0([2.10.0],,AC_MSG_ERROR([Gtk+ 2.10.0 or higher required.]))

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h memory.h netdb.h netinet/in.h stdlib.h sys/socket.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([gethostbyname memset socket])

AC_CONFIG_FILES([Makefile
                 Include/Makefile
                 Lib/Makefile])
AC_OUTPUT
