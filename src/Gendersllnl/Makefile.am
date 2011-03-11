##*****************************************************************************
## $Id: Makefile.am,v 1.25 2009-08-12 21:53:52 chu11 Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

INSTALLXARCH="install${PERL_ARCH_INSTALL}arch"
XPREFIX="${PERL_ARCH_INSTALL}prefix"
INSTALLARCH=`$(PERL) -e 'use Config; $$T=$$Config{$(INSTALLXARCH)}; $$T=~/^\Q$$Config{$(XPREFIX)}\E\/(.+)/; print $$1;'`

if WITH_PERL_EXTENSIONS
GENDERSLLNLPMFILES = Gendersllnl.pm
GENDERSLLNLPMFILESdir = $(prefix)/$(INSTALLARCH)
GENDERSLLNLPMFILES_DATA = $(GENDERSLLNLPMFILES)
 
Gendersllnl.$(PERLMAN3EXT):
# Hacks to make distcheck work
	if ! test -a Gendersllnl.pm; then \
		cp $(srcdir)/Gendersllnl.pm .; \
	fi
	$(POD2MAN) Gendersllnl.pm Gendersllnl.$(PERLMAN3EXT)
 
man3_MANS = Gendersllnl.$(PERLMAN3EXT)
 
install-data-hook:
	chmod 444 $(DESTDIR)/$(prefix)/$(INSTALLARCH)/Gendersllnl.pm
endif
 
EXTRA_DIST = Gendersllnl.pm
