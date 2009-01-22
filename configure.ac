#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([trimage], [1.0], [peter@peter-b.co.uk])
AC_CONFIG_SRCDIR([src/pngtest.c])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB
PKG_PROG_PKG_CONFIG([0.23])

# Checks for libraries.
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.8.0])
PKG_CHECK_MODULES([CAIRO], [cairo >= 1.2.0])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

CFLAGS="$CAIRO_CFLAGS $GLIB_CFLAGS $CFLAGS"
LDFLAGS="$CAIRO_LIBS $GLIB_LIBS $LDFLAGS"

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
