##*****************************************************************************
## $Id: Makefile.am,v 1.5 2003-11-04 00:12:24 achu Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

# Use Perl's ExtUtils::MakeMaker to get autoconf/automake to install
# into the correct location

PERL_INSTALL_PREFIX = @PERL_INSTALL_PREFIX@

all: Makefile.xs
	$(MAKE) -f Makefile.xs

Makefile.xs: Makefile.PL Libgendersllnl.xs Libgendersllnl.pm
	cp ../libgendersllnl/gendersllnl.c .
	cp ../libgendersllnl/gendersllnl.h .
	cp ../libgendersllnl/hostlist.c .
	cp ../libgendersllnl/hostlist.h .
	$(PERL) Makefile.PL PREFIX=$(PERL_INSTALL_PREFIX) MAKEFILE=Makefile.xs FIRST_MAKEFILE=Makefile.xs

test: Makefile.xs 
	$(MAKE) -f Makefile.xs test

install: Makefile.xs
	$(MAKE) -f Makefile.xs pure_install

pure_install: Makefile.xs
	$(MAKE) -f Makefile.xs pure_install

install-data-local:
	$(MAKE) -f Makefile.xs pure_install

clean: 
	$(MAKE) -f Makefile.xs clean
	rm -f Makefile.xs
	rm -f Makefile.xs.old
	rm -f gendersllnl.c
	rm -f gendersllnl.h
	rm -f hostlist.c
	rm -f hostlist.h



