##*****************************************************************************
## $Id: Makefile.am,v 1.16 2006-08-01 17:12:10 chu11 Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

# Use Perl's ExtUtils::MakeMaker to get autoconf/automake to install
# into the correct location

# DESTDIR is usually set during make install time, not configure or
# make time, so we work around it with the --with-perl-destdir
# autoconf option.

PERL_DESTDIR = @PERL_DESTDIR@

PERL_INC = "-I../../config -I$(srcdir)/../libgendersllnl"

PERL_LIBS = "-L../libgenders/.libs -lgenders"

MAKEMAKERFLAGS = INSTALLDIRS=site \
		 DESTDIR=$(PERL_DESTDIR) \
		 SITEPREFIX=$(prefix) \
		 INC=$(PERL_INC) \
		 LIBS=$(PERL_LIBS) \
		 MAKEFILE=Makefile.xs \
		 FIRST_MAKEFILE=Makefile.xs

all: Makefile.xs
	$(MAKE) -f Makefile.xs

Makefile.xs: Makefile.PL Libgendersllnl.xs Libgendersllnl.pm
# Hacks to make distcheck work
	if ! test -a Makefile.PL; then \
		cp $(srcdir)/Makefile.PL .; \
	fi
	if ! test -a typemap; then \
		cp $(srcdir)/typemap .; \
	fi
	if ! test -a Libgendersllnl.pm; then \
		cp $(srcdir)/Libgendersllnl.pm .; \
	fi
	if ! test -a Libgendersllnl.xs; then \
		cp $(srcdir)/Libgendersllnl.xs .; \
	fi
	$(PERL) Makefile.PL $(MAKEMAKERFLAGS)

test: Makefile.xs 
	$(MAKE) -f Makefile.xs test

install: Makefile.xs
	$(MAKE) -f Makefile.xs pure_install

pure_install: Makefile.xs
	$(MAKE) -f Makefile.xs pure_install

install-data-local:
	$(MAKE) -f Makefile.xs pure_install

clean: 
	if test -a Makefile.xs; then \
		$(MAKE) -f Makefile.xs clean; \
	fi
	rm -f gendersllnl.*
	rm -f hostlist.*
	rm -f Makefile.xs
	rm -f Makefile.xs.old

EXTRA_DIST = Libgendersllnl.pm Libgendersllnl.xs Makefile.PL typemap

