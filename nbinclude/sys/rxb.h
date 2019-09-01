/*~!rxb.h*/
/* Name:  rxb.h Part No.: _______-____r
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

#ifndef RXB_H
#define RXB_H

#ident	"@(#)nbinclude:rxb.h	1.1"

/* receiver exit block definitions */

struct rxb {
  char  st;     /* return status value */
                /* this value is determined by the user */
  int   rba:24; /* return parameter buffer address (word addr) */
  char  opt;    /* contains receiver exit control option value */
                /* 0 wait for next run req/exit msg receiver */
                /* 1 process next run reg or exit if none */
  char  nu;     /* not used */
  short rq;     /* number of bytes to be returned */
};
#endif
