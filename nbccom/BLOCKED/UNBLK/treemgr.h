/* treemgr.h */
 
/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */
 
/* $Id: treemgr.h,v 1.2 1995/03/06 19:18:32 jbev Exp $	*/
 
/* 
	This file contains items removed from common.h for
	the PCO port.
*/
 
/* $Log: treemgr.h,v $
 * Revision 1.2  1995/03/06  19:18:32  jbev
 * Malloc tree node table instead of hard coding size.
 * Allow XTTval  and X2TTval to set node tree table size.
 * Add new option XJ and X2J to inhibit _ being prepended to names.
 * Correct XT[DS]val options for setting table sizes.
 *
 */
 
NODE       *lastfree;	/* pointer to last free node; (for allocator) */
 
tinit()
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
 
tcheck()
{		/* ensure that all nodes have been freed */
    NODE       *p;
 
    if (!nerrors)
	for (p = nodep; p <= &nodep[TREESZ - 1]; ++p) {
	    if (p->in.op != FREE) {
#ifndef BUG1
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
 
tfree(p) NODE  *p;
{
 /* free the tree p */
    extern tfree1();
 
    if (p->in.op != FREE)
	walkf(p, tfree1);
}
 
tfree1(p) NODE *p;
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
	    dp = (char *) malloc(TSTRSZ);
	    if (dp == 0)
		cerror("out of memory (tstr)");
	    *curtstr = dp;
	}
    }
    strcpy(dp = *curtstr + tstrused, cp);
    tstrused += i + 1;
    return(dp);
}
 
