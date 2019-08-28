/*~!chdir.c*/
/* Name:  chdir.c Part No.: _______-____r
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

#ident	"@(#)nbclib:chdir.c	1.1"

#include <limits.h>
#include <errno.h>
#ifdef MPX1X
#include <finfo.h>
#endif

/* change directory to the path specified */
/* for 1X, this is really the username command */

chdir(path)
char *path;
{
    int reg[8], cc;
    char mpath[PATH_MAX];
#ifdef MPX1X
    struct finfo *foo;
#endif

    strcpy(mpath, path);
    unix2mpx(mpath);

#ifdef MPX1X
    if ((foo = pn2fib(mpath)) == NULL) {
      errno = ENOTDIR;		/* set dir not found error */
      return(-1);		/* error return value */
    }

    /* set username for this file */
    if (setuser(foo->username, foo->userkey) != NULL) {
      errno = ENOTDIR;		/* set dir not found error */
      return(-1);		/* error return value */
    }

#else

    reg[1] = (strlen(mpath)<<24) | (int)  (mpath);
    reg[4] = 0;		/* no project change  */
    reg[5] = 0;		/* no key */
    reg[7] = 0;		/* no cnp */
    cc = mpxsvc(0x2027, reg, reg);
    if (reg[7] != 0 ) {
      switch(reg[7]) {
    	case 1:
    	  errno = ENOTDIR;
    	  break;
    	case 4:
    	case 7:
    	default:
    	  errno = ENOENT;
    	  break;
    	case 28:
    	  errno = EACCES;
    	  break;
      }
      return (-1) ;
    }
#endif
    /* now update the current volume and directory */
    getcwvd();		/* get updated info */
    return (0);
}
