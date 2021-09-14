/* ldefs.c */
/*
 * 	(c) Copyright 1986 Gould Inc.
 * 	    All Rights Reserved.
 */

#ifndef lint
static char *rcsid1 = "@(#) (Gould) $Header: /bulk2/simhv/nbc-master/nblex/RCS/ldefs.c,v 1.5 2019/03/11 22:01:08 jbev Exp $";
#endif /* lint */

/*	ldefs.c	4.1	83/08/11	*/

# include <stdio.h>
# define PP 1

# if defined(unix) || defined(MPX)
# define CWIDTH 7
# define CMASK 0177
# define ASCII 1
# endif

# ifdef gcos
# define CWIDTH 9
# define CMASK 0777
# define ASCII 1
# endif

# ifdef ibm
# define CWIDTH 8
# define CMASK 0377
# define EBCDIC 1
# endif

# ifdef ASCII
# define NCH 128
# endif

# ifdef EBCDIC
# define NCH 256
# endif

# define TOKENSIZE 1000
# define DEFSIZE 40
# define DEFCHAR 1000

#if gould
# define STARTCHAR 1000
#else
# define STARTCHAR 100
#endif

# define STARTSIZE 256
# define CCLSIZE 1000

# ifdef SMALL
# define TREESIZE 600
# define NTRANS 1500
# define NSTATES 300
# define MAXPOS 1500
# define NOUTPUT 1500
# else
# define TREESIZE 1000
# define NSTATES 500
# define MAXPOS 2500
# define NTRANS 2000
# define NOUTPUT 3000
# endif

# define NACTIONS 100
# define ALITTLEEXTRA 30

# define RCCL NCH+90
# define RNCCL NCH+91
# define RSTR NCH+92
# define RSCON NCH+93
# define RNEWE NCH+94
# define FINAL NCH+95
# define RNULLS NCH+96
# define RCAT NCH+97
# define STAR NCH+98
# define PLUS NCH+99
# define QUEST NCH+100
# define DIV NCH+101
# define BAR NCH+102
# define CARAT NCH+103
# define S1FINAL NCH+104
# define S2FINAL NCH+105

# define DEFSECTION 1
# define RULESECTION 2
# define ENDSECTION 5
# define TRUE 1
# define FALSE 0

# define PC 1
# define PS 1

# ifdef DEBUG
# define LINESIZE 110
extern int yydebug;
extern int debug;		/* 1 = on */
extern int charc;
# endif

# ifndef DEBUG
# define freturn(s) s
# endif

#ifndef NCFORM
#define NCFORM "/system/lib/ncform"
#endif

extern int sargc;
extern char **sargv;
extern char buf[520];
extern int ratfor;		/* 1 = ratfor, 0 = C */
extern int yyline;		/* line number of file */
extern int sect;
extern int eof;
extern int lgatflg;
extern int divflg;
extern int funcflag;
extern int pflag;
extern int casecount;
extern int chset;	/* 1 = char set modified */
extern FILE *fin, *fout, *fother, *errorf;
extern int fptr;
extern char *ratname, *cname;
extern int prev;	/* previous input character */
extern int pres;	/* present input character */
extern int peek;	/* next input character */
extern int *name;
extern int *left;
extern int *right;
extern int *parent;
extern char *nullstr;
extern int tptr;
extern char pushc[TOKENSIZE];
extern char *pushptr;
extern char slist[STARTSIZE];
extern char *slptr;
extern char **def, **subs, *dchar;
extern char **sname, *schar;
extern char *ccl;
extern char *ccptr;
extern char *dp, *sp;
extern int dptr, sptr;
extern char *bptr;		/* store input position */
extern char *tmpstat;
extern int count;
extern int **foll;
extern int *nxtpos;
extern int *positions;
extern int *gotof;
extern int *nexts;
extern char *nchar;
extern int **state;
extern int *sfall;		/* fallback state num */
extern char *cpackflg;		/* true if state has been character packed */
extern int *atable, aptr;
extern int nptr;
extern char symbol[NCH];
extern char cindex[NCH];
extern int xstate;
extern int stnum;
extern int ctable[];
extern int ZCH;
extern int ccount;
extern char match[NCH];
extern char extra[NACTIONS];
extern char *pcptr, *pchar;
extern int pchlen;
extern int nstates, maxpos;
extern int yytop;
extern int report;
extern int ntrans, treesize, outsize;
extern long rcount;
extern int optim;
extern int *verify, *advance, *stoff;
extern int scon;
extern char *psave;
#if defined(mpx)
extern char *calloc(), *myalloc();
extern void cfree();
#else
//#include <stdlib.h>
extern void *calloc();
extern void *myalloc();
extern void free();
#define cfree(p, n, s) free((p))
#endif
extern int buserr(), segviol();
extern void chd1();
extern void chd2();
extern void ctail();
extern void rtail();
extern void ptail();
extern void rhd1();
extern void phead1();
extern void phead2();
extern void warning();
extern int gch();
extern int space();
extern int digit();
extern void error();
extern void statistics();
extern void yyerror();
extern void get1core();
extern void free1core();
extern void get2core();
extern void free2core();
extern void get3core();
extern void free3core();
extern void scopy();
extern void nb2();
extern void padd();
extern void bprint();
extern void upone();
extern void shiftr();
extern void rprint();
extern void first();
extern void acompute();
extern void nextstate();
extern void packtrans();
extern int printable();
extern int notin();
extern void follow();
extern int member();
extern int slength();
extern void mkmatch();
extern void cfoll();
extern void cgoto();
extern void layout();
extern int yyparse();
extern int alpha();
extern int siconv();
extern int ctrans();
extern void lgate();
extern int lindex();
extern int lookup();
extern int scomp();
extern char *getl();
extern int dupl();
extern int cpyact();
extern int mn0();
extern int mn1();
extern int mn2();
extern void cclinter();
extern int usescape();
extern void munput();
extern int strcmp();
extern int atoi();

/*
 * 	(c) Copyright 1986 Gould Inc.
 * 	    All Rights Reserved.
 */
