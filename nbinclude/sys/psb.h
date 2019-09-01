/*~!psb.h*/
/* Name:  psb.h Part No.: _______-____r
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

#ifndef PSB_H
#define PSB_H

#ident	"@(#)nbinclude:psb.h	1.0"

/* parameter send block definitions */

struct psb {
  int   lmn;    /* load module name 1st 4 char or task num */
  int   pnv;    /* 2nd 4 char of lmn or path name vector */
  char  pri;    /* priority */
  char  nub;    /* not used byte */
  short squa;   /* number of bytes to send */
  int   *sba;   /* send buffer address (word addr) */
  short rpbl;   /* return parameter buff length (bytes) */
  short acrp;   /* actual num of bytes returned */
  int   *rba;   /* return buffer address (word addr) */
  int   *eaa;   /* no-wait request end action address */
  char  cst;    /* completion status */
                /* bit 0 - operation in progress */
                /* bit 1 - dest task was aborted before completion */
                /* bit 2 - dest task was deleted before completion */
                /* bit 3 - ret params truncated */
                /* bit 4 - send parameters truncated */
                /* bit 5 - user end action rtn not xeq'd */
                /* bit 6 - not used */
                /* bit 7 - not used */
  char  ist;    /* processing start status value */
                /*  0 normal initial status */
                /*  1 message reg task num invalid */
                /*  2 run req load modual not found */
                /*  3 not used */
                /*  4 file name not valid load module */
                /*  5 dqe space unavailable */
                /*  6 directory i/o read error */
                /*  7 file i/o read error */
                /*  8 memory unavailable */
                /*  9 invalid task num for run req */
                /* 10 invalid priority specification */
                /* 11 invalid send buffer address or size */
                /* 12 invalid return buffer address or size */
                /* 13 invalid end action address */
                /* 14 memory pool unavailable */
                /* 15 dest task receiver queue full */
                /* 16 invalid psb address */
  char  ust;    /* user status returned (user defined) */
  char  opt;    /* options */
                /* bit 0 - request is to be issued in no-wait mode */
                /* bit 1 - request is to be issued in no call-back mode */
};
#endif
