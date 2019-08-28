/* mac2defs.h */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

/* $Header: /bulk2/simhv/nbc-master/nbccom/RCS/mac2defs.h,v 1.3 2019/01/31 21:51:27 jbev Exp $ */

/*
 * $Log: mac2defs.h,v $
 * Revision 1.3  2019/01/31 21:51:27  jbev
 * Update for Linux
 *
 * Revision 1.2  1996/03/22 00:05:49  jbev
 * Cleanup for Alpha port.
 *
 */

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

 /* Register name definitions have been moved to macdefs.h */

extern int  fregs;
extern int  maxargs;

#define BYTEOFF(x) ((x) & 03)
#define wdal(k) (BYTEOFF (k) == 0)
#define BITOOR(x) ((x) >> 3)	/* bit offset to oreg offset */

#ifndef REGSZ
#ifdef MPX
#define REGSZ 12		/* also defined in macdefs.h */
#else
#define REGSZ 19		/* also defined in macdefs.h */
#endif
#endif

/* may want this to be TP for MPX */
#ifdef MPX
#define TMPREG FP
#else
#define TMPREG FP
#endif

#ifndef MPX	/* no double indexing on MPX */
#define R2REGS 	/* permit double indexing */
#endif /* MPX */

#define STOARG(p) /* just evaluate the arguments, and be done with it... */
#define STOFARG(p)
#define STOSTARG(p)
#define genfcall(a, b) gencall (a, b)

/*#define NESTCALLS*/

#define MYREADER(p) myreader (p)
void optim2();

