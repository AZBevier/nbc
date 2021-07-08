/*~!fault.c*/
/* Name:  fault.c Part No.: _______-____r
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

#ident	"$Id: fault.c,v 1.3 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#define NOTNOW

#include	"defs.h"
#include	<signal.h>
#include	<stdio.h>

extern int error();

extern char *setbrk();

extern void	free();
extern void	done();
extern void	failed();
extern void	execexp();

void setsig();
void clrsig();
int ignsig();

char *trapcom[MAXTRAP];
BOOL	trapflg[MAXTRAP] = 
{
    0,
    0, 	/* hangup */
    0, 	/* interrupt */
    0, 	/* quit */
    0, 	/* illegal instr */
    0, 	/* trace trap */
    0, 	/* IOT */
    0, 	/* EMT */
    0, 	/* float pt. exp */
    0, 	/* kill */
    0, 	/* bus error */
    0, 	/* memory faults */
    0, 	/* bad sys call */
    0, 	/* bad pipe call */
    0, 	/* alarm */
    0, 	/* software termination */
    0, 	/* unassigned */
    0, 	/* unassigned */
    0, 	/* death of child (if not BSD) */
    0, 	/* power fail */
};


void 	(*(sigval[MAXTRAP]))() = {
    0,
    done,
    fault,
    fault,
    done,
    done,
    done,
    done,
    done,
    0,
    done,
    done,
    done,
    done,
    fault,
    fault,
    done,
    done,
    done,
    done,
};


/* ========	fault handling routines	   ======== */


void fault(sig)
register int sig;
{
    register int flag;

#ifdef NOTNOW
printf("fault entered\n");
#endif
    signal(sig, fault);
    if (sig == SIGSEGV) {
    	if (setbrk(brkincr) == (char *)(-1)) {
printf("fault entered, got no space\n");
    	    error(nospace);
    	}
    } else if (sig == SIGALRM) {
    	if (flags & waiting) {
    	    done();
    	}
    } else {
    	flag = (trapcom[sig] ? TRAPSET : SIGSET);
    	trapnote |= flag;
    	trapflg[sig] |= flag;
    	if (sig == SIGINT)
    	    wasintr++;
    }
}


void stdsigs()
{
    setsig(SIGHUP);
    setsig(SIGINT);
    ignsig(SIGQUIT);
    setsig(SIGILL);
    setsig(SIGTRAP);
    setsig(SIGIOT);
#ifdef linux
    setsig(SIGBUS);
#else
    setsig(SIGEMT);
#endif
    setsig(SIGFPE);
#ifdef linux
    setsig(SIGKILL);
#else
    setsig(SIGBUS);
#endif
    signal(SIGSEGV, fault);
#ifdef linux
    setsig(SIGUSR2);
#else
    setsig(SIGSYS);
#endif
    setsig(SIGPIPE);
    setsig(SIGALRM);
    setsig(SIGTERM);
    setsig(SIGUSR1);
}


int ignsig(n)
int n;
{
    register int s, i;

    if ((i = n) == SIGSEGV) {
    	clrsig(i);
    	failed(badtrap, no11trap);
    } else if ((s = (int)(signal(i, SIG_IGN) == SIG_IGN)) == 0) {
    	trapflg[i] |= SIGMOD;
    }
    return(s);
}


void getsig(n)
int n;
{
    register int i;

    if (trapflg[i = n] & SIGMOD || ignsig(i) == 0)
    	signal(i, fault);
}


void setsig(n)
int n;
{
    register int i;

    if (ignsig(i = n) == 0)
    	signal(i, sigval[i]);
}


void oldsigs()
{
    register int i;
    register char *t;

    i = MAXTRAP;
    while (i--) {
    	t = trapcom[i];
    	if (t == 0 || *t)
    	    clrsig(i);
    	trapflg[i] = 0;
    }
    trapnote = 0;
}


void clrsig(i)
int i;
{
    free(trapcom[i]);
    trapcom[i] = 0;
    if (trapflg[i] & SIGMOD) {
    	trapflg[i] &= ~SIGMOD;
    	signal(i, sigval[i]);
    }
}


/*
 * check for traps
 */
void chktrap()
{
    register int i = MAXTRAP;
    register char *t;

    trapnote &= ~TRAPSET;
    while (--i) {
    	if (trapflg[i] & TRAPSET) {
    	    trapflg[i] &= ~TRAPSET;
    	    if (t = trapcom[i]) {
    	    	int savxit = exitval;

    	    	execexp(t, 0);
    	    	exitval = savxit;
    	    	exitset();
    	    }
    	}
    }
}

