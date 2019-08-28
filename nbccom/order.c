/* order.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid = "$Header: /bulk2/simhv/nbc-master/nbccom/RCS/order.c,v 1.6 2019/01/31 22:01:15 jbev Exp $";
#endif

/*
 * $Log: order.c,v $
 * Revision 1.6  2019/01/31 22:01:15  jbev
 * Update for Linux
 *
 * Revision 1.5  1996/03/22 00:15:04  jbev
 * Cleanup for Alpha port.
 *
 */

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

#include "mfile2.h"

int revbr[] = {		/* used when switching order of compare */
    EQ, NE, GE, GT, LE, LT, UGE, UGT, ULE, ULT
};

void stoasg(p, o) register NODE *p; int o;
{
 /*
  * should the assignment op p be stored,
  * given that it lies as the right operand of o
  * (or the left, if o==UNARY MUL)
  */
    if (p->in.op == INCR || p->in.op == DECR)
	return;
    if (o == UNARY MUL && p->in.left->in.op == REG &&
	(p->in.left->tn.rval & 7) == 0)
	SETSTO(p, INAREG);

}

int deltest(p) register NODE   *p;
{
 /* should we delay the INCR or DECR operation p */
    register    int lo = p->in.left->in.op;
    return(lo == REG || ((lo == NAME || lo == OREG) &&
	 ispow2(p->in.right->tn.lval) >= 0));
}

int autoincr(p) NODE   *p;
{
    return(0);
}

void mkadrs(p) register NODE    *p;
{
    register    int o;

    o = p->in.op;

    if (asgop(o)) {
	if (p->in.left->in.su >= p->in.right->in.su) {
	    if (p->in.left->in.op == UNARY MUL) {
		if (p->in.right->in.su == 0 ||
			p->in.left->in.left->in.su > 1) {
		    SETSTO(p->in.left->in.left, INTEMP);
	    /* DJK hmmmm */
		}
		else {
		    SETSTO(p->in.right, INTEMP);

		}
	    }
	    else
		if (p->in.left->in.op == FLD &&
		 p->in.left->in.left->in.op == UNARY MUL) {
	    /* SETSTO(p->in.left->in.left->in.left, INTEMP); DJK hmmmm */
		    if (p->in.right->in.su != 0) {
			SETSTO(p->in.right, INTEMP);
		    }
		    else {
			SETSTO(p->in.left->in.left->in.left, INTEMP);

		    }
		}
		else {		/* should be only structure assignment */
		    SETSTO(p->in.left, INTEMP);
		}
	}
	else
	    SETSTO(p->in.right, INTEMP);
    }
    else {
	if (p->in.left->in.su > p->in.right->in.su) {
	    SETSTO(p->in.left, INTEMP);
	}
	else {
	    SETSTO(p->in.right, INTEMP);
	}
    }
}

int notoff(t, r, off, cp) int t, r; CONSZ     off;
char       *cp;
{
 /*
  * is it legal to make an OREG or NAME entry which has an
  * offset of off, (from a register of r), if the
  * resulting thing had type t
  */

#ifdef MPX
#ifndef BUG1
if(odebug)
printf ("notoff t %x, r %x, off %x, cp %c\n",t,r,off,cp[0]);
#endif

    if (r == R0 || off < 0 || off >= 0x80000 || cp[0]=='L')
	return(1);	/* NO */
    switch (r) {
	case 1:
	case 2:
	case 3:
	case FP:
	case AP:
	case TP:
	case CP:
	    return(0);		/* YES */
    }
    return(1);	/* NO */
#else
#ifdef FORT
    if (r == R0 || r == B0 || off < 0 || off >= 0x80000 || cp[0]=='L')
#else /* NOT FORT */
#ifdef MPX
    if (r == R0 || off < 0 || off >= 0x80000 || cp[0]=='L')
#else
    if (r == R0 || r == B0 || off < 0 || off >= 60000 || cp[0]=='L')
#endif
#endif /* FORT */
	return(1);	/* NO */
    return(0);		/* YES */
#endif /* MPX */
}

#define max(x, y) ((x) < (y) ? (y) : (x))

void sucomp(p) register NODE    *p;
{

 /* set the su field in the node to the sethi-ullman number, or local equivalent */

    register    int o, ty, sul, sur, r, szr;
#ifdef MPX /* MAR23 */
    int t, mt, mf;

    t = p->in.type;
#endif
    o = p->in.op;
    ty = optype(o);
    p->in.su = szty(p->in.type); /* 2 for float or double, else 1 */ ;

    if (ty == LTYPE) {
	if (o == OREG) {
	    r = p->tn.rval;
    /* oreg cost is (worst case) 1 + number of temp registers used */
	    if (R2TEST(r)) {
		if (R2UPK1(r) != 100 && istreg(R2UPK1(r)))
		    ++p->in.su;
		if (istreg(R2UPK2(r)))
		    ++p->in.su;
	    }
	    else {
		if (istreg(r))
		    ++p->in.su;
	    }
	}
	if (p->in.su == szty(p->in.type)
		&& (p->in.op != REG || !istreg(p->tn.rval))
		&& (p->in.op != REG || (p->tn.rval >= R4 && p->tn.rval <= R7))
		&& p->in.type != USHORT
		&& p->in.type != CHAR
	    )
	    p->in.su = 0;
	return;
    }

    else
	if (ty == UTYPE) {
	    switch (o) {
		case UNARY CALL:
		case UNARY STCALL:
		    p->in.su = fregs;	/* all regs needed */
		    return;

#ifdef MPX /* MAR23 */
  case SCONV:
   mt = t == FLOAT || t == DOUBLE || t == LONG || t == SCONV;
   mf  = p->in.left->in.type == FLOAT || p->in.left->in.type == DOUBLE;
   if (mt != mf || t == LONG || t == DOUBLE || t == SCONV){
    p->in.su = fregs;
    return;
   }
#endif
		case UNARY MUL:
		    p->in.su = szty(p->in.type);
		    if (p->in.su < p->in.left->in.su) {
			p->in.su = p->in.left->in.su;
		    }
		    if (p->in.left->in.op == REG) {
			p->in.su = 0;
		    }
		    return;

#ifdef MPX
		case UMULP:
		    p->in.su = max (p->in.left->in.su, szty (p->in.type));
		    return;
#endif

		default:
		    p->in.su = p->in.left->in.su + (szty(p->in.type) > 1 ? 2 : 0);
		    return;
	    }
	}


 /* If rhs needs n, lhs needs m, regular su computation */

    sul = p->in.left->in.su;
    sur = p->in.right->in.su;
    szr = szty( p->in.right->in.type );
    if ( szty( p->in.type ) > szr && szr >= 1 ) {
	     /* implicit conversion on rhs */
	     szr = szty( p->in.type );
	     sur = max( szr, sur );
    }

    if (o == ASSIGN) {
 /* computed by doing right, then left (if not in mem), then doing it */
	p->in.su = max(sur, sul + 1);
	return;
    }

    if (o == CALL || o == STCALL) {
 /* in effect, takes all free registers */
	p->in.su = fregs;
	return;
    }

    if (o == STASG) {
 /* right, then left */
	p->in.su = max(max(1 + sul, sur), fregs);
	return;
    }

    if (asgop(o)) {
 /* computed by doing right, doing left address, doing left, op, and store */
	p->in.su = max(sur, sul + 2);
#ifdef MPX /* MAR23 */
  if (t == LONG || t == DOUBLE || p->in.left->in.op == UNARY MUL)
   p->in.su = max(p->in.su, sur+1); /* address computed first */
#endif
	return;
    }

    switch (o) {
	case ANDAND:
	case OROR:
	case QUEST:
	case COLON:
	case COMOP:
	    p->in.su = max(max(sul, sur), 1);
	    return;

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
        /* logical ops, put harder on left and switch sense */

	    if (sur > sul
		&& !istnode (p->in.left)) {
		register NODE  *temp;
		temp = p->in.left;
		p->in.left = p->in.right;
		p->in.right = temp;
		p->in.op = revbr[p->in.op - EQ];
		ty = sur;
		sur = sul;
		sul = ty;
	    }
	    break;

	case MUL:
	case PLUS:
	case OR:
	case ER:
	case AND:
    /* commutative ops; put harder on left */
	    if (sur > sul && !istnode(p->in.left)) {
		register NODE  *temp;
		temp = p->in.left;
		p->in.left = p->in.right;
		p->in.right = temp;
		ty = sur;
		sur = sul;
		sul = ty;
		szr = szty( p->in.right->in.type );
		if ( szty( p->in.type ) > szr && szr >= 1 ) {
			 /* implicit conversion on rhs */
			 szr = szty( p->in.type );
			 sur = max( szr, sur );
		}
	    }
	    break;
    }

 /* binary op, computed by left, then right, then do op */

    if (dope[o] & MULFLG) {
	sur += 2;
    }

    p->in.su = max(sul, szty(p->in.right->in.type) + sur);
}

#ifndef BUG1
int         radebug = 0;
#endif

void rallo(p, down) NODE    *p; int down;
{
 /* do register allocation */
    register    int o, type, down1, down2, ty;

#ifndef BUG2
    if (radebug)
	printf("rallo( %x, ", p), print("rall", down), printf(")\n");
#endif

    down2 = NOPREF;
    p->in.rall = down;
    down1 = (down &= ~MUSTDO);

    ty = optype(o = p->in.op);
    type = p->in.type;

    if (type == DOUBLE || type == FLOAT || type == LONG) {
	if (o == FORCE)
	    down1 = callreg(p) | MUSTDO;
#ifdef MPX /* MAR23 */
	if (asgop(o)){
	    if (p->in.left->in.op == UNARY MUL){
		rallo(p->in.left->in.left, R2);
#ifndef SEP26
		if (type == DOUBLE && p->in.right->in.op == SCONV &&
		   p->in.right->in.left->in.op != SCONV &&
		   p->in.right->in.left->in.type != DOUBLE)
		  rallo(p->in.right, R1);
		else
#endif
		  rallo(p->in.right, R0);
		return;
	    }
	}
#endif
    }
    else
	switch (o) {
	    case ASSIGN:
		down2 = down;
		down1 = NOPREF;
		break;
	    case CALL:
	    case EQ:
	    case NE:
	    case GT:
	    case GE:
	    case LT:
	    case LE:
#ifdef MPX
		down1 = NOPREF;
		break;
	    case STASG:
		down2 = down;
		down1 = R2;
	    case UNARY MUL:
		if (down == NOPREF) {
			down = R2;
			p->in.rall = down;
		}
		down1 = R2;	/* preference */
		break;
	    case MINUS:
		if ((p->in.left->in.op == UNARY MUL) ||
		    (p->in.right->in.op == MOD || p->in.right->in.op == DIV))
		down1 = R2;	/* preference */
		break;

	    case DIV:	/* TUE */
	    case MOD:	/* TUE */
#ifdef SEP25
		down2 = R2;	/* preference */
		break;
#endif
	    case MUL:	/* TUE */
		down1 = R1;	/* preference */
		break;
#endif
	    case NOT:
	    case ANDAND:
	    case OROR:
		down1 = NOPREF;
		break;

	    case FORCE:
		down1 = callreg(p) | MUSTDO;
		break;

	}

    if (ty != LTYPE)
	rallo(p->in.left, down1);
    if (ty == BITYPE)
	rallo(p->in.right, down2);

}

void offstar(p) register NODE   *p;
{
#ifndef BUG1
    if(odebug) {
	printf("offstar(%x)\n", p);
	fwalk(p, eprint, 0);
	prbusy();
    }
#endif
    if (p->in.op == PLUS) {
	if (p->in.left->in.su == fregs) {
	    order(p->in.left, INTAREG | INAREG);
	    return;
	}
	else
	    if (p->in.right->in.su == fregs) {
		order(p->in.right, INTAREG | INAREG);
		return;
	    }
    }
    if (p->in.op == PLUS) {
	if (p->in.right->in.op == ICON
		&& p->in.right->tn.lval >= 0
		&& p->in.right->in.name[0] == '\0'
#ifdef FORT
		&& p->in.right->tn.lval < 0x80000) {
#else /* NOT FORT */
#ifdef MPX
		&& p->in.right->tn.lval < 0x80000) {
#else
		&& p->in.right->tn.lval < 60000) {
#endif
#endif /* FORT */
	    p = p->in.left;
	    order(p, INTAREG | INAREG);
	    return;
	}
    }

    order(p, INTAREG | INAREG);
}

/*
 *	delincr() is used by rewrites for U* and INCR/DECR
 *	to optimize postfix ++ and -- on register variables.
 */
int delincr(p, cook) register NODE   *p; int cook;
{
	register NODE *pl;
	register int op, lop;
	NODE	*ptemp;

#ifndef BUG1
	if(odebug) {
		printf("delincr(%x)\n", p);
		fwalk(p, eprint, 0);
	}
#endif

	op = p->in.op;
	if(op != INCR && op != DECR)
		return(0);

	pl = p->in.left;
	lop = pl->in.op;
	if(lop != REG && lop != NAME && lop != OREG)
		return(0);

	if( cook & FOREFF ) {
		/* We dont need the result, so just use the original */
		/* tree for the incrementation. */

		ptemp = p;

	} else {
		/* Copy the tree for the delayed incrementation */
		/* Then overwrite original tree and get the result, */
		/* which is simply the original value. */

		ptemp = tcopy(p);
		tfree(p->in.right);
		ncopy(p, pl);			/* copy pl over p */
		pl->in.op = FREE;		/* mustn't use tfree here. */
#ifndef BUG1
	if(odebug) {
		printf("delincr0(%x)\n", ptemp);
		fwalk(ptemp, eprint, 0);
    		prbusy();
	}
#endif
		if(cook & (FORCC|FORZCC) )	/* wait till after increment */
			order(p, INAREG);	/* to set condition codes */
		else
			order(p, cook);
	}

	/* Now do the incrementation */

	if(op == INCR)
		ptemp->in.op = ASG PLUS;	/* p becomes REG += ICON */
	else
		ptemp->in.op = ASG MINUS;	/* p becomes REG += ICON */
#ifndef BUG1
	if(odebug) {
		printf("delincr2(%x)\n", ptemp);
		fwalk(ptemp, eprint, 0);
    		prbusy();
	}
#endif
	order(ptemp, FOREFF);

#ifndef BUG1
	if(odebug) {
		printf("delincr3(%x)\n", ptemp);
		fwalk(ptemp, eprint, 0);
    		prbusy();
	}
#endif
	if(cook & (FORCC|FORZCC) )
		order(p, cook);			/* set condition codes now */

	return(1);
}

int setincr(p) register NODE   *p;
{
#ifndef BUG1
    if(odebug) {
	printf("setincr(%x):\n", p);
	fwalk(p, eprint, 0);
    }
#endif

    p = p->in.left;
    if (p->in.op == UNARY MUL) {
	NODE *pl = p->in.left;
#ifndef AUG231993
    	offstar(p->in.left);
        oreg2(p);
#endif
#ifdef AUG231993
	order(pl, INTAREG | INAREG);
	if(pl->tn.rval == R0)
		order(pl, INTAREG | INAREG);
	p->in.op = OREG;
	p->tn.lval = pl->tn.lval;
	p->tn.rval = pl->tn.rval;
	tfree(pl);
#endif
	return(1);
    }
    return(0);
}

int setbin(p, cookie)
register NODE    *p;
int cookie;
{
    register    int ro, rt;
    NODE	*pl, *pr;
    int		po;

#ifndef BUG1
    if(xdebug) {
	printf("setbin(%x, ", p);
	print("cookie", cookie);
	printf("):\n");
	fwalk(p, eprint, 0);
	prbusy();
    }
#endif

    po = p->in.op;
    pl = p->in.left;
    pr = p->in.right;
    rt = p->in.right->in.type;
    ro = p->in.right->in.op;

    if (canaddr(p->in.left) && !canaddr(p->in.right)) {
 /* address rhs */
	if (ro == UNARY MUL) {
#ifdef MPX /* MAR24 */
	    /* left op of U* is reg, see if R0 */
	    if (pr->in.left->in.op == REG && pr->in.left->tn.rval == R0) {
		/* left node of U* is reg and in R0 */
		/* if left node is REG we need to put in temp */
		if (pl->in.op == REG && busy[R1] && busy[R2]) {
		    order(p->in.left, INTEMP);
	    	    return(1);
		}
	    }
#endif
#ifndef BUG1
    if(xdebug) {
	printf("setbin ro=U*(%x, ", p);
	print("cookie", cookie);
	printf("): Doing offstar call with left/right\n");
	fwalk(p, eprint, 0);
	prbusy();
    }
#endif
	    offstar(p->in.right->in.left);
	    return(1);
	}
	else {
#ifndef MPX_MAR7
#ifndef BUG1
    if(xdebug) {
	printf("setbin0(%x, ", p);
	print("cookie", cookie);
	printf("): testing for r0 & r1 req'd\n");
	fwalk(p, eprint, 0);
	prbusy();
    }
#endif
	if (p->in.left->in.op == REG && 
	  p->in.right->in.right &&
	  busy[R0] && busy[R1]) {
		order(p->in.left, INTEMP);
		return(1);
	}
	if (p->in.left->in.op == REG && 
	  (ro == UNARY AND || p->in.right->in.right) &&
	  busy[R1] && busy[R2]) {
#ifndef OCT2191
	    if (!busy[R0] && p->in.su <= 1) {
		p->in.right->tn.rall = R0 | MUSTDO;
	        order(p->in.right, INAREG | INTAREG | SOREG);
	    } else
#else
	    if (!busy[R0]) {
		p->in.right->tn.rall = R0 | MUSTDO;
	        order(p->in.right, INAREG | INTAREG | SOREG);
	    } else
#endif
		order(p->in.left, INTEMP);
	    return(1);
	}
	if (p->in.left->in.op == REG &&
	  (p->in.left->tn.rval == 1 || p->in.left->tn.rval == 0) &&
	    ((ro == MOD || ro == DIV || ro == MUL) ||
#ifdef DEC04
            (ro == SCONV && p->in.right->in.type == DOUBLE))) {
#else
            (ro == SCONV && 
	    (p->in.right->in.type == DOUBLE || p->in.right->in.type == FLOAT)
		))) {
#endif
#ifndef BUG1
	if(xdebug) {
	printf("setbin0 : calling order with left\n");
	fwalk(p, eprint, 0);
	prbusy();
	}
#endif
            if (ro != SCONV) {
        	if(p->in.left->tn.rall == NOPREF) {
        		p->in.left->tn.rall = R2;
        	}
                order(p->in.left, INAREG | INTAREG);
            } else {
                order(p->in.left, INTEMP);
            }
#ifndef BUG1
	if(xdebug) {
	printf("setbin0 : after order call with left\n");
	fwalk(p, eprint, 0);
	prbusy();
	}
#endif
	    return(1);
	}
#endif
#ifndef MAR29
#ifndef BUG1
	if(xdebug) {
	  printf("setbinx : looking for store into temp\n");
	  fwalk(p, eprint, 0);
	  prbusy();
	}
#endif
	if (p->in.left->in.op == REG && 
	  p->in.right->in.left &&
	  (p->in.right->in.left ->in.op == MUL ||
	  p->in.right->in.left->in.op == DIV) &&
	  (busy[R0] || busy[R1])) {
		order(p->in.left, INTEMP);
		return(1);
	}
#ifndef OCT2191
	if (p->in.left->in.op == REG && 
	  p->in.right->in.left &&
	  (p->in.right->in.su > 1) &&
	  (busy[R0] || busy[R1] || busy[R2]) ) {
		order(p->in.left, INTEMP);
		return(1);
	}
#endif
#endif
	    order(p->in.right, INAREG | INTAREG | SOREG);
	    return(1);
	}
    }

#ifndef BUG1
	if(xdebug) {
	  printf("setbiny : Before istnode test\n");
	  fwalk(p, eprint, 0);
	  prbusy();
	}
#endif

#ifndef SPR02_26_94
    if ((p->in.left->in.op == OREG ||
    	  (p->in.left->in.op == REG &&
    	  p->in.left->tn.rval > 2)) &&
	  p->in.right->in.left &&
	  p->in.right->in.op == UNARY MUL &&
	  (p->in.right->in.left->in.op == REG &&
    	  p->in.right->in.left->tn.rval > 2)) {
/* 	  (busy[R1] || busy[R2]) )) { */
	    offstar(p->in.right->in.left);
		return(1);
    }
#endif
    if (!istnode(p->in.left)) {		/* try putting LHS into a reg */
	order(p->in.left, INAREG | INTAREG | INBREG | INTBREG );
	return(1);
    }

#ifndef BUG1
	if(xdebug) {
	  printf("setbiny : Before switch test\n");
	  fwalk(p, eprint, 0);
	  prbusy();
	}
#endif
#ifndef SPR02_26_94
	if (p->in.left->in.op == REG && 
	  p->in.right->in.left &&
	  p->in.right->in.op == UNARY MUL &&
	  (p->in.right->in.left->in.op == REG &&
/*	  (busy[R0] || busy[R1] || busy[R2]) )) { */
	  (busy[R1] && busy[R2]) )) {
		order(p->in.left, INTEMP);
		return(1);
	}
#endif
    switch(po) {
	case PLUS:
	case MINUS:
	case AND:
	case OR:
	case ER:
	case LS:
	case RS:
#ifdef MPX
	case SRA:
	case SLA:
#endif
		/* left is temp reg */
#ifdef DEC04
		if(busy[p->in.left->tn.rval] == 1) {   /*  Safety first */
#else
		if ((busy[p->in.left->tn.rval] == 1) ||   /*  Safety first */
		  (busy[p->in.left->tn.rval] == 2)) {   /*  Safety first */
#endif
			p->in.op = ASG po;
			return(1);
		}
    }

    if (ro == UNARY MUL && rt != CHAR && rt != UCHAR) {
	    offstar(p->in.right->in.left);
	    return(1);
    }
    /*
     * This machine does not have native CHAR or USHORT operators
     */
#ifndef OCT07
    if ( ro == REG) {
		return(0);
    }
#endif
    if ( ro == ICON) {
#ifndef MPX_MAR14
#ifndef BUG1
    if(xdebug) {
	printf("setbin1(%x, ", p);
	print("cookie", cookie);
	printf("): testing for r0 & r1 req'd\n");
	fwalk(p, eprint, 0);
	prbusy();
    }
#endif
	if (p->in.left->in.op == REG &&
	  (p->in.left->tn.rval == 1 || p->in.left->tn.rval == 0) &&
	    (po == MOD || po == DIV || po == MUL)) {
#ifndef BUG1
	if(xdebug) {
	printf("setbin1: calling order with left\n");
	fwalk(p, eprint, 0);
	prbusy();
	}
#endif
	    if(p->in.left->tn.rall == NOPREF) {
		p->in.left->tn.rall = R2;
	    }
	    order(p->in.left, INAREG | INTAREG);
#ifndef BUG1
	if(xdebug) {
	printf("setbin1 : after order call with left\n");
	fwalk(p, eprint, 0);
	prbusy();
	}
#endif
	    return(1);
	}

#ifdef DEC04_nogood
	/* looking for allocated oreg on left with icon to * on right */
	if (p->in.left->in.op == REG && 
	  busy[R0] && busy[R1]) {
		order(p->in.left, INTEMP);
		return(1);
	}
#endif
	order(p->in.right, INAREG | INBREG);
	return(1);
    }

    if (rt == CHAR || rt == USHORT || (ro != NAME && ro != OREG)) {
	order(p->in.right, INAREG | INBREG);
	return(1);
    }

    /* work like devil to make unsigned compares work */
#ifndef BUG1
    if(xdebug) {
	printf("setbin(%x):  logop test reached\n", p);
    }
#endif
    if(logop(p->in.op)) {
	if(pl->in.type == UNSIGNED || pr->in.type == UNSIGNED) {
		pl = talloc();
		pl->in.op = SCONV;
		pl->in.rall = NOPREF;
		pl->in.type = LONG;
		pl->in.left = p->in.left;
		p->in.left = pl;

		pr = talloc();
		pr->in.op = SCONV;
		pr->in.rall = NOPREF;
		pr->in.type = LONG;
		pr->in.left = p->in.right;
		p->in.right = pr;

		order(p->in.right, INTEMP);
		order(p->in.left, INAREG);
		return(1);
	}
    }
#endif
    return(0);
}

int setstr(p) register NODE    *p;
{			/* structure assignment */

#ifndef BUG1
    if(odebug) {
	printf("setstr(%x)\n", p);
	fwalk(p, eprint, 0);
	prbusy();
    }
#endif

    if (p->in.right->in.op != REG) {
	order(p->in.right, INTAREG);
	return(1);
    }

    p = p->in.left;
    if (p->in.op != NAME && p->in.op != OREG) {
	if (p->in.op != UNARY MUL)
	    cerror("bad setstr");
	order(p->in.left, INTAREG);
	return(1);
    }
    return(0);
}

#ifndef MPX
loadstruct(p)
register NODE	*p;
{
	register NODE	*lf, *rt;
	int		align, size;
	NODE		tempnode;
	NODE		*tp;

	align = p->stn.stalign;
	size  = p->stn.stsize;
	lf    = p->in.left;
	rt    = p->in.right;

#ifndef BUG1
	if(odebug) {
		printf("loadstruct(0x%x):\n", p);
		prbusy();
		fwalk(p, eprint, 0);
	}
#endif

	if(size > 8 || align > 8 || p->in.op != STASG)
		cerror("bad loadstruct");

	if(rt->in.op != REG)
		order(rt, INAREG);

	if(align < 4 || ( (size & 3) != 0)) {
		/* copy the structure to temp first */
		/* to guarantee alignment and padding */

		tempnode.in.op = OREG;
		tempnode.in.type = INT;
		tempnode.in.name = "";
		tempnode.tn.rval = TMPREG;
		tempnode.tn.lval = BITOOR(freetemp(2));	/* 2 words */

		tp = talloc();
		*tp = tempnode;		/* copy node structure */
		p->in.left = tp;
		expand(p, FOREFF, "ZS");	/* do STASG into temp */

		p->in.right = &tempnode;
		p->in.left = lf;	/* original REG on lhs */
		rfree(rt->tn.rval, INT);
		rt = p->in.right;
	}


	rt->in.op = OREG;	/* for adrput() */
	lf->in.type = INT;	/* kluge the type, for poor reclaim() */
	if(size > 4) {
		rt->tn.lval += 4;
		lf->tn.rval += 1;
#ifdef MPX
		expand(p, FOREFF, "	trr	AR,AL\n");
#else
		expand(p, FOREFF, "	movw	AR,AL\n");
#endif /* MPX */
		/* rfree(rt->tn.rval, INT); causes reg overfreed */
		lf->tn.rval -= 1;
		rt->tn.lval -= 4;
		lf->in.type = DOUBLE;
	}
#ifdef MPX
	expand(p, FOREFF, "	trr	AR,AL\n");
#else
	expand(p, FOREFF, "	movw	AR,AL\n");
#endif /* MPX */
	rt->in.op = REG;	/* restore original op */
	rfree(rt->tn.rval, INT);

	/* fix up busy array if needed. */

	*p = *lf;			/* copy reg node to node at p */
	lf->in.op = FREE;

#ifndef BUG1
	if(odebug) {
		printf("loadstruct(0x%x) returning:\n");
		prbusy();
		fwalk(p, eprint, 0);
	}
#endif

	return(1);
}
#endif /* MPX */

int setasg(p, cook) register NODE    *p;
int cook;
{
 /* setup for assignment operator */
    register    int ro, lo;

#ifndef BUG1
    if(odebug) {
	printf("setasg(%x, ", p);
	print("cookie", cook);
	printf("):\n");
	fwalk(p, eprint, 0);
	prbusy();
    }
#endif

    ro = p->in.right->in.op;
    lo = p->in.left->in.op;
    if (!canaddr(p->in.right)) {
	/* SPR02_28_94_NEW */
	if (lo == UNARY MUL && ro == UNARY MUL) {
	    offstar(p->in.left->in.left);
	    return(1);
	}

#ifndef SPR02_28_94_NEW
    	if (lo == OREG && ro == UNARY MUL &&
    	  p->in.right->in.su > 2 &&
    	  busy[R1] && !busy[R2]) {
    	    int newreg = 2;
    	    /*
    	     * We need to do a reg-reg change to free r1.
    	     * We should move it into r2.  
    	     */
    	    p->in.left->tn.rval = newreg;
    	    printf("\ttrr\tr1,r2\n");
    	    ++busy[R2];
    	    --busy[R1];
    	    return(1);
    	}
#endif /* SPR_28_94 */
	if (ro == UNARY MUL)
	    offstar(p->in.right->in.left);
#ifndef MAR24
	else if (ro == UNARY AND && lo == UNARY MUL)
	    order(p->in.left, INAREG | INBREG | SOREG);
#endif
	else
	    order(p->in.right, INAREG | INBREG | SOREG);
	return(1);
    }
/* can address right */
#ifndef RCS_PORT_ERRORS
#ifndef BUG1
    if(odebug) {
	printf("setasg RCS_PORT(%x, ", p);
	print("cookie", cook);
	printf("):\n");
	fwalk(p, eprint, 0);
	prbusy();
    }
#endif
    if (ro == REG && lo == UNARY MUL &&
      p->in.left->in.su >= 3 &&
      (busy[R0] || busy[R1]) && !busy[R2]) {
        int newreg = 2;
        /*
         * We need to do a reg-reg change to free r1 or r0.
         * We should move it into r2.  
         */
	if (busy[R0]) {
          printf("\ttrr\tr0,r2\n");
          --busy[R0];
	} else {
          printf("\ttrr\tr1,r2\n");
          --busy[R1];
	}
        p->in.right->tn.rval = newreg;
        ++busy[R2];
        return(1);
    }
#ifndef NASA_FIX_01_24_95
    if ((ro == NAME || ro == OREG) && lo == OREG &&
      p->in.left->in.su >= 3 &&
      (busy[R0] || busy[R1]) && !busy[R2]) {
        int newreg = 2;
        /*
         * We need to do a reg-reg change to free r1 or r0.
         * We should move it into r2.  
         */
	if (busy[R0]) {
          printf("\ttrr\tr0,r2\n");
          --busy[R0];
	} else {
          printf("\ttrr\tr1,r2\n");
          --busy[R1];
	}
    	p->in.left->tn.rval = newreg;
        ++busy[R2];
        return(1);
    }
#endif /* NASA_FIX_01_24_95 */
#if 0
    if (ro == REG && lo == UNARY MUL &&
      p->in.left->in.su >= 3 &&
      (busy[R0] || busy[R1])) {
	order(p->in.right, INTEMP);
    	return(1);
    }
#endif
#endif /* SPR_04_18_95 */
    if (lo == UNARY MUL) {
	offstar(p->in.left->in.left);
	return(1);
    }
    if (lo == FLD && p->in.left->in.left->in.op == UNARY MUL) {
	offstar(p->in.left->in.left->in.left);
	return(1);
    }
/* FLD patch */
    if (lo == FLD
	    && p->in.right->in.op != ICON
	    && p->in.right->in.op != REG) {
	order(p->in.right, INAREG);
	return(1);
    }
/* end of FLD patch */
    if (lo != REG && ro != REG) {
	order(p->in.right, INAREG);
	return(1);
    }
#ifdef MPX
/* need to check here if reg var, if so, order into an AREG */
    if(lo == REG && !istreg(p->in.left->tn.rval)) {
	order(p->in.right, INAREG);
	return(1);
    } else {
        if(ro == REG && isfakereg(p->in.right->tn.rval) )
		order(p->in.right, INAREG);
	return(1);
    }
#else
    if(ro == REG && isfakereg(p->in.right->tn.rval) )
	order(p->in.right, INAREG);
#endif /* MPX */
#ifndef MPX
    return(0);
#endif
}

int setasop(p) register NODE   *p;
{
 /* setup for ops= */
    register    int rt, ro;

#ifndef BUG1
    if(odebug) {
	printf("setasop(%x)\n", p);
	fwalk(p, eprint, 0);
	prbusy();
    }
#endif

#ifdef MPX /* MAR24 */
 if( ttype(p->in.type, TDOUBLE|TLONG) )	/* added TLONG MAR26 */
  return(setdouble(p));
#endif
    rt = p->in.right->in.type;
    ro = p->in.right->in.op;

    if (ro == UNARY MUL && rt != CHAR) {
	offstar(p->in.right->in.left);
	return(1);
    }
    if ((rt == CHAR || rt == USHORT ||
		(ro != REG && ro != ICON && ro != NAME && ro != OREG))) {
	order(p->in.right, INAREG | INBREG);
	return(1);
    }

/*
* DJK:
* #%&*(&*(&$#%& SEL machine has unusable byte and short logical
* instructions (they don't touch top bits of a register)
*/
    if (dope[p->in.op] & BITFLG && ro != REG && rt != INT && rt != UNSIGNED) {
	order(p->in.right, INAREG | INBREG);
	return(1);
    }

#ifndef MAR24
 /*
  * find mem += 2^n instruction
  */
#ifdef FEB2692
    if ((p->in.op == ASG PLUS || p->in.op == INCR)
#else
    if ((p->in.op == ASG PLUS )
#endif
	    && p->in.left->in.op == UNARY MUL
	    && p->in.type != DOUBLE
	    && p->in.type != LONG
	    && p->in.type != FLOAT
	    && p->in.right->in.op == ICON
#ifdef AUG231993
	    && (ispow2(p->in.right->tn.lval) >= 0) ) {
#else
	    && (ispow2(p->in.right->tn.lval > 0 ? p->in.right->tn.lval :
    	      -p->in.right->tn.lval) >= 0) ) {
#endif
#ifndef BUG1
		if (odebug)
		    printf("setasop - found mem += 2^n, order left\n");
#endif
		if (p->in.left->in.left->in.op == OREG)
		    return(0);
		offstar(p->in.left->in.left);
		oreg2(p->in.left);
		return(1);
	}

#endif

 /*
  * find mem += reg instruction
  */
#ifdef ON26FEB92
    if ((p->in.op == ASG PLUS || p->in.op == ASG MINUS ||
      p->in.op == INCR || p->in.op == DECR)
#else
    if ((p->in.op == ASG PLUS || p->in.op == ASG MINUS)
#endif
	    && p->in.type != DOUBLE
	    && p->in.type != LONG
	    && p->in.type != FLOAT
	    && p->in.left->in.op != FLD
	    && ro != REG) {

	order(p->in.right, INAREG);
	return(1);
    }

    p = p->in.left;
    if (p->in.op == FLD)
	p = p->in.left;

    switch (p->in.op) {

	case REG:
	case ICON:
	case NAME:
	case OREG:
	    return(0);

	case UNARY MUL:
	    if (p->in.left->in.op == OREG)
		return(0);
	    else
#ifndef BUG1
		if (odebug)
		    printf("setasop - found UNARY MUL, order left\n");
#endif
		offstar(p->in.left);
#ifndef MAR24
		oreg2(p);
#endif
	    return(1);

    }
    cerror("illegal setasop");  /* no return */
    return(0);                  /* stop warning error */
}

int         crs2lab = 999999;	/* GOULD CSD */

int get2lab()
{
    return(crs2lab--);
}

void deflab(l) int l;
{
/*    printf("L%d\tequ\t$\n", l); */
    printf("L%d\tcequ\t$\n", l);
}

/* Old (Powernode) version of genargs().  From UTX/32 2.0. */
/* Generate code to put args on stack.                     */

void genargs(p, ptemp) register NODE    *p, *ptemp;
{
    NODE       *pasg;
    NODE       *parg;
    NODE	*psv;
    register    int align;
    register    int size;
    register TWORD  type;

 /* generate code for the arguments */

#ifndef BUG1
    if (odebug) {
	printf("genargs( %x, %x)\n ", p);
	fwalk(p, eprint, 0);
	printf("\t");  prbusy();
	printf("genargs() ptemp:\n");
	fwalk(ptemp, eprint, 0);
    }
#endif

    if (p->in.op == CM) {
	genargs(p->in.left, ptemp);
	p->in.op = FREE;
	p = p->in.right;
    }
    pasg = talloc();


    /*  There are 2 general cases of arguments to deal with. They   */
    /*  are:  ordinary structure-typed args, and simple args 	    */
    /* 	(doubleword or less). */
    /*  The next "if" statement identify  which case we are dealing */
    /*  with and branches to the appropriate section.               */

    if(p->in.op == STARG) {
	goto smallstarg;
    } else {	
	goto simplearg;
    }

smallstarg:	/* This section only deals with reasonably sized */
		/* STAGRS.  Most STARGS should go thru here.     */

	size = p->stn.stsize;
	align = p->stn.stalign;
	if (p->in.left->in.op == ICON) {
	    p->in.op = FREE;
	    p = p->in.left;
	}
	else {
    /* make it look beautiful... */
	    p->in.op = UNARY MUL;
	    canon(p);		/* turn it into an oreg */
	    if (p->in.op != OREG) {
		offstar(p->in.left);
		canon(p);
		if (p->in.op != OREG) {
		    offstar(p->in.left);
		    canon(p);
		    if (p->in.op != OREG)
			cerror("stuck starg");
		}
	    }
	}

	pasg->in.op = STASG;
	pasg->stn.stsize = size;
	pasg->stn.stalign = align;
	pasg->in.right = p;
	SETOFF(ptemp->tn.lval, align < ALINT / SZCHAR ? ALINT / SZCHAR : align);
	pasg->in.left = tcopy(ptemp);

 /*
  * the following line is done only with the knowledge
  * that it will be undone by the STASG node,
  * with the offset (lval) field retained
  */

#ifndef BUG1
	if(odebug) {
	   printf("genargs() with smallarg before OREG:\n");
	   printf("genargs() p:\n");
	   fwalk(p, eprint, 0);
	   printf("genargs() pasg:\n");
	   fwalk(pasg, eprint, 0);
	   printf("genargs() ptemp:\n");
	   fwalk(ptemp, eprint, 0);
	}
#endif

	if (p->in.op == OREG)
	    p->in.op = REG;		/* only for temporaries */
	if (size & 3) {
	    size &= ~3;
	    size += 4;
	}
	pasg->in.rall = NOPREF;
	ptemp->in.rall = NOPREF;

#ifndef BUG1
	if(odebug) {
	   printf("genargs() with smallarg calling order:\n");
	   fwalk(pasg, eprint, 0);
	   printf("\t");  prbusy();
	   printf("genargs() ptemp:\n");
	   fwalk(ptemp, eprint, 0);
	}
#endif

	order(pasg, FOREFF);
	ptemp->tn.lval += size;
	goto out;


simplearg:

	pasg->in.op = ASSIGN;
	pasg->in.rall = NOPREF;
#ifndef FORT
	if (p->in.type == FLOAT || p->in.type == DOUBLE) {
	    pasg->in.type = DOUBLE;
	    ptemp->in.type = DOUBLE;
	    SETOFF(ptemp->tn.lval, (size = (SZDOUBLE / SZCHAR)));
	}
#else /* FORT */
	if (p->in.type == DOUBLE) {
	    pasg->in.type = DOUBLE;
	    ptemp->in.type = DOUBLE;
	    SETOFF(ptemp->tn.lval, (size = SZDOUBLE / SZCHAR));
	}
	else if (p->in.type == FLOAT) {
	    pasg->in.type = FLOAT;
	    ptemp->in.type = FLOAT;
	    SETOFF(ptemp->tn.lval, (size = SZDOUBLE / SZCHAR));
	}
	else if (p->in.type == LONG) {
	    pasg->in.type = LONG;
	    ptemp->in.type = LONG;
	    SETOFF(ptemp->tn.lval, (size = SZLONG/ SZCHAR));
	}
#endif /* NOT FORT */
	else {
	    pasg->in.type = INT;
	    ptemp->in.type = INT;
	    size = SZINT / SZCHAR;
	}
	pasg->in.right = p;
	pasg->in.left = tcopy(ptemp);

	pasg->in.rall = NOPREF;
	ptemp->in.rall = NOPREF;

#ifndef BUG1
	if(odebug) {
	   printf("genargs() with simparg calling order:\n");
	   fwalk(pasg, eprint, 0);
	   printf("\t");  prbusy();
	   printf("genargs() ptemp:\n");
	   fwalk(ptemp, eprint, 0);
	}
#endif

	order(pasg, FOREFF);
	ptemp->tn.lval += size;
	/* goto out; FALL THROUGH */

out:

#ifndef BUG1
	if(odebug) {
	   printf("genargs(%x, %x) returning\n");
	   fwalk(pasg, eprint, 0);
	   printf("\t");  prbusy();
	   printf("genargs() ptemp:\n");
	   fwalk(ptemp, eprint, 0);
	}
#endif
	/* stop the errors */
	;

}

int argsize(p) register NODE   *p;
{
    register    int off;
    register int al,sz;
    NODE *pp;				/* node with CM to nail */

    if (p->in.op == CM) {
	pp = p;
	off = argsize(p->in.left);
	p = p->in.right;
    }
    else {
	pp = NIL;
	off = 0;
    }
    if (p->in.type == LONG || p->in.type == DOUBLE || p->in.type == FLOAT) {
	al = 8;
	sz = al;
    }
    else {
	if (p->in.op == STARG) {
	    if(p->stn.stsize > MAXARGSIZE/SZCHAR) {
		/* Actual arg will be pointer to a copy of real */
		/* argument in fartemp.                         */
		sz = 4;
		al = sz;
	    } else {
		al = p->stn.stalign < 4 ? 4 : p->stn.stalign;
		sz = ((p->stn.stsize + 3) / 4) *4;
	    }
	}
	else {
	    al = 4;
	    sz = al;
	}
    }

    SETOFF (off, al);
    if ((p = pp) != NIL) {
	p->in.stalign = off;		/* remember end of stuff to left */
    }
    off += sz;
    return (off);
}

#ifndef BUG1
void prbusy()
{
	register int i;

	printf("busy[] = ");
	for(i=0; i<REGSZ; ++i) {
		printf(" %d", busy[i]);
	}
	printf("\n");
}
#endif

#ifdef MPX /* MAR24 */
int setdouble( p ) register NODE *p;
{
 /* setup for asg ops on doubles */
 /* get right in temp and left in */
 /* reg, as 32/27 has no reg-to-reg */
 /* floating point instructions.    */
 int ro, lo;
 NODE *p2, t;
#ifndef BUG1
 if(xdebug) printf("setdouble(%x)\n", p);
#endif
 ro = p->in.right->in.op;
 lo = p->in.left->in.op;

 if(ro == OREG && p->tn.rval == R1) {
  /* Move R1 to another register, as */
  /* R0,R1 pair will probably be needed. */
#ifndef BUG1
 if(xdebug) printf("setdouble(%x) ordering out of r1\n", p);
#endif
  p2 = tcopy(p->in.left);
  p2->in.op = REG;
  order(p2, INBREG);
  p->in.left->tn.rval = p2->tn.rval;
  reclaim(p2, RNULL, 0);
  return(1);
 }
 if(lo == UNARY MUL && ro != UNARY MUL) {
/* UNARY needs to go to reg2, because we will need R0 & R1 */
    rallo(p->in.left->in.left, R2);
  offstar(p->in.left->in.left);
  oreg2(p->in.left);
  if(p->in.left->in.op != OREG) {
   cerror("setdouble: cant reduce U*");
  }
  return(1);
 }
 if(ro == UNARY MUL && lo != UNARY MUL) {
/* UNARY needs to go to reg2, because we will need R0 & R1 */
    rallo(p->in.right->in.left, R2|MUSTDO);
  offstar(p->in.right->in.left);
  oreg2(p->in.right);
  if(p->in.right->in.op != OREG) {
   order(p->in.right, INAREG|INTAREG);
  }
  return(1);
 }
 if(ro != NAME && ro != OREG && ro != ICON) {
  order(p->in.right, INTEMP);
  return(1);
 }
 if(lo != REG) {
  /* 1. rewrite as left = left op= right; */
  /* 2. get middle part in register pair */
  /* 3. go again    */
  p2 = tcopy(p);
  p->in.op = ASSIGN;
  reclaim(p->in.right, RNULL, 0);
  p->in.right = p2;
  order(p2->in.left, INAREG);
  return(1);
 }
 cerror("illegal setdouble");
 return(0); /* shut up warnings */
}
#endif
