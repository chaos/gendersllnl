/*
 * $Id: gendersllnl.c,v 1.1.1.1 2003-05-13 01:20:50 achu Exp $
 * $Source: /g/g0/achu/temp/genders-cvsbackup-full/gendersllnl/src/libgendersllnl/gendersllnl.c,v $
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gendersllnl.h"
#include "hostlist.h"

#define GENDERSLLNL_BUFFERLEN             65536

#define GENDERSLLNL_GENDNAME_NOPRESERVE   0
#define GENDERSLLNL_GENDNAME_PRESERVE     1
#define GENDERSLLNL_ALTNAME_NOPRESERVE    2
#define GENDERSLLNL_ALTNAME_PRESERVE      3

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 64
#endif

int genders_get_cluster(genders_t handle,
                        const char *node,
                        char *buf,
                        int buflen) {
  int ret;

  ret = genders_testattr(handle, 
                         node, 
                         GENDERS_CLUSTER_ATTRIBUTE,
                         buf,
                         buflen);

  if (ret == 1)
    ret = 0;

  return ret;
}

int genders_altnodelist_create(genders_t handle, char ***altnodelist) {
  int i, j, numnodes, maxvallen;
  char **temp;
 
  if ((numnodes = genders_getnumnodes(handle)) == -1)
    return -1;

  if ((maxvallen = genders_getmaxvallen(handle)) == -1)
    return -1;

  if (numnodes > 0) {
    temp = (char **)malloc(sizeof(char *) * numnodes);
    if (temp == NULL) {
      genders_set_errnum(GENDERS_ERR_OUTMEM);
      return -1;
    }
    
    for (i = 0; i < numnodes; i++) {
      temp[i] = (char *)malloc(maxvallen+1);
      if (temp[i] == NULL) {
        
        for (j = 0; j < i; j++)
          free(temp[j]);
        free(temp);
        
        genders_set_errnum(GENDERS_ERR_OUTMEM);
        return -1;
      }
      memset(temp[i], '\0', maxvallen+1);
    }

    *altnodelist = temp;
  }

  return numnodes;
}

int genders_altnodelist_clear(genders_t handle, char **altnodelist) {
  int i, numnodes, maxvallen;
 
  if (altnodelist == NULL) {
    genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
    return -1;
  }

  if ((numnodes = genders_getnumnodes(handle)) == -1)
    return -1;

  if ((maxvallen = genders_getmaxvallen(handle)) == -1)
    return -1;

  if (numnodes > 0) {
    for (i = 0; i < numnodes; i++) {
      if (altnodelist[i] == NULL) {
        genders_set_errnum(handle, GENDERS_ERR_NULLPTR);
        return -1;
      }
      memset(altnodelist[i], '\0', maxvallen + 1);
    }
  }

  return 0;
}

int genders_altnodelist_destroy(genders_t handle, char **altnodelist) {
  int i, numnodes;
 
  if (altnodelist == NULL) {
    genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
    return -1;
  }

  if ((numnodes = genders_getnumnodes(handle)) == -1)
    return -1;

  if (numnodes > 0) {
    for (i = 0; i < numnodes; i++)
      free(altnodelist[i]);
    free(altnodelist);
  }

  return 0;
}

int genders_getaltnodes_common(genders_t handle,
                               char *altnodes[],
                               int len,
                               const char *attr,
                               const char *val,
                               int which) {
  int i, maxvallen, nodes_len, ret;
  char **nodes = NULL;
  char *altnodebuf = NULL;
  
  if ((nodes_len = genders_nodelist_create(handle, &nodes)) == -1)
    goto cleanup;
  
  if ((maxvallen = genders_getmaxvallen(handle)) == -1)
    goto cleanup;
  
  if ((altnodebuf = (char *)malloc(maxvallen+1)) == NULL) {
    genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
    goto cleanup;
  }

  if ((ret = genders_getnodes(handle, nodes, nodes_len, attr, val)) == -1)
    goto cleanup;

  if (ret > len) {
    genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
    goto cleanup;
  }

  for (i = 0; i < ret; i++) {
    memset(altnodebuf, '\0', maxvallen+1);
    if (which == GENDERSLLNL_ALTNAME_NOPRESERVE) {
      if (genders_to_altname(handle, 
                             nodes[i], 
                             altnodebuf, 
                             maxvallen+1) == -1)
        goto cleanup;
    }
    else { 
      if (genders_to_altname_preserve(handle, 
                                      nodes[i],
                                      altnodebuf,
                                      maxvallen+1) == -1)
        goto cleanup;
    }
    strcpy(altnodes[i], altnodebuf);
  }

  if (genders_nodelist_destroy(handle, nodes) == -1)
    goto cleanup;

  free(altnodebuf);
  return ret;

 cleanup:

  (void)genders_nodelist_destroy(handle, nodes);
  free(altnodebuf);

  return -1;
}

int genders_getaltnodes(genders_t handle,
                        char *altnodes[],
                        int len,
                        const char *attr,
                        const char *val) {

  return genders_getaltnodes_common(handle,
                                    altnodes,
                                    len,
                                    attr,
                                    val,
                                    GENDERSLLNL_ALTNAME_NOPRESERVE);
}

int genders_getaltnodes_preserve(genders_t handle,
                                 char *altnodes[],
                                 int len,
                                 const char *attr,
                                 const char *val) {

  return genders_getaltnodes_common(handle,
                                    altnodes,
                                    len,
                                    attr,
                                    val,
                                    GENDERSLLNL_ALTNAME_PRESERVE);
}

int genders_isaltnode(genders_t handle, const char *altnode) {

  return genders_isattrval(handle,
                           GENDERS_ALTNAME_ATTRIBUTE,
                           altnode);
}

int genders_isnode_or_altnode(genders_t handle, const char *nodename) {

  int ret;

  /* must be non-NULL, b/c isnode() interprets
   * NULL to be the current node
   */
  if (nodename == NULL) {
    genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
    return -1;
  }

  if ((ret = genders_isnode(handle, nodename)) == -1)
    return -1;

  if (ret != 1)
    ret = genders_isaltnode(handle, nodename);

  return ret;
}

int genders_to_gendname_common(genders_t handle,
                               const char *altnode,
                               char *buf,
                               int buflen) {
  int maxnodelen, ret;
  char *nodebuf = NULL;
  
  if (altnode == NULL || buf == NULL || buflen <= 0) {
    genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
    goto cleanup;
  }

  if ((ret = genders_isnode(handle, altnode)) == -1)
    goto cleanup;
 
  if (ret == 1) {
    /* already a gendname */
    if (strlen(altnode) + 1 > buflen) {
      genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
      goto cleanup;
    }
    strcpy(buf, altnode);
    return 1;
  }

  if ((maxnodelen = genders_getmaxnodelen(handle)) == -1)
    goto cleanup;
  
  if ((nodebuf = (char *)malloc(maxnodelen+1)) == NULL) {
    genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
    goto cleanup;
  }
  memset(nodebuf, '\0', maxnodelen+1);
  
  if ((ret = genders_getnodes(handle, 
                              &nodebuf,
                              1,
                              GENDERS_ALTNAME_ATTRIBUTE,
                              altnode)) == -1) {
    if (genders_errnum(handle) == GENDERS_ERR_OVERFLOW) {
      genders_set_errnum(handle, GENDERS_ERR_PARSE);
      goto cleanup;
    }
    goto cleanup;
  }

  if (ret > 1) {
    genders_set_errnum(handle, GENDERS_ERR_INTERNAL);
    goto cleanup;
  }

  if (ret == 1) {  
    if (strlen(nodebuf) + 1 > buflen) {
      genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
      goto cleanup;
    }
    strcpy(buf, nodebuf);
  }

  free(nodebuf);
  return ret;

 cleanup:

  free(nodebuf);

  return -1;
}

int genders_to_gendname(genders_t handle, 
                        const char *altnode, 
                        char *buf,       
                        int buflen) {
  int ret;

  if ((ret = genders_to_gendname_common(handle, 
                                        altnode,
                                        buf,
                                        buflen)) == -1)
    return -1;

  if (ret == 0) {
    genders_set_errnum(handle, GENDERS_ERR_NOTFOUND);
    return -1;
  }

  return 0;
}

int genders_to_gendname_preserve(genders_t handle, 
                                 const char *altnode, 
                                 char *buf, 
                                 int buflen) {
  int ret;

  if ((ret = genders_to_gendname_common(handle, 
                                        altnode,
                                        buf,
                                        buflen)) == -1)
    return -1;

  if (ret == 0) {
    if (strlen(altnode) + 1 > buflen) {
      genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
      return -1;
    }
    strcpy(buf, altnode);
  }

  return 0;
}

int genders_to_altname_common(genders_t handle,
                              const char *node,
                              char *buf,
                              int buflen) {
  int ret, maxvallen;
  char *altnodebuf = NULL;

  if (node == NULL || buf == NULL || buflen <= 0) {
    genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
    goto cleanup;
  }

  if ((ret = genders_isattrval(handle, 
                               GENDERS_ALTNAME_ATTRIBUTE,
                               node)) == -1)
    goto cleanup;
  
  if (ret == 1) {
    /* already an alternate name */ 
    if (strlen(node) + 1 > buflen) {
      genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
      goto cleanup;
    }
    strcpy(buf, node);
    return 1;
  }

  /* is it a legit node? */
  if ((ret = genders_isnode(handle, node)) == -1)
    goto cleanup;
  
  if (ret == 0)
    return 0;
  /* else ret == 1, get the altname */

  if ((maxvallen = genders_getmaxvallen(handle)) == -1)
    goto cleanup;
  
  if ((altnodebuf = (char *)malloc(maxvallen+1)) == NULL) {
    genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
    goto cleanup;
  }
  memset(altnodebuf, '\0', maxvallen+1);

  if ((ret = genders_testattr(handle,
                              node,
                              GENDERS_ALTNAME_ATTRIBUTE,
                              altnodebuf,
                              maxvallen + 1)) == -1)
    goto cleanup;
  
  /* check for possibility there is no alternate name value */
  if (ret == 1 && strlen(altnodebuf) == 0)
    ret = 0; 

  if (ret == 1) {
    if (strlen(altnodebuf) + 1 > buflen) {
      genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
      goto cleanup;
    }
    strcpy(buf, altnodebuf);
  }

  free(altnodebuf);
  return ret;

 cleanup:

  free(altnodebuf);

  return -1;
}

int genders_to_altname(genders_t handle, 
                       const char *node, 
                       char *buf, 
                       int buflen) {
  int ret;

  if ((ret = genders_to_altname_common(handle, 
                                       node,
                                       buf,
                                       buflen)) == -1)
    return -1;

  if (ret == 0) {
    genders_set_errnum(handle, GENDERS_ERR_NOTFOUND);
    return -1;
  }

  return 0;
}

int genders_to_altname_preserve(genders_t handle, 
                                const char *node, 
                                char *buf, 
                                int buflen) {
  int ret;

  if ((ret = genders_to_altname_common(handle, 
                                       node,
                                       buf,
                                       buflen)) == -1)
    return -1;

  if (ret == 0) {
    if (strlen(node) + 1 > buflen) {
      genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
      return -1;
    }
    strcpy(buf, node);
  }

  return 0;
}

int genders_string_common(genders_t handle,
                          const char *str,
                          char *buf,
                          int buflen,
                          int which) {

  int maxlen;
  char *nodename = NULL;
  char *nodebuf = NULL;
  hostlist_t src = NULL;
  hostlist_t dest = NULL;
  hostlist_iterator_t iter = NULL;

  if (str == NULL || buf == NULL || buflen <= 0) {
    genders_set_errnum(handle, GENDERS_ERR_PARAMETERS);
    goto cleanup;
  }

  maxlen = MAXHOSTNAMELEN;

  if ((nodebuf = (char *)malloc(maxlen+1)) == NULL) {
    genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
    goto cleanup;
  }

  if ((src = hostlist_create(str)) == NULL) {
    genders_set_errnum(handle, GENDERS_ERR_INTERNAL);
    goto cleanup;
  }

  if ((dest = hostlist_create(NULL)) == NULL) {
    genders_set_errnum(handle, GENDERS_ERR_INTERNAL);
    goto cleanup;
  }

  if ((iter = hostlist_iterator_create(src)) == NULL) {
    genders_set_errnum(handle, GENDERS_ERR_INTERNAL);
    goto cleanup;
  }

  while ((nodename = hostlist_next(iter)) != NULL) {

    if (strlen(nodename) > maxlen) {
      maxlen = strlen(nodename);
      if ((nodebuf = (char *)realloc(nodebuf, maxlen+1)) == NULL) {
        genders_set_errnum(handle, GENDERS_ERR_OUTMEM);
        goto cleanup;
      }
    }
    memset(nodebuf, '\0', maxlen+1);

    if (which == GENDERSLLNL_GENDNAME_NOPRESERVE) {
      if (genders_to_gendname(handle,
                              nodename,
                              nodebuf,
                              maxlen+1) == -1)
        goto cleanup;
    }
    else if (which == GENDERSLLNL_GENDNAME_PRESERVE) {
      if (genders_to_gendname_preserve(handle,
                                       nodename,
                                       nodebuf,
                                       maxlen+1) == -1)
        goto cleanup;
    }
    else if (which == GENDERSLLNL_ALTNAME_NOPRESERVE) {
      if (genders_to_altname(handle,
                             nodename,
                             nodebuf,
                             maxlen+1) == -1)
        goto cleanup;
    }
    else if (which == GENDERSLLNL_ALTNAME_PRESERVE) {
      if (genders_to_altname_preserve(handle,
                                      nodename,
                                      nodebuf,
                                      maxlen+1) == -1)
        goto cleanup;
    }

    if (hostlist_push_host(dest, nodebuf) == 0) {
      genders_set_errnum(handle, GENDERS_ERR_INTERNAL);
      goto cleanup;
    }

    free(nodename);
  }
  nodename = NULL;
  
  if (hostlist_ranged_string(dest, buflen, buf) == -1) {
    genders_set_errnum(handle, GENDERS_ERR_OVERFLOW);
    goto cleanup;
  }  

  hostlist_iterator_destroy(iter);
  hostlist_destroy(src);
  hostlist_destroy(dest);
  free(nodebuf);
  return 0;

 cleanup:

  hostlist_iterator_destroy(iter);
  hostlist_destroy(src);
  hostlist_destroy(dest);

  free(nodebuf);
  free(nodename);

  return -1;
}

int genders_string_to_gendnames(genders_t handle,
                                const char *str,
                                char *buf,
                                int buflen) {

  return genders_string_common(handle,
                               str,
                               buf,
                               buflen,
                               GENDERSLLNL_GENDNAME_NOPRESERVE);
}

int genders_string_to_gendnames_preserve(genders_t handle,
                                         const char *str,
                                         char *buf,
                                         int buflen) {
  return genders_string_common(handle,
                               str,
                               buf,
                               buflen,
                               GENDERSLLNL_GENDNAME_PRESERVE);
}

int genders_string_to_altnames(genders_t handle,
                               const char *str,
                               char *buf,
                               int buflen) {

  return genders_string_common(handle,
                               str,
                               buf,
                               buflen,
                               GENDERSLLNL_ALTNAME_NOPRESERVE);
}

int genders_string_to_altnames_preserve(genders_t handle,
                                        const char *str,
                                        char *buf,
                                        int buflen) {

  return genders_string_common(handle,
                               str,
                               buf,
                               buflen,
                               GENDERSLLNL_ALTNAME_PRESERVE);
}
