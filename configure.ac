##*****************************************************************************
## $Id: configure.ac,v 1.12 2003-11-04 00:12:24 achu Exp $
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

# Perl Install Prefix
# - Used almost exclusively so perl install works with rpm builds
AC_MSG_CHECKING(for --with-perl-install-prefix )
AC_ARG_WITH(perl-install-prefix,
    AC_HELP_STRING([--with-perl-install-prefix=path], [define perl modules install prefix]),
    [ case "$withval" in
    yes)
        withperllinstallprefix=yes
        ;;
    no)
        ;;
    *)
        withperllinstallprefix=yes
        PERL_INSTALL_PREFIX="$withval"
        ;;
    esac ]
)
AC_MSG_RESULT(${withperllinstallprefix=no})
if test -z "$PERL_INSTALL_PREFIX"; then
   PERL_INSTALL_PREFIX='${prefix}'
fi
AC_SUBST(PERL_INSTALL_PREFIX)

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

