##*****************************************************************************
## $Id: Makefile.am,v 1.16 2007-01-17 00:52:10 chu11 Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

INSTALLSITEARCH=`$(PERL) -e 'use Config; $$T=$$Config{installsitearch}; $$T=~/^\Q$$Config{siteprefix}\E\/(.+)/; print $$1;'`

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

EXTRA_DIST = Hostlist.pm
