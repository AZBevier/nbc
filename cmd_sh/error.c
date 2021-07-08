/*~!error.c*/
/* Name:  error.c Part No.: _______-____r
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

#ident	"$Id: error.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

/* #define NOTNOW */

#include	"defs.h"
#ifndef mpx
#include <stdlib.h>
/*#include <unistd.h>*/
#endif

void rmfunctmp();
void exitsh();

extern void execexp();
extern void clear_buff();
extern void makearg();
extern void unlink();
extern void rmtemp();
extern void free();
extern void chktrap();
extern void clearup();
extern void restore();
extern void prc();
extern void prs();
extern void prp();
extern void prs_cntl();
extern int expand();

/* ========	error handling	======== */

void failed(s1, s2)
char *s1, *s2;
{
    prp();
    prs_cntl(s1);
    if (s2) {
    	prs(colon);
    	prs(s2);
    }
    newline();
#ifdef NOTNOW
printf("failed: calling exitsh exitval = %x\n", (int)ERROR);
#endif
    exitsh(ERROR);
}


void error(s)
char *s;
{
    failed(s, NIL);
}


void exitsh(xno)
int xno;
{
    /*
     * Arrive here from `FATAL' errors
     *  a) exit command,
     *  b) default trap,
     *  c) fault with no trap set.
     *
     * Action is to return to command level or exit.
     */
#ifdef NOTNOW
printf("exitsh xno = %x\n", xno);
#endif
    exitval = xno;
    flags |= eflag;
    if ((flags & (forked | errflg | ttyflg)) != ttyflg) {
#ifdef NOTNOW
printf("exitsh doing done\n");
#endif
    	done();
    } else
     {
    	clearup();
    	restore(0);
    	clear_buff();
    	execbrk = breakcnt = funcnt = 0;
#ifdef NOTNOW
printf("exitsh doing longjump\n");
#endif
    	longjmp(errshell, 1);
    }
}

static int bnhere;

void done()
{
    register char *t;

#ifdef NOTNOW
printf("done: entry exitval = %x, bnhere = %x\n", exitval, bnhere);
#endif
    if(bnhere++)return;

    if (t = trapcom[0]) {
    	trapcom[0] = 0;
    	execexp(t, 0);
    	free(t);
    } else
    	chktrap();

    rmtemp(0);
    rmfunctmp();

#ifdef NOTNOW
printf("done: calling exit exitval = %x\n", exitval);
#endif
    exit(exitval);
}


void rmtemp(base)
struct ionod *base;
{
    while (iotemp > base) {
    	unlink(iotemp->ioname);
    	free(iotemp->iolink);
    	iotemp = iotemp->iolst;
    }
}


void rmfunctmp()
{
    while (fiotemp) {
    	unlink(fiotemp->ioname);
    	fiotemp = fiotemp->iolst;
    }
}

