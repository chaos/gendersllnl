##*****************************************************************************
## $Id: configure.ac,v 1.19 2005-04-22 22:32:53 achu Exp $
##*****************************************************************************
## Process this file with autoconf to produce a configure script.
##*****************************************************************************

##
# Prologue.
##
AC_INIT([gendersllnl])
AC_META
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([README])
AC_CANONICAL_SYSTEM

##
# Automake support.
##
AM_INIT_AUTOMAKE($PROJECT, $VERSION)
AM_CONFIG_HEADER([config/config.h])
AM_MAINTAINER_MODE

# Update this information before a public release only!
 
# libgendersllnl versioning
#
# If library source code has changed at all increment rev
# (current:rev:age) = (current:rev+1:age)
#
# If any interfaces have been added,removed, or changed increment current
#  and set rev = 0;
#
# If any interfaces have been added increment age
#
# If any interfaces have been removed, set age = 0
#
LIBGENDERSLLNL_CURRENT=0
LIBGENDERSLLNL_REVISION=0
LIBGENDERSLLNL_AGE=0
LIBGENDERSLLNL_VERSION_INFO=$LIBGENDERSLLNL_CURRENT:$LIBGENDERSLLNL_REVISION:$LIBGENDERSLLNL_AGE
AC_SUBST([LIBGENDERSLLNL_VERSION_INFO])
 
# Libgendersllnl and Gendersllnl versioning
PERLGENDERSLLNL_MAJOR=0
PERLGENDERSLLNL_MINOR=01
PERLGENDERSLLNL_VERSION=$PERLGENDERSLLNL_MAJOR.$PERLGENDERSLLNL_MINOR
AC_SUBST([PERLGENDERSLLNL_VERSION])

##
# Checks for programs.
##
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_MAKE_SET
AM_CONDITIONAL(WITH_GNU_LD, test "$with_gnu_ld" = "yes")
AC_PATH_PROG(PERL, perl)
AC_DEBUG

##
# Checks for header files.
##
AC_HEADER_STDC
AC_CHECK_HEADERS( \
  fcntl.h
  unistd.h \
  genders.h \
)

#
# Check for perl install destdir
#
AC_PERL_INSTALL_DESTDIR

##
# Checks for typedefs, structures, and compiler characteristics.
##
AC_C_BIGENDIAN
AC_C_CONST
AC_TYPE_UID_T

##
# Checks for library functions.
##
AC_FUNC_MALLOC
AC_CHECK_FUNCS( \
  strcmp \
  strlen \
  strcpy \
  strchr \
  strsep \
  strspn \
  strtok_r \
)

##
# Check for genders library that we need
##
AC_CHECK_LIB(genders, genders_handle_create, ,
             AC_MSG_ERROR([libgenders must be installed]))

##
# Epilogue.
##
AC_CONFIG_FILES( \
  gendersllnl.spec \
  Makefile \
  src/Makefile \
  src/libgendersllnl/Makefile \
  src/Libgendersllnl/Makefile \
  src/Gendersllnl/Makefile \
  dist/Makefile \
  compat/Makefile \
  man/Makefile \
  man/dist/Makefile \
  src/Libgendersllnl/Libgendersllnl.pm \
  src/Gendersllnl/Gendersllnl.pm \
)
AC_OUTPUT

