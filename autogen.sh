#!/bin/sh
##
# $Id: autogen.sh,v 1.1 2005-04-19 23:53:52 achu Exp $
##

PATH=/bin:/usr/bin:/usr/local/bin

set -x
aclocal -I config || exit 1
libtoolize --copy || exit 1
autoheader || exit 1
automake --add-missing --copy --gnu || exit 1
autoconf --warnings=all || exit 1
exit 0
