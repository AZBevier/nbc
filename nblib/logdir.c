/*~!logdir.c*/
/* Name:  logdir.c Part No.: _______-____r
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

#ident	"@(#)nbclib:logdir.c	1.1"

/* routine to log current directory */
/* */

#ifdef MPX1X
#include <finfo.h>
#endif

#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

static int reg[8];
static int rlb[8];
static char buff[64];
static char path[PATH_MAX];
#ifdef MPX1X
static struct finfo foosave;		/* file info block save area */
#endif

/* routine to log a directory */
/* dirp is directory name pointer */
/* this must be uppercase MPX filename format */
/* opt is 0 - first time call */
/*        1 - continue with log */
/* returns ptr to file name */
/* else NULL */

char * logdir (dirp, opt)
char *dirp;
int opt;
{
    int i;
#ifdef MPX1X
    struct finfo * foo;		/* file info block pointer */
#endif

    /* see if this the first time through */
    if (opt == 0) {
      if (!(dirp != 0 && dirp != 0)) {
        errno = ENOENT;		/* set file not found error */
        return ((char *)NULL);	/* error return value */
      }

      strcpy(path, dirp);	/* make a local copy */
      unix2mpx(dirp);		/* convert to MPX path */

#ifdef MPX1X
      if ((foo = pn2fib(path)) == NULL) {
        errno = ENOENT;		/* set file not found error */
        return ((char *)NULL);	/* error return value */
      }

      /* set username for this file, save old */
      if (setuser(foo->username, foo->userkey) != NULL) {
        errno = ENOENT;		/* set file not found error */
        return ((char *)NULL);	/* error return value */
      }

      if ((strncmp((char*)foo->username, "SYSTEM  ", 8) == 0) ||
        (strncmp((char*)foo->username, "        ", 8) == 0) ||
        ((foo->username[0] == 0) && (foo->username[1] == 0)))
    	reg[4] = 2;		/* system files only */
      else
    	reg[4] = 3;		/* user files only */
      reg[5] = (int)rlb;	/* where SMD entry goes */
    }

#else /* MPX1X */

      reg[2] = (int)rlb;	/* rlb address to reg 2 */
      reg[7] = 0;		/* no cnp */
      /* set up rlb for dir log */
      rlb[0] = ((strlen(dirp) << 24) | (int)(dirp)); /* dir to log */
      rlb[1] = 0;		/* no rd to be returned */
      rlb[4] = 0;		/* assign to curr dir */
      rlb[5] = (16 << 24) | (int)buff;	/* len and addr of buf */
      rlb[6] = 0;		/* use sys fcb */
      rlb[7] = 0;		/* init return status */
    }
#endif

    /* enter here if not first time */
#ifdef MPX1X
    mpxsvc (0x1073, reg, reg);	/* m.log service */
    if (reg[5] != 0) {
      memcpy(buff, (char *)rlb, 8);	/* get the file name */
      for (i=0; ((i < 8) && (buff[i] != ' ')); i++);
      buff[i] = 0;		/* null terminate it */
      return(buff);
    }

    /* we are all done, reset username and exit */
    /* must reset username to what it before log */
    resetuser();		/* reset username to what it was */
    return ((char *)NULL);	/* return all done indicator */
#else
    while (1) {
      mpxsvc(0x2029, reg, reg);
      if (!(rlb[4] & 0x80000000))
    	break;
      for (i=0; ((i < 16) && (buff[i] != ' ')); i++);
      buff[i] = 0;
      return(buff);
    }
    return ((char *)NULL);	/* return all done indicator */
#endif
}
