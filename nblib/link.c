/*~!link.c*/
/* Name:  link.c Part No.: _______-____r
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

#ident	"@(#)nbclib:link.c	1.1"

#ifdef MPX1X
#include <types.h>
#include <stat.h>
#include <finfo.h>
#endif
#include <string.h>
#include <errno.h>
#include <limits.h>

link(path1, path2)		/* rename path1 to path2 */
char *path1, *path2;
{
    int reg[8];
    char ppath1[PATH_MAX], ppath2[PATH_MAX];
#ifdef MPX1X
    unsigned int smd[8];
    unsigned int smd2[8];
    struct finfo fin;
    struct finfo fout;
    struct finfo *foo;
    int temp;
    int i;
#endif

    if (!(path1 != 0 && *path1 != 0)) {
      errno=ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }
    if (!(path2 != 0 && *path2 != 0)) {
      errno=ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }
    strcpy(ppath1, path1);
    strcpy(ppath2, path2);
    unix2mpx(ppath1);
    unix2mpx(ppath2);

#ifndef MPX1X
    reg[1] = (int) ppath1;	/* get address of path1 */
    reg[1] |= (strlen(ppath1) << 24);	/* get path length */
    reg[2] = (int) ppath2;	/* get address of path2 */
    reg[2] |= (strlen(ppath2) << 24);	/* get path length */
    reg[7] = 0;			/* no cnp */
    mpxsvc (0x202d, reg, reg);	/* m.renam service */

    if (reg[7] != 0) {
      errno=ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }
#else
    if(strcmp(ppath1, ppath2) == 0)
      return(0);	/* if file is to be renamed to itself, return */

    /* do pathname conversion */
    if ((foo = pn2fib(ppath1)) == 0) {
      errno = ENOENT;
      return (-1);
    }
    /* now copy in the structure */
    memcpy (&fin, foo, sizeof (struct finfo));
/*    fin = *foo;			/* copy structure */

    /* do pathname conversion */
    if ((foo = pn2fib(ppath2)) == 0) {
      errno = ENOENT;
      return (-1);
    }
    /* now copy in the structure */
    memcpy (&fout, foo, sizeof (struct finfo));
/*    fout = *foo;		/* copy structure */

    /* see if target file already exits, if so, delete it first */
    if(stat1x(ppath2, smd) != -1) {
      /* file exists, delete it */
      if (unlink(ppath2) == -1) {
    	/* can not delete file, give error return */
    	errno = ENOENT;
    	return (-1);
      }
    }

    /* see if source file exits, if so, log the SMD entry */
    if(stat1x(ppath1, smd) == -1) {
      /* file does not exists, give error return */
      errno = ENOENT;
      return (-1);
    }

    /* copy the smd entry */
    for (i=0; i<8; i++)
      smd2[i] = smd[i];
    /* turn off no save, password for write, password for r/w bits */
    smd[3] &= ~(0x23000000);
    smd[0] = fout.filename[0];		/* 1st part of filename */
    smd[1] = fout.filename[1];		/* 2nd part of filename */
    smd[4] = fout.username[0];		/* 1st part of username */
    smd[5] = fout.username[1];		/* 2nd part of username */
    /* compress the key */
    temp = fout.userkey[0] + fout.userkey[1];
    temp = (((unsigned int)temp & 0xffff0000) >> 16) + (temp & 0xffff);
    smd[6] = (smd[6] & 0xffff) | ((unsigned int)temp << 16);
    /* now rewite the smd entry for the new file */
    if (wrtsmd(smd) == -1) {
      errno = ENOENT;
      return (-1);
    }
    smd2[3] &= ~(0x80000000);		/* make old file a temp */
    /* now rewite the smd entry for the old file */
    if (wrtsmd(smd2) == -1) {
      errno = ENOENT;
      return (-1);
    }
#endif
    return(0);			/* file renamed */
}

#ifdef MPX1X
/* wrtsmd - routine to rewite an SMD entry
 * this code must be run privledged
 */

int
wrtsmd(smd)
register int *smd;
{
    register int ret;
    /* ret value will be in reg 6 */
    /* smd address will be in reg 7 */

    asm(" la r4,ERRET");	/* set error return address */
    asm(" li r6,-1");		/* show we have error for error return */
    asm(" trr r7,r1");		/* set smd address */
    asm(" li r7,1");		/* set priv indicator */
    asm(" svc 1,x'11'");	/* go privledged */
    asm(" svc 0,4*256+2");	/* do m.call h.fise,2 */
    asm(" zr r6");		/* show O.K. return */
    /* we will return at ERRET if their is a problem, r6 already set up */
    asm("ERRET li r7,0");	/* set unpriv indicator */
    asm(" svc 1,x'11'");	/* go unprivledged */
    return(ret);		/* return value from reg 6 */
}
#endif
