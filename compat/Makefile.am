##*****************************************************************************
## $Id: Makefile.am,v 1.19 2009-08-12 21:53:52 chu11 Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

INSTALLXARCH="install${PERL_ARCH_INSTALL}arch"
XPREFIX="${PERL_ARCH_INSTALL}prefix"
INSTALLARCH=`$(PERL) -e 'use Config; $$T=$$Config{$(INSTALLXARCH)}; $$T=~/^\Q$$Config{$(XPREFIX)}\E\/(.+)/; print $$1;'`

if WITH_PERL_EXTENSIONS
HOSTLISTPMFILES = Hostlist.pm
HOSTLISTPMFILESdir = $(prefix)/$(INSTALLARCH)
HOSTLISTPMFILES_DATA = $(HOSTLISTPMFILES)

Hostlist.$(PERLMAN3EXT):
# Hacks to make distcheck work
	if ! test -a Hostlist.pm; then \
		cp $(srcdir)/Hostlist.pm .; \
	fi
	$(POD2MAN) Hostlist.pm Hostlist.$(PERLMAN3EXT)

man3_MANS = Hostlist.$(PERLMAN3EXT)

install-data-hook:
	chmod 444 $(DESTDIR)/$(prefix)/$(INSTALLARCH)/Hostlist.pm
endif

EXTRA_DIST = Hostlist.pm
