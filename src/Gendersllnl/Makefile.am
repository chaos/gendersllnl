##*****************************************************************************
## $Id: Makefile.am,v 1.20 2005-05-14 03:04:39 achu Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

INSTALLSITEARCH=`perl -e 'use Config; $$T=$$Config{installsitearch}; $$T=~/\/usr\/(lib|lib64)\/(.*)/; print $$2;'`
 
GENDERSLLNLPMFILES = Gendersllnl.pm
GENDERSLLNLPMFILESdir = $(libdir)/$(INSTALLSITEARCH)
GENDERSLLNLPMFILES_DATA = $(GENDERSLLNLPMFILES)
 
Gendersllnl.3pm:
	$(POD2MAN) Gendersllnl.pm Gendersllnl.3pm
 
man3_MANS = Gendersllnl.3pm
 
install-data-hook:
	chmod 444 $(DESTDIR)/$(libdir)/$(INSTALLSITEARCH)/Gendersllnl.pm
 
EXTRA_DIST = Gendersllnl.pm
