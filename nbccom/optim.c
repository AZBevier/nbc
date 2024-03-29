/* optim.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid = "$Header: /bulk2/simhv/nbc-master/nbccom/RCS/optim.c,v 1.4 2019/01/31 22:01:15 jbev Exp $";
#endif

/*
 * $Log: optim.c,v $
 * Revision 1.4  2019/01/31 22:01:15  jbev
 * Update for Linux
 *
 * Revision 1.3  1996/03/22 00:07:35  jbev
 * Cleanup for Alpha Port.
 *
 */

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

#include "mfile1.h"

#define ISCON(p) ((p)->in.op == ICON)

#define SWAP(p, q) sp = p, p = q, q = sp

#define RCON(p) ISCON(p->in.right)

#define RO(p) p->in.right->in.op
#define RV(p) p->in.right->tn.lval

#define LCON(p) ISCON(p->in.left)

#define LO(p) p->in.left->in.op
#define LV(p) p->in.left->tn.lval

int         oflag = 0;
#ifndef BUG1
extern void eprint();
extern int tdebug;
#endif

NODE       *fortarg(p) NODE    *p;
{
 /* fortran function arguments */

    if (p->in.op == CM) {
	p->in.left = fortarg(p->in.left);
	p->in.right = fortarg(p->in.right);
	return(p);
    }

    while (ISPTR(p->in.type)) {
	p = buildtree(UNARY MUL, p, NIL);
    }
    return(optim(p));
}

 /* mapping relationals when the sides are reversed */
short       revrel[] =
{
    EQ, NE, GE, GT, LE, LT, UGE, UGT, ULE, ULT
};

NODE       *optim(p) register NODE *p;
{
 /* local optimizations, most of which are probably machine independent */

    register    int o, ty;
    NODE       *sp;
    int         i;
    TWORD       t;

#ifndef BUG1
    if(tdebug) {
	printf("optim(%x):\n", p);
	fwalk(p, eprint, 0);
    }
#endif
    if ((t = BTYPE(p->in.type)) == ENUMTY || t == MOETY)
	{
#ifndef BUG1
    if(tdebug) {
	printf("calling econvert optim(%x):\n", p);
	fwalk(p, eprint, 0);
    }
#endif
	econvert(p);
#ifndef BUG1
    if(tdebug) {
	printf("returing form econvert optim(%x):\n", p);
	fwalk(p, eprint, 0);
    }
#endif
	}
    if (oflag)
	return(p);
    ty = optype(o = p->in.op);
    if (ty == LTYPE)
	return(p);

    if (ty == BITYPE) {
	p->in.right = optim (p->in.right);
#ifndef BUG1
	if(tdebug) {
		printf("optim(%x): after optim(right)\n", p);
		fwalk(p, eprint, 0);
	}
#endif
    }

    p->in.left = optim (p->in.left);
#ifndef BUG1
    if(tdebug) {
	printf("optim(%x): after optim(left)\n", p);
	fwalk(p, eprint, 0);
    }
#endif

 /* collect constants */

    switch (o) {
#ifdef MPX
	case CALL:
	case UNARY CALL:
	    if (dobuiltins)
		fixcall (p);
	    break;
#endif /* MPX */

	case ASSIGN:
	    if (RO(p) == PLUS || RO(p) == MINUS) {
		if (LO(p) == REG || LO(p) == OREG || LO(p) == NAME) {
		    NODE       *rn = p->in.right->in.left;
		    sp = p->in.left;

#define _(x) rn->tn.x==sp->tn.x
		    if (_(op) && _(lval) && _(rval)) {
#undef _
			LO(p) = FREE;
			p->in.op = FREE;
			p = p->in.right;
			p->in.op = (p->in.op == MINUS) ? ASG MINUS : ASG PLUS;
		    }
		}
	    }
	    break;

	case SCONV:
	case PCONV:
	    return(clocal(p));

	case FORTCALL:
	    p->in.right = fortarg(p->in.right);
	    break;

	case UNARY AND:
	    if( LO(p) == LNAME || LO(p) == PNAME ) return(p);
	    if (LO(p) != NAME && LO(p) != OREG)
		cerror("& error");
#ifdef MPX
	    if (LO(p) == NAME && p->in.right && (RO(p)== ICON)
		&& RV(p)) {
		if (p->in.left->tn.rval > 0
		  && stab[p->in.left->tn.rval].sclass == EXTERN)
			return (p);
	    }
#endif

	    if (!andable(p->in.left))
		return(p);

	    LO(p) = ICON;

    setuleft:
    /* paint over the type of the left hand side with the type of the top */
#ifndef BUG1
	if(tdebug) {
		printf("optim(%x), setuleft:\n", p);
		fwalk(p, eprint, 0);
	}
#endif
	    p->in.left->in.type = p->in.type;
	    p->in.left->fn.cdim = p->fn.cdim;
	    p->in.left->fn.csiz = p->fn.csiz;
	    p->in.op = FREE;
	    return(p->in.left);

	case UNARY MUL:
#ifdef MPX /* MAR29 */
	/* this fix will cause 
	    la r?,name
	    lw r?,0w,R?
	   to be replaced by
	    lw r?,name
	 */
	    if (LO(p) == ICON &&
		LV(p) >= 0 && LV(p) <= 0x7ffff) {
#ifndef BUG1
		if(tdebug) {
		    printf("optim(%x), UNARY MUL:\n", p);
		    fwalk(p, eprint, 0);
		}
#endif
		LO(p) = NAME;
		goto setuleft;
	    }
#endif
	    if (LO(p) == PCONV) {
		p->in.left = clocal(p->in.left);
	    }
	    if (LO(p) == UNARY AND) {
		sp = p->in.left;
		p->in.left = sp->in.left;
		sp->in.op = FREE;
		goto setuleft;
	    }
	    if (LO(p) == PLUS) {
		sp = p->in.left;
		if (LO(sp) == UNARY AND
			&& LO(sp->in.left) == OREG
			&& nncon(sp->in.right)) {
		    i = sp->in.left->in.left->tn.lval + sp->in.right->tn.lval;
#ifdef MPX
		    if (i >= 0 && i < 0x80000) {
#else
		    if (i >= 0 && i < 60000) {
#endif
			p->in.op = FREE;
			sp = p, p = p->in.left;
			p->in.op = FREE;
			RO(p) = FREE;
			LO(p) = FREE;
			p = p->in.left->in.left;
			p->tn.lval = i;
			p->in.type = sp->in.type;
			p->fn.cdim = sp->fn.cdim;
			p->fn.csiz = sp->fn.csiz;
			return(p);
		    }
		}
	    }
	    /*
	     * Commented out to fix "hello"[5] problem
	     *  if (LO (p) != ICON) {
 	     *	break;
	     *  }
	     *  LO (p) = NAME;
	     *  goto setuleft;
	     */
	    break;


	case ASG MUL:
	    /* change muls to shifts */
	    if (nncon(p->in.right) && (i = ispow2(RV(p))) >= 0) {
		if (i == 0) {			/* multiplication by 1 */
		    p->fn.csiz = INT;
		    goto zapright;
		}
#ifdef MPX
		o = p->in.op = ASG SLA;
#else
		o = p->in.op = ASG LS;
#endif
		p->in.right->in.type = p->in.right->fn.csiz = INT;
		RV(p) = i;
	    }
	    break;

	case ASG MINUS:
	case MINUS:
#ifdef ON26FEB92
	case DECR:
#endif
	    if (!nncon(p->in.right))
		break;
	    RV(p) = -RV(p);
	    o = o == MINUS ? PLUS : ASG PLUS;
	    p->in.op = o;

	    /* DROP THROUGH */

	case MUL:
	case PLUS:
	case AND:
	case OR:
	case ER:
    /* commutative ops; for now, just collect constants */
    /* someday, do it right */
	    if (nncon(p->in.left) || (LCON(p) && !RCON(p)))
		SWAP(p->in.left, p->in.right);
#ifndef BUG1
    	    if(tdebug) {
		printf("optim(%x): sw 1, case PLUS, #1\n", p);
		fwalk(p, eprint, 0);
    	    }
#endif
    /* make ops tower to the left, not the right */
	    if (RO(p) == o) {
		NODE       *t1, *t2, *t3;
		t1 = p->in.left;
		sp = p->in.right;
		t2 = sp->in.left;
		t3 = sp->in.right;
	/* now, put together again */
		p->in.left = sp;
		sp->in.left = t1;
		sp->in.right = t2;
		p->in.right = t3;
	    }
#ifndef BUG1
    	    if(tdebug) {
		printf("optim(%x): sw 1, case PLUS, #2\n", p);
		fwalk(p, eprint, 0);
    	    }
#endif
	    if (o == PLUS
		    && LO(p) == MINUS
		    && RCON(p)
		    && RCON(p->in.left)
		    && conval(p->in.right, MINUS, p->in.left->in.right)) {
	zapleft:
#ifndef BUG1
		if(tdebug) {
			printf("optim(%x), zapleft:\n", p);
			fwalk(p, eprint, 0);
		}
#endif
		RO(p->in.left) = FREE;
		LO(p) = FREE;
		p->in.left = p->in.left->in.left;
	    }
#ifdef MPX
	    if (RCON(p) && LO(p) == o && RCON(p->in.left) &&
		 !nncon(p->in.left->in.right) ) {
		if (p->in.left->in.right->tn.rval > 0
		  && stab[p->in.left->in.right->tn.rval].sclass == EXTERN)
			goto skipfix;
	    }
	    else
#ifndef OCT2191
	    if (RCON(p) && LO(p) == o && RCON(p->in.left) &&
		 nncon(p->in.left->in.right) &&
    		 !nncon(p->in.right) ) {
		if (p->in.right->tn.rval > 0
		  && stab[p->in.right->tn.rval].sclass == EXTERN)
			goto skipfix;
	    }
	    else
#endif
#endif
	    if (RCON(p)
		    && LO(p) == o
		    && RCON(p->in.left)
		    && conval(p->in.right, o, p->in.left->in.right)) {
		goto zapleft;
	    }
	    else
#ifdef MPX
	    if (LCON(p) && RCON(p) && RV(p) &&
	     !nncon(p->in.left)) {
		if (p->in.left->tn.rval > 0
		  && stab[p->in.left->tn.rval].sclass == EXTERN)
		   goto skipfix;
	    } else
#endif
		if (LCON(p) && RCON(p) &&
			conval(p->in.left, o, p->in.right)) {
	    zapright:
#ifndef BUG1
		    if(tdebug) {
			printf("optim(%x), zapright:\n", p);
			fwalk(p, eprint, 0);
		    }
#endif
		    RO(p) = FREE;
		    if (p->in.type == LONG)
			p->in.type = INT;		/* DJK KLUDGE */
		    p->in.left = makety(p->in.left, p->in.type, p->fn.cdim, p->fn.csiz);
		    p->in.op = FREE;
		    return(clocal(p->in.left));
		}

#ifdef MPX
skipfix:
#endif
    /* change muls to shifts */

	    if (o == MUL && nncon(p->in.right) && (i = ispow2(RV(p))) >= 0) {
		if (i == 0) {			/* multiplication by 1 */
		    p->in.type = INT;
		    p->fn.csiz = INT;
		    goto zapright;
		}
#ifdef MPX
		o = p->in.op = SLA;
#else
		o = p->in.op = LS;
#endif
		p->in.type = PTR | INT;
		p->in.right->in.type = p->in.right->fn.csiz = INT;
		RV(p) = i;
	    }

	    if (o == PLUS) {
		if (nncon(p->in.right)) {
		    sp = p->in.left;
		    if (LO(p) == UNARY AND) {
			if (LO(sp) == NAME) {
#ifdef mpx
			    LV(sp) = LV(sp) + RV(p);
#else
			    LV(sp) += RV(p);
#endif
			    goto foldedadd;

		}
			else
			    if (LO(sp) == OREG) {
				i = LV(sp) + RV(p);
#ifdef MPX
				if (i >= 0 && i < 0x80000) {
#else
				if (i >= 0 && i < 60000) {
#endif
				    LV(sp) = i;
			    foldedadd:
#ifndef BUG1
				    if(tdebug) {
					printf("optim(%x), foldedadd:\n", p);
					fwalk(p, eprint, 0);
				    }
#endif
				    RO(p) = FREE;
				    p->in.op = FREE;
				    return(sp);
				}
			    }
		    }
		    else {
#ifndef BUG1
    	    if(tdebug) {
		printf("optim(%x): sw 1, case PLUS, #4\n", p);
		printf("testing sp = %x\n", sp);
		fwalk(p, eprint, 0);
    	    }
#endif
#ifdef JUNK_SEP4
			if (sp->in.op == NAME
#ifdef MPX /* MAR28 */
	     			&& (sp->tn.rval != NONAME)
#endif
				&& sp->tn.rval > 0
				&& stab[sp->tn.rval].sflags & SGERRYMANDER) {
					    /* it's gerrymandered */
			    sp->tn.lval += RV(p);
			    goto foldedadd;
			}
#endif
		    }
	    /* change +'s of negative consts back to - */

		    if (RV(p) < 0) {
			RV(p) = -RV(p);
			o = p->in.op = MINUS;
		    }
		}
		else {
	    /*
	     * try to find  int array[expr+const]
	     * right could be ICON, REG, or &OREG
	     */
		    NODE       *m, *c;
		    if (LO(p) == MUL || LO(p) == LS) {
			m = p->in.left;
			c = p->in.right;
		    }
		    else {
			if (RO(p) == MUL || RO(p) == LS) {
			    m = p->in.right;
			    c = p->in.left;
			}
			else {
			    break;
			}
		    }
		    if ((sp = m->in.left)->in.op == PLUS
			    && nncon(m->in.right)
			    && nncon(sp->in.right)) {

			i = RV(sp);
			if (m->in.op == MUL) {
			    i *= RV(m);
			}
			else {
			    i = (unsigned)i << (unsigned)RV(m);
			}
			switch (c->in.op) {

			    case ICON:
				i += c->tn.lval;
#ifdef MPX
				if (i >= 0 && i < 0x80000) {
#else
				if (i >= 0 && i < 60000) {
#endif
				    goto dontmesswith;
				}
				c->tn.lval = i;
				break;

			    case UNARY AND:
				if (LO(c) != OREG) {
				    break;
				}
				i += LV(c);
#ifdef MPX
				if (i < 0 || i >= 0x80000) {
#else
				if (i < 0 || i >= 60000) {
#endif
				    goto dontmesswith;
				}
				LV(c) = i;
				break;

			    case REG:
				RV(sp) = i;
				m->in.left = sp->in.left;
				sp->in.left = p;
				return(sp);
				break;

			    default:
				goto dontmesswith;
			}
			m->in.left = sp->in.left;
			sp->in.right->in.op = FREE;
			sp->in.op = FREE;
		    }
	    dontmesswith: ;
#ifndef BUG1
		    if(tdebug) {
			printf("optim(%x), dontmesswith:\n", p);
			fwalk(p, eprint, 0);
		    }
#endif
		}
	    }
	    break;

	case ASG MOD:
	case MOD:
	    /*
	     * When "MODing" by a power of two, change to an AND
	     * if MODing by 1, or if the dividend is unsigned
	     * (DAW)
	     */
	    if (nncon(p->in.right)
		&& (i = ispow2(RV(p))) >= 0) {

#ifdef MPX /* MAR4 */
		if (i == 0		/* any mod of 1 */
		    || ISUNSIGNED (p->in.left->in.type)) {
			/* or unsigned mod of (1<<const) */
#endif
		    o += AND - MOD;	/* change to ASG AND or AND */
		    p->in.op = o;
		    p->in.right->in.type = p->in.right->fn.csiz = INT;
		    RV(p) = ~((unsigned)(-1) << i);
		    /* if i is zero, this will be further improved below */
#ifdef MPX /* MAR4 */
		}
#endif
	    }
	    break;

	case ASG DIV:
	case DIV:
	    /*
	     * When dividing by a power of two, change to a shift
	     * if dividing by 1, or if the dividend is unsigned
	     * (DAW)
	     */
	    if (nncon(p->in.right)
		&& (i = ispow2(RV(p))) >= 0) {

#ifdef MPX
		    o += SRA - DIV;
#else
		    o += RS - DIV;
#endif
		    p->in.op = o;	/* change to RS or ASG RS */
		    p->in.right->in.type = p->in.right->fn.csiz = INT;
		    RV(p) = i;
		    /* if i is zero, this will be further improved below */
	    }
	    break;

	case EQ:
	case NE:
	case LT:
	case LE:
	case GT:
	case GE:
	case ULT:
	case ULE:
	case UGT:
	case UGE:
	    if (!LCON(p))
		break;

    /* exchange operands */

	    sp = p->in.left;
	    p->in.left = p->in.right;
	    p->in.right = sp;
	    p->in.op = revrel[p->in.op - EQ];
	    break;

	case OROR:
	case ANDAND:
	case CBRANCH:
	    sp = p->in.left;
	    if ((i = sp->in.op) == FLD) {
		goto fixfield;
	    }
	    if (i == NOT && sp->in.left->in.op == FLD) {
		sp->in.op = EQ;
		sp->in.right = bcon(0);
		sp = sp->in.left;
		goto fixfield;
	    }
	    break;
    }
 /*
  * one more chance for xxxx op constant
  *	taken from 68000 ccompiler
  */

#ifndef BUG1
    if(tdebug) {
	printf("optim(%X), after switch   1\n", p);
	fwalk(p, eprint, 0);
    }
#endif

    if (ty == BITYPE && nncon(p->in.right)) {
	i = RV(p);
	switch (o) {

	    case ASG AND:
		if (i == -1) {
		    goto zapright;
		}
		break;

	    case ASG MUL:
		if (i == 0) {
		    p->in.op = ASSIGN;
		} else {

		    /* change assign muls to assign shifts */

	    	    if ((i = ispow2 (RV (p))) >= 0) {
#ifdef MPX
			o = p->in.op = ASG SLA;
#else
			o = p->in.op = ASG LS;
#endif

			p->in.type = INT;

			p->in.right->in.type = p->in.right->fn.csiz = INT;
			RV (p) = i;
	    	    }
		}
		break;

	    case ASG OR:
		if (i == -1) {
		    p->in.op = ASSIGN;
		    break;
		}				/* fall through */

	    case ASG PLUS:
	    case ASG MINUS:
	    case ASG ER:
	    case PLUS:
	    case MINUS:
	    case ER:
		if (i == 0) {
		    goto zapright;
		}
		break;
	    case RS:
	    case LS:
	    case ASG RS:
	    case ASG LS:
#ifndef BUG1
		if(tdebug) {
			printf("optim(%x), case RS, LS:\n", p);
			printf("i = %d\n", i);
		}
#endif
		if( i & ~(0x1f) ) {
			werror("shift count truncated mod 32");
			RV(p) = (i &= 0x1f);
		}
		if (i == 0) {
		    goto zapright;
		}
		break;

	    case AND:
		if (i == -1) {
		    goto zapright;
		}
	    case MUL:
		if (i == 0) {
		    p->in.op = COMOP;
		    break;
		}
		break;

	    case OR:
		if (i == 0) {
		    goto zapright;
		}
		if (i == -1) {
		    p->in.op = COMOP;
		    break;
		}
		break;

	    case EQ:
	    case NE:
		if (i == 0 && LO(p) == FLD) {
		    sp = p->in.left;
	    /*
	     * change a FLD node into (addr & mask)
	     */
	    fixfield:
		/*
		*    Comment out to make fixfield a no-op

		*    if(tdebug) {
		*	printf("optim(%x), fixfield:\n", p);
		*	fwalk(p, eprint, 0);
		*    }
		*    t = sp->in.type;
		*    i = sp->tn.rval;
		*    s = UPKFSZ (i);
		*    o = SZINT - UPKFOFF (i) - s;
		*    if (t == SHORT || t == USHORT) {
		*	o -= SZSHORT;
		*    }
		*    if (t == CHAR || t == UCHAR) {
		*	o -= SZINT - SZCHAR;
		*    }
		*    sp->in.op = AND;
		*    sp->in.left->in.type = t;
		*    sp->in.right = bcon (((1 << s) - 1) << o);
		*    if(tdebug) {
		*	printf("optim(%x), fixfield done:\n", p);
		*	fwalk(p, eprint, 0);
		*    }
		*/
		     break;
		}
		break;
	}
    }
    return(p);
}

int nncon(p) NODE  *p;
{
 /* is p a constant without a name */
    return(p->in.op == ICON && p->tn.rval == NONAME);
}

