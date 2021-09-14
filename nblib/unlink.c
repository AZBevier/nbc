/*~!unlink.c*/
/* Name:  unlink.c Part No.: _______-____r
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

#ident	"@(#)nbclib:unlink.c	1.1"

#ifdef MPX1X
#include <finfo.h>
#endif

#include <string.h>
#include <limits.h>
#include <errno.h>

unlink(pname)			/* delete file or directory */
char *pname;
{
    int reg[8];
    char path[PATH_MAX];
#ifdef MPX1X
    struct finfo * foo;		/* file info block pointer */
#endif

    if (pname == 0 || *pname == 0) {
      errno = ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }

    strcpy(path, pname);	/* make a local copy */
    unix2mpx(path);		/* convert to MPX path */

#ifndef MPX1X
    reg[1] = (int) path;	/* get pnv */
    reg[1] |= (strlen(path) << 24);	/* get pnv */
    reg [7] = 0;		/* no cnp */
    mpxsvc (0x2024, reg, reg);	/* m.delr service */
    if (reg[7] != 0) {
      errno=ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }

#else /* MPX1X */

    if ((foo = pn2fib(path)) == NULL) {
      errno=ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }

    /* set username for this file, save old */
    if (setuser(foo->username, foo->userkey) != NULL) {
      errno=ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }

    /* assume no password for file */
    reg[4] = reg[5] = 0;
    /* we need to check for blank (null) password */
    if (strncmp ((char *)foo->password, "        ", 8) == 0)
      ;
    /* not blanks, copy password, could be null or ascii */
    else {
      reg[4] = foo->password[0];	/* set password */
      reg[5] = foo->password[1];	/* set password */
    }

    /* if username is null, delete system file */
    if ((foo->username[0] == 0) ||
      (strncmp ((char *)foo->username, "SYSTEM  ", 8) == 0))
      reg[3] = 'S';		/* delete system file */
    else
      reg[3] = 0;		/* delete user file */
    reg[6] = foo->filename[0];  /* first part of filename */
    reg[7] = foo->filename[1];  /* second part of filename */
    mpxsvc (0x1077, reg, reg);  /* m.delete service */

    /* if r7 returned 0, file not deleted */
    if (reg[7] == 0) {
      resetuser();		/* reset username to what it was */
      errno=ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }

    /* must reset username to what it before delete */
    resetuser();		/* reset username to what it was */
#endif /* MPX1X */
    return(0);			/* return o.k. */
}
