##*****************************************************************************
## $Id: configure.ac,v 1.10 2003-09-11 16:00:07 achu Exp $
##*****************************************************************************
## Process this file with autoconf to produce a configure script.
##*****************************************************************************

##
# Prologue.
##
AC_INIT([gendersllnl])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([README])
AC_CANONICAL_SYSTEM

##
# Automake support.
##
AM_INIT_AUTOMAKE($PROJECT, $VERSION)
AM_CONFIG_HEADER([config/config.h])
AM_MAINTAINER_MODE

# Libgenders install location
AC_MSG_CHECKING(for --with-xs-prefix )
AC_ARG_WITH(xs-prefix,
    AC_HELP_STRING([--with-xs-prefix=path], [define perl xs prefix dir]),
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
   XS_PREFIX='${prefix}'
fi
AC_SUBST(XS_PREFIX)

# Gendersllnl.pm install location
AC_MSG_CHECKING(for --with-gendersllnl-pm-prefix )
AC_ARG_WITH(gendersllnl-pm-prefix,
    AC_HELP_STRING([--with-gendersllnl-pm-prefix=path], [define gendersllnl.pm prefix dir]),
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
   GENDERSLLNL_PM_PREFIX='${prefix}'
fi
AC_SUBST(GENDERSLLNL_PM_PREFIX)

# compat install location
AC_MSG_CHECKING(for --with-compat-prefix )
AC_ARG_WITH(compat-prefix,
    AC_HELP_STRING([--with-compat-prefix=path], [define compat subpackage prefix]),
    [ case "$withval" in
    yes)
        withcompatprefix=yes
        ;;
    no)
        ;;
    *)
        withcompatprefix=yes
        COMPAT_PREFIX="\"$withval\""
        ;;
    esac ]
)
AC_MSG_RESULT(${withcompatprefix=no})
if test -z "$COMPAT_PREFIX"; then
   COMPAT_PREFIX='${prefix}'
fi
AC_SUBST(COMPAT_PREFIX)

##
# Checks for programs.
##
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_MAKE_SET
AC_PATH_PROG(PERL, perl)

##
# Checks for header files.
##
AC_HEADER_STDC
AC_CHECK_HEADERS( \
  errno.h \
  stdio.h \
  stdlib.h \
  string.h \
  unistd.h \
  genders.h \
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
)
AC_OUTPUT

