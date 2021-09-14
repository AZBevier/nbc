/* switch.c */
/*
 * 	(c) Copyright 1986 Gould Inc.
 * 	    All Rights Reserved.
 */
 
/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */
 
#ifndef lint
static char *rcsid = "@(#) (Gould) $Header: /u/nbc/nbccom/RCS/switch.c,v 1.2 1995/01/27 23:11:22 jbev Exp $";
#endif
 
/*
 *  C compiler for Gould processors, base register instruction set.
 *
 *	Switch routines moved here for pco.
 */
 
#include <stdio.h>
#ifdef ONEPASS
#include "mfile1.h"
#else
#include "mfile2.h"
#define	branch(l)	cbgen(0,(l),0)
#endif
 
struct sw heapsw[SWITSZ];	/* heap for switches */
#ifndef ONEPASS
struct sw swtab[SWITSZ];
#endif
 
#define ISSHORT(x) ((x) <= 0x7fff &&(x) >= -32768)
 
genswitch(p, n, swreg)
register struct sw *p;
int n;
int swreg;
{
 /* p points to an array of structures, each consisting 
  * of a constant value and a label. The first is >=0 if there
  * is a default label; its value is the label number 
  * The entries p[1] to p[n] are the nontrivial cases 
  */
    register    i;
    register CONSZ  j, range;
    register    dlab, swlab;
 
    range = p[n].sval - p[1].sval;
 
#ifndef BUG1
    if(tdebug) {
	printf("genswitch(p=0x%x. m=0x%x)  range=%d\n", p, n, range);
    }
#endif
 
    /* implement a direct switch */
    if (range > 0 && range <= 3 * n && n >= 4) {
 
#ifndef BUG1
	if(tdebug) {
		printf("genswitch(): doing direct (indexed) switch\n");
	}
#endif
 
	swlab = get2lab();
	dlab = p -> slab >= 0 ? p -> slab : get2lab();
 
	/* Value for condition is in Return register on each system */
	printf ("	sll	r%d,2\n",callreg(p));	/* maybe c2 can fix */
 
	if (p[1].sval) {
 
 /* already in callreg(p) because of FORCE */
	    if (ISSHORT (p[1].sval * 4))
		printf ("	sui	r%d,%d\n", callreg(p), p[1].sval * 4);
	    else
		printf ("	sumw	r%d,=x'%x'\n", callreg(p), p[1].sval * 4);
	}
 
	else {
	    printf ("	trr	r%d,r%d\n", callreg(p), callreg(p));
	}
 
	printf("\tblt	L%d\n\tci	r%d,%d\n\tbgt	L%d\n",
		dlab, callreg(p), range * 4, dlab);
/*	printf("\ttrr	r%d,r%d\n\tbu	*L%d,r%d\nL%d\tequ\t$\n", */
	printf("\ttrr	r%d,r%d\n\tbu	*L%d,r%d\nL%d\tcequ\t$\n",
		callreg(p), callreg(p) + 1, swlab, callreg(p) + 1,
		swlab);
    	/* 
    	 * make table here. put in defaults
    	 */
	for (i = 1, j = p[1].sval; i <= n; j++) {
	    printf("	dataw	L%d\n",
	      (j == p[i].sval ? ((j = p[i++].sval), p[i - 1].slab) : dlab));
	}
 
	if (p -> slab >= 0)
	    printf("	dataw	L%d\n", dlab);
	    /* branch(dlab); */
	else
	    deflab (dlab);
	return;
 
    }
 
    if (n > 8) {		/* heap switch */
#ifndef BUG1
	if(tdebug) {
		printf("genswitch(): doing heap switch\n");
	}
#endif
 
	heapsw[0].slab = dlab = p -> slab >= 0 ? p -> slab : get2lab();
	makeheap(p, n, 1);	/* build heap */
 
	walkheap(1, n);		/* produce code */
 
	if (p -> slab >= 0)
	    branch(dlab);
	else
	    deflab (dlab);
	return;
    }
 
#ifndef BUG1
 /* debugging code */
 
    if(tdebug) {
 	printf( "genswitch(): if/else switch: n=%d, range/n=%d\n",
		n, (int) (range/n) );
	if( n >= 4)
		printf("inefficient.\n");
    }
#endif
 
 /* simple switch code */
 
    for (i = 1; i <= n; ++i) {
#ifndef JUNK
	if (ISSHORT(p[i].sval))
#else
	if ((p[i].sval) <= 0x7fff && (p[i].sval) >= -32868)
#endif
	    printf ("	ci	r%d,%d\n", callreg(p), p[i].sval);
	else
	    printf ("	camw	r%d,=n'%d'\n", callreg(p), p[i].sval);
	printf("	beq	L%d\n", p[i].slab);
    }
 
    if (p -> slab >= 0)
	branch(p -> slab);
}
 
makeheap(p, m, n)
register struct sw *p;
{
    register int    q;
 
#ifndef BUG1
    if(tdebug) {
	printf("makeheap(p=0x%x, m=%d, n=%d):\n", p, m, n);
    }
#endif
    q = select(m);
    heapsw[n] = p[q];
    if (q > 1)
	makeheap(p, q - 1, 2 * n);
    if (q < m)
	makeheap(p + q, m - q, 2 * n + 1);
#ifndef BUG1
    if(tdebug) {
	printf("makeheap(p=0x%x, m=%d, n=%d) returning\n", p, m, n);
    }
#endif
}
 
select(m)
{
    register int    l, i, k;
    register v;
 
    for (i = 1;; i <<= 1)
	if ((i - 1) > m)
	    break;
    l = ((k = i / 2 - 1) + 1) / 2;
    v = (l + (m - k < l ? m - k : l));
#ifndef BUG1
    if(tdebug) {
	printf("select(m=%d) returning %d\n", m, v);
    }
#endif
    return(v);
}
 
walkheap(start, limit)
{
    int         label;
 
 
#ifndef BUG1
    if(tdebug) {
	printf("walkheap(start=%d, limit=%d):\n", start, limit);
    }
#endif
 
    if (start > limit)
	return;
    if (ISSHORT(heapsw[start].sval))
	printf("	ci	r%d,%d\n", callreg(p), heapsw[start].sval);
    else
	printf("	camw	r%d,=n'%d'\n", callreg(p), heapsw[start].sval);
    printf("	beq	L%d\n", heapsw[start].slab);
    if ((2 * start) > limit) {
	branch(heapsw[0].slab);
	return;
    }
    if ((2 * start + 1) <= limit) {
	label = get2lab();
	printf("	bgt	L%d\n", label);
    }
    else
	printf("	bgt	L%d\n", heapsw[0].slab);
    walkheap(2 * start, limit);
    if ((2 * start + 1) <= limit) {
	deflab (label);
	walkheap(2 * start + 1, limit);
    }
}
 
/*
 * 	(c) Copyright 1986 Gould Inc.
 * 	    All Rights Reserved.
 */
