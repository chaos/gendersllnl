##*****************************************************************************
## $Id: Makefile.am,v 1.5 2003-11-04 00:12:24 achu Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

# Use Perl's ExtUtils::MakeMaker to get autoconf/automake to install
# into the correct location

PERL_INSTALL_PREFIX = @PERL_INSTALL_PREFIX@

all: Makefile.pm
	$(MAKE) -f Makefile.pm

Makefile.pm: Makefile.PL
	$(PERL) Makefile.PL PREFIX=$(PERL_INSTALL_PREFIX) MAKEFILE=Makefile.pm FIRST_MAKEFILE=\Makefile.pm

install: Makefile.pm
	$(MAKE) -f Makefile.pm pure_install

pure_install: Makefile.pm
	$(MAKE) -f Makefile.pm pure_install

install-data-local:
	$(MAKE) -f Makefile.pm pure_install

clean:
	$(MAKE) -f Makefile.pm clean
	rm -f Makefile.pm
	rm -f Makefile.pm.old
