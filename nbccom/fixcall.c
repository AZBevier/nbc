/* fixcall.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid = "$Header: /bulk2/simhv/nbc-master/nbccom/RCS/fixcall.c,v 1.3 2019/01/31 21:47:03 jbev Exp $";
#endif

/*
 * $Log: fixcall.c,v $
 * Revision 1.3  2019/01/31 21:47:03  jbev
 * Update for Linux
 *
 * Revision 1.2  1996/03/22 00:07:35  jbev
 * Cleanup for Alpha Port.
 *
 */

#include "mfile1.h"
#include <string.h>

struct spclrtn {
	char	sr_name[12];	/* name of routine we can replace */
	short	sr_op;		/* type of tree node to use */
	short	sr_narg;	/* expected number of args to fcn */
	TWORD	sr_tresult;	/* type of resulting operation */
	TWORD	sr_targ1;	/* type of first arg */
	TWORD	sr_targ2;	/* type of second arg */
};

static struct spclrtn Spclrtn[] = {
#ifdef MPX
	{"LCD",		UMULP,	1,	LONG,	INCREF(LONG), 0},
	{"STCD",	ASGP,	2,	LONG,	INCREF(LONG), LONG},
	{"LCW",		UMULP,	1,	INT,	INCREF(INT), 0},
	{"STCW",	ASGP,	2,	INT,	INCREF(INT), INT},
	{"LCH",		UMULP,	1,	SHORT,	INCREF(SHORT), 0},
	{"STCH",	ASGP,	2,	SHORT,	INCREF(SHORT), SHORT},
	{"LCB",		UMULP,	1,	CHAR,	INCREF(CHAR), 0},
	{"STCB",	ASGP,	2,	CHAR,	INCREF(CHAR), CHAR},
	{"LCRA",	UANDP,	1,	INCREF(INT), INCREF(INT), 0},
#else /* MPX */
	{"asm_lwp",	UMULP,	1,	INT,	INCREF(INT), 0},
	{"asm_stwp",	ASGP,	2,	INT,	INCREF(INT), INT},
	{"asm_lhp",	UMULP,	1,	SHORT,	INCREF(SHORT), 0},
	{"asm_sthp",	ASGP,	2,	SHORT,	INCREF(SHORT), SHORT},
#ifndef RETIRED
	{"asm_lbp",	UMULP,	1,	CHAR,	INCREF(CHAR), 0},
	{"asm_stbp",	ASGP,	2,	CHAR,	INCREF(CHAR), CHAR},
#endif /* RETIRED */
	{"asm_lap",	UANDP,	1,	INCREF(INT), INCREF(INT), 0},
#endif /* MPX */
	{0,		0,	0,	0,	0,	0},
};

 /*
  * replace certain known routine calls with
  * special tree operations.
  */
int fixcall (p)
NODE *p;
{
    struct symtab *symp;
    NODE *ap1, *ap2;
    register struct spclrtn *sp;
    register char *name;
    NODE *cast();
    TWORD typ;
    NODE *block(), *optim();
/*    void eprint(); */
#ifndef BUG2
    extern int edebug;
#endif

    if (p->in.op == CALL)
    {
	ap1 = p->in.right;
    }
    else
    {
	if (p->in.op == UNARY CALL)
	{
	    ap1 = NIL;
	}
	else
	{
	    return (0);
	}
    }

#ifndef BUG2
    if (edebug)
    {
	printf ("fixcall looking at symp:\n");
	fwalk (p, eprint, 0);
        printf(" in.left->in.left = %x\n",p->in.left->in.left);
        printf(" in.left->in.right = %x\n",p->in.left->in.right);
    }
#endif
#ifdef MPX
    if (p->in.left->in.left)return (0);
#endif
    symp = &stab[p->in.left->tn.rval];
    name = symp->sname;

    for (sp = &Spclrtn[0];; ++sp)
    {
	if (sp->sr_name[0] == 0)
	    return (0);

	if (*name == sp->sr_name[0] && strcmp (name, sp->sr_name) == 0)
	    break;
    }

#ifndef BUG2
    if (edebug)
    {
	printf ("fixcall changing:\n");
	fwalk (p, eprint, 0);
    }
#endif

    p->in.left->in.op = FREE;
    p->in.op = sp->sr_op;
    p->in.type = sp->sr_tresult;

    p->in.right = p->in.left = NIL;

    switch (sp->sr_narg)
    {
	case 3:
	    cerror ("fixcall table error");
	    break;

	case 2:
	    if (ap1 == NIL || ap1->in.op != CM)
	    {
	      mismatch:
		uerror ("Arg mismatch on builtin function");
		return (0);
	    }
	    ap2 = ap1->in.right;
	    ap1->in.op = FREE;
	    ap1 = ap1->in.left;

	    typ = sp->sr_targ2;

	    if (ap2->in.type != typ)
		ap2 = cast (ap2, typ);

	    if (ISPTR(typ))
	    {
		typ = DECREF(typ);
		ap2 = block(UNARY MUL, ap2, 0, typ, 0, typ);

		if (ap2->in.type != typ)
		    ap2 = cast (ap2, typ);
	    }

	    p->in.right = optim (ap2);

	    /* drop through */

	case 1:
	    if (ap1 == NIL || ap1->in.op == CM)
		goto mismatch;

	    typ = sp->sr_targ1;

	    if (ap1->in.type != typ)
		ap1 = cast (ap1, typ);

	    if (ISPTR(typ))
	    {
		typ = DECREF(typ);
		ap1 = block(UNARY MUL, ap1, 0, typ, 0, typ);

		if (ap1->in.type != typ)
		    ap1 = cast (ap1, typ);
	    }

	    p->in.left = optim (ap1);
	    break;

	case 0:
	    if (ap1 != NIL)
		goto mismatch;
	    break;
    }

#ifndef BUG2
    if (edebug)
    {
	printf (".... to:\n");
	fwalk (p, eprint, 0);
    }
#endif

    return (1);
}

