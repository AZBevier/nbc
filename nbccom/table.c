/* table.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid = "$Header: /bulk2/simhv/nbc-master/nbccom/RCS/table.c,v 1.10 1996/03/22 00:15:04 jbev Exp $";
#endif

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.

NOTES:
	FORCC cookie will never be used with an UNSIGNED node, unless
	    comparison is for EQUALITY.

	respref[] has been adjusted such that FORCC will pick up
	    almost any addressable value if RESCC wasn't present.
	    It can be used whenever a simple mov? result,Rtemp
	    would give you the right ccodes.
	
	FORZCC cookie means that RESCC will only expect to pick
	    up a valid ZERO condition code.

	Reclaim assures us that SAREG|STAREG will be only
		INT, UNSIGNED, FLOAT or DOUBLE
		LONG may occur but only in the context of OPLOG or OPLEAF-FORCC
*/

#include "mfile2.h"

#define AWD		SNAME|SOREG|SCON
#define MEM		SNAME|SOREG
#define TWORD		TINT|TUNSIGNED|TPOINT
#define THALF		TUSHORT|TSHORT
#define TBYTE		TUCHAR|TCHAR
#define TSCALAR 	TWORD|TBYTE|THALF
#define TNATURAL 	TINT|TPOINT|TBYTE|TSHORT	/* had TUCHAR FEB25 */
#define TFP		TFLOAT|TDOUBLE|TLONG		/* added TLONG MAR26 */
#define TSSCALAR	TINT|TSHORT|TBYTE		/* had TCHAR FEB25 */
#ifndef MPX113091	/* remove TUSHORT */
#define TUSCALAR	TUNSIGNED|TBYTE			/* had TUCHAR FEB25 */
#else
#define TUSCALAR	TUNSIGNED|TUSHORT|TBYTE		/* had TUCHAR FEB25 */
#endif
#define TUNSVAL		TUSCALAR|TPOINT		/* any unsigned val FEB25 */

struct optab    table[] =
{
INIT, FOREFF,
    SNAME, TANY,
    SANY, TWORD,
    0, RNOP,
	"	dataw	AL\n",

INIT, FOREFF,
    SCON, TANY,
    SANY, TLONG,
    0, RNOP,
	"	datad	CL\n",

INIT, FOREFF,
    SCON, TANY,
    SANY, TWORD,
    0, RNOP,
	"	dataw	CL\n",

INIT, FOREFF,
    SCON, TANY,
    SANY, THALF,
    0, RNOP,
	"	datah	CL\n",

INIT, FOREFF,
    SCON, TANY,
    SANY, TBYTE,
    0, RNOP,
	"	datab	CL\n",

STASG, INAREG|FOREFF,
    SNAME|SOREG, TANY,
    SCON|SAREG, TANY,
    0, RRIGHT,
	"ZS",

STASG, INAREG|INTAREG,
    SNAME|SOREG, TANY,
    SCON|SAREG, TANY,
    0, RRIGHT,
	"ZS",

STASG, INAREG|FOREFF,
    MEM|SAREG, TANY,
#ifdef STASG_FIX_01_15_96
    SCON|SOREG|SAREG, TANY,
#else
    SCON|SAREG, TANY,
#endif
    0, RRIGHT,
	"ZS",

STARG, INTEMP,
    SCON|SAREG, TANY,
    SANY, TANY,
    NTEMP|NAREG, RESC2,
	"ZS",

/* 8 */
SCONV, INTAREG|FORCC,
    AWD, TUSHORT,
    SANY, TWORD,
    NAREG, RESC1|RESCC,
	"	zr	A1\n	ormh	A1,AL\n",

SCONV, INTAREG|FORCC,
    AWD, TUNSVAL|TNATURAL,	/* was just TUNSIGNED FEB25 */
    SANY, TWORD,
    NASL|NAREG, RESC1|RESCC,
	"	lZLP	A1,AL\n",

/* CHAR -> WORD taken care of by all moves through STAREG */

/* 10 */
SCONV, INTAREG|FORCC,
    AWD, TBYTE,
    SANY, TWORD,
    NAREG, RESC1|RESCC,
	"	lZLP	A1,AL\n	anmw	A1,=x'ff'\n",

SCONV, INTAREG|FORCC,
    STAREG, TSCALAR,
    SANY, TBYTE,	/* was TUCHAR 05/03/94 */
    0, RLEFT|RESCC,
	"	anmw	AL,=x'ff'\n",

SCONV, INTAREG|FORCC,
    STAREG, TSCALAR,
    SANY, TUSHORT,
    0, RLEFT|RESCC,
	"	anmw	AL,=x'ffff'\n",

#ifndef SPR_022694
SCONV, INTAREG|FORCC,
    STAREG, TWORD,
    SANY, TUSHORT,
    0, RLEFT|RESCC,
	"	anmw	AL,=x'ffff'\n",
#endif

#ifndef SPR_022694
SCONV, INTAREG|FORCC,
    STAREG, TSCALAR,
    SANY, TCHAR,
    0, RLEFT|RESCC,
	"	lZLP	A1,AL\n	stb	A1,AL\n",
/* 	"	lb	AL,A1\n	stb	A1,AL\n", */
#endif

#ifdef JUNK_050394
SCONV, INTAREG|FORCC,
    STAREG, TSCALAR,
    SANY, TSHORT,
    0, RLEFT|RESCC,
	/* added anmw DEC14 */
 	"	lh	A1,AL\n	anmw	A1,=x'ffff' XX\n	sth	A1,AL\n",
/* 	"	lh	AL,A1\n	sth	A1,AL\n", */
#endif

/* 15 */
#ifdef IEEE_FIX
SCONV, INTAREG,		/* added SAT from above */
    SAREG, TFLOAT,
    SANY, TDOUBLE | TLONG,
    NASL|NDREG, RESC1,	/* was NAREG */
	"G	trr	AL,A1\n	zr	U1\n", 

SCONV, INTAREG,		/* had FOREFF THU */
    AWD, TFLOAT,
    SANY, TDOUBLE | TLONG,
    NASL|NDREG, RESC1,		/* was NAREG SAT */
	"	lw	A1,AL\n	zr	U1\n",

SCONV, INTEMP,
    SAREG, TFLOAT,
    SANY, TDOUBLE | TLONG,
    2*NTEMP, RESC1,
	"	stw	AL,A1\n	zmw	U1\n",

#else /* IEEE_FIX */
SCONV, INTAREG,		/* added SAT from above */
    SAREG, TFLOAT,
    SANY, TLONG,
    NASL|NDREG, RESC1,	/* was NAREG */
	"G	trr	AL,A1\n	zr	U1\n", 

SCONV, INTAREG,		/* added SAT from above */
    SAREG, TFLOAT,
    SANY, TDOUBLE,
    NASL|NDREG, RESC1,	/* was NAREG */
	"G	trr	AL,A1\n	.cf2d	A1\n", 

SCONV, INTAREG,		/* had FOREFF THU */
    AWD, TFLOAT,
    SANY, TLONG,
    NASL|NDREG, RESC1,		/* was NAREG SAT */
	"	lw	A1,AL\n	zr	U1\n",

SCONV, INTAREG,		/* had FOREFF THU */
    AWD, TFLOAT,
    SANY, TDOUBLE,
    NASL|NDREG, RESC1,		/* was NAREG SAT */
	"	lw	A1,AL\n	.cf2d	A1\n",

SCONV, INTEMP,
    SAREG, TFLOAT,
    SANY, TLONG,
    2*NTEMP, RESC1,
	"	stw	AL,A1\n	zmw	U1\n",

#ifdef IEEE_JUNK
SCONV, INTEMP,
    SAREG, TFLOAT,
    SANY, TDOUBLE,
    2*NTEMP, RESC1,
	"	stw	AL,A1\n	zmw	U1\n",
#endif

#endif /* IEEE_FIX */
SCONV, INAREG|INTAREG|FORCC,
    STAREG, TFLOAT,
    SANY, TSCALAR,
    0, RLEFT|RESCC,
	"	fixw	AL,AL\n",

SCONV, INAREG|INTAREG|FORCC,
    STAREG, TSCALAR,
    SANY, TFLOAT,
    0, RLEFT|RESCC,
	"	fltw	AL,AL\n",

/* 20 */
SCONV, INTAREG,		/* had FORCC NOV08 */
    SAREG, TUNSIGNED,
    SANY, TLONG,
    NASL|NAREG, RESC1,
	"G	trr	AL,U1\n	zr	A1\n",

SCONV, INTAREG,		/* had FORCC NOV08 */
    AWD, TUNSIGNED,
    SANY, TLONG,
    NASL|NAREG, RESC1,
	"	lw	U1,AL\n	zr	A1\n",

SCONV, INTAREG|FORCC,
    AWD, TNATURAL,
    SANY, TLONG,
    NASL|NAREG, RESC1|RESCC,
	"	lZLP	U1,AL\n	es	A1\n",

SCONV, INTAREG|FORCC,
    SAREG, TNATURAL|TLONG,	/* added TLONG FRI */
    SANY, TLONG,
    NASL|NAREG, RESC1|RESCC,
	"G	trr	AL,U1\n	es	A1\n",

SCONV, INTAREG|FORCC,
    SAREG, TUNSIGNED,
    SANY, TDOUBLE,
    NASL|NAREG, RESC1|RESCC,
	"G	trr	AL,U1\n	zr	A1\n	fltd	A1,A1\n",

SCONV, INTAREG|FORCC,
    AWD, TUNSIGNED,
    SANY, TDOUBLE,
    NASL|NAREG, RESC1|RESCC,
	"	lw	U1,AL\n	zr	A1\n	fltd	A1,A1\n",

SCONV, INTAREG|FORCC,
    AWD, TNATURAL,
    SANY, TDOUBLE,
    NASL|NAREG, RESC1|RESCC,
	"	lZLP	U1,AL\n	es	A1\n	fltd	A1,A1\n",

SCONV, INTAREG|FORCC,
    SAREG, TNATURAL|TLONG,	/* added TLONG FRI */
    SANY, TDOUBLE,
    NASL|NAREG, RESC1|RESCC,
	"G	trr	AL,U1\n	es	A1\n	fltd	A1,A1\n",

#ifdef IEEE_FIX
SCONV, INAREG|INTAREG, /* WED */
    SAREG, TDOUBLE,
    SANY, TFLOAT,
    0, RLEFT,
	"",

#else /* IEEE_FIX */
SCONV, INAREG|INTAREG, /* WED */
    SAREG, TDOUBLE,
    SANY, TFLOAT,
    0, RLEFT,
	"	.cd2f	AL\n",

#endif /* IEEE_FIX */
SCONV, INAREG|INTAREG|FORCC,
    STAREG, TDOUBLE,
    SANY, TSCALAR,
    0, RESUPPER|RLEFT|RESCC,
	"	fixd	AL,AL\n",

/* 30 */
SCONV, INAREG|FORCC,
    SAREG, TNATURAL,
    SANY, TLONG,
    NASL|NAREG, RESC1|RESCC,
	"G	trr	AL,U1\n	es	A1\n",

SCONV, INAREG|FORCC,
    AWD, TNATURAL,
    SANY, TLONG,
    NASL|NAREG, RESC1|RESCC,
	"	lZLP	U1,AL\n	es	A1\n",

SCONV, INAREG,
    AWD, TUNSIGNED,
    SANY, TLONG,
    NASL|NAREG, RESC1,	/* SAT */
	"	zr	A1\n	lw	U1,AL\n",

SCONV, INAREG|FORZCC,	/* FEB10 */ /* had FORCC NOV08 */
    SOREG, TUNSIGNED,
    SANY, TLONG,
    NASL|NDREG, RESC1|RESCC,
	"	zr	A1\n	lw	U1,AL\n",

SCONV, INAREG|FORZCC,	/* FEB10 */ /* had FORCC NOV08 */
    SAREG, TUNSIGNED,
    SANY, TLONG,
    NASL|NDREG, RESC1|RESCC,
	"	zr	A1\n	trr	AL,U1\n",

/* 35 */
SCONV, INAREG|FORCC,	/* had FORCC NOV08 */
    AWD, TUSHORT,
    SANY, TLONG,
    NDREG, RESC1|RESCC,
	"	zr	A1\n	zr	U1\n	ormh	U1,AL\n",

SCONV, INAREG|FORCC,	/* modified FRI  had FORCC NOV08 */
    SAREG, TCHAR,
    SANY, TLONG,
    NASL|NAREG, RESC1|RESCC,
	"	zr	A1\n	lb	U1,AL\n",	/* swapped code NOV08 */

#ifdef SPR_031194
SCONV, INAREG|INTAREG|FOREFF,
    SAREG, TSCALAR,	/* was TINT */
    SANY, TBYTE,
    NAREG, RESC1,
	"G	trr	AL,A1\n	anmw	A1,=x'ff'\n",

SCONV, INAREG|INTAREG|FOREFF,
    SAREG, TSCALAR,	/* was TINT */
    SANY, TUSHORT,
    NAREG, RESC1,
	"G	trr	AL,A1\n	anmw	A1,=x'ffff'\n",

#ifndef SPR_022694
SCONV, INAREG|INTAREG|FOREFF,
    SAREG, TWORD,
    SANY, TUSHORT,
    NAREG, RESC1,
	"G	trr	AL,A1\n	anmw	A1,=x'ffff'\n",
#endif
#else
/*SCONV, INAREG|INTAREG|FOREFF, */
/*SCONV, INAREG|FOREFF, */
SCONV, INTAREG,
    SAREG, TSCALAR,	/* was TINT */
    SANY, TBYTE,
    0, RLEFT,
	"	anmw	AL,=x'ff'\n",

/*SCONV, INAREG|INTAREG|FOREFF, */
/*SCONV, INAREG|FOREFF, */
SCONV, INTAREG,
    SAREG, TSCALAR,	/* was TINT */
    SANY, TUSHORT,
    0, RLEFT,
	"	anmw	AL,=x'ffff'\n",

#ifdef SPR_022694
/*SCONV, INAREG|INTAREG|FOREFF, */
SCONV, INAREG,
    SAREG, TWORD,
    SANY, TUSHORT,
    0, RESC1,
	"	anmw	AL,=x'ffff'\n",
#endif
#ifndef SPR_022694
SCONV, INAREG|INTAREG|FOREFF,
    SAREG, TSCALAR,	/* was TINT */
    SANY, TBYTE,
    NAREG, RESC1,
	"G	trr	AL,A1\n	anmw	A1,=x'ff'\n",

SCONV, INAREG|INTAREG|FOREFF,
    SAREG, TWORD,
    SANY, TUSHORT,
    NAREG, RESC1,
	"G	trr	AL,A1\n	anmw	A1,=x'ffff'\n",
#endif
#endif

/* 40 */
#ifdef SPR_031194
SCONV, INTAREG|FOREFF,
    SAREG, TUNSIGNED,
    SANY, TINT,
    0, RLEFT,
	"",

SCONV, INTAREG|FOREFF,
    SAREG, TWORD,
    SANY, TWORD,
    NAREG, RESC1,
	"K	trr	AL,A1\n",
#endif

SCONV, INAREG|INTAREG|FOREFF,
    SAREG, TSCALAR,
    SANY, TSCALAR,
    0, RLEFT,
	"",

SCONV, INTEMP,
    STAREG, TINT|TPOINT,
    SANY, TLONG,
    2 * NTEMP, RESC1,
	"	stw	AL,U1\n	sra	AL,31\n	stw	AL,A1\n",

SCONV, INTEMP,
    SAREG, TUNSIGNED,
    SANY, TLONG,
    2 * NTEMP, RESC1,
	"	stw	AL,U1\n	zmw	A1\n",

#ifdef FORT
GOTO, FOREFF,
	AWD, TINT,
	SANY, TANY,
	2*NAREG, RNULL,
		"	lw	A2,AL\n	bu	0,A2\n",
#endif

GOTO, FOREFF,
    SAREG, TANY,
    SANY, TANY,
    0, RNULL,
	"	bu	0,AL\n",

#ifdef ON26FEB92
DECR, FOREFF,
    SAREG, TSCALAR,
    SSCON, TANY,
    0, RESC1,
	"	sui	AL,CR\n",	/* had an F MAR6 */

DECR, FOREFF,
    SAREG, TSCALAR,
    SCON, TANY,
    0, RESC1,
	"	sumZLP	AL,AR\n",
#endif

DECR, FOREFF|INAREG|INTAREG,
    SAREG, TSCALAR,	/* OCT19 was TWORD */
    SSCON, TANY,
    NAREG, RESC1,
	"F	trr	AL,A1\n	sui	AL,CR\n",

DECR, FOREFF|INAREG|INTAREG,
    SAREG, TWORD,
    SCON, TANY,
    NAREG, RESC1,
	"F	trr	AL,A1\n	sumw	AL,AR\n",

#ifdef VISTA_BUG
DECR, FOREFF,
    AWD, TSCALAR,	/* OCT05 was TWORD */
    SSCON, TANY,
    NAREG, RNULL,
	"	li	A1,-CR\n	armZLP	A1,AL\n",
#else
DECR, FOREFF,		/* NEWWAY */
    AWD, TUSHORT,		
    SSCON, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	anmw	A1,=x'ffff'\n	adi	A1,-CR\n	stZLP	A1,AL\n",

DECR, FOREFF,		/* NEWWAY */
    AWD, TBYTE|THALF,		
    SSCON, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	adi	A1,-CR\n	stZLP	A1,AL\n",

DECR, FOREFF,
    AWD, TWORD,		/* OCT05 was TWORD */
    SSCON, TANY,
    NAREG, RNULL,
	"	li	A1,-CR\n	armZLP	A1,AL\n",

/* 50 */
DECR, FOREFF,		/* NEWWAY */
    AWD, TUSHORT,		
    SCON, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	sumZLP	A1,AR\n	anmw	A1,=x'ffff'\n	stZLP	A1,AL\n",

DECR, FOREFF,		/* NEWWAY */
    AWD, TBYTE|THALF,		
    SCON, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	sumZLP	A1,AR\n	anmw	A1,=x'ffff'\n	stZLP	A1,AL\n",
#endif

DECR, FOREFF,
    AWD, TWORD,
    SCON, TANY,
    NAREG, RNULL,
	"	lnw	A1,AR\n	armw	A1,AL\n", /* MAR6 */

DECR, INAREG|INTAREG|FOREFF,	/* added FOREFF OCT19 */
    AWD, TWORD,
    SSCON, TANY,
    2*NAREG, RESC1,
	"	lw	A1,AL\n	li	A2,-CR\n	armw	A2,AL\n",

DECR, INAREG|INTAREG|FOREFF,	/* added FOREFF OCT19 */
    AWD, TWORD,
    SCON, TANY,
    2*NAREG, RESC1,
	"	lw	A1,AL\n	lnw	A2,AR\n	armw	A2,AL\n", /* MAR6 */

DECR, INAREG|INTAREG|FOREFF,	/* added FOREFF OCT19 */
    AWD, TWORD,
    SSCON, TANY,
    NAREG, RESC1,
	"	lw	A1,AL\n	sui	A1,CR\n\
	stw	A1,AL\n	 adi	A1,CR\n",

DECR, INAREG|INTAREG|FOREFF,	/* added FOREFF OCT19 */
    AWD, TWORD,
    SCON, TANY,
    NAREG, RESC1,
	"	lw	A1,AL\n	sumw	A1,AR\n\
	stw	A1,AL\n	 admw	A1,AR\n",

#ifdef ON26FEB92
DECR, INAREG|FOREFF,
    AWD, TWORD|TSHORT|TBYTE,	/* 113091 added TSHORT, TBYTE */
    SAREG, TANY,
    0, RLEFT,
	"	armZLP	AR,AL\n",
#endif

INCR, FOREFF, 	/* had FORCC */
    SAREG, TANY,
    SPOW2, TANY,
    0, RESC1|RESCC,
	"	abr	AL,Zn\n",	/* had an F MAR6 */

#ifdef VISTA_BUG
INCR, FOREFF, 	/* had FORCC */
    AWD, TANY,
    SPOW2, TANY,
    0, 0,	/* had RESC1|RESCC */
	"	abm	Zn,AL\n",	/* had an F MAR6 */
#else
#ifdef NEWWAY
INCR, FOREFF, 	/* had FORCC */
    AWD, TWORD,
    SPOW2, TANY,
    0, 0,	/* had RESC1|RESCC */
	"	abm	Zn,AL\n",	/* had an F MAR6 */
#else
INCR, FOREFF,
    AWD, TUSHORT,
    SPOW2, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	anmw	A1,=x'ffff'\n	abr	A1,Zo\n	stZLP	A1,AL\n",

INCR, FOREFF,
    AWD, THALF|TBYTE,
    SPOW2, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	abr	A1,Zo\n	stZLP	A1,AL\n",

/* 60 */
INCR, FOREFF,
    AWD, TWORD,
    SPOW2, TANY,
    0, 0,
	"	abm	Zn,AL\n",	/* had an F MAR6 */
#endif
#endif

INCR, FOREFF|INAREG|INTAREG,
    SAREG, TPOINT,
    SONE, TANY,
    NAREG, RESC1,
	"F	trr	AL,A1\n	abr	AL,31\n",

INCR, FOREFF|INAREG|INTAREG,
    SAREG, TPOINT,
    SPOW2, TANY,
    NAREG, RESC1,
	"F	trr	AL,A1\n	abr	AL,Zn\n",

INCR, FOREFF|INAREG|INTAREG,
    SAREG, TPOINT,
#ifdef OCT1092
    SCCON, TANY,
#else
    SSCON, TANY,	/* 16 bit value, not 7 bit value */
#endif
    NAREG, RESC1,
	"	adi	AL,CR\n",	/* had an F MAR6 */

INCR, FOREFF|INAREG|INTAREG,
    SAREG, TPOINT,
    SMCON, TANY,	/* FEB17 was SOCON */
    NAREG, RESC1,
#ifdef OCT1092
	"F	trr	AL,A1\n\tla	AL,CR,A1\n",
#else
	"	trr	AL,A1\n\tla	AL,CR,A1\n",
#endif

/* 65 */
INCR, FOREFF|INTAREG|INAREG,	/* MAR26 added INAREG */
/*    SAREG, TWORD,	old MAR26 */
    SAREG|STAREG, TWORD|TPOINT,		/* new MAR26 */
    SPOW2, TANY,
    NAREG, RESC1,
	"F	trr	AL,A1\n	abr	AL,Zn\n",

INCR, FOREFF|INTAREG|INAREG,
    AWD, TWORD,		/* removed SAREG MAR26 */
    SPOW2, TANY,
    NAREG, RESC1,
	"F	lZLP	A1,AL\n	abm	Zn,AL\n",

INCR, FOREFF|INAREG|INTAREG,
    SAREG, TWORD,
    SSCON, TANY,
    NAREG, RESC1,
	"F	trr	AL,A1\n	adi	AL,CR\n",

INCR, FOREFF|INAREG|INTAREG,
    SAREG, TWORD,
    SCON, TANY,
    NAREG, RESC1,
	"F	trr	AL,A1\n	admw	AL,AR\n",

INCR, FOREFF|INAREG|INTAREG,
    AWD, TWORD,
    SSCON, TANY,
    2*NAREG, RESC1,
	"F	lw	A1,AL\n	li	A2,CR\n	armw	A2,AL\n", /* MAR6 */

/* 70 */
INCR, FOREFF|INAREG|INTAREG,
    AWD, TWORD,
    SCON, TANY,
    2*NAREG, RESC1,
	"F	lw	A1,AL\n	li	A2,CR\n	armw	A2,AL\n", /* MAR6 */

INCR, FOREFF|INAREG|INTAREG,
    AWD, TWORD,
    SSCON, TANY,
    NAREG, RESC1,
	"	lw	A1,AL\n	adi	A1,CR\n\
	stw	A1,AL\nF	sui	A1,CR\n",

INCR, FOREFF|INAREG|INTAREG,
    AWD, TWORD,
    SCON, TANY,
    NAREG, RESC1,
	"	lw	A1,AL\n	admw	A1,AR\n\
	stw	A1,AL\nF	sumw	A1,AR\n",

#ifdef COMP_BUG_AUG171993
INCR, FOREFF|INAREG|INTAREG,
    AWD, THALF,
    SSCON, TANY,
    NAREG, RESC1,
	"	lh	A1,AL\n	adi	A1,CR\n\
	sth	A1,AL\nF	sui	A1,CR\n",

INCR, FOREFF|INAREG|INTAREG,
    AWD, TBYTE,
    SSCON, TANY,
    NAREG, RESC1,
	"	lb	A1,AL\n	adi	A1,CR\n\
	stb	A1,AL\nF	sui	A1,CR\n",
#endif

OPLOG, FORCC|FOREFF,
    SAREG, TDOUBLE|TLONG,
    AWD, TDOUBLE|TLONG,
    0, RESCC,
	"	camd	AL,AR\nZJ",

OPLOG, FORCC,
    SAREG, TDOUBLE|TLONG,
    SAREG, TDOUBLE|TLONG,
    2 * NTEMP, RESCC,
	"	std	A1,AR\n	camd	A1,AL\nZJ",

OPLOG, FORCC|FORZCC,
    SAREG, TANY,
    SAREG, TANY,
    0, RESCC,
	"	car	AR,AL\nZJ",

/* 75 */
OPLOG, FORCC,
    SAREG, TANY,
    SSCON, TNATURAL,
    0, RESCC,
	"	ci	AL,CR\nZJ",

#ifndef SPR_022594
OPLOG, FORZCC,
    AWD, TCHAR,
    AWD, TCHAR,
    NAREG, RESCC,
	"	lb	A1,AL\n	camb	A1,AR\nZJ",
#endif

#ifndef SPR_022594
OPLOG, FORCC,
    SAREG, TANY,
    SSCON, TUNSIGNED|TUSHORT,
    0, RESCC,
	"	ci	AL,CR\nZJ",
#endif

OPLOG, FORCC,
    SAREG, TANY,
    AWD, TFP|TNATURAL,
    0, RESCC,
	"	camZRP	AL,AR\nZJ", /* must fix for immediate ops */

#ifndef SPR_022594
OPLOG, FORZCC,
    SAREG, TUSHORT,
    AWD, TUSHORT,
    NAREG, RESCC,
/*	"	lh	A1,AL\n	camh	A1,AR\nZJ", */
	"	lh	A1,AR\n	anmw	A1,=x'ffff'\n	car	A1,AL\nZJ",
#endif

/* 80 */
#ifdef SPR_022594
OPLOG, FORZCC,
    SAREG, TANY,
    AWD, TWORD,
    0, RESCC,
	"	camw	AL,AR\nZJ",
#else
OPLOG, FORZCC,
    SAREG, TANY,
    AWD, TWORD,
    0, RESCC,
	"	camZLP	AL,AR\nZJ",
#endif

#ifdef SPR_022594
OPLOG, FORZCC,
    AWD, TCHAR,
    AWD, TCHAR,
    NAREG, RESCC,
	"	lb	A1,AL\n	camb	A1,AR\nZJ",
#endif

OPLOG, FOREFF|FORCC,
    SAREG, TUNSIGNED|TUSHORT,
    SAREG, TUNSIGNED|TUSHORT,
    0, RESCC,
    "	tbr	AL,0\n\
	bns	$+4w\n\
	tbr	AR,0\n\
	bs	$+4w\n\
	bu	$+5w\n\
	tbr	AR,0\n\
	bs	$+3w\n\
	car	AR,AL\n\
	bu	$+3h\n\
	car	AL,AR\nZJ",

OPLOG, FOREFF|FORCC,
    STAREG, TUNSIGNED|TUSHORT,
    AWD, TUNSIGNED|TUSHORT,
    NAREG, RESCC,
    "	zr	A1\n\
	ormZRP	A1,AR\n\
	tbr	AL,0\n\
	bns	$+4w\n\
	tbr	A1,0\n\
	bs	$+4w\n\
	bu	$+5w\n\
	tbr	A1,0\n\
	bs	$+3w\n\
	car	A1,AL\n\
	bu	$+3h\n\
	car	AL,A1\nZJ",

OPLOG, FORZCC,
    AWD, TUSHORT,
    AWD, TUSHORT,
    NAREG, RESCC,
	"	lh	A1,AL\n	camh	A1,AR\nZJ",

OPLOG, FORZCC,
    SAREG, TUNSIGNED,
    AWD, TUCHAR|TUNSIGNED,
    0, RESCC,
	"	camZRP	AL,AR\nZJ",

/* casts would have been inserted if TUNSIGNED hadn't been manufactured
   by reclaim
*/
OPLOG, FORCC,
    SAREG, TUNSIGNED,
    SCON, TANY,
    0, RESCC,
	"	camw	AL,AR\nZJ",

CCODES, INAREG|INTAREG,
    SANY, TANY,
    SANY, TANY,
    NAREG, RESC1,
	"	li	A1,1\nZN",

/* new for MPX */
UANDP, INTAREG|FORCC,
    AWD, TANY,
    SANY, TANY,
    NASL|NAREG, RESC1|RESCC,
	"	lcra	A1,AL\n",

UNARY AND, INAREG|INTAREG|FOREFF,	/* added FOREFF FEB17 */
    SOREG|SNAME, TANY,
    SANY, TANY,
    NASL|NAREG, RESC1,
	"	la	A1,AL\n",

UNARY AND, INAREG|INTAREG|FOREFF,	/* added FOREFF FEB17 */
    SCON, TANY,
    SANY, TANY,
    NASL|NAREG, RESC1,
	"	la	A1,AL\n",

UNARY CALL, INTAREG,
    SCON, TANY,
    SANY, TANY,
    NASL|NAREG, RESC1,
	"	bl	CL\n",

UNARY CALL, INAREG|INTAREG,
    SAREG, TANY,
    SANY, TANY,
    NASL|NAREG, RESC1,
	"	bl	0w,CL\n",

UNARY FORTCALL, INTAREG,
    AWD, TANY,
    SANY, TANY,
    NAREG|NASL, RESC1,
    	"ZQ	bl	_f.callZd\n	ach	CL\n",

UNARY FORTCALL, INTAREG,
    SAREG, TANY,
    SANY, TANY,
    NAREG|NASL, RESC1,
    	"ZQ	bl	_f.callZd\n	ach	0,AL\n",

/* must fix for MPX */
UNARY STCALL, INTAREG,
    SCON, TANY,
    SANY, TANY,
    NTEMP|NAREG, RESC1,
	"\tmovea\tA2,r0\n\tmovw\tr0,21w[b2]\n\tcall\tCL,Zm,ZC\n",

UNARY STCALL, INTAREG,
    SAREG, TANY,
    SANY, TANY,
    NTEMP|NAREG|NASR, RESC1,
	"\tmovea\tA2,r0\n\tmovw\tr0,21w[b2]\n\tcallr\tCL,Zm,ZC\n",

/* tst stuff */
REG, FORCC,
    SAREG, TLONG|TDOUBLE,
    SANY, TANY,
    0, RESCC,
	"	camd	AR,ZD\n",	/* compare to zero to get cc's */

#ifdef VISTA_FEB0792
REG, FOREFF|FORCC,	/* added whole thing FEB15 */
#else
REG, FORCC,	/* added whole thing FEB15 */
#endif
    SANY, TANY,
    SANY, TANY,
    0, RESCC,
	"	trr	AR,AR\n",

REG, INAREG|FORCC,
    SANY, TANY,
    SANY|SOREG, TANY,
    NAREG, RESC1|RESCC,
	"	trr	AR,A1\n",

REG, INAREG|FORCC,
    SANY, TANY,
    SANY, TANY,
    NAREG, RESC1|RESCC,
	"	trr	AR,A1\n",

/* 100 */
REG, INAREG|FORCC,
    AWD, TANY,
    SANY, TNATURAL|TFLOAT|TWORD,
    NAREG, RESC1|RESCC,
	"	trr	AR,A1\n",

REG, INTEMP,
    SANY, TANY,
    SAREG, TDOUBLE|TLONG,
    2 * NTEMP, RESC1,
	"	std	AR,A1\n",

REG, INTEMP,
    SANY, TANY,
    SAREG, TANY,
    NTEMP, RESC1,
#ifndef FIX_050994
	"	stZLP	AR,A1\n",
#else
/*	"	stw	AR,A1\n", */
#endif

OPLEAF, INAREG|FOREFF|FORCC,
    SAREG, TDOUBLE|TLONG,
    SZERO, TDOUBLE|TLONG,
    NDREG, RLEFT|RESCC,
	"	zr	AL\n	zr	UL\n",

OPLEAF, INAREG|INTAREG|FOREFF|FORCC,
    SAREG, TSCALAR,
    SZERO, TANY,
    0, RLEFT|RESCC,
	"	zr	AL\n",

OPLEAF, INAREG|INTAREG|FOREFF,
    SZERO, TANY,
    SANY, TDOUBLE|TLONG,
    NDREG, RESC1,
	"	zr	A1\n	zr	U1\n",

OPLEAF, INAREG|INTAREG|FOREFF,	/* FEB15 added FOREFF */
    SZERO, TANY,
    SANY, TANY,
    NAREG, RESC1,
	"	zr	A1\n",

#ifdef VISTA_BUG
OPLEAF, FORCC|FOREFF,		/* had FORCC */
    SPOW2, TANY,
    SANY, TANY,
    0, RESC1,	/* had RESC1|RESCC */
	"	abm	Zn,AL\n",
#else
OPLEAF, FORCC|FOREFF,		/* had FORCC */
    SPOW2, TANY,
    SANY, TWORD,
    0, RESC1,	/* had RESC1|RESCC */
	"	abm	Zn,AL\n",
#endif

OPLEAF, INAREG|INTAREG|FOREFF,
    SSCON, TANY,
    SANY, TANY,
    NAREG, RESC1,
	"	li	A1,CL\n",

OPLEAF, INAREG|INTAREG,
    SICON, TANY,
    SANY, TANY,
    NAREG, RESC1,
	"	lZP	A1,AL\n",

OPLEAF, INAREG|INTAREG|FORCC,
    SAREG|STAREG, TFLOAT|TNATURAL|TUNSIGNED|TSCALAR,	/* TUE  added STAREG */
    SANY, TANY,
    NASL|NAREG, RESC1|RESCC,
	"	trr	AL,A1\n",

/* 115 */
OPLEAF, INAREG|INTAREG|FORCC,
    AWD, TFLOAT|TNATURAL|TUNSIGNED|TSCALAR,
    SZERO, TFLOAT|TNATURAL|TUNSIGNED|TSCALAR,
    NASL|NAREG, RESC1|RESCC,
	"	zr	A1\n",

OPLEAF, INAREG|INTAREG|FORCC,
    AWD, TFLOAT|TNATURAL|TUNSIGNED|TSCALAR,
    SSCON, TANY,
    NASL|NAREG, RESC1|RESCC,
	"	li	A1,CL\n",

OPLEAF, INAREG|FOREFF,
    SOREG|SCON|SNAME, TSCALAR|TNATURAL,	/* added SNAME FEB15 */
    SCON, TWORD,
    NAREG|NASR, RESC1,
	"	lE	A1,QR\n",	/* add imm lit ops */

OPLEAF, INAREG|INTAREG|FORCC,
    SANY, TUSHORT,
    SANY, TANY,
    NASL|NAREG, RESCC|RESC1,
	"	lh	A1,AL\n	anmw	A1,=x'ffff'\n",

OPLEAF, INAREG|INTAREG,
    SANY, TCHAR,
    SANY, TANY,
    NASL|NAREG, RESC1,
	"	lb	A1,AL\n",

/* 120 */
OPLEAF, FORCC,
    SANY, TCHAR,
    SANY, TANY,
    NASL|NAREG, RESCC,
	"	lb	A1,AL\n",

OPLEAF, INAREG|INTAREG|FOREFF,
    SOREG|SCON|SNAME, TSCALAR|TNATURAL,	/* added SNAME FEB15 */
    SCON, TSCALAR,
    NAREG|NASR, RESC1,
	"	lE	A1,QR\n",	/* add imm lit ops */

OPLEAF, INTAREG|INAREG|FORCC,	/* modified TUE */
    AWD, TANY,
    AWD, TANY,
    NASL|NAREG, RESCC|RESC1,
	"	lE	A1,QL\n",

OPLEAF, INAREG|INTAREG|FORCC,
    AWD, TDOUBLE|TLONG,
    SANY, TANY,
    NASL|NDREG, RESCC|RESC1,
	"	lZP	A1,AL\n",

OPLEAF, FORCC,
    SAREG, TLONG|TDOUBLE,
    SANY, TANY,
    0, RESCC,
	"	camd	AL,ZD\nZJ",	/* comprare to zero to get cc's */

/* 125 */
OPLEAF, FOREFF,
    SANY, TANY,
    SANY, TANY,
    0, RLEFT,
	"",		/* 5/15/90 was nop1 */

/* 126 */
LT, FORCC,
    AWD, TCHAR|TSHORT|TINT|TPOINT,
    SZERO, TANY,
    0, RESCC,
	"	tbm	0,AL\nZG",

/* 127 */
ASSIGN, INAREG|FOREFF,
    SAREG, TDOUBLE|TLONG,
    SZERO, TANY,
    0, RRIGHT|RESCC,
	"	zr	AL\n	zr	UL\n",

ASSIGN, INAREG|FOREFF,
    AWD, TANY,
    SZERO, TANY,
    0, RRIGHT|RESCC,
	"	zmZLP	AL\n",

ASSIGN, INAREG|FOREFF|FORCC,
    SAREG, TSCALAR|TFLOAT,
    SZERO, TANY,
    0, RLEFT|RRIGHT|RESCC,
	"	zr	AL\n",

/* 130 */
ASSIGN, INAREG|FOREFF|FORCC,
    SAREG, TANY,
    SSCON, TANY,
    0, RLEFT|RRIGHT|RESCC, 
	"	li	AL,CR\n",

ASSIGN, INAREG|FOREFF|FORCC,
    SAREG, TANY,
    SICON, TANY,
    0, RLEFT|RRIGHT|RESCC,
	"	lE	AL,QR\n",

ASSIGN, INAREG|FOREFF|FORCC,
    SAREG, TSCALAR|TFLOAT,
    SAREG, TSCALAR|TFLOAT,
    0, RLEFT|RESCC,
	"	trr	AR,AL\n",

ASSIGN, INAREG|FOREFF,
    MEM, TANY,		/* MEM was SAREG WED */
    STAREG, TSCALAR,	/* was SAREG WED */
    0, RLEFT|RRIGHT,	/* TUE also had RRIGHT */
	"	stZLP	AR,AL\n",

ASSIGN, INAREG|FOREFF,
    AWD, TANY,
    SAREG, TSCALAR,
    0, RLEFT,		/* TUE also had RRIGHT */
	"	stZLP	AR,AL\n",

/* 135 */
ASSIGN, INAREG|FOREFF,
    SAREG, TWORD|TFLOAT,	/* added TFLOAT NOV28 */
    SOREG|SCON|SNAME, TWORD|TFLOAT,	/* added FEB15 */
    0, RLEFT,
	"	lE	AL,QR\n",	/* add imm lit ops */

ASSIGN, INAREG|FOREFF|FORCC,	/* had FORCC NOV08 */
    SAREG, TCHAR,
    AWD, TWORD|THALF,
    0, RLEFT|RESCC,
	"	lZRP	AL,AR\n	anmw	AL,=x'ff'\n",

ASSIGN, INAREG|FOREFF|FORCC,	/* had FORCC NOV08 */
    SAREG, TANY,
    AWD, TCHAR,
    0, RLEFT|RESCC,
	"	lb	AL,AR\n",

ASSIGN, INAREG|FOREFF|FORCC,	/* had FORCC NOV08 */
    SAREG, TANY,
    AWD, TUSHORT,
    0, RLEFT|RESCC,
	"	zr	AL\n	ormh	AL,AR\n",

ASSIGN, INAREG|FOREFF|FORCC,
    SAREG, TANY,
    AWD, TNATURAL|TUNSIGNED|TFLOAT,
    0, RLEFT|RESCC,
	"	lZRP	AL,AR\n",

/* 140 */
ASSIGN, INAREG|FOREFF,
    AWD, TDOUBLE | TLONG,
    SAREG, TDOUBLE | TLONG,
    0, RLEFT,
	"	std	AR,AL\n",	/* fixed SAT */

ASSIGN, INAREG|FOREFF,
    SAREG, TDOUBLE | TLONG,
    SAREG, TDOUBLE | TLONG,
    0, RLEFT,
	"	trr	AR,AL\n	trr	UR,UL\n",

ASSIGN, INAREG|INTAREG|FOREFF,
    SAREG, TFLOAT,
    SAREG, TFLOAT,
    0, RLEFT,
	"G	trr	AR,AL\n",

ASSIGN, INAREG|FOREFF,
    AWD, TFLOAT,
    SAREG, TFLOAT,
    0, RLEFT,
	"	stw	AR,AL\n",

#ifdef IEEE_FIX
ASSIGN, INAREG|FOREFF,
    AWD, TDOUBLE | TLONG,
    SAREG, TFLOAT,
    0, RLEFT,
	"	zmw	UL\n	stw	AR,AL\n",
#endif /* IEEE_FIX */

#ifdef IEEE_FIX
ASSIGN, INAREG|FOREFF|FORCC,
    SAREG, TDOUBLE | TLONG,
    AWD, TFLOAT | TNATURAL | TSCALAR ,	/*| TUNSIGNED, */
    0, RLEFT|RESCC,
	"	zr	UL\n	lw	AL,AR\n",

ASSIGN, INAREG|FOREFF|FORCC,
    SAREG, TDOUBLE | TLONG,
    SAREG, TFLOAT,
    0, RLEFT|RESCC,
	"	zr	UL\n	trr	AR,AL\n",

#else /* IEEE_FIX */
ASSIGN, INAREG|FOREFF|FORCC,
    SAREG, TLONG,
    AWD, TFLOAT | TNATURAL | TSCALAR,
    0, RLEFT|RESCC,
	"	zr	UL\n	lw	AL,AR\n",

/* 145 */
ASSIGN, INAREG|FOREFF|FORCC,
    SAREG, TDOUBLE,
    AWD, TFLOAT,
    0, RLEFT|RESCC,
	"	lw	AL,AR\n	.cf2d	AL\n",

ASSIGN, INAREG|FOREFF|FORCC,
    SAREG, TLONG,
    SAREG, TFLOAT,
    0, RLEFT|RESCC,
	"G	trr	AR,AL\n	zr	UL\n",

ASSIGN, INAREG|FOREFF|FORCC,
    SAREG, TDOUBLE,
    SAREG, TFLOAT,
    0, RLEFT|RESCC,
	"G	trr	AR,AL\n	.cf2d	AL\n",

#endif /* IEEE_FIX */

#ifndef TEST_20FEB92
ASSIGN, INAREG|FOREFF,
    SZERO, TDOUBLE|TLONG,
    AWD, TWORD|TSCALAR|TFLOAT|TDOUBLE,	/* added TDOUBLE 20FEB92 */
    0, RESC1,
	"	zmZLP	AL\n",
#endif

ASSIGN, INAREG|FOREFF|FORCC,
    AWD, TDOUBLE | TLONG,
    AWD, TDOUBLE | TLONG,
/*    NASL|NDREG, RLEFT|RESCC, NASA FIX 01/24/96 */
    NDREG, RLEFT|RESCC,
	"	ld	A1,AR\n	std	A1,AL\n",

/* 150 */
#ifdef NASA_FIX_01_24_96
ASSIGN, FOREFF|FORCC,
    AWD, TDOUBLE | TLONG,
    AWD, TDOUBLE | TLONG,
    NASL|NDREG, RLEFT|RESCC,	/* NAREG was 0 */
	"	ld	A1,AR\n	std	A1,AL\n",
#endif

#ifdef IEEE_FIX
ASSIGN, INAREG|FOREFF|FORCC,
    AWD, TDOUBLE | TLONG,
    AWD, TFLOAT | TNATURAL | TUNSIGNED | TSCALAR,
    NAREG, RLEFT|RESCC,
	"	zmw	UL\n	lw	A1,AR\n	stw	A1,AL\n",

#else /* IEEE_FIX */
ASSIGN, INAREG|FOREFF|FORCC,
    AWD, TLONG,
    AWD, TFLOAT | TNATURAL | TUNSIGNED | TSCALAR,
    NAREG, RLEFT|RESCC,
	"	zmw	UL\n	lw	A1,AR\n	stw	A1,AL\n",

ASSIGN, INAREG|FOREFF|FORCC,
    AWD, TDOUBLE,
    AWD, TFLOAT,
    NASL|NDREG, RLEFT|RESCC,
	"	lw	A1,AR\n	.cf2d	A1\n	std	A1,AL\n",

#endif /* IEEE_FIX */

ASSIGN, INAREG|FOREFF,
    AWD, TWORD|TSCALAR|TFLOAT|TDOUBLE,	/* added TDOUBLE 20FEB92 */
    SZERO, TWORD|TANY,
    0, RESC1,
	"	zmZLP	AL\n",

ASSIGN, INAREG|FOREFF|FORCC,
    AWD, TWORD|TSCALAR|TFLOAT,
    SZERO, TANY,
    NAREG, RESC1|RLEFT|RESCC,
	"	zr	A1\n	stZLP	A1,AL\n",

ASSIGN, INAREG|FOREFF|FORCC,
    AWD, TWORD,
    SSCON, TWORD,
    NAREG|NASR, RLEFT|RESCC,
	"	li	A1,CR\n	stw	A1,AL\n",

ASSIGN, INAREG|FOREFF,
    SOREG|SCON|SNAME, TWORD,	/* added SNAME FEB15 */
    SCON, TWORD,
    NAREG|NASR, RLEFT,
	"	lE	A1,QR\n	stw	A1,AL\n",	/* add imm lit ops */

ASSIGN, INAREG|FOREFF|FORCC,
    AWD, TANY,
    SSCON, TNATURAL|TWORD|TLONG|TSCALAR,	/* FEB17 TLONG was TFLOAT */
    NAREG|NASR, RLEFT|RESCC,
	"	li	A1,CR\n	stZLP	A1,AL\n",

ASSIGN, INAREG|FOREFF|FORCC,
    AWD, TWORD,
    AWD, TWORD,
    NAREG|NASR, RLEFT|RESCC,
	"	lw	A1,AR\n	stw	A1,AL\n",	/* add imm ops */

ASSIGN, FOREFF|FORZCC,
    AWD, TBYTE,
    AWD, TUCHAR,
    NAREG|NASR, RLEFT|RESCC,
	"	lb	A1,AR\n	stb	A1,AL\n",

/* 130 */
ASSIGN, FOREFF,
    AWD, TBYTE,
    AWD, TSCALAR,
    NAREG|NASR, RLEFT,
	"	lZRP	A1,AR\n	stb	A1,AL\n",

ASSIGN, INAREG|FOREFF,	/* added DEC14 */
    AWD, TNATURAL|TSCALAR,
    AWD, TUSHORT,
    NAREG|NASR, RESC1|RLEFT,
	"	lZRP	A1,AR\n	anmw	A1,=x'ffff'\n	stZLP	A1,AL\n", 

ASSIGN, INAREG|FOREFF,
    AWD, THALF,
    AWD, TNATURAL|THALF|TWORD,
    NAREG|NASR, RESC1|RLEFT,
	"	lZRP	A1,AR\n	stZLP	A1,AL\n", /* DEC14 sth -> stZLP */

ASSIGN, INAREG|FOREFF|FORCC,
    AWD, TWORD|TFLOAT,
    AWD, TWORD|TFLOAT,
    NAREG|NASR, RESC1|RLEFT|RESCC,
	"	lw	A1,AR\n	stw	A1,AL\n",

ASSIGN, INAREG|FOREFF,
    AWD, TANY,
    AWD, TNATURAL|TWORD|TFLOAT|TSCALAR,
    NAREG|NASR, RLEFT,
	"	lZRP	A1,AR\n	stZLP	A1,AL\n",

ASSIGN, INAREG|FOREFF,
    SFLD, TANY,
    SICON, TANY,
    NAREG|NASR, RRIGHT,
	"JZF",

ASSIGN, INAREG|INTAREG|FOREFF|FORCC,
    SFLD, TANY,
    STAREG, TANY,
    NAREG, RRIGHT|RESCC,
	"J\
	lZP	A1,AL\n\
	anmw	A1,N\n\
D	sll	AR,H\n\
	anmw	AR,M\n\
	orr	AR,A1\n\
	stZP	A1,AL\n",

ASSIGN, INAREG|INTAREG|FOREFF,
    SFLD, TANY,
    SAREG, TANY,
    2*NAREG, RRIGHT,
	"J\
	trr	AR,A2\n\
	lZP	A1,AL\n\
	anmw	A1,N\n\
D	sll	A2,#H\n\
	anmw	A2,M\n\
	orr	A2,A1\n\
	stZP	A1,AL\n",

/* new for MPX */
ASGP, FOREFF,
    AWD, TSCALAR|TFLOAT,
    SAREG, TWORD,
    0, RLEFT,
	"	stcZP	AR,AL\n",

/* new for MPX */
ASGP, FOREFF,
    AWD, TLONG|TDOUBLE,
    SAREG, TDOUBLE|TLONG,
    0, RLEFT,
	"	stcZP	AR,AL\n",

/* new for MPX */
UMULP, FOREFF|INAREG|FORCC,
    AWD, TSCALAR|TFLOAT,
    SANY, TANY,
    NAREG|NASL, RESC1|RESCC,
	"	lcZP	A1,AL\n",

/* new for MPX */
UMULP, FOREFF|INAREG|FORCC,
    AWD, TLONG|TDOUBLE,
    SANY, TANY,
    NDREG|NASL, RESC1,
	"	lcZP	A1,AL\n",

/* 140 */
UNARY MUL, INAREG | FORCC,
    SOREG, TANY,	/* was awd */
    SAREG, TANY,
    NAREG, RESC1|RESCC,
	"	lw	A1,AL\n	lZP	A1,0,A1\n",

UNARY MUL, FOREFF|FORCC,	/* added FORCC FEB15 */
    SANY, TANY,
    SPOW2, TANY,
    0, RESC1|RESCC,	/* added FORCC FEB15 */
	"	tbm	Zn,AL\nZG",	/* was ZP FEB15 */

UNARY MUL, FOREFF|FORCC,	/* added FORCC FEB15 */
    SPOW2, TANY,
    SANY, TANY,
    0, RESC1|RESCC,	/* added FORCC FEB15 */
	"	tbm	Zn,AL\nZG",	/* was ZP FEB15 */

UNARY MUL, FOREFF,
    SCON, TANY,
    SANY, TANY,
    2 * NAREG, RESC1,
	"	lw	A2,AL\n	lZP	A1,0,A2\n",

UNARY MINUS, INTAREG|FORCC,	/* changes FRI */
    STAREG, TDOUBLE | TLONG,
    SANY, TANY,
    0, RLEFT|RESCC,
	"	trc	AL,AL\n	trn	UL,UL\n	bne	$+6\n	abr	AL,31\n",

UNARY MINUS, INTAREG|FORCC,
    AWD, TDOUBLE | TLONG,
    SANY, TANY,
    NAREG, RESC1|RESCC,
	"	lnd	A1,AL\n",

UNARY MINUS, INTAREG|INAREG|FORCC,
    SAREG|STAREG, TWORD|TFLOAT,
    SANY, TANY,
    NAREG|NASL, RESC1|RESCC,
	"	trn	AL,A1\n",

UNARY MINUS, INTAREG|INAREG|FORCC,	/* added INAREG MAR26 */
    AWD, TNATURAL|TPOINT|MEM,	/* added TPOINT|MEM MAR26 */
    SANY, TANY,
    NAREG, RESC1|RESCC,
	"	lnZLP	A1,AL\n",

COMPL, INTAREG|INAREG|FORCC,
    SAREG, TWORD,
    SANY, TANY,
    NAREG|NASL, RESC1|RESCC,
	"	trc	AL,A1\n",

AND, FOREFF|FORZCC,
    AWD, TWORD,		/* added THALF TBYTE SEP26 */
    SPOW2, TANY,
    0, RESCC,
	"	tbm	Zn,AL\nZB",	/* had ZJ FEB15 */

AND, FOREFF|FORZCC,
    AWD, THALF,		/* added THALF TBYTE SEP26 */
    SHPOW2, TANY,
    0, RESCC,
	"	tbm	Zn,AL\nZB",	/* had ZJ FEB15 */

AND, FOREFF|FORZCC,
    AWD, TBYTE,		/* added THALF TBYTE SEP26 */
    SBPOW2, TANY,
    0, RESCC,
	"	tbm	Zn,AL\nZB",	/* had ZJ FEB15 */

AND, FOREFF,	/* added whole thing SEP26 */
    AWD, TANY,		/* added THALF TBYTE SEP26 */
    SPOW2, TANY,
    0, RESCC,
	"	tbm	Zn,AL\nZB",	/* had ZJ FEB15 */

AND, FOREFF|FORZCC,
    SAREG, TWORD,
    SPOW2, TANY,
    0, RESCC,
	"	tbr	AL,Zn\nZB",	/* had ZJ FEB15 */

/* 150 */
AND, FORZCC,
    AWD, THALF,
    SHPOW2, TANY,
    0, RESCC,
	"	tbm	Zn,AL\nZB",

AND, FORZCC,
    AWD, TBYTE,
    SBPOW2, TANY,
    0, RESCC,
	"	tbm	Zn,AL\nZB",

ASG AND, FOREFF|FORCC,
    AWD, TWORD,
    SCPOW2, TANY,
    0, RNULL|RESCC,
	"	zbm	Zn,AL\n",

ASG AND, FOREFF|FORCC,
    SAREG, TWORD,
    SCPOW2, TANY,
    0, RNULL|RESCC,
	"	zbr	AL,Zn\n",

ASG AND, FOREFF|FORCC,
    AWD, THALF,
    SHCPOW2, TANY,
    0, RNULL|RESCC,
	"	zbm	Zn,AL\n",

ASG AND, FOREFF|FORCC,
    AWD, TBYTE,
    SBCPOW2, TANY,
    0, RNULL|RESCC,
	"	zbm	Zn,AL\n",

ASG OR, FOREFF,
    SAREG, TWORD,
    SPOW2, TANY,
    0, RNULL,
	"	sbr	AL,Zn\n",

ASG OR, FOREFF,
    AWD, TWORD,
    SPOW2, TANY,
    0, RNULL,
	"	sbm	Zn,AL\n",

ASG OR, FOREFF,
    AWD, THALF,
    SHPOW2, TANY,
    0, RNULL,
	"	sbm	Zn,AL\n",

ASG OR, FOREFF,
    AWD, TBYTE,
    SBPOW2, TANY,
    0, RNULL,
	"	sbm	Zn,AL\n",

/*
* machine botch. byte and short adds to memory don't set
* usable condition codes
*/
/* 160 */
PLUS, INAREG|INTAREG|FOREFF|FORCC,
    STAREG, TANY,	/* was TWORD OCT03 */
    SPOW2, TWORD,
    0, RLEFT|RESCC,
	"	abr	AL,Zn\n",

PLUS, INAREG|INTAREG|FOREFF|FORCC,
    STAREG, TSCALAR,	/* OCT05 was TWORD */
    SSCON, TWORD,
    0, RLEFT|RESCC,
	"	adi	AL,CR\n",

PLUS, INAREG|INTAREG|FOREFF|FORCC,
    STAREG, TWORD,
    AWD, TWORD,
    0, RLEFT|RESCC,
	"	admw	AL,AR\n",

PLUS, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TFLOAT,
    STAREG, TFLOAT,
    0, RRIGHT|RESCC,
	"	adfw	AR,AL\n",

PLUS, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TDOUBLE,
    STAREG, TDOUBLE,
    0, RRIGHT|RESCC,
	"	adfd	AR,AL\n",

/* START NOREG_REG */
PLUS, INAREG|INTAREG|FOREFF|FORCC|NOREG,	/* no reg version */
    STAREG, TFLOAT,
    STAREG, TFLOAT,
    NTEMP, RLEFT|RESCC,
	"	stw	AL,A1\n	adfw	AR,A1\n",

PLUS, INAREG|INTAREG|FOREFF|FORCC,	/* reg-reg version */
    STAREG, TFLOAT,
    STAREG, TFLOAT,
    0, RLEFT|RESCC,
	"	adrfw	AL,AR\n",

PLUS, INAREG|INTAREG|FOREFF|FORCC|NOREG,	/* no reg version */
    STAREG, TDOUBLE,
    STAREG, TDOUBLE,
    2*NTEMP, RLEFT|RESCC,
	"	std	AL,A1\n	adfd	AR,A1\n",

PLUS, INAREG|INTAREG|FOREFF|FORCC,	/* reg-reg version */
    STAREG, TDOUBLE,
    STAREG, TDOUBLE,
    0, RLEFT|RESCC,
	"	adrfd	AL,AR\n",
/* END NOREG_REG */

ASG PLUS, INAREG|FOREFF|FORCC,
    SAREG, TSSCALAR,
    STAREG, TPOINT,	/* make STAREG from SAREG to only use r0-r2 */
    0, RRIGHT|RESCC,
	"	adr	AL,AR\n",

ASG PLUS, INAREG|FOREFF|FORCC,
    SAREG, TPOINT,
    SAREG, TPOINT,
    0, RLEFT|RESCC,
	"	adr	AR,AL\n",

#ifdef VISTA_BUG
ASG PLUS, FOREFF,	/* had FORCC */
    AWD, TANY,
    SPOW2, TANY,
    0, 0,	/* had RESCC */
	"	abm	Zn,AL\n", /* JCB needs fix */
#else
#ifndef NEWWAY
ASG PLUS, FOREFF,
    AWD, TUSHORT,
    SPOW2, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	anmw	A1,=x'ffff'\n	abr	A1,Zo\n	stZLP	A1,AL\n",

ASG PLUS, FOREFF,
    AWD, THALF|TBYTE,
    SPOW2, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	abr	A1,Zo\n	stZLP	A1,AL\n",

ASG PLUS, FOREFF,
    AWD, TWORD,
    SPOW2, TANY,
    0, 0,
	"	abm	Zn,AL\n",
#endif
#endif

#ifdef ON26FEB92
ASG PLUS, FOREFF,
    AWD, TSCALAR,	/* OCT05 was TWORD */
    SSCON, TANY,
    NAREG, RNULL,
	"	li	A1,CR\n	armZLP	A1,AL\n",
#else
#ifndef NEWWAY
ASG PLUS, FOREFF,
    AWD, TUSHORT,
    SSCON, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	anmw	A1,=x'ffff'\n	adi	A1,CR\n	stZLP	A1,AL\n",

ASG PLUS, FOREFF,
    AWD, TBYTE|THALF,
    SSCON, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	adi	A1,CR\n	stZLP	A1,AL\n",

ASG PLUS, FOREFF,
    AWD, TWORD,
    SSCON, TANY,
    NAREG, RNULL,
	"	li	A1,CR\n	armZLP	A1,AL\n",
#endif
#endif

#ifndef NEWWAY
ASG PLUS, FOREFF,
    AWD, TFLOAT,	/* OCT05 was TWORD */
    SSCON, TANY,
    NAREG, RNULL,
	"	li	A1,CR\n	armZLP	A1,AL\n",
#endif

ASG PLUS, INAREG|FOREFF,	/* had FORCC */
    SAREG, TANY,	/* was TWORD OCT03 */
    SPOW2, TANY,
    0, RLEFT|RESCC,
	"	abr	AL,Zn\n",

#ifdef VISTA_BUG
ASG PLUS, FOREFF|INAREG,	/* had INAREG|FORCC */
    AWD, TANY,
    SPOW2, TANY,
    0, RLEFT,	/* had RLEFT|RESCC */
	"	abm	Zn,AL\n", /* JCB needs fix */
#else
#ifndef NEWWAY
ASG PLUS, FOREFF|INAREG,
    AWD, TUSHORT,
    SPOW2, TANY,
    NAREG, RLEFT,
	"	lZLP	A1,AL\n	anmw	A1,=x'ffff'\n	abr	A1,Zo\n	stZLP	A1,AL\n",

ASG PLUS, FOREFF|INAREG,
    AWD, TBYTE|THALF,
    SPOW2, TANY,
    NAREG, RLEFT,
	"	lZLP	A1,AL\n	abr	A1,Zo\n	stZLP	A1,AL\n",

ASG PLUS, FOREFF|INAREG,
    AWD, TWORD,
    SPOW2, TANY,
    0, RLEFT,
	"	abm	Zn,AL\n",
#endif
#endif

ASG PLUS, INAREG|INTAREG|FOREFF,
    STAREG, TSCALAR,	/* OCT05 was TWORD */
    SSCON, TWORD,
    0, RLEFT,
	"	adi	AL,CR\n",

#ifdef VISTA_BUG
ASG PLUS, INAREG|FOREFF,
    AWD, TUSHORT,	/* 113091 made THALF TSHORT */
    SAREG, TANY,
    0, RLEFT,
	"	anmw	AR,=x'ffff'\n	armZLP	AR,AL\n",
#else /* AUG171993 */
ASG PLUS, INAREG|FOREFF,
    AWD, TUSHORT,	/* 113091 made THALF TSHORT */
    SAREG, TANY,
    0, RLEFT,
	"	admZLP	AR,AL\n	anmw	AR,=x'ffff'\n	stZLP	AR,AL\n",

ASG PLUS, INAREG|FOREFF,
    AWD, TSHORT|TBYTE,
    SAREG, TANY,
    0, RLEFT,
	"	admZLP	AR,AL\n	stZLP	AR,AL\n",
#endif

#ifdef VISTA_BUG
ASG PLUS, INAREG|FOREFF,
    AWD, TWORD|TSHORT|TBYTE,	/* 113091 added TSHORT, TBYTE */
    SAREG, TANY,
    0, RLEFT,
	"	armZLP	AR,AL\n",
#else
ASG PLUS, INAREG|FOREFF,
    AWD, TWORD,		/* 113091 added TSHORT, TBYTE */
    SAREG, TANY,
    0, RLEFT,
	"	armZLP	AR,AL\n",
#endif

#ifdef COMP_BUG_AUG171993
ASG PLUS, FOREFF|INAREG|INTAREG,
    AWD, TUSHORT,
    SSCON, TANY,
    NAREG, RESC1,
	"	lZLP	A1,AL\n	anmw	=x'ffff'\n	adi	A1,CR\n\
		stZLP	A1,AL\nF	sui	A1,CR\n",

ASG PLUS, FOREFF|INAREG|INTAREG,
    AWD, TANY,
    SSCON, TANY,
    NAREG, RESC1,
	"	lZLP	A1,AL\n	adi	A1,CR\n\
	stZLP	A1,AL\nF	sui	A1,CR\n",
#endif

ASG PLUS, INAREG|INTAREG|FOREFF,
    AWD, TFLOAT,
    STAREG, TFLOAT,
    0, RRIGHT|RESCC,
/*	"	adfw	AR,AL\n", */
	"	adfw	AR,AL\n	stZLP	AR,AL\n",	/* NASA FIX 12/20/95 */

ASG PLUS, INAREG|INTAREG|FOREFF,
    AWD, TDOUBLE,
    STAREG, TDOUBLE,
    0, RRIGHT|RESCC,
/*	"	adfd	AR,AL\n", */
	"	adfd	AR,AL\n	stZLP	AR,AL\n",	/* NASA FIX 12/20/95 */

ASG PLUS, INAREG|INTAREG|FOREFF|FORCC,
    STAREG, TFLOAT,
    AWD, TFLOAT,
    0, RLEFT|RESCC,
	"	adfw	AL,AR\n",

ASG PLUS, INAREG|INTAREG|FOREFF|FORCC,
    STAREG, TDOUBLE,
    AWD, TDOUBLE,
    0, RLEFT|RESCC,
	"	adfd	AL,AR\n",

/* START NOREG_REG */
ASG PLUS, INAREG|INTAREG|FOREFF|FORCC|NOREG,	/* no reg-reg */
    STAREG, TFLOAT,
    STAREG, TFLOAT,
    NTEMP, RLEFT|RESCC,
	"	stw	AL,A1\n	adfw	AR,A1\n",

ASG PLUS, INAREG|INTAREG|FOREFF|FORCC,		/* reg-reg version */
    STAREG, TFLOAT,
    STAREG, TFLOAT,
    0, RLEFT|RESCC,
	"	adrfw	AL,AR\n",

ASG PLUS, INAREG|INTAREG|FOREFF|FORCC|NOREG,	/* no reg version */
    STAREG, TDOUBLE,
    STAREG, TDOUBLE,
    2*NTEMP, RLEFT|RESCC,
	"	std	AL,A1\n	adfd	AR,A1\n",

ASG PLUS, INAREG|INTAREG|FOREFF|FORCC,		/* reg-reg version */
    STAREG, TDOUBLE,
    STAREG, TDOUBLE,
    0, RLEFT|RESCC,
	"	adrfd	AL,AR\n",
/* END NOREG_REG */

MINUS, INAREG|INTAREG|FOREFF|FORCC,
    STAREG, TWORD,
    SSCON, TWORD,
    0, RLEFT|RESCC,
	"	sui	AL,CR\n",

/* 170 */
MINUS, INAREG|FOREFF|FORCC,
    AWD, TFLOAT,
    STAREG, TFLOAT,
    0, RRIGHT|RESCC,
	"	sufw	AR,AL\n",

MINUS, INAREG|FOREFF|FORCC,
    AWD, TDOUBLE,
    STAREG, TDOUBLE,
    0, RRIGHT|RESCC,
	"	sufd	AR,AL\n",

/* START NOREG_REG */
MINUS, INAREG|INTAREG|FOREFF|FORCC|NOREG,	/* no reg entry */
    STAREG, TFLOAT,
    STAREG, TFLOAT,
    NTEMP, RLEFT|RESCC,
	"	stw	AL,A1\n	sufw	AR,A1\n",

MINUS, INAREG|INTAREG|FOREFF|FORCC,		/* reg-reg entry */
    STAREG, TFLOAT,
    STAREG, TFLOAT,
    0, RLEFT|RESCC,
	"	surfw	AL,AR\n",

MINUS, INAREG|INTAREG|FOREFF|FORCC|NOREG,	/* no reg entry */
    STAREG, TDOUBLE,
    STAREG, TDOUBLE,
    2*NTEMP, RLEFT|RESCC,
	"	std	AL,A1\n	sufd	AR,A1\n",

MINUS, INAREG|INTAREG|FOREFF|FORCC,		/* reg-reg entry */
    STAREG, TDOUBLE,
    STAREG, TDOUBLE,
    0, RLEFT|RESCC,
	"	surfd	AL,AR\n",
/* END NOREG_REG */

#ifndef NEWWAY
ASG MINUS, FOREFF,
    AWD, TUSHORT,
    SSCON, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	anmw	A1,=x'ffff'\n	sui	A1,CR\n	stZLP	A1,AL\n",

ASG MINUS, FOREFF,
    AWD, TWORD,
    SSCON, TANY,
    NAREG, RNULL,
	"	li	A1,CR\n	armZLP	A1,AL\n",

ASG MINUS, FOREFF,
    AWD, TANY,
    SSCON, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	sui	A1,CR\n	stZLP	A1,AL\n",

ASG MINUS, FOREFF,
    AWD, TUSHORT,
    SCON, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	anmw	A1,=X'ffff'\n	sumZLP	A1,AR\n	stZLP	A1,AL\n",

ASG MINUS, FOREFF,
    AWD, TWORD,
    SSCON, TANY,
    NAREG, RNULL,
	"	lZRP	A1,AR\n	armZLP	A1,AL\n",

ASG MINUS, FOREFF,
    AWD, TANY,
    SCON, TANY,
    NAREG, RNULL,
	"	lZLP	A1,AL\n	sumZLP	A1,AR\n	stZLP	A1,AL\n",
#endif

ASG MINUS, INAREG|INTAREG|FOREFF,
    AWD, TFLOAT,
    STAREG, TFLOAT,
    0, RRIGHT|RESCC,
/*	"	sufw	AR,AL\n", */
	"	sufw	AR,AL\n	stZLP	AR,AL\n",	/* NASA FIX 12/20/95 */

ASG MINUS, INAREG|INTAREG|FOREFF,
    AWD, TDOUBLE,
    STAREG, TDOUBLE,
    0, RRIGHT|RESCC,
/*	"	sufd	AR,AL\n", */
	"	sufd	AR,AL\n	stZLP	AR,AL\n",	/* NASA FIX 12/20/95 */

ASG MINUS, INAREG|INTAREG|FOREFF|FORCC,
    STAREG, TFLOAT,
    AWD, TFLOAT,
    0, RLEFT|RESCC,
	"	sufw	AL,AR\n",

ASG MINUS, INAREG|INTAREG|FOREFF|FORCC,
    STAREG, TDOUBLE,
    AWD, TDOUBLE,
    0, RLEFT|RESCC,
	"	sufd	AL,AR\n",

/* START NOREG_REG */
ASG MINUS, INAREG|INTAREG|FOREFF|FORCC|NOREG,	/* no reg entry */
    STAREG, TFLOAT,
    STAREG, TFLOAT,
    NTEMP, RLEFT|RESCC,
	"	stw	AL,A1\n	sufw	AR,A1\n",

ASG MINUS, INAREG|INTAREG|FOREFF|FORCC,		/* reg-reg entry */
    STAREG, TFLOAT,
    STAREG, TFLOAT,
    0, RLEFT|RESCC,
	"	surfw	AL,AR\n",

ASG MINUS, INAREG|INTAREG|FOREFF|FORCC|NOREG,	/* no reg entry */
    STAREG, TDOUBLE,
    STAREG, TDOUBLE,
    2*NTEMP, RLEFT|RESCC,
	"	std	AL,A1\n	sufd	AR,A1\n",

ASG MINUS, INAREG|INTAREG|FOREFF|FORCC,		/* reg-reg entry */
    STAREG, TDOUBLE,
    STAREG, TDOUBLE,
    0, RLEFT|RESCC,
	"	surfd	AL,AR\n",
/* END NOREG_REG */

#ifndef COMP_BUG_AUG171993
ASG MINUS, FOREFF|INAREG|INTAREG,
    AWD, TUSHORT,
    SSCON, TANY,
    NAREG, RESC1,
	"	lZLP	A1,AL\n	anmw	=x'ffff'\n	sui	A1,CR\n\
		stZLP	A1,AL\nF	adi	A1,CR\n",

ASG MINUS, FOREFF|INAREG|INTAREG,
    AWD, TANY,
    SSCON, TANY,
    NAREG, RESC1,
	"	lZLP	A1,AL\n	sui	A1,CR\n\
	stZLP	A1,AL\nF	adi	A1,CR\n",

ASG MINUS, FOREFF|INAREG|INTAREG,
    AWD, TUSHORT,
    SCON, TANY,
    NAREG, RESC1,
	"	lZLP	A1,AL\n	anmw	=x'ffff'\n	sumw	A1,AR\n\
		stZLP	A1,AL\nF	admw	A1,AR\n",

ASG MINUS, FOREFF|INAREG|INTAREG,
    AWD, TANY,
    SCON, TANY,
    NAREG, RESC1,
	"	lZLP	A1,AL\n	sumw	A1,AR\n\
	stZLP	A1,AL\nF	admw	A1,AR\n",
#endif

#ifdef VISTA_BUG
ASG MINUS, INAREG|FOREFF,
    AWD, TSCALAR,
    STAREG, TANY,
    0, RLEFT,
	"	trn	AR,AR\n	armZLP	AR,AL\n",
#else
ASG MINUS, INAREG|FOREFF,
    AWD, TWORD,
    STAREG, TANY,
    0, RLEFT,
	"	trn	AR,AR\n	armZLP	AR,AL\n",

#ifndef NEWWAY
ASG MINUS, INAREG|FOREFF,
    AWD, TBYTE|THALF,
    STAREG, TANY,
    0, RLEFT,
	"	trn	AR,AR\n	admZLP	AR,AL\n	stZLP	AR,AL\n",
#endif
#endif

/* 207 */
MUL, INTAREG|FORCC,
    SAREG, TWORD,
    SAREG, TWORD,
    NASL|NDREG, RESUPPER|RESC1|RESCC,
	"G	trr	AL,U1\n	mpr	AR,A1\n",

MUL, INTAREG|FORCC,
    SAREG, TWORD,
    SAREG, TWORD,
    NASR|NDREG, RESUPPER|RESC1|RESCC,	/* DEC13 made NASL into NASR */
	"G	trr	AR,U1\n	mpr	AL,A1\n", /* DEC13 reversed AR & AL */

MUL, INTAREG|FORCC,	/* made SSCON from below */
    SAREG, TWORD,
    SSCON, TUNSIGNED|TNATURAL,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	mpi	A1,CR\n",

MUL, INTAREG|FORCC,
    SAREG, TWORD,
    AWD, TUNSIGNED|TNATURAL,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	mpmZRP	A1,AR\n",

MUL, INTAREG|FORCC,
    AWD, TUNSIGNED|TNATURAL,
    SAREG, TWORD,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AR,U1\n	mpmZLP	A1,AL\n",

MUL, INTAREG|FORCC,	/* made SSCON from below */
    AWD, TUNSIGNED|TNATURAL,
    SSCON, TUNSIGNED|TNATURAL,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"	lZLP	U1,AL\n	mpi	A1,CR\n",

MUL, INTAREG|FORCC,
    AWD, TUNSIGNED|TNATURAL,
    AWD, TUNSIGNED|TNATURAL,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"	lZLP	U1,AL\n	mpmZRP	A1,AR\n",

/* START NOREG_REG */
MUL, INTAREG|FORCC|NOREG,		/* no reg entry */
    STAREG, TFLOAT,
    SAREG, TFLOAT,
    NTEMP, RESCC|RLEFT,
	"	stw	AR,A1\n	mpfZLP	AL,A1\n",

MUL, INTAREG|FORCC,			/* reg-reg entry */
    STAREG, TFLOAT,
    SAREG, TFLOAT,
    0, RESCC|RLEFT,
	"	mprfZLP	AR,AL\n",
/* END NOREG_REG */

/* 215 */
MUL, INTAREG|FORCC,
    AWD, TFP,
    AWD, TFP,
    NASL|NDREG, RESCC|RESC1,	/* THU had RESUPPER|RESC1 */
	"	lZLP	A1,AL\n	mpfZRP	A1,AR\n",

MUL, INTAREG|FORCC,
    STAREG, TUNSIGNED|TNATURAL,
    SAREG, TWORD,
    NASR|NASL|NDREG, RESUPPER|RESCC|RESC1,	/* DEC13 added NASR */
	"G	trr	AL,U1\n	mpr	AR,A1\n",	/* WED */

MUL, INTAREG|FORCC,
    STAREG, TUNSIGNED|TNATURAL,
    SSCON, TUNSIGNED|TNATURAL,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	mpi	A1,CR\n",

MUL, INTAREG|FORCC,
    STAREG, TUNSIGNED|TNATURAL,
    AWD, TUNSIGNED|TNATURAL,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	mpmZRP	A1,AR\n",

MUL, INTAREG|FORCC,	/* ADDED INAREG MAR14 */
    STAREG, TANY,
#ifdef OCT1092
    SCCON, TANY,
#else
    SSCON, TANY,	/* 16 bit value, not 7 bit value */
#endif
    NASL|NDREG, RLEFT|RESCC,	/* was RESC1 SAT *//* added NDREG MAR21 */
	"	mpi	U1,CR\n",	/* MAR14 was AR,AR */

/* 220 */
MUL, INTAREG|FORCC,	/* ADDED INAREG MAR14 */
    STAREG, TANY,
    SAREG, TANY,
    NASL|NDREG, RRIGHT|RESCC,	/* DEC13 added NASR,chg RLLEFT to RRIGHT*/
	"	mpr	AR,U1\n",	/* DEC13 A1 was U1, AL was AR */

ASG MUL, INAREG|FOREFF|FORCC, /* JCB needs fix */
    SAREG, TSCALAR,
    SSCON, TSCALAR,
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AL,U1\n	mpi	A1,CR\n	trr	U1,AL\n",

ASG MUL, INAREG|FOREFF|FORCC, /* JCB needs fix */
    SAREG, TSCALAR,
    AWD, TSCALAR,
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AL,U1\n	mpmZRP	A1,AR\n	trr	U1,AL\n",

ASG MUL, INAREG|FOREFF|FORCC,	/* made SSCON from below */
    AWD, TSCALAR,
    SSCON, TSCALAR,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	mpi	A1,CR\n	stZLP	U1,AL\n",

ASG MUL, INAREG|FOREFF|FORCC, /* JCB needs fix */
    AWD, TSCALAR,
    SAREG, TSCALAR,
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AR,U1\n	mpmZLP	A1,AL\n	stZLP	U1,AL\n",

ASG MUL, INAREG|FOREFF|FORCC, /* JCB needs fix */
    AWD, TSCALAR,
    AWD, TSCALAR,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AR\n	mpmZRP	A1,AL\n	stZLP	U1,AL\n",

/* START NOREG_REG */
MUL, INTAREG|FORCC|NOREG,		/* no reg entry */
    SAREG, TFP,
    SAREG, TFP,
    2*NTEMP, RESCC|RLEFT,
	"	std	AR,A1\n	mpfZLP	AL,A1\n",

ASG MUL, INAREG|FOREFF|FORCC,		/* reg-reg entry */
    SAREG, TFP,
    SAREG, TFP,
    0, RESCC|RLEFT,
	"	mprfZLP	AR,AL\n",
/* END NOREG_REG */

ASG MUL, INAREG|FOREFF|FORCC,
    SAREG, TFP,
    AWD, TFP,
    0, RESCC|RLEFT,
	"	mpfZLP	AL,AR\n",    /* MAR21 */

ASG MUL, INAREG|FOREFF|FORCC,
    SAREG, TSCALAR,
    SAREG, TSCALAR,
    NASR|NASL|NDREG, RESCC|RLEFT,	/* DEC13 added NASR */
	"G	trr	AL,U1\n	mpr	AR,A1\n	trr	U1,AL\n",

/*
* special case: hardops has siphoned off all uns /= (int|uns) into
* calls to _udiv.  any TUNSIGNEDs came from reclaim promoting
*   UCHAR and USHORT to TUNSIGNED. But, UC and US can still be
* represented by TINT!
*/

DIV, INTAREG|FORCC,	/* added DEC14 */
    STAREG, TUNSIGNED,
    SAREG, TNATURAL|TUNSIGNED,	/* THU had AWD */
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	zr	A1\n	dvr	AR,A1\n",

DIV, INTAREG|FORCC,
    STAREG, TNATURAL,	/* deleted TUNSIGNED & made above entry */
    SAREG, TNATURAL|TUNSIGNED,	/* THU had AWD */
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	es	A1\n	dvr	AR,A1\n",

DIV, INTAREG|FORCC,	/* added DEC14 */
    SAREG, TUNSIGNED,
    SAREG, TNATURAL|TUNSIGNED,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	zr	A1\n	dvr	AR,A1\n",

DIV, INTAREG|FORCC,
    SAREG, TNATURAL,	/* deleted TUNSIGNED & made above entry */
    SAREG, TNATURAL|TUNSIGNED,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	es	A1\n	dvr	AR,A1\n",

DIV, INTAREG|FORCC,
    AWD, TNATURAL|TUNSIGNED,
    SAREG, TNATURAL|TUNSIGNED,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"	lZLP	U1,AL\n	es	A1\n	dvr	AR,A1\n",

/* START NOREG_REG */
DIV, INTAREG|FOREFF|FORCC|NOREG,	/* FIX_080395 no reg entry */
    STAREG|SAREG, TFLOAT,
    SAREG, TFLOAT,
    NTEMP, RESCC|RLEFT,
	"	stw	AR,A1\n	dvfZLP	AL,A1\n",

DIV, INTAREG|FOREFF|FORCC|NOREG,	/* FIX_080395 no reg entry */
    STAREG|SAREG, TFP,
    SAREG, TFP,
    2*NTEMP, RESCC|RLEFT,
	"	std	AR,A1\n	dvfZLP	AL,A1\n",

DIV, INTAREG|FOREFF|FORCC,		/* FIX_080395 reg-reg entry */
    STAREG|SAREG, TFP,
    SAREG, TFP,
    0, RESCC|RLEFT,
	"	dvrfZLP	AR,AL\n",
/* END NOREG_REG */

DIV, INTAREG|FORCC|FOREFF,
    STAREG, TANY,
    SAREG, TANY,
    NASL|NDREG, RESC1|RESCC,	/* TUE was just NAREG */
	"G	trr	AR,A1\n	es	AR\n	dvr	AL,AR\n",

DIV, INTAREG|FORCC,		/* ADDED TUE */
    STAREG, TANY,
    SAREG, TANY,
    NAREG, RLEFT|RESCC,		/* SAT */
	"G	trr	AR,U1\n	es	A1\n	dvr	AR,A1\n",

DIV, INTAREG|FORCC,
    SAREG, TNATURAL|TUNSIGNED,
    SSCON, TNATURAL|TUNSIGNED,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	es	A1\n	dvi	A1,CR\n",

DIV, INTAREG|FORCC,		/* made SSCON from below */
    SAREG, TNATURAL|TUNSIGNED,
    SSCON, TNATURAL|TUNSIGNED,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	es	A1\n	dvi	A1,CR\n",

DIV, INTAREG|FORCC,
    AWD, TNATURAL|TUNSIGNED,
    SSCON, TNATURAL|TUNSIGNED,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"	lZLP	U1,AL\n	es	A1\n	dvi	A1,CR\n",

DIV, INTAREG|FORCC,
    SAREG, TUSHORT,
    AWD, TUSHORT,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	zr	A1\n	anmw	U1,=x'ffff'\n\
\tlh	r2,AR\n\
\tanmw	r2,=x'ffff'\n\
\tdvr	r2,A1\n",

DIV, INTAREG|FORCC,
    SAREG, TUSHORT,
    AWD, TUNSVAL,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	zr	A1\n\
	anmw	U1,=x'ffff'\n	dvmZRP	A1,AR\n",

DIV, INTAREG|FORCC,
    SAREG, TUNSVAL|TNATURAL,	/* added TNATURAL FEB25 */
    AWD, TUSHORT,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	zr	A1\n\
\tlh	r2,AR\n\
\tanmw	r2,=x'ffff'\n\
\tdvr	r2,A1\n",

DIV, INTAREG|FORCC,
    SAREG, TUNSVAL|TNATURAL,	/* added TNATURAL FEB25 */
    AWD, TUNSVAL,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	zr	A1\n	dvmZRP	A1,AR\n",

DIV, INTAREG|FORCC,
    SAREG, TNATURAL,
    AWD, TNATURAL,
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"G	trr	AL,U1\n	es	A1\n	dvmZRP	A1,AR\n",

DIV, INTAREG|FORCC,
    AWD, TUSHORT,
    AWD, TUSHORT,		/* had SAREG| FEB25 */
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"	lZLP	U1,AL\n	zr	A1\n	anmw	U1,=x'ffff'\n\
\tlh	r2,AR\n\
\tanmw	r2,=x'ffff'\n\
\tdvr	r2,A1\n",

DIV, INTAREG|FORCC,
    AWD, TUSHORT,
    AWD, TUNSVAL,		/* had SAREG| FEB25 */
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"	lZLP	U1,AL\n	zr	A1\n\
	anmw	U1,=x'ffff'\n	dvmZRP	A1,AR\n",

DIV, INTAREG|FORCC,
    AWD, TUNSVAL,
    AWD, TUSHORT,		/* had SAREG| FEB25 */
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"	lZLP	U1,AL\n	zr	A1\n\
\tlh	r2,AR\n\
\tanmw	r2,=x'ffff'\n\
\tdvr	r2,A1\n",

DIV, INTAREG|FORCC,
    AWD, TUNSVAL,
    AWD, TUNSVAL,		/* had SAREG| FEB25 */
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"	lZLP	U1,AL\n	zr	A1\n	dvmZRP	A1,AR\n",

DIV, INTAREG|FORCC,
    AWD, TNATURAL,		/* had TUNSIGNED FEB25 */
    AWD, TNATURAL,		/* had TUNSIGNED SAREG| FEB25 */
    NASL|NDREG, RESUPPER|RESCC|RESC1,
	"	lZLP	U1,AL\n	es	A1\n	dvmZRP	A1,AR\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TUSHORT,
    SSCON, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	anmw	U1,=x'ffff'\n\
	zr	A1\n	dvi	A1,CR\n	stZLP	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TUNSVAL,
    SSCON, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	zr	A1\n\
	dvi	A1,CR\n	stZLP	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TSCALAR|TPOINT,
    SSCON, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	es	A1\n\
	dvi	A1,CR\n	stZLP	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    STAREG|SAREG, TUSHORT,
    SSCON, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AL,U1\n	anmw	U1,=x'ffff'\n\
	zr	A1\n	dvi	A1,CR\n	trr	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    STAREG|SAREG, TUNSVAL,
    SSCON, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AL,U1\n	zr	A1\n\
	dvi	A1,CR\n	trr	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    STAREG|SAREG, TSCALAR|TPOINT,
    SSCON, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AL,U1\n	es	A1\n\
	dvi	A1,CR\n	trr	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    STAREG|SAREG, TUSHORT,
    AWD, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AL,U1\n	zr	A1\n\
	anmw	U1,=x'ffff'\n	dvmZRP	A1,AR\n	trr	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    STAREG|SAREG, TUNSVAL,
    AWD, TSCALAR|TUNSVAL,		/* added TUNSVAL DEC06 */
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AL,U1\n	zr	A1\n\
	dvmZRP	A1,AR\n	trr	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    STAREG|SAREG, TSCALAR|TPOINT,
    AWD, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AL,U1\n	es	A1\n\
	dvmZRP	A1,AR\n	trr	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TUSHORT,
    AWD, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	anmw	U1,=x'ffff'\n\
	zr	A1\n	dvmZRP	A1,AR\n	stZLP	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TUNSVAL,
    AWD, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	zr	A1\n\
	dvmZRP	A1,AR\n	stZLP	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TSCALAR|TPOINT,
    AWD, TUSHORT,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	zr	A1\n\
\tlh	r2,AR\n\
\tanmw	r2,=x'ffff'\n\
\tdvr	r2,A1\n\
	stZLP	U1,AL\n",
/* 	dvmZRP	A1,AR\n	stZLP	U1,AL\n", */

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TSCALAR|TPOINT,
    AWD, TUNSVAL,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	zr	A1\n\
	dvmZRP	A1,AR\n	stZLP	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TSCALAR|TPOINT,
    AWD, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	es	A1\n\
	dvmZRP	A1,AR\n	stZLP	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    STAREG|SAREG, TUSHORT,
    STAREG|SAREG, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AL,U1\n	zr	A1\n\
	anmw	U1,=x'ffff'\n	dvr	AR,A1\n	trr	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    STAREG|SAREG, TUNSVAL,
    STAREG|SAREG, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AL,U1\n	zr	A1\n\
	dvr	AR,A1\n	trr	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    STAREG|SAREG, TSCALAR|TPOINT,
    STAREG|SAREG, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"G	trr	AL,U1\n	es	A1\n\
	dvr	AR,A1\n	trr	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TUSHORT,
    SAREG|STAREG, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	anmw	U1,=x'ffff'\n\
	zr	A1\n	dvr	AR,A1\n	stZLP	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TUNSVAL,
    SAREG|STAREG, TSCALAR|TPOINT,
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	zr	A1\n	dvr	AR,A1\n	stZLP	U1,AL\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,
    AWD, TSCALAR|TPOINT,
    SAREG|STAREG, TSCALAR|TPOINT,	/* had TUNSIGNED FEB25 */
    NASL|NDREG, RESCC|RLEFT,
	"	lZLP	U1,AL\n	es	A1\n	dvr	AR,A1\n	stZLP	U1,AL\n",

/* START NOREG_REG */
ASG DIV, INAREG|INTAREG|FOREFF|FORCC|NOREG,	/* FIX_080395 no reg entry */
    STAREG|SAREG, TFLOAT,
    SAREG, TFLOAT,
    NTEMP, RESCC|RLEFT,
	"	stw	AR,A1\n	dvfZLP	AL,A1\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC|NOREG,	/* no reg entry */
    STAREG|SAREG, TFP,
    SAREG, TFP,
    2*NTEMP, RESCC|RLEFT,
	"	std	AR,A1\n	dvfZLP	AL,A1\n",

ASG DIV, INAREG|INTAREG|FOREFF|FORCC,		/* reg-reg entry */
    STAREG|SAREG, TFP,
    SAREG, TFP,
    0, RESCC|RLEFT,
	"	dvrfZLP	AR,AL\n",
/* END NOREG_REG */

ASG DIV, INAREG|FOREFF|FORCC,
    STAREG|SAREG, TFP,
    AWD, TFP,
    0, RESCC|RLEFT,
	"	dvfZLP	AL,AR\n",

MOD, INAREG,	/* TUE modified */
    STAREG, TANY,
    STAREG, TANY,
    NASL|NDREG, RLEFT,
	"G	trr	AR,A1\n	es	AR\n	dvr	AL,AR\n",

MOD, INTAREG,
    STAREG, TNATURAL|TUNSIGNED,
    SAREG, TNATURAL|TUNSIGNED,	/* THU had AWD */
    NASL|NDREG, RESC1,
	"G	trr	AL,U1\n	es	A1\n	dvr	AR,A1\n",

MOD, INTAREG,	/* fixed SAT */
    STAREG, TANY,
    SAREG, TANY,
    NAREG, RRIGHT,/* added NASL THU */
	"G	trr	AR,U1\n	es	A1\n	dvr	AR,A1\n",

MOD, INTAREG,	/* MON */
    SAREG, TNATURAL|TUNSIGNED,
    SAREG, TNATURAL|TUNSIGNED,
    NASL|NDREG, RESC1,
	"G	trr	AL,U1\n	es	A1\n	dvr	AR,A1\n",

MOD, INTAREG,	/* MON */
    AWD, TNATURAL|TUNSIGNED,
    SAREG, TNATURAL|TUNSIGNED,
    NASL|NDREG, RESC1,
	"	lZLP	U1,AL\n	es	A1\n	dvr	AR,A1\n",

MOD, INTAREG,	/* MON */ /* SEP26 */
    SSCON, TNATURAL|TUNSIGNED,
    SAREG, TNATURAL|TUNSIGNED,
    NASL|NDREG, RESC1,
	"G	trr	AL,U1\n	es	A1\n	dvi	A1,CR\n",

MOD, INTAREG,	/* FRI */ /* SEP26 */
    SAREG, TNATURAL|TUNSIGNED,
    SSCON, TNATURAL|TUNSIGNED,	/* had AWD FRI */
    NASL|NDREG, RESC1,
	"G	trr	AL,U1\n	es	A1\n	dvi	A1,CR\n",

MOD, INTAREG,
    AWD, TNATURAL|TUNSIGNED,
    SSCON, TNATURAL|TUNSIGNED,
    NASL|NDREG, RESC1,
	"	lZLP	U1,AL\n	es	A1\n	dvi	A1,CR\n",

MOD, INTAREG,
    SAREG|STAREG, TUSHORT,
    AWD, TUSHORT,
    NASL|NDREG, RESC1,
	"G	trr	AL,U1\n	zr	A1\n	anmw	U1,=x'ffff'\n\
\tlh	r2,AR\n\
\tanmw	r2,=x'ffff'\n\
\tdvr	r2,A1\n",
/*	dvmZRP	A1,AR\n", */

MOD, INTAREG,
    SAREG|STAREG, TUNSVAL|TNATURAL,
    AWD, TUSHORT,
    NASL|NDREG, RESC1,
	"G	trr	AL,U1\n	zr	A1\n\
\tlh	r2,AR\n\
\tanmw	r2,=x'ffff'\n\
\tdvr	r2,A1\n",
/*	dvmZRP	A1,AR\n", */

MOD, INTAREG,
    SAREG|STAREG, TUSHORT,
    AWD, TUNSVAL,
    NASL|NDREG, RESC1,
	"G	trr	AL,U1\n	zr	A1\n\
	anmw	U1,=x'ffff'\n	dvmZRP	A1,AR\n",

MOD, INTAREG,
    SAREG|STAREG, TUNSVAL|TNATURAL,
    AWD, TUNSVAL,
    NASL|NDREG, RESC1,
	"G	trr	AL,U1\n	zr	A1\n	dvmZRP	A1,AR\n",

MOD, INTAREG,	/* MON */
    SAREG|STAREG, TNATURAL,	/* had TUNSIGNED FEB25 */
    AWD, TNATURAL,		/* had SAREG|AWD TUNSIGNED FEB25 */
    NASL|NDREG, RESC1,		/* had RESUPPER FEB 12 */
	"G	trr	AL,U1\n	es	A1\n	dvmZRP	A1,AR\n",

MOD, INTAREG,
    STAREG, TNATURAL,	/* had TUNSIGNED */
    AWD, TNATURAL|TUNSIGNED,
    NASL|NDREG, RESC1,
	"G	trr	AL,U1\n	es	A1\n	dvmZRP	A1,AR\n",

ASG MOD, INAREG|INTAREG,
    SAREG|STAREG, TUSHORT,
    SSCON, TSCALAR|TPOINT,
    NASL|NDREG, RESC1|RLEFT,
	"G	trr	AL,U1\n	anmw	U1,=x'ffff'\n\
	zr	A1\n	dvi	A1,CR\n	trr	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    SAREG|STAREG, TUNSVAL,
    SSCON, TSCALAR|TPOINT,
    NASL|NDREG, RESC1|RLEFT,
	"G	trr	AL,U1\n	zr	A1\n\
	dvi	A1,CR\n	trr	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    SAREG|STAREG, TSCALAR|TPOINT,	/* added TSCALAR */
    SSCON, TSCALAR|TPOINT,	/* added TSCALAR */
    NASL|NDREG, RESC1|RLEFT,
	"G	trr	AL,U1\n	es	A1\n\
	dvi	A1,CR\n	trr	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    AWD, TUSHORT,
    SSCON, TSCALAR|TPOINT,
    NASL|NDREG, RESC1|RLEFT,
	"	lZLP	U1,AL\n	anmw	U1,=x'ffff'\n\
	zr	A1\n	dvi	A1,CR\n	stZLP	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    AWD, TUNSVAL,
    SSCON, TSCALAR|TPOINT,
    NASL|NDREG, RESC1|RLEFT,
	"	lZLP	U1,AL\n	zr	A1\n\
	dvi	A1,CR\n	stZLP	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    AWD, TSCALAR|TPOINT,
    SSCON, TSCALAR|TPOINT,
    NASL|NDREG, RESC1|RLEFT,
	"	lZLP	U1,AL\n	es	A1\n\
	dvi	A1,CR\n	stZLP	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    SAREG|STAREG, TUSHORT,
    AWD, TSCALAR|TPOINT,	/* TRY THIS instead of TUSHORT */
    NASL|NDREG, RESC1|RLEFT,
	"G	trr	AL,U1\n	anmw	U1,=x'ffff'\n\
	zr	A1\n	dvmZRP	A1,AR\n	trr	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    SAREG|STAREG, TUNSVAL,
    AWD, TSCALAR|TUNSVAL,	/* added TUNSVAL DEC06 */
    NASL|NDREG, RESC1|RLEFT,
	"G	trr	AL,U1\n	zr	A1\n\
	dvmZRP	A1,AR\n	trr	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    SAREG|STAREG, TSCALAR|TPOINT,	/* added TSCALAR */
    AWD, TSCALAR|TPOINT,	/* added TSCALAR */
    NASL|NDREG, RESC1|RLEFT,
	"G	trr	AL,U1\n	es	A1\n\
	dvmZRP	A1,AR\n	trr	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    SAREG|STAREG, TUSHORT,
    SAREG|STAREG, TSCALAR|TPOINT,
    NASL|NDREG, RESC1|RLEFT,
	"G	trr	AL,U1\n	anmw	U1,=x'ffff'\n\
	zr	A1\n	dvr	AR,A1\n	trr	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    SAREG|STAREG, TUNSVAL,
    SAREG|STAREG, TSCALAR|TPOINT,
    NASL|NDREG, RESC1|RLEFT,
	"G	trr	AL,U1\n	zr	A1\n\
	anmw	U1,=x'ffff'\n	dvr	AR,A1\n	trr	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    SAREG|STAREG, TSCALAR|TPOINT,
    SAREG|STAREG, TSCALAR|TPOINT,
    NASL|NDREG, RESC1|RLEFT,
	"G	trr	AL,U1\n	es	A1\n\
	dvr	AR,A1\n	trr	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    AWD, TUSHORT,
    AWD, TSCALAR|TPOINT,	/* TRY THIS instead of TUSHORT */
    NASL|NDREG, RESC1|RLEFT,
	"	lZLP	U1,AL\n	anmw	U1,=x'ffff'\n\
	zr	A1\n	dvmZRP	A1,AR\n	stZLP	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    AWD, TUNSVAL,
    AWD, TSCALAR|TUNSVAL,	/* added TUNSVAL DEC06 */
    NASL|NDREG, RESC1|RLEFT,
	"	lZLP	U1,AL\n	zr	A1\n\
	dvmZRP	A1,AR\n	stZLP	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    AWD, TSCALAR|TUNSVAL,	/* added TUNSVAL DEC06 */
    AWD, TUSHORT,
    NASL|NDREG, RESC1|RLEFT,
	"	lZLP	U1,AL\n	zr	A1\n\
\tlh	r2,AR\n\
\tanmw	r2,=x'ffff'\n\
\tdvr	r2,A1\n\
	stZLP	A1,AL\n",
/*	dvmZRP	A1,AR\n	stZLP	A1,AL\n", */

ASG MOD, INAREG|INTAREG,
    AWD, TSCALAR|TUNSVAL,	/* added TUNSVAL DEC06 */
    AWD, TUNSVAL,
    NASL|NDREG, RESC1|RLEFT,
	"	lZLP	U1,AL\n	zr	A1\n\
	dvmZRP	A1,AR\n	stZLP	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    AWD, TSCALAR|TPOINT,		/* had TUNSIGNED FEB25 */
    AWD, TSCALAR|TPOINT,		/* had TUNSIGNED FEB25 */
    NASL|NDREG, RESC1|RLEFT,
	"	lZLP	U1,AL\n	es	A1\n	dvmZRP	A1,AR\n	stZLP	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    AWD, TUSHORT,
    SAREG|STAREG, TSCALAR|TPOINT,
    NASL|NDREG, RESC1|RLEFT,
	"	lZLP	U1,AL\n	anmw	U1,=x'ffff'\n\
	zr	A1\n	dvr	AR,A1\n	stZLP	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    AWD, TUNSVAL,
    SAREG|STAREG, TSCALAR|TPOINT,
    NASL|NDREG, RESC1|RLEFT,
	"	lZLP	U1,AL\n	zr	A1\n	anmw	=x'ffff'\n\
	dvr	AR,A1\n	stZLP	A1,AL\n",

ASG MOD, INAREG|INTAREG,
    AWD, TSCALAR|TPOINT,
    SAREG|STAREG, TSCALAR|TPOINT,	/* had TUNSIGNED FEB25 */
    NASL|NDREG, RESC1|RLEFT,
	"	lZLP	U1,AL\n	es	A1\n	dvr	AR,A1\n	stZLP	A1,AL\n",

/*    NOTE!!!!, TSCALAR is a lie... But negative shifts are
 *    guaranteed to be unpredictable, therefore ignore that the
 *    sel hardware can't properly load signed char, unsigned
 *    short,....
 */

SRA, INTAREG|FOREFF|FORCC,	/* SPR02_25_94 */
    STAREG, TANY,
    SCCON, TANY,
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	sra	AL,CR\n",

ASG SRA, INTAREG|INAREG|FOREFF|FORCC,	/* SPR02_25_94 */
    SAREG, TANY,
    SCCON, TANY,
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	sra	AL,CR\n",

ASG RS, INTAREG|INAREG|FOREFF|FORZCC,	/* SPR02_25_94 */
    SAREG, TINT,
    SCCON, TUSHORT,
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	srl	AL,CR\n",

ASG RS, INTAREG|INAREG|FOREFF|FORZCC,	/* SPR02_25_94 */
    SAREG, TINT,
    SCCON, TUNSVAL,
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	srl	AL,CR\n",

ASG RS, INTAREG|INAREG|FOREFF|FORZCC,	/* SPR02_25_94 */
    SAREG, TUSHORT,
    SCCON, TANY,		/* was SCON */
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	srl	AL,CR\n",

#ifndef SPR02_25_94
ASG RS, INTAREG|INAREG|FOREFF|FORZCC,	/* SPR02_25_94 */
    SAREG, TUNSVAL,	/* was TUSCALAR FEB25 */
    SCCON, TANY,		/* was SCON */
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	srl	AL,CR\n",

#else /* SPR02_25_94 */
ASG RS, INTAREG|INAREG|FOREFF,
    SAREG, TUNSVAL,	/* was TUSCALAR FEB25 */
    SCCON, TANY,		/* was SCON */
    0, RLEFT,
	"	srl	AL,CR\n",
#endif /* SPR02_25_94 */

ASG RS, INTAREG|INAREG|FOREFF|FORCC,	/* SPR02_25_94 */
    SAREG, TINT,
    SCCON, TNATURAL,	/* was TSCALAR DEC03 */
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	sra	AL,CR\n",	/* DEC13 was sra */

ASG RS, INTAREG|INAREG|FOREFF|FORCC,	/* SPR02_25_94 */
    SAREG, TANY,
    SCCON, TANY,		/* was SCON */
    0, RESC1|RLEFT|RESCC,		/* added RESC1 MAR21 */
	"	sra	AL,CR\n",	/* DEC13 was sra */

ASG RS, INAREG|FORZCC,	/* SPR02_25_94 */
    SAREG, TUSHORT,
    AWD, TSCALAR,
    NAREG, RLEFT|RESCC,	/* SPR02_25_94 */
    "	li	A1,x'1f'\n\
	anmZRP	A1,AR\n\
	ormh	A1,$+1w\n\
	srl	AL,0\n\
	exrr	A1\n",

ASG RS, INAREG|FORZCC,	/* SPR02_25_94 */
    SAREG, TUNSVAL,
    AWD, TSCALAR,
    NAREG, RLEFT|RESCC,	/* SPR02_25_94 */
    "	li	A1,x'1f'\n\
	anmZRP	A1,AR\n\
	ormh	A1,$+1w\n\
	srl	AL,0\n\
	exrr	A1\n",

ASG RS, INAREG|FORCC,	/* SPR02_25_94 */
 SAREG, TNATURAL,
 AWD, TSCALAR,
    NAREG, RLEFT|RESCC,	/* SPR02_25_94 */
  "	li	A1,x'1f'\n\
	anmZRP	A1,AR\n\
	ormh	A1,$+1w\n\
	sra	AL,0\n\
	exrr	A1\n",

SLA, INTAREG|FOREFF|FORCC,	/* SPR02_25_94 */
    STAREG, TANY,
    SCCON, TANY,
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	sla	AL,CR\n",

ASG SLA, INTAREG|INAREG|FOREFF|FORCC,	/* SPR02_25_94 */
    SAREG, TANY,
    SCCON, TANY,
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	sla	AL,CR\n",

ASG LS, INTAREG|INAREG|FOREFF|FORCC,	/* SPR02_25_94 */
    SAREG, TUSHORT,
    SCCON, TANY,	/* was SCON */
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	sll	AL,CR\n",

ASG LS, INTAREG|INAREG|FOREFF|FORZCC,	/* SPR02_25_94 */
    SAREG, TUNSVAL,	/* as TUSCALAR FEB25 */
    SCCON, TANY,	/* was SCON */
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	sll	AL,CR\n",

ASG LS, INTAREG|INAREG|FOREFF|FORZCC,	/* SPR02_25_94 */
    SAREG, TNATURAL,
    SCCON, TUSHORT,
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	sll	AL,CR\n",

ASG LS, INTAREG|INAREG|FOREFF|FORZCC,	/* SPR02_25_94 */
    SAREG, TNATURAL,
    SCCON, TUNSVAL,
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	sll	AL,CR\n",

ASG LS, INTAREG|INAREG|FOREFF|FORZCC,	/* SPR02_25_94 */
    SAREG, TNATURAL,
    SCCON, TANY,	/* was SCON */
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	sll	AL,CR\n",	/* DEC13 was sla */

ASG LS, INAREG|FORCC,	/* SPR02_25_94 */
 SAREG, TUSHORT,
 AWD, TSCALAR,
  NAREG, RLEFT|RESCC,	/* SPR02_25_94 */
  "	li	A1,x'1f'\n\
	anmZRP	A1,AR\n\
	ormh	A1,$+1w\n\
	sll	AL,0\n\
	exrr	A1\n",

ASG LS, INAREG|FORZCC,	/* SPR02_25_94 */
 SAREG, TUNSVAL,
 AWD, TSCALAR,
  NAREG, RLEFT|RESCC,	/* SPR02_25_94 */
  "	li	A1,x'1f'\n\
	anmZRP	A1,AR\n\
	ormh	A1,$+1w\n\
	sll	AL,0\n\
	exrr	A1\n",

ASG LS, INAREG|FORCC,	/* SPR02_25_94 */
 SAREG, TNATURAL,
 AWD, TSCALAR,
  NAREG, RLEFT|RESCC,	/* SPR02_25_94 */
  "	li	A1,x'1f'\n\
	anmZRP	A1,AR\n\
	ormh	A1,$+1w\n\
	sll	AL,0\n\
	exrr	A1\n",

ASG OPSHFT, INAREG|FORCC,	/* SPR02_25_94 */
 SAREG, TANY,
 SCCON, TSCALAR,	/* was SSCON */
  NAREG, RLEFT|RESCC,	/* SPR02_25_94 */
  "	lZRP	A1,AR\n\
	anmw	A1,=x'1f'\n\
	ormh	A1,$+1w\n\
	OI	AL,0\n\
	exrr	A1\n",

ASG OPSHFT, INAREG|FORCC,	/* SPR02_25_94 */
 SAREG, TSCALAR,
 STAREG, TSCALAR,
  0, RLEFT|RESCC,	/* SPR02_25_94 */
  "	anmw	AR,=x'1f'\n\
	ormh	AR,$+1w\n\
	OI	AL,0\n\
	exrr	AR\n",

ASG OPSHFT, INAREG|FORCC,	/* SPR02_25_94 */
 SAREG, TSCALAR,
 SAREG, TSCALAR,
  NAREG, RLEFT|RESCC,	/* SPR02_25_94 */
  "	trr	AR,A1\n\
	anmw	A1,=x'1f'\n\
	ormh	A1,$+1w\n\
	OI	AL,0\n\
	exrr	A1\n",

ASG OPSHFT, INAREG|FORCC,	/* SPR02_25_94 */
 SAREG, TSCALAR,
 AWD, TSCALAR,
  NAREG, RLEFT|RESCC,	/* SPR02_25_94 */
  "	li	A1,x'1f'\n\
	anmZRP	A1,AR\n\
	ormh	A1,$+1w\n\
	OI	AL,0\n\
	exrr	A1\n",

ASG OPSHFT, INAREG|FORCC,	/* SPR02_25_94 */
 SAREG, TLONG,
 AWD, TSCALAR,
  NAREG, RLEFT|RESCC,	/* SPR02_25_94 */
  "	li	A1,x'1f'\n\
	anmZRP	A1,AR\n\
	ormh	A1,$+1w\n\
	OD	AL,0\n\
	exrr	A1\n",

ASG OPSHFT, INAREG|FORCC,	/* SPR02_25_94 */
 AWD, TSCALAR,
 STAREG, TSCALAR,
  NAREG, RESC1|RESCC,	/* SPR02_25_94 */
  "	lZLP	A1,AL\n\
	anmw	AR,=x'1f'\n\
	ormh	AR,$+1w\n\
	OI	A1,0\n\
	exrr	AR\n\
	stZLP	A1,AL\n",

ASG OPSHFT, INAREG|FORCC,	/* SPR02_25_94 */
 AWD, TLONG,
 SAREG, TSCALAR,
  NTEMP, RRIGHT|RESCC,	/* SPR02_25_94 */
  "	anmw	AR,=31\n\
	ormh	AR,$+1w\n\
	OD	AR,0\n\
	stw	AR,A1\n\
	ld	AR,AL\n\
	exm	2b+A1\n\
	std	AR,AL\n",

ASG OPSHFT, INAREG|FORCC,	/* SPR02_25_94 */
    SAREG, TANY,
    SCCON, TINT|TUNSIGNED|TLONG,
    0, RLEFT|RESCC,	/* SPR02_25_94 */
	"	OI	AL,CR\n",

ASG OPSIMP, INAREG|FOREFF|FORCC,
    SAREG, TFP,
    SAREG, TFP,
    0, RLEFT|RESCC,
	"	OIrfZRP	AR,AL\n",

ASG OPSIMP, INAREG|FOREFF|FORCC,
    SAREG, TSCALAR,	/* was TWORD OCT04 */
    SAREG, TSCALAR,	/* was TWORD OCT04 */
    0, RLEFT|RESCC,
	"	OIr	AR,AL\n",

ASG OPSIMP, INAREG|FOREFF|FORCC,
    SAREG, TFP,
    AWD, TFP,
    0, RLEFT|RESCC,
	"	OIfZRP	AL,AR\n",

ASG OPSIMP, INAREG|FOREFF|FORCC,
    SAREG, TSCALAR,	/* was TWORD OCT04 */
    SSCON, TNATURAL|TWORD,
    0, RLEFT|RESCC,
	"	OIi	AL,CR\n",

ASG OPSIMP, INAREG|FOREFF|FORCC,
    SAREG, TSCALAR,	/* was TWORD OCT04 */
    AWD, TNATURAL|TWORD,
    0, RLEFT|RESCC,
	"	OImZRP	AL,AR\n",

ASG OPBIT, INAREG|FOREFF|FORCC,
    SAREG, TSCALAR,	/* was TWORD OCT04 */
    SAREG, TSCALAR,	/* was TWORD OCT04 */
    0, RLEFT|RESCC,
	"	OIr	AR,AL\n",

ASG AND, INAREG|FOREFF|FORCC,
    SAREG, TWORD,
    SACON, TANY,
    0, RLEFT|RESCC,
	"	anmw	AL,=CR\n",

ASG OR, INAREG|FOREFF|FORCC,
    SAREG, TWORD,
    SOCON, TANY,
    0, RLEFT|RESCC,
	"	ormw	AL,=CR\n",

ASG ER, INAREG|FOREFF|FORCC,
    SAREG, TWORD,
    SOCON, TANY,
    0, RLEFT|RESCC,
	"	eomw	AL,=CR\n",

ASG OPBIT, INAREG|FOREFF|FORCC,
    SAREG, TWORD,
    AWD, TWORD,
    0, RLEFT|RESCC,
	"	OImw	AL,AR\n",

AND, INTAREG|INAREG|FOREFF|FORCC,
    STAREG, TWORD,
    SCPOW2, TANY,
    0, RLEFT|RESCC,
	"	zbr	AL,Zn\n",

AND, INTAREG|INAREG|FOREFF|FORCC,
    STAREG, TWORD,
    SACON, TANY,
    0, RLEFT|RESCC,
	"	anmw	AL,=CR\n",

AND, FOREFF|FORCC,
    AWD, TWORD,
    SCPOW2, TANY,
    0, RNULL|RESCC,
	"	zbm	Zn,AL\n",

OR, INTAREG|INAREG|FOREFF|FORCC,
    STAREG, TWORD,
    SPOW2, TANY,
    0, RLEFT|RESCC,
	"	sbr	AL,Zn\n",

OR, INTAREG|INAREG|FOREFF|FORCC,
    STAREG, TWORD,
    SOCON, TANY,
    0, RLEFT|RESCC,
	"	ormw	AL,=CR\n",

OR, FOREFF|FORCC,
    AWD, TWORD,
    SPOW2, TANY,
    0, RLEFT|RESCC,
	"	sbm	Zn,AL\n",

ER, INTAREG|INAREG|FOREFF|FORCC,
    STAREG, TWORD,
    SOCON, TANY,
    0, RLEFT|RESCC,
	"	eomw	AL,=CR\n",

OPBIT, INTAREG|INAREG|FOREFF|FORCC,
    STAREG, TWORD,
    SCON, TANY,
    0, RLEFT|RESCC,
	"	OImw	AL,AR\n",

OPLTYPE, FOREFF|FORCC,	/* added FOREFF FEB15 */
    SANY, TANY,
    SAREG, TANY,
    0, RESCC,		/* deleted NAREG */
	"	trr	AR,AR\n",	/* was AR,A1 */

GOTO,	FOREFF,
	SCON,	TANY,
	SANY,	TANY,
	0,	RNOP,
	"	bu	CL\n",

GOTO,	FOREFF,
	SAREG,	TANY,
	SANY,	TANY,
	0,	RNOP,
	"	bu	AL\n",

/*Default actions for hard trees ... */

#define DF(x) FORREW, SANY, TANY, SANY, TANY, REWRITE, x, "mm"

UNARY MUL, DF(UNARY MUL),

INCR, DF(INCR),

DECR, DF(INCR),

ASSIGN, DF(ASSIGN),

/* new in MPX */
ASGP, DF(ASSIGN),

UMULP, DF(UMULP),

STASG, DF(STASG),

OPLEAF, DF(NAME),

OPLOG, FORCC,
    SANY, TANY,
    SANY, TANY,
    REWRITE, BITYPE,
	"	nop	2\n",

OPLOG, DF(NOT),

COMOP, DF(COMOP),

INIT, DF(INIT),

OPUNARY, DF(UNARY MINUS),

ASG OPANY, DF(ASG PLUS),

OPANY, DF(BITYPE),

FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, "help; I'm in trouble\n"
};
