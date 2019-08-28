/* trees.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid =
"@(#) $Header: /bulk2/simhv/nbc-master/nbccom/RCS/trees.c,v 1.15 2019/01/31 22:03:56 jbev Exp jbev $";
#endif

/*
 * $Log: trees.c,v $
 * Revision 1.15  2019/01/31 22:03:56  jbev
 * Update for Linux
 *
 * Revision 1.14  1997/01/22 18:28:07  jbev
 * Correct pointer/integer problem with error messages.
 * Only on Alpha because of 64 bit pointers and 32 bit ints.
 *
 * Revision 1.13  1996/10/26 22:29:03  jbev
 * Fix for Alpha Port
 * l.
 *
 * Revision 1.12  1996/03/19 00:13:28  jbev
 * Mods for Alpha port.
 *
 * Revision 1.11  1996/03/18 23:55:06  jbev
 * Mods for Alpha port.
 *
 */

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

#include "mfile1.h"

/* some special actions, used in finding the type of nodes */
#define NCVT 1
#define PUN 2
#define TYPL 4
#define TYPR 8
#define TYMATCH 0x10
#define LVAL 0x40
#define CVTO 0x80
#define CVTL 0x100
#define CVTR 0x200
#define PTMATCH 0x400
#define OTHER 0x800
#define NCVTR 0x1000

/* node conventions:

	NAME:	rval>0 is stab index for external
		rval<0 is -inlabel number
		lval is offset in bits
	ICON:	lval has the value
		rval has the STAB index, or - label number,
			if a name whose address is in the constant
		rval = NONAME means no name
	REG:	rval is reg. identification cookie
	LNAME:  lval is offset
		rval is unique id number
	PNAME:	as for LNAME

*/

#ifndef BUG1
int         bdebug = 0;
extern      int ddebug;
#endif
extern	int      lastloc;

NODE       *buildtree(o, l, r) int o; register NODE   *l, *r;
{
    register NODE  *p, *q;
    register    int actions;
    register    int opty;
    register struct symtab *sp;
    register NODE  *lr, *ll;
    int         i;
#ifndef BUG1
    extern void eprint();
    extern int tdebug;
#endif

#ifndef BUG1
    if (bdebug) {
	printf(" BUILDTREE( %s, %x, %x )\n", opst[o], l, r);
	if(l)
		fwalk(l, eprint, 0);
	if(r)
		fwalk(r, eprint, 0);
    }
#endif
    opty = optype(o);

 /* check for constants */

    if (opty == UTYPE && l->in.op == ICON) {

	switch (o) {

	    case NOT: 
		if (hflag)
		    werror("constant argument to NOT");
	    case UNARY MINUS: 
	    case COMPL: 
		if (conval(l, o, l))
		    return(l);
		break;

	}
    }

    else
	if (o == UNARY MINUS && l->in.op == FCON) {
#ifdef MYATOF
	    FP_NEG(&l->fpn.fpnum);
#else
	    l->fpn.dval = FP_NEG(l->fpn.dval);
/*	    l->fpn.dval = -l->fpn.dval; */
#endif
	    return(l);
	}

	else
	    if (o == QUEST && l->in.op == ICON) {
		l->in.op = FREE;
		r->in.op = FREE;
		if (l->tn.lval) {
		    tfree(r->in.right);
		    return(r->in.left);
		}
		else {
		    tfree(r->in.left);
		    return(r->in.right);
		}
	    }

	    else
		if ((o == ANDAND || o == OROR) && (l->in.op == ICON || r->in.op == ICON))
		    goto ccwarn;

		else
		    if (opty == BITYPE && l->in.op == ICON && r->in.op == ICON) {

			switch (o) {

			    case ULT: 
			    case UGT: 
			    case ULE: 
			    case UGE: 
			    case LT: 
			    case GT: 
			    case LE: 
			    case GE: 
			    case EQ: 
			    case NE: 
			    case ANDAND: 
			    case OROR: 
			    case CBRANCH: 

			ccwarn: 
				if (hflag)
				    werror("constant in conditional context");

			    case PLUS: 
			    case MINUS: 
			    case MUL: 
			    case DIV: 
			    case MOD: 
			    case AND: 
			    case OR: 
			    case ER: 
			    case LS: 
			    case RS: 
				if (conval(l, o, r)) {
				    r->in.op = FREE;
				    return(l);
				}
				break;
			}
		    }

		    else
			if (opty == BITYPE && (l->in.op == FCON || l->in.op == ICON) &&
				(r->in.op == FCON || r->in.op == ICON)) {
			    switch (o) {
				case PLUS: 
				case MINUS: 
				case MUL: 
				case DIV: 
				    if (l->in.op == ICON) {
#ifdef MYATOF
					FP_LTOD(l->tn.lval, &l->fpn.fpnum);
#else
/*					l->fpn.dval = l->tn.lval; */
					l->fpn.dval = FP_LTOD(l->tn.lval);
#endif
				    }
				    if (r->in.op == ICON) {
#ifdef MYATOF
					FP_LTOD(r->tn.lval, &r->fpn.fpnum);
#else
/*					r->fpn.dval = r->tn.lval; */
					r->fpn.dval = FP_LTOD(r->tn.lval);
#endif
				    }
				    l->in.op = FCON;
				    l->in.type = l->fn.csiz = DOUBLE;
				    r->in.op = FREE;
				    switch (o) {
					case PLUS: 
#ifdef MYATOF
					    FP_PLUS(&l->fpn.fpnum, &r->fpn.fpnum);
#else
/*					    l->fpn.dval += r->fpn.dval; */
					    l->fpn.dval = FP_PLUS(l->fpn.dval, r->fpn.dval);
#endif
					    return(l);
					case MINUS: 
#ifdef MYATOF
					    FP_MINUS(&l->fpn.fpnum, &r->fpn.fpnum);
#else
/*					    l->fpn.dval -= r->fpn.dval; */
					    l->fpn.dval = FP_MINUS(l->fpn.dval, r->fpn.dval);
#endif
					    return(l);
					case MUL: 
#ifdef MYATOF
					    FP_TIMES(&l->fpn.fpnum, &r->fpn.fpnum);
#else
/*					    l->fpn.dval *= r->fpn.dval; */
					    l->fpn.dval = FP_TIMES(l->fpn.dval, r->fpn.dval);
#endif
					    return(l);
					case DIV: 
#ifdef MYATOF
					    if (FP_ISZERO(&r->fpn.fpnum))
						uerror("division by 0.");
					    else
					        FP_DIVIDE(&l->fpn.fpnum, &r->fpn.fpnum);
#else
/*					    if (r->fpn.dval == 0) */
					    if (FP_ISZERO(r->fpn.dval))
						uerror("division by 0.");
					    else
/*						l->fpn.dval /= r->fpn.dval; */
					        l->fpn.dval = FP_DIVIDE(l->fpn.dval, r->fpn.dval);
#endif
					    return(l);
				    }
			    }
			}

 /* its real; we must make a new node */

    p = block(o, l, r, INT, 0, INT);

    actions = opact(p);

    if (actions & LVAL) {		/* check left descendent */
	if (notlval(p->in.left)) {
	    uerror("illegal lhs of assignment operator");
	}
    }

    if (actions & NCVTR) {
	p->in.left = pconvert(p->in.left);
    }
    else
	if (!(actions & NCVT)) {
	    switch (opty) {

		case BITYPE: 
		    p->in.right = pconvert(p->in.right);
		case UTYPE: 
		    p->in.left = pconvert(p->in.left);

	    }
	}

    if ((actions & PUN) && (o != CAST || cflag)) {
	chkpun(p);
    }

    if (actions & (TYPL | TYPR)) {

	q = (actions & TYPL) ? p->in.left : p->in.right;

	p->in.type = q->in.type;
	p->fn.cdim = q->fn.cdim;
	p->fn.csiz = q->fn.csiz;
    }

    if (actions & CVTL)
	p = convert(p, CVTL);
    if (actions & CVTR)
	p = convert(p, CVTR);
    if (actions & TYMATCH)
	p = tymatch(p);
    if (actions & PTMATCH)
	p = ptmatch(p);

    if (actions & OTHER) {
	l = p->in.left;
	r = p->in.right;

	switch (o) {

	    case NAME: 
		sp = &stab[idname];

#ifndef BUG1
		if (tdebug) {
		    printf("buildtree(1): p->tn.rval=%x\n", p->tn.rval);
		    fwalk(p, eprint, 0);
		    if(p->tn.rval > 0)
			prstab(p->tn.rval);
		}
#endif

		if (sp->stype == UNDEF) {
    		    uerror("%s undefined", sp->sname); /* VOID 07/29/91 JCB */
		    /* make p look reasonable */
		    p->in.type = p->fn.cdim = p->fn.csiz = INT;
		    p->tn.rval = idname;
		    p->tn.lval = 0;
		    defid(p, SNULL);
#ifndef BUG1
		if (tdebug) {
		    printf("buildtree(1a): p->tn.rval=%x\n", p->tn.rval);
		    fwalk(p, eprint, 0);
		    if(p->tn.rval > 0)
			prstab(p->tn.rval);
		}
#endif
		    break;
		}

#ifndef BUG1
		if (tdebug) {
		    printf("buildtree(2): p->tn.rval=%x\n", p->tn.rval);
		    fwalk(p, eprint, 0);
		}
#endif

		p->in.type = sp->stype;
		p->fn.cdim = sp->dimoff;
		p->fn.csiz = sp->sizoff;
		p->tn.lval = 0;
		p->tn.rval = idname;

#ifndef BUG1
		if (tdebug) {
		    printf("buildtree(3): p->tn.rval=%x\n", p->tn.rval);
		    fwalk(p, eprint, 0);
		}
#endif

	/* special case: MOETY is really an ICON... */
		if (p->in.type == MOETY) {
		    p->tn.rval = NONAME;
		    p->tn.lval = sp->offset;
		    p->fn.cdim = 0;
		    p->in.type = ENUMTY;
		    p->in.op = ICON;
		}

#ifndef BUG1
		if (tdebug) {
		    printf("buildtree(4): p->tn.lval=%x\n", p->tn.lval);
		    fwalk(p, eprint, 0);
		}
#endif
		break;

	    case ICON: 
		p->in.type = INT;
		p->fn.cdim = 0;
		p->fn.csiz = INT;
		break;

	    case STRING: 
		p->in.op = NAME;
		if (onlyuchar) {
		    p->in.type = UCHAR + ARY;
		    p->fn.csiz = UCHAR;
		}
		else {
		    p->in.type = CHAR + ARY;
		    p->fn.csiz = CHAR;
		}
		p->tn.lval = 0;
		p->tn.rval = NOLAB;
		p->fn.cdim = curdim;

#ifndef BUG1
		if (tdebug) {
		    printf("after STRING: p->tn.lval = %x\n", p->tn.lval);
		    fwalk( p, eprint, 0);
		}
#endif
		break;

	    case FCON: 
		p->tn.lval = 0;
		p->tn.rval = 0;
#ifdef MYATOF
		zerof(&p->fpn.fpnum);
#endif
		p->in.type = DOUBLE;
		p->fn.cdim = 0;
		p->fn.csiz = DOUBLE;
#ifndef BUG1
		if (tdebug) {
		    printf("after FCON: p->tn.lval=%x\n", p->tn.lval);
		    printf("after FCON: p->tn.rval=%x\n", p->tn.rval);
		    fwalk(p, eprint, 0);
		}
#endif
		break;

	    case STREF: 
	/* p->x turned into *(p+offset) */
	/* rhs must be a name; check correctness */

#ifndef BUG1
		if(ddebug) {
			pr_strdim( l->fn.csiz );
		}
#endif

		i = r->tn.rval;
		if (i < 0 || ((sp = &stab[i])->sclass != MOS && 
		  sp->sclass != MOU && !(sp->sclass & FIELD))) {
		    uerror("member of structure or union required");
		}
		else	/* if this name is non-unique, find right one */
		    if (stab[i].sflags & SNONUNIQ &&
			(l->in.type == PTR + STRTY || l->in.type ==
			PTR + UNIONTY) && (l->fn.csiz + 1) >= 0) {
		/* nonunique name && structure defined */
			char       *memnam, *tabnam;
			register    int k;
			int         j;
			int         memi;
			j = dimtab[l->fn.csiz + 1];
			for (; (memi = dimtab[j]) >= 0; ++j) {
			    tabnam = stab[memi].sname;
			    memnam = stab[i].sname;
#ifndef BUG1
			    if (ddebug > 1) {
				printf("member %s==%s?\n", memnam, tabnam);
			    }
#endif
			    if (stab[memi].sflags & SNONUNIQ) {
				if (memnam != tabnam)
				    goto next;
				r->tn.rval = i = memi;
				break;
			    }
		    next:   continue;
			}
			if (memi < 0) {
			    uerror("illegal member use: %s", stab[i].sname);
			}
		    }
		    else {
			register    int j;
			if (l->in.type != PTR + STRTY && l->in.type != PTR + UNIONTY) {
			    if (stab[i].sflags & SNONUNIQ) {
				uerror("nonunique name demands struct/union or struct/union pointer");
			    }
			    else
				if( ISPTR(l->in.type))
			/* changed to uerror from werror DEC03,1990 */
					uerror("struct/union or struct/union pointer required");
				else
					uerror("struct/union or struct/union pointer required");
			}
			else
			    if ((j = l->fn.csiz + 1) < 0)
				cerror("undefined structure or union");
			    else
				if (!chkstr(i, dimtab[j], DECREF(l->in.type))) {
				    werror("illegal member use: %s", stab[i].sname);
				}
		    }

		p = stref(p);
		break;

	    case UNARY MUL: 
#ifndef BUG1
		if (tdebug) {
		    printf("begin UNARY MUL: p->tn.lval = %x\n", p->tn.lval);
		    printf("begin UNARY MUL: p->tn.rval = %x\n", p->tn.rval);
		    fwalk ( p, eprint, 0);
		}
#endif

		if (l->in.op == UNARY AND) {
		       /*
			*  SPR# 87001506, UPR# 10144 Indirection with Strings --
			*  Correction for *"string" constructs which removed
			*  indirection associated with the compiler generating
			*  an external name of #_name so that an address literal
			*  is actually generated.
			*
			*  Instead of using this code in all cases:
			*
			*     p->in.op = l->in.op = FREE;
			*     p = l->in.left;
			*/
		   q = l->in.left;
		   if ((l->in.type == PTR+CHAR
			|| l->in.type == PTR+UCHAR
			)
			&& q->in.op == NAME
			&& (q->in.type == CHAR || q->in.type == UCHAR)
			&& q->tn.rval < 0
		    ) {
		       q->in.op = ICON;
		       q->in.type += PTR;
		       l->in.op = FREE;
		       p->in.left = q;
		   }
		   else {
		       p->in.op = l->in.op = FREE;
		       p = l->in.left;
		   }
		}
		if (!ISPTR(l->in.type))
		    uerror("illegal indirection");
		p->in.type = DECREF(l->in.type);
		p->fn.cdim = l->fn.cdim;
		p->fn.csiz = l->fn.csiz;

#ifndef BUG1
		if (tdebug) {
		    printf("after UNARY MUL: p->tn.lval = %x\n", p->tn.lval);
		    fwalk ( p, eprint, 0);
		}
#endif
		break;

	    case UNARY AND: 
		switch (l->in.op) {

		    case UNARY MUL: 
			p->in.op = l->in.op = FREE;
			p = l->in.left;

		    case NAME: 
		    case LNAME:
		    case PNAME:
#ifndef BUG1
			if (tdebug) {
			   printf("buildtree(6,NAME): p->tn.lval = %x\n",p->tn.lval);
			   fwalk( p, eprint, 0);
			}
#endif
			p->in.type = INCREF(l->in.type);
			p->fn.cdim = l->fn.cdim;
			p->fn.csiz = l->fn.csiz;

#ifndef BUG1
			if (tdebug) {
			   printf("buildtree(6): p->tn.lval = %x\n",p->tn.lval);
			   fwalk( p, eprint, 0);
			}
#endif
			break;

		    case COMOP: 
			lr = buildtree(UNARY AND, l->in.right, NIL);
			p->in.op = l->in.op = FREE;
			p = buildtree(COMOP, l->in.left, lr);
			break;

		    case QUEST: 
			lr = buildtree(UNARY AND, l->in.right->in.right, NIL);
			ll = buildtree(UNARY AND, l->in.right->in.left, NIL);
			p->in.op = l->in.op = l->in.right->in.op = FREE;
			p = buildtree(QUEST, l->in.left, buildtree(COLON, ll, lr));
			break;

#ifdef ADDROREG
		    case OREG: 
		/* 
		 * OREG was built in clocal()
		 * for an auto or formal parameter
		 * now its address is being taken
		 * local code must unwind it
		 * back to PLUS/MINUS REG ICON
		 * according to local conventions
		 */
			{
			    extern NODE    *addroreg();
			    p->in.op = FREE;
			    p = addroreg(l);
			}
			break;

#else
		    case OREG: 
			p->in.type = INCREF(l->in.type);
			p->fn.cdim = l->fn.cdim;
			p->fn.csiz = l->fn.csiz;
#ifndef BUG1
	if(tdebug)
		printf("from OREG in buildtree\n");
#endif
			break;
#endif

		    default: 
			uerror("unacceptable operand of &");
			break;
		}
		break;

	    case LS: 
	    case RS: 
	    case ASG LS: 
	    case ASG RS: 
		if (tsize(p->in.right->in.type, p->in.right->fn.cdim,
		 p->in.right->fn.csiz) > SZINT)
		    p->in.right = makety(p->in.right, INT, 0, INT);
		break;

	    case RETURN: 
	    case ASSIGN: 
	    case CAST: 
	/* structure assignment */
	/* 
	 * take the addresses of the two sides; then make an 
	 * operator using STASG and 
	 * the addresses of left and right
	 */
		{
		    register TWORD  t;
		    register    int d, s;

		    if (l->fn.csiz != r->fn.csiz)
			uerror("assignment of different structures");

#ifndef BUG1
    if (tdebug) {
        printf("buildtree(66): in ASSIGN\n");
        fwalk( p, eprint, 0);
    }
#endif
		    r = buildtree(UNARY AND, r, NIL);
		    t = r->in.type;
		    d = r->fn.cdim;
		    s = r->fn.csiz;

		    l = block(STASG, l, r, t, d, s);

		    if (o == RETURN) {
			p->in.op = FREE;
			p = l;
			break;
		    }

		    p->in.op = UNARY MUL;
		    p->in.left = l;
		    p->in.right = NIL;
#ifndef BUG1
    if (tdebug) {
        printf("buildtree(66): after ASSIGN\n");
        fwalk( p, eprint, 0);
    }
#endif
		    break;
		}
	    case COLON: 
	/* structure colon */

		if (l->fn.csiz != r->fn.csiz)
		    uerror("type clash in conditional");
		break;

	    case CALL: 
		p->in.right = r = strargs(p->in.right);
	    case UNARY CALL: 
		if (!ISPTR(l->in.type))
		    uerror("illegal function");
		p->in.type = DECREF(l->in.type);
		if (!ISFTN(p->in.type))
		    uerror("illegal function");
		p->in.type = DECREF(p->in.type);
		p->fn.cdim = l->fn.cdim;
		p->fn.csiz = l->fn.csiz;
		if (l->in.op == UNARY AND && l->in.left->in.op == NAME &&
			l->in.left->tn.rval >= 0 && l->in.left->tn.rval != NONAME &&
			((i = stab[l->in.left->tn.rval].sclass) == FORTRAN || i == UFORTRAN)) {
		    p->in.op += (FORTCALL - CALL);
		}
		if (p->in.type == STRTY || p->in.type == UNIONTY) {
	    /* function returning structure */
	    /*  make function really return ptr to str., with * */

		    p->in.op += STCALL - CALL;
		    p->in.type = INCREF(p->in.type);
		    p = buildtree(UNARY MUL, p, NIL);

		}
		break;

	    default: 
		cderror("other code %d", o);
	}

    }

#ifndef BUG1
    if (tdebug) {
        printf("buildtree(): after big switch [%x]\n", actions);
        fwalk( p, eprint, 0);
    }
#endif

    if (actions & CVTO)
	p = oconvert(p);
    p = clocal(p);

#ifndef BUG1
    if (tdebug) {
        printf("buildtree(7): p->tn.lval = %x\n",p->tn.lval);
        printf("buildtree(7): p->tn.rval = %x\n",p->tn.rval);
        fwalk( p, eprint, 0);
    }
#endif

    return(p);

}

NODE       *strargs(p) register NODE   *p;
{		/* rewrite structure flavored arguments */

    if (p->in.op == CM) {
	p->in.left = strargs(p->in.left);
	p->in.right = strargs(p->in.right);
	return(p);
    }

    if (p->in.type == STRTY || p->in.type == UNIONTY) {
	p = block(STARG, p, NIL, p->in.type, p->fn.cdim, p->fn.csiz);
	p->in.left = buildtree(UNARY AND, p->in.left, NIL);
	p = clocal(p);
    }
    return(p);
}

int chkstr(i, j, type) int i, j; TWORD    type;
{
 /* is the MOS or MOU at stab[i] OK for strict reference by a ptr */
 /* i has been checked to contain a MOS or MOU */
 /* j is the index in dimtab of the members... */
    int         k, kk;

#ifndef BUG1
    extern int  ddebug;
#endif

#ifndef BUG1
    if (ddebug > 1)
	printf("chkstr( %s(%d), %d )\n", stab[i].sname, i, j);
#endif
    if ((k = j) < 0)
	uerror("undefined structure or union");
    else {
	for (; (kk = dimtab[k]) >= 0; ++k) {
#ifndef BUG1
	    if(ddebug > 1) {
		printf("dimtab[%d]: %d\n", k, kk);
	    }
#endif
	    if (kk >= SYMTSZ) {
		cerror("gummy structure");
		return(1);
	    }
	    if (kk == i)
		return(1);
	    switch (stab[kk].stype) {

		case STRTY: 
		case UNIONTY: 
		    if (type == STRTY)
			continue;	/* no recursive looking for strs */
		    if (hflag && chkstr(i, dimtab[stab[kk].sizoff + 1], stab[kk].stype)) {
			if (stab[kk].sname[0] == '$')
			    return(0);		/* $FAKE */
			werror(
				"illegal member use: perhaps %s.%s?",
				stab[kk].sname, stab[i].sname);
			return(1);
		    }
	    }
	}
    }
    return(0);
}

int conval(p, o, q) register NODE  *p, *q; int o;
{
 /* apply the op o to the lval part of p; if binary, rhs is val */
    int         i, u;
    CONSZ       val;

#ifndef BUG1
    if (tdebug) {
        printf("conval(0): p->tn.lval = %x, q->tn.lval = %x, op = %s\n",
		p->tn.lval, q->tn.lval, opst[o]);
        fwalk( p, eprint, 0);
    }
#endif

    val = q->tn.lval;
    u = ISUNSIGNED(p->in.type) || ISUNSIGNED(q->in.type);
    if (u && (o == LE || o == LT || o == GE || o == GT))
	o += (UGE - GE);

    if (p->tn.rval != NONAME && q->tn.rval != NONAME)
	return(0);
    if (q->tn.rval != NONAME && o != PLUS)
	return(0);
    /* this stops extern - displacement */
    if (p->tn.rval != NONAME && o != PLUS)
	return(0);

    switch (o) {

	case PLUS: 
	    p->tn.lval += val;
	    if (p->tn.rval == NONAME) {
		p->tn.rval = q->tn.rval;
		p->in.type = q->in.type;
	    }
	    break;
	case MINUS: 
	    p->tn.lval -= val;
	    break;
	case MUL: 
	    p->tn.lval *= val;
	    break;

	/*	This section replaced with Sun code, for t3.c */
	case DIV:
		if( val == 0 )
			uerror( "division by 0" );
		else if (u)
			p->tn.lval /= (unsigned)val;
		else
			p->tn.lval /= val;
		break;
	case MOD:
		if( val == 0 )
			uerror( "division by 0" );
		else if (u)
			p->tn.lval %= (unsigned)val;
		else
			p->tn.lval %= val;
		break;
	case AND:
		p->tn.lval &= val;
		break;
	case OR:
		p->tn.lval |= val;
		break;
	case ER:
		p->tn.lval ^=  val;
		break;
	case LS:
	    i = val;
	    if (i < 32) {
		if (u)
			p->tn.lval = (unsigned)p->tn.lval << i;
		else
			p->tn.lval = p->tn.lval << i;
	    }
	    else {
		p->tn.lval = 0;
	    }
	    break;

	case RS:
		i = val;
		if (u)
			p->tn.lval = (unsigned)p->tn.lval >> i;
		else
			p->tn.lval = p->tn.lval >> i;
		break;
	/*  END of Sun code for t3.c */

	case UNARY MINUS: 
	    p->tn.lval = -p->tn.lval;
	    break;
	case COMPL: 
	    p->tn.lval = ~p->tn.lval;
	    break;
	case NOT: 
	    p->tn.lval = !p->tn.lval;
	    break;
	case LT: 
	    p->tn.lval = p->tn.lval < val;
	    break;
	case LE: 
	    p->tn.lval = p->tn.lval <= val;
	    break;
	case GT: 
	    p->tn.lval = p->tn.lval > val;
	    break;
	case GE: 
	    p->tn.lval = p->tn.lval >= val;
	    break;
     case ULT: 
     p->tn.lval = (p->tn.lval - val) < 0;
     break;
     case ULE: 
     p->tn.lval = (p->tn.lval - val) <= 0;
     break;
     case UGE: 
     p->tn.lval = (p->tn.lval - val) >= 0;
     break;
     case UGT: 
     p->tn.lval = (p->tn.lval - val) > 0;
     break;
	case EQ: 
	    p->tn.lval = p->tn.lval == val;
	    break;
	case NE: 
	    p->tn.lval = p->tn.lval != val;
	    break;
	default: 
	    return(0);
    }
    return(1);
}

void chkpun(p) register NODE    *p;
{

/* checks p for the existance of a pun */

/* this is called when the op of p is ASSIGN, RETURN, CAST, COLON, or relational */

/* one case is when enumerations are used: this applies only to lint */
/* in the other case, one operand is a pointer, the other integer type */
/* we check that this integer is in fact a constant zero... */

/* in the case of ASSIGN, any assignment of pointer to integer is illegal */
/* this falls out, because the LHS is never 0 */

    register NODE  *q;
    register    int t1, t2;
    register    int d1, d2;

    t1 = p->in.left->in.type;
    t2 = p->in.right->in.type;

    if (t1 == ENUMTY || t2 == ENUMTY) {		/* check for enumerations */
	if (t1 == ENUMTY && t2 == ENUMTY)
	    if(p->in.left->fn.csiz == p->in.right->fn.csiz)
		return;
	    else
	    {
		werror("operands are from different enumerations, operator %s", opst[p->in.op]);
		return;
	    }
	else
	    if (t1 == INT || t2 == INT)
		return;
#ifndef FIX_041195
	    /* if pointer to something, no warning message */
	    if (p->in.left->in.op == UNARY MUL)
		return;
#endif
	    else
	    {
		werror("enumeration type clash, operator %s", opst[p->in.op]);
		return;
	    }
    }

    if (ISPTR(t1) || ISARY(t1))
	q = p->in.right;
    else
	q = p->in.left;

    if (!ISPTR(q->in.type) && !ISARY(q->in.type)) {
	if (q->in.op != ICON || q->tn.lval != 0) {
	    werror("illegal combination of pointer and integer, op %s",
		    opst[p->in.op]);
	}
    }
    else {
	d1 = p->in.left->fn.cdim;
	d2 = p->in.right->fn.cdim;
	for (;;) {
	    if (t1 == t2) {;
		if (p->in.left->fn.csiz != p->in.right->fn.csiz) {
		    werror("illegal structure pointer combination");
		}
		return;
	    }
	    if (ISARY(t1) || ISPTR(t1)) {
		if (!ISARY(t2) && !ISPTR(t2))
		    break;
		if (ISARY(t1) && ISARY(t2) && dimtab[d1] != dimtab[d2]) {
		    werror("illegal array size combination");
		    return;
		}
		if (ISARY(t1))
		    ++d1;
		if (ISARY(t2))
		    ++d2;
	    }
	    else
		break;
	    t1 = DECREF(t1);
	    t2 = DECREF(t2);
	}

	/* suppress warning for assignment of string constant to uchar */
	if(t1 == UCHAR && t2 == CHAR)
		if(isstrcon(p->in.right))
			return;
	werror("illegal pointer combination");
    }

}

/*
 *	Return 1 if its a string constant, zero otherwise.
 */
int isstrcon(p)
NODE *p;
{
	register NODE *q = p;

	switch(p->in.op) {
	case UNARY AND:
		q = p->in.left;
		if(q->in.type == CHAR && q->tn.rval < 0)
			return(1);
		break;
	case NAME:
		if(q->in.type == PTR+CHAR && q->tn.rval < 0)
			return(1);
		break;
	default:
		break;
	}

	return(0);
}

NODE       *stref(p) register NODE *p;
{

    TWORD       t;
    int         d, s, dsc, align;
    OFFSZ       off;
    register struct symtab *q;

 /* make p->x */
 /* this is also used to reference automatic variables */

#ifndef BUG1
    if(tdebug) {
	printf("stref(%x):\n", p);
	fwalk(p, eprint, 0);
    }
#endif

    q = &stab[p->in.right->tn.rval];
    p->in.right->in.op = FREE;
    p->in.op = FREE;
    p = pconvert(p->in.left);

 /* make p look like ptr to x */

    if (!ISPTR(p->in.type)) {
	p->in.type = PTR + UNIONTY;
    }

    t = INCREF(q->stype);
    d = q->dimoff;
    s = q->sizoff;

    p = makety(p, t, d, s);

 /* compute the offset to be added */

    off = q->offset;
    dsc = q->sclass;

    if (dsc & FIELD) {			/* normalize offset */
	align = ALINT;
	s = INT;
	off = (off / align) *align;
    }
    if (off != 0)
	p = clocal(block(PLUS, p, offcon(off, t, d, s), t, d, s));

    p = buildtree(UNARY MUL, p, NIL);

 /* if field, build field info */

    if (dsc & FIELD) {
	p = block(FLD, p, NIL, q->stype, 0, q->sizoff);
	p->tn.rval = PKFIELD(dsc & FLDSIZ, q->offset % align);
    }

    return(clocal(p));
}

int notlval(p) register NODE   *p;
{

 /* return 0 if p an lvalue, 1 otherwise */

again: 

    switch (p->in.op) {

	case FLD: 
	    p = p->in.left;
	    goto again;

	case UNARY MUL: 
    /* fix the &(a=b) bug, given that a and b are structures */
	    if (p->in.left->in.op == STASG)
		return(1);
    /* and the f().a bug, given that f returns a structure */
	    if (p->in.left->in.op == UNARY STCALL ||
		    p->in.left->in.op == STCALL)
		return(1);
	case NAME: 
	case LNAME:
	case PNAME:
	case OREG: 
	    if (ISARY(p->in.type) || ISFTN(p->in.type))
		return(1);
	case REG: 
	    return(0);

	default: 
	    return(1);

    }

}

NODE       *bcon(i)
int i;
{				/* make a constant node with value i */
    register NODE  *p;

#ifndef BUG1
    if(ddebug) {
	printf("bcon(i=0x%x):\n", i);
    }
#endif
    p = block(ICON, NIL, NIL, INT, 0, INT);
    p->tn.lval = i;
    p->tn.rval = NONAME;
    p = clocal(p);
#ifndef BUG1
    if(ddebug) {
	printf("bcon() returning %x\n", p);
	fwalk(p, eprint, 0);
    }
#endif
    return(p);
}

NODE       *bpsize(p) register NODE    *p;
{
    return(offcon(psize(p), p->in.type, p->fn.cdim, p->fn.csiz));
}

OFFSZ psize(p) NODE  *p;
{
 /* p is a node of type pointer; psize returns the size of the thing pointed to */

    if (!ISPTR(p->in.type)) {
	uerror("pointer required");
	return(SZINT);
    }
 /* note: no pointers to fields */
    return(tsize(DECREF(p->in.type), p->fn.cdim, p->fn.csiz));
}

NODE       *convert(p, f) register NODE    *p; int f;
{
 /*  convert an operand of p f is either CVTL or CVTR operand has type int, and is converted by the size of the other
    side */

    register NODE  *q, *r;

#ifndef BUG1
    if (tdebug) {
        printf("convert(0): p->tn.lval = %x, q->tn.lval = %x, op = %s\n",
		p->tn.lval, q->tn.lval, opst[p->in.op]);
        fwalk( p, eprint, 0);
    }
#endif
    q = (f == CVTL) ? p->in.left : p->in.right;

    r = block(PMCONV,
	    q, bpsize(f == CVTL ? p->in.right : p->in.left), INT, 0, INT);
    r = clocal(r);
    if (f == CVTL)
	p->in.left = r;
    else
	p->in.right = r;
#ifndef BUG1
    if (tdebug) {
        printf("oconvert(1): p->tn.lval = %x, q->tn.lval = %x, op = %s\n",
		p->tn.lval, q->tn.lval, opst[p->in.op]);
        fwalk( p, eprint, 0);
    }
#endif
    return(p);

}

void econvert(p) register NODE  *p;
{

 /* change enums to ints, or appropriate types */

    register TWORD  ty;

    if ((ty = BTYPE(p->in.type)) == ENUMTY || ty == MOETY) {
	if (dimtab[p->fn.csiz] == SZCHAR)
	    ty = CHAR;
	else
	    if (dimtab[p->fn.csiz] == SZINT)
		ty = INT;
	    else
		if (dimtab[p->fn.csiz] == SZSHORT)
		    ty = SHORT;
		else
		    ty = LONG;
	ty = ctype(ty);
	p->fn.csiz = ty;
	MODTYPE(p->in.type, ty);
if (p->in.op == ICON /*&& ty != LONG  DJK KLUDGE TO KILL LONG CONST */ )
	    p->in.type = p->fn.csiz = INT;
    }
}

NODE       *pconvert(p) register NODE  *p;
{

 /* if p should be changed into a pointer, do so */

    if (ISARY(p->in.type)) {
	p->in.type = DECREF(p->in.type);
	++p->fn.cdim;
	return(buildtree(UNARY AND, p, NIL));
    }
    if (ISFTN(p->in.type))
	return(buildtree(UNARY AND, p, NIL));

    return(p);
}

NODE       *oconvert(p) register NODE  *p;
{
 /* convert the result itself: used for pointer and unsigned */

    int         ru, lu;

#ifndef BUG1
    if(tdebug) {
	printf("oconvert(%x): op = %s\n", p, opst[p->in.op]);
	fwalk(p, eprint, 0);
    }
#endif

    switch (p->in.op) {

	case LE: 
	case LT: 
	case GE: 
	case GT: 
	    if (p->in.left->in.type == UNSIGNED
		    || p->in.right->in.type == UNSIGNED) {
		p->in.left = makety(p->in.left, LONG, 0, LONG);
		p->in.right = makety(p->in.right, LONG, 0, LONG);
	    }
	    return(p);
    /* 
     * equality comparison of two unsigneds is ok
     */
	case EQ: 
	case NE: 
	    ru = ISUNSIGNED(p->in.right->in.type);
	    lu = ISUNSIGNED(p->in.left->in.type);
    /* 
     * check for a constant which would be unsigned anyway
     */
	    if (lu) {
		if (!ru) {
		    if (p->in.right->in.op == ICON) {
			if (p->in.right->tn.rval == NONAME 
	&&
	!( ((unsigned)p->in.right->tn.lval >> (SZINT-1)) & 1)
	) {
			    p->in.right->in.type = UNSIGNED;
			    ru = 1;
			}
		    }
		}
	    }

	    if ((ru || lu) && ru != lu)
	    {
		p->in.left = makety(p->in.left, UNSIGNED, 0, UNSIGNED);
		p->in.right = makety(p->in.right, UNSIGNED, 0, UNSIGNED);
	    }
	    return(p);

	case MINUS: 
	    return(clocal(block(PVCONV,
			    p, bpsize(p->in.left), INT, 0, INT)));
    }

    cderror("illegal oconvert: %d", p->in.op);

    return(p);
}

NODE       *ptmatch(p) register NODE   *p;
{

 /* makes the operands of p agree; they are either pointers or integers, by this time */
 /* with MINUS, the sizes must be the same */
 /* with COLON, the types must be the same */

    TWORD       t1, t2, t;
    int         o, d2, d, s2, s;

    o = p->in.op;
    t = t1 = p->in.left->in.type;
    t2 = p->in.right->in.type;
    d = p->in.left->fn.cdim;
    d2 = p->in.right->fn.cdim;
    s = p->in.left->fn.csiz;
    s2 = p->in.right->fn.csiz;

    switch (o) {

	case ASSIGN: 
	case RETURN: 
	case CAST: 
	    {
		break;
	    }

	case MINUS: 
	    {
		if (psize(p->in.left) != psize(p->in.right)) {
		    uerror("illegal pointer subtraction");
		}
		break;
	    }
	case COLON: 
	    {
		if (t1 != t2)
		    uerror("illegal types in :");
		break;
	    }
	default: 	/* must work harder: relationals or comparisons */

	    if (!ISPTR(t1)) {
		t = t2;
		d = d2;
		s = s2;
		break;
	    }
	    if (!ISPTR(t2)) {
		break;
	    }

    /* both are pointers */
	    if (talign(t2, s2) < talign(t, s)) {
		t = t2;
		s = s2;
	    }
	    break;
    }

    p->in.left = makety(p->in.left, t, d, s);
    p->in.right = makety(p->in.right, t, d, s);
    if (o != MINUS && !logop(o)) {

	p->in.type = t;
	p->fn.cdim = d;
	p->fn.csiz = s;
    }

    return(clocal(p));
}

#ifndef BUG1
int         tdebug = 0;
#endif

NODE       *tymatch(p) register NODE   *p;
{

 /* satisfy the types of various arithmetic binary ops */

 /* 
  * rules are:
  * 	if assignment, op, type of LHS if any float or doubles,
  *  make double if any longs, make long otherwise,
  *  make int if either operand is unsigned, the result is...
  */

    register TWORD  t1, t2, t, tu;
    register    int o, u;
 /* 
  * UTX/32 1.2 fix for unsigned vs. negative compares
  */
    NODE  *pl, *pr;

    o = p->in.op;
 /*
  * UTX/32 1.2 fix for unsigned vs. negative compares
  */
    pl = p->in.left;
    pr = p->in.right;

    t1 = p->in.left->in.type;
    t2 = p->in.right->in.type;
    if ((t1 == UNDEF || t2 == UNDEF) && o != CAST)
	uerror("void type illegal in expression");

/*
 *  UTX/32 1.2 fix for warning on unsigned vs.     
 *  negative compares
 *
 */
    if (logop(o) && optype(o) == BITYPE ){
	if(ISUNSIGNED(t1) && !ISUNSIGNED(t2)) {
		if(pr->in.op == ICON  && pr->tn.lval < 0  )
			werror("unsigned compared to negative number");
	}
	if(ISUNSIGNED(t2) && !ISUNSIGNED(t1)) {
		if(pl->in.op == ICON && pl->tn.lval < 0)
			werror("negative number compared to unsigned");
	}
    }
    u = 0;
    if (ISUNSIGNED(t1)) {
	u = 1;
	t1 = DEUNSIGN(t1);
    }
    if (ISUNSIGNED(t2)) {
	u = 1;
	t2 = DEUNSIGN(t2);
    }

    if ((t1 == CHAR || t1 == SHORT) && o != RETURN)
	t1 = INT;
    if (t2 == CHAR || t2 == SHORT)
	t2 = INT;

    if (t1 == FLOAT && t2 == FLOAT) {
	t = FLOAT;
    }
    else {
	if (t1 == DOUBLE || t1 == FLOAT || t2 == DOUBLE || t2 == FLOAT)
	    t = DOUBLE;
	else
	    if (t1 == LONG || t2 == LONG)
		t = LONG;
	    else
		t = INT;
    }

#define WantBrokenAsops 1
    if (asgop(o)) {
#ifndef WantBrokenAsops
 /* 
  * attempt to deal with int op= float;  is made difficult
  * by places where 'int' has side effects like
  * The assembler has a bug where mulw rx,ry gets turned into
  * mprfw instr instead of doing integer multiply as expected.
  *
  *       *ip++ *= floatingvar;
  *
  *   guess i would have to take of two cases
  *	simp is any expression that easily doesn't have side effects
  
  *    simp *= float->  simp = simp * float;
  *    anyelse *= float-> *ptr = *(ptr = &anyelse) * float;
  *
  */
	if (o != RETURN && o != CAST && o != ASSIGN && t1 == INT && t == DOUBLE) {
	    NODE       *ptr = talloc();

	    if (p->in.left->in.op == OREG
		    || p->in.left->in.op == REG
		    || p->in.left->in.op == NAME) {

		*ptr = *(p->in.left);
		p->in.op = NOASG o;
		p->in.type = p->in.right->in.type;
		return tymatch(block(ASSIGN, ptr, tymatch(p), t1, 0, t1));
	    }
	    else {
		NODE       *p2, *l = p->in.left;
		ptr->in.op = OREG;
		ptr->in.type = INCREF(t1);
		ptr->tn.rval = STKREG;
		/* BUG  in statement below. Cant use autooff here, as */
		/* it has already been used to establish offset for temps */
		/* in back end.  */
		ptr->tn.lval = upoff(SZPOINT, ALPOINT, &autooff)/SZCHAR;
		p2 = talloc(), *p2 = *ptr;

		if (l->in.op == UNARY MUL) {
		    l->in.op = FREE;
		    l = l->in.left;
		}
		else {
		    l = block(UNARY AND, l, 0, INCREF(t1), 0, INT);
		}
		l = block(ASSIGN, p2, l, INCREF(t1), 0, INT);

		p->in.op = NOASG o;
		p->in.left = block(UNARY MUL, l, 0, t1, 0, t1);

		return(tymatch(block(
				ASSIGN,
				block(UNARY MUL, ptr, 0, t1, 0, INT),
				tymatch(p),
				t1,
				0,
				INT)));
	    }
	}
#endif
	tu = p->in.left->in.type;
	t = t1;
    }
    else {
	tu = (u && UNSIGNABLE(t)) ? ENUNSIGN(t) : t;
    }

 /* because expressions have values that are at least as wide as INT or UNSIGNED, the only conversions needed are those
    involving FLOAT/DOUBLE, and those from LONG to INT and ULONG to UNSIGNED */

    if (t != t1)
	p->in.left = makety(p->in.left, tu, 0, (int) tu);

    if (t != t2 || o == CAST)
	p->in.right = makety(p->in.right, tu, 0, (int) tu);

    if (asgop(o)) {
	p->in.type = p->in.left->in.type;
	p->fn.cdim = p->in.left->fn.cdim;
	p->fn.csiz = p->in.left->fn.csiz;
    }
    else
	if (!logop(o)) {
	    p->in.type = tu;
	    p->fn.cdim = 0;
	    p->fn.csiz = t;
	}

#ifndef BUG1
    if (tdebug) {
	printf("tymatch(%x): ", p);
	tprint(t1);
	printf(" %s ", opst[o]);
	tprint(t2);
	printf(" => ");
	tprint(tu);
	printf("\n");
    }
#endif

    return(p);
}

NODE       *makety(p, t, d, s) register NODE   *p;
int         d, s;
TWORD       t;
{
 /* make p into type t by inserting a conversion */

    char nn[32];
    int ttval;
    if (p->in.type == ENUMTY && p->in.op == ICON)
	econvert(p);
    if (t == p->in.type) {
	p->fn.cdim = d;
	p->fn.csiz = s;
	return(p);
    }

    if (t & TMASK) {
 /* non-simple type */
	return(block(PCONV, p, NIL, t, d, s));
    }

    if (p->in.op == ICON) {
	if (t == DOUBLE || t == FLOAT) {
	    p->in.op = FCON;
	    if (ISUNSIGNED(p->in.type)) {
#ifdef MYATOF
		/* convert unsigned integer to double */
		FP_ULTOD((unsigned long)p->tn.lval, &p->fpn.fpnum);
#else
/*		p->fpn.dval = *//* (unsigned CONSZ) *//* p->tn.lval; */
		p->fpn.dval = FP_ULTOD((unsigned long)p->tn.lval);
#endif
	    } else {
#ifdef MYATOF
		/* convert integer to double */
		FP_LTOD((unsigned long)p->tn.lval, &p->fpn.fpnum);
#else
/*		p->fpn.dval = p->tn.lval; */
		p->fpn.dval = FP_LTOD(p->tn.lval);
#endif
	    }

	    p->in.type = p->fn.csiz = t;
	    return(clocal(p));
	}
    }

    /* Sun fix for $w/sunfixes/t4.c - added clocal() call to return */
    return( clocal( block( SCONV, p, NIL, t, d, s ) ) );

}

NODE       *block(o, l, r, t, d, s) register NODE  *l, *r;
int         o, d, s;
TWORD       t;
{

    register NODE  *p;

    p = talloc();
    p->in.op = o;
    p->in.left = l;
    p->in.right = r;
    p->in.type = t;
    p->fn.cdim = d;
    p->fn.csiz = s;
    return(p);
}

int icons(p) register NODE *p;
{
 /* if p is an integer constant, return its value */
    int         val;

    if (p->in.op != ICON) {
	uerror("constant expected");
	val = 1;
    }
    else {
	val = p->tn.lval;
	if (val != p->tn.lval)
	    uerror("constant too big for cross-compiler");
    }
    tfree(p);
    return(val);
}

/* 	the intent of this table is to examine the
	operators, and to check them for
	correctness.

	The table is searched for the op and the
	modified type (where this is one of the
	types INT (includes char and short), LONG,
	DOUBLE (includes FLOAT), and POINTER

	The default action is to make the node type integer

	The actions taken include:
		PUN	  check for puns
		CVTL	  convert the left operand
		CVTR	  convert the right operand
		TYPL	  the type is determined by the left operand
		TYPR	  the type is determined by the right operand
		TYMATCH	  force type of left and right to match, by inserting conversions
		PTMATCH	  like TYMATCH, but for pointers
		LVAL	  left operand must be lval
		CVTO	  convert the op
		NCVT	  do not convert the operands
		OTHER	  handled by code
		NCVTR	  convert the left operand, not the right...
	*/

#define MINT 1		/* integer */
#define MDBI 2		/* integer or double */
#define MSTR 4		/* structure */
#define MPTR 8		/* pointer */
#define MPTI 0x10	/* pointer or integer */
#define MENU 0x20	/* enumeration variable or member */

int opact(p) NODE  *p;
{

    register    int mt12, mt1, mt2, o;

    mt12 = 0;

    switch (optype(o = p->in.op)) {

	case BITYPE: 
	    mt12 = mt2 = moditype(p->in.right->in.type);
	case UTYPE: 
	    mt12 &= (mt1 = moditype(p->in.left->in.type));

    }

    switch (o) {

	case NAME: 
	case STRING: 
	case ICON: 
	case FCON: 
	case CALL: 
	case UNARY CALL: 
	case UNARY MUL: 
	    {
		return(OTHER);
	    }
	case UNARY MINUS: 
	    if (mt1 & MDBI)
		return(TYPL);
	    break;

	case COMPL: 
	    if (mt1 & MINT)
		return(TYPL);
	    break;

	case UNARY AND: 
	    {
		return(NCVT + OTHER);
	    }
	case INIT: 
	case CM: 
	case NOT: 
	case CBRANCH: 
	case ANDAND: 
	case OROR: 
	    return(0);

	case MUL: 
	case DIV: 
	    if (mt12 & MDBI)
		return(TYMATCH);
	    break;

	case MOD: 
	case AND: 
	case OR: 
	case ER: 
	    if (mt12 & MINT)
		return(TYMATCH);
	    break;

	case LS: 
	case RS: 
	    if (mt12 & MINT)
		return(TYMATCH + OTHER);
	    break;

	case EQ: 
	case NE: 
	case LT: 
	case LE: 
	case GT: 
	case GE: 
	    if ((mt1 & MENU) || (mt2 & MENU))
		return(PTMATCH + PUN + NCVT);
	    if (mt12 & MDBI)
		return(TYMATCH + CVTO);
	    else
		if (mt12 & MPTR)
		    return(PTMATCH + PUN);
		else
		    if (mt12 & MPTI)
			return(PTMATCH + PUN);
		    else
			break;

	case QUEST: 
	case COMOP: 
	    if (mt2 & MENU)
		return(TYPR + NCVTR);
	    return(TYPR);

	case STREF: 
	    return(NCVTR + OTHER);

	case FORCE: 
	    return(TYPL);

	case COLON: 
	    if (mt12 & MENU)
		return(NCVT + PUN + PTMATCH);
	    else
		if (mt12 & MDBI)
		    return(TYMATCH);
		else
		    if (mt12 & MPTR)
			return(TYPL + PTMATCH + PUN);
		    else
			if ((mt1 & MINT) && (mt2 & MPTR))
			    return(TYPR + PUN);
			else
			    if ((mt1 & MPTR) && (mt2 & MINT))
				return(TYPL + PUN);
			    else
				if (mt12 & MSTR)
				    return(NCVT + TYPL + OTHER);
	    break;

	case ASSIGN: 
/* fprintf(stderr,"mt1 = %x mt2 = %x mt12 = %x\n", mt1, mt2, mt12); */
	    if ((mt1 & MSTR) && (mt12 == 0))
    		return(TYPL);
	case RETURN: 
	    if (mt12 & MSTR)
		return(LVAL + NCVT + TYPL + OTHER);
	case CAST: 
	    if (o == CAST && mt1 == 0)
		return(TYPL + TYMATCH);
	    if (mt12 & MDBI)
		return(TYPL + LVAL + TYMATCH);
	    else
		if ((mt1 & MENU) || (mt2 & MENU))
		    return(LVAL + NCVT + TYPL + PTMATCH + PUN);
		else
		    /*
		    * DJK put in the type != VOID
		    * so you can construct a pointer to a void function
		    */
		    if (mt12 == 0 && p->in.right->in.type != TVOID)
			break;
		    else
			/* Sun fix $w/sunfixes/t5.c */
			/* if right is TVOID and looks like a CALL, is not ok */
			if (mt2 == 0 && 
			    (p->in.right->in.op == CALL 
			    || p->in.right->in.op == UNARY CALL))
			    break;
			/* End of Sun fix */
		        else
			    if (mt1 & MPTR)
			        return(LVAL + PTMATCH + PUN);
			    else
			        if (mt12 & MPTI)
			 	    return(TYPL + LVAL + TYMATCH + PUN);
	    break;

	case ASG LS: 
	case ASG RS: 
	    if (mt12 & MINT)
		return(TYPL + LVAL + OTHER);
	    break;

	case ASG MUL: 
	case ASG DIV: 
	    if (mt12 & MDBI)
		return(LVAL + TYMATCH);
	    break;

	case ASG MOD: 
	case ASG AND: 
	case ASG OR: 
	case ASG ER: 
	    if (mt12 & MINT)
		return(LVAL + TYMATCH);
	    break;

	case ASG PLUS: 
	case ASG MINUS: 
	case INCR: 
	case DECR: 
	    if (mt12 & MDBI)
		return(TYMATCH + LVAL);
	    else
		if ((mt1 & MPTR) && (mt2 & MINT))
		    return(TYPL + LVAL + CVTR);
		if ((mt1 & MENU) || (mt2 & MENU))
		    return(NCVT);
	    break;

	case MINUS: 
	    if (mt12 & MPTR)
		return(CVTO + PTMATCH + PUN);
	    if (mt2 & MPTR)
		break;
	case PLUS: 
	    if (mt12 & MDBI)
		return(TYMATCH);
	    else
		if ((mt1 & MPTR) && (mt2 & MINT))
		    return(TYPL + CVTR);
		else
		    if ((mt1 & MINT) && (mt2 & MPTR))
			return(TYPR + CVTL);
		else
		    if ((mt1 & MPTR) && (mt2 & MENU))
		        return(TYPL + CVTR);
		else
		    if ((mt1 & MENU) || (mt2 & MENU))
		        return(NCVT);

    }
    uerror("operands of %s have incompatible types", opst[o]);
    return(NCVT);
}

int moditype(ty) TWORD  ty;
{

    switch (ty) {

	case TVOID:
	case UNDEF: 
	    return(0);		/* type is void */
	case ENUMTY: 
	case MOETY: 
	    return(MENU);

	case STRTY: 
	case UNIONTY: 
	    return(MSTR);

	case CHAR: 
	case SHORT: 
	case UCHAR: 
	case USHORT: 
	    return(MINT | MPTI | MDBI);
	case UNSIGNED: 
	case ULONG: 
	case INT: 
	case LONG: 
	    return(MINT | MDBI | MPTI);
	case FLOAT: 
	case DOUBLE: 
	    return(MDBI);
	default: 
	    return(MPTR | MPTI);

    }
}

NODE       *doszof(p) register NODE    *p;
{
 /* do sizeof p */
    int         i;

 /* whatever is the meaning of this if it is a bitfield? */
    i = tsize(p->in.type, p->fn.cdim, p->fn.csiz) / SZCHAR;

    tfree(p);
    sizeofflag = 0;
    if (i <= 0)
	werror("sizeof returns 0");
    return(bcon(i));
}

#ifndef BUG2
#ifdef DBXDEBUG
void DBprint(p)		/* for use when debugging from dbx */
	register NODE *p;
{
	fwalk(p, eprint, 0);
}
#endif /* DBXDEBUG */

void eprint(p, down, a, b) register NODE    *p;
int down;
int        *a, *b;
{
    register    int ty;
    char *os;
    char *ns;
    int idp;

    *a = *b = down + 1;
    while (down > 1) {
	printf("\t");
	down -= 2;
    }
    if (down)
	printf("    ");

    ty = optype(p->in.op);

    os = opst[p->in.op];
    if (!os)
        os = "???";
    printf("%x) %s, ", p, os);
    if (ty == LTYPE) {
	printf(CONFMT, p->tn.lval);
	printf(", %d, ", p->tn.rval);
	switch(p->in.op) {
	case NAME:
	case ICON:
	    idp = p->tn.rval;
	    if(idp > 0 && idp != NONAME) {
		ns = stab[idp].sname;
		if((int)ns <= 0)
			ns = "NONAME";
	    	printf("=> %s ", ns);
	    	if(p->tn.lval > 0)
			printf(" + 0x%x", p->tn.lval);
		printf(", ");
	    }
	    break;

	case FCON:
#ifdef MYATOF
	    printf("[%x,%x]dval:man 0x%x frac",
		p->tn.lval, p->tn.rval, p->fpn.fpnum.ne);
	    for(idp = 0; idp < NF; idp++)
		printf(" %x", p->fpn.fpnum.nf[idp]);
	    printf(", ");
#else
	    printf("dval:%s 0x%x 0x%x, ",  "",  p->fpn.dval);
#endif
	    break;


	} /* end switch */
    }
    tprint(p->in.type);
    printf(", %d, %d\n", p->fn.cdim, p->fn.csiz);
}
#endif

#ifdef ONEPASS

#ifdef MYATOF

static int fdigits;		/* number of digits printed */
static int dc;

void putsman( nn, f1 )
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
#endif

void prtdcon(p) register NODE   *p;
{
    int         i;
    char	nn[64];

#ifndef BUG1
    if(edebug) {
	printf("prtdcon(%x):\n", p);
	fwalk(p, eprint, 0);
	fflush(stdout);
    }
#endif

#ifdef MYATOF
    if (p->in.op == FCON && (p->in.type == DOUBLE || p->in.type == FLOAT) &&
#else
    if (p->in.op == FCON && p->in.type == DOUBLE &&
#endif
#ifdef MYATOF
    	!FP_ISZERO(&p->fpn.fpnum) ) {
#else
/*	p->fpn.dval != 0) { */
    	!FP_ISZERO(p->fpn.dval) ) {
#endif
#ifdef MYATOF
	    FPN f1;

	    f1 = p->fpn.fpnum;
	    dc = 0;
	    if(p->in.type == FLOAT)
		nn[dc++] = 'w';
	    else
		nn[dc++] = 'd';
	    nn[dc++] = '\t';
	    if(p->in.type == FLOAT)
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
	    sprintf(&nn[dc], "%d'",f1.ne);

#else /* MYATOF */
#if defined(linux) || defined(__alpha)
	    {
		union {
			double d;
			int    n[2];
		} dd;
		dd = p->fpn.dval;
		sprintf(nn, "d\tx'%08x%08x'\0", dd.n[1], dd.n[0]);
	    }
#else
	    sprintf(nn, "d\tx'%08x%08x'", p->fpn.dval);
#endif
#endif /* MYATOF */
	    /* set string for delayed store and get label */
	    i = settmpstr(nn);
	    p->tn.lval = 0;
	    p->tn.rval = -i;
	    p->in.op = NAME;
	    return;
    }
    if (p->in.op == FCON && p->in.type == DOUBLE) {
#ifdef MYATOF
    	if (FP_ISZERO(&p->fpn.fpnum)) {
#else
/*	if ( p->fpn.dval == 0 ) */
    	if (FP_ISZERO(p->fpn.dval)) {
#endif
	   getlab();
/* printf("Got zero double fcon\n"); */
	}
    }
    if (p->in.op == FCON) {
	/*
	 * old code: int v;
	 * v = *(int *) &p->fpn.dval;
	 * p->tn.lval = v;
	 *
	 * Why not? p->tn.lval = *(int *) &p->fpn.dval;
	 */
#ifdef MYATOF
	FP_FLOAT f;
 /* printf("Got in bad place\n"); */
	f = FP_DTOFP(p->fpn.fpnum);
#else
/*	float f = p->fpn.dval; */
	FP_FLOAT f = FP_DTOFP(p->fpn.dval);
#endif
	p->in.op = ICON;
	p->tn.rval = NONAME;
	p->tn.lval = *(int *) &f;
    }
/* added code - SPR 86100503 */
    if (p->in.op == ICON
	    && p->tn.rval != NONAME && ( p->in.type == LONG
		|| p->in.type == ULONG)) {
	locctr(DATA);
	defalign(ALDOUBLE);
	deflab(i = getlab());
	if (p->tn.rval >= 0)
	    printf("\t.word\t0, _%s+%#x\n",
			stab[p->tn.rval].sname, p->tn.lval);
	else
	    printf("\t.word\t0, L%d+%#x\n", - p->tn.rval, p->tn.lval);
	p->tn.lval = 0;
	p->tn.rval = -i;
	p->in.op = NAME;
	return;
    }
/* end of SPR 86100503 fix */
}
#endif


#ifndef BUG1
int         edebug = 0;
#endif
void ecomp(p) register NODE *p;
{

#ifndef BUG2
    if (edebug)
	fwalk(p, eprint, 0);
#endif
    if (!reached) {
	werror("statement not reached");
	reached = 1;
    }
    p = optim(p);
#ifndef BUG1
	if(edebug) {
		printf("after optim(%x):\n", p);
		fwalk(p, eprint, 0);
	}
#endif
#ifdef ONEPASS
    walkf(p, prtdcon);
#endif /* ONEPASS */
    locctr(PROG);
    ecode(p);
    tfree(p);
}

#ifdef STDPRTREE
#ifdef TWOPASS

extern void fltprint();

void prtree(p)
register NODE    *p;
{
    register struct symtab *q;
    register    int ty;
    int		n;
    register    int op;

#ifdef MYPRTREE
    MYPRTREE(p);	/* local action can be taken here; then return... */
#endif

    if( p->in.op == ICON && p->tn.rval != NONAME )
	p->in.op = ADDR;

    op = p->in.op;
    ty = optype(op);

    printf("%d\t%o\t", op, p->in.type );

    if( ty == LTYPE ) {
	if( op == FCON ) {
		fltprint(p);	/* machine dependent */
	} else {
		printf(CONFMT, p->tn.lval);
		printf("\t");
	}
    }

    if( ty != BITYPE ) {
	switch(op)
	{
	case ICON:
		printf("0\t");
		break;

	case NAME:
	case LNAME:
	case PNAME:
	case ADDR:
	case LADDR:
		if( p->tn.rval != NONAME && p->tn.rval >= 0 )
		{
			q = &stab[p->tn.rval];
			printf( "%d\t", q->uniqid );
		}
		else
		if(p->in.op == NAME && p->tn.rval == NONAME)
		{
			/* So the optimizer can recognize this as
			 * a "no-name" NAME
			 */
			printf("0\t");
		}
		else
			printf( "%d\t", p->tn.rval );
		break;

	case FCON:
		break;

	default:
		printf( "%d\t", p->tn.rval );
		break;
		}
	}

 /* handle special cases */

    switch (p->in.op) {

	case LADDR:
	case ADDR:	/* (MEY) (15-Jan-87) Added to match 1.3 PCO */
	case PNAME:	/* (MEY) (15-Jan-87) Added to match 1.3 PCO */
	case LNAME:	/* (MEY) (15-Jan-87) Added to match 1.3 PCO */
	case NAME: 
	case ICON: 	/* ? (MEY) Weren't named ICONs changed to ADDR above */

    /* print external name */
	    if (p->tn.rval == NONAME)
		printf("\n");
	    else
		if (p->tn.rval >= 0) {
		    q = &stab[p->tn.rval];
		    if(q->sclass == STATIC && q->slevel >1) {
		    	n = p->tn.rval;
			printf(LABFMT, n );
		    } else {
		        printf("%s\n",
 			    exname(q->sname, q));	
		    }
		}
		else {				/* label */
		    n = -p->tn.rval;
		    printf( LABFMT, n );
		    printf("\n");
		}
	    break;

	case STARG: 
	case STASG: 
	case STCALL: 
	case UNARY STCALL: 
	    /* print out size */
	    /* use lhs size, in order to avoid hassles with the
	       structure `.' operator */

	    /* note: p->in.left not a field... */
	    printf(CONFMT,
	 (CONSZ) tsize(STRTY, p->in.left->fn.cdim, p->in.left->fn.csiz));
	    printf("\t%d\t\n", talign(STRTY, p->in.left->fn.csiz));
	    break;

	default: 
	    printf("\n");
    }

    if (ty != LTYPE)
	prtree(p->in.left);
    if (ty == BITYPE)
	prtree(p->in.right);

}

#else  /* TWOPASS  */

/* ONEPASS equivalent of prtree()  */

void p2tree(p) register NODE    *p;
{
    register    int ty;
    register struct symtab *sp;

    if( p->in.op == ICON && p->tn.rval != NONAME )
	p->in.op = ADDR;

#ifdef MYP2TREE
    MYP2TREE(p);	/* local action can be taken here; then return... */
#endif

    ty = optype(p->in.op);

    switch (p->in.op) {

	case LNAME:
	case PNAME:
	case NAME: 
	case ICON: 
	case ADDR:
	case LADDR:
	  {
	    char        temp[32], *t = temp+3;
	    int		n;

	    if (p->tn.rval == NONAME) {
		p->in.name = "";
		break;
	    }

	    if (p->tn.rval >= 0) {	/* rval is a symbol tbl index */
	        sp = &stab[p->tn.rval];
		if(sp->sclass == STATIC && sp->slevel > 1) {
		    sprintf(t, LABFMT, sp->offset);
		    p->in.name = tstr(t);
		} else {
	            p->in.name = tstr( exname(sp->sname, sp) );
		}
		break;
	    }

	    /* the rval field is negative, so we convert it to a label */
		
	    n = -p->tn.rval;
	    sprintf(t, LABFMT, n);
	    p->in.name = tstr(t);
	    break;
	  }

	case STARG: 
	case STASG: 
	case STCALL: 
	case UNARY STCALL: 
    	    /* set up size parameters */
	    p->stn.stsize =
		( tsize(STRTY, p->in.left->fn.cdim, p->in.left->fn.csiz)
		  + SZCHAR - 1 ) / SZCHAR;

	    p->stn.stalign = talign(STRTY, p->in.left->fn.csiz) / SZCHAR;
	    break;

	case REG: 
	    /* Rev G change - rbusy call moved to treeinit in pass 2 */
	    /* FALL THROUGH */
	default: 
	    p->in.name = "";
    }

    p->in.rall = NOPREF;

    if (ty != LTYPE)
	p2tree(p->in.left);
    if (ty == BITYPE)
	p2tree(p->in.right);
}

#endif  /* TWOPASS */
#endif  /* STDPRTREE */
