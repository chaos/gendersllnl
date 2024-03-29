/*****************************************************************************\
 *  $Id: Libgendersllnl.xs,v 1.12 2007-10-17 18:45:32 chu11 Exp $
 *****************************************************************************
 *  Copyright (C) 2007-2015 Lawrence Livermore National Security, LLC.
 *  Copyright (C) 2001-2007 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Jim Garlick <garlick@llnl.gov> and Albert Chu <chu11@llnl.gov>.
 *  UCRL-CODE-2003-004.
 *
 *  This file is part of Gendersllnl, a cluster configuration database
 *  and rdist preprocessor for LLNL site specific needs.  This package
 *  was originally a part of the Genders package, but has now been
 *  split off into a separate package.  For details, see
 *  <https://github.com/chaos/gendersllnl>.
 *
 *  Gendersllnl is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of the
 *  License, or (at your option) any later version.
 *
 *  Gendersllnl is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more information.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Gendersllnl.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include <string.h>

#include <genders.h>
#include "gendersllnl.h"

MODULE = Libgendersllnl         PACKAGE = Libgendersllnl

PROTOTYPES: ENABLE

SV *
GENDERS_ALTNAME_ATTRIBUTE (sv=&PL_sv_undef)
    SV *sv
    CODE:
        RETVAL = newSVpv(GENDERS_ALTNAME_ATTRIBUTE, 0);
    OUTPUT:
        RETVAL

SV *
GENDERS_CLUSTER_ATTRIBUTE (sv=&PL_sv_undef)
    SV *sv
    CODE:
        RETVAL = newSVpv(GENDERS_CLUSTER_ATTRIBUTE, 0);
    OUTPUT:
        RETVAL

SV *
GENDERS_ALL_ATTRIBUTE (sv=&PL_sv_undef)
    SV *sv
    CODE:
        RETVAL = newSVpv(GENDERS_ALL_ATTRIBUTE, 0);
    OUTPUT:
        RETVAL

SV *
genders_get_cluster (handle, node=NULL)
    genders_t handle
    char *node
    PREINIT:
        int maxvallen;
        char *buf = NULL;
    CODE:
        if ((maxvallen = genders_getmaxvallen(handle)) < 0)
            goto handle_error;

        if (!(buf = (char *)malloc(maxvallen+1)))
            goto handle_error;

        memset(buf, '\0', maxvallen+1);

        if (genders_get_cluster(handle, node, buf, maxvallen + 1) < 0)
            goto handle_error;

        RETVAL = newSVpv(buf, 0);
        free(buf);
        goto the_end;

        handle_error:

            free(buf);
            XSRETURN_UNDEF;

        the_end:
    OUTPUT:
        RETVAL

AV *
genders_getaltnodes (handle, attr=NULL, val=NULL)
    genders_t handle
    char *attr
    char *val
    PREINIT:
        int len, num, errnum, i;
        char **altlist = NULL;
    CODE:
        if ((len = genders_altnodelist_create(handle, &altlist)) < 0)
            goto handle_error;

        if ((num = genders_getaltnodes(handle, altlist, len, attr, val)) < 0)
            goto handle_error;

        RETVAL = newAV();
        for (i = 0; i < num; i++)
            av_push(RETVAL, newSVpv(altlist[i], 0));

        if (genders_altnodelist_destroy(handle, altlist) < 0)
            goto handle_error;

        goto the_end;

        handle_error:

            errnum = genders_errnum(handle);

            (void)genders_altnodelist_destroy(handle, altlist);

            genders_set_errnum(handle, errnum);

            XSRETURN_UNDEF;

        the_end:
    OUTPUT:
        RETVAL

AV *
genders_getaltnodes_preserve (handle, attr=NULL, val=NULL)
    genders_t handle
    char *attr
    char *val
    PREINIT:
        int len, num, errnum, i;
        char **altlist = NULL;
    CODE:
        if ((len = genders_altnodelist_create(handle, &altlist)) < 0)
            goto handle_error;

        if ((num = genders_getaltnodes_preserve(handle,
                                                altlist,
                                                len,
                                                attr,
                                                val)) < 0)
            goto handle_error;

        RETVAL = newAV();
        for (i = 0; i < num; i++)
            av_push(RETVAL, newSVpv(altlist[i], 0));

        if (genders_altnodelist_destroy(handle, altlist) < 0)
            goto handle_error;

        goto the_end;

        handle_error:

            errnum = genders_errnum(handle);

            (void)genders_altnodelist_destroy(handle, altlist);

            genders_set_errnum(handle, errnum);

            XSRETURN_UNDEF;

        the_end:
    OUTPUT:
        RETVAL

int
genders_isaltnode (handle, altnode)
    genders_t handle
    char *altnode
    CODE:
        RETVAL = genders_isaltnode(handle, altnode);
    OUTPUT:
        RETVAL

int
genders_isnode_or_altnode (handle, nodename)
    genders_t handle
    char *nodename
    CODE:
        RETVAL = genders_isnode_or_altnode(handle, nodename);
    OUTPUT:
        RETVAL

SV *
genders_to_gendname (handle, altnode)
    genders_t handle
    char *altnode
    PREINIT:
        int maxnodelen;
        char *buf = NULL;
    CODE:
        if ((maxnodelen = genders_getmaxnodelen(handle)) < 0)
            goto handle_error;

        if (!(buf = (char *)malloc(maxnodelen+1)))
            goto handle_error;

        memset(buf, '\0', maxnodelen+1);

        if (genders_to_gendname(handle, altnode, buf, maxnodelen + 1) < 0)
            goto handle_error;

        RETVAL = newSVpv(buf, 0);
        free(buf);
        goto the_end;

        handle_error:

            free(buf);
            XSRETURN_UNDEF;

        the_end:
    OUTPUT:
        RETVAL

SV *
genders_to_gendname_preserve (handle, altnode)
    genders_t handle
    char *altnode
    PREINIT:
        int maxnodelen;
        char *buf = NULL;
    CODE:
        if ((maxnodelen = genders_getmaxnodelen(handle)) < 0)
            goto handle_error;

        if (altnode != NULL && strlen(altnode) > maxnodelen)
            maxnodelen = strlen(altnode);

        if (!(buf = (char *)malloc(maxnodelen+1)))
            goto handle_error;

        memset(buf, '\0', maxnodelen+1);

        if (genders_to_gendname_preserve(handle,
                                         altnode,
                                         buf,
                                         maxnodelen + 1) < 0)
            goto handle_error;

        RETVAL = newSVpv(buf, 0);
        free(buf);
        goto the_end;

        handle_error:

            free(buf);
            XSRETURN_UNDEF;

        the_end:
    OUTPUT:
        RETVAL


SV *
genders_to_altname (handle, node)
    genders_t handle
    char *node
    PREINIT:
        int maxvallen;
        char *buf = NULL;
    CODE:
        if ((maxvallen = genders_getmaxvallen(handle)) < 0)
            goto handle_error;

        if (!(buf = (char *)malloc(maxvallen+1)))
            goto handle_error;

        memset(buf, '\0', maxvallen+1);

        if (genders_to_altname(handle, node, buf, maxvallen + 1) < 0)
            goto handle_error;

        RETVAL = newSVpv(buf, 0);
        free(buf);
        goto the_end;

        handle_error:

            free(buf);
            XSRETURN_UNDEF;

        the_end:
    OUTPUT:
        RETVAL

SV *
genders_to_altname_preserve (handle, node)
    genders_t handle
    char *node
    PREINIT:
        int maxvallen;
        char *buf = NULL;
    CODE:
        if ((maxvallen = genders_getmaxvallen(handle)) < 0)
            goto handle_error;

        if (node != NULL && strlen(node) > maxvallen)
            maxvallen = strlen(node);

        if (!(buf = (char *)malloc(maxvallen+1)))
            goto handle_error;

        memset(buf, '\0', maxvallen+1);

        if (genders_to_altname_preserve(handle,
                                        node,
                                        buf,
                                        maxvallen + 1) < 0)
            goto handle_error;

        RETVAL = newSVpv(buf, 0);
        free(buf);
        goto the_end;

        handle_error:

            free(buf);
            XSRETURN_UNDEF;

        the_end:
    OUTPUT:
        RETVAL
