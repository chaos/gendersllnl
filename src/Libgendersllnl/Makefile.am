##*****************************************************************************
## $Id: Makefile.am,v 1.2 2003-05-14 01:06:40 achu Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

# This is a hack to get autoconf, automake, and ExtUtils::MakeMaker
# to work together.  
#
# Currently, it only supports the common MakeMaker options of
#
# make install
# make pure_install
# make test

XS_PREFIX = @XS_PREFIX@

all: Makefile.xs
	$(MAKE) -f Makefile.xs

Makefile.xs: Makefile.PL Libgendersllnl.xs Libgendersllnl.pm
	cp ../libgendersllnl/gendersllnl.c .
	cp ../libgendersllnl/gendersllnl.h .
	cp ../libgendersllnl/hostlist.c .
	cp ../libgendersllnl/hostlist.h .
	$(PERL) Makefile.PL PREFIX=$(XS_PREFIX) MAKEFILE=Makefile.xs FIRST_MAKEFILE=Makefile.xs

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



