##*****************************************************************************
## $Id: Makefile.am,v 1.21 2005-05-14 05:00:22 achu Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

INSTALLSITEARCH=`perl -e 'use Config; $$T=$$Config{installsitearch}; $$T=~/\/usr\/(lib|lib64)\/(.*)/; print $$2;'`
 
GENDERSLLNLPMFILES = Gendersllnl.pm
GENDERSLLNLPMFILESdir = $(libdir)/$(INSTALLSITEARCH)
GENDERSLLNLPMFILES_DATA = $(GENDERSLLNLPMFILES)
 
Gendersllnl.3pm:
# Hacks to make distcheck work
	if ! test -a Gendersllnl.pm; then \
		cp $(srcdir)/Gendersllnl.pm .; \
	fi
	$(POD2MAN) Gendersllnl.pm Gendersllnl.3pm
 
man3_MANS = Gendersllnl.3pm
 
install-data-hook:
	chmod 444 $(DESTDIR)/$(libdir)/$(INSTALLSITEARCH)/Gendersllnl.pm
 
EXTRA_DIST = Gendersllnl.pm
