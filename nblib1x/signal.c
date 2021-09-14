/*~!signal.c*/
/* Name:  signal.c Part No.: _______-____r
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

#ident	"@(#)nbclib:signal.c	1.2"

#include <signal.h>
#include <errno.h>

static int (*sigfun[NSIG])();	/* function address for signals */
static int abrset = 0;		/* non zero if abort receiver set */
static int brkset = 0;		/* non zero if break receiver set */
static int sigval = 0;		/* storage for signals */
static int signum;		/* storage for signal number */

int (*signal(sig, funct))()
int sig;
int (*funct)();
{
    int (*ret)();

    if (!brkset) {		/* see if we are setup yet */
    	asm(" zr r4");		/* our task */
    	asm(" zr r5");
    	asm(" li r6,3");	/* set value */
    	asm(" li r7,0");	/* to zero */
    	asm(" svc 1,x'48'");	/* set status */
    	brkset++;		/* don't do again */
    	asm(" la r7,BREAK");	/* our break routine address */
    	asm(" svc 1,x'6e'");	/* tell system about it */
    }
    if (sig <= 0 || sig > NSIG) {
    	errno = EINVAL;
    	return((int(*)())-1);		/* invalid signal number */
    }
    /* SIGINT is the break receiver interrupt */
    /* SIGKILL is the abort receiver interrupt */
    ret = sigfun[sig];		/* return old value */
    sigfun[sig] = funct;	/* set function address */
    /* test for abort receiver request */
#ifdef FIX_031394
    if (sig == SIGKILL && (!abrset) && ((int)funct > 16)) {
#else
    if ((sig == SIGKILL || sig == SIGABRT) && (!abrset) &&
      ((int)funct > 16)) {
#endif
    	asm (" la r7,ABORT");	/* get our abort receiver addr */
    	asm (" svc 1,x'60'");	/* set it to us */
    	abrset = 1;		/* so we won't do it again */
    }
    return (ret);		/* return */
}

/* abort receiver established when user requests SIGKILL
 * we will enter here 1st before calling user.
 */
static int
abrtrcv()	/* just a dummy name, we enter at ABORT */
{
    asm(" bound 1w");		/* word bound */
#ifdef FIX_031394
    asm("ABORT la sp,STKA-32F");	/* get stack pointer */
#else
    asm("ABORT la sp,STKA");	/* get stack pointer */
#endif
    asm(" sea");		/* run extended */
#ifdef FIX_031394
    if ((int)sigfun[SIGKILL] > 16)	/* see if we have a function */
    	sigfun[SIGKILL]();	/* call the user */
#else
    if ((int)sigfun[SIGABRT] > 16)	/* see if we have a function */
    	sigfun[SIGABRT]();	/* call the user */
    if ((int)sigfun[SIGABRT] != (int)sigfun[SIGKILL]) {
    	/* only call once, if user defined both to same function */
    	if ((int)sigfun[SIGKILL] > 16)	/* see if we have a function */
    	    sigfun[SIGKILL]();	/* call the user */
    }
#endif
    asm(" svc 1,x'55'");	/* never to return */
}

/* break receiver for signal functions.  The program option
 * word will be read and the signal bits processed.  If non
 * are set, we will call the user break receiver because we
 * must have got a 'real' break.  The user must read and save
 * the program option word before calling the signal routine
 * to save any options set during task activation.  The options
 * will be initially zeroed when we are connected.
 */
static int
brkrcv()
{
    asm(" bound 1w");		/* word bound */
    asm("BREAK zr r6");		/* setup for get status word */
    asm(" zr r7");
    asm(" sea");		/* run extended */
    asm(" svc 1,x'49'");	/* get status */
    asm(" stw r7,_sigval");	/* save the signals */
    asm(" la sp,STKA");		/* get stack pointer */
    /* now process the signal */
    if (sigval) {
    	signum = 1;		/* start with signal 1 */
    	while (sigval) {
    	    if(sigval & 1) {
    		/* found a signal to process */
    		asm(" zr r4");		/* our task */
    		asm(" zr r5");
    		asm(" li r6,2");	/* reset bit */
    		asm(" li r7,32");	/* bits start from left */
    		asm(" sumw r7,_signum");	/* get signal number */
    		asm(" svc 1,x'48'");	/* reset signal bit */
    		/* see if we have a function */
    		if ((int)sigfun[signum] > 16)
    		    sigfun[signum](signum);	/* call the user */
    	    }
    	    signum++;			/* next signal */
    	    sigval >>= 1;		/* next bit to test */
    	}
    } else if ((int)sigfun[SIGINT] > 16)
    	sigfun[SIGINT](SIGINT);		/* call the user */
    asm(" svc 1,x'70'");		/* exit break receiver */
}

/* just a dummy for stack definition */
static int
dummy()
{
    asm(" dsect");		/* data is in dsect */
    asm(" bound 1f");
    asm(" res 64f");		/* 2k byte stack */
    asm("STKA dequ  $");	/* bottom of stack */
    asm(" res 1f");		/* for stack bounding */
    asm("PARM res 1w");		/* parameter storage location for call */
    asm(" rez 7w");		/* just for the hell of it */
    asm(" csect");
}
