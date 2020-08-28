/*~!recmsg.c*/
/* Name:  recmsg.c Part No.: _______-____r
 *
 * Copyright 1993 - J B Systems, Morrison, CO
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

#ident	"@(#)sample:recmsg.c	1.0"

#include <stdio.h>
#include <sys/types.h>
#include <psb.h>
#include <prb.h>

/*
 * message receiver for messages from server doing upcalls
 */
static struct prb prb;	/* parameter receive block */
static int usa[16];	/* message parameters */
static int msgret[2];	/* message return buf */
static int *rxb = msgret;	/* ret buffer address */
static int rxb2 = 0;	/* rxb 2nd word */

msgupint()	/* initialize message receiver address */
{
    asm (" la r7,MSGRCV");	/* message receiver address */
    asm (" svc 1,x'6b'");	/* tell MPX about us */
}

static int cmd;		/* command to execute */
static int *usaddr;	/* shared memory address */
static int count;	/* the count value */
static int usrpid;	/* pid to wakeup */

msgdummy()	/* dummy entry */
{
    int retval = 0;	/* return value */
    int errval;		/* error return value */

    asm ("MSGRCV sea");		/* entry */
    asm (" la r4,_usa");	/* receive buff addr */
    asm (" stw r4,_prb");	/* put in prb */
    asm (" li r4,4*4");		/* 4 words (max) to be returned */
    asm (" sth r4,_prb+1w");	/* set recv buff length */
    asm (" zmw _usa");		/* just for the hell of it */
    asm (" la r2,_prb");	/* parameter recv block addr */
    asm (" svc 1,x'7a'");	/* get data M.GMSGP */
    asm (" trr r6,r6");		/* test for error */
    asm (" bz MSG");		/* br if none */
    asm (" zmw _rxb2");		/* no return information */
    asm (" la r2,_rxb");	/* exit block */
    asm (" svc 1,x'5e'");	/* exit now */

    asm ("MSG la sp,stacke");	/* get a stack pointer */

process:			/* process the request */
    cmd = usa[0];		/* wakeup reason */
    usrpid = prb.tskn;		/* who called us */
    usaddr = (int *)usa[1];	/* address */
    count = usa[2];		/* set null return value */

    /* the return value is returned in the exit parameter block buffer
     */

    msgret[0] = retval;		/* set return value */
    msgret[1] = errval;		/* set errno value */
    rxb2 = 8;			/* return 8 bytes */

    asm (" la r2,_rxb");	/* exit block */
    asm (" svc 1,x'5e'");	/* exit now M.XMSGR */

    asm (" dsect");
    asm (" bound 1d");
    asm (" rez 16f");		/* .5kb stack */
    asm (" bound 1f");
    asm ("stacke rez 1w");	/* end of stack */
    asm (" rez 3f");		/* parameter space */
    asm (" csect");
}

