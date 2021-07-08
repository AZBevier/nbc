/* manifest.h */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

/* $Id: manifest.h,v 1.14 2021/07/01 03:14:55 jbev Exp $ */

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

/*
 * $Log: manifest.h,v $
 * Revision 1.14  2021/07/01 03:14:55  jbev
 * Add more externals.
 *
 * Revision 1.13  2019/01/31 21:56:19  jbev
 * Update for Linux
 *
 * Revision 1.12  1996/10/26 22:18:07  jbev
 * Alpha port fixes
 *
 * Revision 1.11  1996/03/20 21:35:50  jbev
 * Mods for alpha port.
 *
 * Revision 1.10  1995/03/06 19:18:32  jbev
 * Malloc tree node table instead of hard coding size.
 * Allow XTTval  and X2TTval to set node tree table size.
 * Add new option XJ and X2J to inhibit _ being prepended to names.
 * Correct XT[DS]val options for setting table sizes.
 *
 */

#include <stdio.h>
#ifdef MYATOF
#include "float.h"
#endif /* MYATOF */

/* manifest constant file for the lex/yacc interface */
#define ERROR 1
#define NAME 2
#define STRING 3
#define ICON 4
#define FCON 5
#define PLUS 6
#define MINUS 8
#define MUL 11
#define AND 14
#define OR 17
#define ER 19
#define QUEST 21
#define COLON 22
#define ANDAND 23
#define OROR 24

/* the defines for ASOP, RELOP, EQUOP, DIVOP,
   SHIFTOP, ICOP, UNOP, and STROP have been
   moved to mfile1 */
/* reserved words, etc */
#define TYPE 33
#define CLASS 34
#define STRUCT 35
#define RETURN 36
#define GOTO 37
#define IF 38
#define ELSE 39
#define SWITCH 40
#define BREAK 41
#define CONTINUE 42
#define WHILE 43
#define DO 44
#define FOR 45
#define DEFAULT 46
#define CASE 47
#define SIZEOF 48
#define ENUM 49

/*	little symbols, etc. */
/*	namely,

	LP	(
	RP	)

	LC	{
	RC	}

	LB	[
	RB	]

	CM	,
	SM	;

	*/

/*  These defines are being moved to mfile1
    to alleviate preprocessor problems with
    second pass files.  
# define LP 50
# define RP 51
# define LC 52
# define RC 53
*/
#define LB 54
#define RB 55
#define CM 56
#define SM 57
#define ASSIGN 58
#define ASM 59
/*	END OF YACC */

/*	left over tree building operators */
#define COMOP 59
#define DIV 60
#define MOD 62
#define LS 64
#define RS 66
#define DOT 68
#define STREF 69
#define CALL 70
#define FORTCALL 73
#define NOT 76
#define COMPL 77
#define INCR 78
#define DECR 79
#define EQ 80
#define NE 81
#define LE 82
#define LT 83
#define GE 84
#define GT 85
#define ULE 86
#define ULT 87
#define UGE 88
#define UGT 89
#define SRA 90
#define SLA 92

#define REG 94
#define OREG 95
#define CCODES 96
#define FREE 97
#define STASG 98
#define STARG 99
#define STCALL 100

/*	some conversion operators */
#define FLD 103
#define SCONV 104
#define PCONV 105
#define PMCONV 106
#define PVCONV 107

/*	special node operators, used for special contexts */
#define FORCE 108
#define CBRANCH 109
#define INIT 110
#define CAST 111

# define LNAME 112	/* atomic local automatic */
# define PNAME 113	/* atomic local parm */
# define TNAME 114	/* optimizer stack temporary */
# define TREG 115	/* optimizer register temporary */

# define OCONVLEAF 116	/* optimizer conversion node - leaf */
# define OCONVTREE 117	/* optimizer conversion node - tree */
# define LADDR 118	/* addr of a local */
# define PADDR 119	/* addr of a param */
# define ADDR 120	/* addr of anything else */

# define LEAFNOP 121	/* leaf no-op - used by optimizer */
# define UNARYNOP 122	/* unary no-op - ditto */

# define LTEMP 123	/* Loop invariant temporary */
# define STATNAME 124	/* Atomic local static - used mostly bo Fortran */
# define STADDR 125	/* Address of a STATNAME */

# define INCALL 126	/* inline call */

			/* 127 and 128 for UNARY INCALL, etc. */

# define STLABEL 129	/* statement label */

#define UMULP	130		/* load, given physical address */
#define ASGP	131		/* store given physical address */
#define UANDP	132		/* get phys address given logical addr */
#define MCON    133             /* ICON >=0 && <= ffffff */

	/* THIS MUST BE THE LAST DEFINITION */

#define LABCON	137		/* for f77 PCO only - here for completeness */
#define B3MASK	0x1000

 /* DSIZE is the size of the dope array */
#define DSIZE LABCON+1

/*	node types */
#define LTYPE 02
#define UTYPE 04
#define BITYPE 010

/*	type names, used in symbol table building */
#define TNULL PTR	/* pointer to UNDEF */
#define TVOID FTN	/* function returning UNDEF (for void) */
#define UNDEF 0
#define FARG 1
#define CHAR 2
#define SHORT 3
#define INT 4
#define LONG 5
#define FLOAT 6
#define DOUBLE 7
#define STRTY 8
#define UNIONTY 9
#define ENUMTY 10
#define MOETY 11
#define UCHAR 12
#define USHORT 13
#define UNSIGNED 14
#define ULONG 15

#define ASG 1+
#define UNARY 2+
#define NOASG (-1)+
#define NOUNARY (-2)+

/*	various flags */
#define NOLAB (-1)

/* type modifiers */

#define PTR  020
#define FTN  040
#define ARY  060

/* type packing constants */

#define TMASK 060
#define TMASK1 0300
#define TMASK2  0360
#define BTMASK 017
#define BTSHIFT 4
#define TSHIFT 2

/*	macros	*/

#define MODTYPE(x,y) x = ( (x)&(~BTMASK))|(y)	/* set basic type of x to y */
#define BTYPE(x)  ( (x)&BTMASK)			/* basic type of x */
#define ISUNSIGNED(x) ((x)<=ULONG&&(x)>=UCHAR)
#define UNSIGNABLE(x) ((x)<=LONG&&(x)>=CHAR)
#define ENUNSIGN(x) ((x)+(UNSIGNED-INT))
#define DEUNSIGN(x) ((x)+(INT-UNSIGNED))
#define ISPTR(x) (( (x)&TMASK)==PTR)
#define ISFTN(x)  (( (x)&TMASK)==FTN)		/* is x a function type */
#define ISARY(x)   (( (x)&TMASK)==ARY)		/* is x an array type */
#define INCREF(x) ((( (x)&~BTMASK)<<TSHIFT)|PTR|( (x)&BTMASK))
#define DECREF(x) ((( (x)>>TSHIFT)&~BTMASK)|( (x)&BTMASK))
#define SETOFF(x,y)   if( (x)%(y) != 0 ) (x) = ( ((x)/(y) + 1) * (y))
 /* advance x to a multiple of y */
#define NOFIT(x,y,z)   ( ( (x)%(z) + (y) ) > (z) )
 /* can y bits be added to x without overflowing z */
 /* pack and unpack field descriptors (size and offset) */
#define PKFIELD(s,o) (( (unsigned)(o)<<6)| (unsigned)(s) )
#define UPKFSZ(v)  ( (v) &077)
#define UPKFOFF(v) ( (v) >>6)

/* Default definitions in the absence of emulation. */

extern int errno;

#ifdef MYATOF
#define	FP_FLOAT	FPN	/* prevent unfortunate conversions */
#define	FP_DOUBLE	FPN	/* type containing doubles */
#define	FP_DTOF(d)	(d)	/* no conversion */
#define	FP_DTOFP(d)	(d)	/* no conversion */
extern long itod();
#define FP_LTOD(d,e)	itod(d,e)
extern long uitod();
#define FP_ULTOD(d,e)	uitod(d,e)
extern long ftoi();
#define FP_DTOL(d)	(ftoi(d,0))
#define	FP_NEG(d)	(negf(d))
extern void addff();
#define FP_PLUS(d1,d2)	(addff(d1,d2))
extern void subff();
#define FP_MINUS(d1,d2) (subff(d1,d2))
extern void mulff();
#define FP_TIMES(d1,d2) (mulff(d1,d2))
extern void divff();
#define FP_DIVIDE(d1,d2) (divff(d1,d2))
extern int isnzf();
#define	FP_ISZERO(d)	(!isnzf(d))
extern FPN ifpn;	/* last floating point number */
#endif /* MYATOF */

#ifdef MYATOF
#define	FP_ATOF(s) myatof(s)	/* use my atof() */
extern FPN *myatof();
#else
#ifdef NEWATOF
#define	FP_ATOF(s) atofn(s)	/* use UNIX atof() */
extern double atofn();
#else /* NEWATOF */
#define	FP_ATOF(s) atof(s)	/* use UNIX atof() */
extern double atof();
#endif /* NEWATOF */
#endif /* MYATOF */

#ifndef	FP_DOUBLE
#define	FP_DOUBLE	double	/* type containing doubles */
#endif
#ifndef	FP_FLOAT
#define	FP_FLOAT	float	/* type containing floats */
#endif
#ifndef	FP_DTOF
#define	FP_DTOF(d) ((float) d)	/* convert double to float */
#endif
#ifndef	FP_DTOFP		/* truncate double to float precision */
#define	FP_DTOFP(d) ((double) FP_DTOF(d))
#endif
#ifndef	FP_DTOL			/* convert double to long */
#define	FP_DTOL(d) ((long) (d))
#endif
#ifndef FP_DTOUL		/* convert double to unsigned long */
#define FP_DTOUL(d) ((unsigned long) (d))
#endif
#ifndef	FP_LTOD			/* convert long to double */
#define	FP_LTOD(l) ((double) (l))
#endif
#ifndef	FP_ULTOD		/* convert unsigned long to double */
#define	FP_ULTOD(ul) ((double) (ul))
#endif
#ifndef	FP_NEG			/* negate double */
#define	FP_NEG(d) (-(d))
#endif
#ifndef	FP_PLUS			/* add double */
#define	FP_PLUS(d1,d2) ((d1)+(d2))
#endif
#ifndef	FP_MINUS		/* subtract double */
#define	FP_MINUS(d1,d2) ((d1)-(d2))
#endif
#ifndef	FP_TIMES		/* multiply double */
#define	FP_TIMES(d1,d2) ((d1)*(d2))
#endif
#ifndef	FP_DIVIDE		/* divide double */
#define	FP_DIVIDE(d1,d2) ((d1)/(d2))
#endif
#ifndef	FP_ISZERO		/* is double value zero? */
#define	FP_ISZERO(d) (!(d))
#endif
#ifndef	FP_CMPD			/* compare two doubles */
#define	FP_CMPD(x,y) ((x)==(y)?0:((x)>(y)?1:-1))
#endif

/*	operator information */

#define TYFLG 016
#define ASGFLG 01
#define LOGFLG 020

#define SIMPFLG 040
#define COMMFLG 0100
#define DIVFLG 0200
#define FLOFLG 0400
#define LTYFLG 01000
#define CALLFLG 02000
#define MULFLG 04000
#define SHFFLG 010000
#define ASGOPFLG 020000

#define SPFLG 040000
#define BITFLG 0100000		/* bit operators */

#define COMMUTEFLG 0200000	/* commutative operators */

#define optype(o) (dope[o]&TYFLG)
#define asgop(o) (dope[o]&ASGFLG)
#define logop(o) (dope[o]&LOGFLG)
#define callop(o) (dope[o]&CALLFLG)

#define commuteop(o) (dope[o]&COMMUTEFLG)

/*	table sizes	*/

/* mode table now malloced in scan.c/reader.c */
#define TREESZ 1000		/* space for building parse tree */
extern int TREESIZE;		/* trees */

char       *tstr();
extern int  tstrused;
extern char    *tstrbuf[], **curtstr;
#define	freetstr()	curtstr = tstrbuf, tstrused = 0

/*	common defined variables */

extern int  nerrors;		/* number of errors seen so far */

typedef union ndu   NODE;
typedef int     TWORD;
#define NIL (NODE *)0
extern int  dope[];		/* a vector containing operator information */
extern char    *opst[];		/* a vector containing names for ops */

extern unsigned offsz, caloff();

#ifdef ONEPASS
 /* in one-pass operation, define the tree nodes */

union       ndu
{

    struct {
	int         op;
	int         rall;
	TWORD       type;
	int         su;
	char       *name;
	long        stalign;
	NODE       *left;
	NODE       *right;
    }           in;			/* interior node */

    struct {
	int         op;
	int         rall;
	TWORD       type;
	int         su;
	char       *name;
	long        stalign;
	long        lval;
	long        rval;
    } tn;				/* terminal node */

    struct {
	int         op;
    	int	    rall;
	TWORD       type;
	int         su;
	long        label;		/* for use with branching */
	long        stalign;
    } bn;				/* branch node */

    struct {
	int         op;
	int	    rall;
	TWORD       type;
	int         su;
	long        stsize;		/* sizes of structure objects */
	long        stalign;		/* alignment of structure objects */
    } stn;				/* structure node */

    struct {
	int         op;
	int         cdim;
	TWORD       type;
	int         csiz;
    } fn;				/* front node */

    struct {
 /* this structure is used when a floating point constant is being computed */
	int         op;
	int         cdim;
	TWORD       type;
	int         csiz;
#ifdef MYATOF
	char       *name;
/*	int         stalign; */		/* alignment of structure objects */
	FPN         fpnum;
#else
	char       *name;
	int         stalign;		/* alignment of structure objects */
	FP_DOUBLE   dval;
#endif /* MYATOF */
    } fpn;				/* floating point node */

};
#endif

/* define NOBUG to eliminate debug code */
#define NOBUG
#ifdef NOBUG
#define BUG4
#endif

#ifdef BUG2
#define BUG1
#endif

#ifdef BUG3
#define BUG2
#define BUG1
#endif

#ifdef BUG4
#define BUG1
#define BUG2
#define BUG3
#endif

#ifndef ONEPASS

#ifndef EXPR
#ifdef MPX
#define EXPR '='
#else
#define EXPR '*'
#endif
#endif

#ifndef BBEG
#define BBEG '['
#endif
#ifndef BEND
#define BEND ']'
#endif

# ifndef IBRANCH
# define IBRANCH '>'
# endif
# ifndef ILABEL
# define ILABEL '<'
# endif
# ifndef FBEGIN
# define FBEGIN '{'
# endif
# ifndef FEND
# define FEND '}'
# endif
# ifndef EOJFLG
# define EOJFLG 'E'
# endif
# ifndef IRETURN
# define IRETURN 'R'
# endif
# ifndef ESWITCH
# define ESWITCH 'S'
# endif
# ifndef STABINFO
# define STABINFO '@'
# endif
# ifndef PFHERE
# define PFHERE 'H'
# endif
# ifndef PFETCH
# define PFETCH 'P'
# endif
# ifndef PSAVE
# define PSAVE 'V'
# endif
# ifndef IDATA
# define IDATA 'D'
# endif
# ifndef ITEXT
# define ITEXT 'T'
# endif
# ifndef IASM
# define IASM 'A'
# endif

# else /* ONEPASS */

/* make IDATA and ITEXT tabs for ONEPASS version */
# ifndef IDATA
# define IDATA '\t'
# endif
# ifndef ITEXT
# define ITEXT '\t'
# endif

# endif /* ONEPASS */

/* stack offsets, also see mfile1.h, mfile2.h */

#define MAXARGSIZE 3200		/* 3200 bits == 100 words */

/* switch definitions */

#ifdef TWOPASS
#define SWITSZ 500	/*500*/		/* size of switch table */
#else
#define SWITSZ 250	/*500*/		/* size of switch table */
#endif

struct      sw
{
    CONSZ       sval;
    int         slab;
};

extern struct sw    swtab[];

extern int         extflg;
#define C_LD	0x1
#define C_DL	0x2
#define C_ULD	0x4
#define C_DUL	0x8
#define C_IF	0x10
#define C_FI	0x20
#define C_UIF	0x40
#define C_FUI	0x80
#define C_FC	0x100
#define C_FCD	0x200
#define EXTFUNS 10

#ifdef TWOPASS
extern void tinit();
extern void tcheck();
extern int locctr2();
extern void LookForEOL();
extern void LclReturn();
extern void ParamFetch();
extern void dumpstr();
extern void p2bend();
extern void fltread();
extern int tdebug;
#ifdef MYATOF
extern long itod();
extern long uitod();
extern long ftoi();
extern void addff();
extern void subff();
extern void mulff();
extern void divff();
extern void negf();
extern void zerof();
extern int isnzf();
extern FPN ifpn;	/* last floating point number */
#endif
#endif
