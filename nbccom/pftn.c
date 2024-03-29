/* pftn.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid = "$Id: pftn.c,v 1.9 2019/01/31 22:01:15 jbev Exp $";
#endif

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

/*
 * $Log: pftn.c,v $
 * Revision 1.9  2019/01/31 22:01:15  jbev
 * Update for Linux
 *
 * Revision 1.8  1997/01/22 18:28:07  jbev
 * Correct pointer/integer problem with error messages.
 * Only on Alpha because of 64 bit pointers and 32 bit ints.
 *
 * Revision 1.7  1996/10/26 22:29:03  jbev
 * Fix for Alpha Port
 * l.
 *
 * Revision 1.6  1996/03/20 21:36:39  jbev
 * Mods for alpha port.
 *
 * Revision 1.5  1995/04/05 23:14:10  jbev
 * Do not emit redefinition warning if not debugging.
 *
 * Revision 1.4  1995/03/06  19:18:32  jbev
 * Malloc tree node table instead of hard coding size.
 * Allow XTTval  and X2TTval to set node tree table size.
 * Add new option XJ and X2J to inhibit _ being prepended to names.
 * Correct XT[DS]val options for setting table sizes.
 *
 */

#include "mfile1.h"

extern int gdebug;
extern unsigned int    offsz;
int         entered_symbol;

struct      instk
{
    int         in_sz;		/* size of array element */
    int         in_x;		/* current index for structure member
				   in structure initializations */
    int         in_n;		/* number of initializations seen */
    int         in_s;		/* sizoff */
    int         in_d;		/* dimoff */
    TWORD       in_t;		/* type */
    int         in_id;		/* stab index */
    int         in_fl;		/* flag which says if this level
				   is controlled by {} */
    OFFSZ       in_off;		/* offset of the beginning of this level */
} instack[10], *pstk;

 /* defines used for getting things off of the initialization stack */
struct symtab  *relook();

#ifndef BUG1
int         ddebug = 0;
#endif

static int LocalUniqid = REGSZ+1;
static int GlobalUniqid = 1;
static int stkvarnum = 0;

struct symtab  *mknonuniq();

void defid(q, class) NODE   *q; int class;
{
    register struct symtab *p;
    int         idp;
    TWORD       type;
    TWORD       stp;
    int         scl;
    int         dsym;
    int         ddef;
    int         slev;
    int         temp;

    if (q == NIL)
	return;			/* an error was detected */

    if (q < nodep || q >= &nodep[TREESIZE])
	cerror("defid call");

    idp = q->tn.rval;

    if (idp < 0)
	cerror("tyreduce");
    p = &stab[idp];

#ifndef BUG1
    if (ddebug) {
	printf("defid( %s (%d), ", p->sname, idp);
	tprint(q->in.type);
	printf(", %s, (%d,%d) ), level %d\n",
    	  scnames(class), q->fn.cdim, q->fn.csiz, blevel);
	prstab(idp);
    }
#endif

    fixtype(q, class);

    if(forcealign != 0)  {
	if(class != STNAME && class != UNAME) {
		uerror("Misplaced ALIGN directive ignored.");
		forcealign = 0;
	}
    }

    type = q->in.type;
    class = fixclass(class, type);

    stp = p->stype;
    slev = p->slevel;

#ifndef BUG1
    if (ddebug) {
	printf("	modified to ");
	tprint(type);
	printf(", %s\n", scnames(class));
	printf("	previous def'n: ");
	tprint(stp);
	printf(", %s, (%d,%d) ), level %d\n", scnames(p->sclass), p->dimoff, p->sizoff, slev);
    }
#endif

    if (stp == FTN && p->sclass == SNULL)
	goto enter;
 /* name encountered as function, not yet defined */
    if (stp == UNDEF || stp == FARG) {
	if (blevel == 1 && stp != FARG)
	    switch (class) {

		default:
		    if (!(class & FIELD))
			uerror("declared argument %s is missing", p->sname);
		case MOS:
		case STNAME:
		case MOU:
		case UNAME:
		case MOE:
		case ENAME:
		case TYPEDEF:
		    ;
	    }
	goto enter;
    }

    if (type != stp)
	goto mismatch;
 /* test (and possibly adjust) dimensions */
    dsym = p->dimoff;
    ddef = q->fn.cdim;
    for (temp = type; temp & TMASK; temp = DECREF(temp)) {
	if (ISARY(temp)) {
	    if (dimtab[dsym] == 0)
		dimtab[dsym] = dimtab[ddef];
	    else
		if (dimtab[ddef] != 0 && dimtab[dsym] != dimtab[ddef]) {
		    goto mismatch;
		}
	    ++dsym;
	    ++ddef;
	}
    }

 /* check that redeclarations are to the same structure */
    if ((temp == STRTY || temp == UNIONTY || temp == ENUMTY) && p->sizoff != q->fn.csiz
	    && class != STNAME && class != UNAME && class != ENAME) {
	goto mismatch;
    }

    scl = (p->sclass);

#ifndef BUG1
    if (ddebug) {
	printf("	previous class: %s\n", scnames(scl));
    }
#endif

    if (class & FIELD) {
 /* redefinition */
	if (!falloc(p, class & FLDSIZ, 1, NIL)) {
    /* successful allocation */
	    psave(idp);
	    return;
	}
 /* blew it: resume at end of switch... */
    }

    else
	switch (class) {

	    case EXTERN:
		switch (scl) {
		    case STATIC:
		    case USTATIC:
			if (slev == 0)
			    return;
			break;
		    case EXTDEF:
		    case EXTERN:
		    case FORTRAN:
		    case UFORTRAN:
			return;
		}
		break;

	    case STATIC:
		if (scl == USTATIC || (scl == EXTERN && blevel == 0)) {
		    p->sclass = STATIC;
		    if (ISFTN(type))
			curftn = idp;
		    return;
		}
		break;

	    case USTATIC:
		if (scl == STATIC || scl == USTATIC)
		    return;
		break;

	    case LABEL:
		if (scl == ULABEL) {
		    p->sclass = LABEL;
		    deflab(p->offset);
		    return;
		}
		break;

	    case TYPEDEF:
		if (scl == class)
		    return;
		break;

	    case UFORTRAN:
		if (scl == UFORTRAN || scl == FORTRAN)
		    return;
		break;

	    case FORTRAN:
		if (scl == UFORTRAN) {
		    p->sclass = FORTRAN;
		    if (ISFTN(type))
			curftn = idp;
		    return;
		}
		break;

	    case MOU:
	    case MOS:
		if (scl == class) {
		    if (oalloc(p, &strucoff))
			break;
		    if (class == MOU)
			strucoff = 0;
		    psave(idp);
		    return;
		}
		break;

	    case MOE:
		if (scl == class) {
		    if (p->offset != strucoff++)
			break;
		    psave(idp);
		}
		break;

	    case EXTDEF:
		if (scl == EXTERN) {
		    p->sclass = EXTDEF;
		    if (ISFTN(type))
			curftn = idp;
		    return;
		}
		break;

	    case STNAME:
	    case UNAME:
	    case ENAME:
		if (scl != class)
		    break;
		if(forcealign > 0) {
			if(dimtab[p->sizoff + 1] != ALSTRUCT)
			    uerror("ALIGN directive redeclares another");
			else
			    dimtab[p->sizoff + 1] = forcealign;
			forcealign = 0;
		}
		if (dimtab[p->sizoff] == 0)
		    return;	/* previous entry just a mention */
		break;

	    case ULABEL:
		if (scl == LABEL || scl == ULABEL)
		    return;
	    case PARAM:
	    case AUTO:
	    case REGISTER:
		;		/* mismatch.. */

	}

mismatch:
#ifndef BUG1
	if(ddebug) printf("        mismatch hit\n");
#endif

 /* allow nonunique structure/union member names */

    if (class == MOU || class == MOS || class & FIELD) {/* make a new entry */
	int        *memp;
	p->sflags |= SNONUNIQ;	/* old entry is nonunique */
 /* determine if name has occurred in this structure/union */
	for (memp = &paramstk[paramno - 1];
		 /* while */ *memp >= 0 && stab[*memp].sclass != STNAME
		&& stab[*memp].sclass != UNAME;
		 /* iterate */ --memp) {
	    char       *cname, *oname;
	    if (stab[*memp].sflags & SNONUNIQ) {
		int         k;
		cname = p->sname;
		oname = stab[*memp].sname;
		if (cname != oname)
		    goto diff;
		uerror("redeclaration of: %s", p->sname);
		break;
	diff:   continue;
	    }
	}
	p = mknonuniq(&idp);	/* update p and idp to new entry */
	goto enter;
    }
    if (blevel > slev && class != EXTERN && class != FORTRAN &&
	    class != UFORTRAN && !(class == LABEL && slev >= 2)) {
	q->tn.rval = idp = hide(p);
	p = &stab[idp];
	goto enter;
    }
    uerror("redeclaration of %s", p->sname);
    if (class == EXTDEF && ISFTN(type))
	curftn = idp;
    return;

enter: 				/* make a new entry */

#ifndef BUG1
    if (ddebug)
	printf("	new entry made\n");
#endif
    /*
     * Allow TYPEDEF symbol to be added as an id even though it's
     * type is undefined.  This change still restricts an actual
     * definition of the symbol but allows for the definition of
     * of symbols in terms of its name... PNR# 10601.
     */
    if ((type == UNDEF) && (class != TYPEDEF))
	uerror("void type for %s", p->sname);
    p->stype = type;
    p->sclass = class;
    p->slevel = blevel;
    entered_symbol |= 1 << blevel;
    p->offset = NOOFFSET;
    p->suse = lineno;
    if (class == STNAME || class == UNAME || class == ENAME) {
	p->sizoff = curdim;
	dstash(0);			/* size */
	dstash(-1);			/* index to members of str or union */
#ifndef BUG1
	if(ddebug)
		printf("defid: forcealign = %d\n", forcealign);
#endif
	if(forcealign > ALSTRUCT)	/* alignment */
		dstash(forcealign);
	else
		dstash(ALSTRUCT);
	forcealign = 0;
	dstash(idp);
    }
    else {
	switch (BTYPE(type)) {
	    case STRTY:
	    case UNIONTY:
	    case ENUMTY:
		p->sizoff = q->fn.csiz;
		break;
	    default:
		p->sizoff = BTYPE(type);
	}
    }

 /* copy dimensions */

    p->dimoff = q->fn.cdim;

 /* allocate offsets */
    if (class & FIELD) {
	falloc(p, class & FLDSIZ, 0, NIL);		/* new entry */
	psave(idp);
    }
    else
	switch (class) {

	    case AUTO:
		oalloc(p, &autooff);
#ifndef NOCAID
#ifdef XXXX_CAID
    		printf("*STK%d.%d .stk %s ", ftnno, stkvarnum++, p->sname);
    		tprint(p->stype);
    		printf(" LOC%d+%db\n", ftnno, 32 + (p->offset/SZCHAR));
#endif
#endif
	    case PARAM:
		p->uniqid = LocalUniqid++;
#ifdef TWOPASS
			if( class != PARAM )
				StabInfoPrint(p);
#endif
		if( CanBeLNAME(p->stype) )
			p->optflags = (class == PARAM) ? IsPNAME : IsLNAME;
		break;

	    case STATIC:
	    case EXTDEF:
		p->uniqid = GlobalUniqid++;
		p->offset = getlab();
#ifdef TWOPASS
		StabInfoPrint(p);
#endif
		if (ISFTN(type))
		    curftn = idp;
		break;
	    case USTATIC:	/* happens for: static func(); */
		p->uniqid = GlobalUniqid++;
#ifdef TWOPASS
			StabInfoPrint(p);
#endif
		break;	
	    case ULABEL:
	    case LABEL:
		p->offset = getlab();
		p->slevel = 2;
		entered_symbol |= 1 << 2;
		if (class == LABEL) {
		    locctr(PROG);
		    deflab(p->offset);
		}
		break;
	    case EXTERN:
	    case UFORTRAN:
	    case FORTRAN:
		p->uniqid = GlobalUniqid++;
		p->offset = getlab();
		p->slevel = 0;
		entered_symbol |= 1;
#ifdef TWOPASS
			StabInfoPrint(p);
#endif
		break;
	    case MOU:
	    case MOS:
		oalloc(p, &strucoff);
		if (class == MOU)
		    strucoff = 0;
		psave(idp);
		break;

	    case MOE:
		p->offset = strucoff++;
		psave(idp);
		break;
	    case REGISTER:
		regvar -= cisreg(type);
		p->offset = regvar + 1;
		p->uniqid = LocalUniqid++;
		if (blevel == 1)
		    p->sflags |= SSET;
		if (regvar < minrvar)
		    minrvar = regvar;
#ifdef TWOPASS
			/* don't print stab info for params here - its
			 * in the wrong place, namely before the FBEGIN
			 */
			if( blevel != 1 )
				StabInfoPrint(p);
#endif
#ifndef NOCAID
#ifdef XXXX_CAID
    		printf("*STK%d.%d .stk %s ", ftnno, stkvarnum++, p->sname);
    		tprint(p->stype);
    		printf(" REG%d\n", p->offset);
#endif
#endif
		break;
	}

 /* user-supplied routine to fix up new definitions */
 /* defer stab processing of arrays until after any possible */
 /* initializations are seen.  */

    if( ! (ISARY( p->stype )) )
	outstab(p);

#ifndef BUG1
    if (ddebug) {
	printf("       final stab entry:\n");
	prstab(p - stab);
    }
#endif

}

# ifdef TWOPASS
# ifdef LINT
void StabInfoPrint(p) struct symtab *p; {}
#else
void StabInfoPrint(p)
	register struct symtab *p;
{
	int id;		/* unique identifier to pass to the optimizer */
	TWORD type;	/* type to pass to the optimizer */
	int op;		/* op that will go on tree nodes */
	NODE *t;	/* Tree node for ENUM kludge */

	type = p->stype;
	id   = p->uniqid;

	switch(p->sclass)
	{
		case PARAM:
			op = PNAME;
			break;

		case AUTO:
			op = LNAME;
			break;

		case REGISTER:
			/* Register variables are known by unique id cookie;
			 * all others are known by register number
			 */
			if( !IsRegVar(p->offset) )
				id = p->offset;
			op = REG;
			break;

		case STATIC:
			if( p->slevel > 1 )
				id = - p->offset;
			op = NAME;
			break;

		default:
			op = NAME;
			break;
	}

	if( BTYPE(type) == ENUMTY )
	{
		/* Pass 1 always lies about ENUMs, even on the lhs of
		 * assignments.  We must do likewise.
		 */

		t = talloc();
		t->in.op = op;
		t->in.type = type;
		t->fn.csiz = p->sizoff;
		econvert(t);
		t->in.op = FREE;
		type = t->in.type;
	}

	if(p->slevel > 1 && p->sclass == STATIC) {
	    printf("%c%d\t%d\t%d\tL%d\n", STABINFO, id, type, op, id);
	} else {
	    printf("%c%d\t%d\t%d\t%s\n", STABINFO, id, type, op,
				exname(p->sname, p));
	}
}
# endif /* LINT */
# endif /* TWOPASS */

void psave(i)
int i;
{
    if (paramno >= PARAMSZ) {
	cerror("parameter stack overflow");
    }
    paramstk[paramno++] = i;
}

void ftnend()
{				/* end of function */
    if (retlab != NOLAB) {	/* inside a real function */
	efcode();
	LocalUniqid = REGSZ+1;
    }
    checkst(0);
    retstat = 0;
    tcheck();
    curclass = SNULL;
    brklab = contlab = retlab = NOLAB;
    flostat = 0;
    if (nerrors == 0) {
	if (psavbc != &asavbc[0])
	    cerror("bcsave error");
	if (paramno != 0)
	    cerror("parameter reset error");
	if (swx != 0)
	    cerror("switch error");
    }
    psavbc = &asavbc[0];
    paramno = 0;
    autooff = AUTOINIT;
    minrvar = regvar = MAXRVAR;
    reached = 1;
    swx = 0;
    swp = swtab;
    stkvarnum = 0;
    locctr(DATA);
}

void dclargs()
{
    register    int i, j;
    register struct symtab *p;
    register NODE  *q;
    int temp;

    argoff = ARGINIT;
#ifndef BUG1
    if (ddebug > 2)
	printf("dclargs()\n");
#endif
    for (i = 0; i < paramno; ++i) {
	if ((j = paramstk[i]) < 0)
	    continue;
	p = &stab[j];
#ifndef BUG1
	if (ddebug > 2) {
	    printf("\t%s (%d) ", p->sname, j);
	    tprint(p->stype);
	    printf("\n");
	}
#endif
	if (p->stype == FARG) {
	    q = block(FREE, NIL, NIL, INT, 0, INT);
	    q->tn.rval = j;
	    defid(q, PARAM);
	}
	FIXARG(p);	/* local arg hook, eg. for sym. debugger */
	if(p->sclass == REGISTER && p->stype == FLOAT) {
		temp = p->offset;
		p->sclass = PARAM;
		p->offset = NOOFFSET;
		oalloc(p, &argoff);
		p->offset = temp;
		p->sclass = REGISTER;
	} else {
		oalloc(p, &argoff);
	}
#ifndef BUG1
	if(edebug) {
		printf("dclargs(): for end: \n");
		prstab(p - stab);
	}
#endif

    } /* end "for" loop */

    cendarg();
    locctr(PROG);
    defalign(ALINT);
    ftnno++;
    bfcode(paramstk, paramno);
    paramno = 0;
}

NODE       *rstruct(idn, soru) int idn, soru;
{		/* reference to a structure or union, with no definition */
    register struct symtab *p;
    register NODE  *q;
    p = &stab[idn];
    switch (p->stype) {

	case UNDEF:
    def:
	    q = block(FREE, NIL, NIL, 0, 0, 0);
	    q->tn.rval = idn;
	    q->in.type = (soru & INSTRUCT) ? STRTY :
    	      ((soru & INUNION) ? UNIONTY : ENUMTY);
	    defid(q, (soru & INSTRUCT) ? STNAME :
    	      ((soru & INUNION) ? UNAME : ENAME));
	    break;

	case STRTY:
	    if (soru & INSTRUCT)
		break;
	    goto def;

	case UNIONTY:
	    if (soru & INUNION)
		break;
	    goto def;

	case ENUMTY:
	    if (!(soru & (INUNION | INSTRUCT)))
		break;
	    goto def;

    }
    stwart = instruct;
    return(mkty(p->stype, 0, p->sizoff));
}

void moedef(idn) int idn;
{
    register NODE  *q;

    q = block(FREE, NIL, NIL, MOETY, 0, 0);
    q->tn.rval = idn;
    if (idn >= 0)
	defid(q, MOE);
}

int bstruct(idn, soru) int idn, soru;
{		/* begining of structure or union declaration */
    register NODE  *q;

    psave(instruct);
    psave(curclass);
    psave(strucoff);
    strucoff = 0;
    instruct = soru;
    q = block(FREE, NIL, NIL, 0, 0, 0);
    q->tn.rval = idn;
    if (instruct == INSTRUCT) {
	curclass = MOS;
	q->in.type = STRTY;
	if (idn >= 0)
	    defid(q, STNAME);
    }
    else
	if (instruct == INUNION) {
	    curclass = MOU;
	    q->in.type = UNIONTY;
	    if (idn >= 0)
		defid(q, UNAME);
	}
	else {				/* enum */
	    curclass = MOE;
	    q->in.type = ENUMTY;
	    if (idn >= 0)
		defid(q, ENAME);
	}
    psave(idn = q->tn.rval);
 /* the "real" definition is where the members are seen */
    if (idn >= 0)
	stab[idn].suse = lineno;
    return(paramno - 4);
}

NODE       *dclstruct(oparam) int oparam;
{
    register struct symtab *p;
    register    int i, al, sa, j, sz, szindex;
    register TWORD  temp;
    register    int high, low;

 /* paramstack contains:
    paramstack[ oparam ] = previous instruct
    paramstack[ oparam+1 ] = previous class
    paramstk[oparam+2 ] = previous strucoff
    paramstk[ oparam+3 ] = structure name
    paramstk[ oparam+4, ... ]  = member stab indices
  */


    if ((i = paramstk[oparam + 3]) < 0) {
	szindex = curdim;
	dstash(0);			/* size */
	dstash(-1);			/* index to member names */
#ifndef BUG1
	if(ddebug)
		printf("dclstruct(): forcealign = %d\n", forcealign);
#endif
	if(forcealign > ALSTRUCT)	/* alignment */
		dstash(forcealign);
	else
		dstash(ALSTRUCT);
	forcealign = 0;
	dstash(-lineno);		/* name of structure */
    }
    else {
	szindex = stab[i].sizoff;
    }

#ifndef BUG1
    if (ddebug) {
	printf("dclstruct( %s ), szindex = %d\n",
    	  (i >= 0) ? stab[i].sname : "??", szindex);
    }
#endif
    temp = (instruct & INSTRUCT) ? STRTY :
       ((instruct & INUNION) ? UNIONTY : ENUMTY);
    stwart = instruct = paramstk[oparam];
    curclass = paramstk[oparam + 1];
    dimtab[szindex + 1] = curdim;
    al = dimtab[szindex + 2];

    high = low = 0;

    for (i = oparam + 4; i < paramno; ++i) {
	dstash(j = paramstk[i]);
	if (j < 0 || j >= SYMTSZ)
	    cerror("gummy structure member");
	p = &stab[j];
	if (temp == ENUMTY) {
	    if (p->offset < low)
		low = p->offset;
	    if (p->offset > high)
		high = p->offset;
	    p->sizoff = szindex;
	    continue;
	}
	sa = talign(p->stype, p->sizoff);
	if (p->sclass & FIELD) {
	    sz = p->sclass & FLDSIZ;
	}
	else {
	    sz = tsize(p->stype, p->dimoff, p->sizoff);
	}
	if (sz == 0) {
	    werror("illegal zero sized structure member: %s", p->sname);
	}
	if (sz > strucoff)
	    strucoff = sz;		/* for use with unions */
	SETOFF(al, sa);
 /* set al, the alignment, to the lcm of the alignments of the members */
    }
    dstash(-1);				/* endmarker */
    SETOFF(strucoff, al);

    if (temp == ENUMTY) {
	register TWORD  ty;

#ifdef ENUMSIZE
	ty = ENUMSIZE(high, low);
#else
	if ((char) high == high && (char) low == low)
	    ty = ctype(CHAR);
	else
	    if ((short) high == high && (short) low == low)
		ty = ctype(SHORT);
	    else
		ty = ctype(INT);
#endif
	strucoff = tsize(ty, 0, (int) ty);
	dimtab[szindex + 2] = al = talign(ty, (int) ty);
    }

    if (strucoff == 0)
	uerror("zero sized structure");
    dimtab[szindex] = strucoff;
    dimtab[szindex + 2] = al;
    dimtab[szindex + 3] = paramstk[oparam + 3];		/* name index */

#ifndef BUG1
    if(ddebug) {
        printf("dclstruct: before FIXSTRUCT, p - stab == %d\n", p-stab);
        prstab(p - stab);
	lookat("(dimtab + szindex)", dimtab + szindex);
	lookat("(paramstk + oparam)", paramstk + oparam);
    }
#endif

    if(dimtab[szindex + 3] >= 0)
       FIXSTRUCT(szindex, oparam); /* local hook, eg. for sym debugger */
#ifndef BUG1
    if (ddebug > 1) {
	printf("\tdimtab[%d,%d,%d] = %d,%d,%d\n", szindex, szindex + 1, szindex + 2,
		dimtab[szindex], dimtab[szindex + 1], dimtab[szindex + 2]);
	for (i = dimtab[szindex + 1]; dimtab[i] >= 0; ++i) {
	    printf("\tmember %s(%d)\n", stab[dimtab[i]].sname, dimtab[i]);
	}
    }
#endif

    strucoff = paramstk[oparam + 2];
    paramno = oparam;

    return(mkty(temp, 0, szindex));
}

/* VARARGS */
void yyerror(s) char    *s;
{				/* error printing routine in parser */
    uerror(s);
}

void yyaccpt()
{
    ftnend();
}

void ftnarg(idn) int idn;
{
    switch (stab[idn].stype) {

	case UNDEF:
    /* this parameter, entered at scan */
	    break;
	case FARG:
	    uerror("redeclaration of formal parameter, %s",
		    stab[idn].sname);
    /* fall thru */
	case FTN:
    /* the name of this function matches parm */
    /* fall thru */
	default:
	    idn = hide(&stab[idn]);
	    break;
	case TNULL:
    /* unused entry, fill it */
	    ;
    }
    stab[idn].stype = FARG;
    stab[idn].sclass = PARAM;
    psave(idn);
}

int talign(ty, s)
register unsigned int ty;
register int s;
{
 /* compute the alignment of an object with type ty, sizeoff index s */

    register    int i;
    if (s < 0 && ty != INT && ty != CHAR && ty != SHORT && ty != UNSIGNED && ty != UCHAR && ty != USHORT
#ifdef LONGFIELDS
	    && ty != LONG && ty != ULONG
#endif
	    ) {
	return(fldal(ty));
    }

    for (i = 0; i <= (SZINT - BTSHIFT - 1); i += TSHIFT) {
	switch (((unsigned)ty >> i) & TMASK) {

	    case FTN:
		cerror("compiler takes alignment of function");
	    case PTR:
		return(ALPOINT);
	    case ARY:
		continue;
	    case 0:
		break;
	}
    }

    switch (BTYPE(ty)) {

	case UNIONTY:
	case ENUMTY:
	case STRTY:
	    return((unsigned int) dimtab[s + 2]);
	case CHAR:
	case UCHAR:
	    return(ALCHAR);
	case FLOAT:
	    return(ALFLOAT);
	case DOUBLE:
	    return(ALDOUBLE);
	case LONG:
	case ULONG:
	    return(ALLONG);
	case SHORT:
	case USHORT:
	    return(ALSHORT);
	default:
	    return(ALINT);
    }
}

OFFSZ tsize(ty, d, s) TWORD   ty; int d, s;
{
 /* compute the size associated with type ty, dimoff d, and sizoff s */
 /* BETTER NOT BE CALLED WHEN t, d, and s REFER TO A BIT FIELD... */

    int         i;
    OFFSZ       mult;

    mult = 1;

    for (i = 0; i <= (SZINT - BTSHIFT - 1); i += TSHIFT) {
	switch (((unsigned)ty >> i) & TMASK) {

	    case FTN:
		uerror("function name illegal in pointer arithmetic");
	    case PTR:
		return(SZPOINT * mult);
	    case ARY:
		mult *= (unsigned int) dimtab[d++];
		continue;
	    case 0:
		break;

	}
    }

    if (dimtab[s] == 0) {
	uerror("unknown size");
	return(SZINT);
    }
    return((unsigned int) dimtab[s] * mult);
}

void inforce(n) OFFSZ    n;
{				/* force inoff to have the value n */
 /* inoff is updated to have the value n */
    OFFSZ       wb;
    register    int rest;
 /* rest is used to do a lot of conversion to ints... */

    if (inoff == n)
	return;
    if (inoff > n) {
	cerror("initialization alignment error");
    }

    wb = inoff;
    SETOFF(wb, SZINT);

 /* wb now has the next higher word boundary */

    if (wb >= n) {		/* in the same word */
	rest = n - inoff;
#ifndef BUG1
    if(ddebug) {
printf(" 1 inforce calling vfdzero rest = %d, wd = %d, inoff = %d\n", rest, wb, inoff);
    }
#endif
	vfdzero(rest);
	return;
    }

 /* otherwise, extend inoff to be word aligned */

    rest = wb - inoff;
#ifndef BUG1
    if(ddebug) {
printf(" 2 inforce calling vfdzero rest = %d, wd = %d, inoff = %d\n", rest, wb, inoff);
    }
#endif
    vfdzero(rest);

 /* now, skip full words until near to n */

    rest = (n - inoff) / SZINT;
    zecode(rest);

 /* now, the remainder of the last word */

    rest = n - inoff;
#ifndef BUG1
    if(ddebug) {
printf(" 3 inforce calling vfdzero rest = %d, wd = %d, inoff = %d\n", rest, wb, inoff);
    }
#endif
    vfdzero(rest);
    if (inoff != n)
	cerror("inoff error");

}

void vfdalign(n) int n;
{		/* make inoff have the offset the next alignment of n */
    OFFSZ       m;

    m = inoff;
    SETOFF(m, n);
#ifndef BUG1
    if(ddebug) {
printf("vfdalign calling inforce m = %d, n = %d\n", m, n);
    }
#endif
    inforce(m);
}


#ifndef BUG1
int	idebug = 0;
#endif

int	ibseen = 0;	/* the number of } constructions which have been filled */

int	iclass;		/* storage class of thing being initialized */

int	ilocctr = 0; /* location counter for current initialization */

void beginit(curid) int curid;
{
 /* beginning of initilization; set location ctr and set type */
    register struct symtab *p;
    int         size;
    int		class;

    p = &stab[curid];

    class = p->sclass;
    if(class == STATIC || class == EXTERN || class == EXTDEF)
    	ininit = 1;

#ifndef BUG1
    if (idebug >= 3) {
	printf("beginit(%d) = %s, flags ", curid, p->sname);
	prstab(p - stab);
	printf ("\n");
    }
#endif

    iclass = p->sclass;
    if (curclass == EXTERN || curclass == FORTRAN)
	iclass = EXTERN;
    switch (iclass) {

	case EXTERN:
	case UNAME:
	    return;
	case AUTO:
	case REGISTER:
	    break;
	case EXTDEF:
	case STATIC:
#ifdef MPXMON
if (p->sclass == STATIC && p->slevel > 1) {
printf ("defining label %d\n", p->offset);
printf ("dimoff is %d\n", p->dimoff);
printf ("sizoff is %d\n", p->sizoff);
printf ("doing static init of size %d\n", p->sizoff);
	prstab(p - stab);
}
#endif
	    ilocctr = ISARY(p->stype) ? ADATA : DATA;
	    locctr(ilocctr);
#ifndef MPX
	    defalign(talign(p->stype, p->sizoff));
#else
	    /* statics and extdefs are on word boundries */
	    defalign((size = talign(p->stype, p->sizoff)) <= ALINT ? ALINT :size );
#endif
	    defnam(p);
    }

    inoff = 0;
    ibseen = 0;

    pstk = 0;

    instk(curid, p->stype, p->dimoff, p->sizoff, inoff);

}

void instk(id, t, d, s, off) OFFSZ   off; int d, s, id;
TWORD       t;
{
 /* make a new entry on the parameter stack to initialize id */

    register struct symtab *p;

    for (;;) {
#ifndef BUG1
	if (idebug)
	    printf("instk((%d, %x,%d,%d, %d)\n", id, t, d, s, off);
#endif

 /* save information on the stack */

	if (!pstk)
	    pstk = instack;
	else
	    ++pstk;

	pstk->in_fl = 0;		/* { flag */
	pstk->in_id = id;
	pstk->in_t = t;
	pstk->in_d = d;
	pstk->in_s = s;
	pstk->in_n = 0;		/* number seen */
	pstk->in_x = t == STRTY ? dimtab[s + 1] : 0;
	pstk->in_off = off;	/* offset at the beginning of this element */
 /* if t is an array, DECREF(t) can't be a field */
 /* INS_sz has size of array elements, and -size for fields */
	if (ISARY(t)) {
	    pstk->in_sz = tsize(DECREF(t), d + 1, s);
	}
	else
	    if (stab[id].sclass & FIELD) {
		pstk->in_sz = -(stab[id].sclass & FLDSIZ);
	    }
	    else {
		pstk->in_sz = 0;
	    }

	if ((iclass == AUTO || iclass == REGISTER) &&
		(ISARY(t) || t == STRTY))
	    uerror("no automatic aggregate initialization");

 /* now, if this is not a scalar, put on another element */

	if (ISARY(t)) {
	    t = DECREF(t);
	    ++d;
	    continue;
	}
	else
	    if (t == STRTY) {
		id = dimtab[pstk->in_x];
		p = &stab[id];
		if (p->sclass != MOS && !(p->sclass & FIELD))
		    cerror("insane structure member list");
		t = p->stype;
		d = p->dimoff;
		s = p->sizoff;
		off += p->offset;
		continue;
	    }
	    else
		return;
    }
}

NODE       *getstr()
{		/* decide if the string is external or an initializer, and get
		   the contents accordingly */

    register    int l, temp;
    register NODE  *p;

# ifdef TWOPASS
    struct symtab STEnt;
# endif /* TWOPASS */

    if ((iclass == EXTDEF || iclass == STATIC) && (pstk->in_t == CHAR || pstk->in_t == UCHAR) &&
	    pstk != instack && ISARY(pstk[-1].in_t)) {
 /* treat "abc" as { 'a', 'b', 'c', 0 } */
	strflg = 1;
	ilbrace();			/* simulate { */
	inforce(pstk->in_off);
 /* if the array is inflexible (not top level), pass in the size and be prepared to throw away unwanted initializers */
	lxstr((pstk - 1) != instack ? dimtab[(pstk - 1)->in_d] : 0);
 /* get the contents */
	irbrace();			/* simulate } */
	return(NIL);
    }
    else {	/* make a label, and get the contents and stash them away */
	if (iclass != SNULL) {		/* initializing */
    /* fill out previous word, to permit pointer */
	    vfdalign(ALPOINT);
	}
#ifdef MPX
	l = getlab();
	strflg = 0;
	gettmpstr(0, l);		/* get the contents */
#else /* MPX */
	temp = locctr(blevel == 0 ? ISTRNG : STRNG);    /* set up location counter */
	deflab(l = getlab());
	strflg = 0;
	lxstr(0);				/* get the contents */
	locctr(blevel == 0 ? ilocctr : temp);
#endif /* MPX */
	p = buildtree(STRING, NIL, NIL);
	p->tn.rval = -l;
# ifdef TWOPASS
	/* print out fake symbol table info for this string */
	STEnt.sclass = STATIC;
	STEnt.slevel = 2;
	STEnt.stype = p->in.type;
	STEnt.offset = l;
	STEnt.sname = "string!";
	StabInfoPrint(&STEnt);
# endif /* TWOPASS */
	return(p);
    }
}

void putbyte(v) int v;
{		/* simulate byte v appearing in a list of integer values */
    register NODE  *p;
    p = bcon(v);
    incode(p, SZCHAR);
    tfree(p);
    gotscal();
}

void endinit()
{
    register TWORD  t;
    register int d, s, n, d1;
    register struct symtab *p;

#ifndef BUG1
    if (idebug)
	printf("endinit(), inoff = %d\n", inoff);
#endif

    switch (iclass) {

	case TYPEDEF:
	    uerror("Typedefs may not have initialization");
	case EXTERN:
	case AUTO:
	case REGISTER:
	    goto out;
#ifndef DEC05
	default:
	    if (iclass == -1)
		goto out;
#endif
    }

    pstk = instack;

    t = pstk->in_t;
    d = pstk->in_d;
    s = pstk->in_s;
    n = pstk->in_n;

    if (ISARY(t)) {
	d1 = dimtab[d];

#ifndef MPXMON
	vfdalign(pstk->in_sz); /* fill out part of the last element, if needed */
#endif
	n = inoff / pstk->in_sz;	/* real number of initializers */
	if (d1 >= n) {
    /* once again, t is an array, so no fields */
	    inforce(tsize(t, d, s));
	    n = d1;
	}
	if (d1 != 0 && d1 != n)
	    uerror("too many initializers");
	if (n == 0)
	    werror("empty array declaration");
	dimtab[d] = n;
    }

    else
	if (t == STRTY || t == UNIONTY) {
    /* clearly not fields either */
	    inforce(tsize(t, d, s));
	}
	else
	    if (n > 1)
		uerror("bad scalar initialization");
 /* this will never be called with a field element... */
	    else
		inforce(tsize(t, d, s));

    paramno = 0;
#ifndef MPX /* OCT03 */
    vfdalign(ALCHAR);
#else
    vfdalign(AL_INIT);
#endif
    inoff = 0;
    iclass = SNULL;
#ifndef CAID_080293
    p = &stab[pstk->in_id];
    if (p->sclass == STATIC && p->slevel > 1) {
    	locctr(PROG);
    }
#endif
  out:
	ininit = 0;
	return;
}

void doinit(p) register NODE    *p;
{
 /* take care of generating a value for the initializer p */
 /* inoff has the current offset (last bit written) in the
  * current word being generated */

    register int sz, d, s;
    register TWORD  t;
    extern void eprint();

#ifndef BUG1
    if (idebug > 1) {
	printf("doinit(%x)\n", p);
	if(p != NIL)
		fwalk(p, eprint, 0);
    }
#endif

 /* note: size of an individual initializer is assumed to fit into an int */

    if (iclass < 0)
	goto leave;
    if (iclass == EXTERN || iclass == UNAME) {
	uerror("cannot initialize extern or union");
	iclass = -1;
	goto leave;
    }

    if (iclass == AUTO || iclass == REGISTER) {
 /* do the initialization and get out, without regard for filing out the variable with zeros, etc. */
	bccode();
	idname = pstk->in_id;
	p = buildtree(ASSIGN, buildtree(NAME, NIL, NIL), p);
	ecomp(p);
	return;
    }

    if (p == NIL)
	return;	/* for throwing away strings that have been turned into lists */

    if (ibseen) {
	uerror("} expected");
	goto leave;
    }

#ifndef BUG1
    if (idebug > 1) {
	printf("doinit(%x), middle\n", p);
	fwalk(p, eprint, 0);
    }
#endif

    t = pstk->in_t;			/* type required */
    d = pstk->in_d;
    s = pstk->in_s;
    if (pstk->in_sz < 0) {		/* bit field */
	sz = -pstk->in_sz;
    }
    else {
	sz = tsize(t, d, s);
    }

    inforce(pstk->in_off);

    p = buildtree(ASSIGN, block(NAME, NIL, NIL, t, d, s), p);
    p->in.left->in.op = FREE;
    p->in.left = p->in.right;
    p->in.right = NIL;
    p->in.left = optim(p->in.left);
#ifndef MAR21
    if (p->in.left->in.op == UNARY MINUS && 
	(p->in.left->in.type == LONG || p->in.left->in.type == DOUBLE)) {
#ifndef MYATOF
        FP_DOUBLE dd;
#endif
	p->in.left->in.op = FREE;
	p->in.left = p->in.left->in.left;
#ifdef MYATOF
	/* negate the floating point value */
        FP_NEG(&p->in.left->fpn.fpnum);
#else
        dd = p->in.left->fpn.dval;
        dd = FP_NEG(dd);
        p->in.left->fpn.dval = dd;
#endif
    }
#endif
    if (p->in.left->in.op == UNARY AND) {
	p->in.left->in.op = FREE;
	p->in.left = p->in.left->in.left;
    }
    p->in.op = INIT;

    if(optype(p->in.left->in.op) != LTYPE) {
	NODE *tp = bcon(0);
	
/*
printf("doinit(%x), != LTYPE\n", p);
fwalk(p, eprint, 0);
*/

if (iclass == STATIC || iclass == EXTDEF) {
if (p->in.left->in.op == PLUS) {
#ifdef MPX
if (p->in.left->in.left->in.op == ICON && p->in.left->in.left->tn.rval >0) {
	if( stab[p->in.left->in.left->tn.rval].sclass == EXTERN) {
uerror("cannot initialize extern definition with offset");
iclass = -1;
goto leave;
}
	/*	werror("Initializing extern with offset"); */
}
#endif
 p->in.left->in.left->tn.lval += p->in.left->in.right->tn.lval;
 tp = p->in.left->in.left;
 p->in.left->in.op = FREE;
 p->in.left->in.right->in.op = FREE;
 p->in.left = tp;
}
} else

if (iclass != EXTERN) {
	tp->in.type = p->in.left->in.type;
	tfree(p->in.left);
	p->in.left = tp;
} 
/* else
if (iclass == EXTERN && (p->in.op == PLUS || p->in.op == MINUS)) {
uerror("cannot initialize extern definition with offset");
iclass = -1;
goto leave;
}
*/
/*
printf("doinit(%x), != LTYPE\n", p);
fwalk(p, eprint, 0);
*/
    }

    if (sz < SZINT) {		/* special case: bit fields, etc. */
	if (p->in.left->in.op != ICON || p->in.left->tn.rval != NONAME)
	    uerror("bitfield, char or short initialization not an integer");
	else
	    incode(p->in.left, sz);
    }
    else
	if (p->in.left->in.op == FCON) {
#ifdef MYATOF
	    fincode(&p->in.left->fpn.fpnum, sz);
#else
	    fincode(p->in.left->fpn.dval, sz);
#endif /* MYATOF */
	}
	else {
	    cinit(optim(p), sz);
	}

    gotscal();

leave:
    tfree(p);
}

void gotscal()
{
    register    int t, ix;
    register    int n, id;
    struct symtab  *p;
    OFFSZ       temp;

    for (; pstk > instack;) {

	if (pstk->in_fl)
	    ++ibseen;

	--pstk;

	t = pstk->in_t;

	if (t == STRTY) {
	    ix = ++pstk->in_x;
	    if ((id = dimtab[ix]) < 0)
		continue;

    /* otherwise, put next element on the stack */

	    p = &stab[id];
	    instk(id, p->stype, p->dimoff, p->sizoff, p->offset + pstk->in_off);
	    return;
	}
	else
	    if (ISARY(t)) {
		n = ++pstk->in_n;
		if (n >= dimtab[pstk->in_d] && pstk > instack)
		    continue;

	/* put the new element onto the stack */

		temp = pstk->in_sz;
		instk(pstk->in_id, (TWORD) DECREF(pstk->in_t), pstk->in_d + 1, pstk->in_s,
			pstk->in_off + n * temp);
		return;
	    }

    }

}

void ilbrace()
{			/* process an initializer's left brace */
    register    int t;
    struct instk   *temp;

    temp = pstk;

    for (; pstk > instack; --pstk) {

	t = pstk->in_t;
	if (t != STRTY && !ISARY(t))
	    continue;			/* not an aggregate */
	if (pstk->in_fl) {		/* already associated with a { */
	    if (pstk->in_n)
		uerror("illegal {");
	    continue;
	}

 /* we have one ... */
	pstk->in_fl = 1;
	break;
    }

 /* cannot find one */
 /* ignore such right braces */

    pstk = temp;
}

void irbrace()
{
 /* called when a '}' is seen */

#ifndef BUG1
    if (idebug)
	printf("irbrace(): paramno = %d on entry\n", paramno);
#endif

    if (ibseen) {
	--ibseen;
	return;
    }

    for (; pstk > instack; --pstk) {
	if (!pstk->in_fl)
	    continue;

 /* we have one now */

	pstk->in_fl = 0;	/* cancel { */
	gotscal();		/* take it away... */
	return;
    }

 /* these right braces match ignored left braces: throw out */

}

int upoff(size, alignment, poff) register int  size, alignment, *poff;
{
 /*
  * update the offset pointed to by poff; return the
  * offset of a value of size `size', alignment `alignment',
  * given that off is increasing
  */

    register    int off;

#ifndef BUG1
    if(ddebug) {
	printf("upoff( %d, %d, %x:  %d):\n", size, alignment, poff, *poff);
    }
#endif
    off = *poff;
    SETOFF(off, alignment);
    if ((offsz - off) < size) {
	if (instruct != INSTRUCT)
	    cerror("too many local variables");
	else
	    cerror("Structure too large");
    }
    *poff = off + size;
#ifndef BUG1
    if(ddebug)
	printf("upoff():  updated *poff to %d\n", *poff);
#endif
    return(off);
}

int oalloc(p, poff) register struct symtab *p;
register   int *poff;
{
 /* allocate p with offset *poff, and update *poff */
    register    int al, off, tsz;
    int         noff;

#ifndef BUG1
    if(ddebug) {
	printf("oalloc(%d, poff->%d):\n", p - stab, *poff);
	prstab(p - stab);
    }
#endif

 /*
  * Floats are OK as parameters, but they are always sent as
  * doubles
  */
    if (p->sclass == PARAM && p->stype == FLOAT) {
	al = talign(DOUBLE, p->sizoff);
	noff = off = *poff;
	tsz = tsize(DOUBLE, p->dimoff, DOUBLE);
    }
    else {
	al = talign(p->stype, p->sizoff);
	noff = off = *poff;
	tsz = tsize(p->stype, p->dimoff, p->sizoff);
    }
    if (tsz == 0) {
	werror("zero sized object");
    }
#ifdef BACKAUTO
    if (p->sclass == AUTO) {
	if ((offsz - off) < tsz)
	    cerror("too many local variables");
	noff = off + tsz;
	SETOFF(noff, al);
	off = -noff;
    }
    else {
	if (p->sclass == PARAM && (tsz < SZINT || tsz > MAXARGSIZE)) {
	    off = upoff(SZINT, ALINT, &noff);
#ifndef RTOLBYTES
	    if(p->stype != STRTY && p->stype != UNIONTY)
	    	off = noff - tsz;
#endif
	}
	else {
	    off = upoff(tsz, al, &noff);
	}
    }
#else
    if (p->sclass == PARAM && (tsz < SZINT || tsz > MAXARGSIZE)) {
	off = upoff(SZINT, ALINT, &noff);
#ifndef RTOLBYTES
	if(p->stype != STRTY && p->stype != UNIONTY)
		off = noff - tsz;
#endif
    }
    else {
	off = upoff(tsz, al, &noff);
    }
#endif

    if (p->sclass != REGISTER) {
	/* in case we are allocating stack space for register arguments */
	if (p->offset == NOOFFSET)
	    p->offset = off;
	else
	    if (off != p->offset)
		return(1);
    }

    *poff = noff;

#ifndef BUG1
    if(ddebug) {
	printf("oalloc() returning: *poff = %d\n", *poff);
	prstab(p - stab);
    }
#endif

    return(0);
}

int falloc(p, w, new, pty) register struct symtab  *p;
int w, new;
NODE       *pty;
{
 /* allocate a field of width w */
 /* new is 0 if new entry, 1 if redefinition, -1 if alignment */

    register    int al, sz, type;

    type = (new < 0) ? pty->in.type : p->stype;

 /* this must be fixed to use the current type in alignments */
    switch (new < 0 ? pty->in.type : p->stype) {

	case ENUMTY:
	    {
		int         s;
		s = new < 0 ? pty->fn.csiz : p->sizoff;
		al = dimtab[s + 2];
		sz = dimtab[s];
		break;
	    }

	case CHAR:
	case UCHAR:
	    al = ALCHAR;
	    sz = SZCHAR;
	    break;

	case SHORT:
	case USHORT:
	    al = ALSHORT;
	    sz = SZSHORT;
	    break;

	case INT:
	case UNSIGNED:
	    al = ALINT;
	    sz = SZINT;
	    break;
#ifdef LONGFIELDS

	case LONG:
	case ULONG:
	    al = ALLONG;
	    sz = SZLONG;
	    break;
#endif

	default:
	    if (new < 0) {
		uerror("illegal field type");
		al = ALINT;
	    }
	    else {
		al = fldal(p->stype);
		sz = SZINT;
	    }
    }

    if (w > sz) {
	uerror("field too big");
	w = sz;
    }

    if (w == 0) {		/* align only */
	SETOFF(strucoff, al);
	if (new >= 0)
	    uerror("zero size field");
	return(0);
    }

    if (strucoff % al + w > sz)
	SETOFF(strucoff, al);
    if (new < 0) {
	if ((offsz - strucoff) < w)
	    cerror("structure too large");
	strucoff += w;		/* we know it will fit */
	return(0);
    }

 /* establish the field */

    if (new == 1) {		/* previous definition */
	if (p->offset != strucoff || p->sclass != (FIELD | w))
	    return(1);
    }
    p->offset = strucoff;
    if ((offsz - strucoff) < w)
	cerror("structure too large");
    strucoff += w;
    p->stype = type;
    fldty(p);
    return(0);
}

extern	int  stabLCSYM;	/* MPX */

void nidcl(p) NODE  *p;
{				/* handle unitialized declarations */
 /* assumed to be not functions */
    register    int class;
    register    int commflag;	/* flag for labelled common declarations */
    register struct symtab *s;
    int         sz;

    commflag = 0;

 /* compute class */
    if ((class = curclass) == SNULL) {
	if (blevel > 1)
	    class = AUTO;
	else
	    if (blevel != 0 || instruct)
		cerror("nidcl error");
	    else {		/* blevel = 0 */
		class = noinit();
		if (class == EXTERN)
		    commflag = 1;
	    }
    }
 /* hack so stab will come at as LCSYM rather than STSYM */
    if (class == STATIC) {
	stabLCSYM = 1;
    }

    defid(p, class);

    s = &stab[p->tn.rval];
    sz = -1;

#ifndef MPX
    if (class == STATIC) {
	extern int  stabLCSYM;
	char       *isitfar = "";

	if (s->sizoff) {
	    sz = tsize(s->stype, s->dimoff, s->sizoff) / SZCHAR;
	}
	stabLCSYM = 0;
	if (sz % sizeof(int))
	    sz += sizeof(int) - (sz % sizeof(int));
	if (s->slevel > 1)
	    printf("Lc%d	%smpxtern	L%d(%d)\n", s->offset,
		isitfar, s->offset, sz/4);
	else {
	    printf("%s	%smpxtern	%s,(%d)\n",
		s->sname, isitfar, exname(s->sname, s), sz/4);
	}
#else /* MPX */
	if (class == STATIC) {
    /* simulate initialization by 0 */
	    beginit(p->tn.rval);
	    endinit();
#ifndef NOCAID
    	    if (s->slevel > 1)
    		locctr(PROG);
#endif
	}
#endif /* MPX */
#ifndef MPX
    }
#endif /* MPX */
    else
	if (class == EXTDEF) {
    /* simulate initialization by 0 */
	    beginit(p->tn.rval);
	    endinit();
	}
#ifdef DEC05_JUNK
#ifdef MPX
    if (commflag || class == EXTERN)
#else
    if (commflag)
#endif /* MPX */
	commdec(p->tn.rval);
#endif /* DEC05_JUNK */
}

TWORD types(t1, t2, t3) TWORD   t1, t2, t3;
{
 /* return a basic type from basic types t1, t2, and t3 */

    TWORD       t[3], noun, adj, unsg;
    register    int i;

    t[0] = t1;
    t[1] = t2;
    t[2] = t3;

    unsg = INT;			/* INT or UNSIGNED */
    noun = UNDEF;		/* INT, CHAR, or FLOAT */
    adj = INT;			/* INT, LONG, or SHORT */

    for (i = 0; i < 3; ++i) {
	switch (t[i]) {

	    default:
	bad:
		uerror("illegal type combination");
		return(INT);

	    case UNDEF:
		continue;

	    case UNSIGNED:
		if (unsg != INT)
		    goto bad;
		unsg = UNSIGNED;
		continue;

	    case LONG:
	    case SHORT:
		if (adj != INT)
		    goto bad;
		adj = t[i];
		continue;

	    case INT:
	    case CHAR:
	    case FLOAT:
		if (noun != UNDEF)
		    goto bad;
		noun = t[i];
		continue;
	}
    }

 /* now, construct final type */
    if (noun == UNDEF)
	noun = INT;
    else
	if (noun == FLOAT) {
	    if (unsg != INT || adj == SHORT)
		goto bad;
	    return(adj == LONG ? DOUBLE : FLOAT);
	}
	else
	    if (noun == CHAR && adj != INT)
		goto bad;

 /* now, noun is INT or CHAR */
    if (adj != INT)
	noun = adj;
    if (unsg == UNSIGNED)
	return(noun + (UNSIGNED - INT));
    else
	return(noun);
}

NODE       *tymerge(typ, idp) NODE *typ, *idp;
{
 /* merge type typ with identifier idp  */

    register unsigned int  t;
    register    int i;
/*   extern void eprint(); */

#ifndef BUG1
    if(ddebug) {
	printf("tymerge entry(typ=%x, idp=%x):\n", typ, idp);
	if(typ != NIL)
		fwalk(typ, eprint, 0);
    }
#endif

    if (typ->in.op != TYPE)
	cerror("tymerge: arg 1");
    if (idp == NIL) {
#ifndef BUG1
	if(ddebug)
		printf("tymerge(): returning NIL\n");
#endif
	return(NIL);
    }

#ifndef BUG1
    if (ddebug) {
	printf("tymerge(idp=%x):\n", idp);
	fwalk(idp, eprint, 0);
    }
#endif

    idp->in.type = typ->in.type;
    idp->fn.cdim = curdim;
    tyreduce(idp);
    idp->fn.csiz = typ->fn.csiz;

    for (t = typ->in.type, i = typ->fn.cdim; t & TMASK; t = DECREF(t)) {
	if (ISARY(t))
	    dstash(dimtab[i++]);
    }

 /* now idp is a single node: fix up type */

    idp->in.type = ctype(idp->in.type);

    if ((t = BTYPE(idp->in.type)) != STRTY && t != UNIONTY && t != ENUMTY) {
	idp->fn.csiz = t;	/* in case ctype has rewritten things */
    }

#ifndef BUG1
    if(ddebug) {
	printf("tymerge() returning %x\n", idp);
	fwalk(idp, eprint, 0);
    }
#endif
    return(idp);
}

void tyreduce(p) register NODE  *p;
{

 /* build a type, and stash away dimensions, from a parse tree of the declaration */
 /* the type is build top down, the dimensions bottom up */
    register int   o, temp;
    register unsigned  int t;
    register NODE *q = p->in.left;

#ifndef BUG1
    if (ddebug) {
	printf("tyreduce entry(p=%x, q=%x):\n", p, q);
	fwalk(p, eprint, 0);
    }
#endif
    o = p->in.op;
    p->in.op = FREE;

    if (o == NAME)
	return;

    t = INCREF(p->in.type);
    if (o == UNARY CALL)
	t += (FTN - PTR);
    else
	if (o == LB) {
	    t += (ARY - PTR);
	    temp = p->in.right->tn.lval;
	    p->in.right->in.op = FREE;
	    if ((temp == 0) & (p->in.left->tn.op == LB))
		uerror("Null dimension");
	}

    p->in.left->in.type = t;
    tyreduce(p->in.left);

    if (o == LB)
	dstash(temp);

#ifndef BUG1
    q = p->in.left;
    if (ddebug) {
	printf("tyreduce return 0 (p=%x, q=%x):\n", p, q);
	fwalk(p, eprint, 0);
    }
#endif
    p->tn.rval = p->in.left->tn.rval;
    p->in.type = p->in.left->in.type;
#ifndef BUG1
    if (ddebug) {
	printf("tyreduce return (p=%x, q=%x):\n", p, q);
	fwalk(p, eprint, 0);
    }
#endif

}

void fixtype(p, class) register NODE    *p; int class;
{
    register unsigned int  t, type;
    register  int  mod1, mod2;
 /* fix up the types, and check for legality */

    if ((type = p->in.type) == UNDEF)
	return;
    if ( (class&FIELD) && (class&FLDSIZ)==SZINT) {
	p->in.type = UNSIGNED;
#ifndef BUG1
	if(ddebug) printf("fixtype: modified field[32]\n");
#endif
	return;
    }
    if (mod2 = (type & TMASK)) {
	t = DECREF(type);
	while (mod1 = mod2, mod2 = (t & TMASK)) {
	    if (mod1 == ARY && mod2 == FTN) {
		uerror("array of functions is illegal");
		type = 0;
	    }
	    else
		if (mod1 == FTN && (mod2 == ARY || mod2 == FTN)) {
		    uerror("function returns illegal type");
		    type = 0;
		}
	    t = DECREF(t);
	}
    }

 /* detect function arguments, watching out for structure declarations */
 /* for example, beware of f(x) struct [ int a[10]; } *x; { ... } */
 /* the danger is that "a" will be converted to a pointer */

    if (class == SNULL && blevel == 1 && !(instruct & (INSTRUCT | INUNION)))
	class = PARAM;
    if (class == PARAM || (class == REGISTER && blevel == 1)) {
	if (type == FLOAT) {
    /*   type = DOUBLE;  DJK says: FLOAT ARGS are OK! */
    /* Naturally, they are still passed as double. */
	}
	else
	    if (ISARY(type)) {
		++p->fn.cdim;
		type += (PTR - ARY);
	    }
	    else
		if (ISFTN(type)) {
		    werror("a function is declared as an argument");
		    type = INCREF(type);
		}

    }

    if (instruct && ISFTN(type)) {
	uerror("function illegal in structure or union");
	type = INCREF(type);
    }
    p->in.type = type;
}

int uclass(class) register  int class;
{
 /* give undefined version of class */
    if (class == SNULL)
	return(EXTERN);
    else
	if (class == STATIC)
	    return(USTATIC);
	else
	    if (class == FORTRAN)
		return(UFORTRAN);
	    else
		return(class);
}

int fixclass(class, type) int class; TWORD     type;
{

 /* first, fix null class */

    if (class == SNULL) {
	if (instruct & INSTRUCT)
	    class = MOS;
	else
	    if (instruct & INUNION)
		class = MOU;
	    else
		if (blevel == 0)
		    class = EXTDEF;
		else
		    if (blevel == 1)
			class = PARAM;
		    else
			class = AUTO;

    }

 /* now, do general checking */

    if (ISFTN(type)) {
	switch (class) {
	    default:
		uerror("function has illegal storage class");
	    case AUTO:
		class = EXTERN;
	    case EXTERN:
	    case EXTDEF:
	    case FORTRAN:
	    case TYPEDEF:
	    case STATIC:
	    case UFORTRAN:
	    case USTATIC:
		;
	}
    }

    if (class & FIELD) {
	if (!(instruct & INSTRUCT))
	    uerror("illegal use of field");
	else
		if((class&FLDSIZ) == SZINT)
			class = MOS;
	return(class);
    }

    switch (class) {

	case MOU:
	    if (!(instruct & INUNION))
		uerror("illegal class");
	    return(class);

	case MOS:
	    if (!(instruct & INSTRUCT))
		uerror("illegal class");
	    return(class);

	case MOE:
	    if (instruct & (INSTRUCT | INUNION))
		uerror("illegal class");
	    return(class);

	case REGISTER:
	    if (blevel == 0)
		uerror("illegal register declaration");
	    else
		if (regvar >= MINRVAR && cisreg(type))
		    return(class);
	    if (blevel == 1)
		return(PARAM);
	    else
		return(AUTO);

	case AUTO:
	case LABEL:
	case ULABEL:
	    if (blevel < 2)
		uerror("illegal class");
	    return(class);

	case PARAM:
	    if (blevel != 1)
		uerror("illegal class");
	    return(class);

	case UFORTRAN:
	case FORTRAN:
#ifdef NOFORTRAN
	    NOFORTRAN;	/* a condition which can regulate the FORTRAN usage */
#endif
	    if (!ISFTN(type))
		uerror("fortran declaration must apply to function");
	    else {
		type = DECREF(type);
		if (ISFTN(type) || ISARY(type) || ISPTR(type)) {
		    uerror("fortran function has wrong type");
		}
	    }
	case STNAME:
	case UNAME:
	case ENAME:
	case EXTERN:
	case STATIC:
	case EXTDEF:
	case TYPEDEF:
	case USTATIC:
	    return(class);

	default:
	    cderror("illegal class: %d", class);
	    return(0);

    }
}

struct symtab  *mknonuniq(idindex) int *idindex;
{
 /* locate a symbol table entry for */
 /* an occurrence of a nonunique structure member name */
 /* or field */
    register    int i;
    register struct symtab *sp;
    char       *p, *q;

    sp = &stab[i = *idindex];		/* position search at old entry */
    while (sp->stype != TNULL) {	/* locate unused entry */
	if (++i >= SYMTSZ) {		/* wrap around symbol table */
	    i = 0;
	    sp = stab;
	}
	else
	    ++sp;
	if (i == *idindex)
	    cerror("Symbol table full");
    }
    sp->sflags = SNONUNIQ | SMOS;
    p = sp->sname;
    q = stab[*idindex].sname;		/* old entry name */
    sp->sname = stab[*idindex].sname;
#ifndef BUG1
    if (ddebug) {
	printf("\tnonunique entry for %s from %d to %d\n",
		q, *idindex, i);
    }
#endif
    *idindex = i;
    return(sp);
}

int lookup(name, s) char   *name; int s;
{
 /* look up name: must agree with s w.r.t. STAG, SMOS and SHIDDEN */

    register char  *p, *q;
    int         i, j, ii;
    register struct symtab *sp;

 /* compute initial hash index */
#ifndef BUG1
    if (ddebug > 2) {
	printf("lookup( %s, %d ), stwart=%d, instruct=%d\n", name, s, stwart, instruct);
    }
#endif

    i = 0;
    i = (int) name;
    i = i % SYMTSZ;
    sp = &stab[ii = i];

    for (;;) {				/* look for name */

	if (sp->stype == TNULL) {	/* empty slot */
	/* set STAG, SMOS if needed, turn off all others */
	    sp->sflags = s;	
	    sp->sname = name;
	    sp->stype = UNDEF;
	    sp->sclass = SNULL;
	    return(i);
	}
	if ((sp->sflags & (STAG | SMOS | SHIDDEN)) != s)
	    goto next;
	p = sp->sname;
	q = name;
	if (p == q)
	    return(i);
next:
	if (++i >= SYMTSZ) {
	    i = 0;
	    sp = stab;
	}
	else
	    ++sp;
	if (i == ii)
	    cerror("symbol table full");
    }
}

#ifndef checkst
/* if not debugging, make checkst a macro */
void checkst(lev)
int lev
{
    register int    s, i, j;
    register struct symtab *p, *q;
    char mymsg[48];

    for (i = 0, p = stab; i < SYMTSZ; ++i, ++p) {
	if (p->stype == TNULL)
	    continue;
	j = lookup(p->sname, p->sflags & (SMOS | STAG));
	if (j != i) {
	    q = &stab[j];
	    if (q->stype == UNDEF ||
		    q->slevel <= p->slevel) {
		cerror("check error: %s", q->sname);
	    }
	}
	else {
	    if (p->slevel > lev) {
#ifdef alpha_fix
		cerror("%s check at level %d", p->sname, lev);
#else
		sprintf(mymsg, "%s check at level %d", p->sname, lev);
		cerror(mymsg);
#endif
	    }
	}
    }
}
#endif

struct symtab  *relook(p) register struct symtab   *p;
{
 /* look up p again, and see where it lies */

    register struct symtab *q;

#ifndef BUG1
    if(ddebug) {
	printf("relook(p = 0x%x):->stab[%d]\n", p, p - stab);
	prstab(p - stab);
    }
#endif

 /* I'm not sure that this handles towers of several
    hidden definitions in all cases */

    q = &stab[lookup(p->sname, p->sflags & (STAG | SMOS | SHIDDEN))];

#ifndef BUG1
    if(ddebug) {
	printf("relook() after lookup q = 0x%x->stab[%d]\n", q, q - stab);
	prstab(q - stab);
    }
#endif

 /* make relook always point to either p or an empty cell */

    if (q->stype == UNDEF) {
	q->stype = TNULL;
	q->sflags = 0;
	q->offset = 0;
	goto out;
    }
    while (q != p) {
	if (q->stype == TNULL)
	    break;
	if (++q >= &stab[SYMTSZ])
	    q = stab;
    }

  out:
#ifndef BUG1
    if(ddebug) {
	printf("relook() returning q = 0x%x->stab[%d]\n", q, q - stab);
	prstab(q - stab);
    }
#endif

    return(q);
}

void clearst(lev) int lev;
{
    /* clear entries of internal scope from the symbol table */
    register struct symtab *p, *q, *r;
    register int    temp, rehash;

#ifndef BUG1
    if(ddebug) {
	printf("clearst(lev=%d):\n");
    }
#endif

    /* djk adds quick noclear code */
    if ((temp = ~((2 << lev) - 1)) && !(entered_symbol & temp)) {
	return;
    }
    entered_symbol &= ~temp;
    temp = lineno;
    aobeg();

    /* first, find an empty slot to prevent newly hashed
     * entries from being slopped into... */

    for (q = stab; q < &stab[SYMTSZ]; ++q) {
	if (q->stype == TNULL)
	    goto search;
    }

    cerror("symbol table full");

search:
    p = q;

    for (;;) {
	if (p->stype == TNULL) {
	    rehash = 0;
	    goto next;
	}
	lineno = p->suse;
	if (lineno < 0)
	    lineno = -lineno;
	if ( (p->slevel > lev) && ((p->sflags & SMOS) == 0) ) {
	    /* must clobber */
	    if (p->stype == UNDEF || (p->sclass == ULABEL && lev < 2)) {
		lineno = temp;
		uerror("%s undefined_pftn", p->sname); /* VOID 07/29/91 JCB */
	    }
	    else
		aocode(p);
#ifndef BUG1
	    if (ddebug) {
		printf("removing %s from stab[ %d], flags %x level %d\n",
			p->sname, p - stab, p->sflags, p->slevel);
		prstab(p - stab);
	    }
#endif
	    if (p->sflags & SHIDES)
		unhide(p);
	    p->stype = TNULL;
	    p->sflags = 0;
	    p->offset = 0;
	    p->optflags = 0;
	    rehash = 1;
	    goto next;
	}
	if (rehash) {
	    if ((r = relook(p)) != p) {
		movestab(r, p);
		if( (p->sflags & SMOS) !=0) {
			/* copy to preserve hashing rules, but dont */
			/* clobber.  Fixes "illegal member" problem */
			/* caused by dangling dimtab indices.       */

			p->sflags |= SNONUNIQ;
			r->sflags |= SNONUNIQ;
		} else {
			p->stype = TNULL;
			p->sflags = 0;
			p->offset = 0;
			if(p == &stab[curftn])
				curftn = r - stab;
		}
	    }
	}
next:
	if (++p >= &stab[SYMTSZ])
	    p = stab;
	if (p == q)
	    break;
    }
    lineno = temp;
    aoend();

#ifndef BUG1
    if(ddebug) {
	printf("clearst() returning\n");
    }
#endif
}

void movestab(p, q) register struct symtab  *p, *q;
{
    int         k;
 /* structure assignment: *p = *q; */
    p->stype = q->stype;
    p->sclass = q->sclass;
    p->slevel = q->slevel;
    entered_symbol |= 1 << q->slevel;
    p->offset = q->offset;
    p->sflags = q->sflags;
    p->dimoff = q->dimoff;
    p->sizoff = q->sizoff;
    p->suse = q->suse;
    p->sname = q->sname;
}


int hide(p) register struct symtab *p;
{
    register struct symtab *q;
    for (q = p + 1;; ++q) {
	if (q >= &stab[SYMTSZ])
	    q = stab;
	if (q == p)
	    cerror("symbol table full");
	if (q->stype == TNULL)
	    break;
    }
    movestab(q, p);
    p->sflags |= SHIDDEN;
    q->sflags = (p->sflags & (SMOS | STAG)) | SHIDES;
    if (hflag && gdebug)
	werror("%s redefinition hides earlier one", p->sname);
#ifndef BUG1
    if (ddebug)
	printf("	%d hidden in %d\n", p - stab, q - stab);
#endif
    return(idname = q - stab);
}

void unhide(p) register struct symtab   *p;
{
    register struct symtab *q;
    register    int s, j;

#ifndef BUG1
    if(ddebug) {
	printf("unhide() p = 0x%x->stab[%d]\n", p, p - stab);
	prstab(p - stab);
    }
#endif

    s = p->sflags & (SMOS | STAG);
    q = p;

    for (;;) {

	if (q == stab)
	    q = &stab[SYMTSZ - 1];
	else
	    --q;

	if (q == p)
	    break;

	if ((q->sflags & (SMOS | STAG)) == s) {
	    if (p->sname == q->sname) {
#ifndef BUG1
		if (ddebug) {
		    printf("unhide uncovered %d from %d\n", q - stab, p - stab);
		    prstab(q - stab);
		    prstab(p - stab);
		}
#endif
		q->sflags &= ~SHIDDEN;
		return;
	    }
	}

    }
    cerror("unhide fails");
}

#ifndef BUG1
void prstab(i)
int i;
{
	struct symtab *q;

#ifdef MPX
if (i<0) {
printf("prstab is negative %x\n", -i);
return;
}
#endif
	q = &stab[i];
	printf("stab[%d]: ", i);
	if(q->sname)
		printf("%s", q->sname);
	else
		printf("NONAME");
	printf(", flags: ");
	prsflags(q->sflags);
	printf("\n        class: %s, type: ", scnames(q->sclass));
	tprint( q->stype );
	printf(", suse: %d\n", q->suse);
	printf("        level: %d, dim: %d, sizoff: %d, offset: %d\n",
		q->slevel, q->dimoff, q->sizoff, q->offset);
}

void prsflags(f)
int	f;
{
	int	mask = 1;
	char	*s, *sep;

	if(f == 0) {
		printf("NULL");
		return;
	}

	sep = "";

	for(mask=1; mask < 0x4000000; mask <<= 1) {
		if( f & mask) {
			switch(mask) {
			case SMOS:	s = "SMOS";	break;
			case SHIDDEN:	s = "SHIDDEN";	break;
			case SHIDES:	s = "SHIDES";	break;
			case SSET:	s = "SSET";	break;
			case SREF:	s = "SREF";	break;
			case SNONUNIQ:	s = "SNONUNIQ";	break;
			case STAG:	s = "STAG";	break;
			default:	printf("0x%x==???", mask);
					sep = "|";
					continue;
			}

			printf("%s%s", sep, s);
			sep = "|";
		}
	}
}

void lookat(str, ptr)
char *str;
register YYSTYPE *ptr;
{
	register int i;

	for(i = (-6); i < 4; i++) {
		printf("%s[%d] = 0x%x\n", str, i, ptr[i]);
	}
}

void pr_strdim(idx)
int	idx;
{
	struct dimhdr {
		int	dh_strsize;	/* struct/union size in bits */
		int	dh_mbridx;	/* index of members in dimtab */
		int	dh_align;	/* alignment, in bits */
		int	dh_tagidx;	/* stab idx of tagname */
	} *dhp;

	register int i, bound;

	if(idx < 0 || idx >= DIMTABSZ) {
		printf("pr_strdim(%d): index out of bounds\n");
		return;
	}

	dhp = (struct dimhdr *) &dimtab[idx];
	printf("pr_strdim(idx = %d):\n", idx);
	printf("  strsize: %d bits, mbridx: %d, align: %d bits, tagidx: %d\n",
	    dhp->dh_strsize, dhp->dh_mbridx, dhp->dh_align, dhp->dh_tagidx);
	fflush(stdout);

        /*------  after midas crash ------------*/

        i = dhp->dh_tagidx;
        if( i < 0 )
                printf("no tagname\n");
        else
                if(i >= SYMTSZ)
                        printf("bad tagname stab idx\n");
                else {
                        printf("tag: ");
                        prstab(i);
                }
        printf("\n");

        /*  Now the members */

        i = dhp->dh_mbridx;
        bound = i + 100;
        if(i < 0)
                printf("no members defined\n");
        else {
                if(i >= DIMTABSZ)
                        printf("bad mbr index in dimhdr !!!\n");
                else {
                        printf("members:\n");
                        for( ; dimtab[i] >= 0 && i < bound; ++i) {
                                printf("member %d: ", i - dhp->dh_mbridx);
                                if(dimtab[i] >= SYMTSZ)
                                        printf("bad member stab idx %d !!!\n",
                                                dimtab[i]);
                                else
                                        prstab(dimtab[i]);
                        }
                }
        }

        return;
}
#endif
