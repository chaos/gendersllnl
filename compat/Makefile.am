##*****************************************************************************
## $Id: Makefile.am,v 1.17 2009-02-19 01:06:32 chu11 Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

INSTALLSITEARCH=`$(PERL) -e 'use Config; $$T=$$Config{installsitearch}; $$T=~/^\Q$$Config{siteprefix}\E\/(.+)/; print $$1;'`

if WITH_PERL_EXTENSIONS
HOSTLISTPMFILES = Hostlist.pm
HOSTLISTPMFILESdir = $(prefix)/$(INSTALLSITEARCH)
HOSTLISTPMFILES_DATA = $(HOSTLISTPMFILES)

Hostlist.$(PERLMAN3EXT):
# Hacks to make distcheck work
	if ! test -a Hostlist.pm; then \
		cp $(srcdir)/Hostlist.pm .; \
	fi
	$(POD2MAN) Hostlist.pm Hostlist.$(PERLMAN3EXT)

man3_MANS = Hostlist.$(PERLMAN3EXT)

install-data-hook:
	chmod 444 $(DESTDIR)/$(prefix)/$(INSTALLSITEARCH)/Hostlist.pm
endif

EXTRA_DIST = Hostlist.pm
