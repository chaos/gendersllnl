##*****************************************************************************
## $Id: Makefile.am,v 1.9 2004-06-08 16:16:36 achu Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

# Use Perl's ExtUtils::MakeMaker to get autoconf/automake to install
# into the correct location

PERL_INSTALL_PREFIX = @PERL_INSTALL_PREFIX@

all: Makefile.xs
	$(MAKE) -f Makefile.xs

Makefile.xs: Makefile.PL Libgendersllnl.xs Libgendersllnl.pm
	cp $(srcdir)/../libgendersllnl/gendersllnl.c .
	cp $(srcdir)/../libgendersllnl/gendersllnl.h .
	cp $(srcdir)/../libgendersllnl/hostlist.c .
	cp $(srcdir)/../libgendersllnl/hostlist.h .
	$(PERL) $(srcdir)/Makefile.PL PREFIX=$(PERL_INSTALL_PREFIX) MAKEFILE=Makefile.xs FIRST_MAKEFILE=Makefile.xs

test: Makefile.xs 
	$(MAKE) -f Makefile.xs test

install: Makefile.xs
	$(MAKE) -f Makefile.xs pure_install

pure_install: Makefile.xs
	$(MAKE) -f Makefile.xs pure_install

install-data-local:
	$(MAKE) -f Makefile.xs pure_install

clean: 
	if test -a Makefile.xs; then $(MAKE) -f Makefile.xs clean; fi
	rm -f gendersllnl.*
	rm -f hostlist.*
	rm -f Makefile.xs
	rm -f Makefile.xs.old

EXTRA_DIST = Libgendersllnl.pm Libgendersllnl.xs Makefile.PL typemap

