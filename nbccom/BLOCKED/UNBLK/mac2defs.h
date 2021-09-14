/* mac2defs.h */
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
 
/*	@(#) (Gould) $Header: /u/nbc/nbccom/RCS/mac2defs.h,v 1.1 1995/01/27 20:56:20 jbev Exp $		  */
 
/*
    C compiler for Gould processors, base register instruction set.
 
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
int optim2();
 
/*
 * 	(c) Copyright 1986 Gould Inc.
 * 	    All Rights Reserved.
 */
