/* treemgr.h */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

/* $Id: treemgr.h,v 1.6 2021/07/01 03:00:13 jbev Exp $	*/

/* 
	This file contains items removed from common.h for
	the PCO port.
*/

/*
 * $Log: treemgr.h,v $
 * Revision 1.6  2021/07/01 03:00:13  jbev
 * Add missing external.
 *
 * Revision 1.5  2019/01/31 22:03:56  jbev
 * Update for Linux
 *
 * Revision 1.4  1996/03/20 23:43:30  jbev
 * Use O/S malloc function for alpha, not internal function.
 * More mods for alpha port.
 *
 * Revision 1.3  1996/03/20 21:35:50  jbev
 * Mods for alpha port.
 *
 * Revision 1.2  1995/03/06 19:18:32  jbev
 * Malloc tree node table instead of hard coding size.
 * Allow XTTval  and X2TTval to set node tree table size.
 * Add new option XJ and X2J to inhibit _ being prepended to names.
 * Correct XT[DS]val options for setting table sizes.
 *
 */

#include <string.h>

NODE       *lastfree;	/* pointer to last free node; (for allocator) */

void tinit()
{			/* initialize expression tree search */

    NODE       *p;

    for (p = nodep; p <= &nodep[TREESIZE - 1]; ++p)
	p->in.op = FREE;
    lastfree = nodep;
}

#define TNEXT(p) (p == &nodep[TREESIZE - 1] ? nodep : p + 1)

NODE       *talloc()
{
    NODE       *p, *q;

    q = lastfree;
    for (p = TNEXT(q); p != q; p = TNEXT(p))
	if (p->in.op == FREE)
	    return(lastfree = p);

    cerror("out of tree space; simplify expression");
    return(0);
}

void tcheck()
{		/* ensure that all nodes have been freed */
    NODE       *p;

    if (!nerrors)
	for (p = nodep; p <= &nodep[TREESZ - 1]; ++p) {
	    if (p->in.op != FREE) {
#ifndef BUG1
        extern int tdebug;
		if(tdebug) {
			printf("tcheck():  wasted space\n");
			fwalk(p, eprint, 0);
		}
#endif
		p->in.op = FREE;
	    }
#ifdef ONEPASS
	    p->in.rall = NOPREF;
#endif /* ONEPASS */
    }
    tinit();
    freetstr();
}

void tfree(p) NODE  *p;
{
 /* free the tree p */
    extern void tfree1();

    if (p->in.op != FREE)
	walkf(p, tfree1);
}

void tfree1(p) NODE *p;
{
    if (p == 0)
	cerror("freeing blank tree!");
    else
	p->in.op = FREE;
}

#define	NTSTRBUF	40
#define	TSTRSZ		2048
char        itstrbuf[TSTRSZ];
char       *tstrbuf[NTSTRBUF] =
{
    itstrbuf
};
char      **curtstr = tstrbuf;
int         tstrused;

char       *tstr(cp)
register char  *cp;
{
    register int    i = strlen(cp);
    register char  *dp;

    if (tstrused + i >= TSTRSZ) {
	if (++curtstr >= &tstrbuf[NTSTRBUF])
	    cerror("out of temporary string space");
	tstrused = 0;
	if (*curtstr == 0) {
	    dp = (char *) domalloc(TSTRSZ);
	    if (dp == 0)
		cerror("out of memory (tstr)");
	    *curtstr = dp;
	}
    }
    strcpy(dp = *curtstr + tstrused, cp);
    tstrused += i + 1;
    return(dp);
}

