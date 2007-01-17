##*****************************************************************************
## $Id: Makefile.am,v 1.18 2007-01-17 00:52:10 chu11 Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

# Use Perl's ExtUtils::MakeMaker to get autoconf/automake to install
# into the correct location

# DESTDIR is usually set during make install time, not configure or
# make time, so we work around it with the --with-perl-destdir
# autoconf option.

PERL_DESTDIR = @PERL_DESTDIR@

PERL_INC = "-I../../config -I$(srcdir)/../libgendersllnl @GENDERS_INCLUDEDIR@"

PERL_LIBS = "-L../libgendersllnl/.libs -lgendersllnl @GENDERS_LIBDIR@ -lgenders"

MAKEMAKERFLAGS = INSTALLDIRS=site \
		 DESTDIR=$(PERL_DESTDIR) \
		 SITEPREFIX=$(prefix) \
		 INSTALLSITEMAN3DIR=$(mandir)/man3 \
		 INC=$(PERL_INC) \
		 LIBS=$(PERL_LIBS) \
		 GENDERSLLNL_LIBDIRS=$(libdir):@GENDERS_LIBDIR@ \
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

