#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include <string.h>

#include <genders.h>
#include "gendersllnl.h"

MODULE = Libgendersllnl		PACKAGE = Libgendersllnl		

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
        if ((maxvallen = genders_getmaxvallen(handle)) == -1) 
            goto handle_error;

        if ((buf = (char *)malloc(maxvallen+1)) == NULL) 
            goto handle_error;

        memset(buf, '\0', maxvallen+1);

        if (genders_get_cluster(handle, node, buf, maxvallen + 1) == -1)
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
        int num, ret, i;
        char **altnodelist = NULL;
    CODE:
        if ((num = genders_altnodelist_create(handle, &altnodelist)) == -1)
            goto handle_error;

        if ((ret = genders_getaltnodes(handle,
                                       altnodelist,
                                       num,
                                       attr,
                                       val)) == -1)
            goto handle_error;

        RETVAL = newAV();
        for (i = 0; i < ret; i++)
            av_push(RETVAL, newSVpv(altnodelist[i], 0));

        (void)genders_altnodelist_destroy(handle, altnodelist);
        goto the_end;

        handle_error:
            /* manually destroy lists, to preserve error value */
            if (altnodelist != NULL) {
                for (i = 0; i < num; i++)
                    free(altnodelist[i]);
                free(altnodelist);
            }

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
        int num, ret, i;
        char **altnodelist = NULL;
    CODE:
        if ((num = genders_altnodelist_create(handle, &altnodelist)) == -1)
            goto handle_error;

        if ((ret = genders_getaltnodes_preserve(handle,
                                                altnodelist,
                                                num,
                                                attr,
                                                val)) == -1)
            goto handle_error;

        RETVAL = newAV();
        for (i = 0; i < ret; i++)
            av_push(RETVAL, newSVpv(altnodelist[i], 0));

        (void)genders_altnodelist_destroy(handle, altnodelist);
        goto the_end;

        handle_error:
            /* manually destroy lists, to preserve error value */
            if (altnodelist != NULL) {
                for (i = 0; i < num; i++)
                    free(altnodelist[i]);
                free(altnodelist);
            }

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
        if ((maxnodelen = genders_getmaxnodelen(handle)) == -1)
            goto handle_error;

        if ((buf = (char *)malloc(maxnodelen+1)) == NULL)
            goto handle_error;

        memset(buf, '\0', maxnodelen+1);

        if (genders_to_gendname(handle, altnode, buf, maxnodelen + 1) == -1)
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
        if ((maxnodelen = genders_getmaxnodelen(handle)) == -1)
            goto handle_error;

        if (altnode != NULL && strlen(altnode) > maxnodelen)
            maxnodelen = strlen(altnode);

        if ((buf = (char *)malloc(maxnodelen+1)) == NULL)
            goto handle_error;

        memset(buf, '\0', maxnodelen+1);

        if (genders_to_gendname_preserve(handle, 
                                         altnode, 
                                         buf, 
                                         maxnodelen + 1) == -1)
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
        if ((maxvallen = genders_getmaxvallen(handle)) == -1)
            goto handle_error;

        if ((buf = (char *)malloc(maxvallen+1)) == NULL)
            goto handle_error;

        memset(buf, '\0', maxvallen+1);

        if (genders_to_altname(handle, node, buf, maxvallen + 1) == -1)
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
        if ((maxvallen = genders_getmaxvallen(handle)) == -1)
            goto handle_error;

        if (node != NULL && strlen(node) > maxvallen)
            maxvallen = strlen(node);

        if ((buf = (char *)malloc(maxvallen+1)) == NULL)
            goto handle_error;

        memset(buf, '\0', maxvallen+1);

        if (genders_to_altname_preserve(handle, 
                                        node,
                                        buf,
                                        maxvallen + 1) == -1)
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
