/* match.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid = "$Header: /bulk2/simhv/nbc-master/nbccom/RCS/match.c,v 1.8 2021/07/01 03:08:31 jbev Exp $";
#endif

/*
 * $Log: match.c,v $
 * Revision 1.8  2021/07/01 03:08:31  jbev
 * Define two pass variable.
 *
 * Revision 1.7  2019/03/13 21:00:19  jbev
 * Make tdebug external to stop error.
 *
 * Revision 1.6  2019/01/31 21:56:44  jbev
 * Update for Linux
 *
 * Revision 1.5  1997/01/22 18:28:07  jbev
 * Correct pointer/integer problem with error messages.
 * Only on Alpha because of 64 bit pointers and 32 bit ints.
 *
 * Revision 1.4  1996/03/22 00:07:35  jbev
 * Cleanup for Alpha Port.
 *
 */

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

#include "mfile2.h"

#ifdef WCARD1
#ifdef WCARD2
#define NOINDIRECT
#endif
#endif

#ifdef MPX
static char *opstri();
#endif

#ifndef BUG3
extern int vdebug;
#endif

int         fldsz, fldshf, fldaddr;

static int  mamask[] =
{				/* masks for matching dope with shapes */
    SIMPFLG,			/* OPSIMP */
    SIMPFLG | ASGFLG,		/* ASG OPSIMP */
    COMMFLG,			/* OPCOMM */
    COMMFLG | ASGFLG,		/* ASG OPCOMM */
    MULFLG,			/* OPMUL */
    MULFLG | ASGFLG,		/* ASG OPMUL */
    DIVFLG,			/* OPDIV */
    DIVFLG | ASGFLG,		/* ASG OPDIV */
    UTYPE,			/* OPUNARY */
    TYFLG,			/* ASG OPUNARY is senseless */
    LTYPE,			/* OPLEAF */
    TYFLG,			/* ASG OPLEAF is senseless */
    0,				/* OPANY */
    ASGOPFLG | ASGFLG,		/* ASG OPANY */
    LOGFLG,			/* OPLOG */
    TYFLG,			/* ASG OPLOG is senseless */
    FLOFLG,			/* OPFLOAT */
    FLOFLG | ASGFLG,		/* ASG OPFLOAT */
    SHFFLG,			/* OPSHFT */
    SHFFLG | ASGFLG,		/* ASG OPSHIFT */
    SPFLG,			/* OPLTYPE */
    TYFLG,			/* ASG OPLTYPE is senseless */
    BITFLG,			/* OPBIT */
    BITFLG | ASGFLG,		/* ASG OPBIT */
};

#ifndef BUG3
int         sdebug = 0;
#endif

int tshape(p, shape) NODE  *p;
int shape;
{
 /* return true if shape is appropriate for the node p
  * side effect for SFLD is to set up fldsz, etc
  */
    register    int o, mask;
    register 	int retval;

    o = p->in.op;

#ifndef BUG3
    if (sdebug) {
	printf("tshape( %x, ", p);
	print("shape", shape);
	printf("), op = %s", opst[o]);
    }
#define return(X) {retval=(X);goto out;}
#endif

    if (shape & SPECIAL) {

	if (o == ICON && !p->in.name[0]) {
	    mask = p->tn.lval;
#ifndef BUG3
	if (sdebug)
	    printf ("mask is %x\n");
#endif
	    switch (shape) {
		case SZERO:
		    return(mask == 0);
		case SONE:
		    return(mask == 1);
		case SMONE:
		    return(mask == -1);
		case SSCON:
		    return(mask >= -(1 << 15) && mask < (1 << 15));
		case SCCON:
		    return(mask >= -(1 << 7) && mask < (1 << 7));
		case SOCON:
#ifdef FORT
		    return(mask >= 0 && mask < 0x80000);
#else /* NOT FORT */
		    return(mask >= 0 && mask < 60000);
#endif /* FORT */
		case SPOW2:
		    return((fldsz = unsispow2(mask)) >= 0);
		case SCPOW2:
		    return((fldsz = unsispow2(~mask)) >= 0);
		case SHPOW2:
		    return((fldsz = unsispow2(mask)) >= 0 && fldsz <= 15);
		case SHCPOW2:
		    return((fldsz = unsispow2(~mask)) >= 0 && fldsz <= 15);
		case SICON:
		    return(1);
		case SBPOW2:
		    return((fldsz = unsispow2(mask)) >= 0 && fldsz <= 7);
		case SBCPOW2:
		    return((fldsz = unsispow2(~mask)) >= 0 && fldsz <= 7);
		case SACON:
		    return((mask & 0xffff0000) == 0xffff0000);
#ifdef MPX
		case SMCON:
		    return(mask >= 0 && mask <= 0x7ffff);
#endif
	    }
	}
#ifdef MULTILEVEL
	if (shape & MULTILEVEL)
	    return(mlmatch(p, shape, 0));
	else
	    return(special(p, shape));
#else
	return(special(p, shape));
#endif
    }

    if (shape & SANY)
	return(1);

    if ((shape & INTEMP) && shtemp(p))
	return(1);

    if ((shape & SWADD) && (o == NAME || o == OREG)) {
	if (BYTEOFF(p->tn.lval))
	    return(0);
    }

#ifdef WCARD1
    if (shape & WCARD1)
	return(wcard1(p) & shape);
#endif

#ifdef WCARD2
    if (shape & WCARD2)
	return(wcard2(p) & shape);
#endif
    switch (o) {

	case FCON:
	case NAME:
	    return(shape & SNAME);

	case ICON:
	    return(shape & SCON);

	case FLD:
	    if (shape & SFLD) {
		int         ty = p->in.type;
		if (!flshape(p->in.left))
		    return(0);
	/* it is a FIELD shape; make side-effects */
		fldaddr = 0;
		o = p->tn.rval;
		fldsz = UPKFSZ(o);
#ifdef RTOLBYTES
		fldshf = UPKFOFF(o);
#else
		fldshf = SZINT - fldsz - UPKFOFF(o);
#endif

		if (ty == SHORT || ty == USHORT) {
		    if (fldshf >= SZSHORT) {
			fldshf -= SZSHORT;
		    }
		    else {
			fldaddr = 2;
		    }
		}
		if (ty == CHAR || ty == UCHAR) {
		    if (fldshf >= (SZINT - SZCHAR)) {
			fldshf -= SZINT - SZCHAR;
		    }
		    else {
			fldaddr = 3 - (fldshf / SZCHAR);
			fldshf %= SZCHAR;
		    }
		}
		return(1);
	    }
	    return(0);

	case CCODES:
	    return(shape & (SCC | SZCC));

	case REG:
    /*
     * distinctions:
     * SAREG	any scalar register
     * STAREG any temporary scalar register
     * SBREG	any pointer register
     * STBREG	any temporary pointer register
     */
	    mask = isbreg(p->tn.rval) ? SBREG : SAREG;
	    if (istreg(p->tn.rval) && busy[p->tn.rval] <= 1)
		mask |= mask == SAREG ? STAREG : STBREG;
	    return(shape & mask);

	case OREG:
	    return(shape & SOREG);

/* #ifndef NOINDIRECT */
#ifdef MPX
	case UNARY MUL:
    /* return STARNM or STARREG or 0 */
	    return(shumul(p->in.left) & shape);
#endif

    }

    return(0);
#ifndef BUG3
#undef return
 out:
    if (sdebug)
	printf ("->%d\n", retval);
    return (retval);
#endif
}

#ifndef BUG3
#ifdef TWOPASS
int tdebug;
#else
extern int	tdebug;
#endif
#endif

int ttype(t, tword) TWORD   t;
int tword;
{
 /* does the type t match tword */

    if (tword & TANY)
	return(1);

    if (t == UNDEF)
	t = INT;		/* void functions eased thru tables */
#ifndef BUG3
    if (tdebug) {
	printf("ttype(");
	tprint(t);
	printf(", ");
	print("type", tword);
	printf(")\n");
    }
#endif
    if (ISPTR(t) && (tword & TPTRTO)) {
	do {
	    t = DECREF(t);
	} while (ISARY(t));
 /* arrays that are left are usually only in structure references... */
	return(ttype(t, tword & (~TPTRTO)));
    }
    if (t != BTYPE(t))
	return(tword & TPOINT);		/* TPOINT means not simple! */
    if (tword & TPTRTO)
	return(0);

    switch (t) {

	case CHAR:
	    return(tword & TCHAR);
	case SHORT:
	    return(tword & TSHORT);
	case STRTY:
	case UNIONTY:
	    return(tword & TSTRUCT);
	case INT:
	    return(tword & TINT);
	case UNSIGNED:
	    return(tword & TUNSIGNED);
	case USHORT:
	    return(tword & TUSHORT);
	case UCHAR:
	    return(tword & TUCHAR);
	case ULONG:
	    return(tword & TULONG);
	case LONG:
	    return(tword & TLONG);
	case FLOAT:
	    return(tword & TFLOAT);
	case DOUBLE:
	    return(tword & TDOUBLE);
#ifdef JCB073091_JUNK
	case VOID:
	    return(tword & TVOID);
#endif

    }

    return(0);
}

struct optab   *rwtable;

struct optab   *opptr[DSIZE];

void setrew()
{
 /* set rwtable to first value which allows rewrite */
    register struct optab  *q;
    register int    i;

#ifdef MULTILEVEL
 /* also initialize multi-level tree links */
    mlinit();
#endif

    for (q = table; q->op != FREE; ++q) {
	if (q->needs == REWRITE) {
	    rwtable = q;
	    goto more;
	}
    }
    cerror("bad setrew");


more:
    for (i = 0; i < DSIZE; ++i) {
	if (dope[i]) {			/* there is an op... */
	    for (q = table; q->op != FREE; ++q) {
/*  beware; things like LTYPE that match multiple things in the tree
    must not try to look at the NIL at this stage of things!
    Put something else first in table.c  */
/*  at one point, the operator matching was 15% of the total compile time;
    thus, the function call that was here was removed... */

		if (q->op < OPSIMP) {
		    if (q->op == i)
			break;
		}
		else {
		    register int opmtemp;
		    if ((opmtemp = mamask[q->op - OPSIMP]) & SPFLG) {
			if (i == NAME || i == ICON || i == OREG)
			    break;
			else
			    if (shltype(i, NIL))
				break;
		    }
		    else
			if ((dope[i] & (opmtemp | ASGFLG)) == opmtemp)
			    break;
		}
	    }
	    opptr[i] = q;
	}
    }
}

extern int noreg;	/* set non zero if no reg reg instructions */

int match(p, cookie) NODE  *p;
int cookie;
{
 /* called by: order, gencall look for match in table and generate code
    if found unless entry specified REWRITE.
    returns MDONE, MNOPE, or rewrite specification from table */

    register struct optab  *q;
    register NODE  *r;
    int i;

#ifndef BUG3
    if(rdebug) {
	printf("match(): busy[] = ");
	for(i=0; i<REGSZ; i++)
		printf(" %d", busy[i]);
	printf("\n");
    }
#endif
    rcount();
    if (cookie == FORREW)
	q = rwtable;
    else
	q = opptr[p->in.op];

    for (; q->op != FREE; ++q) {

 /* at one point the call that was here was over 15% of the total time;
    thus the function call was expanded inline */
	if (q->op < OPSIMP) {
	    if (q->op != p->in.op)
		continue;
	}
	else {
	    register int opmtemp;
	    if ((opmtemp = mamask[q->op - OPSIMP]) & SPFLG) {
		if (p->in.op != NAME && p->in.op != ICON &&
		p->in.op != OREG && !shltype(p->in.op, p))
		    continue;
	    }
	    else
		if ((dope[p->in.op] & (opmtemp | ASGFLG)) != opmtemp)
		    continue;
	}

    	/* here we need to add code to test for no regreg instructions
    	 * and select the correct table entry.  Add NOREG to cookie to
    	 * get a match.  The NOREG entries must be in the table first
    	 */
    	if (!(q->visit & cookie))
    	    continue;

    	/* see if no reg option */
    	if (!noreg) {
    	    /* no it's not, is this no reg table entry */
    	    if (q->visit & NOREG)
    		/* yes, ignore it */
		continue;
    	}

#ifndef BUG3
	if(odebug) {
		printf("Table[%d]: op=%d, visit=0%o\n",
			q - table, q->op, q->visit);
	}
#endif
	r = GETL(p);		/* see if left child matches */
	if (!(q->lshape & SANY) && !tshape(r, q->lshape))
	    continue;
	if (!(q->ltype & TANY) && !ttype(r->in.type, q->ltype))
	    continue;
	r = GETR(p);		/* see if right child matches */
	if (!(q->rshape & SANY) && !tshape(r, q->rshape))
	    continue;
	if (!(q->rtype & TANY) && !ttype(r->in.type, q->rtype))
	    continue;

 /* REWRITE means no code from this match but go ahead and rewrite node to help future match */
	if (q->needs & REWRITE)
	    return(q->rewrite);
#ifndef BUG3
	if(odebug) {
		printf("match(): calling allo()\n");
	}
#endif

	if (!allo(p, q))
	    continue;		/* if can't generate code, skip entry */

 /* resources are available */

#ifndef BUG3
	if(odebug) {
		printf("Table[%d]: match found\n", q - table);
	}
#endif
	expand(p, cookie, q->cstring);	/* generate code */
	reclaim(p, q->rewrite, cookie);
#ifndef BUG3
	if (odebug)
	    fwalk (p, eprint,0);
#endif
	return(MDONE);

    }

    return(MNOPE);
}

int         rtyflg = 0;

void expand(p, cookie, cp) NODE *p;
int cookie;
register char  *cp;
{
 /* generate code by interpreting table entry */

    register    int c;
    CONSZ       val;

    rtyflg = 0;

    for (; *cp; ++cp) {
	switch (*cp) {

	    default:
		PUTCHAR(*cp);
		continue;	/* this is the usual case... */

	    case 'T':
	/* rewrite register type is suppressed */
		rtyflg = 1;
		continue;

	    case 'Z': 		/* special machine dependent operations */
#ifdef NEWZZZ
		switch (c = *++cp) {

		    case '1':
		    case '2':
		    case '3':
			zzzcode(&resc[c - '1'], *++cp);
			break;
		    case 'R':
			zzzcode(GETR(p), *++cp);
			break;
		    case 'L': 			/* get down first */
			zzzcode(GETL(p), *++cp);
			break;
		    default: 	/* normal zzzcode processing otherwise */
			zzzcode(p, c);
			break;
		}
#else
		zzzcode(p, *++cp);
#endif
		continue;

#ifdef MPX
		case 'K':
		case 'G':
		{
		    char *cl = cp;
    		    char swv = *cp;
		    char nxc;
		    NODE * zx;
		    int	regl = 0;
		    int	regr = 0;

		    for (;*cl != '\n'; cl++) {
			switch (*cl) {
			    case 'A':
				nxc = *++cl;
				if (nxc == 'R') {
				    zx = GETR(p);
				    regl = zx->tn.rval;
				    continue;
				}
				if (nxc == 'L') {
				    zx = GETL(p);
				    regl = zx->tn.rval;
				    continue;
				}
				zx = getlr(p, nxc);
				regr = zx->tn.rval;
				continue;
			    case 'U':
				zx = getlr(p, *++cl);
				regr = zx->tn.rval + 1;
				continue;
			}
		    }
    		/* we only want to do this reg transfer if
    		 * we are moving from a reg variable to
    		 * the call return reg.
    		 */
#ifdef NOTUSED_NOW
if(swv == 'K')
printf("regl = %d , regr = %d\n", regl, regr);
#endif
    		if (swv == 'K' && regl < 4 && regr != 0) {
		    while (*++cp != '\n');		/* VOID */
    		    continue;
    		}
	    	/* this line deleted if trr is to same reg */
#ifdef IEEE_FIX
		if (regl == regr && regr != 0)
		    while (*++cp != '\n');		/* VOID */
#else /* IEEE_FIX */
		if (regl == regr && !(cookie & FORCC))
		    while (*++cp != '\n');		/* VOID */
#endif /* IEEE_FIX */
		}
		continue;
#endif
	    case 'F': 		/* this line deleted if FOREFF is active */
#ifdef MPX
		if (cookie & FOREFF)
		    while (*++cp != '\n');		/* VOID */
#endif
		continue;

	    case 'S': 			/* field size */
		printf("%d", fldsz);
		continue;

	    case 'D':
		if (fldshf == 0) {
		    while (*++cp != '\n');	/* delete zero size shifts */
		}
		continue;
	    case 'H': 				/* field shift */
#ifdef MPX
		printf("%d", fldshf);
#else
		printf("%dH", fldshf);
#endif
		continue;

	    case 'J':
		if (p->in.left->in.op != FLD) {
		    cerror("field assignment only");
		}
		p->in.left->in.left->tn.lval += fldaddr;
		continue;

	    case 'M': 			/* field mask */
	    case 'N': 			/* complement of field mask */
		val = 1;
		val = (unsigned)val << (unsigned)fldsz;
		--val;
		val = (unsigned)val << (unsigned)fldshf;
		adrcon(*cp == 'M' ? val : ~val);
		continue;

	    case 'L':			/* output special label field */
	    {
		int	    LC[3];
		c = *++cp;
		if (c == 'C') {
		   c = *++cp;
		   LC[c - '0'] = get2lab();
#ifdef MPX
/*		   printf("L%d	equ	$",LC[c - '0']); */
		   printf("L%d	cequ	$",LC[c - '0']);
#else
		   printf("L%d:",LC[c - '0']);
#endif
		}
		else if (c == 'J') {
		   c = *++cp;
		   printf("L%d",LC[c - '0']);
		}
		else
		   printf("%d", p->bn.label);
		continue;
	    }


	    case 'O': 			/* opcode string */
		hopcode(*++cp, p->in.op);
		continue;

	    case 'B': 			/* byte offset in word */
		val = getlr(p, *++cp)->tn.lval;
		val = BYTEOFF(val);
		printf(CONFMT, val);
		continue;

	    case 'C': 			/* for constant value only */
		conput(getlr(p, *++cp));
		continue;

	    case 'W': 			/* for constant value only */
		initcon(getlr(p, *++cp));
		continue;

	    case 'I': 			/* in instruction */
		insput(getlr(p, *++cp));
		continue;

#ifdef MPX
	    case 'E':
		{
		NODE * tmp;
		tmp = (GETR(p));
		if (tmp->in.op == FLD)
		    tmp = tmp->in.left;
#ifdef FEB17
		if (tmp->in.name[0]) {
		    printf (" FOUND a NAME %s ", tmp->in.name);
		}
		fwalk (tmp, eprint,0);
#endif
	/* DEC03 added test for long type */
		if ((tmp->in.op == ICON) && (p->in.type != LONG)) {
		    if (tmp->tn.lval >= 0 && tmp->tn.lval <= 0x7ffff) {
			printf("a");	/* make la */
			continue;
		    }
		}
#ifdef MPX
		prtype(tmp);
#else
		printf("w");	/* make lw */
#endif
		continue;
		}

	    case 'Q':
		c = *++cp;
		if (c == 'R') {
		    NODE * tmp;
		    tmp = (GETR(p));
		    if (tmp->in.op == FLD)
			tmp = tmp->in.left;
		    if (tmp->in.op == ICON) {
		        if (tmp->tn.lval >= 0 && tmp->tn.lval <= 0x7ffff) {
			    ahcon(tmp);
			    continue;
			}
		    }
		}
		--cp;
		/* fall through */
#endif
		
	    case 'A': 			/* address of */
		c = *++cp;
		if (c == 'R') {
		    adrput(GETR(p));
		    continue;
		}
		if (c == 'L') {
		    adrput(GETL(p));
		    continue;
		}
		adrput(getlr(p, c));
		continue;

	    case 'U': 			/* for upper half of address, only */
		upput(getlr(p, *++cp));
		continue;

	}

    }

}

NODE       *getlr(p, c) register NODE  *p;
int c;
{

 /* return the pointer to the left or right side of p,
    or p itself, depending on the optype of p */

    switch (c) {

	case '1':
	case '2':
	case '3':
	    return(&resc[c - '1']);

	case 'L':
	    return(optype(p->in.op) == LTYPE ? p : p->in.left);

	case 'R':
	    return(optype(p->in.op) != BITYPE ? p : p->in.right);

    }
    cderror("bad getlr: %d", c);
    return(0);
}
#ifdef MULTILEVEL

union       mltemplate
{
    struct      ml_head {
	int         tag;		/* identifies class of tree */
	int         subtag;		/* subclass of tree */
	union mltemplate   *nexthead;	/* linked by mlinit() */
    }           mlhead;
    struct      ml_node {
	int         op;		/* either an operator or op description */
	int         nshape;		/* shape of node */
 /* both op and nshape must match the node.
  * where the work is to be done entirely by
  * op, nshape can be SANY, visa versa, op can * be OPANY. */
	int         ntype;		/* type descriptor from mfile2 */
    }           mlnode;
};

#define MLSZ 30

extern union mltemplate     mltree[];
int         mlstack[MLSZ];
int        *mlsp;			/* pointing into mlstack */
NODE       *ststack[MLSZ];
NODE      **stp;			/* pointing into ststack */

void mlinit()
{
    union mltemplate  **lastlink;
    register union mltemplate  *n;
    register    int mlop;

    lastlink = &(mltree[0].nexthead);
    n = &mltree[0];
    for (; (n++)->mlhead.tag != 0;
	    *lastlink = ++n, lastlink = &(n->mlhead.nexthead)) {
#ifndef BUG3
	if (vdebug)
	    printf("mlinit: %d\n", (n - 1)->mlhead.tag);
#endif
 /* wander thru a tree with a stack finding
  * its structure so the next header can be located. */
	mlsp = mlstack;

	for (;; ++n) {
	    if ((mlop = n->mlnode.op) < OPSIMP) {
		switch (optype(mlop)) {

		    default:
			cderror("(1)unknown opcode: %x", mlop);
		    case BITYPE:
			goto binary;
		    case UTYPE:
			break;
		    case LTYPE:
			goto leaf;
		}
	    }
	    else {
		if (mamask[mlop - OPSIMP] &
			(SIMPFLG | COMMFLG | MULFLG | DIVFLG | LOGFLG | FLOFLG | SHFFLG)) {
	    binary:
		    *mlsp++ = BITYPE;
		}
		else
		    if (!(mamask[mlop - OPSIMP] & UTYPE)) {
		/* includes OPANY */

		leaf:
			if (mlsp == mlstack)
			    goto tree_end;
			else
			    if (*--mlsp != BITYPE)
				cderror("(1)bad multi-level tree descriptor around mltree[%d]",
					n - mltree);
		    }
	    }
	}
tree_end: 				/* n points to final leaf */
	;
    }
#ifndef BUG3
    if (vdebug > 3) {
	printf("mltree={\n");
	for (n = &(mltree[0]); n->mlhead.tag != 0; ++n)
	    printf("%x: %d, %d, %x,\n", n,
		    n->mlhead.tag, n->mlhead.subtag, n->mlhead.nexthead);
	printf("	}\n");
    }
#endif
}

int mlmatch(subtree, target, subtarget) NODE   *subtree;
int         target, subtarget;
{
 /*
  * does subtree match a multi-level tree with
  * tag "target"?  Return zero on failure,
  * non-zero subtag on success (or MDONE if
  * there is a zero subtag field).
  */
    union mltemplate   *head;		/* current template header */
    register union mltemplate  *n;	/* node being matched */
    NODE       *st;			/* subtree being matched */
    register int    mlop;

#ifndef BUG3
    if (vdebug)
	printf("mlmatch(%x,%d)\n", subtree, target);
#endif
    for (head = &(mltree[0]); head->mlhead.tag != 0;
	    head = head->mlhead.nexthead) {
#ifndef BUG3
	if (vdebug > 1)
	    printf("mlmatch head(%x) tag(%d)\n",
		    head->mlhead.tag);
#endif
	if (head->mlhead.tag != target)
	    continue;
	if (subtarget && head->mlhead.subtag != subtarget)
	    continue;
#ifndef BUG3
	if (vdebug)
	    printf("mlmatch for %d\n", target);
#endif

 /* potential for match */

	n = head + 1;
	st = subtree;
	stp = ststack;
	mlsp = mlstack;
 /* compare n->op, ->nshape, ->ntype to * the subtree node st */
	for (;; ++n) {		/* for each node in multi-level template */
    /* opmatch */
	    if (n->op < OPSIMP) {
		if (st->op != n->op)
		    break;
	    }
	    else {
		register int opmtemp;
		if ((opmtemp = mamask[n->op - OPSIMP]) & SPFLG) {
		    if (st->op != NAME && st->op != ICON && st->op != OREG &&
			    !shltype(st->op, st))
			break;
		}
		else
		    if ((dope[st->op] & (opmtemp | ASGFLG)) != opmtemp)
			break;
	    }
    /* check shape and type */

	    if (!(n.mlnode.nshape & SANY) && !tshape(st, n->mlnode.nshape))
		break;
	    if (!(n->mlnode.ntype & TANY) && !ttype(st->type, n->mlnode.ntype))
		break;

    /* that node matched, let's try another */
    /* must advance both st and n and halt at right time */

	    if ((mlop = n->mlnode.op) < OPSIMP) {
		switch (optype(mlop)) {

		    default:
			cderror("(2)unknown opcode: %x", mlop);
		    case BITYPE:
			goto binary;
		    case UTYPE:
			st = st->left;
			break;
		    case LTYPE:
			goto leaf;
		}
	    }
	    else {
		if (mamask[mlop - OPSIMP] &
			(SIMPFLG | COMMFLG | MULFLG | DIVFLG | LOGFLG | FLOFLG | SHFFLG)) {
	    binary:
		    *mlsp++ = BITYPE;
		    *stp++ = st;
		    st = st->left;
		}
		else
		    if (!(mamask[mlop - OPSIMP] & UTYPE)) {
		/* includes OPANY */

		leaf:
			if (mlsp == mlstack)
			    goto matched;
			else
			    if (*--mlsp != BITYPE)
				cderror("(2)bad multi-level tree descriptor around mltree[%d]",
					n - mltree);
			st = (*--stp)->right;
		    }
		    else		/* UNARY */
			st = st->left;
	    }
	    continue;

    matched:
    /* complete multi-level match successful */
#ifndef BUG3
	    if (vdebug)
		printf("mlmatch() success\n");
#endif
	    if (head->mlhead.subtag == 0)
		return(MDONE);
	    else {
#ifndef BUG3
		if (vdebug)
		    printf("\treturns %d\n",
			    head->mlhead.subtag);
#endif
		return(head->mlhead.subtag);
	    }
	}
    }
    return(0);
}
#endif
 
int unsispow2(x)
unsigned int x;
{
#ifdef MPX
    if (~x == 0x7fffffff) {
#else
    if ((unsigned) x == (unsigned) 0x80000000) {
#endif
	return(31);
    }
    else
	return(ispow2(x));
}

