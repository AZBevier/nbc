/*~!prb.h*/
/* Name:  prb.h Part No.: _______-____r
 *
 * Copyright 1991 - J B Systems, Morrison, CO.
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

#ifndef PRB_H
#define PRB_H

#ident	"@(#)nbinclude:prb.h	1.1"

/* parameter receive block definitions */

struct prb {
  char  st;     /* completion status value */
                /* 0 normal status */
                /* 1 invalid prb address */
                /* 2 invalid receive buf address or size */
                /* 3 no active send request */
                /* 4 receive buffer length exceeded */
  int   rba:24; /* return buffer address (word addr) */
  short rbl;    /* receive buff length (bytes) */
  short arq;    /* number of bytes received */
  char  own[8]; /* owner name of sending task */
  int   tskn;   /* task number of sending task */
};
#endif
