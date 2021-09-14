/*~!tempnam.c*/
/* Name:  tempnam.c Part No.: _______-____r
 *
 * Copyright 1990 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:tempnam.c	1.0"

#include <stdio.h>
#include <string.h>

#define max(A,B) (((A)<(B))?(B):(A))

extern char *malloc(), *getenv(), *mktemp();
extern int access();

static char tmpdir[] = "TMPDIR";
static char tmp[] = "/system/tmp";
static char Xs[] = "XXXXXX";
static char usr_tmp[] = ".";

static char *pcopy(), *seed="AAA";

char *
tempnam(dir, pfx)
char *dir;		/* use this directory please (if non-NULL) */
char *pfx;		/* use this (if non-NULL) as filename prefix */
{
    register char *p, *q, *tdir;
    int x=0, y=0, z;

    z = strlen(usr_tmp);
    if((tdir = getenv(tmpdir)) != NULL) {
      x = strlen(tdir);
    }
    if(dir != NULL) {
      y = strlen(dir);
    }
    if((p = malloc((unsigned)(max(max(x, y), z) + 16))) == NULL)
      return(NULL);
    if(x > 0 && access(pcopy(p, tdir), 3) == 0)
      goto OK;
    if(y > 0 && access(pcopy(p, dir), 3) == 0)
      goto OK;
    if(access(pcopy(p, usr_tmp), 3) == 0)
      goto OK;
    if(access(pcopy(p, tmp), 3) != 0)
      return(NULL);
OK:
    (void)strcat(p, "/");
    if(pfx) {
      *(p + strlen(p) + 5) = '\0';
      (void)strncat(p, pfx, 5);
    }
    (void)strcat(p, seed);
    (void)strcat(p, Xs);
    q = seed;
    while(*q == 'Z')
      *q++ = 'A';
    if(*q != '\0')
      ++*q;
    if(*mktemp(p) == '\0')
      return(NULL);
    return(p);
}

static char*
pcopy(space, arg)
char *space, *arg;
{
    char *p;

    if(arg) {
      (void)strcpy(space, arg);
      p = space - 1 + strlen(space);
      if(*p == '/')
    	*p = '\0';
    }
    return(space);
}
