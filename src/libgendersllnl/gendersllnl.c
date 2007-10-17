/*****************************************************************************\
 *  $Id: gendersllnl.c,v 1.28 2007-10-17 18:09:15 chu11 Exp $
 *****************************************************************************
 *  Copyright (C) 2001-2007 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Jim Garlick <garlick@llnl.gov> and Albert Chu <chu11@llnl.gov>.
 *  UCRL-CODE-2003-004.
 *
 *  This file is part of Gendersllnl, a cluster configuration database
 *  and rdist preprocessor for LLNL site specific needs.  This package
 *  was originally a part of the Genders package, but has now been
 *  split off into a separate package.  For details, see
 *  <http://www.llnl.gov/linux/genders/>.
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
 *  with Gendersllnl; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
\*****************************************************************************/

#if HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdlib.h>
#include <stdio.h>
#if STDC_HEADERS
#include <string.h>
#endif /* STDC_HEADERS */

#include "gendersllnl.h"
#include "hostlist.h"

#define GENDNAME_NO_PRESERVE   0
#define GENDNAME_PRESERVE      1
#define ALTNAME_NO_PRESERVE    2
#define ALTNAME_PRESERVE       3

int 
genders_get_cluster(genders_t handle, const char *node, char *buf, int buflen)
{
  int rv;

  if ((rv = genders_testattr(handle, 
			     node, 
			     GENDERS_CLUSTER_ATTRIBUTE, 
			     buf, 
			     buflen)) < 0)
    return -1;

  if (!rv) 
    {
      /* cluster attribute not found */ 
      genders_set_errnum(handle, GENDERS_ERR_PARSE);
      return -1;
    }
  else if (rv) 
    {
      genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
      return 0;
    }

  /* NOT REACHED */
  return 0;
}

int 
genders_altnodelist_create(genders_t handle, char ***altnodelist) 
{
  int numnodes;
 
  if ((numnodes = genders_getnumnodes(handle)) < 0)
    return -1;

  if (numnodes > 0) 
    {
      int i, j, maxnodelen, maxvallen, maxlen;
      char **nodelist;

      if (!altnodelist) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
	  return -1;
	}

      if ((maxnodelen = genders_getmaxnodelen(handle)) < 0)
	return -1;

      if ((maxvallen = genders_getmaxvallen(handle)) < 0)
	return -1;
      
      maxlen = (maxnodelen > maxvallen) ? maxnodelen : maxvallen;

      if (!(nodelist = (char **)malloc(sizeof(char *) * numnodes))) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
	  return -1;
	}
    
      for (i = 0; i < numnodes; i++) 
	{
	  if (!(nodelist[i] = (char *)malloc(maxlen+1))) 
	    {
	      
	      for (j = 0; j < i; j++)
		free(nodelist[j]);
	      free(nodelist);
	      
	      genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
	      return -1;
	    }
	  memset(nodelist[i], '\0', maxlen+1);
	}

      *altnodelist = nodelist;
    }

  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return numnodes;
}

int 
genders_altnodelist_clear(genders_t handle, char **altnodelist) 
{
  int numnodes;
 
  if ((numnodes = genders_getnumnodes(handle)) < 0)
    return -1;

  if (numnodes > 0) 
    {
      int i, maxnodelen, maxvallen, maxlen;

      if (!altnodelist) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
	  return -1;
	}

      if ((maxnodelen = genders_getmaxnodelen(handle)) < 0)
	return -1;

      if ((maxvallen = genders_getmaxvallen(handle)) < 0)
	return -1;

      maxlen = (maxnodelen > maxvallen) ? maxnodelen : maxvallen;
     
      for (i = 0; i < numnodes; i++) 
	{
	  if (!altnodelist[i]) 
	    {
	      genders_set_errnum(handle, GENDERS_ERR_NULLPTR);
	      return -1;
	    }
	  memset(altnodelist[i], '\0', maxlen + 1);
	}
    }
  
  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return 0;
}

int 
genders_altnodelist_destroy(genders_t handle, char **altnodelist) 
{
  int numnodes;

  if ((numnodes = genders_getnumnodes(handle)) < 0)
    return -1;

  if (numnodes > 0) 
    {
      int i;

      if (!altnodelist) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
	  return -1;
	}
      
      for (i = 0; i < numnodes; i++)
	free(altnodelist[i]);
      free(altnodelist);
    }
  
  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return 0;
}

/* 
 * _getaltnodes
 *
 * Common function for genders_getaltnodes and
 * genders_getaltnodes_preserve.
 */
static int 
_getaltnodes(genders_t handle, 
	     char *altnodes[], 
	     int len,
             const char *attr, 
	     const char *val, 
	     int preserve_flag) 
{
  int i, maxvallen, maxnodelen, maxlen, nodeslen, numnodes, rv = -1;
  int errnum = GENDERS_ERR_SUCCESS;
  char **nodes = NULL;
  char *buf = NULL;
  
  if ((!altnodes && len > 0) || len < 0) 
    {
      errnum = GENDERS_ERR_PARAMETERS;
      goto cleanup;
    }

  if ((nodeslen = genders_nodelist_create(handle, &nodes)) < 0)
    goto cleanup;
  
  if ((maxvallen = genders_getmaxvallen(handle)) < 0)
    goto cleanup;

  if ((maxnodelen = genders_getmaxnodelen(handle)) < 0)
    goto cleanup;

  /* to protect against possible overflow on 'to_altname_preserve' */
  maxlen = (maxnodelen > maxvallen) ? maxnodelen : maxvallen;
  
  if (!(buf = (char *)malloc(maxlen+1))) 
    {
      errnum = GENDERS_ERR_OUTMEM;
      goto cleanup;
    }

  if ((numnodes = genders_getnodes(handle, nodes, nodeslen, attr, val)) < 0)
    goto cleanup;

  if (numnodes > len) 
    {
      errnum = GENDERS_ERR_OVERFLOW;
      goto cleanup;
    }

  for (i = 0; i < numnodes; i++) 
    {
      int temp;

      memset(buf, '\0', maxlen+1);

      if (preserve_flag == ALTNAME_NO_PRESERVE)
	temp = genders_to_altname(handle, nodes[i], buf, maxlen+1);
      else 
	temp = genders_to_altname_preserve(handle, nodes[i], buf, maxlen+1);
      
      if (temp < 0)
	goto cleanup;
      
      if (!altnodes[i]) 
	{
	  errnum = GENDERS_ERR_NULLPTR;
	  goto cleanup;
	}
      strcpy(altnodes[i], buf);
    }
  
  errnum = GENDERS_ERR_SUCCESS;
  rv = numnodes;

 cleanup:
  free(buf);
  (void)genders_nodelist_destroy(handle, nodes);
  genders_set_errnum(handle, errnum); /* must be after genders_nodelist_destroy */
  return rv;
}

int 
genders_getaltnodes(genders_t handle, 
		    char *altnodes[], 
		    int len,
                    const char *attr, 
		    const char *val) 
{
  return _getaltnodes(handle, altnodes, len, attr, val, ALTNAME_NO_PRESERVE);
}

int 
genders_getaltnodes_preserve(genders_t handle, 
			     char *altnodes[], 
			     int len,
                             const char *attr, 
			     const char *val) 
{
  return _getaltnodes(handle, altnodes, len, attr, val, ALTNAME_PRESERVE);
}

int 
genders_isaltnode(genders_t handle, const char *altnode) 
{
  return genders_isattrval(handle, GENDERS_ALTNAME_ATTRIBUTE, altnode);
}

int 
genders_isnode_or_altnode(genders_t handle, const char *nodename) 
{
  int rv;

  /* 
   * Must be non-NULL, b/c isnode() interprets NULL to be the current
   * node
   */
  if (!nodename) 
    {
      genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
      return -1;
    }

  if ((rv = genders_isnode(handle, nodename)) < 0)
    return -1;

  if (!rv)
    rv = genders_isaltnode(handle, nodename);

  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return rv;
}

/* 
 * _to_gendname
 *
 * Common function for genders_to_gendname and
 * genders_to_gendname_preserve.
 * 
 * Returns 1 if gendname returned, 0 if not, -1 on error
 */
static int 
_to_gendname(genders_t handle, const char *altnode, char *buf, int buflen) 
{
  int maxnodelen, flag, rv = -1;
  char *nodebuf = NULL;

  if (!altnode || !buf || buflen <= 0) 
    {
      genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
      goto cleanup;
    }

  if ((flag = genders_isnode(handle, altnode)) < 0)
    goto cleanup;
 
  if (flag) 
    {
      /* already a gendname */
      if (strlen(altnode) + 1 > buflen) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
	  goto cleanup;
	}
      strcpy(buf, altnode);
      return 1;
    }

  if ((maxnodelen = genders_getmaxnodelen(handle)) < 0)
    goto cleanup;
  
  if (!(nodebuf = (char *)malloc(maxnodelen+1))) 
    {
      genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
      goto cleanup;
    }
  memset(nodebuf, '\0', maxnodelen+1);
  
  if ((flag = genders_getnodes(handle, 
			       &nodebuf, 
			       1, 
			       GENDERS_ALTNAME_ATTRIBUTE, 
			       altnode)) < 0)
    goto cleanup;

  if (flag) 
    {  
      if (strlen(nodebuf) + 1 > buflen) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
	  goto cleanup;
	}
      strcpy(buf, nodebuf);
    }
  rv = flag;
  
 cleanup:
  free(nodebuf);
  return rv;
}

int 
genders_to_gendname(genders_t handle, 
		    const char *altnode, 
                    char *buf, 
		    int buflen) 
{
  int rv;
  
  if ((rv = _to_gendname(handle, altnode, buf, buflen)) < 0)
    return -1;
  
  if (!rv) 
    {
      genders_set_errnum(handle, GENDERS_ERR_NOTFOUND);
      return -1;
    }

  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return 0;
}

int 
genders_to_gendname_preserve(genders_t handle, 
			     const char *altnode, 
                             char *buf, 
			     int buflen) 
{
  int rv;

  if ((rv = _to_gendname(handle, altnode, buf, buflen)) < 0)
    return -1;

  if (!rv) 
    {
      if (strlen(altnode) + 1 > buflen) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
	  return -1;
	}
      strcpy(buf, altnode);
    }
  
  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return 0;
}

/* 
 * _to_altname
 *
 * Common function for genders_to_altname and
 * genders_to_altname_preserve.
 * 
 * Returns 1 if altname returned, 0 if not, -1 on error
 */
static int 
_to_altname(genders_t handle, const char *node, char *buf, int buflen) 
{
  int flag, maxvallen, rv = -1;
  char *altnodebuf = NULL;

  if (!node || !buf || buflen <= 0) 
    {
      genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
      goto cleanup;
    }

  if ((flag = genders_isaltnode(handle, node)) < 0)
    goto cleanup;
  
  if (flag) 
    {
      /* already an alternate name */ 
      if (strlen(node) + 1 > buflen) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
	  goto cleanup;
	}
      strcpy(buf, node);
      return 1;
    }

  /* is it a legit node? */
  if ((flag = genders_isnode(handle, node)) < 0)
    goto cleanup;
  
  if (!flag)
    return 0;
  /* else flag == 1, get the altname */

  if ((maxvallen = genders_getmaxvallen(handle)) < 0)
    goto cleanup;
  
  if (!(altnodebuf = (char *)malloc(maxvallen+1))) 
    {
      genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
      goto cleanup;
    }
  memset(altnodebuf, '\0', maxvallen+1);

  if ((flag = genders_testattr(handle, 
			       node, 
			       GENDERS_ALTNAME_ATTRIBUTE, 
			       altnodebuf, 
			       maxvallen + 1)) < 0)
    goto cleanup;
  
  /* check for possibility the attribute has no value */
  if (flag && !strlen(altnodebuf))
    flag = 0; 

  if (flag) 
    {
      if (strlen(altnodebuf) + 1 > buflen) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
	  goto cleanup;
	}
      strcpy(buf, altnodebuf);
    }
  rv = flag;

 cleanup:
  free(altnodebuf);
  return rv;
}

int 
genders_to_altname(genders_t handle, 
		   const char *node, 
                   char *buf, 
		   int buflen) 
{
  int rv;

  if ((rv = _to_altname(handle, node, buf, buflen)) < 0)
    return -1;

  if (!rv) 
    {
      genders_set_errnum(handle, GENDERS_ERR_NOTFOUND);
      return -1;
    }

  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return 0;
}

int 
genders_to_altname_preserve(genders_t handle, 
			    const char *node, 
                            char *buf, 
			    int buflen) 
{
  int rv;

  if ((rv = _to_altname(handle, node, buf, buflen)) < 0)
    return -1;

  if (!rv) 
    {
      if (strlen(node) + 1 > buflen) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
	  return -1;
	}
      strcpy(buf, node);
    }
  
  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return 0;
}

/* 
 * _string_to
 *
 * Common function for genders_string_to_gendnames,
 * genders_string_to_gendnames_preserve, genders_string_to_altnames,
 * genders_string_to_altnames_preserve
 * 
 * Returns 0 on success, -1 on error
 */
static int 
_string_to(genders_t handle,
	   const char *str, 
	   char *buf, 
	   int buflen, 
	   int preserve_flag) 
{
  int maxvallen, maxnodelen, maxlen, rv = -1;
  char *node = NULL;
  char *strbuf = NULL;
  hostlist_t src = NULL;
  hostlist_t dest = NULL;
  hostlist_iterator_t iter = NULL;

  if (!str || !buf || buflen <= 0) 
    {
      genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
      goto cleanup;
    }

  if ((maxvallen = genders_getmaxvallen(handle)) < 0)
    goto cleanup;

  if ((maxnodelen = genders_getmaxnodelen(handle)) < 0)
    goto cleanup;

  /* to protect against possible overflow on 'to_altname_preserve' */
  maxlen = (maxnodelen > maxvallen) ? maxnodelen : maxvallen;

  if (!(strbuf = (char *)malloc(maxlen+1))) 
    {
      genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
      goto cleanup;
    }

  if (!(src = hostlist_create(str))) 
    {
      genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
      goto cleanup;
    }

  if (!(dest = hostlist_create(NULL))) 
    {
      genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
      goto cleanup;
    }

  if (!(iter = hostlist_iterator_create(src))) 
    {
      genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
      goto cleanup;
    }

  while ((node = hostlist_next(iter))) 
    {
      int temp;

      /* realloc b/c of potential buf overflow */ 
      if (strlen(node) > maxlen) 
	{
	  maxlen = strlen(node);
	  if (!(strbuf = (char *)realloc(strbuf, maxlen+1))) 
	    {
	      genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
	      goto cleanup;
	    }
	}
      memset(strbuf, '\0', maxlen+1);
      
      if (preserve_flag == GENDNAME_NO_PRESERVE)
	temp = genders_to_gendname(handle, node, strbuf, maxlen+1);
      else if (preserve_flag == GENDNAME_PRESERVE)
	temp = genders_to_gendname_preserve(handle, node, strbuf, maxlen+1);
      else if (preserve_flag == ALTNAME_NO_PRESERVE)
	temp = genders_to_altname(handle, node, strbuf, maxlen+1);
      else
	temp = genders_to_altname_preserve(handle, node, strbuf, maxlen+1);
      
      if (temp < 0)
	goto cleanup;

      if (!hostlist_push_host(dest, strbuf)) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_INTERNAL);
	  goto cleanup;
	}
      
      free(node);
    }
  node = NULL;
  
  hostlist_sort(dest);

  if (hostlist_ranged_string(dest, buflen, buf) < 0) 
    {
      genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
      goto cleanup;
    }  
  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  rv = 0;

 cleanup:
  hostlist_iterator_destroy(iter);
  hostlist_destroy(src);
  hostlist_destroy(dest);
  free(strbuf);
  free(node);
  return rv;
}

int 
genders_string_to_gendnames(genders_t handle, 
			    const char *str, 
                            char *buf, 
			    int buflen) 
{
  return _string_to(handle, str, buf, buflen, GENDNAME_NO_PRESERVE);
}

int 
genders_string_to_gendnames_preserve(genders_t handle, 
				     const char *str,
                                     char *buf, 
				     int buflen) 
{
  return _string_to(handle, str, buf, buflen, GENDNAME_PRESERVE);
}

int 
genders_string_to_altnames(genders_t handle, 
			   const char *str,
                           char *buf, 
			   int buflen) 
{
  return _string_to(handle, str, buf, buflen, ALTNAME_NO_PRESERVE);
}

int 
genders_string_to_altnames_preserve(genders_t handle, 
				    const char *str,
                                    char *buf, 
				    int buflen) 
{
  return _string_to(handle, str, buf, buflen, ALTNAME_PRESERVE);
}
