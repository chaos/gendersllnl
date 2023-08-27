##*****************************************************************************
## $Id: configure.ac,v 1.28 2009-02-19 01:07:51 chu11 Exp $
##*****************************************************************************
## Process this file with autoconf to produce a configure script.
##*****************************************************************************

##
# Prologue.
##
AC_INIT([gendersllnl],[1.20.1])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([README])
AC_CANONICAL_TARGET

##
# Automake support.
##
AM_INIT_AUTOMAKE([tar-ustar subdir-objects])
AC_CONFIG_HEADERS([config/config.h])
AM_MAINTAINER_MODE

# Update this information before a public release only!
 
# libgendersllnl versioning
#
# If the library source code has changed at all since the last update,
# then increment c:r: c:r+1:).                                                                                     
#
# If any interfaces have been added, removed, or changed since the
# last update, increment current, and set revision to 0.
#
# If any interfaces have been added since the last public release,
# then increment age.
#
# If any interfaces have been removed or changed since the last public                                                
# release, then set age to 0.
#                                               
LIBGENDERSLLNL_CURRENT=0
LIBGENDERSLLNL_REVISION=1
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
LT_INIT
AC_PROG_MAKE_SET
AM_CONDITIONAL(WITH_GNU_LD, test "$with_gnu_ld" = "yes")
AC_PATH_PROG(PERL, perl)
AC_PATH_PROG([POD2MAN], [pod2man], [/usr/bin/pod2man], [$PATH:/usr/perl5/bin/])
AC_DEBUG

##
# Optional genders include and library directories.
# Tests that required header and library are usable.
##
AC_GENDERS_INCLUDEDIR
AC_GENDERS_LIBDIR

##
# Checks for header files.
##
AC_HEADER_STDC
AC_CHECK_HEADERS( \
  fcntl.h \
  unistd.h \
)

#
# Check for perl stuff
#
AC_PERL_DESTDIR
AC_PERL_EXTENSIONS
AM_CONDITIONAL(WITH_PERL_EXTENSIONS, [test "$ac_with_perl_extensions" = "yes"])

#
# Determine Perl section-3 man page extension
#
PERLMAN3EXT=`$PERL -MConfig -e 'print $Config{man3ext}'`
AC_SUBST([PERLMAN3EXT])

#
# Determine Perl Install Location
#
AC_PERL_SITE_ARCH
AC_PERL_VENDOR_ARCH
if test "$ac_with_perl_site_arch" = yes && \
   test "$ac_with_perl_vendor_arch" = yes ; then
   AC_MSG_ERROR([cannot specify both perl site arch and vendor arch])
elif test "$ac_with_perl_site_arch" = yes; then
   PERL_ARCH_INSTALL=site
elif test "$ac_with_perl_vendor_arch" = yes; then
   PERL_ARCH_INSTALL=vendor
else
   PERL_ARCH_INSTALL=vendor
fi
AC_SUBST(PERL_ARCH_INSTALL)

##
# Checks for typedefs, structures, and compiler characteristics.
##
AC_C_BIGENDIAN
AC_C_CONST
AC_TYPE_UID_T

##
# Checks for library functions.
##
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

