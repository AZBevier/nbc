/* xdefs.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid = "$Id: xdefs.c,v 1.6 2019/01/31 22:03:56 jbev Exp $";
#endif

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

/*
 * $Log: xdefs.c,v $
 * Revision 1.6  2019/01/31 22:03:56  jbev
 * Update for Linux
 *
 * Revision 1.5  1996/03/20 21:36:39  jbev
 * Mods for alpha port.
 *
 * Revision 1.4  1995/03/06 19:18:32  jbev
 * Malloc tree node table instead of hard coding size.
 * Allow XTTval  and X2TTval to set node tree table size.
 * Add new option XJ and X2J to inhibit _ being prepended to names.
 * Correct XT[DS]val options for setting table sizes.
 *
 */

#include "mfile1.h"

/*	communication between lexical routines	*/

char        ftitle[100] = "";	/* title of the file */
char        ititle[100] = "";	/* title of initial file */
int         lineno;		/* line number of the input file */

CONSZ       lastcon;	/* the last constant read by the lexical analyzer */
#ifndef MYATOF
FP_DOUBLE   dcon;	/* the last double read by the lexical analyzer */
#endif /* MYATOF */

/*	symbol table maintainence */

struct symtab   *stab;		/* one extra slot for scratch */

int         curftn;		/* "current" function */
int         ftnno;		/* "current" function number */

#ifdef MPX
int DIMTABSZ;
int SYMTSZ;
int sizeofflag;
#endif

int         curclass,		/* current storage class */
            instruct,		/* "in structure" flag */
            stwart,		/* for accessing names which
				   are structure members or names */
            blevel,		/* block level: 0 for extern,
				   1 for ftn args, >=2 inside function */
            curdim;		/* current offset into the dimension table */
int	    forcealign = 0;	/* forced minimum alignment */
				/* set by ALIGN-n special comment */
int         ininit=0;		/* "in initializer" flag */

int         *dimtab;

int         paramstk[PARAMSZ];	/* used in the definition of function parameters */
int         paramno;		/* the number of parameters */
int         autooff;		/* the next unused automatic offset */
int         argoff;		/* the next unused argument offset */

int         strucoff;		/*  the next structure offset position */

int         regvar;	/* the next free register for register variables */
int         minrvar;	/* the smallest that regvar gets witing a function */
OFFSZ       inoff;	/* offset of external element being initialized */

int         brkflag = 0;  /* complain about break statements not reached */

struct sw   swtab[SWITSZ];	/* table for cases within a switch */
struct sw  *swp;	/* pointer to next free entry in swtab */
int         swx;	/* index of beginning of cases for current switch */

#ifndef BUG1
/* debugging flag */
int	xdebug = 0;
#endif

int         strflg;	/* if on, strings are to be treated as lists */

int         reached;	/* true if statement can be reached... */

int         idname;	/* tunnel to buildtree for name id's */

#ifdef NOW_MALLOCED
NODE        node[TREESZ];
#else
NODE        *nodep;
int	    TREESIZE;
#endif

#ifdef FIX_27OCT92
int         cflag = 0;	/* do we check for funny casts */
int         hflag = 0;	/* do we check for various heuristics 
				which may indicate errors */
int         pflag = 0;	/* do we check for portable constructions */
#else
int         cflag = 0;	/* do we check for funny casts */
int         hflag = 1;	/* do we check for various heuristics 
				which may indicate errors */
int         pflag = 1;	/* do we check for portable constructions */
#endif

int         brklab;
int         contlab;
int         flostat;
int         retlab = NOLAB;
int         retstat;

/* save array for break, continue labels, and flostat */

int         asavbc[BCSZ];
int        *psavbc = asavbc;

#ifndef BUG1
static char    *ccnames[] =
{			/* names of storage classes */
    "SNULL",
    "AUTO",
    "EXTERN",
    "STATIC",
    "REGISTER",
    "EXTDEF",
    "LABEL",
    "ULABEL",
    "MOS",
    "PARAM",
    "STNAME",
    "MOU",
    "UNAME",
    "TYPEDEF",
    "FORTRAN",
    "ENAME",
    "MOE",
    "UFORTRAN",
    "USTATIC",
    "ABSLABEL",
};

char       *scnames(c) register     int c;
{
 /* return the name for storage class c */
    static char     buf[12];
    if (c & FIELD) {
	sprintf(buf, "FIELD[%d]", c & FLDSIZ);
	return(buf);
    }
    return(ccnames[c]);
}
#endif
