/*~!chown.c*/
/* Name:  chown.c Part No.: _______-____r
 *
 * Copyright 1994 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:chowm.c	1.1"

#include <errno.h>
#include <limits.h>

/*
 * Change owner and group of a file
 */

chown(path,owner,group)		/* entry */
char  *path;
int   owner,group;
{
#ifndef FIX_050294
    char *op = "SYSTEM";
    char *pp = "SYSTEM";

    /* if owner is 0, set to system, else ignore */
    if (owner == 0)
    	if (group == 0)
    	    return(chownm(path, op, pp));
    	else
    	    return(chownm(path, op, (char *)0));
    else
    	if (group == 0)
    	    return(chownm(path, (char *)0, pp));
    return (0);		/* return o.k. status */
#else
    /*    this routine does nothing   */
    return (0); 	/* return o.k. status */
#endif
}

/*
 * Set new owner and project names
 */

#ifndef FIX_050294
/* do not move this definition, must be 2w bounded */
asm (" bound 1d");
static int rdbuf[192];		/* resource descriptor buffer 2w bounded */
#endif

chownm(file, op, pp)
char  *file;
char  *op;		/* new owner name */
char  *pp;		/* new project name */
{
/* implemented 05/02/94 */
#ifndef FIX_050294
    int reg[8];
    char path[PATH_MAX];
    int len;

    if (!(file != 0 && *file != 0)) {
      errno = ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }

    strcpy(path, file);		/* make a local copy */
    unix2mpx(path);		/* convert to MPX path */
    
    /* now read the file rd for modification */
    reg[1] = (int)path;		/* get pnv */
    reg[1] |= (strlen(path) << 24);	/* get pnv */
    reg[6] = (int)rdbuf;	/* rd buffer address */
    reg[7] = 0;			/* no cnp */
    mpxsvc (0x202a, reg, reg);	/* m.mod service */
    if (reg[7] != 0) {
      errno = ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }

    /* modify the rd */
    /* if owner name is not null, update the rd */
    if (op != (char *)0 && *op != '\0') {
    	len = strlen(op);
    	memset(&rdbuf[26], ' ', 8);	/* pre blank */
    	memcpy(&rdbuf[26], op, len >= 8 ? 8 : len);	/* copy in */
    }
    /* if project name is not null, update the rd */
    if (pp != (char *)0 && *pp != '\0') {
    	len = strlen(pp);
    	memset(&rdbuf[28], ' ', 8);	/* pre blank */
    	memcpy(&rdbuf[28], pp, len >= 8 ? 8 : len);	/* copy in */
    }
    /* now write the file rd after modification */
    reg[6] = (int)rdbuf;	/* rd buffer address */
    reg[7] = 0;			/* no cnp */
    mpxsvc (0x202b, reg, reg);	/* m.rewrit service */
    if (reg[7] != 0) {
      errno = ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }
    return (0);			/* return o.k. */
#endif
}

chtype(file, type)
char  *file;
int   type;			/* new file type */
{
/* implemented 05/02/94 */
#ifndef FIX_050294
    int reg[8];
    char path[PATH_MAX];

    if (!(file != 0 && *file != 0)) {
      errno = ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }

    strcpy(path, file);		/* make a local copy */
    unix2mpx(path);		/* convert to MPX path */
    
    /* now read the file rd for modification */
    reg[1] = (int)path;		/* get pnv */
    reg[1] |= (strlen(path) << 24);	/* get pnv */
    reg[6] = (int)rdbuf;	/* rd buffer address */
    reg[7] = 0;			/* no cnp */
    mpxsvc (0x202a, reg, reg);	/* m.mod service */
    if (reg[7] != 0) {
      errno = ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }

    /* modify the rd */
    /* set new file type */
    rdbuf[64] = ((rdbuf[64] & 0xffffff) | (type << 24));

    /* now write the file rd after modification */
    reg[6] = (int)rdbuf;	/* rd buffer address */
    reg[7] = 0;			/* no cnp */
    mpxsvc (0x202b, reg, reg);	/* m.rewrit service */
    if (reg[7] != 0) {
      errno = ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }
    return (0);			/* return o.k. */
#endif
}
