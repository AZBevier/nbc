/*~!fstat.c*/
/* Name:  fstat.c Part No.: _______-____r
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

#ident	"@(#)nbclib:fstat.c	1.0"

#include <stdio.h>

fstat(fid, sb)    /* get file status */
int     fid;      /* file number */
struct stat *sb;  /* status buffer pointer */
{

    FILE    *tid;

    if (fid < 0)return (-1);
    if (fid > _NFILE) {
        tid = (FILE *)fid;
        fid = fileno(tid);
    }
    if (fcbadr(fid) <= 0)return (-1);
    return (stat (getpath(fid), sb));   /* get file status */
}
