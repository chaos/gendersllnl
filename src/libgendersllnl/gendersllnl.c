/*****************************************************************************\
 *  $Id: gendersllnl.c,v 1.24 2005-05-07 00:10:05 achu Exp $
 *****************************************************************************
 *  Copyright (C) 2001-2003 The Regents of the University of California.
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
 *  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
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
  int ret;
  char *clustattr = GENDERS_CLUSTER_ATTRIBUTE;

  if ((ret = genders_testattr(handle, node, clustattr, buf, buflen)) < 0)
    return -1;

  if (!ret) 
    {
      /* cluster attribute not found */ 
      genders_set_errnum(handle, GENDERS_ERR_PARSE);
      return -1;
    }
  else if (ret) 
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
  int i, j, numnodes, maxvallen;
  char **temp;
 
  if ((numnodes = genders_getnumnodes(handle)) < 0)
    return -1;

  if (numnodes > 0) 
    {
      if ((maxvallen = genders_getmaxvallen(handle)) < 0)
	return -1;
      
      if (!altnodelist) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
	  return -1;
	}

      if (!(temp = (char **)malloc(sizeof(char *) * numnodes))) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
	  return -1;
	}
    
      for (i = 0; i < numnodes; i++) 
	{
	  if (!(temp[i] = (char *)malloc(maxvallen+1))) 
	    {
	      
	      for (j = 0; j < i; j++)
		free(temp[j]);
	      free(temp);
	      
	      genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
	      return -1;
	    }
	  memset(temp[i], '\0', maxvallen+1);
	}

      *altnodelist = temp;
    }

  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return numnodes;
}

int 
genders_altnodelist_clear(genders_t handle, char **altnodelist) 
{
  int i, numnodes, maxvallen;
 
  if ((numnodes = genders_getnumnodes(handle)) < 0)
    return -1;

  if (numnodes > 0) 
    {
      if ((maxvallen = genders_getmaxvallen(handle)) < 0)
	return -1;
      
      if (!altnodelist) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
	  return -1;
	}
      
      for (i = 0; i < numnodes; i++) 
	{
	  if (!altnodelist[i]) 
	    {
	      genders_set_errnum(handle, GENDERS_ERR_NULLPTR);
	      return -1;
	    }
	  memset(altnodelist[i], '\0', maxvallen + 1);
	}
    }
  
  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return 0;
}

int 
genders_altnodelist_destroy(genders_t handle, char **altnodelist) 
{
  int i, numnodes;

  if ((numnodes = genders_getnumnodes(handle)) < 0)
    return -1;

  if (numnodes > 0) 
    {
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

static int 
_getaltnodes(genders_t handle, char *altnodes[], int len,
             const char *attr, const char *val, int flag) 
{
  int i, maxvallen, maxnodelen, maxlen, nodes_len, num, ret;
  int errnum = GENDERS_ERR_SUCCESS;
  int retval = -1;
  char **nodes = NULL;
  char *buf = NULL;
  
  if ((!altnodes && len > 0) || len < 0) 
    {
      errnum = GENDERS_ERR_PARAMETERS;
      goto cleanup;
    }

  if ((nodes_len = genders_nodelist_create(handle, &nodes)) < 0)
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

  if ((num = genders_getnodes(handle, nodes, nodes_len, attr, val)) < 0)
    goto cleanup;

  if (num > len) 
    {
      errnum = GENDERS_ERR_OVERFLOW;
      goto cleanup;
    }

  for (i = 0; i < num; i++) 
    {
      memset(buf, '\0', maxlen+1);

      if (flag == ALTNAME_NO_PRESERVE)
	ret = genders_to_altname(handle, nodes[i], buf, maxlen+1);
      else 
	ret = genders_to_altname_preserve(handle, nodes[i], buf, maxlen+1);
      
      if (ret < 0)
	goto cleanup;
      
      if (!altnodes[i]) 
	{
	  errnum = GENDERS_ERR_NULLPTR;
	  goto cleanup;
	}
      strcpy(altnodes[i], buf);
    }
  
  errnum = GENDERS_ERR_SUCCESS;
  retval = num;

 cleanup:
  free(buf);
  (void)genders_nodelist_destroy(handle, nodes);
  genders_set_errnum(handle, errnum); /* must be after genders_nodelist_destroy */
  return retval;
}

int 
genders_getaltnodes(genders_t handle, char *altnodes[], int len,
                    const char *attr, const char *val) 
{
  return _getaltnodes(handle, altnodes, len, attr, val, ALTNAME_NO_PRESERVE);
}

int 
genders_getaltnodes_preserve(genders_t handle, char *altnodes[], int len,
                             const char *attr, const char *val) 
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
  int ret;

  /* must be non-NULL, b/c isnode() interprets NULL to be the current node
   */
  if (!nodename) 
    {
      genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
      return -1;
    }

  if ((ret = genders_isnode(handle, nodename)) < 0)
    return -1;

  if (!ret)
    ret = genders_isaltnode(handle, nodename);

  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return ret;
}

static int 
_to_gendname(genders_t handle, const char *altnode, char *buf, int buflen) 
{
  int maxnodelen, ret, retval = -1;
  char *nodebuf = NULL;
  char *altattr = GENDERS_ALTNAME_ATTRIBUTE;

  if (!altnode || !buf || buflen <= 0) 
    {
      genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
      goto cleanup;
    }

  if ((ret = genders_isnode(handle, altnode)) < 0)
    goto cleanup;
 
  if (ret) 
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
  
  if ((ret = genders_getnodes(handle, &nodebuf, 1, altattr, altnode)) < 0)
    goto cleanup;

  if (ret) 
    {  
      if (strlen(nodebuf) + 1 > buflen) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
	  goto cleanup;
	}
      strcpy(buf, nodebuf);
    }
  retval = ret;
  
 cleanup:
  free(nodebuf);
  return retval;
}

int 
genders_to_gendname(genders_t handle, const char *altnode, 
                    char *buf, int buflen) 
{
  int ret;

  if ((ret = _to_gendname(handle, altnode, buf, buflen)) < 0)
    return -1;

  if (!ret) 
    {
      genders_set_errnum(handle, GENDERS_ERR_NOTFOUND);
      return -1;
    }

  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return 0;
}

int 
genders_to_gendname_preserve(genders_t handle, const char *altnode, 
                             char *buf, int buflen) 
{
  int ret;

  if ((ret = _to_gendname(handle, altnode, buf, buflen)) < 0)
    return -1;

  if (!ret) 
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

static int 
_to_altname(genders_t handle, const char *node, char *buf, int buflen) 
{
  int ret, maxvallen, retval = -1;
  char *altnodebuf = NULL;
  char *altattr = GENDERS_ALTNAME_ATTRIBUTE;

  if (!node || !buf || buflen <= 0) 
    {
      genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
      goto cleanup;
    }

  if ((ret = genders_isaltnode(handle, node)) < 0)
    goto cleanup;
  
  if (ret) 
    {
      /* already an alternate name */ 
      if (strlen(node) + 1 > buflen) {
	genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
	goto cleanup;
      }
      strcpy(buf, node);
      return 1;
    }

  /* is it a legit node? */
  if ((ret = genders_isnode(handle, node)) < 0)
    goto cleanup;
  
  if (!ret)
    return 0;
  /* else ret == 1, get the altname */

  if ((maxvallen = genders_getmaxvallen(handle)) < 0)
    goto cleanup;
  
  if (!(altnodebuf = (char *)malloc(maxvallen+1))) 
    {
      genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
      goto cleanup;
    }
  memset(altnodebuf, '\0', maxvallen+1);

  if ((ret = genders_testattr(handle, node, altattr, altnodebuf, maxvallen + 1)) < 0)
    goto cleanup;
  
  /* check for possibility the attribute has no value */
  if (ret && !strlen(altnodebuf))
    ret = 0; 

  if (ret) 
    {
      if (strlen(altnodebuf) + 1 > buflen) 
	{
	  genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
	  goto cleanup;
	}
      strcpy(buf, altnodebuf);
    }
  retval = ret;

 cleanup:
  free(altnodebuf);
  return retval;
}

int 
genders_to_altname(genders_t handle, const char *node, 
                   char *buf, int buflen) 
{
  int ret;

  if ((ret = _to_altname(handle, node, buf, buflen)) < 0)
    return -1;

  if (!ret) 
    {
      genders_set_errnum(handle, GENDERS_ERR_NOTFOUND);
      return -1;
    }

  genders_set_errnum(handle, GENDERS_ERR_SUCCESS);
  return 0;
}

int 
genders_to_altname_preserve(genders_t handle, const char *node, 
                            char *buf, int buflen) 
{
  int ret;

  if ((ret = _to_altname(handle, node, buf, buflen)) < 0)
    return -1;

  if (!ret) 
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

static int 
_string_to(genders_t handle, const char *str, char *buf, int buflen, int flag) 
{
  int maxvallen, maxnodelen, maxlen, ret = -1, retval = -1;
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
      
      if (flag == GENDNAME_NO_PRESERVE)
	ret = genders_to_gendname(handle, node, strbuf, maxlen+1);
      else if (flag == GENDNAME_PRESERVE)
	ret = genders_to_gendname_preserve(handle, node, strbuf, maxlen+1);
      else if (flag == ALTNAME_NO_PRESERVE)
	ret = genders_to_altname(handle, node, strbuf, maxlen+1);
      else if (flag == ALTNAME_PRESERVE)
	ret = genders_to_altname_preserve(handle, node, strbuf, maxlen+1);
      
      if (ret < 0)
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
  retval = 0;

 cleanup:
  hostlist_iterator_destroy(iter);
  hostlist_destroy(src);
  hostlist_destroy(dest);
  free(strbuf);
  free(node);
  return retval;
}

int 
genders_string_to_gendnames(genders_t handle, const char *str, 
                            char *buf, int buflen) 
{
  return _string_to(handle, str, buf, buflen, GENDNAME_NO_PRESERVE);
}

int 
genders_string_to_gendnames_preserve(genders_t handle, const char *str,
                                     char *buf, int buflen) 
{
  return _string_to(handle, str, buf, buflen, GENDNAME_PRESERVE);
}

int 
genders_string_to_altnames(genders_t handle, const char *str,
                           char *buf, int buflen) 
{
  return _string_to(handle, str, buf, buflen, ALTNAME_NO_PRESERVE);
}

int 
genders_string_to_altnames_preserve(genders_t handle, const char *str,
                                    char *buf, int buflen) 
{
  return _string_to(handle, str, buf, buflen, ALTNAME_PRESERVE);
}
