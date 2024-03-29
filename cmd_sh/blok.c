/*~!blok.c*/
/* Name:  blok.c Part No.: _______-____r
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

#ident	"$Id: blok.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

/* #define DEBUG */
/* #define NOTNOW */

#include	"defs.h"

/*
 *	storage allocator
 *	(circular first fit strategy)
 */

#define BUSY 01
#define busy(x)	(Rcheat((x)->word) & BUSY)

extern int error();

unsigned brkincr = BRKINCR;
struct blk *blokp;		/* current search pointer */
struct blk *bloktop;		/* top of arena (last blok) */
char *brkbegin;

char *setbrk();
void addblok();

char  *alloc(nbytes)
unsigned int nbytes;
{
    register unsigned rbytes = round(nbytes + BYTESPERWORD, BYTESPERWORD);

#ifdef smpx_MAYBENOT
    if (stakbot == 0) {
    	addblok(0);
    }
#endif
    for (; ; ) {
    	int c = 0;
    	register struct blk *p = blokp;
    	register struct blk *q;

    	do
    	 {
    	    if (!busy(p)) {
    	    	while (!busy(q = p->word))
    	    	    p->word = q->word;
    	    	if ((char *)q - (char *)p >= rbytes) {
    	    	    blokp = (struct blk *)((char *)p + rbytes);
    	    	    if (q > blokp)
    	    	    	blokp->word = p->word;
    	    	    p->word = (struct blk *)(Rcheat(blokp) | BUSY);
    	    	    return((char *)(p + 1));
    	    	}
    	    }
    	    q = p;
    	    p = (struct blk *)(Rcheat(p->word) & ~BUSY);
    	} while (p > q || (c++) == 0);
    	addblok(rbytes);
    }
}


void addblok(reqd)
unsigned int reqd;
{
    if (stakbot == 0) {
    	brkbegin = setbrk(3 * BRKINCR);
    	bloktop = (struct blk *)brkbegin;
    }

#ifdef NOTNOW
printf("addblok entered reqd = %x\n", reqd);
#endif
    if (stakbas != staktop) {
    	register char *rndstak;
    	register struct blk *blokstak;

    	pushstak(0);
    	rndstak = (char *)round(staktop, BYTESPERWORD);
    	blokstak = (struct blk *)(stakbas) - 1;
    	blokstak->word = stakbsy;
    	stakbsy = blokstak;
    	bloktop->word = (struct blk *)(Rcheat(rndstak) | BUSY);
    	bloktop = (struct blk *)(rndstak);
    }
    reqd += brkincr;
    reqd &= ~(brkincr - 1);
#ifdef NOTNOW
printf("addblok2 entered reqd = %x\n", reqd);
#endif
    if(setbrk(reqd) <= 0)error(nospace);
#ifdef NOTNOW
printf("addblok3 entered reqd = %x\n", reqd);
#endif
    blokp = bloktop;
    bloktop = bloktop->word = (struct blk *)(Rcheat(bloktop) + reqd);
/* #ifdef smpx MAYBENOT */
/*    if(setbrk(reqd) <= 0)error(nospace); */
/* #endif MAYNENOT */
    bloktop->word = (struct blk *)(brkbegin + 1);
     {
    	register char *stakadr = (char *)(bloktop + 2);

    	if (stakbot != staktop)
    	    staktop = movstr(stakbot, stakadr);
    	else
    	    staktop = stakadr;

    	stakbas = stakbot = stakadr;
    }
#ifdef DEBUG
    chkmem();
#endif
}


void free(ap)
struct blk *ap;
{
    register struct blk *p;
    	if ((p = ap) && p < bloktop) {
#ifdef DEBUG
    	    chkbptr(p);
#endif
    	    --p;
    	    p->word = (struct blk *)(Rcheat(p->word) & ~BUSY);
    	}
}


#ifdef DEBUG

void chkbptr(ptr)
struct blk *ptr;
{
    int exf = 0;
    register struct blk *p = (struct blk *)brkbegin;
    register struct blk *q;
    int us = 0, un = 0;

    for (; ; ) {
    	q = (struct blk *)(Rcheat(p->word) & ~BUSY);

    	if (p + 1 == ptr)
    	    exf++;

    	if (q < (struct blk *)brkbegin || q > bloktop)
    	    abort(3);

    	if (p == bloktop)
    	    break;

    	if (busy(p))
    	    us += q - p;
    	else
    	    un += q - p;

    	if (p >= q)
    	    abort(4);

    	p = q;
    }
    if (exf == 0)
    	abort(1);
}


void chkmem()
{
    register struct blk *p = (struct blk *)brkbegin;
    register struct blk *q;
    int us = 0, un = 0;

    for (; ; ) {
    	q = (struct blk *)(Rcheat(p->word) & ~BUSY);

    	if (q < (struct blk *)brkbegin || q > bloktop)
    	    abort(3);

    	if (p == bloktop)
    	    break;

    	if (busy(p))
    	    us += q - p;
    	else
    	    un += q - p;

    	if (p >= q)
    	    abort(4);

    	p = q;
    }

    prs("un/used/avail ");
    prn(un);
    blank();
    prn(us);
    blank();
    prn((char *)bloktop - brkbegin - (un + us));
    newline();
}

#endif

