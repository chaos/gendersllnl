##*****************************************************************************
## $Id: configure.ac,v 1.2 2003-05-14 00:30:35 achu Exp $
##*****************************************************************************
## Process this file with autoconf to produce a configure script.
##*****************************************************************************

##
# Prologue.
##
AC_INIT([gendersllnl], [2.0], [chu11@llnl.gov])
AC_CONFIG_AUX_DIR([config])
AC_CANONICAL_SYSTEM

##
# Automake support.
##
AM_INIT_AUTOMAKE([check-news dist-bzip2 gnu])
AM_CONFIG_HEADER([config/config.h])
AM_MAINTAINER_MODE

# Libgenders install location
AC_MSG_CHECKING(for --with-xs-prefix )
AC_ARG_WITH(xs-prefix,
    AC_HELP_STRING([--with-xs-prefix=path], [define perl xs prefix for install]),
    [ case "$withval" in
    yes)
        withxsprefix=yes
        ;;
    no)
        ;;
    *)
        withxsprefix=yes
        XS_PREFIX="\"$withval\""
        ;;
    esac ]
)
AC_MSG_RESULT(${withxsprefix=no})
if test -z "$XS_PREFIX"; then
   XS_PREFIX="/usr"
fi
AC_SUBST(XS_PREFIX)

# Genders.pm install location
AC_MSG_CHECKING(for --with-gendersllnl-pm-prefix )
AC_ARG_WITH(gendersllnl-pm-prefix,
    AC_HELP_STRING([--with-gendersllnl-pm-prefix=path], [define genders.pm install dir]),
    [ case "$withval" in
    yes)
        withgendersllnlpm=yes
        ;;
    no)
        ;;
    *)
        withgendersllnlpm=yes
        GENDERSLLNL_PM_PREFIX="\"$withval\""
        ;;
    esac ]
)
AC_MSG_RESULT(${withgendersllnlpm=no})
if test -z "$GENDERSLLNL_PM_PREFIX"; then
   GENDERSLLNL_PM_PREFIX="/usr"
fi
AC_SUBST(GENDERSLLNL_PM_PREFIX)

##
# Checks for programs.
##
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_MAKE_SET

##
# Checks for header files.
##
AC_HEADER_STDC
AC_CHECK_HEADERS( \
  errno.h \
  stdlib.h \
  string.h \
  unistd.h \
  unistd.h \
)

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
AC_CHECK_LIB(genders, genders_handle_create)

##
# Epilogue.
##
AC_CONFIG_FILES( \
  Makefile \
  src/Makefile \
  src/libgendersllnl/Makefile \
  src/Libgendersllnl/Makefile \
  src/Gendersllnl/Makefile \
)
AC_OUTPUT

