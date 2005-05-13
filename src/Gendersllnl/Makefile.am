##*****************************************************************************
## $Id: Makefile.am,v 1.16 2005-05-13 23:11:05 achu Exp $
##*****************************************************************************
## Process this file with automake to produce Makefile.in.
##*****************************************************************************

INSTALLSITEARCH=`perl -e 'use Config; $$T=$$Config{installsitearch}; $$T=~/\/usr\/lib(.*)/; print $$1;'`
 
GENDERSPMFILES = Gendersllnl.pm
GENDERSPMFILESdir = $(libdir)/$(INSTALLSITEARCH)
GENDERSPMFILES_DATA = $(GENDERSPMFILES)
 
Gendersllnl.3pm:
	$(POD2MAN) Gendersllnl.pm Gendersllnl.3pm
 
man3_MANS = Gendersllnl.3pm
 
install-data-hook:
	chmod 444 $(DESTDIR)/$(libdir)/$(INSTALLSITEARCH)/Gendersllnl.pm
 
EXTRA_DIST = Gendersllnl.pm
