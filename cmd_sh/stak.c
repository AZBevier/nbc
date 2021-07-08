/*~!stak.c*/
/* Name:  stak.c Part No.: _______-____r
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

#ident	"$Id: stak.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

/* #define NOTNOW */

#include	"defs.h"

extern char *setbrk();

extern void free();
extern void rmtemp();

extern int error();

/* ========	storage allocation	======== */
char *getstak(asize)			/* allocate requested stack */
int asize;
{
    register char *oldstak;
    register int size;

#ifdef NOTNOW
printf("getstak: entry, asize = %x, stackbot = %x\n", asize, stakbot);
#endif
    size = round(asize, BYTESPERWORD);
    oldstak = stakbot;
    staktop = stakbot += size;
#ifdef NOTNOW
printf("getstak: return, staktop = %x, stackbot = %x, oldstak = %x\n",
 staktop, stakbot, oldstak);
#endif
    return(oldstak);
}


/*
 * set up stack for local use
 * should be followed by `endstak'
 */
char *locstak()
{
    if (brkend - stakbot < BRKINCR) {
    	if (setbrk(brkincr) == (char *)(-1))
    	    error(nostack);
    	if (brkincr < BRKMAX)
    	    brkincr += 256;
    }
    return(stakbot);
}


char *savstak()
{
#ifdef NOTNOW
printf("savstak: entry\n");
#endif
    assert(staktop == stakbot);
#ifdef NOTNOW
printf("savstak: exit, stackbot = %x\n", stakbot);
#endif
    return(stakbot);
}


char *endstak(argp)		/* tidy up after `locstak' */
register char *argp;
{
    register char *oldstak;

    *argp++ = 0;
    oldstak = stakbot;
    stakbot = staktop = (char *)round(argp, BYTESPERWORD);
#ifdef NOTNOW
printf("endstak: exit, stackbot = %x, oldstak = %x\n", stakbot, oldstak);
#endif
    return(oldstak);
}


void tdystak(x)		/* try to bring stack back to x */
register char *x;
{
    while ((char *)(stakbsy) > (char *)(x)) {
    	free(stakbsy);
    	stakbsy = stakbsy->word;
    }
    staktop = stakbot = max((char *)(x), (char *)(stakbas));
    rmtemp(x);
}


void stakchk()
{
    if ((brkend - stakbas) > BRKINCR + BRKINCR)
    	setbrk(-BRKINCR);
}


char *cpystak(x)
char *x;
{
    return(endstak(movstr(x, locstak())));
}


