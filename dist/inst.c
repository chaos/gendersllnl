/*****************************************************************************\
 *  $Id: inst.c,v 1.6 2007-09-05 17:49:18 chu11 Exp $
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
 *  Gendersllnl is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more information.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Gendersllnl; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
\*****************************************************************************/

/*
 * install program with the following features
 * - if -q specified, we are verbose about installing, quiet about not 
 *   installing (install command is probably @prefixed in Makefile)
 * - if dest exists and is older than source:
 *   -c  install only if a cmp fails
 *   -C  install only if a normalized diff fails
 * - if dest exists and is newer than source
 *   -f  force install (default is to abort)
 * 
 * Intended to be used in conjunction with rdist.  Files that are to be
 * rdisted should not be updated lightly as broadcasting an identical file
 * is costly and pointless.
 * 
 * This script was inst.pl, but perl startup was too slow when checking lots
 * of files.
 * 
 * Created 10/8/97 by Jim Garlick <garlick@llnl.gov>
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <stdlib.h>
#include <utime.h>

#define _PATH_DIFF	"/usr/bin/diff"
#define _PATH_CMP	"/usr/bin/cmp"
#define _PATH_DEV_NULL  "/dev/null"

#define USAGE "\
inst -s file -d dstdir [-m mode] [-o owner] [-g group] [-c|-C] [-f] [-q]"

#define WHY_SAMEMTIME	"source and destination have same mtime"
#define WHY_DESTNEWER	"destination is newer than source"
#define WHY_CMP		"source and destination are identical (cmp)"
#define WHY_DIFF	"source and destination are identical (diff -b)"

#define NONE (-3)

static void usage(void);

int main(int argc, char *argv[])
{
    int c;
    extern int optind;
    extern char *optarg;
    struct passwd *pw;
    struct group *gr;
    struct stat sb_src, sb_dst, sb_dstdir;
    char *src_file = NULL;
    char *dst_dir = NULL;
    char dst_file[MAXPATHLEN];
    mode_t dst_mode = NONE;
    uid_t in_uid, dst_uid = NONE;
    gid_t in_gid, dst_gid = NONE;
    int opt_c = 0, opt_C = 0, opt_f = 0, opt_q = 0;
    int do_copy, do_chmod, do_chown;
    pid_t pid;
    int st, rv;
    char *why, *ptr;
    struct timeval times[2];
    int dst_fd, src_fd, dev_null_fd;
    unsigned char buf[BUFSIZ];

    while ((c = getopt(argc, argv, "s:d:m:o:g:cCfq")) != EOF) {
        switch (c) {
        case 's':
            src_file = strdup(optarg);
            if (stat(src_file, &sb_src) == -1) {
                fprintf(stderr, "%s does not exist\n", src_file);
                exit(1);
            }
            if (!S_ISREG(sb_src.st_mode)) {
                fprintf(stderr, "%s not a plain file\n", src_file);
                exit(1);
            }
            break;
        case 'd':
            dst_dir = strdup(optarg);
            if (stat(dst_dir, &sb_dstdir) == -1) {
                fprintf(stderr, "%s does not exist\n", dst_dir);
                exit(1);
            }
            if (!S_ISDIR(sb_dstdir.st_mode)) {
                fprintf(stderr, "%s not a directory\n", dst_dir);
                exit(1);
            }
            break;
        case 'm':
            if (sscanf(optarg, "%o", &dst_mode) != 1
                || (dst_mode < 0 || dst_mode > 07777)) {
                fprintf(stderr, "bad mode: %s\n", optarg);
                exit(1);
            }
            break;
        case 'o':
            pw = getpwnam(optarg);
            if (!pw) {
                in_uid = strtoul(optarg, &ptr, 10);
                if (ptr == (optarg + strlen(optarg)))
                    pw = getpwuid(in_uid);
            }
            if (!pw) {
                fprintf(stderr, "bad owner: %s\n", optarg);
                exit(1);
            }
            dst_uid = pw->pw_uid;
            break;
        case 'g':
            gr = getgrnam(optarg);
            if (!gr) {
                in_gid = strtoul(optarg, &ptr, 10);
                if (ptr == (optarg + strlen(optarg)))
                    gr = getgrgid(in_gid);
            }
            if (!gr) {
                fprintf(stderr, "bad group: %s\n", optarg);
                exit(1);
            }
            dst_gid = gr->gr_gid;
            break;
        case 'c':
            opt_c = 1;
            break;
        case 'C':
            opt_C = 1;
            break;
        case 'f':
            opt_f = 1;
            break;
        case 'q':
            opt_q = 1;
            break;
        default:
            usage();
        }
    }

    if (!src_file || !dst_dir)
        usage();
    if (dst_mode == NONE)
        dst_mode = sb_src.st_mode & 07777;
    if (dst_uid == NONE)
        dst_uid = sb_src.st_uid;
    if (dst_gid == NONE)
        dst_gid = sb_src.st_gid;
    sprintf(dst_file, "%s/%s", dst_dir, src_file);

    /*
     * If destination exists, determine if we need to copy, chmod or chown
     */
    do_copy = 1;
    do_chmod = 1;
    do_chown = 1;
    if (stat(dst_file, &sb_dst) != -1) {

        /* dest same age as src: assume we put it there */
        if (sb_dst.st_mtime == sb_src.st_mtime) {
            if (!opt_f) {
                do_copy = 0;
                why = WHY_SAMEMTIME;
            }

            /* dest newer than src: someone may have updated wrong file */
        } else if (sb_dst.st_mtime > sb_src.st_mtime) {
            if (!opt_f) {
                do_copy = 0;
                why = WHY_DESTNEWER;
            }

            /* src newer than dest: probably install; not neccessarily */
        } else if (sb_dst.st_mtime < sb_src.st_mtime) {

            /* compare binary files */
            if (opt_c) {
                switch (pid = fork()) {
                case (-1):
                    perror("fork");
                    exit(1);
                case 0:
                    /* cannot close stdout, cmp will fail if it cannot
                     * write to stdout.  We must redirect instead.  
                     */
                    if ((dev_null_fd = open(_PATH_DEV_NULL, O_RDWR)) < 0) { 
                        perror("open");
                        exit(1);
                    }
                    dup2(dev_null_fd, 1);
                    dup2(dev_null_fd, 2);
                    if (execl(_PATH_CMP, "cmp", src_file, dst_file, 0) < 0)
                        exit(1);
                default:
                    rv = waitpid(pid, &st, 0);
                    break;
                }
                if (rv != -1 && WIFEXITED(st)
                    && WEXITSTATUS(st) == 0) {
                    do_copy = 0;
                    why = WHY_CMP;
                }

                /* compare text files with normalized white space */
            } else if (opt_C) {
                switch (pid = fork()) {
                case (-1):
                    perror("fork");
                    exit(1);
                case 0:
                    /* cannot close stdout, diff will fail if it cannot
                     * write to stdout.  We must redirect instead.
                     */
                    if ((dev_null_fd = open(_PATH_DEV_NULL, O_RDWR)) < 0) { 
                        perror("open");
                        exit(1);
                    }
                    dup2(dev_null_fd, 1);
                    dup2(dev_null_fd, 2);
                    if (execl(_PATH_DIFF, "diff", "-b", src_file, dst_file, 0) < 0)
                        exit(1);
                default:
                    rv = waitpid(pid, &st, 0);
                    break;
                }
                if (rv != -1 && WIFEXITED(st)
                    && WEXITSTATUS(st) == 0) {
                    do_copy = 0;
                    why = WHY_DIFF;
                }
            }
        }

        /* figure out if we need to chmod or chown the file */
        if (!do_copy) {
            if (sb_dst.st_uid == dst_uid && sb_dst.st_gid == dst_gid)
                do_chown = 0;
            if ((sb_dst.st_mode & 07777) == dst_mode)
                do_chmod = 0;
        }
    }
#if 0
    printf("src_file =  %s\n", src_file);
    printf("dst_dir =   %s\n", dst_dir);
    printf("dst_file =  %s (%d:%d %o)\n",
           dst_file, dst_uid, dst_gid, dst_mode);
    printf("do_copy =   %s\n", do_copy ? "yes" : "no");
    if (!do_copy)
        printf("why =       %s\n", why);
    printf("do_chown =  %s\n", do_chown ? "yes" : "no");
    printf("do_chmod =  %s\n", do_chmod ? "yes" : "no");
#else
    if (!do_copy && !(opt_q && strcmp(why, WHY_DESTNEWER) != 0))
        printf("%s not copied: %s\n", src_file, why);
    if (opt_q && do_copy)
        printf("installing %s\n", dst_file);
#endif
    if (do_copy) {
        /* copy the file */
        if ((dst_fd = open(dst_file, O_CREAT | O_TRUNC | O_WRONLY)) == -1) {
            perror(dst_file);
            exit(1);
        }
        if ((src_fd = open(src_file, O_RDONLY)) == -1) {
            perror(src_file);
            exit(1);
        }
        while ((rv = read(src_fd, buf, BUFSIZ)) > 0)
            if (write(dst_fd, buf, rv) == -1) {
                perror(dst_file);
                unlink(dst_file);
                exit(1);
            }
        close(src_fd);
        close(dst_fd);

        /* touch date to be the same as source file */
        times[0].tv_sec = sb_src.st_mtime;
        times[0].tv_usec = 0;
        times[1] = times[0];
        if (utimes(dst_file, times) == -1)
            perror(dst_file);
    }

    if (do_chown)
        if (chown(dst_file, dst_uid, dst_gid) == -1)
            perror(dst_file);
    if (do_chmod)
        if (chmod(dst_file, dst_mode) == -1)
            perror(dst_file);

    exit(0);
}

static void usage(void)
{
    fprintf(stderr, "Usage: %s\n", USAGE);
    exit(1);
}

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */
