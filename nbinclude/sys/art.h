/*~!art.h*/
/* Name:  art.h Part No.: _______-____r
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

#ifndef ART_H
#define ART_H

#ident	"@(#)nbinclude:art.h	1.1"

typedef struct art {  /* ART structure */

/*** word 0 ***/
    char *block;  /* bits   0-7; udt index */
                  /* bits  8-31; resource descriptor block addr */

/*** word 1 ***/
    int  caccm;   /* access mode and table pointer */
/*     read  bit  0;     read access */
/*     write      1;     write access */
/*     modfy      2;     modify access */
/*     updat      3;     update access */
/*     appdn      4;     append access */
/*     unused   5-7;     reserved unused bits */
/*     mvta    8-31;     mounted volume table entry pointer */
/*     nblks             or number of blocks in segment definition */
/*     smta              or shared memory table entry address */
/*     udta              or unit definition table entry pointer */

/*** word 2 ***/
    short flags;    /* resource allocation flags */
/*     exshr bit  0;     explicit shared use */
/*     imshr      1;     implicit shared use */
/*     mnt        2;     allocated as mount device */
/*     delet      3;     resource marked for deletion */
/*     space      4;     space definition */
/*     part       5;     memory partition */
/*     devc       6;     device */
/*     actv       7;     this art entry active */
/*     trunc      8;     resource marked for truncation */
/*     unused  9-11;     reserved */
/*     dplk      12;     dual processor lock in effect */
/*     wown      13;     dp resource being written by this processor */
/*     dualp     14;     resource treated as dual processor */
/*     port      15;     port designation for dp resource lock owner */

    char xrl;      /* dqe index of exclusive lock owner */
    char srl;      /* dqe index of synchronous lock owner */

/*** word 3 ***/
    char assns;    /* number of active assignments */
    char users;    /* number of users/allocations of resource */
    char que;      /* number of dual processor requests queued */
    char rdrs;     /* number of readers currently on this resource */

/*** word 4 ***/
    int eof;       /* current EOF position in this file */

/*** word 5 ***/
    int eom;       /* current EOM position in this file */

/*** word 6 ***/
    char mpid;     /* port number of multiport resource lock owner */
    char ldqe;     /* dqe index of task locking a multiport resource */
    short rcnt;    /* resource reserve count */

/*** word 7 ***/
    int rwd;       /* reserved word */

} ;
#endif
