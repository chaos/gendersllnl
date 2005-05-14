##*****************************************************************************
## $Id: Makefile.am,v 1.15 2005-05-14 05:00:22 achu Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

INSTALLSITEARCH=`perl -e 'use Config; $$T=$$Config{installsitearch}; $$T=~/\/usr\/(lib|lib64)\/(.*)/; print $$2;'`

HOSTLISTPMFILES = Hostlist.pm
HOSTLISTPMFILESdir = $(libdir)/$(INSTALLSITEARCH)
HOSTLISTPMFILES_DATA = $(HOSTLISTPMFILES)

Hostlist.3pm:
# Hacks to make distcheck work
	if ! test -a Hostlist.pm; then \
		cp $(srcdir)/Hostlist.pm .; \
	fi
	$(POD2MAN) Hostlist.pm Hostlist.3pm

man3_MANS = Hostlist.3pm

install-data-hook:
	chmod 444 $(DESTDIR)/$(libdir)/$(INSTALLSITEARCH)/Hostlist.pm

EXTRA_DIST = Hostlist.pm
