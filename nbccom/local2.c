/* local2.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid = "$Id: local2.c,v 1.28 2019/03/02 23:31:40 jbev Exp jbev $";
#endif

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

/*
 * $Log: local2.c,v $
 * Revision 1.28  2019/03/02 23:31:40  jbev
 * Call do free in common.h as standard free call.
 *
 * Revision 1.27  2019/01/31 21:50:20  jbev
 * Update for Linux
 *
 * Revision 1.26  1997/01/22 18:28:07  jbev
 * Correct pointer/integer problem with error messages.
 * Only on Alpha because of 64 bit pointers and 32 bit ints.
 *
 * Revision 1.25  1996/03/20 23:43:30  jbev
 * Use O/S malloc function for alpha, not internal function.
 * More mods for alpha port.
 *
 * Revision 1.24  1996/03/20 21:42:39  jbev
 * Mods for alpha port.
 *
 * Revision 1.23  1996/03/18 23:55:06  jbev
 * Mods for Alpha port.
 *
 * Revision 1.22  1996/01/15 18:05:10  jbev
 * Correct structure assignment when we have a pointer in the stack.
 *
 * Revision 1.21  1995/09/20  02:39:50  jbev
 * Just a format fix.
 *
 * Revision 1.20  1995/04/28  20:48:15  jbev
 * Modifications for sectioned code.
 *
 * Revision 1.19  1995/04/13  00:01:13  jbev
 * Fix structure moves, again.
 *
 * Revision 1.18  1995/04/05  22:30:38  jbev
 * Correct structure assignments.
 *
 * Revision 1.17  1995/03/13  18:53:38  jbev
 * Fix spelling error.
 *
 * Revision 1.16  1995/03/06  19:18:32  jbev
 * Malloc tree node table instead of hard coding size.
 * Allow XTTval  and X2TTval to set node tree table size.
 * Add new option XJ and X2J to inhibit _ being prepended to names.
 * Correct XT[DS]val options for setting table sizes.
 *
 */

#include "mfile2.h"
#include "ctype.h"
#include <a.out.h>
#include <string.h>

#ifdef FORT
int         ftlab1, ftlab2;
#endif /* FORT */

extern int fdefflag;	/* set if in a function */
extern void dofree();

/* a lot of the machine dependent parts of the second pass */

#define BITMASK (n) ((unsigned)((unsigned)1L << n) - 1)

NODE	*fortaddr();
int 	argcnt;		/* needed for fortran calls */
int     argwordcount;
int     bittestused;

void where(c) int c;
{
    fprintf(stderr, "%s, line %d: ", filename, lineno);
}

void lineid(l, fn) int l; char *fn;
{
 /* identify line l and file fn */
    static char     lastfn[40];
    static int labno;
#ifndef NOCAID
    if (lflag) {
    	/* only output E. if in a function */
    	if (fdefflag)
/*    	    printf("*E.%d%s line %d\n", l, fn, l) */ ;
#else
    if (lflag >= 2) {
#endif
	if (strncmp(lastfn, fn, sizeof lastfn)) {
	    strncpy(lastfn, fn, sizeof lastfn);
#ifdef NOT_NOW_FOR_CAID
#ifndef NOCAID
    	    printf("*X.%d%s line %d\n", labno, fn, l);
#else
	    printf("*	.stabs %s,0x%x,0,LLL%d\nLLL%d:\n",
	 	fn, N_SO, labno, labno);
#endif
#endif
	    labno++;
	}
#ifdef NOT_NOW_FOR_CAID
#ifndef NOCAID
	printf("*.stabd 0x%x,0,0x%x\n", N_SLINE, l);
#else
	printf("*	.stabd 0x%x,0,0x%x\n", N_SLINE, l);
#endif
#endif
    } else {
	printf("*	line %d, file %s\n", l, fn);
    }
}

int         maxargs;
void eobl2(nregs) int nregs;
{
    OFFSZ       spoff;		/* offset from stack pointer */
    OFFSZ	ntmp;
    maxargs *= SZCHAR;
    SETOFF(maxargs, ALLONG);
    SETOFF(maxoff, ALLONG);
    {
	OFFSZ   regsave;
	ntmp = maxargs + maxoff;		/* base of near temp, for c2 */
	regsave = maxargs + maxoff + FRAMESZ;	/* base of far locals (FLOC) */
	SETOFF(regsave, ALFRAME);
/*	printf("CALL%d	equ	0w\n", ftnno); */
	printf("CALL%d	cequ	0w\n", ftnno);
/*	printf("LOC%d	equ	%dw\n", ftnno, maxargs / SZINT); */
	printf("LOC%d	cequ	%dw\n", ftnno, maxargs / SZINT);
/*	printf("L_TMP%d	equ	%dw\n", ftnno, ntmp / SZINT); */
	printf("L_TMP%d	cequ	%dw\n", ftnno, ntmp / SZINT);
#ifdef FORT
	printf("FRM%d	equ	%dw\n", ftnno, regsave / SZINT);
#else /* NOT FORT */
/*	printf("LA%d	equ	%dw\n", ftnno, regsave / SZINT); */
	printf("LA%d	cequ	%dw\n", ftnno, regsave / SZINT);
#ifndef SECTION_FIX
	printf("SLA%d\tdataw\tLA%d\n", ftnno, ftnno);
#endif /* SECTION_FIX */
#endif /* FORT */

    }
    maxargs = 0;
}

struct      hoptab
{
    int         opmask;
    char       *opstring;
}           ioptab[] =
{
		ASG PLUS, "ad",
                ASG MINUS, "su",
                ASG MUL, "mp",
                ASG DIV, "dv",
                ASG OR, "or",
                ASG ER, "eo",
                ASG AND, "an",
                ASG LS, "sll",
                ASG RS, "srl",
                PLUS, "ad",
                MINUS, "su",
                MUL, "mp",
                DIV, "dv",
                OR, "or",
                ER, "eo",
                AND, "an",
		LS, "sll",
                RS, "srl",
               -1, ""
};

void hopcode(f, o) int f, o;
{
 /* output the appropriate string from the above table */

    register struct hoptab *q;

    for (q = ioptab; q->opmask >= 0; ++q) {
	if (q->opmask == o) {
	    printf("%s", q->opstring);
	    switch (f) {

		case 'L': 
		case 'W': 
		case 'H': 
		case 'B': 
		case 'D': 
		case 'F': 
		    printf("%c", tolower(f));
		    break;

	    }
	    return;
	}
    }
    cerror("no hoptab for %s", opst[o]);
}

int	    szrnames = 12;	/* Nbr entries in rnames[] */
char       *rnames[] =
{				/* keyed to register number tokens */
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
    "FP","AP","TP","CP",
};

/*
 * fix register classes
 */
int         rstatus[] =
{
    SAREG | STAREG,
    SAREG | STAREG,
    SAREG | STAREG,
    SAREG,
    SAREG ,
    SAREG ,
    SAREG ,
    SAREG ,

    SBREG,
    SBREG,
    SBREG,
    SBREG,

};

int tlen(p) NODE   *p;
{
    switch (p->in.type) {

	case CHAR: 
	case UCHAR: 
	    return(1);

	case SHORT: 
	case USHORT: 
	    return(2);

	case LONG: 
	case DOUBLE: 
	    return(8);

	default: 
	    return(4);
    }
}

int mixtypes(p, q) NODE    *p, *q;
{
    register    int tp, tq;

    tp = p->in.type;
    tq = q->in.type;

    return((tp == FLOAT || tp == DOUBLE) !=
	    (tq == FLOAT || tq == DOUBLE));
}

void prtype(n) NODE *n;
{
    switch (n->in.type) {

	case LONG: 
	case ULONG: 
	case DOUBLE:
	    printf("d");
	    return;

	case FLOAT:
	case INT: 
	case UNSIGNED: 
#ifdef FORT
reg_is_int:
#endif /* FORT */
	    printf("w");
	    return;

	case SHORT: 
	case USHORT: 
#ifdef FORT
	    if (n->in.op == REG)
		goto reg_is_int;
#endif /* FORT */
	    printf("h");
	    return;

	case CHAR: 
	case UCHAR: 
#ifdef FORT
	    if (n->in.op == REG)
		goto reg_is_int;
#endif /* FORT */
	    printf("b");
	    return;

	default: 
#ifdef FORT
	    if (n->in.op == ICON) {
		printf("w");
		return;
	    }
	    if (!ISPTR(n->in.type) && !ISARY(n->in.type))
#else /* NOT FORT */
	    if (!ISPTR(n->in.type) && !ISARY(n->in.type))
#endif /* FORT */
{
#ifndef BUG1
		    fwalk(n, eprint, 0);
#endif
		cerror("Xzzzcode- bad type");
}
	    else {
		printf("w");
		return;
	    }
    }
}

int plusused = 0;
struct optab psuedocook[] = {
	STASG, FOREFF|INAREG,
	SANY, TANY,
	SANY, TANY,
	2*NAREG, RNULL,
	    "-- psuedo cookie"
};

void zzzcode(p, c) register NODE    *p; int c;
{
    register    int m;
    CONSZ       val;

    switch (c) {

	case '-':
	    plusused--;
	    break;

	case '+':	/* Generate + if lval >0, else nothing, */
			/* to pacify assembler.  I.E. - use     */
			/* 1ZL+AL in place of 1+AL, etc.	*/
			/* Also, generate + for OREG when that  */
			/* OREG does not represent an actual    */
			/* register. Fix for fang_406		*/
			/* Also, generate + for NAME because    */
			/* [13]_symbol will not be a valid      */
			/* operand. Fix for SPR 88000127	*/
	    if((p->in.op == OREG && isfakereg(p->tn.rval))
		|| p->in.op == NAME || p->tn.lval != 0) {
		plusused++;
		printf("+");
	    }

	    break;


	case 'r':	/* register moves, mainly for getting "fake" */
			/* register values into temp reg for STASG   */
	  {
	    NODE *p2 = getlr(p, 'R');

#ifndef BUG3
	    if(rdebug) {
		printf("zzzcode():   Zr\n");
	    }
#endif
	    if(isfakereg(p2->tn.rval)) {
		p2->in.op = OREG;	/* for adrput() */
		expand(p2, FOREFF, "\tla	A1,AR");
		p2->in.op = REG;		/* restore original value */
	    } else {
		expand(p2, FOREFF, "\ttrr	AR,A1");
	    }
	    break;
	  }

	case 'C': 
	    adrcon(argwordcount);
	    return;

	case 'D': 		/* generate double precision 0 */
	    {
	    NODE	tempnode;

	    tempnode.in.op = INT;
	    tempnode.in.type = LONG;
	    tempnode.in.name = "";
	    tempnode.tn.rval = 0;
	    tempnode.tn.lval = 0;	/* value of zero */
#ifdef MYATOF
	    zerof(&tempnode.fpn.fpnum);
#endif
	    adrput(&tempnode);
	    return;
	    }

    	case 'd':
    	    if (p->in.type == LONG || p->in.type == DOUBLE) {
    		printf("d");
    		extflg |= C_FCD;	/* emit extern */
    	    } else {
    		extflg |= C_FC;		/* emit exterm */
    	    }
	    return;

    	case 'Q':	/* put arg cnt into reg */
    	    printf("	li	r2,%dw\n", argcnt >> 2);
	    return;

	case 'm':
	    return;

	case 'M': 
	    adrcon(-p->tn.lval);
	    return;

	case '~': 
	    adrcon(~p->tn.lval);
	    return;

	case 'G': 
	    bittestused = 2;		/* when used to see sign bit */
	    cbgen(p->in.op, p->bn.label, c);
	    return;

	case 'B': 
	    bittestused = 1;		/* when used to see one bit */
	    break;

	case 'N': 			/* logical ops, turned into 0-1 */
    /* use register given by register 1 */
	    bittestused = 0;		/* when used to see sign bit */
	    cbgen(0, m = get2lab(), 'I');
	    deflab(p->bn.label);
	    printf("	zr	%s\n", rnames[resc[0].tn.rval]);
	    deflab(m);
	    return;

	case 'J': 
	    bittestused = 0;		/* when used to see sign bit */
	    cbgen(p->in.op, p->bn.label, c);
	    return;


    /* 
     * emit code to do a field assignment of
     *  f = constant;
     */
	case 'F': {
		val = p->in.right->tn.lval;
		if (fldsz == 2) {
		    expand(p, FOREFF, val & 2 ? "	sbm" : "	zbm");
		    switch (p->in.type) {
			case SHORT: 
			case USHORT: 
			    if (p->in.left->in.op == REG)
				break;
			    fldshf += 16;
			    break;
			case CHAR: 
			case UCHAR: 
			    if (p->in.left->in.op == REG)
				break;
			    fldshf += 24;
			    break;
			default: 
			    break;
		    }
		    printf ("	%d,", 30-fldshf);
		    adrput(p->in.left);
		    PUTCHAR('\n');
		    fldsz = 1;
		}
		if (fldsz == 1) {
		    expand(p, FOREFF, val & 1 ? "	sbm" : "	zbm");
		    switch (p->in.type) {
			case SHORT: 
			case USHORT: 
			    if (p->in.left->in.op == REG)
				break;
			    fldshf += 16;
			    break;
			case CHAR: 
			case UCHAR: 
			    if (p->in.left->in.op == REG)
				break;
			    fldshf += 24;
			    break;
			default: 
			    break;
		    }
		    printf ("	%d,", 31-fldshf);
		    adrput(p->in.left);
		    PUTCHAR('\n');
		    return;
		}
		if (fldsz == 32) {
		    expand(p, FOREFF, "\tlw\tA1,AR\n\tstw\tA1,AL\n");
		    return;
		}
		val &= ((unsigned)1 << (unsigned)fldsz) - 1;
		m = val != (((unsigned)1 << (unsigned)fldsz) - 1);
		val = (unsigned)val << (unsigned)fldshf;
		p->in.right->tn.lval = val;
		expand(p, FOREFF, "	lZP	A1,AL\n");
		if (m) {
		    expand(p, FOREFF, "	anmw	A1,N\n");
		}
		if (val) {
		    expand(p, FOREFF, "	ormw	A1,AR\n");
		}
		expand(p, FOREFF, "	stZP	A1,AL\n");
		val = (unsigned)val >> (unsigned)fldshf;
		p->in.right->tn.lval = val;

	    }
	    return;

	case 'P': 
	    prtype(p);
	    return;

	case 'S': 		/* structure assignment */
	    {
		register NODE  *l, *r;
		register    int size;
		int	    i;
		int         inc = p->in.stalign;
		int         oldtype = p->in.type;
		char	    movedreg = 0;
		int	    sr=0;
		int	    dr=0;
		int	    xr=0;
		int	    rr=0;
		int	    sxr=0;
		int	    looplab;
		char	    ilchar;
		NODE	    tempnode;

#ifndef BUG3
		if(rdebug) {
			printf("zzzcode():  NODE dump:\n");
			    	fwalk(p, eprint, 0);
			printf("zzzcode():  ZS, resources:\n");
			for(i=0; i<4; ++i) {
			    if(resc[i].in.op == REG
			      || resc[i].in.op == NAME
			      || resc[i].in.op == OREG) {
				printf("resc[%d]:  ", i);
			    	fwalk(&resc[i], eprint, 0);
			    }
			}
		}
#endif

		if (p->in.op == STASG) {
		    l = p->in.left;
		    r = p->in.right;
#ifndef BUG3
		    if (rdebug) {
			printf("zzzcode():  ZS, leftreg = %x, rightreg = %x\n",
				l->tn.rval, r->tn.rval);
		    	printf ("left op is %s\n", opst[l->in.op]);
		    	printf ("right op is %s\n", opst[r->in.op]);
		    }
#endif
		}
		else {
		    if (p->in.op != STARG) {
			cerror("STASG bad");
		    }
		    r = p->in.left;
		    l = &resc[1];
		}

		switch (inc) {

		    case 1: 
			p->in.type = CHAR;
			ilchar = 'b';
			break;

		    case 2: 
			p->in.type = SHORT;
			ilchar = 'h';
			break;

		    case 8: 
			inc = 4;
			/* fall thru to case 4 */

		    case 4: 
			p->in.type = INT;
			ilchar = 'w';
			break;
		}
#ifndef FIX_ASG
		/* We have an address of a structure */
		if (r->in.op == ICON) {
		    order(r, INAREG);
#ifndef BUG3
	if(rdebug) {
		printf("zzzcode():  NODE dump:\n");
		    	fwalk(p, eprint, 0);
	}
#endif
		}
#endif
#ifndef FIX_ASG_01_15_96
		/* See if we have an address of a structure */
		if (r->in.op == OREG && ISPTR(r->in.type)) {
		    order(r, INAREG);
#ifndef BUG3
	if(rdebug) {
		printf("zzzcode():  NODE dump:\n");
		    	fwalk(p, eprint, 0);
	}
#endif
		}
#endif
		if (r->in.op == ICON)
		    r->in.op = NAME;
		else
		    if (r->in.op == REG) {
			r->in.op = OREG;

			if (r->tn.rval == 0) {

			/*  should be able to use R0 as pointer */
			    int	newreg;
#ifndef BUG3
		if (rdebug) {
		    printf ("lf found op %s\n", opst[l->in.op]);
		    printf ("rt found op %s\n", opst[r->in.op]);
		}
#endif
			/* need to transfer structure address that is in
		 	 * register 0 into an OREG to x1 or x2 so
		 	 * we can move the structure.
		 	 */
		    	    if (!busy[R1]) newreg = R1;
		    	    else if (!busy[R2]) newreg = R2;
		    	    else cerror ("Index reg not available for struct move"); 
			    r->tn.rval = newreg;
			    printf("	trr	r0,r%d\n", newreg);
			    ++busy[newreg];
			    --busy[R0];
			    movedreg = 1;
			}
		    }
		    else
			if (r->in.op != OREG)
			    cerror("STASG-r");

		size = p->stn.stsize;

#ifndef BUG3
    if (rdebug) {
	printf("lf2 found op %s\n", opst[l->in.op]);
	printf("rt2 found op %s\n", opst[r->in.op]);
	printf("leftreg = %x, rightreg = %x\n", l->tn.rval, r->tn.rval);
	printf("dr = %x size/inc = %d\n", dr, size/inc);
	if (busy[R0]) printf("R0 busy\n");
	if (busy[R1]) printf("R1 busy\n");
	if (busy[R2]) printf("R2 busy\n");
	if (busy[R3]) printf("R3 busy\n");
    }
#endif
		if ((size/inc) > 2) {

		/* need to transfer structure address that is in
		 * a reg variable made into an OREG to x1 or x2 so
		 * we can move the structure.  I can't seem to make
		 * local or trees not optimize away the UNARY MUL
	         * required to transfer the reg variable to an SAREG. 
		 */

		if (r->in.op==OREG && (r->tn.rval >= R4 && r->tn.rval <= R7)) {
		    sr = r->tn.rval;
		    if (!busy[R1]) dr = R1;
		    else if (!busy[R2]) dr = R2;
		    else cerror ("Index reg not available for struct move"); 
		    expand(r, FOREFF|INAREG, "\ttrr\t");
		    printf("r%d,r%d\n", sr, dr); 
		    r->tn.rval = dr;
#ifdef FIX_040795
		} else if ((l->in.op == NAME) || (isfakereg (l->tn.rval) &&
    		    (l->in.op == OREG))) {
		    if (!busy[R1]) dr = R1;
		    else if (!busy[R2]) dr = R2;
		    else cerror ("Index reg not available for struct move"); 
#endif
    		}

    		if (busy[R4]) {		/* use R4 for bib reg */
    		    /* allocate temp space on stack */
    		    tempnode.in.op = OREG;
    		    tempnode.in.type = INT;
    		    tempnode.in.name = "";
    		    tempnode.tn.rval = TMPREG;
    		    tempnode.tn.lval = BITOOR(freetemp(1));	/* 1 word */

    		    /* save bib register */
    		    printf("\tstw\tr4,");
    		    adrput(&tempnode);  
    		    printf("\n");
    		}

    		if ((size & 3) == 0) {
    		    printf("\tli\tr4,-%dw\n", size/(SZINT/SZCHAR));
    		} else {
    		    printf("\tli\tr4,-%d\n", size);
    		}

      		r->tn.lval = size-inc;

#ifndef FIX_040795
		/* get reg for left */
		if ((l->in.op == NAME) || (isfakereg (l->tn.rval) &&
    		  (l->in.op == OREG))) {
		    if (dr != R1 && !busy[R1]) xr = R1;
		    else if (dr != R2 && !busy[R2]) xr = R2;
		    else cerror ("Index reg not available for struct move"); 
    		    printf ("\tla\tr%d,", xr);
    		    expand(l, FOREFF, "AL\n");
    		} else {
    		    if (l->in.op != NAME && l->in.op != OREG)
cerror ("left op NOT NAME OR OREG, found op %s\n", opst[l->in.op]);
		}
		/* get reg for right */
		if ((r->in.op == NAME) || (isfakereg (r->tn.rval) &&
    		  (r->in.op == OREG))) {
		    if (xr != R1 && !busy[R1]) rr = R1;
		    else if (xr != R2 && !busy[R2]) rr = R2;
		    else cerror ("Index reg not available for struct move"); 
    		    printf ("\tla\tr%d,", rr);
    		    expand(r, FOREFF, "AR\n");
    		}
#endif

#ifdef FIX_040795
    		/* if name is extern, can't have offset */
    		if (l->in.op == NAME) {
		    if (dr == 1) {
    			xr = 1;
    			printf ("\tla\tr1,");
		    } else if (dr == 2) {
    			xr = 2;
    			printf ("\tla\tr2,");
    		    } else
    			 cderror ("Unavailable reg for struct move, reg = %d", dr); 
    		    expand(l, FOREFF, "AL\n");
    		} else
    		  if ((isfakereg (l->tn.rval) && (l->in.op == OREG))) {
		    if (dr == 1) {
    			xr = 1;
    			printf ("\tla\tr1,");
		    } else if (dr == 2) {
    			xr = 2;
    			printf ("\tla\tr2,");
    		    } else
    			 cderror ("Unavailable reg for struct move, reg = %d", dr); 
    		    expand(l, FOREFF, "AL\n");
    		  } else {
    		    if (l->in.op != NAME && l->in.op != OREG)
cerror ("left op NOT NAME OR OREG, found op %s\n", opst[l->in.op]);
    		  }
#endif

    		l->tn.lval = size-inc;
    		looplab = get2lab();
/*    		printf("L%d\tequ\t$\n", looplab); */
    		printf("L%d\tcequ\t$\n", looplab);

#ifdef FIX_040795
    		expand(p, FOREFF, "\tlZP\tr0,");
    		expand(r, FOREFF, "AR\n");
    		expand(p, FOREFF, "\tstZP\tr0,");

    		/* if name is extern, can't have offset */
    		if (l->in.op == NAME) {
    		    if (((size-inc) & 3) == 0)
    			printf("%dw,r%d\n", (size-inc)/(SZINT/SZCHAR), xr);
    		    else
    			printf("%d,r%d\n", (size-inc), xr);
    		    printf("\tsui\tr%d,%x\n", r->tn.rval, inc);
    		    printf("\tsui\tr%d,%x\n", xr, inc);
    		} else
    		  if ((isfakereg (l->tn.rval) && (l->in.op == OREG))) {
    		    if (((size-inc) & 3) == 0)
    			printf("%dw,r%d\n", (size-inc)/(SZINT/SZCHAR), xr);
    		    else
    			printf("%d,r%d\n", (size-inc), xr);
    		    printf("\tsui\tr%d,%x\n", r->tn.rval, inc);
    		    printf("\tsui\tr%d,%x\n", xr, inc);
    		} else {
    		    expand(l, FOREFF, "AL\n");
    		    printf("\tsui\tr%d,%x\n", r->tn.rval, inc);
    		    printf("\tsui\tr%d,%x\n", l->tn.rval, inc);
    		}
#else
    		expand(p, FOREFF, "\tlZP\tr0,");
		if (dr)
    		    printf("%dw,r%d\n", (size-inc)/(SZINT/SZCHAR), dr);
		else if (rr)
    		    printf("%dw,r%d\n", (size-inc)/(SZINT/SZCHAR), rr);
		else
    		    expand(r, FOREFF, "AR\n");
    		expand(p, FOREFF, "\tstZP\tr0,");
		if (xr)
    		    printf("%dw,r%d\n", (size-inc)/(SZINT/SZCHAR), xr);
		else
    		    expand(l, FOREFF, "AL\n");
		if (dr)
    		    printf("\tsui\tr%d,%x\n", dr, inc);
		else if (rr)
    		    printf("\tsui\tr%d,%x\n", rr, inc);
		else
    		    printf("\tsui\tr%d,%x\n", r->tn.rval, inc);
		if (xr)
    		    printf("\tsui\tr%d,%x\n", xr, inc);
		else
    		    printf("\tsui\tr%d,%x\n", l->tn.rval, inc);
#endif
    		printf("\tbi%c\tr4,L%d\n", ilchar, looplab);

    		if (busy[R4]) {
    		    /* restore bib reg */
    		    printf("\tlw\tr%d,",sr);
    		    adrput(&tempnode);	
    		    printf("\n");
    		}

		if(sr)
		    r->tn.rval = sr;

    		goto zzzScont;

		}	/* end of code for large structures */

#ifndef SPR_022794
    		/* if name is extern, can't have offset */
    		if (l->in.op == NAME) {
		    sxr = l->tn.rval;
		    if (!busy[R1]) xr = R1;
		    else if (!busy[R2]) xr = R2;
		    else cerror ("Index reg not available for struct move"); 
    		    printf ("\tla\tr%d,", xr);
    		    expand(l, FOREFF, "AL\n");
    		}
#endif
		l->tn.lval += size;
		r->tn.lval += size;
		while (size % inc) {
		    size -= 1;
		    l->tn.lval -= 1;
		    r->tn.lval -= 1;
		    expand(r, FOREFF, "\tlb\tr0,AR\n\tstb\tr0,");
#ifndef SPR_022794
    		    if (xr) {
    			printf("%db,r%d\n", l->tn.lval, xr);
    		    } else
#endif
		    expand(l, FOREFF, "AL\n");
		}

		/* need to transfer structure address that is in
		 * a reg variable made into an OREG to x1 or x2 so
		 * we can move the structure.  I can't seem to make
		 * local or trees not optimize away the UNARY MUL
	         * required to transfer the reg variable to an SAREG. 
		 */

#ifndef BUG3
		if (rdebug) {
		    printf ("rt found op %s\n", opst[r->in.op]);
		    printf ("lf found op %s\n", opst[l->in.op]);
		}
#endif
		if (r->in.op==OREG && (r->tn.rval >= R4 && r->tn.rval <= R7)) {
		    sr = r->tn.rval;
		    if (!busy[R1]) dr = R1;
		    else if (!busy[R2]) dr = R2;
		    else cerror ("Index reg not available for struct move"); 
		    expand(r, FOREFF|INAREG, "\ttrr\t");
		    printf("r%d,r%d\n", sr, dr); 
		    r->tn.rval = dr;
		}

		for (; size > 0; size -= inc) {
		    l->tn.lval -= inc;
		    r->tn.lval -= inc;

		    expand(p, FOREFF, "	lZP	r0,");
		    expand(r, FOREFF, "AR\n");
		    expand(p, FOREFF, "	stZP	r0,");
#ifndef SPR_022794
    		    if (xr) {
    			printf("%dw,r%d\n", l->tn.lval/(SZINT/SZCHAR), xr);
		/* 	printf("%d,r%d\n", l->tn.lval, xr); */
    		    } else
#endif
			expand(l, FOREFF, "AL\n");
		}
 
		if(sr)
		    r->tn.rval = sr;

  zzzScont:

		if (r->in.op == NAME)
		    r->in.op = ICON;

		/* deleted else clause that changes result reg */
		if(r->in.op == OREG) {
			r->in.op = REG;
		    }
		p->in.type = oldtype;
	    }
	    break;
	case 'n':			/* bit number of single-bit const */
	    switch (p->in.left->in.type) {
		case SHORT: 
		case USHORT: 
		    if (p->in.left->in.op == REG)
			break;
		    fldsz += 16;
		    break;
		case CHAR: 
		case UCHAR: 
		    if (p->in.left->in.op == REG)
			break;
		    fldsz += 24;
		    break;
		default: 
		    break;
	    }
	    printf ("%d", 31-fldsz);
	    break;

	case 'o':			/* bit number of single-bit const */
    					/* for mem incr replacement */
    					/* when we load into reg */
	    printf ("%d", 31-fldsz);
	    break;

	default: 
/* 	    printf ("bad zzzcode of %c\n",c); */
	    cerror("illegal zzzcode");
    }
}

void rmove(rt, rs, t) int rt, rs, t;
{
    if (t == DOUBLE || t == LONG)
	printf ("	trr	%s,%s\n", rnames[rs+1], rnames[rt+1]);
    printf("	trr	%s,%s\n", rnames[rs], rnames[rt]);
}

struct      respref
respref[] =
{
    INTAREG | INTBREG, STAREG | STBREG,
    INAREG | INBREG, SAREG | SBREG,
    INAREG | INBREG, SAREG | SBREG | SOREG | STARREG | STARNM | SNAME | SCON,
    INTEMP, INTEMP,
    0, 0
};

/* set up temporary registers */
void setregs()
{
    fregs = 4;
}

/* size, in registers, needed to hold thing of type t */
#ifndef szty
int szty(t)
{
    return((t == LONG || t == DOUBLE) ? 2 : 1);
}
#endif

#ifndef rewfld
int rewfld(p) NODE *p;
{
    return(1);
}
#endif

#ifndef callreg
int callreg(p) NODE    *p;
{
    return(R0);
}
#endif

#ifdef R2REGS 
int base(p) register NODE  *p;
{
    register int    o = p->in.op;
    register int    retval;

#ifndef BUG3
    if(odebug) {
	printf("base(0x%x):\n", p);
	fwalk(p, eprint, 0);
    }
#endif

/*
 *    if ((o == ICON && p->in.name[0] != '\0')) {
 *	retval = 100;				/* ie no base reg *-/
 *	goto out;
 *    }
 */
    if (o == REG && isbreg(p->tn.rval) && ! isfakereg(p->tn.rval)) {
	retval = p->tn.rval;
	goto out;
    }
    if ((o == PLUS || o == MINUS) && p->in.left->in.op == REG 
	&& isbreg(p->in.left->tn.rval)
	&& ! isfakereg(p->in.left->tn.rval)
	&& (p->in.right->in.op == ICON) ) {
	retval = p->in.left->tn.rval;
	goto out;
    }
/*
 *	Comment out for now.  OREG shouldn't be allowed here,
 *	but U& OREG probably should.
 *
 *    if (o == OREG && !R2TEST(p->tn.rval) 
 *	&& (p->in.type == INT || p->in.type == UNSIGNED 
 *	    || ISPTR(p->in.type))) {
 *	retval = p->tn.rval + 0x80 * 1;
 *	goto out;
 *    }
 */
    if (o == INCR && p->in.left->in.op == REG
	&& isbreg(p->in.left->tn.rval)
	&&  ! isfakereg(p->in.left->tn.rval)) {
	retval = p->in.left->tn.rval + 0x80 * 2;
	goto out;
    }
    if (o == ASG MINUS && p->in.left->in.op == REG
	&& isbreg(p->in.left->tn.rval)
	&& ! isfakereg(p->in.left->tn.rval)         ) {
	retval = p->in.left->tn.rval + 0x80 * 4;
	goto out;
    }
    if (o == UNARY MUL && p->in.left->in.op == INCR 
	&& p->in.left->in.left->in.op == REG
	&& isbreg(p->in.left->in.left->tn.rval)
	&& ! isfakereg(p->in.left->in.left->tn.rval)
    	&& (p->in.type == INT || p->in.type == UNSIGNED 
	    || ISPTR(p->in.type))) {
	retval = p->in.left->in.left->tn.rval + 0x80 * (1 + 2);
	goto out;
    }
    retval = (-1);

  out:
#ifndef BUG3
    if(odebug) {
	printf("	returning 0x%x\n", retval);
    }
#endif
    return(retval);
}
#endif

#ifdef R2REGS 
int offset(p, tyl) register NODE   *p;
int         tyl;
{
    register int retval;

#ifndef BUG3
    if(odebug) {
	printf("offset(p=0x%x, tyl=0x%x)\n", p, tyl);
	fwalk(p, eprint, 0);
    }
#endif
    if (tyl <= 4 && p->in.op == REG
	    && p->tn.rval != R0
	    && ! isfakereg(p->tn.rval)
	    && (p->in.type == INT || p->in.type == UNSIGNED
		|| ISPTR(p->in.type)) ) {
	retval = p->tn.rval;
	goto out;
    }
    if ((p->in.op == LS
	&& p->in.left->in.op == REG
	&& p->tn.rval != R0
	&& ! isfakereg(p->tn.rval)
	&& (p->in.left->in.type == INT 
		|| p->in.left->in.type == UNSIGNED)
		&& (p->in.right->in.op == ICON 
		&& p->in.right->in.name[0] == '\0')
		&& ((unsigned)1 << (unsigned)p->in.right->tn.lval) == tyl)) {
	retval = p->in.left->tn.rval;
	goto out;
    }
    retval = (-1);

  out:
#ifndef BUG3
    if(odebug) {
	printf("	returning 0x%x\n", retval);
    }
#endif
    return(retval);
}
#endif

#ifdef R2REGS 
makeor2(p, q, b, o) register NODE  *p, *q;
register int    b, o;
{
    register NODE  *t;
    register int    i;
    NODE       *f;

#ifndef BUG3
    if(odebug) {
	printf("makeor2(p=0x%x, q=0x%x, b=%d, o=%d)\n", p, q, b, o);
    }
#endif

    p->in.op = OREG;
    f = p->in.left;		/* have to free this subtree later */

 /* init base */
    switch (q->in.op) {

	case ICON: 
	case REG: 
	case OREG: 
	    t = q;
	    break;

	case MINUS: 
	    q->in.right->tn.lval = -q->in.right->tn.lval;

	case PLUS: 
	    t = q->in.right;
	    break;

	case INCR: 
	case ASG MINUS: 
	    t = q->in.left;
	    break;

	case UNARY MUL: 
	    t = q->in.left->in.left;
	    break;

	default: 
	    cerror("illegal makeor2");
    }

    p->tn.lval = t->tn.lval;
    p->in.name = t->in.name;

 /* init offset */
    p->tn.rval = R2PACK((b & 0x7f), o, (b >> 7));

    tfree(f);
    return;
}
#endif

int canaddr(p) NODE    *p;
{
    register int    o = p->in.op;

    if (o == NAME || o == ICON
	    || o == OREG
	    || (o == SCONV && p->in.left->in.op == OREG)
	    || (o == UNARY MUL && shumul(p->in.left)))
	return(1);
    if(o == REG && ! isfakereg(p->tn.rval))
	return(1);
    return(0);
}

int shltype(o, p) int o; register NODE    *p;
{
    return(o == REG || o == NAME || o == ICON
	    || o == OREG
	    || (o == UNARY MUL && shumul(p->in.left)));
}

int flshape(p) register NODE   *p;
{
    return(p->in.op == REG
	    || p->in.op == NAME
	    || p->in.op == ICON
	    || (p->in.op == OREG && (!R2TEST(p->tn.rval) || tlen(p) == 1)));
}

int shtemp(p) register NODE    *p;
{
    if (p->in.op == STARG)
	p = p->in.left;
    return(p->in.op == NAME
	    || p->in.op == ICON
	    || p->in.op == OREG
	    || (p->in.op == UNARY AND && p->in.left->in.op == OREG)
	    || (p->in.op == UNARY MUL && shumul(p->in.left)));
}

int shumul(p) register NODE    *p;
{
    return(p->in.op == REG && p->tn.rval & 7);
}

void adrcon(val) CONSZ   val;
{
    printf("=x'%x'", val);
}

void conput(p) register NODE    *p;
{
    switch (p->in.op) {

	case ICON: 
	    ahcon(p);
	    return;

	case REG: 
	    printf("%s", rnames[p->tn.rval]);
	    return;

	default: 
	    cerror("illegal conput");
    }
}

void insput(p) register NODE    *p;
{
    cerror("insput");
}

void upput(p) register NODE *p;
{
    int         temp;
    switch (p->in.op) {

	case REG: 
	    temp = p->tn.rval;
	    p->tn.rval++;
	    adrput(p);
	    p->tn.rval = temp;
	    break;

	default: 
	    temp = p->tn.lval;
	    p->tn.lval += (SZINT / SZCHAR);
	    adrput(p);
	    p->tn.lval = temp;
    }
}

#ifdef TWOPASS

extern	int	handopt;
int         lastloc = IDATA;

int locctr2(l)
int l;
{
    register int temp;
 /* l is ITEXT or IDATA */

    if (l == lastloc )
	return(l);
    temp = lastloc;
    lastloc = l;
    switch (l) {

	case ITEXT:
	    if (handopt)
		printf ("\tdsect\n");	/* all o/s code is dsect */
	    else
		printf ("\tcsect\n");
	    break;

	case IDATA:

	    printf ("\tdsect\n");
	    break;

	default:
	    cerror("illegal location counter");
    }

    return(temp);
}

static int tstrlen;	/*keep length of string around temporarily*/

struct	tstrngs *begstrng = NULL; 	/* beginning list of init strings */
struct	tstrngs *currstng = NULL; 	/* current entry of init string */

static int putting = 0;

void putabyte(v)
char    v;
{
	if(++putting >= 32)
	{       /* break string onto several lines */
		putting = 1;
		printf("'\n\tdatab\tc'");
	}

	if (v < ' ') {
		putchar('"');
		putchar(v+64);
		putting++;	/* for extra char */
		return;
	}

	if (v > '~') {
		printf("',x'%x',c'",v);
		putting += 12;	/* for extra chars */
		return;
	}

	/* undo funny characters */
	switch(v)
	{
	case '%':
	case '"':
	case '\'':
	case ';':
		putchar('"');
		putting++;	/* for extra char */
	default:
		putchar(v);
	}
}

void dumpstr()
{
	char *strptr;
    	int iz = 0;

    	if (begstrng) {
    	    locctr2(IDATA);
    	    iz++;
    	}
	while (begstrng)
	{
		char *p;
		int  lim, i;

	    if (begstrng->slabel >= 0) {
		deflab(begstrng->slabel);
		putting = 0;
		printf("\tdatab\tc'");
		p = begstrng->strng;
		lim = begstrng->length - 1;
		/* -1 so we dont put out the null byte */
		for(i = 0; i < lim; i++,p++)
			putabyte( *p);
		printf("\"@'\n");
	    } else {
		printf("L%d\tdata%s\n",-begstrng->slabel, begstrng->strng);
	    }
		dofree(begstrng->strng);  /* string area is removed */
		currstng = begstrng;    /* so free will work      */
		begstrng = begstrng->next;
		dofree(currstng);         /* string struct is gone  */
	}
	currstng = NULL;
	begstrng = NULL;
#ifdef JUNK
    	if(!handopt && iz)
	    locctr2(ITEXT);
#else
    	if(iz)
	    locctr2(ITEXT);
#endif
}

int settmpstr(ch)
char * ch;	/*char string to save */
{
	int l;		/*the label number*/
	int i;
	char *cp;
	struct tstrngs * tempptr;

	tstrlen = strlen(ch);
	if (begstrng == NULL)
	{
		begstrng = (struct tstrngs *)domalloc(sizeof(struct tstrngs));
		currstng = begstrng;
		l = get2lab();	/* get a label for returning */
	}
	else
	{
	/* test to see if string is allready assigned, if so return label */
		for (tempptr=begstrng; tempptr; tempptr=tempptr->next)
			if (strcmp(tempptr->strng, ch) == 0)
			/* same string found, return its label */
				return(-tempptr->slabel);
		/* not found, save the string with a new label */
		l = get2lab();	/* get a label for returning */

		currstng->next =(struct tstrngs *)domalloc(sizeof(struct tstrngs));
		currstng = currstng->next;
	}
	currstng->next = NULL;
	currstng->slabel = -l;
	currstng->strng = cp = (char *)domalloc(tstrlen+1);
	currstng->length = tstrlen;
	for(i = 0; i < tstrlen; i++)
		*cp++ = *ch++;
	*cp = (char)0;
	return (l);
}

#endif

#ifdef MYATOF
static int fdigits;		/* number of digits printed */
static int dc;
static void putsman();
#endif

void adrput(p) register NODE    *p;
{
    register int    r;
    char nn[64];
    int ll;

    /* output an address, with offsets, from p */
    if (p->in.op == FLD) {
	p = p->in.left;
    }
    switch (p->in.op) {

	case NAME: 
	    acon(p);
	    return;

	case ICON: 
#ifdef TWOPASS_NOTNOW
#ifdef MYATOF
	case FCON: 
#endif
#endif
#ifdef FORT
	case FCON: 
#endif /* FORT */
    /* addressable value of the constant */
	    if (p->in.type == LONG || p->in.type == ULONG) {
	        if (p->in.name && p->in.name[0])
		  sprintf(nn, "d\t%s", p->in.name);
		else
#ifdef MYATOF
		  sprintf(nn, "d\t%d", p->tn.lval);
#else
		  sprintf(nn, "d\tx'00000000%08x'", p->tn.lval);
#endif
		ll = settmpstr(nn);
		/* print returned label number */
		printf("L%d",ll);
		return;
	    }
	    if (p->in.name[0] && !p->tn.lval) {
		sprintf(nn, "w\t%s", p->in.name);
		ll = settmpstr(nn);
		/* print returned label number */
		printf("L%d",ll);
		return;
	    }
#ifdef MYATOF_NOT_ANY_MORE
	    if (p->in.type == FLOAT || p->in.type == DOUBLE) {
		FPN f1;
		f1 = p->fpn.fpnum;
		dc = 0;
		if (p->in.type == DOUBLE)
		    nn[dc++] = 'd';
		else
		    nn[dc++] = 'w';
		nn[dc++] = '\t';
		if (p->in.type == DOUBLE)
		    nn[dc++] = 'r';
		else
		    nn[dc++] = 'e';
		nn[dc++] = '\'';
		if( isnegf( &f1 ) ){
			nn[dc++] = '-';
			negf( &f1 );
		}
		fdigits = 0;
		putsman( nn, &f1 );
		nn[dc++] = '.';
		nn[dc++] = 'e';
		if( f1.ne >= 0 )
		nn[dc++] = '+';
		sprintf(&nn[dc], "%d'\0",f1.ne);
		ll = settmpstr(nn);
		/* print returned label number */
		printf("L%d",ll);
	    return;
	    } 
#endif
	    /* generate literal constant */
	    PUTCHAR('=');
	    ahcon(p);
	    return;

	case REG: 
	    printf("%s", rnames[p->tn.rval]);
	    return;

	case OREG: 
	    r = p->tn.rval;
	    if (R2TEST(r)) {		/* double indexing */
		if (p->tn.lval != 0 || p->in.name[0] != '\0')
		    acon(p);
		if (R2UPK1(r) > R7)
		    printf ("(%s),%s", rnames[R2UPK1(r)], rnames[R2UPK2(r)]);
		else
		    printf ("(%s),%s", rnames[R2UPK2(r)], rnames[R2UPK1(r)]);
		return;
	    }
	    if (r == AP) {			/* in the arg region */
		if (p->tn.lval) {
		    if (p->tn.lval & 3) {
			printf("%d+LA%d,sp", p->tn.lval, ftnno);
		    }
		    else {
			printf("%dw+LA%d,sp", p-> tn.lval/(SZINT/SZCHAR), ftnno);
		    }
		}
		else
		    printf("LA%d,sp", ftnno);
		return;
	    }
	    if (r == FP) {
	    if (p->tn.lval & 3) {
		printf("%d+LOC%d,sp", p->tn.lval+(FRAMESZ/SZCHAR), ftnno);
	    }
	    else {
		printf("%dw+LOC%d,sp", (p->tn.lval+(FRAMESZ/SZCHAR))/(SZINT/SZCHAR), ftnno);
		    }
		return;
	    }
	    if (r == CP) {
		if (p->tn.lval & 3) {
		    printf("%d+CALL%d,sp", p->tn.lval + ARGINIT / SZCHAR, ftnno);
		}
		else {
		    printf("%dw+CALL%d,sp", (p->tn.lval / (SZINT / SZCHAR)) + ARGINIT / SZINT, ftnno);
		}
		return;
	    }
	    if (p->tn.lval != 0 || p->in.name[0] != '\0')
		acon(p);
	    else
		printf ("0");
	    printf(",%s", rnames[p->tn.rval]);
	    return;

	default: 
	    cerror("illegal address");
	    return;

    }

}

void ahcon(p)
register NODE *p;
{				/* print out a constant */
    register  int  v = p->tn.lval;

#ifdef JUNK
printf("\nahcon type = %s val = %x\n",
 p->in.type == FLOAT ? "FLOAT" : "DOUBLE", v);
#endif
#ifdef FORT
    if (p->in.type == DOUBLE && v != 0) {	/* double zero ok */
#else /* NOT FORT */
    if ((p->in.type == DOUBLE || p->in.type == LONG) && v != 0) {
    /* double zero ok */
    /* if (p->in.type == DOUBLE) { */
    /* Introducing special case for  */
    /* Double Precision constants = 0*/
#endif /* FORT */
	cerror("double precision constant attempted");
    }
    if (p->in.name[0] == '\0') {
	if (v >= 0 && v < 10) {
	    printf("%d", v);
	    return;
	}
	printf("x'%x'", v);
    } else
	if (v == 0) {
	    printf("%s", p->in.name);
	} else {
	    printf("%s+%d", p->in.name, v);
	}
}

void acon(p) register NODE  *p;
{						/* print out a constant */
    char *prefix = "";

    if(p->in.op == OREG && plusused == 0)
	prefix = "";
    if (p->in.name[0] == '\0') {
	    int val = p->tn.lval;
	    char *wd = "";

	    if ((val & 3) == 0) {
		val /= (SZINT / SZCHAR);
		wd = "w";
	    }
		printf ("%s%d%s", prefix, val, wd);
    }
    else {
	if (p->tn.lval == 0) {
	    printf("%s%s", prefix, p->in.name);
	}
	else {
	    int val = p->tn.lval;
	    char *wd = "";

	    if ((val & 3) == 0) {
		val /= (SZINT / SZCHAR);
		wd = "w";
	    }
	    if(val < 0)
		printf ("%s%s-%d%s", prefix, p->in.name, - val, wd);
	    else
		printf ("%s%s+%d%s", prefix, p->in.name, val, wd);
	}
    }
}


void initcon(p) register NODE  *p;
{						/* print out a constant */
    char *prefix;

    if (p->in.name[0] == '\0') {
	printf("%d", p->tn.lval);
    }
    else {
	prefix = "";
	if (p->tn.lval == 0) {
	    printf("%s%s", prefix, p->in.name);
	}
	else {
#ifdef FORT
	    if(p->tn.lval < 0)
 		printf ("%s%s-%d", prefix, p->in.name, - p->tn.lval);
	    else
 		printf ("%s%s+%d", prefix, p->in.name, p->tn.lval);
#else
	    if ((p->tn.lval & 3) == 0)
		printf("%s+%dw", p->in.name, p->tn.lval / (SZINT / SZCHAR));
	    else
		printf("%s+%d", p->in.name, p->tn.lval);
#endif
	}
    }
}


int genscall(p, cookie) register NODE  *p; int cookie;
{
 /* structure valued call */
    return(gencall(p, cookie));
}

extern void regfix();

int gencall(p, cookie) register NODE   *p; int cookie;
{
 /* generate the call given by p */
    register NODE  *p1, *ptemp;
    register    int temp, temp1;
    register    int m;
    int		fort;
    int     saveawc = argwordcount;
    NODE	*argnode = NIL;
    NODE	*genargs();
    NODE	*svp = NIL;		/* node with structure dest addr */
    int		ty;

#ifndef BUG3
    if (odebug) {
	printf("gencall( %x, ", p);
	print("cookie", cookie);
	printf(" )\n");
	fwalk(p, eprint, 0);
	if(p->in.right) {
		printf("args:");
		fwalk(p->in.right, eprint, 0);
	}
    }
#endif

    fort = 0;
    if (p->in.right)
	temp = argsize(p->in.right);
    else
	temp = 0;
    argcnt = 0;
    if (p->in.op == FORTCALL || p->in.op == UNARY FORTCALL) {
    	fort = 1;
    	temp += 8;
    }
    argwordcount = temp / (SZINT / SZCHAR);

    if (p->in.op == STCALL || p->in.op == UNARY STCALL) {
    	/* set aside room for structure return */

	if (p->stn.stsize > temp)
	    temp1 = p->stn.stsize;
	else
	    temp1 = temp;
    }

    if (temp > maxargs)
	maxargs = temp;

    SETOFF(temp1, (SZINT / SZCHAR));

    if (p->in.right) { /* make temp node, put offset in, and generate args */
	ptemp = talloc();
	ptemp->in.type = INT;
	ptemp->in.op = OREG;
	ptemp->tn.lval = 0;
    	if (fort)
    	    ptemp->tn.lval += 4;	/* room for aRG COUNT */
	ptemp->tn.rval = CP;
	ptemp->in.name = "";
	ptemp->in.rall = NOPREF;
	ptemp->in.su = 0;
        /* insert address nodes for Fortran */
    	if (fort)
    	    p->in.right = fortaddr( p->in.right );

	genargs(p->in.right, ptemp);
	ptemp->in.op = FREE;
    }
    /* If any temp regs are busy, get them out of the way here. */

    if(busytregs())
	fwalk(stotree, regfix, 0);

    p1 = p->in.left;
 /* 
  * undo damage done by making & name usually go for movea
  */
    if (p1->in.op == UNARY AND && p1->in.left->in.op == NAME) {
	p->in.left = p1->in.left;
	p1->in.op = FREE;
	p->in.left->in.op = ICON;
    }
    else {
	if (p1->in.op != ICON) {
		p1->in.rall = R1;
		order(p1, INAREG);
	}
    }

    /* Fix for spr 86100263,  (*b())() problem */
    /* All busy temp regs have been stashed away by regfix() above. */

    if(p1->in.op == REG && p1->tn.rval == R0) {
	p1->tn.rall = R1;
	order(p1, INAREG); /* was INTAREG NOV1 */
    }

    /* End of 86100263 fix. */

    if (fort)
    	p->in.op = UNARY FORTCALL;
    else
    	p->in.op = UNARY CALL;

    m = match(p, INTAREG | INTBREG);

#ifndef BUG3
    if (odebug) {
	printf("gencall( %x, ...) returning\n ", p);
	fwalk(p, eprint, 0);
    }
#endif

 /* 
  * nesting of calls is ok when the call is for the first parameter
  */
    argwordcount = saveawc;
    return(m != MDONE);
}

NODE * fortaddr(p)	/* insert U& nodes for Fortran arguments */
NODE *p;
{
    NODE * pa, *pcv;
    if (p->in.op == CM) {
    	p->in.left = fortaddr(p->in.left);
    	p->in.right = fortaddr(p->in.right);
    	return(p);
    }
    argcnt += 4;
    if (p->in.op == UNARY MUL) {
    	/* we can remove it because OREG's are already created */
    	p->in.op = FREE;
    	pa = p->in.left;
    } else {
    	pa = talloc();
    	pa->in.op = UNARY AND;
    	pa->in.left = p;
    	pa->in.type = INCREF( p->in.type );
    }

    switch( p->in.type ) {
    	case CHAR:
    	case SHORT:
    	case USHORT:
    	/*
    	case LONG:
    	case DOUBLE:
    	*/
    	    pcv = talloc();
    	    pcv->in.op = PCONV;
    	    pcv->in.left = pa;
    	    pcv->in.type = pa->in.type;
    	    return(pcv);
    }
    return(pa);
}

char       *ccbranches[] =
{
    "	beq	L%d\n",
    "	bne	L%d\n",
    "	ble	L%d\n",
    "	blt	L%d\n",
    "	bge	L%d\n",
    "	bgt	L%d\n",
    "	bule	L%d\n",
    "	bult	L%d\n",
    "	buge	L%d\n",
    "	bugt	L%d\n",
};

void cbgen(o, lab, mode) int o, lab, mode;
{		/*   printf conditional and unconditional branches */

    if (o == 0)
	printf("	bu	L%d\n", lab);
    else {
	if (bittestused == 2) {

	    switch (o) {

		case GE: 
		    printf("	bs	L%d\n", lab);
		    break;

		case LT: 
		    printf("	bns	L%d\n", lab);
		    break;

		case EQ: 
		    printf("	bns	L%d\n", lab);
		    break;

		case NE: 
		    printf("	bs	L%d\n", lab);
		    break;
		default: 
		printf ("bit test op2 bad, op=%s\n", opst[o]);
		    cerror("bit test incorrectly selected");
	    }
	    bittestused = 0;
	    return;
	}
	if (bittestused == 1) {
	    switch (o) {

		case EQ: 
		    printf("	bns	L%d\n", lab);
		    break;

		case AND:
		case NE: 
		    printf("	bs	L%d\n", lab);
		    break;

		default: 
		printf ("bit test op1 bad, op = %s\n", opst[o]);
		    cerror("bit test incorrectly selected");
	    }
	    bittestused = 0;
	}
	else {

	    if (o >= ULE)
		cerror("bad conditional branch: %s", opst[o]);
	    printf(ccbranches[o - EQ], lab);
	}
    }
}

int nextcook(p, cookie) NODE   *p; int cookie;
{
 /* we have failed to match p with cookie; try another */
    if (cookie == FORREW)
	return(0);			/* hopeless! */
    if (!(cookie & (INTAREG | INTBREG)))
	return(INTAREG | INTBREG);
    if (!(cookie & INTEMP) && asgop(p->in.op))
	return(INTEMP | INAREG | INTAREG | INTBREG | INBREG);
    return(FORREW);
}

int lastchance(p, cook) NODE   *p; int cook;
{
 /* forget it! */
#ifndef BUG4
    printf("-- lastchance %x (", p);
    print ("cookie", cook);
    printf (")\n");
    if (odebug) {
	fwalk(p, eprint, 0);
    }
#endif
    return(0);
}

void optim2(p) register NODE    *p;
{
 /* do local tree transformations and optimizations */

    register NODE  *r;

#ifndef BUG3
    if (odebug) {
	printf("optim2(%x):\n", p);
	fwalk(p, eprint, 0);
    }
#endif

    switch (p->in.op) {
#ifndef SPR_031294
    	case SCONV:
    		/* reg values can change type */
    		if (p->in.left->in.op == REG && 
    		    p->in.type == INT) {
    			r = p->in.left;
    			*p = *r;
    			r->in.op = FREE;
/*    			p->in.left->in.type = p->in.type; */
    		}
		break;
#endif
	case LADDR:
	case PADDR:
		LAddrFix(p);
		break;

	case STADDR:
	case ADDR:
		p->in.op = ICON;
		break;

	case LNAME:
	case PNAME:
	case STATNAME:
		LNameFix(p);
		break;

	case EQ:
	case NE:
	    if ((p->in.left->in.type == CHAR 
			|| p->in.left->in.type == UCHAR)
		&& (p->in.right->in.type == CHAR 
			|| p->in.right->in.type == UCHAR)) {
		p->in.left->in.type = UCHAR;
		p->in.right->in.type = UCHAR;
	    }
	    break;
    }
}

#ifndef ONEPASS
extern int mainp2();

int main(argc, argv)
int argc;
char  *argv[];
{
    return(mainp2(argc, argv));
}
#endif

#ifndef NO_REG_REG	/* HARDOPS  /* forget hardops for MPX */
extern	int _flag;	/* set if no _ on names */
struct      functbl
{
    int         fop;
    int		flag;
    TWORD       rtype;
    TWORD       ftype;
    char       *func;
} opfunc[] = {

    SCONV, C_LD, LONG, DOUBLE, "_cvtld",	/* fltd emulation */
    SCONV, C_DL, DOUBLE, LONG, "_cvtdl",	/* fixd emulation */
    SCONV, C_ULD, ULONG, DOUBLE, "_cvtuld",	/* fltd emulation */
    SCONV, C_DUL, DOUBLE, ULONG, "_cvtdul",	/* fixd emulation */

    SCONV, C_LD, INT, DOUBLE, "_cvtld",		/* fltd emulation */
    SCONV, C_DL, DOUBLE, INT, "_cvtdl",		/* fixd emulation */
    SCONV, C_ULD, UNSIGNED, DOUBLE, "_cvtuld",	/* fltd emulation */
    SCONV, C_DUL, DOUBLE, UNSIGNED, "_cvtdul",	/* fixd emulation */

    SCONV, C_IF, INT, FLOAT, "_cvtif",		/* fltw emulation */
    SCONV, C_FI, FLOAT, INT, "_cvtfi",		/* fixw emulation */
    SCONV, C_UIF, UNSIGNED, FLOAT, "_cvtuif",	/* fltw emulation */
    SCONV, C_FUI, FLOAT, UNSIGNED, "_cvtfui",	/* fixw emulation */
    0, 0, 0
};

void hardops(p) register NODE   *p;
{
 /* change hard to do operators into function calls.  */
    register NODE  *q;
    register struct functbl    *f;
    register    int o;
    register TWORD  t;

    o = p->in.op;
    if (o != SCONV)
    	return;
    t = p->in.type;

#ifdef FORT
 /* 
  * NOTE: only mulops need rewriting
  */
 /* 
  * fortran compiler believes that the machine actually
  * has a  double = single * double
  * type auto-converting floating point instruction set.
  * *sigh* we must SCONV it otherwise
  */
    if (t == FLOAT || t == DOUBLE) {
	if (o == ASSIGN || (dope[o] & (FLOFLG | LOGFLG))) {
	    if (asgop(o)) {
		t = p->in.left->in.type;
	    }
	    else {
		if (p->in.left->in.type != t) {
		    q = talloc();
		    q->in.rall = NOPREF;
		    q->in.op = SCONV;
		    q->in.type = t;
		    q->in.left = p->in.left;
		    p->in.left = q;
		    hardops(q);
		}
	    }
	    if (p->in.right->in.type != t) {
		q = talloc();
		q->in.rall = NOPREF;
		q->in.op = SCONV;
		q->in.type = t;
		q->in.left = p->in.right;
		p->in.right = q;
		hardops(q);
	    }
	    return;
	}
    }
#endif /* FORT */

    /* look for the proper match */
    for (f = opfunc; f->fop; f++) {
	if (o == f->fop) {
    	    if (o == SCONV && t == f->ftype &&
    	      p->in.left->in.type == f->rtype) {
    		p->in.right = p->in.left;
    		goto makeitcall;
    	    }
    	}
    }
    return;

 /* put function name in left node of call */
makeitcall: 
    p->in.op = CALL;
    p->in.left = q = talloc();
    q->in.op = ICON;
    q->in.rall = NOPREF;
    q->in.type = INCREF(FTN + p->in.type);
    if (_flag)
	q->in.name = &f->func[1];	/* no _ in name */
    else
	q->in.name = f->func;
    q->tn.lval = 0;
    q->tn.rval = 0;
    extflg |= f->flag;		/* set ext flag */

    return;

}

#endif /* NO_REG_REG HARDOPS */

extern int noreg;		/* set non zero if no reg-reg instrs */

void myreader(p) register NODE  *p;
{
#ifndef BUG3
    if (odebug) {
	printf("myreader(%x):\n", p);
	fwalk(p, eprint, 0);
    }
#endif

#ifndef NO_REG_REG	/* HARDOPS  /* forget hardops for MPX */
    if (noreg)		/* call conversion subs if no reg-reg */
    	walkf(p, hardops);	/* convert ops to function calls */
#ifndef BUG3
    if(odebug) {
	printf("myreader(): after hardops()\n");
	fwalk(p, eprint, 0);
    }
#endif
#endif	/* NO_REG_REG HARDOPS */
    canon(p);			/* expands r-vals for fields */
#ifndef BUG3
    if(odebug) {
	printf("myreader(): after canon()\n");
	fwalk(p, eprint, 0);
    }
#endif
    walkf(p, optim2);
}

int special(p, shape) register NODE    *p; int shape;
{
    return(0);
}

int busytregs()	/* check for busy temp regs before doing call */
{
	if( busy[R0] || busy[R1] || busy[R2] || busy[R3] )
		return(1);
	else
		return(0);
}

void regfix(p)
NODE *p;
{
	int o;

	o = p->in.op;
	if( o != REG && o != OREG )
		return;

#ifndef BUG3
	if(odebug) {
		printf("regfix(%x): busy[%d] = %d\n", p, p->tn.rval,
			busy[p->tn.rval]);
	}
#endif

	switch(p->tn.rval) { /* Catch refs to temp registers. */
	case R0:
	case R1:
	case R2:
	case R3:
		order(p, INTEMP);  /* Stash it away in temp */
	}

#ifndef BUG3
	if(odebug) {
		printf("regfix() returns: busy[%d] = %d\n",  p->tn.rval,
			busy[p->tn.rval]);
	}
#endif
}

#define INRIGHT		0x1
#define INLEFT		0x2
#define INOUTER		0x4

#define iseven(r)	(((r) & 01) == 0)

int lastditch(p, cookie)
NODE	*p;
int	cookie;
{
	register NODE	*pl, *pr;
	int		m, reg, rlower, rupper;
	int		rval0, rval1;

	int		rusage[REGSZ];	/* Values: or'ed together
					 *	INLEFT   - left side of p
					 *	INRIGHT  - right side of p
					 *	INOUTER  - Used outside of p
					 */

	int		rcount[REGSZ];	/*	Use count within tree p */
	int		wasbusy[REGSZ];	/*	Saved busy state */
	NODE		*n, svnode[2];	/*	Temps for save/restore */

#ifndef BUG3
	if(odebug) {
		printf("lastditch( %x, ", p);
		print("cookie", cookie);
		printf(")\n");
		fwalk(p, eprint, 0);
    		prbusy();
	}
#endif

	/* Check to see if tree obviously wont match. */
	pl = p->in.left;
	pr = GETR(p);

	/* Inventory register usage per tree and busy[] */

	for(reg=0; reg<REGSZ; reg++) {
		rusage[reg] = 0;
		rcount[reg] = 0;
		wasbusy[reg] = 0;
	}

	switch(optype(p->in.op)) {

	case BITYPE:
	case LTYPE:
		if(pr->in.op == REG || pr->in.op == OREG) {
			reg = pr->tn.rval;
			rusage[reg] |= INRIGHT;
			rcount[reg] += 1;
			if(szty(pr->in.type) > 1) {
				rusage[reg+1] |= INRIGHT;
				rcount[reg+1] += 1;
			}
		}

		if(optype(p->in.op) == LTYPE)
			break;

		/* for BITYPE, fall thru to case UTYPE to do left side. */

	case UTYPE:
		if(pl->in.op == REG || pl->in.op == OREG) {
			reg = pl->tn.rval;
			rusage[reg] |= INLEFT;
			rcount[reg] += 1;
			if((szty(pl->in.type)) > 1) {
				rusage[reg+1] |= INLEFT;
				rcount[reg+1] += 1;
			}
		}
		break;
	default:
		goto sorry;
	}

	for(reg=0; reg<REGSZ; reg++) {
		if(rcount[reg] < busy[reg])
			rusage[reg] |= INOUTER;
	}

	/* Pick best even/odd pair.  For now just use R0, R1. */

	rlower = R0; rupper = R1;
	
	/* Save regs picked for use, as needed per rusage[] */

	reg = rlower;
	while(1) {
		if(rusage[reg] & INOUTER) {
			n = &svnode[reg];
			n->in.op = OREG;
			n->in.name = "";
			n->tn.rval = TMPREG;
    			/* 1 word of temp space */
			n->tn.lval = BITOOR(freetemp(1));

			printf("	stw	%s,", rnames[reg]);
			adrput(n);
			printf("\n");

			wasbusy[reg] = busy[reg];
			busy[reg] = 0;
			/* Maybe need to account for possibility that
			   reg is in left or right as well as INOUTER ?? */
		} else {
			if((rusage[reg] & INRIGHT) ) {
				if( szty(pr->in.op) == 1 || iseven(reg) )
					order(pr, INTEMP);
			} else {
				if(rusage[reg] & INLEFT && !asgop(p->in.op)) {
					if(szty(pl->in.op) ==1 || iseven(reg) )
						order(pl, INTEMP);
				}
			}
		}

		if(reg == rupper)
			break;
		reg = rupper;
	}

#ifndef BUG3
	if(odebug) {
		prditch("rusage", rusage);
		prditch("rcount", rcount);
		prditch("wasbusy", wasbusy);
		prditch("busy", busy);
	}
#endif
#ifndef BUG3
	if(odebug) {
		printf("lastditch0( %x, ", p);
		print("cookie", cookie);
		printf(")\n");
		fwalk(p, eprint, 0);
    		prbusy();
	}
#endif

	/* Attempt to match the tree p and cookie */

	m = match(p, cookie);
	if(m != MDONE)
		m = match(p, INTEMP);
	if( m != MDONE)
		goto sorry;

	/* Save result in temp if restoring registers will clobber it. */

	if( (rusage[rlower] & INOUTER) || (rusage[rupper] & INOUTER) ) {
		rval0 = -1;
		rval1 = -1;
		if(p->in.op == REG || p->in.op == OREG) {
			rval0 = p->tn.rval;
			if(szty(p->in.type) > 1)
				rval1 = rval0 + 1;
		}

		if(rval0 == rlower || rval0 == rupper
		   || rval1 == rlower || rval1 == rupper) {
			match(p, INTEMP);
		}
	}


#ifndef BUG3
	if(odebug) {
		printf("lastditch1( %x, ", p);
		print("cookie", cookie);
		printf(")\n");
		fwalk(p, eprint, 0);
    		prbusy();
	}
#endif
    	/* we need to check regs again and somehow leave
    	 * the stored register in the temp loc and continue
    	 * without trying to reload the store reg
    	 */
	/* Restore registers as needed per rusage. */

	reg = rlower;
	while(1) {
		if(rusage[reg] & INOUTER) {
			/* generate movw to restore reg */
			printf("	lw	%s,", rnames[reg]);
			adrput(&svnode[reg]);
			printf("\n");
			busy[reg] = wasbusy[reg];
		}

		if(reg == rupper)
			break;
		reg = rupper;
	}
#ifndef BUG3
	if(odebug) {
		printf("lastditch2( %x, ", p);
		print("cookie", cookie);
		printf(")\n");
		fwalk(p, eprint, 0);
    		prbusy();
	}
#endif
	return(1);

  sorry:
	/* cant match */
	cerror("last ditch effort failed");
	return(0); /* silence warnings */
}


#ifndef BUG3
void prditch(s, ip)
char *s;
int  *ip;
{
	register int i;

	printf("%s[] = ", s);
	for(i=0; i<REGSZ; ++i) {
		printf(" %d", ip[i]);
	}
	printf("\n");
}
#endif

#ifdef FORT
/* SPR86100175 */  /* try making double register available by register swap */

static int rswpto, rswpfm;

int tryregswap() {
	register int i, nlim, nbusy;
	extern int mina, maxa;
	extern int regswap();
	NODE *p;

	rswpto = -1, rswpfm = -1, 
	nlim = maxa - mina - 1;
	nbusy = 0;
	for (i = maxa; i >= mina; --i) {
	    if (busy[i]) {
		if (++nbusy > nlim)
		    return 0;
		if (rswpto >= 0 && !busy[i ^ 1]
			&& (i & ~1) != (rswpto & ~1)) {
		    rswpfm = i;		/* highest reg below rswpto's pair */
					/* whose pairmate is not busy */
		    break;
		}
	    }
	    else if (rswpto < 0)
		    rswpto = i;		/* highest non-busy reg */
	}
	if (rswpto < 0 || rswpfm < 0)
	    return 0;
	printf("\ttrr\tr%d,r%d\n", rswpfm, rswpto);
	p = stotree;
#ifndef BUG3
	if (edebug)
	    fwalk(p, eprint, 0);
#endif
	fwalk(p, regswap, 0);
	return 1;
}

void regswap(p)
NODE *p;
{
	if ((p->in.op == REG || p->in.op == OREG) && p->tn.rval == rswpfm) {
	    p->tn.rval = rswpto;
	    ++busy[rswpto];
	    --busy[rswpfm];
#ifndef BUG3
	    if (edebug)
		printf("swapped %d, %d in %#x\n", rswpfm, rswpto, p);
#endif
	} else
#ifndef BUG3
	    if (edebug)
		printf("swapped %d, %d in %#x\n", rswpfm, rswpto, p);
#endif
}
#endif /* FORT */

/*
 * Turn LNAME and PNAME nodes into OREGs, STATNAMEs into NAMEs
 */
void LNameFix(p)
	register NODE *p;
{
	if( p->in.op == STATNAME )
	{
		p->in.op = NAME;
	}
	else
	{
		/* NEED a FLEXNAME fix HERE ??? */
		p->tn.name = "";		/* forget name */
		p->tn.rval = (p->tn.op == LNAME ) ? FP : AP;
		p->in.op = OREG;
	}
}

/*
 * Fix up addresses of params and locals.  Main idea is to turn [LP]ADDR
 * into &, [LP]NAME and let others do all the work.
 */
void LAddrFix(p)
	register NODE *p;
{
	register NODE *q;

	q = talloc();
	*q = *p;
	p->in.op = UNARY AND;
	p->in.left = q;
	p->tn.rval = 0;
	p->in.rall = NOPREF;
	p->in.name = "";
	q->in.type = DECREF(p->in.type);

	switch(q->in.op)
	{
	case LADDR:
		q->in.op = LNAME;
		break;

	case PADDR:
		q->in.op = PNAME;
		break;

	default:
		cerror("bad op type in LAddrFix");
	}

	/* Now, have &, [LP]NAME.  Call LNameFix to turn the [LP]NAME into
	 * an OREG, then call optim2 to turn the &,OREG into the correct
	 * arithmetic
	 */
	LNameFix(q);
	optim2(p);
}

#ifndef FORT
#ifndef ONEPASS

#ifdef MYATOF

extern int divsk();
extern int isnzs();

static void putsman( nn, f1 )
char *nn;
register FPN *f1;
{
	register int	k;

	k = divsk( f1->nf, NF, 10, 0 );
	if( isnzs( f1->nf, NF ) ) putsman( nn, f1 );
#ifdef MYASM
	if (fdigits++ <= 20)
#else
	if (fdigits++ < 15)
#endif
		nn[dc++] = ( k + '0' );
	else
		f1->ne++;
}
#endif /* MYATOF */

void fltread(p) register NODE *p;
{
	int i;
	char buf[10];
	char nn[32];
#ifdef MYATOF
	FPN f1;
#endif
	/* Read a floating point literal from the intermediate file */
#ifdef MYATOF
	p->fpn.fpnum.ne = rdin(16);	/* get 16bit exponent */
	for (i = 0; i < NF; i++)	/* get mantissa */
		p->fpn.fpnum.nf[i] = rdin(16);
#else /* MYATOF */
	p->tn.lval = rdin(16);
	p->tn.rval = rdin(16);
#endif
	/* discard rest of line */
	while ( getchar() != '\n' ) ;

#ifdef MYATOF
	/* patch up FCONs to something pass2 understands */
	if ((p->in.type == DOUBLE || p->in.type == FLOAT) 
	    && !FP_ISZERO(&p->fpn.fpnum)) {
		f1 = p->fpn.fpnum;
		dc = 0;
		if (p->tn.type == FLOAT)
			nn[dc++] = 'w';
		else
			nn[dc++] = 'd';
		nn[dc++] = '\t';
		if (p->tn.type == FLOAT)
			nn[dc++] = 'e';
		else
			nn[dc++] = 'r';
		nn[dc++] = '\'';
		if( isnegf( &f1 ) ){
			nn[dc++] = '-';
			negf( &f1 );
		}
		fdigits = 0;
		putsman( nn, &f1 );
		nn[dc++] = '.';
		nn[dc++] = 'e';
		if( f1.ne >= 0 )
			nn[dc++] = '+';
		sprintf(&nn[dc], "%d'\0",f1.ne);
		i = settmpstr(nn);
		p->tn.lval = 0;
		p->tn.rval = 0;
		/* print returned label number */
		sprintf(buf, "L%d\0", i);
		p->tn.name = tstr(buf);
		p->tn.op = NAME;
	} else if (p->in.type == DOUBLE && FP_ISZERO(&p->fpn.fpnum)) {
		p->tn.op = ICON;
		p->tn.name = "\0";
	} else if (p->in.type == FLOAT && FP_ISZERO(&p->fpn.fpnum)) {
    		p->tn.type = DOUBLE;
		p->tn.op = ICON;
		p->tn.name = "\0";
	} else
		cerror("ERROR in fltread\n");
#else /* MYATOF */
	/* patch up FCONs to something pass2 understands */
	if (p->tn.type == FLOAT) {
/* printf("got float %x %x\n", p->tn.lval, p->tn.rval); */
	 	if(p->tn.lval != 0)
			p->tn.name = tstr("\0");
    		else
			p->tn.name = "\0";
		p->tn.op = ICON;
	} else 	if(p->tn.lval == 0 && p->tn.rval == 0) {
    		p->tn.type = DOUBLE;
/* printf("got double zero %x %x, op = %x, name = %x,%s\n",
 p->tn.lval, p->tn.rval, p->tn.op, p->tn.name, p->tn.name); */
		p->tn.op = ICON;
		p->tn.name = "\0";
	} else { /* DOUBLE */
#if defined(linux) || defined(__alpha)
		sprintf(nn,"d\tx'%08x%08x'", p->tn.rval, p->tn.lval);
#else
		sprintf(nn,"d\tx'%08x%08x'", p->tn.lval, p->tn.rval);
#endif
		i = settmpstr(nn);
		p->tn.lval = 0;
		p->tn.rval = 0;
		/* print returned label number */
		sprintf(buf, "L%d\0", i);
		p->tn.name = tstr(buf);
		p->tn.op = NAME;
	}
#endif /* MYATOF */
}

#endif /* ONEPASS */
/* generate code for a return
 * plus a hint to the optimizer
 */

#ifdef ONEPASS
void LclReturn(temp_label)
	register int temp_label;
{
#else
void LclReturn()
{
	register int temp_label;

	temp_label = rdin(10);
#endif /* ONEPASS */
	printf("\tbu\tL%d\n", temp_label);
}
#endif /* FORT */

void ParamFetch(reg, offset, type, ftnnox)
int reg, offset, type, ftnnox;
{
    /* load register value */
    printf ("	lw	r%d", reg);
    printf(",%dw+LA%d,sp\n", offset / (SZINT/SZCHAR), ftnnox);
}

