#include "gendersllnl.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE       1000

void err_exit(char *msg, char *errmsg) {

  if (msg != NULL) {
    printf("%s: ", msg);
  }

  if (errmsg != NULL) {
    printf("%s", errmsg);
  } 

  printf("\n");

  exit(1);
}

char * buf_malloc(int size) {
  char *buf;

  if ((buf = (char *)malloc(size)) == NULL) {
    err_exit("malloc()", NULL);
  }

  return buf;
}

int main() {
  int len, ret, i;
  genders_t handle;
  char *buf;
  char **altnodes;

  if ((handle = genders_handle_create()) == NULL)
    err_exit("genders_handle_create()", genders_errormsg(handle));

  if (genders_load_data(handle, NULL) == -1)
    err_exit("genders_load_data()", genders_errormsg(handle));

  buf = buf_malloc(BUFSIZE);

  memset(buf, '\0', BUFSIZE);
  if (genders_get_cluster(handle, NULL, buf, BUFSIZE) == -1)
    err_exit("genders_get_cluster()", genders_errormsg(handle));
  printf("Cluster: %s\n", buf);
  printf("\n");

  printf("gendname\n");
  memset(buf, '\0', BUFSIZE);
  ret = genders_to_gendname(handle, "mdevi", buf, BUFSIZE);
  printf("mdevi: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_to_gendname(handle, "emdevi", buf, BUFSIZE);
  printf("emdevi: %d %s\n", ret, buf);
  
  memset(buf, '\0', BUFSIZE);
  ret = genders_to_gendname(handle, "foo", buf, BUFSIZE);
  printf("foo: %d %s\n", ret, buf);
  printf("\n");

  printf("gendname preserve\n");
  memset(buf, '\0', BUFSIZE);
  ret = genders_to_gendname_preserve(handle, "mdevi", buf, BUFSIZE);
  printf("mdevi: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_to_gendname_preserve(handle, "emdevi", buf, BUFSIZE);
  printf("emdevi: %d %s\n", ret, buf);
  
  memset(buf, '\0', BUFSIZE);
  ret = genders_to_gendname_preserve(handle, "foo", buf, BUFSIZE);
  printf("foo: %d %s\n", ret, buf);
  printf("\n");

  printf("altname\n");
  memset(buf, '\0', BUFSIZE);
  ret = genders_to_altname(handle, "mdevi", buf, BUFSIZE);
  printf("mdevi: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_to_altname(handle, "emdevi", buf, BUFSIZE);
  printf("emdevi: %d %s\n", ret, buf);
  
  memset(buf, '\0', BUFSIZE);
  ret = genders_to_altname(handle, "foo", buf, BUFSIZE);
  printf("foo: %d %s\n", ret, buf);
  printf("\n");

  printf("altname preserve\n");
  memset(buf, '\0', BUFSIZE);
  ret = genders_to_altname_preserve(handle, "mdevi", buf, BUFSIZE);
  printf("mdevi: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_to_altname_preserve(handle, "emdevi", buf, BUFSIZE);
  printf("emdevi: %d %s\n", ret, buf);
  
  memset(buf, '\0', BUFSIZE);
  ret = genders_to_altname_preserve(handle, "foo", buf, BUFSIZE);
  printf("foo: %d %s\n", ret, buf);
  printf("\n");

  printf("string to gendname\n");
  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_gendnames(handle, "mdev[0-5]", buf, BUFSIZE);
  printf("mdev[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_gendnames(handle, "emdev[0-5]", buf, BUFSIZE);
  printf("emdev[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_gendnames(handle, "foo[0-5]", buf, BUFSIZE);
  printf("foo[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_gendnames(handle, "mdev[0-1],emdev[2-3]", buf, BUFSIZE);
  printf("mdev[0-1],emdev[2-3]: %d %s\n", ret, buf);
  printf("\n");

  printf("string to gendname_preserve\n");
  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_gendnames_preserve(handle, "mdev[0-5]", buf, BUFSIZE);
  printf("mdev[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_gendnames_preserve(handle, "emdev[0-5]", buf, BUFSIZE);
  printf("emdev[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_gendnames_preserve(handle, "foo[0-5]", buf, BUFSIZE);
  printf("foo[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_gendnames_preserve(handle, "mdev[0-1],emdev[2-3]", buf, BUFSIZE);
  printf("mdev[0-1],emdev[2-3]: %d %s\n", ret, buf);
  printf("\n");

  printf("string to altname\n");
  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_altnames(handle, "mdev[0-5]", buf, BUFSIZE);
  printf("mdev[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_altnames(handle, "emdev[0-5]", buf, BUFSIZE);
  printf("emdev[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_altnames(handle, "foo[0-5]", buf, BUFSIZE);
  printf("foo[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_altnames(handle, "mdev[0-1],emdev[2-3]", buf, BUFSIZE);
  printf("mdev[0-1],emdev[2-3]: %d %s\n", ret, buf);
  printf("\n");

  printf("string to altname_preserve\n");
  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_altnames_preserve(handle, "mdev[0-5]", buf, BUFSIZE);
  printf("mdev[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_altnames_preserve(handle, "emdev[0-5]", buf, BUFSIZE);
  printf("emdev[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_altnames_preserve(handle, "foo[0-5]", buf, BUFSIZE);
  printf("foo[0-5]: %d %s\n", ret, buf);

  memset(buf, '\0', BUFSIZE);
  ret = genders_string_to_altnames_preserve(handle, "mdev[0-1],emdev[2-3]", buf, BUFSIZE);
  printf("mdev[0-1],emdev[2-3]: %d %s\n", ret, buf);
  printf("\n");

  printf("test altnode\n");
  ret = genders_isaltnode(handle, "mdevi");
  printf("mdevi: %d\n", ret);
  ret = genders_isaltnode(handle, "emdevi");
  printf("emdevi: %d\n", ret);
  ret = genders_isaltnode(handle, "foo");
  printf("foo: %d\n", ret);
  printf("\n");

  printf("test node altnode\n");
  ret = genders_isnode_or_altnode(handle, "mdevi");
  printf("mdevi: %d\n", ret);
  ret = genders_isnode_or_altnode(handle, "emdevi");
  printf("emdevi: %d\n", ret);
  ret = genders_isnode_or_altnode(handle, "foo");
  printf("foo: %d\n", ret);
  printf("\n");
  
  if ((len = genders_altnodelist_create(handle, &altnodes)) == -1)
    err_exit("genders_altnodelist_create()", genders_errormsg(handle));
  
  printf("altnodes\n");
  if (genders_altnodelist_clear(handle, altnodes) == -1)
    err_exit("genders_altnodelist_clear()", genders_errormsg(handle));

  if ((ret = genders_getaltnodes(handle, altnodes, len, NULL, NULL)) == -1)
    err_exit("genders_getaltnodes()", genders_errormsg(handle));

  printf("NULL %d: ", ret);
  for (i = 0; i < ret; i++)
    printf("%s ", altnodes[i]);
  printf("\n");

  if (genders_altnodelist_clear(handle, altnodes) == -1)
    err_exit("genders_altnodelist_clear()", genders_errormsg(handle));

  if ((ret = genders_getaltnodes(handle, altnodes, len, "all", NULL)) == -1)
    err_exit("genders_getaltnodes()", genders_errormsg(handle));

  printf("all %d: ", ret);
  for (i = 0; i < ret; i++)
    printf("%s ", altnodes[i]);
  printf("\n");

  if (genders_altnodelist_clear(handle, altnodes) == -1)
    err_exit("genders_altnodelist_clear()", genders_errormsg(handle));

  if ((ret = genders_getaltnodes(handle, altnodes, len, "qla", NULL)) == -1)
    err_exit("genders_getaltnodes()", genders_errormsg(handle));

  printf("qla %d: ", ret);
  for (i = 0; i < ret; i++)
    printf("%s ", altnodes[i]);
  printf("\n");

  if (genders_altnodelist_clear(handle, altnodes) == -1)
    err_exit("genders_altnodelist_clear()", genders_errormsg(handle));

  if ((ret = genders_getaltnodes(handle, altnodes, len, "altname", "mdev0")) == -1)
    err_exit("genders_getaltnodes()", genders_errormsg(handle));

  printf("altname=mdev0 %d: ", ret);
  for (i = 0; i < ret; i++)
    printf("%s ", altnodes[i]);
  printf("\n");

  if (genders_altnodelist_clear(handle, altnodes) == -1) 
    err_exit("genders_altnodelist_clear()", genders_errormsg(handle));

  if ((ret = genders_getaltnodes(handle, altnodes, len, "altname", "emdev0")) == -1)
    err_exit("genders_getaltnodes()", genders_errormsg(handle));

  printf("altname=emdev0 %d: ", ret);
  for (i = 0; i < ret; i++)
    printf("%s ", altnodes[i]);
  printf("\n");
  printf("\n");
  
  printf("altnodes_preserve\n");
  if (genders_altnodelist_clear(handle, altnodes) == -1)
    err_exit("genders_altnodelist_clear()", genders_errormsg(handle));

  if ((ret = genders_getaltnodes(handle, altnodes, len, NULL, NULL)) == -1)
    err_exit("genders_getaltnodes()", genders_errormsg(handle));

  printf("NULL %d: ", ret);
  for (i = 0; i < ret; i++)
    printf("%s ", altnodes[i]);
  printf("\n");

  if (genders_altnodelist_clear(handle, altnodes) == -1)
    err_exit("genders_altnodelist_clear()", genders_errormsg(handle));

  if ((ret = genders_getaltnodes(handle, altnodes, len, "all", NULL)) == -1)
    err_exit("genders_getaltnodes()", genders_errormsg(handle));

  printf("all %d: ", ret);
  for (i = 0; i < ret; i++)
    printf("%s ", altnodes[i]);
  printf("\n");

  if (genders_altnodelist_clear(handle, altnodes) == -1)
    err_exit("genders_altnodelist_clear()", genders_errormsg(handle));

  if ((ret = genders_getaltnodes(handle, altnodes, len, "qla", NULL)) == -1)
    err_exit("genders_getaltnodes()", genders_errormsg(handle));

  printf("qla %d: ", ret);
  for (i = 0; i < ret; i++)
    printf("%s ", altnodes[i]);
  printf("\n");

  if (genders_altnodelist_clear(handle, altnodes) == -1)
    err_exit("genders_altnodelist_clear()", genders_errormsg(handle));

  if ((ret = genders_getaltnodes(handle, altnodes, len, "altname", "mdev0")) == -1)
    err_exit("genders_getaltnodes()", genders_errormsg(handle));

  printf("altname=mdev0 %d: ", ret);
  for (i = 0; i < ret; i++)
    printf("%s ", altnodes[i]);
  printf("\n");

  if (genders_altnodelist_clear(handle, altnodes) == -1)
    err_exit("genders_altnodelist_clear()", genders_errormsg(handle));

  if ((ret = genders_getaltnodes(handle, altnodes, len, "altname", "emdev0")) == -1)
    err_exit("genders_getaltnodes()", genders_errormsg(handle));

  printf("altname=emdev0 %d: ", ret);
  for (i = 0; i < ret; i++)
    printf("%s ", altnodes[i]);
  printf("\n");

  if (genders_altnodelist_destroy(handle, altnodes) == -1)
    err_exit("genders_altnodelist_destroy()", genders_errormsg(handle));

  if (genders_handle_destroy(handle) == -1)
     err_exit("genders_handle_destroy()", genders_errormsg(handle));

  free(buf);
  exit(0);
}
