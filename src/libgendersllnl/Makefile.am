##*****************************************************************************
## $Id: Makefile.am,v 1.8 2007-01-17 00:52:10 chu11 Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

if WITH_GNU_LD
VERSION_SCRIPT = $(srcdir)/gendersllnl.map
OTHER_FLAGS = -Wl,--version-script=$(VERSION_SCRIPT)
endif

include_HEADERS           = gendersllnl.h
noinst_HEADERS            = hostlist.h
lib_LTLIBRARIES           = libgendersllnl.la
libgendersllnl_la_CFLAGS  = -D_REENTRANT @GENDERS_INCLUDEDIR@
libgendersllnl_la_SOURCES = gendersllnl.c hostlist.c
libgendersllnl_la_LDFLAGS = -version-info @LIBGENDERSLLNL_VERSION_INFO@ $(OTHER_FLAGS) @GENDERS_LIBDIR@ -lgenders
EXTRA_DIST                = gendersllnl.map
