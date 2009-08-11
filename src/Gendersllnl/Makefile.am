##*****************************************************************************
## $Id: Makefile.am,v 1.24 2009-08-11 17:07:09 chu11 Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

INSTALLSITEARCH=`$(PERL) -e 'use Config; $$T=$$Config{installsitearch}; print $$T;'`
 
if WITH_PERL_EXTENSIONS
GENDERSLLNLPMFILES = Gendersllnl.pm
GENDERSLLNLPMFILESdir = $(INSTALLSITEARCH)
GENDERSLLNLPMFILES_DATA = $(GENDERSLLNLPMFILES)
 
Gendersllnl.$(PERLMAN3EXT):
# Hacks to make distcheck work
	if ! test -a Gendersllnl.pm; then \
		cp $(srcdir)/Gendersllnl.pm .; \
	fi
	$(POD2MAN) Gendersllnl.pm Gendersllnl.$(PERLMAN3EXT)
 
man3_MANS = Gendersllnl.$(PERLMAN3EXT)
 
install-data-hook:
	chmod 444 $(DESTDIR)/$(INSTALLSITEARCH)/Gendersllnl.pm
endif
 
EXTRA_DIST = Gendersllnl.pm
