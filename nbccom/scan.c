/* scan.c */
/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid = "$Id: scan.c,v 1.22 2022/03/13 22:10:20 jbev Exp $";
#endif

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

/*
 * $Log: scan.c,v $
 * Revision 1.22  2022/03/13 22:10:20  jbev
 * A.out.h is a local include, not system.
 *
 * Revision 1.21  2021/09/13 22:03:21  jbev
 * Change version to 1.4.
 *
 * Revision 1.20  2019/02/24 19:33:29  jbev
 * Remove stdlib.h include for mpx
 *
 * Revision 1.19  2019/01/31 22:02:16  jbev
 * Update for Linux
 *
 * Revision 1.18  1997/01/22 18:28:07  jbev
 * Correct pointer/integer problem with error messages.
 * Only on Alpha because of 64 bit pointers and 32 bit ints.
 *
 * Revision 1.17  1996/10/26 22:29:03  jbev
 * Fix for Alpha Port
 *
 * Revision 1.16  1996/03/20 23:43:30  jbev
 * Use O/S malloc function for alpha, not internal function.
 * More mods for alpha port.
 *
 * Revision 1.15  1996/03/20 22:03:33  jbev
 * Keyboard snake problem.
 *
 * Revision 1.14  1996/03/20 22:00:18  jbev
 * Use unbuffered stdout for alpha machines.
 *
 * Revision 1.13  1996/03/20 21:42:39  jbev
 * Mods for alpha port.
 *
 * Revision 1.12  1996/03/19 00:11:44  jbev
 * Fix Log directive.
 *
 * Revision 1.11  1996/03/19 00:10:26  jbev
 * Mods for Alpha port.
 *
 * Revision 1.10  1995/12/20  17:15:31  jbev
 * Update to 1.2.0p7.  NASA fix applied 12/20/95 for bad code generation.
 *
 * Revision 1.9  1995/09/25  17:58:35  jbev
 * Change revision to 1.2.0p6.
 *
 * Revision 1.8  1995/08/05  15:10:07  jbev
 * Change release to 1.2.0p5.
 *
 * Revision 1.7  1995/04/28  20:50:33  jbev
 * Change version number.
 *
 * Revision 1.6  1995/03/06  19:18:32  jbev
 * Malloc tree node table instead of hard coding size.
 * Allow XTTval  and X2TTval to set node tree table size.
 * Add new option XJ and X2J to inhibit _ being prepended to names.
 * Correct XT[DS]val options for setting table sizes.
 *
 */

#include "mfile1.h"
#include "a.out.h"
#include <ctype.h>
#ifndef mpx
#include <stdlib.h>
#endif
#include <string.h>

extern	int	handopt;	/* handler option word */
extern	int	_flag;		/* don't prepend _ to names */
#define ASMBUF 80		/* max length of asm call */
char asmbuf[ASMBUF];		/* temp holding buffer */
char *asmp;			/* cur char point in asmbuf */
int         asm_esc = 0;	/* asm escaped used in file */

#define NULLZ 0

/* lexical actions */
#define A_ERR 0		/* illegal character */
#define A_LET 1		/* saw a letter */
#define A_DIG 2		/* saw a digit */
#define A_1C 3		/* return a single character */
#define A_STR 4		/* string */
#define A_CC 5		/* character constant */
#define A_BCD 6		/* GCOS BCD constant */
#define A_SL 7		/* saw a / */
#define A_DOT 8		/* saw a . */
#define A_PL 9		/* + */
#define A_MI 10		/* - */
#define A_EQ 11		/* = */
#define A_NOT 12	/* ! */
#define A_LT 13		/* < */
#define A_GT 14		/* > */
#define A_AND 16	/* & */
#define A_OR 17		/* | */
#define A_WS 18		/* whitespace (not \n) */
#define A_NL 19		/* \n */

#define A_STAR	20	/* * */
#define A_PCT	21	/* % */
#define A_HAT	22	/* ^ */
 /* character classes */

#define LEXLET 1
#define LEXDIG 2
#define LEXOCT 4
#define LEXHEX 8
#define LEXWS 0x10
#define LEXDOT 0x20

 /* reserved word actions */

#define AR_TY 0		/* type word */
#define AR_RW 1		/* simple reserved word */
#define AR_CL 2		/* storage class word */
#define AR_S 3		/* struct */
#define AR_U 4		/* union */
#define AR_E 5		/* enum */
#define AR_A 6		/* asm */
#define AR_SZ 7		/* sizeof */
#ifdef FLA
#define AR_FT 8		/* fortran */
#endif

 /* text buffer */
#define	LXTSZ	BUFSIZ
char        yytext[LXTSZ];
char       *lxgcp;

extern int  proflg;
extern int  gdebug;
extern	int  lastloc;

/*
** LINE_BUF is setup so that the assembly listing when printed with line
** numbers will not overflow 132 column printer line width
*/
#ifndef NOCAID
# define LINE_BUF 60
#else
# define LINE_BUF 80
#endif

static int r_c_p = 0;
static char r_c_buf [ LINE_BUF + 1 ] = { 0 };

#ifdef getchar
#undef getchar
#endif
#define getchar() (r_c_buf[r_c_p] ? r_c_buf[r_c_p++] : readcoi())

#ifdef ungetc
#undef ungetc
#endif
#define ungetc(c, p) (r_c_p > 0 ? r_c_p-- : 0)

int readcoi ()
{
int n;

 while ( r_c_buf [ r_c_p ] == 0 ) {
  if ( ( n = getloi ( r_c_buf, LINE_BUF ) ) == 0 )
   return ( EOF );
  r_c_p = 0;
 }
#ifndef CAID_080293
#ifndef CAID_081393
 if((gdebug && r_c_buf[0] != '#') ||
    (!gdebug && r_c_buf[0] != '#' && r_c_buf[0] != '\n'))
#else
 if(r_c_buf[0] != '#')
#endif
#else
 if(r_c_buf[0] != '#' && r_c_buf[0] != '\n')
#endif
  if(r_c_buf [ n - 1 ] != '\n')
   {
   r_c_buf [ n ] = '\n';
   r_c_buf [ n + 1 ] = '\0';
   defloi( r_c_buf );
   r_c_buf [ n ] = '\0';
   }
  else
   defloi( r_c_buf );
 return ( r_c_buf [ r_c_p++ ] );
}

unsigned int caloff();
 /* ARGSUSED */
extern char     ftitle[];
static char    *sourcefile = NULL;
extern char     version[];
int         onlyuchar;

int	    dobuiltins;

int mainp1(argc, argv) int  argc;
char       *argv[];
{		/* control multiple files */

    register    int i;
    register char  *cp;
#ifndef BUG1
    extern int  idebug, bdebug, tdebug, edebug, ddebug, xdebug;
#endif
#ifdef TWOPASS
    extern int  Wflag;
#endif /* TWOPASS */
    extern unsigned int     offsz;
    int         fdef = 0;
/* char       *release = "MPX Version: 1.1 State: Beta Test"; */
/* char       *release = "NBCC Version: 1.1.0 State: Released"; */
/* char       *release = "NBCC Version: 1.1.1 State: Released"; */
/* char       *release = "NBCC Version: 1.2.0 State: Released"; */
/* char       *release = "NBCC Version: 1.2.0p1 State: Released"; */
/* char       *release = "NBCC Version: 1.2.0p2 State: Released"; */
/* char       *release = "NBCC Version: 1.2.0p3 State: Released"; */
/* char       *release = "NBCC Version: 1.2.0p4 State: Released"; */
/* char       *release = "NBCC Version: 1.2.0p5 State: Released"; */
/* char       *release = "NBCC Version: 1.2.0p6 State: Released"; */
/* char       *release = "NBCC Version: 1.2.0p7 State: Released"; */
/* char       *release = "NBCC Version: 1.2.8 State: Released"; */
/*  char       *release = "NBCC Version: 1.3.0 State: Released"; */
    char       *release = "NBCC Version: 1.4.0 State: Released";
    extern int MAXOBJSIZE;

/* #define LNX */
#define LNX
#ifndef LNX
	++ddebug;
	++idebug;
	++bdebug;
	++tdebug;
	++edebug;
	++xdebug;
#endif
#ifndef LNX
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    fprintf(stderr, "main entry\n");
#endif
    dobuiltins = 1;		/* default to builtins */
    offsz = caloff();
#ifndef LNX
    fprintf(stderr, "offsz = %x\n", offsz);
#endif
    SYMTSZ = SYMTSZDEF;
    DIMTABSZ = DIMTSZDEF;	/* MPX */
    TREESIZE = TREESZ;
    for (i = 1; i < argc; ++i) {
	if (*(cp = argv[i]) == '-'
	    && *++cp == 'X' &&  *(cp+1) != '2') {

	    /* NOTE:  -Xoptions => pass 1 debug flags
		      -X2options => pass 2 debug flags
	     */

	    while (*++cp) {	/* scan pass 1 debug options */
#ifndef LNX
    fprintf(stderr, "option char '%c' [%x]\n", *cp, *cp);
#endif
		switch (*cp) {

		    /* For Single Pass Compilation */
		    case 'J':	/* No _ on names */
				_flag = 1;
				break;

		    case 'H':	/* this an MPX handler */
				handopt = 1;
				break;

		    case 'S':
			{
			    extern int SAflag;
			    ++SAflag; /* warn about struct as 1st arg */
			    break;
			}

		    case 'r': 
#ifndef LNX
    fprintf(stderr, "option Xr\n");
#endif
			fprintf(stderr, "%s\n%s\n",
				release,version);
			break;

		    case 'T':
			switch(*++cp) {
				case 'D':
					{
					int size;
#ifdef OLDWAY
					size = atoi(argv[++i]);
#else
					size = atoi(++cp);
#endif
					if (size > DIMTSZDEF) { /* MPX */
					    DIMTABSZ = size;
					    fprintf(stderr,
"Warning: Dimension Table Size is %d (default is %d)\n",DIMTABSZ,DIMTSZDEF); /* MPX */
					}
					else
					    fprintf(stderr,
"Warning: Invalid Dimension Table Size (Using Default)\n");
					continue;
					}
				case 'S':
					{
					int size;
#ifdef OLDWAY
					size = atoi(argv[++i]);
#else
					size = atoi(++cp);
#endif
					if (size > SYMTSZDEF) {
					    SYMTSZ = size;
					    fprintf(stderr,
"Warning: Symbol Table Size is %d (default is %d)\n",SYMTSZ,SYMTSZDEF);
					}
					else
					    fprintf(stderr,
"Warning: Invalid Symbol Table Size (Using Default)\n");
					continue;
					}
				case 'T':
					{
					int size;
					size = atoi(++cp);
					if (size >TREESZ) {
					    TREESIZE = size;
					    fprintf(stderr,
"Warning: Tree Node Table Size is %d (default is %d)\n",TREESIZE, TREESZ);
					}
					else
					    fprintf(stderr,
"Warning: Invalid Tree Node Table Size (Using Default)\n");
					continue;
					}
				default:
#ifdef OLDWAY
		werror("illegal -T[DS] value option ignored");
#else
		werror("illegal -T[DST]VALUE option ignored");
#endif
					continue;
				}
		    case 'F':	/* next arg is input file name */
			sourcefile = argv[++i];
#ifndef LNX
    fprintf(stderr, "option XF sourcefile [%s]\n", sourcefile);
#endif
			if(sourcefile == NULL)
				uerror("input file name expected");
			break;

		    case 'y':
		      {	
#ifndef BUG1
		      	extern int yydebug;
			++yydebug;
#endif
			break;
		      }

		    case 'D': 
#ifndef LNX
    fprintf(stderr, "option XD\n");
#endif
#ifndef BUG1
			++ddebug;
			++idebug;
			++bdebug;
			++tdebug;
			++edebug;
			++xdebug;
			break;
#endif
		    case 'd': 
#ifndef BUG1
			++ddebug;
#endif
			break;
		    case 'i': 
#ifndef BUG1
			++idebug;
#endif
			break;
		    case 'b': 
#ifndef BUG1
			++bdebug;
#endif
			break;
		    case 't': 
#ifndef BUG1
			++tdebug;
#endif
			break;
		    case 'e': 
#ifndef BUG1
			++edebug;
#endif
			break;
		    case 'x': 
#ifndef BUG1
			++xdebug;
#endif
			break;
		    case 'P': 		/* profiling */
			++proflg;
			break;
		    case 'g': 
			++gdebug;	/* debugger symbols out */
			break;
		    case 'U': 
			++onlyuchar;
			break;
		    case 'R':
			dobuiltins = 0;	/* don't do builtins */
			break;
		    case 'l': 	/* control pass2 line listing & stabs */
#ifndef LNX
    fprintf(stderr, "option Xl\n");
#endif
			{
			    extern      int lflag;
		    /* CHEAT....  this is in pass 2!!! */
			    lflag++;
			    break;
			}
		}
	    }
	}
	else {
	    if (*(argv[i]) != '-') {
		switch (fdef++) {
		    case 0: 
#ifndef LNX
    fprintf(stderr, "fdef = %x sourcefile [%s] argv[%d] [%s]\n",
    fdef, sourcefile, i, argv[i]);
#endif
			if (sourcefile == NULL)
			    sourcefile = argv[i];
		    case 1: 
#ifndef LNX
    fprintf(stderr, "fdef = %x sourcefile [%s] argv[%d] [%s]\n",
    fdef, sourcefile, i, argv[i]);
#endif
#ifndef LNX
			if (fdef == 1) {
			  if (freopen(argv[i], "r", stdin) == NULL) {
			    fprintf(stderr, "ccomr fdef %x:can't open %s\n", fdef, argv[i]);
			    exit(1);
			  }
			} else if (freopen(argv[i], "w", stdout) == NULL) {
			    fprintf(stderr, "ccomw fdef %x:can't open %s\n", fdef, argv[i]);
			    exit(1);
			  }
#else
			if (freopen(argv[i], fdef == 1 ? "r" : "w",
			    fdef == 1 ? stdin : stdout) == NULL) {
			    fprintf(stderr, "ccomrw fdef %x:can't open %s\n", fdef, argv[i]);
			    exit(1);
			}
#endif
#ifdef __alpha_NOMORE
			/* alpha core dump with buffered stdout */
			setbuf(stdout, NULL);
#endif
#ifndef LNX
    setbuf(stdout, NULL);
    fprintf(stderr, "xdef = 1 sourcefile [%s] argv[%d] [%s]\n",
    sourcefile, i, argv[i]);
#endif
			break;

		    default: 
			;
		}
	     }
#ifdef TWOPASS
	     else if (*(cp = argv[i]) == '-' && *++cp == 'w') {
		      Wflag++; /* Shut-Up Warnings For Single Pass */
	     }
#endif /* TWOPASS */
	}
    }
#ifndef LNX
    fprintf(stderr, "end of options\n");
#endif
    nodep = (NODE *)domalloc(sizeof(NODE) * TREESIZE);
    if ((int)nodep <= 0)
       cerror("Out of memory: Can not alloc Node Tree Table");
    stab = (struct symtab *)domalloc(sizeof(struct symtab) * (SYMTSZ + 1));
    if ((int)stab <= 0)
       cerror("Out of memory: Can not alloc Symbol Table");
    dimtab = (int *)domalloc(sizeof(int) * DIMTABSZ);
    if ((int)dimtab <= 0)
       cerror("Out of memory: Can not alloc Dimension Table");
    if (sourcefile == NULL)
	strcpy(sourcefile, "main");
    strcpy(ftitle, "\"");
    strcat(ftitle, sourcefile);
    strcat(ftitle, ".c\"");	/* append .c to file name */
    sourcefile = ftitle;	/* set the name */
    cp = sourcefile;
#ifndef LNX
    fprintf(stderr, "starting file %s\n", cp);
#endif
#ifdef BAD_WAY
    do {
      if(isupper(*cp))
    	*cp = tolower(*cp);
    } while (*++cp);
#endif
#ifdef ONEPASS
    p2init(argc, argv);
#ifndef LNX
    fprintf(stderr, "* %s %s\n* call init\n", sourcefile, version);
#endif
#endif

    for (i = 0; i < SYMTSZ; ++i)
	stab[i].stype = TNULL;

#ifndef LNX
    fprintf(stderr, "* %s %s\n*	\n", sourcefile, version);
#endif

    p1init();		/* p1init in local.c */

    lineno = 1;
    lxinit();
    tinit();
    mkdope();

 /* dimension table initialization */

    dimtab[NULLZ] = 0;
    dimtab[CHAR] = SZCHAR;
    dimtab[INT] = SZINT;
    dimtab[FLOAT] = SZFLOAT;
    dimtab[DOUBLE] = SZDOUBLE;
    dimtab[LONG] = SZLONG;
    dimtab[SHORT] = SZSHORT;
    dimtab[UCHAR] = SZCHAR;
    dimtab[USHORT] = SZSHORT;
    dimtab[UNSIGNED] = SZINT;
    dimtab[ULONG] = SZLONG;
 /* starts past any of the above */
    curdim = 16;
    reached = 1;

    locctr(PROG);

#ifndef BUG1
    if(ddebug && edebug) {
	printf("mainp1():\n");
    }
#endif
/*	printf("mainp1():\n"); */

    yyparse();
    yyaccpt();

    ejobcode(nerrors ? 1 : 0);
    exit(nerrors ? 1 : 0);

}

#define CSMASK 0x7f
#define CSSZ 128

short       lxmask[CSSZ + 1];

void lxenter(s, m) register char    *s;
register short  m;
{
 /* enter a mask into lxmask */
    register    int c;

    while (c = *s++)
	lxmask[c + 1] |= m;
}

#define lxget(c,m) (lxgcp=yytext,lxmore(c,m))

void lxmore(c, m) register int c, m;
{
    register char  *cp;

    *(cp = lxgcp) = c;
    while (c = getchar(), lxmask[c + 1] & m) {
	if (cp < &yytext[LXTSZ - 1]) {
	    *++cp = c;
	}
    }
    ungetc(c, stdin);
    *(lxgcp = cp + 1) = '\0';
}

struct      lxdope
{
    short       lxch;		/* the character */
    short       lxact;		/* the action to be performed */
    short       lxtok;		/* the token number to be returned */
    short       lxval;		/* the value to be returned */
}           lxdope[] =
{

    '@', A_ERR, 0, 0,		/* illegal characters go here... */
    '_', A_LET, 0, 0,		/* letters point here */
    '0', A_DIG, 0, 0,		/* digits point here */
    ' ', A_WS, 0, 0,		/* whitespace goes here */
    '\n', A_NL, 0, 0,
    '"', A_STR, 0, 0,		/* character string */
    '\'', A_CC, 0, 0,		/* character constant */
    '`', A_BCD, 0, 0,		/* GCOS BCD constant */
    '(', A_1C, LP, 0,
    ')', A_1C, RP, 0,
    '{', A_1C, LC, 0,
    '}', A_1C, RC, 0,
    '[', A_1C, LB, 0,
    ']', A_1C, RB, 0,
    '*', A_STAR, MUL, MUL,
    '?', A_1C, QUEST, 0,
    ':', A_1C, COLON, 0,
    '+', A_PL, PLUS, PLUS,
    '-', A_MI, MINUS, MINUS,
    '/', A_SL, DIVOP, DIV,
    '%', A_PCT, DIVOP, MOD,
    '&', A_AND, AND, AND,
    '|', A_OR, OR, OR,
    '^', A_HAT, ER, ER,
    '!', A_NOT, UNOP, NOT,
    '~', A_1C, UNOP, COMPL,
    ',', A_1C, CM, CM,
    ';', A_1C, SM, 0,
    '.', A_DOT, STROP, DOT,
    '<', A_LT, RELOP, LT,
    '>', A_GT, RELOP, GT,
    '=', A_EQ, ASSIGN, ASSIGN,
    -1, A_1C, 0, 0,
};

struct lxdope  *lxcp[CSSZ + 1];

void lxinit()
{
    register struct lxdope *p;
    register    int i;
    register char  *cp;
 /* set up character classes */

    lxenter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_$", LEXLET);
    lxenter("0123456789", LEXDIG);
    lxenter("0123456789abcdefABCDEF", LEXHEX);
 /* \013 should become \v someday; \013 is OK for ASCII and EBCDIC */
    lxenter(" \t\r\b\f\013", LEXWS);
    lxenter("01234567", LEXOCT);
    lxmask['.' + 1] |= LEXDOT;

 /* make lxcp point to appropriate lxdope entry for each character */

 /* initialize error entries */

    for (i = 0; i <= CSSZ; ++i)
	lxcp[i] = lxdope;

 /* make unique entries */

    for (p = lxdope;; ++p) {
	lxcp[p -> lxch + 1] = p;
	if (p -> lxch < 0)
	    break;
    }

 /* handle letters, digits, and whitespace */
 /* by convention, first, second, and third places */

    cp = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ$";
    while (*cp)
	lxcp[*cp++ + 1] = &lxdope[1];
    cp = "123456789";
    while (*cp)
	lxcp[*cp++ + 1] = &lxdope[2];
    cp = "\t\b\r\f\013";
    while (*cp)
	lxcp[*cp++ + 1] = &lxdope[3];

 /* first line might have title */
    lxtitle();

}


# define STRBUFSZ	1024
static char newstr[STRBUFSZ + 5]; /*hold the string found in lxstr temporarily*/
static int tstrlen;	/*keep length of string around temporarily*/

void
gettmpstr(ct,l)
int ct;		/*pass directly through to lxstr*/
int l;		/*the label number*/
{
	int i;
	char *cp;

	if (begstrng == NULL)
	{
		begstrng = (struct tstrngs *)domalloc(sizeof(struct tstrngs));
		currstng = begstrng;
	}
	else
	{
		currstng->next =(struct tstrngs *)domalloc(sizeof(struct tstrngs));
		currstng = currstng->next;
	}
	currstng->next = NULL;
	currstng->slabel = l;
	lxstr(ct);		/*ct always zero (we hope)*/
	currstng->strng = cp = (char *)domalloc(tstrlen+1);
	currstng->length = tstrlen;
	for(i = 0; i < tstrlen; i++)
		*cp++ = newstr[i];
}

int settmpstr(ch)
char *ch;	/*char string to save */
{
	int l;		/*the label number*/
	int i;
	char *cp;
	struct tstrngs * tempptr;

	tstrlen = strlen(ch);
	if (begstrng == NULL)
	{
		begstrng = (struct tstrngs *)domalloc(sizeof(struct tstrngs));
		currstng = begstrng;
		l = get2lab();	/* get a label for returning */
	}
	else
	{
	/* test to see if string is allready assigned, if so return label */
		for (tempptr=begstrng; tempptr; tempptr=tempptr->next)
			if (strcmp(tempptr->strng, ch) == 0)
			/* same string found, return its label */
				return(-tempptr->slabel);
		/* not found, save the string with a new label */
		l = get2lab();	/* get a label for returning */

		currstng->next =(struct tstrngs *)domalloc(sizeof(struct tstrngs));
		currstng = currstng->next;
	}
	currstng->next = NULL;
	currstng->slabel = -l;
	currstng->strng = cp = (char *)domalloc(tstrlen+1);
	currstng->length = tstrlen;
	for(i = 0; i < tstrlen; i++)
		*cp++ = *ch++;
	*cp = (char)0;
	return (l);
}

int         lxmatch;	/* character to be matched in char or string constant */

void lxstr(ct)
int ct;
{
 /* match a string or character constant, up to lxmatch */

    register    int c;
    register    int val;
    register    int i;
    int 	tbflag;		/* string too long for buffer */

    tbflag = 0;
    i = 0;
    while ((c = getchar()) != lxmatch) {
	if(tbflag)
		continue;
	switch (c) {

	    case EOF: 
		uerror("unexpected EOF");
		break;

	    case '\n': 
		uerror("newline in string or char constant");
		++lineno;
		break;

	    case '\\': 
		switch (c = getchar()) {

		    case '\n': 
			++lineno;
			continue;

		    default: 
			val = c;
			goto mkcc;

		    case 'n': 
			val = '\n';
			goto mkcc;

		    case 'r': 
			val = '\r';
			goto mkcc;

		    case 'b': 
			val = '\b';
			goto mkcc;

		    case 't': 
			val = '\t';
			goto mkcc;

		    case 'f': 
			val = '\f';
			goto mkcc;

		    case 'v': 
			val = '\013';
			goto mkcc;

		    case '0': 
		    case '1': 
		    case '2': 
		    case '3': 
		    case '4': 
		    case '5': 
		    case '6': 
		    case '7': 
			val = c - '0';
			c = getchar();		/* try for 2 */
			if (lxmask[c + 1] & LEXOCT) {
			    val = ((unsigned)val << 3) | (c - '0');
			    c = getchar();	/* try for 3 */
			    if (lxmask[c + 1] & LEXOCT) {
				val = ((unsigned)val << 3) | (c - '0');
			    }
			    else
				ungetc(c, stdin);
			}
			else
			    ungetc(c, stdin);

			goto mkcc1;

		}
	    default: 
		val = c;
	mkcc: 
		val = CCTRANS(val);
	mkcc1: 
		if (lxmatch == '\'') {
		    if (!onlyuchar && i == 0) {
			lastcon = ((unsigned)val << 24) >> 24;
		    }
		    else {
			makecc(val, i);
		    }
		}
		else {		/* stash the byte into the string */
		    if(i >= STRBUFSZ) {
			wderror("string initializer truncated to %d characters",
			  STRBUFSZ);
			tbflag = 1;
			continue;
		    }
		    if (strflg) {
			if (ct == 0 || i < ct)
			    putbyte(val);
			else
			    if (i == ct)
			wderror("string initializer truncated to %d characters",
			  ct);
		    }
		    else
			newstr[i] = val;
		}
		++i;
		continue;
	}
	break;
    }
 /* end of string or  char constant */

    if (lxmatch == '"') {
	if (strflg) {		/* end the string */
	    if (ct == 0 || i < ct)
		putbyte(0);	/* the null at the end */
	}
		else	{
			newstr[i++]= 0;
			dimtab[curdim] = tstrlen = i;  /* in case of later sizeof ... */
		}
    }
    else {			/* end the character constant */
	if (i == 0)
	    uerror("empty character constant");
	if (i > (SZINT / SZCHAR) || ((pflag || hflag) && i > 1))
	    uerror("too many characters in character constant");
    }
}

void lxcom()
{
    register    int c;
 /* saw a / *: process a comment */

    for (;;) {

	switch (c = getchar()) {

	    case EOF: 
		uerror("unexpected EOF");
		return;

	    case '\n': 
		++lineno;

	    default: 
		continue;

	    case '*': 
		if ((c = getchar()) == '/')
		    return;
		else
		    ungetc(c, stdin);
		continue;
#ifndef LINT
	    case 'N': 
		lxget(c, LEXLET);
		continue;

	    case 'A':
		lxget(c, LEXLET);
		if (strncmp(yytext, "ALIGN", 5) == 0 ) {

		    if(forcealign > 0)
			werror("Previous ALIGN directive overridden");
		    lxget(c, LEXWS);
		    c = getchar();
		    lxget(c, LEXDIG);
		    if( ! isdigit(yytext[0]) ) {
			forcealign = 0;
			uerror("Bad ALIGN directive");
			continue;
		    }
		    forcealign = atoi(yytext);
		    if(forcealign <= 0 || ! ispow2(forcealign) ) {
			forcealign = 0;
			uerror("ALIGN directive must specify power of two");
			continue;
		    }
		    forcealign = (unsigned)forcealign << 3; /* Convert to units of bits */
		}
		continue;
#endif

#ifdef LINT
	    case 'V': 
		lxget(c, LEXLET | LEXDIG);
		{
		    extern int  vaflag;
		    int         i;
		    i = yytext[7] ? yytext[7] - '0' : 0;
		    yytext[7] = '\0';
		    if (strcmp(yytext, "VARARGS"))
			continue;
		    vaflag = i;
		    continue;
		}
	    case 'L': 
		lxget(c, LEXLET);
		if (strcmp(yytext, "LINTLIBRARY"))
		    continue;
		{
		    extern int  libflag;
		    libflag = 1;
		}
		continue;

	    case 'A': 
		lxget(c, LEXLET);
		if (strcmp(yytext, "ARGSUSED"))
		    continue;
		{
		    extern int  argflag, vflag;
		    argflag = 1;
		    vflag = 0;
		}
		continue;

	    case 'N': 
		lxget(c, LEXLET);
		if (strcmp(yytext, "NOTREACHED"))
		    continue;
		reached = 0;
		continue;
#endif
	}
    }
}

int yylex()
{
    for (;;) {

	register    int lxchar;
	register struct lxdope *p;
	register struct symtab *sp;
	int         id;

	switch ((p = lxcp[(lxchar = getchar()) + 1]) -> lxact) {

	    case A_HAT: 
	    case A_STAR: 
	    case A_PCT: 
		lxchar = getchar();
	maybeasop: 
		if (lxchar != '=') {
		    goto onechar;
		}
		yylval.intval = ASG p -> lxval;
		return(ASOP);

	onechar: 
		ungetc(lxchar, stdin);

	    case A_1C: 
	/* eat up a single character, and return an opcode */

		yylval.intval = p -> lxval;
		return(p -> lxtok);

	    case A_ERR: 
		uderror("illegal character: %02x (hex)", lxchar);
		break;

	    case A_LET: 
	/* collect an identifier, check for reserved word, and return */
		lxget(lxchar, LEXLET | LEXDIG);
		if ((lxchar = lxres()) > 0)
		    return(lxchar);		/* reserved word */
		if (lxchar == 0)
		    continue;
		id = lookup(hash(yytext),
			(stwart & TAGNAME) ? STAG :
			(stwart & (INSTRUCT | INUNION | FUNNYNAME)) ? SMOS : 0);
		sp = &stab[id];
		if (sp -> sclass == TYPEDEF && !stwart) {
		    stwart = instruct;
		    yylval.nodep = mkty(sp -> stype, sp -> dimoff, sp -> sizoff);
		    return(TYPE);
		}
		stwart = (stwart & SEENAME) ? instruct : 0;
		yylval.intval = id;
		return(NAME);

	    case A_DIG: 
	/* collect a digit string, then look at last one... */
		lastcon = 0;
		lxget(lxchar, LEXDIG);
		switch (lxchar = getchar()) {

		    case 'x': 
		    case 'X': 
			if (yytext[0] != '0' && !yytext[1])
			    uerror("illegal hex constant");
			lxmore(lxchar, LEXHEX);
		/* convert the value */
			{
			    register char  *cp;
			    for (cp = yytext + 2; *cp; ++cp) {
			/* this code won't work for all wild character sets, 
			   but seems ok for ascii and ebcdic */
				lastcon = (unsigned)lastcon << 4;
				if (isdigit(*cp))
				    lastcon += *cp - '0';
				else
				    if (isupper(*cp))
					lastcon += *cp - 'A' + 10;
				    else
					lastcon += *cp - 'a' + 10;
			    }
			}

		hexlong: 
		/* criterion for longness for hex and octal constants
		   is that it fit within 0177777 */
			if (lastcon & ~0xffff)
			    yylval.intval = 1;
			else
			    yylval.intval = 0;

			goto islong;

		    case '.': 
			lxmore(lxchar, LEXDIG);

		getfp: 
			if ((lxchar = getchar()) == 'e' || lxchar == 'E') {
		    /* exponent */

		    case 'e': 
		    case 'E': 
			    if ((lxchar = getchar()) == '+' || lxchar == '-') {
				*lxgcp++ = 'e';
			    }
			    else {
				ungetc(lxchar, stdin);
				lxchar = 'e';
			    }
			    lxmore(lxchar, LEXDIG);
		    /* now have the whole thing... */
			}
			else {		/* no exponent */
			    ungetc(lxchar, stdin);
			}
			return(isitfloat(yytext));

		    default: 
			ungetc(lxchar, stdin);
			if (yytext[0] == '0') {
		    /* convert in octal */
			    register char  *cp;
			    for (cp = yytext + 1; *cp; ++cp) {
				lastcon = (unsigned)lastcon << 3;
				lastcon += *cp - '0';
			    }
			    goto hexlong;
			}
			else {
		    /* convert in decimal */
			    register char  *cp;
			    for (cp = yytext; *cp; ++cp) {
				lastcon = lastcon * 10 + *cp - '0';
			    }
			}

		/* decide if it is long or not (decimal case) */

		/* if it is positive and fits in 15 bits,
		   or negative and and fits in 15 bits plus an extended sign,
		   it is int; otherwise long */
		/* if there is an l or L following, all bets are off... */

			{
			    CONSZ       v;
			    v = lastcon & ~077777L;
			    if (v == 0 || v == ~077777L)
				yylval.intval = 0;
			    else
				yylval.intval = 1;
			}

		islong: 
		/* finally, look for trailing L or l */
			if ((lxchar = getchar()) == 'L' || lxchar == 'l')
			    yylval.intval = 1;
			else
			    ungetc(lxchar, stdin);
			return(ICON);
		}

	    case A_DOT: 
	/* look for a dot: if followed by a digit, floating point */
		lxchar = getchar();
		if (lxmask[lxchar + 1] & LEXDIG) {
		    ungetc(lxchar, stdin);
		    lxget('.', LEXDIG);
		    goto getfp;
		}
		stwart = FUNNYNAME;
		goto onechar;

	    case A_STR: 
	/* string constant */
		lxmatch = '"';
		return(STRING);

	    case A_CC: 
	/* character constant */
		lxmatch = '\'';
		lastcon = 0;
		lxstr(0);
		yylval.intval = 0;
		return(ICON);

	    case A_BCD: 
		{
		    register    int i;
		    int         j;
		    for (i = 0; i < LXTSZ; ++i) {
			if ((j = getchar()) == '`')
			    break;
			if (j == '\n') {
			    uerror("newline in BCD constant");
			    break;
			}
			yytext[i] = j;
		    }
		    yytext[i] = '\0';
		    uerror("gcos BCD constant illegal");
		    yylval.intval = 0;	/* not long */
		    return(ICON);
		}

	    case A_SL: 
	/* / */
		if ((lxchar = getchar()) == '*') {
		    lxcom();
		    continue;
		}
		goto maybeasop;

	    case A_WS: 
		continue;

	    case A_NL: 
		++lineno;
		lxtitle();
		continue;

	    case A_NOT: 
	/* ! */
		if ((lxchar = getchar()) != '=')
		    goto onechar;
		yylval.intval = NE;
		return(EQUOP);

	    case A_MI: 
	/* - */
		if ((lxchar = getchar()) == '-') {
		    yylval.intval = DECR;
		    return(INCOP);
		}
		if (lxchar == '>') {
		    stwart = FUNNYNAME;
		    yylval.intval = STREF;
		    return(STROP);
		}
		goto maybeasop;

	    case A_PL: 
	/* + */
		if ((lxchar = getchar()) == '+') {
		    yylval.intval = INCR;
		    return(INCOP);
		}
		goto maybeasop;

	    case A_AND: 
	/* & */
		if ((lxchar = getchar()) == '&')
		    return(yylval.intval = ANDAND);
		goto maybeasop;

	    case A_OR: 
	/* | */
		if ((lxchar = getchar()) == '|')
		    return(yylval.intval = OROR);
		goto maybeasop;

	    case A_LT: 
	/* < */
		if ((lxchar = getchar()) == '<') {
		    if ((lxchar = getchar()) != '=') {
			ungetc(lxchar, stdin);
			yylval.intval = LS;
			return(SHIFTOP);
		    }
		    else {
			yylval.intval = ASG LS;
			return(ASOP);
		    }
		}
		if (lxchar != '=')
		    goto onechar;
		yylval.intval = LE;
		return(RELOP);

	    case A_GT: 
	/* > */
		if ((lxchar = getchar()) == '>') {
		    if ((lxchar = getchar()) != '=') {
			ungetc(lxchar, stdin);
			yylval.intval = RS;
			return(SHIFTOP);
		    }
		    else {
			yylval.intval = ASG RS;
			return(ASOP);
		    }
		}
		if (lxchar != '=')
		    goto onechar;
		yylval.intval = GE;
		return(RELOP);

	    case A_EQ: 
	/* = */
		switch (id = lxchar = getchar()) {

		    case '=': 
			yylval.intval = EQ;
			return(EQUOP);


		    case '+': 
			yylval.intval = ASG PLUS;
			break;

		    case '-': 
			yylval.intval = ASG MINUS;

		warn: 
			if (lxmask[(lxchar = getchar()) + 1] & (LEXLET | LEXDIG | LEXDOT)) {
			    werror("ambiguous assignment: assignment op taken");
			}
			ungetc(lxchar, stdin);
			break;

		    case '*': 
			yylval.intval = ASG MUL;
			goto warn;

		    case '/': 
			yylval.intval = ASG DIV;
			break;

		    case '%': 
			yylval.intval = ASG MOD;
			break;

		    case '&': 
			yylval.intval = ASG AND;
			break;

		    case '|': 
			yylval.intval = ASG OR;
			break;

		    case '^': 
			yylval.intval = ASG ER;
			break;

		    case '<': 
			if ((lxchar = getchar()) != '<') {
			    uderror("=<%c illegal", lxchar);
			}
			yylval.intval = ASG LS;
			break;

		    case '>': 
			if ((lxchar = getchar()) != '>') {
			    uderror("=>%c illegal", lxchar);
			}
			yylval.intval = ASG RS;
			break;

		    default: 
			goto onechar;

		}
		wderror("Old fashioned assignment operator =%c", id);
		return(ASOP);

	    default: 
		cderror("yylex error, character %02x (hex)", lxchar);

	}

 /* ordinarily, repeat here... */
	cerror("out of switch in yylex");

    }

}

struct      lxrdope
{
 /* dope for reserved, in alphabetical order */

    char       *lxrch;		/* name of reserved word */
    short       lxract;		/* reserved word action */
    short       lxrval;		/* value to be returned */
}           lxrdope[] =
{

    "asm", AR_A, 0,
    "auto", AR_CL, AUTO,
    "break", AR_RW, BREAK,
    "char", AR_TY, CHAR,
    "case", AR_RW, CASE,
    "continue", AR_RW, CONTINUE,
    "double", AR_TY, DOUBLE,
    "default", AR_RW, DEFAULT,
    "do", AR_RW, DO,
    "extern", AR_CL, EXTERN,
    "else", AR_RW, ELSE,
    "enum", AR_E, ENUM,
    "for", AR_RW, FOR,
    "float", AR_TY, FLOAT,
#ifndef FLA
    "fortran", AR_CL, FORTRAN,
#else
    "fortran", AR_FT, FORTRAN,
#endif
    "goto", AR_RW, GOTO,
    "if", AR_RW, IF,
    "int", AR_TY, INT,
    "long", AR_TY, LONG,
    "return", AR_RW, RETURN,
#ifdef MPXTEMP
    "register", AR_CL, 0,
#else
    "register", AR_CL, REGISTER,
#endif
    "switch", AR_RW, SWITCH,
    "struct", AR_S, 0,
    "sizeof", AR_SZ, SIZEOF,
    "short", AR_TY, SHORT,
    "static", AR_CL, STATIC,
    "typedef", AR_CL, TYPEDEF,
    "unsigned", AR_TY, UNSIGNED,
    "union", AR_U, 0,
    "void", AR_TY, UNDEF,		/* tymerge adds FTN */
    "while", AR_RW, WHILE,
    "", 0, 0,				/* to stop the search */
};

int lxres()
{
 /* 
  * check to see of yytext is reserved; if so,
  * do the appropriate action and return
  * otherwise, return -1
  */

    register    int c, ch;
    register struct lxrdope    *p;

    ch = yytext[0];

    if (!islower(ch))
	return(-1);

    switch (ch) {

	case 'a': 
	    c = 0;
	    break;
	case 'b': 
	    c = 2;
	    break;
	case 'c': 
	    c = 3;
	    break;
	case 'd': 
	    c = 6;
	    break;
	case 'e': 
	    c = 9;
	    break;
	case 'f': 
	    c = 12;
	    break;
	case 'g': 
	    c = 15;
	    break;
	case 'i': 
	    c = 16;
	    break;
	case 'l': 
	    c = 18;
	    break;
	case 'r': 
	    c = 19;
	    break;
	case 's': 
	    c = 21;
	    break;
	case 't': 
	    c = 26;
	    break;
	case 'u': 
	    c = 27;
	    break;
	case 'v': 
	    c = 29;
	    break;
	case 'w': 
	    c = 30;
	    break;

	default: 
	    return(-1);
    }

    for (p = lxrdope + c; p -> lxrch[0] == ch; ++p) {
	if (!strcmp(yytext, p -> lxrch)) {	/* match */
	    switch (p -> lxract) {

		case AR_TY: 
	    /* type word */
		    stwart = instruct;
		    yylval.nodep = mkty((TWORD) p -> lxrval, 0, p -> lxrval);
		    return(TYPE);

		case AR_SZ: 
		    sizeofflag = 1;
		    return(yylval.intval = p -> lxrval);

		case AR_RW: 
	    /* ordinary reserved word */
		    return(yylval.intval = p -> lxrval);

		case AR_CL: 
	    /* class word */
		    yylval.intval = p -> lxrval;
		    return(CLASS);

#ifdef FLA
		case AR_FT: 
	    /* fortran class word */
		    yylval.intval = p -> lxrval;
		    return(FORTRAN);
#endif

		case AR_S: 
	    /* struct */
		    stwart = INSTRUCT | SEENAME | TAGNAME;
		    yylval.intval = INSTRUCT;
		    return(STRUCT);

		case AR_U: 
	    /* union */
		    stwart = INUNION | SEENAME | TAGNAME;
		    yylval.intval = INUNION;
		    return(STRUCT);

		case AR_E: 
	    /* enums */
		    stwart = SEENAME | TAGNAME;
		    return(yylval.intval = ENUM);

		case AR_A: 
	    /* asm */
		    asm_esc = 1;	/* warn the world! */
		    asmp = asmbuf;
		    lxget(' ', LEXWS);
		    if (getchar() != '(')
			goto badasm;
		    lxget(' ', LEXWS);
		    if (getchar() != '"')
			goto badasm;
#ifdef TWOPASS
		    *asmp++ = IASM;
#endif
		    while ((c = getchar()) != '"') {
			if (c == '\n' || c == EOF)
			    goto badasm;
			*asmp++ = c;
			if (asmp >= &asmbuf[ASMBUF-1])
			    uderror("asm > %d chars", ASMBUF);
		    }
		    lxget(' ', LEXWS);
		    if (getchar() != ')')
			goto badasm;
		    *asmp++ = '\0';
		    return (ASM);

	    badasm: 
		    uerror("bad asm construction");
		    return(0);

		default: 
		    cerror("bad AR_?? action");
	    }
	}
    }
    return(-1);
}

extern int  labelno;

void lxtitle()
{
 /* called after a newline; set linenumber and file name */

    register    int c, val;
    register char  *cp, *cq;

    for (;;) {		/* might be several such lines in a row */
	if ((c = getchar()) != '#') {
	    if (c != EOF)
		ungetc(c, stdin);

	    if (lastloc != PROG)
		return;
	    cp = ftitle;
	    cq = ititle;
	    while (*cp)
		if (*cp++ != *cq++)
		    return;
	    if (*cq)
		return;
	    psline();
	    return;
	}

	lxget(' ', LEXWS);
	val = 0;

#ifndef get_names
	for (c = getchar(); isdigit(c); c = getchar()) {
	    val = val * 10 + c - '0';
	}
#else /* get_names */
	c = getchar();
	if (!isdigit(c)) {	/* check for define reference */
	    lxget(' ', LEXWS);
	    defref(c);		/* it is ref to or define of define */
	    continue;
	}

	do {
	    val = val * 10 + c - '0';
	    c = getchar();
	} while (isdigit(c));
#endif /* get_names */

	ungetc(c, stdin);
	lineno = val;
	lxget(' ', LEXWS);
	if ((c = getchar()) != '\n') {
	    for (cp = ftitle; c != '\n'; c = getchar(), ++cp) {
#ifdef BADD_WAY
		*cp = isupper(c) ? tolower(c) : c;
#else
		*cp = c;
#endif
	    }
	    *cp = '\0';
#ifndef LINT
	    if (ititle[0] == '\0') {
		cp = ftitle;
		cq = ititle;
		while (*cp)
		    *cq++ = *cp++;
		*cq = '\0';
		*--cq = '\0';
		if( lastloc == PROG ){
		if (handopt)
		    locctr(DATA);
/* 		    printf("%cdsect\n",ITEXT); */
		else
		    locctr(PROG);
/*		    printf("%ccsect\n",ITEXT); */
		}

#ifdef NOT_4_CAID_NOW
  		pstab(ititle + 1, N_SO);
  		if (gdebug)
  		    printf("0,0,LL%d\n", labelno);
#endif

#ifdef DO_LINE_STABS
		printf ("	.stabs	\"%s\",0x%x,0,0,0\n", ititle+1, N_SO);
#endif

		*cq = '"';
	    }
#endif
	}
    }
}

# ifndef MYASMOUT

void asmout()
         /* write out asm string
          * this is a null function for lint
          */
{
         printf( "%s\n", asmbuf );
}
# endif

#define	NSAVETAB	4096
char       *savetab;
int         saveleft;

char       *savestr(cp)
register char  *cp;
{
    register int    len;

    len = strlen(cp) + 1;
    if (len > saveleft) {
	saveleft = NSAVETAB;
	if (len > saveleft)
	    saveleft = len;
	savetab = (char *) domalloc(saveleft);
	if (savetab == 0)
	    cerror("Ran out of memory (savestr)");
    }
    strncpy(savetab, cp, len);
    cp = savetab;
    savetab += len;
    saveleft -= len;
    return(cp);
}

/** The definition for the segmented hash tables.
 */
#define	MAXHASH	20
#define	HASHINC	1013
struct      ht
{
    char      **ht_low;
    char      **ht_high;
    int         ht_used;
}           htab[MAXHASH];

char       *hash(s)
char       *s;
{
    register char **h;
    register    int i;
    register char  *cp;
    struct ht  *htp;
    int         sh;

 /* 
  * The hash function is a modular hash of
  * the sum of the characters with the sum
  * doubled before each successive character
  * is added.
  */
    cp = s;
    i = 0;
    while (*cp)
	i = i * 2 + *cp++;
    sh = (i & 077777) % HASHINC;
    cp = s;
 /* 
  * There are as many as MAXHASH active
  * hash tables at any given point in time.
  * The search starts with the first table
  * and continues through the active tables
  * as necessary.
  */
    for (htp = htab; htp < &htab[MAXHASH]; htp++) {
	if (htp -> ht_low == 0) {
	    register char **hp = (char **) calloc(sizeof(char **), HASHINC);
	    if (hp == 0)
		cerror("ran out of memory (hash)");
	    htp -> ht_low = hp;
	    htp -> ht_high = htp -> ht_low + HASHINC;
	}
	h = htp -> ht_low + sh;
 /* 
  * quadratic rehash increment
  * starts at 1 and incremented
  * by two each rehash.
  */
	i = 1;
	do {
	    if (*h == 0) {
		if (htp -> ht_used > (HASHINC * 3) / 4)
		    break;
		htp -> ht_used++;
		*h = savestr(cp);
		return(*h);
	    }
	    if (**h == *cp && strcmp(*h, cp) == 0)
		return(*h);
	    h += i;
	    i += 2;
	    if (h >= htp -> ht_high)
		h -= HASHINC;
	} while (i < HASHINC);
    }
    cerror("ran out of hash tables");
    return(0);
}
