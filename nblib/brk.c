/*~!brk.c*/
/* Name:  brk.c Part No.: _______-____r
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

#ident	"@(#)nbclib:brk.c	1.0"

#include <errno.h>

#define GET 0x1067
#define FREE 0x1068
extern char *eas;     /* pointer  to current end of address */
extern int blksize;   /* block size */

brk(neweas)               /* set new end of address space point */
char  *neweas;
{
    int  delta, oldlim, newlim, i;
    int reg[8],service;
    char *nmb;

    oldlim = (int)eas;
    newlim = (int)neweas;
    delta = (oldlim-1)/blksize - (newlim-1)/blksize;  /* find new blk */
    service = ( (delta < 0) ? GET : FREE);

/*    ascertain if stack is in extended memory. If so, use the extended
      data space get and free services       */

    if ((int)&service > 0x80000) service += 2;

    for (i=0; i<abs(delta); i++) {

      mpxsvc(service,reg,reg);
      if ( (char *)reg[3] == 0) {
        errno = ENOMEM;
        return(-1);
      }

      if (delta < 0) {
      register double * mapp = (double *)reg[3];
      register double * mape = (double *)reg[4];

      while((int)mapp < (int)mape)*mapp++ = 0;
      }
    }
    eas = neweas;         /* set new pointer */
    return(0);
}
