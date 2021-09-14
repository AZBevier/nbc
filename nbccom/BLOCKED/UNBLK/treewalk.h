/* treewalk.h */
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
 
/*	@(#) (Gould) $Header: /u/nbc/nbccom/RCS/treewalk.h,v 1.1 1995/01/27 20:56:20 jbev Exp $		 */
 
/* 
	This file contains items removed from common.h for
	the PCO port.
*/
#ifdef MPX
static nwalkf();
#endif
 
fwalk(t, f, down) register NODE    *t;
int(*f)();
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
 
static(*fcn)();
walkf(t, f) register NODE  *t;
int(*f)();
{
    register(*sfcn)() = fcn;
    register    opty = optype(t -> in.op);
    fcn = f;
    if (opty != LTYPE)
	nwalkf(t -> in.left);
    if (opty == BITYPE)
	nwalkf(t -> in.right);
    (*fcn)(t);
    fcn = sfcn;
}
 
static nwalkf(t) register NODE *t;
{
    register    opty;
 
    opty = optype(t -> in.op);
    if (opty != LTYPE)
	nwalkf(t -> in.left);
    if (opty == BITYPE)
	nwalkf(t -> in.right);
    (*fcn)(t);
}
 
#ifndef BUG1
tprint(t) TWORD     t;
{		/* output a nice description of the type of t */
 
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
 
/*
 * 	(c) Copyright 1986 Gould Inc.
 * 	    All Rights Reserved.
 */
