/* print.h */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

/* $Header: /bulk2/simhv/nbc-master/nbccom/RCS/print.h,v 1.3 2019/01/31 22:01:15 jbev Exp $ */

/*
 * $Log: print.h,v $
 * Revision 1.3  2019/01/31 22:01:15  jbev
 * Update for Linux
 *
 * Revision 1.2  1996/03/22 00:05:49  jbev
 * Cleanup for Alpha port.
 *
 */

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.

    2nd pass print routines only.  Print routines common to both passes
    are located in the common.h and treewalk.h files.
*/

#include <string.h>

#ifndef BUG4
char        Ftype[] =
 "TCHAR|TSHORT|TINT|TLONG|TFLOAT|TDOUBLE|TPOINT|TUCHAR|TUSHORT|TUNSIGNED|TULONG|TPTRTO|TANY|TSTRUCT";

char        Fcookie[] =
            "FOREFF|INAREG|INTAREG|INBREG|INTBREG|FORCC|INNAME|INCON|INFLD|INOREG|||INTEMP|FORARG|FORREW||FORZCC";

char        Fshape[] =
            "SANY|SAREG|STAREG|SBREG|STBREG|SCC|SNAME|SCON|SFLD|SOREG|STARNM|STARREG|SHINTEMP||SWADD|..special..|SZCC";
char       *Fspecial[] =
{
    "SZERO", "SONE", "SMONE", "SCCON",
    "SSCON", "SOCON", "SPOW2", "SCPOW2",
    "SICON", "SHPOW2", "SHCPOW2",
    "SBPOW2", "SBCPOW2", "SACON", /* Bit Instructs Added, UA Instructs  */
    0,
};

char        Fresult[] =
            "RLEFT|RRIGHT|RESC1|RESC2|RESC3|||||||RESCC|RNOP|RESUPPER";
char        Frall[1];

/* this can be a problem with some pre-processors MPX */
#ifdef JUNK
#define IS(s,f) if(strcmp(w,"s")==0)return f(n,F#s)
#endif
#ifdef RCC
/* define IS(s,f) if(strcmp(w,"s")==0)return f(n,F/**/s) */
#endif

int prrall();
int prspecial();
int prbit();

int print(w, n) char   *w; int n;
{
#ifdef MPX
    if(strcmp(w,"cookie")==0)return prbit(n,Fcookie);
    if(strcmp(w,"type")==0)return prbit(n,Ftype);
    if(strcmp(w,"shape")==0)return (n & SPECIAL ? prspecial(n) : prbit(n,Fcookie));
    if(strcmp(w,"result")==0)return (n == 0 ? printf("RNULL ") : prbit(n,Fresult));
    if(strcmp(w,"rall")==0)return prrall(n,Frall);
#endif
#ifdef RCC
    IS(cookie,prbit);
    IS(type,prbit);
    IS(shape, n & SPECIAL ? prspecial(n) : prbit);
    IS(result, n == 0 ? printf("RNULL ") : prbit);
    IS(rall,prrall);
#endif

    return printf("%s=%x ", w, n);
}

int prspecial(n) int n;
{
    int         i, t;
    i = (n & ~SPECIAL) >> 1;
    for (t = 0; t < i && Fspecial[t]; t++);
    if (Fspecial[t]) {
	printf("%s ", Fspecial[t]);
    }
    else {
	printf("Special_o%o ", i);
    }
    return(1);         /* dummy return value */
}

int prbit(n, f) char   *f;
unsigned    int n;
{
    int         bpos = 0;
    char        first = 1;
    if (n == 0) {
	return(0);
    }
    for (; n; bpos++, n >>= 1) {
	if (n & 1) {
	    if (!first)
		putchar('|');
	    else
		first = 0;

	    if (*f && *f != '|') {
		while (*f && *f != '|')
		    putchar(*f++);
		if (*f)
		    f++;
	    }
	    else {
		if (*f)
		    f++;
		printf("_%d_", bpos);
	    }
	}
	else {
	    while (*f && *f++ != '|');
	}
    }
    putchar(' ');
    return(1);         /* dummy return value */
}

int prrall(n) int n;
{
    extern char    *rnames[];
    if (n == NOPREF)
	printf("NOPREF");
    else {
	printf((n & MUSTDO) ? "MUSTDO" : "PREF");
	n &= ~MUSTDO;
	if(n >= 0 && n < szrnames)
		printf(" %s", rnames[n]);
	else
		printf(" 0x%x => ???", n | MUSTDO);
    }
    return(1);          /* dummy return value */
}
#endif

