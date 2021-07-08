/*~!setbrk.c*/
/* Name:  setbrk.c Part No.: _______-____r
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

#ident	"$Id: setbrk.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

/* #define NOTNOW */

#include	"defs.h"
#ifndef mpx
#include <stdlib.h>
#endif

static char *xsbrk();

char *setbrk(incr)
int incr;
{
    register char *a = xsbrk(incr);
#ifdef NOTNOW
printf("setbrk: incr = %x, a = %x, brkend = %x\n", incr, a, brkend);
#endif

    brkend = a + incr;
    return(a);
}

/*#ifdef mpx */
#include <errno.h>

static char *sos = 0;		/* start of space */
static char *eas = 0;		/* end of space */
static char *ceas = 0;		/* current end of space */

static char *xsbrk(incr)	/* allocate incr more storage */
int incr;
{
    char *neweas, *oldeas;

#ifdef NOTNOW
printf("sbrk entered, incr = %x, ceas = %x\n", incr, ceas);
#endif
    if (sos == 0) {		/* no memory yet, get some */
    	if ((sos = (char *)calloc(8, BRKMAX)) == 0) {
    	    errno = ENOMEM;
    	    return((char *)(-1));
    	}
    	eas = sos + 8*BRKMAX;	/* set end address */
    	ceas = sos;		/* set current end to start */
#ifdef NOTNOW
printf("sbrk0: incr = %x, sos = %x, neweas = %x, eas = %x\n", incr, sos, neweas, eas);
#endif
    }
    oldeas = ceas;		/* save ceas to be returned */
#ifdef NOTNOW
printf("sbrk: incr(%x) sos(%x) neweas(%x) ceas(%x) eas(%x)\n",
 incr, sos, neweas, ceas, eas);
#endif
    if (incr != 0) {
    	neweas = ceas + incr;	/* shift pointer incr amount */
    	if (neweas > eas) {
    	    errno = ENOMEM;
    	    return((char *)(-1));
    	}
    	ceas = neweas;		/* set new current end address */
#ifdef NOTNOW
printf("sbrk: incr(%x) sos(%x) neweas(%x) ceas(%x) eas(%x)\n",
 incr, sos, neweas, ceas, eas);
#endif
    }
    return(oldeas);		/* return old pointer */
}
/*#endif */

