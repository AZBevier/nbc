/*~!getpath.c*/
/* Name:  getpath.c Part No.: _______-____r
 *
 * Copyright 1992 - J B Systems, Morrison, CO
 *
 * The recipient of this product specifically agrees not to distribute,
 * disclose, or disseminate in any way, to any one, nor use for its own
 * benefit, or the benefit of others, any information contained  herein
 * without the expressed written consent of J B Systems.
 *
 *                     RESTRICTED RIGHTS LEGEND
 *
 * Use, duplication, or disclosure by the Government is  subject  to
 * restriction  as  set forth in paragraph (b) (3) (B) of the Rights
 * in Technical Data and Computer Software  Clause  in  DAR  7-104.9
 * (a).
 */

#ident	"@(#)nbclib:getpath.c	1.1"

#ifndef MPX1X

#include <limits.h>
#include <stdio.h>

extern	int	mpxsvc();
extern	int	*fcbadr();

static  char    pathname[PATH_MAX];

/* reconstruct pathname from file i.d. of open file */
/* returns pointer to pathname if found, else -1 */

char *
getpath(fid)
int     fid;
{

    int     regs[8];
    int     len, l;
    char    path[PATH_MAX];
    FILE    *tid;
    char    *p;

    if (fid < 0)
      return ((char *)(-1));
    if (fid > _NFILE) {
      tid = (FILE *)fid;
      fid = fileno(tid);
    }
    regs[1] = (int)*fcbadr(fid);
    regs[7] = 0;   			/* no cnp */
    regs[4] = (64 << 24) | (int)path;
    mpxsvc(0x202f, regs, regs);		/* reconstruct pathname */
    p = (char *)(regs[4] & 0xffffff);
    len = regs[4] >> 24;
    for (l=0; len--; l++)
      pathname[l] = p[l];
    pathname[regs[4] >> 24] = 0;
    return (pathname);
}

#else /* MPX1X */

#define CASSG
#include "unixio.h"
#include <limits.h>
#include <string.h>

static  char    pathname[PATH_MAX];

char *
getpath(fid)     /* reconstruct pathname from file i.d. of open file */
int     fid;
{
    char * bad = (char *)-1;
    char    path[PATH_MAX];
    char * p;

    if ((fid < 0) || (fid > _NFILE))
      return (bad);			/* return error */
    if (filtabl [fid].filparm.mode & NOTUSED)
      return (bad);
    strcpy (pathname, "@SYSTEM(");
    CPYNAME ((char *)filtabl[fid].fib.username, (p=strchr(pathname, '\0')));
    p = strchr(pathname, '\0');
    if (*(char *)filtabl[fid].fib.userkey != '\0') {
      *p++ = ',';
      CPYNAME ((char *)filtabl[fid].fib.userkey, p);
      p = strchr(pathname,'\0');
    }
    *p++ = ')';
    CPYNAME ((char *)filtabl[fid].fib.filename, p);
    p = strchr(pathname,'\0');
    if (*(char *)filtabl[fid].fib.password != '\0') {
      *p++ = ',';
      CPYNAME ((char *)filtabl[fid].fib.userkey, p);
      p = strchr(pathname,'\0');
    }
    return (pathname);
}
#endif
