/*
 * $Id: gendersllnl.h,v 1.2 2003-05-22 00:44:41 achu Exp $
 * $Source: /g/g0/achu/temp/genders-cvsbackup-full/gendersllnl/src/libgendersllnl/gendersllnl.h,v $
 */

#ifndef _GENDERSLLNL_H
#define _GENDERSLLNL_H

#include <genders.h>

/******************
 * defines        *
 ******************/

#define GENDERS_ALTNAME_ATTRIBUTE      "altname"
#define GENDERS_CLUSTER_ATTRIBUTE      "cluster"
#define GENDERS_ALL_ATTRIBUTE          "all"

/******************
 * API            *
 ******************/

/* Get the name of the cluster
 * If node is NULL, check cluster of current node
 * Return 0 on success, -1 on error
 */
int genders_get_cluster(genders_t handle, 
                        const char *node,
                        char *buf,
                        int buflen);

/* Allocate an array of character strings to store altnodes in 
 * Returns: number of elements the list can store on success,
 *          -1 on failure
 */
int genders_altnodelist_create(genders_t handle, char ***altnodelist);

/* Clears the data stored in a previously created altnodes list
 * Returns: 0 on success, -1 on failure
 */
int genders_altnodelist_clear(genders_t handle, char **altnodelist);

/* Frees memory of a previously created altnodes list
 * Returns: 0 on success, -1 on failure
 */
int genders_altnodelist_destroy(genders_t handle, char **altnodelist);

/* Gets list of altnodes with the specified attribute.  
 * Identical to genders_getnodes(), except altnodes are returned.
 * If attr is NULL, gets all nodes.  
 * If val is non-NULL, get only nodes with attributes=val.
 * Nodes are returned in genders file order.
 * If altnode name does not exist, will return failure.
 * Returns: number of matches on success, -1 on failure.
 */
int genders_getaltnodes(genders_t handle,
                        char *altnodes[],
                        int len,
                        const char *attr,
                        const char *val);

/* Gets list of altnodes with the specified attribute.  
 * Identical to genders_getnodes(), except altnodes are returned.
 * If attr is NULL, gets all nodes.  
 * If val is non-NULL, get only nodes with attributes=val.
 * Nodes are returned in genders file order.
 * If altnode name does not exist, will return genders node name
 * Returns: number of matches on success, -1 on failure.
 */
int genders_getaltnodes_preserve(genders_t handle,
                                 char *altnodes[],
                                 int len,
                                 const char *attr,
                                 const char *val);

/* Tests whether the altnode exists in the genders file
 * Returns: 1=true , 0=false, -1=failure.
 */
int genders_isaltnode(genders_t handle, const char *altnode);

/* Tests whether the nodename exists in the genders file as a 
 * genders node or an altnode.
 * Returns: 1=true , 0=false, -1=failure.
 */
int genders_isnode_or_altnode(genders_t handle, const char *nodename);

/* Convert an altnode into a genders node.  
 * Copies 'altnode' into 'buf' if altnode is already a genders node
 * If alternate name is not found, will return failure.
 * Returns: 0 on success, -1 on failure
 */ 
int genders_to_gendname(genders_t handle, 
                        const char *altnode, 
                        char *buf, 
                        int buflen);

/* Convert an altnode into a genders node.  
 * Copies 'altnode' into 'buf' if altnode is already a genders node
 * If alternate name is not found, will return parameter pointed to by 
 * 'altnode'
 * Returns: 0 on success, -1 on failure
 */ 
int genders_to_gendname_preserve(genders_t handle, 
                                 const char *altnode, 
                                 char *buf, 
                                 int buflen);

/* Convert a node into a altnode.  
 * Copies 'node' into 'buf' if node is already an alternate node
 * If alternate name is not found, will return failure.
 * Returns: 0 on success, -1 on failure
 */ 
int genders_to_altname(genders_t handle, 
                       const char *node, 
                       char *buf, 
                       int buflen);

/* Convert a node into an altnode
 * Copies 'node' into 'buf' if node is already an alternate node
 * If alternate name is not found, will return parameter pointed to by
 * 'node'
 * Returns: 0 on success, -1 on failure
 */ 
int genders_to_altname_preserve(genders_t handle, 
                                const char *node, 
                                char *buf, 
                                int buflen);

/* Convert ranged string of altnodes to genders nodes
 * Will fail if any node is not an altnode
 * Returns: 0 on success, -1 on failure
 */ 
int genders_string_to_gendnames(genders_t handle,
                                const char *str,
                                char *buf,
                                int buflen);

/* Convert ranged string of altnodes to genders nodes
 * Will preserve node names if altnode is not found
 * Returns: 0 on success, -1 on failure
 */ 
int genders_string_to_gendnames_preserve(genders_t handle,
                                         const char *str,
                                         char *buf,
                                         int buflen);

/* Convert ranged string of altnodes to genders nodes
 * Will fail if any node is not an genders node
 * Returns: 0 on success, -1 on failure
 */ 
int genders_string_to_altnames(genders_t handle,
                               const char *str,
                               char *buf,
                               int buflen);

/* Convert ranged string of nodes to altnodes
 * Will preserve node names if node is not found
 * Returns: 0 on success, -1 on failure
 */ 
int genders_string_to_altnames_preserve(genders_t handle,
                                        const char *str,
                                        char *buf,
                                        int buflen);

#endif /* _GENDERSLLNL_H */

