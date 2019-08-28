/* local.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid =
"@(#) $Header: /bulk2/simhv/nbc-master/nbccom/RCS/local.c,v 1.17 2019/01/31 21:50:46 jbev Exp $";
#endif

/*
 * $Log: local.c,v $
 * Revision 1.17  2019/01/31 21:50:46  jbev
 * Update for Linux
 *
 * Revision 1.16  1996/03/18 23:55:06  jbev
 * Mods for Alpha port.
 *
 */

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

#include "mfile1.h"

/*	this file contains code which is dependent on the target machine */

NODE       *cast(p, t) register NODE   *p;
TWORD       t;
{
 /* cast node p to type t */

    p = buildtree(CAST, block(NAME, NIL, NIL, t, 0, (int) t), p);
    p->in.left->in.op = FREE;
    p->in.op = FREE;
    return(p->in.right);
}

NODE       *clocal(p) NODE *p;
{

 /* this is called to do local transformations on an expression tree
    preparitory to its being written out in intermediate code. */

 /* the major essential job is rewriting the automatic variables 
    and arguments in terms of REG and [LP]NAME nodes */
 /* conversion ops which are not necessary are also clobbered here */
 /* in addition, any special features (such as rewriting exclusive or)
    are easily handled here as well */

    register struct symtab *q;
    register NODE  *r;
    register    int o;
    register    int m, ml;
    register	NODE * newtree;		/* points to tree to be returned */
/*    extern int eprint(); */
    int icf;

#ifndef BUG2
    if(edebug) {
	printf("clocal(%x):\n", p);
	fwalk(p, eprint, 0);
    }
#endif

    switch (o = p->in.op) {

	case NAME: 
	    if (p->tn.rval < 0) {	/* already processed; ignore... */
		newtree = p;
#ifndef BUG2
	    if(tdebug) {
		printf("clocal(%x): case NAME, already processed\n", p);
		prstab(p->tn.rval);
	    }
#endif
		goto out;
	    }
#ifndef BUG2
	    if(tdebug) {
		printf("clocal(%x): case NAME\n", p);
		prstab(p->tn.rval);
	    }
#endif
	    q = &stab[p->tn.rval];
	    switch (q->sclass) {

		case AUTO:
		case PARAM:
#ifndef BUG2
			if(tdebug) {
			    printf("clocal(AUTO/PARAM)\n");
			    prstab(q - stab);
			}
#endif
		if( (q->optflags & (IsLNAME|IsPNAME)) != 0) {
#ifndef BUG2
			if(edebug) {
			    printf("clocal(AUTO/PARAM) @ LNAME/PNAME\n");
			    prstab(q - stab);
			}
#endif
			/* atomic id - turn this onto an LNAME or a
			 * PNAME
			 */
			p->in.op = ((q->optflags &IsLNAME) != 0)
				 ? LNAME
				 : PNAME;
			r = offcon( q->offset, INCREF(q->stype),
					q->dimoff,q->sizoff);
			p->tn.lval = r->tn.lval;
			r->in.op = FREE;		/* YECH */
		} else {
			int	paramsz;
			r = bcon(0);
#ifndef BUG2
			if(tdebug) {
			    printf("clocal(AUTO/PARAM)op into OREG\n");
			    prstab(q - stab);
			}
#endif
#ifdef ONEPASS
			p->in.op = OREG;
#else /* TWOPASS */
#ifndef OPTIMIZER
			p->in.op = OREG;
#else
/*XXX*/			p->in.op = REG;
#endif
#endif /* ONEPASS */
			p->tn.lval = 0;
			if(q->sclass == PARAM)
				p->tn.rval = ARGREG;
			else
				p->tn.rval = STKREG;
#ifdef TWOPASS
#ifdef OPTIMIZER
    			/* (MEY) 27-Jan-87  Make id cookie for PCO */
			p->tn.lval = p->tn.rval;
#endif
#endif /* TWOPASS */
#ifdef ONEPASS
			    p = buildtree(UNARY AND, p, 0);
#else /* TWOPASS */
#ifndef OPTIMIZER
			    p = buildtree(UNARY AND, p, 0);
#else
/*XXX*/			    p->in.type = INCREF(p->in.type);
#endif
#endif /* ONEPASS */
			p = buildtree(PLUS, p, r);
			r->tn.lval = q->offset / SZCHAR;
			newtree = buildtree(UNARY MUL, p, 0);
			paramsz = tsize(q->stype, q->dimoff, q->sizoff);
#ifndef BUG2
			if(edebug) {
			    printf("clocal(): paramsz=%d\n", paramsz);
			    prstab(q - stab);
			}
#endif
			if(paramsz > MAXARGSIZE && q->sclass == PARAM) {
			    /* one more level of indirection */
			    p->in.type = INCREF(p->in.type);
			    p->in.left->in.type = p->in.type;
			    newtree->in.type = INCREF(newtree->in.type);
			    newtree = 
				buildtree(UNARY MUL, newtree, 0);
			}
			goto out;
		}
		break;

		case ULABEL: 
		case LABEL: 
		case STATIC: 
		    if (q->slevel == 0)
			break;
		    p->tn.lval = 0;
		    p->tn.rval = -q->offset;
		    break;

		case REGISTER: 
			{
#ifndef BUG2
				if(tdebug) {
				    printf("clocal(REGISTER)op into REG\n");
				    prstab(q - stab);
				}
#endif
				/* provide id cookie for optimizer */
				p->tn.lval = IsRegVar(q->offset) ? q->uniqid
								: q->offset;
				p->in.op = REG;
				p->tn.rval = q->offset;
			}
			break;

	    }
	    break;

	case OREG: 
#ifndef BUG2
	if(edebug) {
		printf("clocal(%x) at OREG\n", p);
		fwalk(p, eprint, 0);
	}
#endif
#ifdef TWOPASS
#ifdef OPTIMIZER
	    cerror("OREG not expected in pass 1");
	    break;
#endif
#endif /* TWOPASS */
#ifndef OPTIMIZER
	    if (p->tn.lval < 0 || p->tn.lval > 0x80000) {
		int     off;
#ifndef BUG2
		if(tdebug) {
		    printf("clocal(OREG)op into UNARY MUL\n");
		    prstab(q - stab);
		}
#endif

		off = p->tn.lval;
		p->tn.lval = 0;
		r = bcon (0);
		p = buildtree (UNARY AND, p, 0);
		p = buildtree (PLUS, p, r);
		r->tn.lval = off;
		newtree = buildtree (UNARY MUL, p, 0);
		goto out;
	    }
	    break;
#endif /* ONEPASS || (TWOPASS && !OPTIMIZER) */

	case PCONV: 
    /* do pointer conversions for char and longs */
	    ml = p->in.left->in.type;
	    if ((ml == CHAR || ml == UCHAR || ml == SHORT || ml == USHORT) && p->in.left->in.op != ICON) {
		uerror("I strongly object to casting char/shorts into pointers");
		break;
	    }
    /* pointers all have the same representation; the type is inherited */

    inherit: 
	    p->in.left->in.type = p->in.type;
	    p->in.left->fn.cdim = p->fn.cdim;
	    p->in.left->fn.csiz = p->fn.csiz;
	    p->in.op = FREE;
	    newtree = p->in.left;
	    goto out;

	case SCONV: 
    	    /* look for a cast of a double/float to void and throw away the
    	     * conversion.  Not used anyway. */
    	    if (p->in.type == UNDEF && p->in.left->in.type == DOUBLE) {
    		p->in.op = FREE;
    		newtree = p->in.left;	/* conversion gets clobbered */
    		goto out;
    	    }
	    m = (p->in.type == FLOAT || p->in.type == DOUBLE);
	    ml = (p ->in.left->in.type == FLOAT || p->in.left->in.type == DOUBLE);
	    if (p->in.type == FLOAT && p->in.left->in.op == FCON) {
		p->in.op = FREE;
		p = p->in.left;
		p->in.type = FLOAT;
#ifdef	MYATOF
		/* no conversion if using myatof */
		/* p->fpn.fpnum = FP_DTOFP(p->fpn.fpnum);*/
		/* p->fpn.fpnum.nf[3] &= 0xf0; */
		for (icf=4; icf<NF; icf++)
		    p->fpn.fpnum.nf[icf];
#else
		p->fpn.dval = FP_DTOFP(p->fpn.dval);
#endif
		newtree = p;
		goto out;
	    }
	    /* new block of code to address "SCONV FCON" to double in
	       clocal() before the match fails because used in init */
	    if (p->in.type == DOUBLE && p->in.left->in.op == FCON) {
		p->in.op = FREE;
		p = p->in.left;
		p->in.type = DOUBLE;
#ifdef	MYATOF
		/* no conversion if using myatof */
		/* p->fpn.fpnum = FP_DTOF(p->fpn.fpnum);*/
		/* p->fpn.fpnum.nf[3] &= 0xf0; */
		for (icf=4; icf<NF; icf++)
		    p->fpn.fpnum.nf[icf];
#else
		p->fpn.dval = (FP_DOUBLE)(p->fpn.dval);
#endif
		newtree = p;
		goto out;
	    }
	    if (m || ml)
		break;

    /* now, look for conversions downwards */

	    m = p->in.type;
	    ml = p->in.left->in.type;
	    if (p->in.left->in.op == NAME &&
		m == INT && ml == UNSIGNED)
		goto inherit;
	    /* simulate the conversion here */
	    if (p->in.left->in.op == ICON ) {
		int       val;
		val = p->in.left->tn.lval;
		switch (m) {
		    case CHAR: 
			if( !onlyuchar){
			    val &= 0xff;
			    if( val&0x80 ){
				val |= ~0xff;
			    }
			    p->in.left->tn.lval = val;
			    break;
			}
		    case UCHAR: 
			p->in.left->tn.lval = val & 0XFF;
			break;
		    case USHORT: 
			p->in.left->tn.lval = val & 0XFFFFL;
			break;
		    case SHORT: 
			val &= 0xffff;
			if( val&0x8000 ){
			    val |= ~0xffff;
			}
			p->in.left->tn.lval = val;
			break;
		    case UNSIGNED: 
		    case INT: 
			break;
		    case LONG:
			if(ml != UNSIGNED) break;
			if( ((unsigned)p->in.left->tn.lval >> (SZINT-1)) & 1) {
				newtree = p;
				goto out;
			}
			break;
		}
		p->in.left->in.type = m;
	    }
	    else {
	/* meaningful ones are conversion of int to char, int to short,
	   and short to char, and unsigned version of them */
		if (m == CHAR || m == UCHAR) {
		    if (ml != CHAR && ml != UCHAR)
			break;
		}
		else
		    if (m == SHORT || m == USHORT) {
			if (ml != CHAR && ml != UCHAR && ml != SHORT && ml != USHORT)
			    break;
		    }
		    else
			if (m == LONG || m == INT) {
			    break;
			}
	    }

    /* clobber conversion */
	    if (tlen(p) == tlen(p->in.left))
		goto inherit;
	    p->in.op = FREE;
	    newtree = p->in.left;	/* conversion gets clobbered */
	    goto out;

	case PVCONV: 
	case PMCONV: 
	    if (p->in.right->in.op != ICON)
		cerror("bad conversion", 0);
	    p->in.op = FREE;
	    newtree = buildtree(o == PMCONV ? MUL : DIV, p->in.left, p->in.right);
	    goto out;


	case FLD: 
    /* make sure that the second pass does not make the descendant
       of a FLD operator into a doubly indexed OREG */

	    if (p->in.left->in.op == UNARY MUL
		    && (r = p->in.left->in.left)->in.op == PCONV)
		if (r->in.left->in.op == PLUS || r->in.left->in.op == MINUS)
		    if (ISPTR(r->in.type)) {
			if (ISUNSIGNED(p->in.left->in.type))
			    p->in.left->in.type = UCHAR;
			else
			    p->in.left->in.type = CHAR;
		    }
	    break;
    }

    newtree = p;

  out:
#ifndef BUG2
	if(edebug) {
		printf("clocal(%x) returning newtree %x\n", p, newtree);
		fwalk(newtree, eprint, 0);
	}
#endif

        return(newtree);
}

int andable(p) NODE    *p;
{
    return(p->in.op == NAME);		/* make all oregs use movea instr */
}

void cendarg()
{	/* at the end of the arguments of a ftn, set the automatic offset */
    autooff = AUTOINIT;
}

int cisreg(t) TWORD     t;
{	/* is an automatic variable of type t OK for a register variable */

    /* TRUST_REG_CHAR_AND_REG_SHORT */
    if (t == INT || t == UNSIGNED || t == LONG || t == ULONG
	    || t == CHAR || t == UCHAR || t == SHORT
	    || t == FLOAT
	    || t == USHORT || ISPTR(t))
	return(1);
    return(0);
}

int CanBeLNAME(t)
TWORD t;
{		/* is an automatic variable of type t OK for LNAME or PNAME */

	return( ISPTR(t) || t == CHAR || t == SHORT || t == INT ||
            t == ENUMTY ||
	    t == LONG || t == FLOAT || t == DOUBLE || ISUNSIGNED(t) );
}

NODE       *offcon(off, t, d, s) OFFSZ  off;
int d, s;
TWORD       t;
{
 /* return a node, for structure references, which is suitable for
    being added to a pointer of type t, in order to be
    off bits offset into a structure */

    register NODE  *p;
 /* t, d, and s are the type, dimension offset, and sizeoffset */
 /* in general they  are necessary for offcon, but not on H'well */

#ifndef BUG2
    if(tdebug) {
	printf("offcon(off = 0x%x):\n", off);
    }
#endif

    p = bcon(0);
    p->tn.lval = off / SZCHAR;
    return(p);

}

static      int inwd /* current bit offsed in word */ ;
static      int word /* word being built from fields */ ;

void incode(p, sz) register NODE    *p; int sz;
{

 /* generate initialization code for assigning a constant c 
    to a field of width sz */
 /* we assume that the proper alignment has been obtained */
 /* inoff is updated to have the proper final value */
 /* we also assume sz  < SZINT */

    if ((sz + inwd) > SZINT)
	cerror("incode: field > int");
    word = (unsigned)word | ((unsigned)(p->tn.lval << (32 - sz))) >> (inwd);
    inwd += sz;
    inoff += sz;
    if (inoff % SZINT == 0) {
	printf("	dataw	x'%x'\n", word);
	word = inwd = 0;
    }
}

#ifdef MYATOF
int	ldigits;	/* maximum digits to print */

void putman( f1 ) register FPN *f1; {
	register	int k;

	k = divsk( f1->nf, NF, 10, 0 );
	if( isnzs( f1->nf, NF ) ) putman( f1 );
#ifdef MYASM
	if (ldigits++ <= 20)
#else
	if (ldigits++ < 15)
#endif
		putchar( k + '0' );
	else
		f1->ne++;
}
#endif

#ifdef MYATOF
void fincode(f1, sz) FPN  *f1; int sz;
#else
void fincode(d, sz) FP_DOUBLE   d; int sz;
#endif
{
 /* output code to initialize space of size sz to the value d */
 /* the proper alignment has been obtained */
 /* inoff is updated to have the proper final value */
 /* on the target machine, write it out in octal! */

#ifdef MYATOF
    if (sz == SZDOUBLE) {
	printf("	datad	r'");
    } else {
	printf("	dataw	e'");
    }
	if( isnegf( f1 ) ){
		putchar( '-' );
		negf( f1 );
	}
	ldigits = 0;
	putman( f1 );
	putchar( '.' );
	putchar( 'e' );
	if( f1->ne >= 0 ) putchar( '+' );
	printf("%d'\n",f1->ne);

#else /* MYATOF */
    if (sz == SZDOUBLE) {
#if defined(linux) || defined(__alpha)
	union {
		double dd;
		int    n[2];
	} dd;
	dd = d;
	printf("	datad	%sx'%08x%08x'\n", "", dd.n[1], dd.n[0]);
#else
	printf("	datad	%sx'%08x%08x'\n", "", d);
#endif
    }
    else {
#if defined(linux) || defined(__alpha)
	union {
		double dd;
		int    n[2];
	} dd;
	dd = d;
	printf("	dataw	%sx'%x'\n", "", dd.n[1]);
#else
	printf("	dataw	%sx'%x'\n", "", d);
#endif
    }
#endif /* MYATOF */
    inoff += sz;
}

void cinit(p, sz) NODE  *p; int sz;
{
 /* arrange for the initialization of p into a space of size sz */
 /* the proper alignment has been opbtained */
 /* inoff is updated to have the proper final value */

        /*
         * Sun fix - see $w/sunfixes/t1.c
         * as a favor (?) to people who want to write
         *     int i = 9600/134.5;
         * we will, under the proper circumstances, do
         * a coersion here.
         */
        NODE *l;

        switch (p->in.type) {
        case INT:
        case UNSIGNED:
                l = p->in.left;
                if (l->in.op != SCONV || l->in.left->tn.op != FCON) break;
                l->in.op = FREE;
                l = l->in.left;
#ifdef MYATOF
                l->tn.lval = FP_DTOL(&l->fpn.fpnum);
#else
                l->tn.lval = FP_DTOL(l->fpn.dval);
#endif /* MYATOF */
                l->tn.rval = NONAME;
                l->tn.op = ICON;
                l->tn.type = INT;
                p->in.left = l;
                break;
        }

    ecode(p);
    inoff += sz;
}

/*
 ** define "n" bits of zeros in a field.
 */
void vfdzero (n)
int n;
{
    NODE	zeroinit;

    if (n <= 0)
	return;

    zeroinit.in.op = ICON;
    zeroinit.tn.lval = 0;
/* printf(" vfdzero calling incode(%x, %d):\n", &zeroinit, n); */
    incode (&zeroinit, n);	/* let initializer do it */
}

extern int	lastloc;
extern int	_flag;

char       *exname(p, q)
char *p;
struct symtab *q;
{
 /* make a name look like an external name in the local machine */

    static char     text[BUFSIZ + 1];
    register char *tp = text;
    int sf = q->sflags;

 /* 
  * For PCO, STAB entries must also be rewritten since they must match
  * the way they are referenced.
  */

    if (!_flag)		/* if _flag set, no _ for names */
        /* if we have a Fortran function, do not prepend with "_" */
	if (!(ISFTN(q->stype)
	  && (q->sclass == FORTRAN || q->sclass == UFORTRAN)))
	    *tp++ = '_';	/* prepend _ */
    while (*p) {		/* copy rest of name */
	*tp++ = *p++;
    }

    *tp = '\0';
    return(text);
}

int ctype(type) int type;
{	/* map types which are not defined on the local machine */
    extern      int onlyuchar;
    switch (BTYPE(type)) {

	case CHAR: 
	    if (onlyuchar) {
		MODTYPE(type, UCHAR);
	    }
	    break;

/*
*       would let LONGS alone if gram treats
*	long long var as a real long. otherwise int.
*/
	case LONG: 
	    MODTYPE(type, INT);
	    break;

	case ULONG: 
	    MODTYPE(type, UNSIGNED);
    }
    return(type);
}

int noinit()
{
/*
 * curid is a variable which is defined but is not initialized
 * (and not a function ); This routine returns the storage
 * class for an uninitialized declaration
 */
    return(EXTDEF);
}

int isitlong(cb, ce) int cb, ce;
{		/* is lastcon to be long or short */
 /* cb is the first character of the representation, ce the last */

    if (ce == 'l' || ce == 'L' ||
	    (unsigned)lastcon >= (unsigned)((unsigned)1L << (SZINT - 1)))
	return(1);
    return(0);
}

int isitfloat(s) char  *s;
{
#ifdef MYATOF
    /* ifpn has floating point number */
    FP_ATOF(s);
#else
    dcon = FP_ATOF(s);
#endif
    return(FCON);
}

#ifdef ONEPASS
void ecode(p) NODE  *p;
{
 /* walk the tree and write out the nodes.. */

    if (nerrors)
	return;
    p2tree(p);
    p2compile(p);
}
#else
void ecode(p) NODE  *p;
{
 /* walk the tree and write out the nodes.. */

    if (nerrors)
	return;
    printf("%1c%d\t%s\n", EXPR, lineno, ftitle);
    prtree(p);
}

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

void fltprint(p) register NODE *p;
{
#ifdef MYATOF
	int iz;
#endif
	/* print the value of a floating point constant to the intermediate
	 * file.
	 */

#ifdef MYATOF
	if(p->in.type == DOUBLE && !isnzs(&p->fpn.fpnum))
    	    getlab();
	printf("%x\t", p->fpn.fpnum.ne);
	for (iz=0; iz<NF; iz++)
		printf("%x\t", p->fpn.fpnum.nf[iz]);
#else
    	if (p->tn.lval == 0 && p->tn.rval == 0 && p->in.type == DOUBLE) 
    	    getlab();
	printf("%lx\t%lx\t",p->tn.lval, p->tn.rval);
#endif
}

#endif

NODE       *addroreg(l) int l;
{
/*
 * OREG was built in clocal()
 * for an auto or formal parameter
 * now its address is being taken
 * local code must unwind it
 * back to PLUS/MINUS REG ICON
 * according to local conventions
 */
    cerror("address of OREG taken");
    return(0);
}
