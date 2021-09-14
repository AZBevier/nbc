/* print.h */
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
 
/*	@(#) (Gould) $Header: /u/nbc/nbccom/RCS/print.h,v 1.1 1995/01/27 20:56:20 jbev Exp $		  */
 
/*
    C compiler for Gould processors, base register instruction set.
 
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
 
    2nd pass print routines only.  Print routines common to both passes
    are located in the common.h and treewalk.h files.
*/
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
 
print(w, n) char   *w;
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
prspecial(n)
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
}
prbit(n, f) char   *f;
unsigned    n;
{
    int         bpos = 0;
    char        first = 1;
    if (n == 0) {
	return;
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
}
 
prrall(n)
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
}
#endif
 
/*
 * 	(c) Copyright 1986 Gould Inc.
 * 	    All Rights Reserved.
 */
