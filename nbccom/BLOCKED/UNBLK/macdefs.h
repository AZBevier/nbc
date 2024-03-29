/* macdefs.h */
 
/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */
 
/*@(#) $Header: /u/nbc/nbccom/RCS/macdefs.h,v 1.2 1995/02/23 16:27:54 jbev Exp $ */
 
/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/
/*
* options that we normally want
*/
#ifdef MPX
#define YYDEBUG 0	/* was 0 12/27/93 */
#else
#define YYDEBUG
#endif /* MPX */
 
#ifndef NOOPTIONS
#define FLEXNAMES
#define STABDOT
#define ASSTRINGS
#define BUFSTDERR
#define NOINDIRECT
#ifndef MPX
#define LCOMM
#endif /* MPX*/
#define NEWZZZ
#endif
 
#define makecc(val, i) lastcon = ((unsigned)lastcon<<8)|((val)&0xff)
 
#define ARGINIT (SZINT*8)
#ifdef MPX
#define AUTOINIT (SZINT*0)
#else
#define AUTOINIT (SZINT*8)
#endif
#define FRAMESZ (SZINT*8)	/* Not sure? Needed for FLOC func. */
 
#define SZCHAR	8
#define SZINT	32
#define SZFLOAT	32
#define SZDOUBLE	64
#define SZLONG	64
#define SZSHORT	16
#define SZPOINT	32
#define ALCHAR	8
#define ALINT	32
#define ALFLOAT	32
#define ALDOUBLE	64
#define ALLONG	64
#define ALSHORT	16
#define ALPOINT	32
#ifdef MPX
#define ALSTRUCT	32	/* double word for MPX */
/* #define ALSTRUCT	8	/* double word for MPX */
#else
#define ALSTRUCT	8
#endif /* MPX */
#define ALSTACK SZINT
#define ALFRAME (SZINT*8)
 
/*	size in which constants are converted */
/*	should be long if feasable */
 
#define CONSZ int
 
#define FCONSZ double		/* needed by pco */
#define UCONSZ unsigned long	/* needed by pco */
 
#define CONFMT "%d"
 
/*	size in which offsets are kept
*	should be large enough to cover address space in bits
*/
 
#define OFFSZ long
 
/* 	character set macro */
 
#define CCTRANS(x) x
 
/* register cookie for stack poINTer */
 
#ifndef MPX
#define STKREG 17		/* known in pass2 as FP */
#define ARGREG 16		/* known in pass2 as AP */
#else
#define STKREG 8		/* known in pass2 as FP */
#define ARGREG 9		/* known in pass2 as AP */
#endif /* MPX */
 
/*	maximum and minimum register variables */
 
#define MAXRVAR 7
#define MINRVAR 4
 
#define IsRegVar(x) ((x) >= MINRVAR && (x) <= MAXRVAR)
#ifdef MPX
#define REGSZ 12		/* needed here for pco changes */
#else
#define REGSZ 19		/* needed here for pco changes */
#endif /* MPX */
 
 /* various standard pieces of code are used */
#define LABFMT "L%d"
 
/* show stack grows negatively but is allocated positively*/
/*#define BACKAUTO*/
/*#define BACKTEMP*/
 
/* bytes are numbered from right to left */
/*#define RTOLBYTES*/
 
/* we want prtree included */
#define STDPRTREE
 
#define ENUMSIZE(high, low) INT
 
/*#define ADDROREG*/
#define FIXDEF(p) outstab(p)
#define FIXSTRUCT(p,xyzzy) outstruct(p,xyzzy)
#define FIXARG(p) fixarg(p)
 
/* register allocation stuff */
/* mostly 2nd pass, but used a little bit in front end */
 
#define NOPREF 020000		/* no register preference */
#define	MUSTDO	010000		/* force register requirements */
 
#ifndef FORT
#ifndef TWOPASS
#define ONEPASS
#endif
#endif
 
/*	Sel Concept 32  Registers */
 
 /* scratch registers */
#define R0 0	/* link reg on MPX */
#define R1 1	/* general xr on MPX */
#define R2 2	/* general xr on MPX */
 
 /* stack pointer on MPX */
#define R3 3
 
 /* register variables */
#define R4 4
#define R5 5
#define R6 6
#define R7 7
 
#ifndef MPX	/* no used on MPX */
/* base registers */
#define B0 8
#define B1 9
#define B2 10
#define B3 11
#define B4 12
#define B5 13
#define B6 14
#define B7 15
#endif /* MPX */
 
 /* special purpose */
#ifndef MPX
#define AP 16		/* argument pointer */
#define FP 17		/* frame pointer */
#define CP 18		/* call arglist pointer */
#else
#define FP 8		/* frame pointer */
#define AP 9		/* argument pointer */
#define TP 10		/* temp pointer */ /* not used now */
#define CP 11		/* call arglist pointer */
#endif
 
 /* floating registers */
 /* there are no floating point registers on the SEL 32/xx */
 
/* Pass 2 should generate labels starting here.  (The flow optimizer starts
 * here too).
 */
 
#define	LAST_P2_LABEL	9999
 
/* This character introduces an assembler comment */
 
#ifndef MPX
#define ASM_CCHAR	'='
#else
#ifdef TWOPASS
#define ASM_CCHAR	'-'
#else
#define ASM_CCHAR	'*'
#endif
#endif /* MPX */
 
