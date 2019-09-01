/*~!kill.c*/
/* Name:  kill.c Part No.: _______-____r
 *
 * Copyright 1991 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:kill.c	1.1"

/* this routine shows how to call MPX for both 1X and 3X.  MPX.1X
 * does not like varibles for SVC calls to be in extended memory.
 * They must be in DSECT.  Notice use of function and inline assembler
 * to make the calls.
 */

#include <errno.h>
#include <signal.h>

static int tid;
static int signum;
#ifdef MPX1X						
static int param[12];		/* parameter return */
#endif				

/* this is the UNIX kill function, not the MPX kill call */

kill(pid,sig)      /* kill task or test for presence */
int pid, sig;
{

    int i;
    int reg[8];
#ifndef MPX1X					
    int param[12];		/* parameter return */	
#endif						

    if (sig < 0 || sig >= NSIG) {	/* see if valid signal number */
    	errno=EINVAL;		/* set error number */
    	return(-1);		/* indicate not found */
    }
    reg[5]=0;			/* 1st time call */
    reg[7] = (int)param;	/* parameter block address */
    param[0]=pid;		/* search for process id */
    for (i=1; i<8; i++)		/* clear rest of parameter block */
    	param[i]=0;
    mpxsvc(0x1064,reg,reg);	/* call m.id service */
    if(reg[5] == 0) {		/* return error if not found */
    	errno=ESRCH;		/* set error number */
    	return(-1);		/* indicate not found */
    }
    if (sig == 0)		/* if just a test, return o.k. */
    	return (0);

    /* send the signal to the specified task */
    /* copy parameters to statics (DSECT) */
    tid = pid;
    signum = sig;
    
    asm(" zr r4");		/* task to signal */
    asm(" lw r5,_tid");
    asm(" li r6,1");		/* set bit for signal */
    asm(" li r7,32");		/* bits start from left */
    asm(" sumw r7,_signum");	/* get signal number */
    asm(" svc 1,x'48'");	/* set signal bit */
    asm(" zr r6");		/* task to signal */
    asm(" lw r7,_tid");
    asm(" svc 1,x'6f'");	/* send signal */
    return (0);			/* all o.k. */
}
