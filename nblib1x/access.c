/*~!access.c*/
/* Name:  access.c Part No.: _______-____r
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

#ident	"@(#)nbclib:access.c	1.0"

#include <types.h>
#include <limits.h>
#include <errno.h>
#include <stat.h>

int
access(pname,amode)	/* determine file accessability */
char *pname;
int amode;
{
    struct stat sb;	/* status buffer */

    if (stat (pname, &sb) != 0)
      return(-1);	/* errno already set */
    if (amode == 0)
      return (0);	/* just checking for existance */
    /* someday we should check correct bits in st_mode for
     * owner, project, and other to see if correct access
     */
    return(0);		/* assume all accesses for now */
}
