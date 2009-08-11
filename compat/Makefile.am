##*****************************************************************************
## $Id: Makefile.am,v 1.18 2009-08-11 17:09:42 chu11 Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

INSTALLSITEARCH=`$(PERL) -e 'use Config; $$T=$$Config{installsitearch}; print $$T;'`

if WITH_PERL_EXTENSIONS
HOSTLISTPMFILES = Hostlist.pm
HOSTLISTPMFILESdir = $(INSTALLSITEARCH)
HOSTLISTPMFILES_DATA = $(HOSTLISTPMFILES)

Hostlist.$(PERLMAN3EXT):
# Hacks to make distcheck work
	if ! test -a Hostlist.pm; then \
		cp $(srcdir)/Hostlist.pm .; \
	fi
	$(POD2MAN) Hostlist.pm Hostlist.$(PERLMAN3EXT)

man3_MANS = Hostlist.$(PERLMAN3EXT)

install-data-hook:
	chmod 444 $(DESTDIR)/$(INSTALLSITEARCH)/Hostlist.pm
endif

EXTRA_DIST = Hostlist.pm
