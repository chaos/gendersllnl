##*****************************************************************************
## $Id: Makefile.am,v 1.7 2005-01-10 23:42:25 achu Exp $
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
libgenders_la_CFLAGS      = -D_REENTRANT
libgendersllnl_la_SOURCES = gendersllnl.c hostlist.c
libgendersllnl_la_LDFLAGS = -version-info @LIBGENDERSLLNL_VERSION_INFO@ $(OTHER_FLAGS)
EXTRA_DIST                = gendersllnl.map
