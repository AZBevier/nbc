/* common.h */
/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */
 
#ifndef COMMON_H
#define COMMON_H
#endif
 
/*	@(#) (Gould) $Header: /u/nbc/nbccom/RCS/common.h,v 1.2 1995/01/30 19:36:03 jbev Exp $		  */
 
/* 
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/
 
/*
 	The items in this file have been moved to the respective
	include files below for the pco port.
*/
 
extern char *malloc(), *mymalloc();
 
int	lflag;
 
#ifndef FORT
ispow2 (c) CONSZ c;
{
    register    i;
    if (c <= 0 || (c & (c - 1)))
	return (-1);
    for (i = 0; c > 1; ++i)
	c  = (unsigned)c >> 1;
    return (i);
}
#endif
 
char *
malloc(amt)
int amt;
{
#ifdef MPX /* MAR25 */
#ifdef TEST
	char * sp;
	register int	i;
#else
	register double *sp;
	register m;
#endif
#endif
	char *rv;
	int failcount = 0;
 
	rv = mymalloc(amt);
#ifdef JUNKJUNK
	while( (int) rv <= 0 ) {
		failcount += 1;
		sleep(5);
		rv = mymalloc(amt);
	}
#endif
#ifdef MPX /* MAR25 */
#ifdef TEST
	for (sp = rv, i=0; i < amt; i++)*sp++ = 0;
#else
	sp = (double *)rv;
        m = (amt + sizeof(double)-1)/sizeof(double);
        while (--m >= 0)*sp++ = 0;
#endif
#endif
	return(rv);
}
 
#ifdef debug
#define ASSERT(p) if(!(p))botch("p");else
botch(s)
char *s;
{
	printf("assertion botched: %s\n",s);
	abort();
}
#else
#define ASSERT(p)
#endif
 
/*	avoid break bug */
#define GRANULE 0
 
/*	C storage allocator
 *	circular first-fit strategy
 *	works with noncontiguous, but monotonically linked, arena
 *	each block is preceded by a ptr to the (pointer of) 
 *	the next following block
 *	blocks are exact number of words long 
 *	aligned to the data type requirements of ALIGN
 *	pointers to blocks must have BUSY bit 0
 *	bit in ptr is 1 for busy, 0 for idle
 *	gaps in arena are merely noted as busy blocks
 *	last block of arena (pointed to by alloct) is empty and
 *	has a pointer to first
 *	idle blocks are coalesced during space search
 *
 *	a different implementation may need to redefine
 *	ALIGN, NALIGN, BLOCK, BUSY, int
 *	where int is integer type to which a pointer can be cast
*/
 
#ifdef gould
/*
 *  GOULD:  for GOULD hardware, always align memory on doubleword boundaries
 */ 
#define ALIGN double
#else /* NOT gould */
#ifdef MPX /* gould may not be defined */
#define ALIGN double
#else /* not MPX */
/*#define ALIGN int */
#define ALIGN double
#endif /* MPX */
#endif	
 
#define NALIGN 1
#define WORD sizeof(union store)
#define BLOCK 1024	/* a multiple of WORD*/
#define BUSY 1
#ifndef NULL
#define NULL 0
#endif
#define testbusy(p) ((int)(p)&BUSY)
#define setbusy(p) (union store *)((int)(p)|BUSY)
#define clearbusy(p) (union store *)((int)(p)&~BUSY)
 
union store { union store *ptr;
	      ALIGN dummy[NALIGN];
	      int calloc;	/*calloc clears an array of integers*/
};
 
static	union store allocs[2];	/*initial arena*/
static	union store *allocp;	/*search ptr*/
static	union store *alloct;	/*arena top*/
static	union store *allocx;	/*for benefit of realloc*/
char	*sbrk();
 
#ifdef JUNK
static mcallcnt = 0;	/* Force failures to test fake malloc() */
#endif
 
char *
mymalloc(nbytes)
unsigned nbytes;
{
	register union store *p, *q;
	register nw;
	static temp;	/*coroutines assume no auto*/
 
 
	if(allocs[0].ptr==0) {	/*first time*/
		allocs[0].ptr = setbusy(&allocs[1]);
		allocs[1].ptr = setbusy(&allocs[0]);
		alloct = &allocs[1];
		allocp = &allocs[0];
	}
	nw = (nbytes+WORD+WORD-1)/WORD;
	ASSERT(allocp>=allocs && allocp<=alloct);
	ASSERT(allock());
	for(p=allocp; ; ) {
		for(temp=0; ; ) {
			if(!testbusy(p->ptr)) {
				while(!testbusy((q=p->ptr)->ptr)) {
					ASSERT(q>p&&q<alloct);
					p->ptr = q->ptr;
				}
				if(q>=p+nw && p+nw>=p)
					goto found;
			}
			q = p;
			p = clearbusy(p->ptr);
			if(p>q)
				ASSERT(p<=alloct);
			else if(q!=alloct || p!=allocs) {
				ASSERT(q==alloct&&p==allocs);
				return(NULL);
			} else if(++temp>1)
				break;
		}
		temp = ((nw+BLOCK/WORD)/(BLOCK/WORD))*(BLOCK/WORD);
		q = (union store *)sbrk(0);
		if(q+temp+GRANULE < q) {
			return(NULL);
		}
		q = (union store *)sbrk(temp*WORD);
		if((int)q == -1) {
			return(NULL);
		}
		ASSERT(q>alloct);
		alloct->ptr = q;
		if(q!=alloct+1)
			alloct->ptr = setbusy(alloct->ptr);
		alloct = q->ptr = q+temp-1;
		alloct->ptr = setbusy(allocs);
	}
found:
	allocp = p + nw;
	ASSERT(allocp<=alloct);
	if(q>allocp) {
		allocx = allocp->ptr;
		allocp->ptr = p->ptr;
	}
	p->ptr = setbusy(allocp);
	return((char *)(p+1));
}
 
/*	freeing strategy tuned for LIFO allocation
*/
free(ap)
register char *ap;
{
	register union store *p = (union store *)ap;
 
#ifndef LNX
	if(ap == 0) return;
#endif
	ASSERT(p>clearbusy(allocs[1].ptr)&&p<=alloct);
	ASSERT(allock());
	allocp = --p;
	ASSERT(testbusy(p->ptr));
	p->ptr = clearbusy(p->ptr);
	ASSERT(p->ptr > allocp && p->ptr <= alloct);
}
 
#ifdef MPX
putenv(x)
char *x;
{
}
#endif
 
#ifdef JUNK_NOTUSED
/*	realloc(p, nbytes) reallocates a block obtained from malloc()
 *	and freed since last call of malloc()
 *	to have new size nbytes, and old content
 *	returns new location, or 0 on failure
*/
 
char *
realloc(p, nbytes)
register union store *p;
unsigned nbytes;
{
	register union store *q;
	union store *s, *t;
	register unsigned nw;
	unsigned onw;
 
	if(testbusy(p[-1].ptr))
		free((char *)p);
	onw = p[-1].ptr - p;
	q = (union store *)malloc(nbytes);
	if(q==NULL || q==p)
		return((char *)q);
	s = p;
	t = q;
	nw = (nbytes+WORD-1)/WORD;
	if(nw<onw)
		onw = nw;
	while(onw--!=0)
		*t++ = *s++;
	if(q<p && q+nw>=p)
		(q+(q+nw-p))->ptr = allocx;
	return((char *)q);
}
#endif /* JUNK_NOTUSED */
 
#ifdef debug
allock()
{
#ifdef longdebug
	register union store *p;
	int x;
	x = 0;
	for(p= &allocs[0]; clearbusy(p->ptr) > p; p=clearbusy(p->ptr)) {
		if(p==allocp)
			x++;
	}
	ASSERT(p==alloct);
	return(x==1|p==allocp);
#else
	return(1);
#endif
}
#endif
 
#include "error.h"
#include "treewalk.h"
#include "opdesc.h"
#include "caloff.h"
#include "treemgr.h"
 
/*
 * 	(c) Copyright 1986 Gould Inc.
 * 	    All Rights Reserved.
 */
