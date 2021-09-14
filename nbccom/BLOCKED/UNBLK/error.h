/* error.h */
 
/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */
 
/*	@(#) (Gould) $Header: /u/nbc/nbccom/RCS/error.h,v 1.2 1995/02/02 19:34:50 jbev Exp $	      */
 
/* 
	This file contains items removed from common.h for
	the PCO port.
*/
 
#ifdef FORT
#undef BUFSTDERR
#endif
#ifndef ONEPASS
#undef BUFSTDERR
#endif
#ifndef EXIT
#define EXIT exit
#endif
 
int         nerrors = 0; /* number of errors */
int         Wflag = 0;	/* Non-zero means do not print warnings */
 
 /* VARARGS1 */
uerror(s, a) char  *s;
{
/*
 * nonfatal error message
 * the routine where is different for pass 1 and pass 2;
 *  it tells where the error took place
 */
    ++nerrors;
    where('u');
    fprintf(stderr, s, a);
    fprintf(stderr, "\n");
#ifdef BUFSTDERR
    fflush(stderr);
#endif
    if (nerrors > 30)
	cerror("too many errors");
}
 
 /* VARARGS1 */
cerror(s, a, b, c) char    *s;
{				/* compiler error: die */
    fflush(stdout);
    where('c');
    if (nerrors && nerrors <= 30) {	/* give the compiler the benefit of the doubt */
	fprintf(stderr, "cannot recover from earlier errors: goodbye!\n");
    }
    else {
	fprintf(stderr, "compiler error: ");
	fprintf(stderr, s, a, b, c);
	fprintf(stderr, "\n");
    }
#ifdef BUFSTDERR
    fflush(stderr);
#endif
    EXIT(1);
}
 
 /* VARARGS1 */
werror(s, a, b) char   *s;
{				/* warning */
    if (Wflag)
	return;
    where('w');
    fprintf(stderr, "warning: ");
    fprintf(stderr, s, a, b);
    fprintf(stderr, "\n");
#ifdef BUFSTDERR
    fflush(stderr);
#endif
}
 
