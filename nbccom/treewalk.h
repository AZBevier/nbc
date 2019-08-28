/* treewalk.h */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

/* $Header: /bulk2/simhv/nbc-master/nbccom/RCS/treewalk.h,v 1.3 2019/01/31 22:04:36 jbev Exp $ */

/*
 * $Log: treewalk.h,v $
 * Revision 1.3  2019/01/31 22:04:36  jbev
 * Update for Linux
 *
 * Revision 1.2  1996/03/21 23:53:35  jbev
 * Just some cleanup.
 *
 */

/* 
	This file contains items removed from common.h for
	the PCO port.
*/

#ifdef MPX
static void nwalkf();
#endif

void fwalk(t, f, down) register NODE    *t;
int(*f)();
int down;
{
    int         down1, down2;

more: 
    down1 = down2 = 0;

    (*f)(t, down, &down1, &down2);

    switch (optype(t -> in.op)) {

	case BITYPE: 
	    fwalk(t -> in.left, f, down1);
	    t = t -> in.right;
	    down = down2;
	    goto more;

	case UTYPE: 
	    t = t -> in.left;
	    down = down1;
	    goto more;
    }
}

static int (*fcn)();

void walkf(t, f) register NODE  *t;
int (*f)();
{
    register int (*sfcn)() = fcn;
    register int opty = optype(t -> in.op);
    fcn = f;
    if (opty != LTYPE)
	nwalkf(t -> in.left);
    if (opty == BITYPE)
	nwalkf(t -> in.right);
    (*fcn)(t);
    fcn = sfcn;
}

static void nwalkf(t) register NODE *t;
{
    register    int opty;

    opty = optype(t -> in.op);
    if (opty != LTYPE)
	nwalkf(t -> in.left);
    if (opty == BITYPE)
	nwalkf(t -> in.right);
    (*fcn)(t);
}

#ifndef BUG1
void tprint(t) TWORD     t;
{	/* output a nice description of the type of t */

    static char    *tnames[] = {
	"undef", "farg", "char", "short",
	"int", "long", "float", "double",
	"strty", "unionty", "enumty", "moety",
	"uchar", "ushort", "unsigned", "ulong",
    };

    for (;; t = DECREF(t)) {

	if (ISPTR(t))
	    printf("PTR ");
	else
	    if (ISFTN(t))
		printf("FTN ");
	    else
		if (ISARY(t))
		    printf("ARY ");
		else {
		    printf("%s", tnames[t]);
		    return;
		}
    }
}
#endif

