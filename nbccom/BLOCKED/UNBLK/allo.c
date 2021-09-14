/* allo.c */
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
static char *rcsid = "@(#) (Gould) $Header: /u/nbc/nbccom/RCS/allo.c,v 1.1 1995/01/27 21:56:20 jbev Exp $";
#endif
 
/*
 
    C compiler for Gould processors, base register instruction set.
 
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
 
*/
#include "mfile2.h"
 
NODE        resc[3];
 
int         busy[REGSZ];
 
int         maxa, mina, maxb, minb;
#ifdef MPX
static ushare();
#endif
 
#ifndef ALLO0
allo0()
{		/* free everything */
 
    register    i;
 
    maxa = maxb = -1;
    mina = minb = 0;
 
    REGLOOP(i) {
	busy[i] = 0;
	if (rstatus[i] & STAREG) {
	    if (maxa < 0)
		mina = i;
	    maxa = i;
	}
	if (rstatus[i] & STBREG) {
	    if (maxb < 0)
		minb = i;
	    maxb = i;
	}
    }
}
#endif
 
#define TBUSY 01000
 
#ifndef ALLO
allo(p, q) NODE    *p;
struct optab   *q;
{
 
    register    n, i, j;
    int         either;
 
#ifndef BUG3
    if(rdebug) {
	printf("allo(p=0x%x, q=0x%x)\n", p, q);
	printf("q->op=%d, q->visit=0%o, q=>needs=0x%x\n",
		q->op, q->visit, q->needs);
    }
#endif
    n = q->needs;
    either = (EITHER & n);
    i = 0;
 
    while (n & NDMASK) {	/* need a register pair */
	resc[i].in.op = REG;
	resc[i].tn.rval = freereg(p, n & (NASL | NASR | NDMASK));
	resc[i].tn.lval = 0;
	resc[i].in.name = "";
	resc[i].in.type = LONG;
	n -= NDREG;
	++i;
    }
    while (n & NACOUNT) {
	resc[i].in.op = REG;
	resc[i].tn.rval = freereg(p, n & NAMASK);
	resc[i].tn.lval = 0;
	resc[i].in.name = "";
	resc[i].in.type = INT;
	n -= NAREG;
	++i;
    }
 
    if (either) {			/* all or nothing at all */
	for (j = 0; j < i; j++)
	    if (resc[j].tn.rval < 0) {	/* nothing */
		i = 0;
		break;
	    }
	if (i != 0)
	    goto ok;			/* all */
    }
 
    while (n & NBCOUNT) {
	resc[i].in.op = REG;
	resc[i].tn.rval = freereg(p, n & NBMASK);
	resc[i].tn.lval = 0;
	resc[i].in.name = "";
	resc[i].in.type = INT;
	n -= NBREG;
	++i;
    }
    if (either) {			/* all or nothing at all */
	for (j = 0; j < i; j++)
	    if (resc[j].tn.rval < 0) {	/* nothing */
		i = 0;
		break;
	    }
	if (i != 0)
	    goto ok;			/* all */
    }
 
    if (n & NTMASK) {
	resc[i].in.op = OREG;
	resc[i].tn.rval = TMPREG;
	resc[i].in.type = INT;
	if (p->in.op == STCALL
	    || p->in.op == STARG
	    || p->in.op == UNARY STCALL
	    || p->in.op == STASG) {
	    resc[i].tn.lval = freetemp((SZCHAR * p->stn.stsize + (SZINT - 1)) / SZINT);
	}
	else {
	    resc[i].tn.lval = freetemp((n & NTMASK) / NTEMP);
	}
	resc[i].in.name = "";
 
	resc[i].tn.lval = BITOOR(resc[i].tn.lval);
	++i;
    }
 
 /* turn off "temporarily busy" bit */
 
ok: 
    REGLOOP(j) {
	busy[j] &= ~TBUSY;
    }
 
    for (j = 0; j < i; ++j) {
	if (resc[j].tn.rval < 0) {
#ifndef BUG3
	    if(rdebug) {
		/* Print variables that affect allocation */
    		for (j = 0; j < i; ++j) {
			printf("checking resc[%d]: op=%d, rval=%d\n", 
				j, resc[j].in.op, resc[j].tn.rval);
		}
		prbusy();
		printf("mina = %d\n", mina);
		printf("maxa = %d\n", maxa);
		printf("minb = %d\n", minb);
		printf("maxb = %d\n", maxb);
		printf("maxtemp = %d\n", maxtemp);
		printf("tmpoff = %d\n", tmpoff);
		printf("baseoff = %d\n", baseoff);
		printf("maxtreg = %d\n", maxtreg);
		printf("allo fails\n");
	    }
#endif
	    return(0);
	}
    }
    return(1);
 
}
#endif
 
extern unsigned int     offsz;
freetemp(k)
{
/*
 * allocate k integers worth of temp space
 * we also make the convention that,
 * it must be aligned for storing doubles...
 */
 
#ifndef BACKTEMP
    int         t;
 
    if (k > 1) {
	SETOFF(tmpoff, ALDOUBLE);
    }
 
    t = tmpoff;
    tmpoff += k * SZINT;
    if (tmpoff > maxoff)
	maxoff = tmpoff;
    if (tmpoff >= offsz)
	cerror("stack overflow");
    if (tmpoff - baseoff > maxtemp)
	maxtemp = tmpoff - baseoff;
    return(t);
 
#else
    tmpoff += k * SZINT;
    if (k > 1) {
	SETOFF(tmpoff, ALDOUBLE);
    }
    if (tmpoff > maxoff)
	maxoff = tmpoff;
    if (tmpoff >= offsz)
	cerror("stack overflow");
    if (tmpoff - baseoff > maxtemp)
	maxtemp = tmpoff - baseoff;
    return(-tmpoff);
#endif
}
 
freereg(p, n) NODE *p;
{
 /* allocate a register of type n */
 /* p gives the type, if floating */
 
    register    j;
 
 /* not general; means that only one register (the result) OK for call */
    if (callop(p->in.op)) {
	j = callreg(p);
	if (usable(p, n, j))
	    return(j);
 /* have allocated callreg first */
    }
    j = p->in.rall & ~MUSTDO;
    if (j != NOPREF) {
	int tem = usable(p, n,j);
	 /* needed and not allocated */
	if(tem) 
	    return(j);
    }
    if (n & (NAMASK | NDMASK)) {
#ifdef FORT
retry:
#endif /* FORT */
	for (j = maxa; j >= mina; --j)
	    if (rstatus[j] & STAREG) {
		if (ISPTR(p->in.type) && j == R0 && !(p->in.rall & MUSTDO)) {
		    continue;
		}
		if (usable(p, n, j)) {
		    return(j);
		}
	    }
#ifdef FORT
	if ((p->in.type == DOUBLE || p->in.type == LONG || p->in.type == ULONG)
			&& tryregswap())		/* SPR86100175 */
	    goto retry;
#endif /* FORT */
    }
    else
	if (n & NBMASK) {
	    for (j = maxb; j >= minb; --j)
		if (rstatus[j] & STBREG) {
		    if (usable(p, n, j)) {
			return(j);
		    }
		}
	}
 
    return(-1);
}
 
#ifndef USABLE
usable(p, n, r) NODE   *p;
{
 /* decide if register r is usable in tree p to satisfy need n */
 
#ifndef BUG3
    if(rdebug) {
	printf("usable(0x%x, mask 0x%x, reg %d\n", p, n, r);
	fwalk(p, eprint, 0);
    } 
#endif
 
 /* checks, for the moment */
    if (!istreg(r))
	return(0);	/* "usable asked about nontemp register" */
 
    if (busy[r] > 1)
	return(0);
    if (isbreg(r)) {
	if (n & (NAMASK | NDMASK))
	    return(0);
    }
    else {
	if (n & NBMASK)
	    return(0);
    }
    if (!callop(p->in.op) && ISPTR(p->in.type) && 
	!(p->in.rall & MUSTDO && r == 0) &&
	(r == 0 || r == 8)) {
	return(0);
    }
    if ((n & NDMASK) || ((n & NAMASK) && (szty(p->in.type) == 2))) {
 /* only do the pairing for real regs */
	if (r & 1)
	    return(0);
	if (!istreg(r + 1))
	    return(0);
	if (busy[r + 1] > 1)
	    return(0);
	if (busy[r] == 0 && busy[r + 1] == 0 ||
		busy[r + 1] == 0 && shareit(p, r, n) ||
		busy[r] == 0 && shareit(p, r + 1, n)) {
	    busy[r] |= TBUSY;
	    busy[r + 1] |= TBUSY;
	    return(1);
	}
	else
	    return(0);
    }
    if (busy[r] == 0) {
	busy[r] |= TBUSY;
	return(1);
    }
 
 /* busy[r] is 1: is there chance for sharing */
    return(shareit(p, r, n));
 
}
#endif
 
shareit(p, r, n) NODE  *p;
{
 /* can we make register r available by sharing from p given that the need is n */
    if ((n & (NASL | NBSL)) && ushare(GETL(p), r))
	return(1);
    if ((n & (NASR | NBSR)) && ushare(GETR(p), r))
	return(1);
    return(0);
}
 
 /* old comment said: can we find a register r to share
    on the left or right (as f=='L' or 'R', respectively) of p NOW,
    p actually points to the node you want to share! DJK. */
static ushare(p, /* f, */ r) NODE  *p;
{
 /* p = getlr(p, f); */
    if (p->in.op == UNARY MUL)
	p = p->in.left;
    if (p->in.op == OREG) {
	if (R2TEST(p->tn.rval)) {
	    return(r == R2UPK1(p->tn.rval) || r == R2UPK2(p->tn.rval));
	}
	else
	    return(r == p->tn.rval);
    }
    if (p->in.op == REG) {
	return(r == p->tn.rval || (szty(p->in.type) == 2 && r == p->tn.rval + 1));
    }
    return(0);
}
 
recl2(p) register NODE *p;
{
    register    r = p->tn.rval;
    if (p->in.op == REG)
	rfree(r, p->in.type);
    else
	if (p->in.op == OREG) {
	    if (R2TEST(r)) {
		if (R2UPK1(r) != 100)
		    rfree(R2UPK1(r), PTR + INT);
		rfree(R2UPK2(r), INT);
	    }
	    else {
		rfree(r, PTR + INT);
	    }
	}
}
 
#ifndef BUG3
int         rdebug = 0;
#endif
 
#ifndef RFREE
rfree(r, t) TWORD   t;
{
 /* mark register r free, if it is legal to do so */
 /* t is the type */
 
#ifndef BUG3
    if (rdebug) {
	printf("rfree( %s ), size %d\n", rnames[r], szty(t));
    }
#endif
 
    if (istreg(r)) {
	if (--busy[r] < 0)
	    cerror("register overfreed");
	if (szty(t) == 2) {
	    if ((r & 1) || (istreg(r) ^ istreg(r + 1)))
		cerror("illegal free");
	    if (--busy[r + 1] < 0)
		cerror("register overfreed");
	}
    }
}
#endif
 
#ifndef RBUSY
rbusy(r, t) TWORD   t;
{
 /* mark register r busy */
 /* t is the type */
 
#ifndef BUG3
    if (rdebug) {
	printf("rbusy( %s ), size %d\n", rnames[r], szty(t));
    }
#endif
 
    if (istreg(r))
	++busy[r];
    if (szty(t) == 2) {
	if (istreg(r + 1))
	    ++busy[r + 1];
	if ((r & 1) || (istreg(r) ^ istreg(r + 1)))
	    cerror("illegal register pair freed");
    }
}
#endif
 
reclaim(p, rw, cookie) NODE    *p;
{
    register NODE **qq;
    register NODE  *q;
    register    i;
    NODE       *recres[5];
    struct respref *r;
 
 /* get back stuff */
 
#ifndef BUG3
    if (rdebug) {
	printf("reclaim( %x, ", p);
	print("result", rw);
	print("cookie", cookie);
	printf(" )\n");
	fwalk(p, eprint, 0);
	printf("reclaim(): busy[] = ");
	for(i=0; i<REGSZ; i++)
		printf(" %d", busy[i]);
	printf("\n");
    }
#endif
 
    if (rw == RNOP || (p->in.op == FREE && rw == RNULL))
	return;		/* do nothing */
 
    walkf(p, recl2);
 
    if (callop(p->in.op)) {
 /* check that all scratch regs are free */
	callchk(p);	/* ordinarily, this is the same as allchk() */
    }
 
 /* totally clobber, leaving nothing */
    if (rw == RNULL || (cookie & FOREFF)) {
	tfree(p);
	return;
    }
 
 /* handle condition codes specially */
 
    if ((cookie & (FORZCC | FORCC)) && (rw & RESCC)) {
 /* result is CC register */
	tfree(p);
	p->in.op = CCODES;
	p->tn.lval = 0;
	p->tn.rval = 0;
	return;
    }
 
 /* locate results */
 
    qq = recres;
 
    if (rw & RLEFT)
	*qq++ = GETL(p);
    if (rw & RRIGHT)
	*qq++ = GETR(p);
    if (rw & RESC1)
	*qq++ = &resc[0];
    if (rw & RESC2)
	*qq++ = &resc[1];
    if (rw & RESC3)
	*qq++ = &resc[2];
 
    if (qq == recres) {
	cerror("illegal reclaim");
    }
 
    *qq = NIL;
 
 /* now, select the best result, based on the cookie */
 
    for (r = respref; r->cform; ++r) {
	if (cookie & r->cform) {
	    for (qq = recres; (q = *qq) != NIL; ++qq) {
		if (r->mform & SANY || tshape(q, r->mform))
		    goto gotit;
	    }
	}
    }
 
 /* we can't do it; die */
    cerror("cannot reclaim");
 
gotit: 
 
    if (p->in.op == STARG) {
	if (q->in.op == OREG) {
	    NODE       *n;
	    n = talloc();
	    n->in.op = UNARY AND;
	    n->in.type = INCREF(p->in.type);
	    n->in.left = p->in.left;
	    p->in.left = n;
	    p = n->in.left;
	}
	else {
	    p = p->in.left;		/* STARGs are still STARGS */
	}
    }
 
    if (rw & RESUPPER) {
	p->in.type = INT;
	if (q->tn.rval & 1 || q->in.op != REG) {
	    cerror("allo: upper part of nonreg or odd reg");
	}
	q->tn.rval++;
    }
    if (rw & RESINT) {
	p->in.type = INT;
    }
 /* to make multi-register allocations work */
    q->in.type = p->in.type;
 /* maybe there is a better way! */
    q = tcopy(q);
 
    tfree(p);
 
    p->in.op = q->in.op;
    p->tn.lval = q->tn.lval;
    p->tn.rval = q->tn.rval;
    p->in.name = q->in.name;
#ifdef ONEPASS
    p->in.stalign = q->in.stalign;
#endif
 
    q->in.op = FREE;
 
 /* if the thing is in a register, adjust the type */
 
    switch (p->in.op) {
 
	case REG: 
	    if (!rtyflg) {
	/* the C language requires intermediate results to change type */
	/* this is inefficient or impossible on some machines */
	/* the "T" command in match supresses this type changing */
		if (p->in.type == CHAR || p->in.type == SHORT) {
		    p->in.type = INT;
		}
		else
		    if (p->in.type == UCHAR || p->in.type == USHORT)
			p->in.type = UNSIGNED;
	    }
	    else {
	/* 
	 * change sense of T when working with single precision
	 */
		if (p->in.type == FLOAT)
		    p->in.type = DOUBLE;
	    }
 
	    if (!(p->in.rall & MUSTDO))
		return;		/* unless necessary, ignore it */
	    i = p->in.rall & ~MUSTDO;
	    if (i & NOPREF)
		return;
	    if (i != p->tn.rval) {
		if (busy[i] || (szty(p->in.type) == 2 && busy[i + 1])) {
		    cerror("faulty register move");
		}
		rbusy(i, p->in.type);
		rfree(p->tn.rval, p->in.type);
		rmove(i, p->tn.rval, p->in.type);
		p->tn.rval = i;
	    }
 
	case OREG: 
	    if (p->in.op == REG || !R2TEST(p->tn.rval)) {
		if (busy[p->tn.rval] > 1 && istreg(p->tn.rval))
		    cerror("potential register overwrite");
	    }
	    else
		if ((R2UPK1(p->tn.rval) != 100 && 
		 busy[R2UPK1(p->tn.rval)] > 1 && istreg(R2UPK1(p->tn.rval)))
		 || (busy[R2UPK2(p->tn.rval)] > 1 && istreg(R2UPK2(p->tn.rval))))
		    cerror("potential register overwrite");
    }
 
}
 
 
#ifndef ncopy
ncopy(q, p) NODE   *p, *q;
{
 /* copy the contents of p into q, without any feeling for the contents */
 /* this code assume that copying rval and lval does the job; 
    in general, it might be necessary to special case the
    operator types */
    register    i;
 
    q->in.op = p->in.op;
    q->in.rall = p->in.rall;
    q->in.type = p->in.type;
    q->tn.lval = p->tn.lval;
    q->tn.rval = p->tn.rval;
    q->in.name = p->in.name;
#ifdef ONEPASS
    q->in.stalign = p->in.stalign;
#endif
 
}
#endif
 
NODE       *tcopy(p) NODE  *p;	/* TMK removed register on *p */
{
 /* make a fresh copy of p */
 
    register NODE  *q;
    register    r;
 
    ncopy(q = talloc(), p);
 
    r = p->tn.rval;
    if (p->in.op == REG)
	rbusy(r, p->in.type);
    else
	if (p->in.op == OREG) {
	    if (R2TEST(r)) {
		if (R2UPK1(r) != 100)
		    rbusy(R2UPK1(r), PTR + INT);
		rbusy(R2UPK2(r), INT);
	    }
	    else {
		rbusy(r, PTR + INT);
	    }
	}
 
    switch (optype(q->in.op)) {
 
	case BITYPE: 
	    q->in.right = tcopy(p->in.right);
	case UTYPE: 
	    q->in.left = tcopy(p->in.left);
    }
 
    return(q);
}
 
allchk()
{
 /* check to ensure that all register are free */
 
    register    i;
 
#ifndef BUG3
    if(rdebug) {
	printf("allchk():\n");
	prbusy();
    }
#endif
 
    REGLOOP(i) {
	if (istreg(i) && busy[i]) {
	    cerror("register allocation error");
	}
    }
}
 
/*
 * 	(c) Copyright 1986 Gould Inc.
 * 	    All Rights Reserved.
 */
