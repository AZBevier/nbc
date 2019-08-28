/* error.h */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

/*	$Header: /bulk2/simhv/nbc-master/nbccom/RCS/error.h,v 1.8 2019/02/24 17:17:07 jbev Exp $	      */

#ifndef mpx
#include <stdlib.h>
#endif

#ifndef ONEPASS
#undef BUFSTDERR
#endif
#ifndef EXIT
#define EXIT exit
#endif

int         nerrors = 0; /* number of errors */
int         Wflag = 0;	/* Non-zero means do not print warnings */
extern void where();

/* VARARGS1 */
void uerror(s, a)		/* second parameter must be a pointer */
char  *s;
char *a;
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

/*
 * This version is required for the alpha because a pointer
 * is 64 bits and an int is 32 bits.  It causes an error.
 */
/* VARARGS1 */
void uderror(s, a)		/* second parameter must be an integer */
char  *s;
int    a;
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
void cerror(s, a, b)
char    *s;
char    *a;
char    *b;
{				/* compiler error: die */
    fflush(stdout);
    where('c');
    if (nerrors && nerrors <= 30) {
	/* give the compiler the benefit of the doubt */
	fprintf(stderr, "cannot recover from earlier errors: goodbye!\n");
    } else {
	fprintf(stderr, "compiler error: ");
	fprintf(stderr, s, a, b);
	fprintf(stderr, "\n");
    }
#ifdef BUFSTDERR
    fflush(stderr);
#endif
    EXIT(1);
}

/*
 * This version is required for the alpha because a pointer
 * is 64 bits and an int is 32 bits.  It causes an error.
 */
/* VARARGS1 */
void cderror(s, a, b)
char    *s;
int	a;
int	b;
{				/* compiler error: die */
    fflush(stdout);
    where('c');
    if (nerrors && nerrors <= 30) {
	/* give the compiler the benefit of the doubt */
	fprintf(stderr, "cannot recover from earlier errors: goodbye!\n");
    } else {
	fprintf(stderr, "compiler error: ");
	fprintf(stderr, s, a, b);
	fprintf(stderr, "\n");
    }
#ifdef BUFSTDERR
    fflush(stderr);
#endif
    EXIT(1);
}

/* VARARGS1 */
void werror(s, a, b)
char   *s;
char   *a;
char   *b;
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

/*
 * This version is required for the alpha because a pointer
 * is 64 bits and an int is 32 bits.  It causes an error.
 */
/* VARARGS1 */
void wderror(s, a, b)
char   *s;
int	a;
int	b;
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

