/* code.c */
/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid =
 "$Id: code.c,v 1.15 2022/03/13 22:10:20 jbev Exp $";
#endif

/*
 * $Log: code.c,v $
 * Revision 1.15  2022/03/13 22:10:20  jbev
 * A.out.h is a local include, not system.
 *
 * Revision 1.14  2019/02/24 17:15:30  jbev
 * Comment out stdlib.h include for mpx
 *
 * Revision 1.13  2019/01/31 21:43:27  jbev
 * Update for Linux
 *
 * Revision 1.12  1996/10/26 22:20:38  jbev
 * Fix for alpha port
 *
 * Revision 1.11  1996/03/22 16:41:23  jbev
 * Fix during Alpha port.
 *
 * Revision 1.10  1996/03/20 21:36:39  jbev
 * Mods for alpha port.
 *
 * Revision 1.9  1995/04/28 20:47:45  jbev
 * Modifictions for sectioned code.
 *
 */

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

#include "mfile1.h"
#include <sys/types.h>
#include <string.h>
#ifndef mpx
#include <stdlib.h>
#endif
#include "a.out.h"

extern int lflag;

int	handopt = 0;		/* handler option word */
int	_flag = 0;		/* don't prepend _ to names */
int	proflg = 0;		/* are we generating profiling code? */
int	strftn = 0;		/* is the current function one which returns a value */
int	gdebug;			/* debugger symbols output if set */
int	fdefflag;		/* are we within a function definition ? */
int	SAflag;			/* warn if first arg is a struct */
char	NULLNAME[8];
int	labelno;
int	slineno;		/* last line number from orig file */
char	progname[20];		/* saved program name */
char	currprog[20];		/* copy of ftitle when progname set */

void branch(n) int n;
{
/* output a branch to label n */
/* exception is an ordinary function branching to retlab: then, return */
    if( n == retlab && !strftn ) {

#ifdef ONEPASS
            LclReturn(n);
#else
	    if ( retstat & RETVAL ) {
        	printf("%c%d\t%d\t\n", IRETURN, n, 1);
	    } else {
        	printf("%c%d\t%d\t\n", IRETURN, n, 0);
	    }
#endif
	/* do NOT put a retstat = 0 here!!!! */
    } else {

#ifdef ONEPASS
#ifndef NOCAID
    	    if(lflag)
    		lineid(lineno, ftitle);
#endif
     	    printf("	bu	L%d\n", n);
#else
            printf( "%c%d\t\n", IBRANCH, n);
#endif

    }
}

int         lastloc = DATA;

short       log2tab[] =
{
    0, 0, 1, 2, 2, 3, 3, 3, 3
};
#define LOG2SZ 9

void defalign(n) int n;
{
 /* cause the alignment to become a multiple of n */
    n /= SZCHAR;
    if (lastloc != PROG && n >1)
	printf("	bound	%d\n", n);
}

int locctr(l) int l;
{
    register int temp;
    /* l is PROG, ADATA, DATA, STRNG, ISTRNG, or STAB */

    if (l == lastloc )
	return(l);
    temp = lastloc;
    lastloc = l;
    switch (l) {

	case PROG:
	    if (handopt)
#ifdef TWOPASS
		printf ("%cdsect\n",IDATA);	/* all o/s code is dsect */
#else
		printf ("\tdsect\n");	/* all o/s code is dsect */
#endif
	    else
#ifdef TWOPASS
		printf ("%ccsect\n",ITEXT);
#else
		printf ("\tcsect\n");
#endif
	    psline();
	    break;

	case FDATA:
#ifdef TWOPASS
	    printf ("%cdsect\n",IDATA);
#else
	    printf ("\tdsect\n");
#endif
	    break;

	case DATA:
	case ADATA:

#ifdef TWOPASS
	    printf ("%cdsect\n",IDATA);
#else
	    printf ("\tdsect\n");
#endif
	    break;

	case STRNG:
#ifdef TWOPASS
    	    printf ("%cdsect\n",IDATA);
#else
	    printf ("\tdsect\n");
#endif
	    break;

	case ISTRNG:
#ifdef TWOPASS
    	    printf ("%cdsect\n",IDATA);
#else
	    printf ("\tdsect\n");
#endif
	    break;

	case STAB:
	    printf("	.stab\n");
	    break;

	default:
	    cerror("illegal location counter");
    }

    return(temp);
}

/*
**  output line of text from the source
*/
void
defloi(s)
char *s;
{
#ifndef NOCAID
    if (gdebug) {
    	char *cp1, *cp2, oldchar;
    	/* only print if same program */
    	for(cp1 = cp2 = ftitle; *cp2; cp2++)
    	    if(*cp2 == '/' || *cp2 == ')') cp1 = cp2;
    	oldchar = *cp1;		/* save old char */
    	*cp1 = '\"';
#ifdef mpx
    	if (stricmp(currprog, cp1) == 0) {
#else
    	if (strcmp(currprog, cp1) == 0) {
#endif
    	    *cp1 = oldchar;
    	    slineno = lineno;	/* save our line number */
    	    if(fdefflag)	/* if in function do E.?? */
    		printf(" .xeq s.%d %s", lineno, s);
    	    else		/* else do S.?? */
    		printf(" .src s.%d %s", lineno, s);
    	} else {
    	    *cp1 = oldchar;
    	    printf(" .com s.%d %s", slineno, s);
    	}
    } else {
    	if (lflag && gdebug == 0)
    	    printf("* %s", s);
    }
#else
    if (lflag) {
    	printf("* %s", s);
    }
#endif
}

/* get a line of input.  called from scan.c   */

int getloi ( s, lim )                    /*  right from the book.  */
char s [];
int lim;
{
 int c, i;

 for(i = 0; --lim >0 && (c =getchar()) != EOF && (s[i++] = c) != '\n';);
 if ((s[i-1] == '\n') && (i >1)) {
  while ((s[i-2] == ' ') && (i >1)) --i;
  s[i-1] = '\n';
 }
 s [ i ] = '\0';
 return ( i );
}

void deflab(n) int n;
{
 /* output something to define the current position as label n */

#ifdef ONEPASS
    if( lastloc == PROG )
/*    printf("L%d 	equ 	$\n", n); */
    	printf("L%d\tcequ\t$\n", n);
    else
    	printf("L%d\tdequ\t$\n", n);
#else
    if( lastloc == PROG )
	printf("%c%d\t\n", ILABEL, n);
    else
/*    	printf("L%d\tequ\t$\n", n); */
    	printf("L%d\tdequ\t$\n", n);
#endif
}

int         crslab = 10;

int getlab()
{
 /* return a number usable for a label */
    return(++crslab);
}

#ifdef TWOPASS
int         crs2lab = 99999;

int get2lab()
{
 /* return a number usable for a label */
    return(crs2lab--);
}
#endif

int         reg_use = 7;
extern      int calloff, autooff;

void efcode()
{
 /* code for the end of a function */

    register struct symtab *p;
    register TWORD	t;
    int	i;
    int	tsz=0;	/* Used to detect func(s) that return >2 words */
    char	*nm;	/* external name of symbol */

#ifndef BUG2
    if(edebug) {
	printf("efcode(): strftn = %d, curftn:\n", strftn);
	prstab(curftn);
    }
#endif

    if (strftn) {	/* copy output (in R2(NP) or R0(PN)) to caller */
	register NODE  *l, *r;
	register int    j;
        int	sz;

	p = &stab[curftn];
	t = p->stype;
	t = DECREF(t);

#ifndef ONEPASS
	printf("%c\n",FEND);
#endif	/* ONEPASS */

	tsz = tsize(t, p->dimoff, p->sizoff); /* Rev G */

	i = getlab();		/* label for return area */
	sz = tsize(t, p->dimoff, p->sizoff) / SZCHAR;
#ifdef OLDWAY
	if (sz % sizeof(int))
	    sz += sizeof(int) - (sz % sizeof(int));
#else
	if (sz % (SZINT/SZCHAR))
	    sz += (SZINT/SZCHAR) - (sz % (SZINT/SZCHAR));
#endif
	locctr (DATA);
	defalign (ALDOUBLE);
	deflab (i);
	zecode (sz / (SZINT/SZCHAR));
	locctr (PROG);

	deflab(retlab);

	psline();
	printf("	la	r1,L%d\n", i);

	reached = 1;
	l = block(REG, NIL, NIL, PTR | t, p->dimoff, p->sizoff);
	l->tn.rval = 1;	/* R1 */
	l->tn.lval = 0;	/* id cookie */

	l = buildtree(UNARY MUL, l, NIL);

	r = block(REG, NIL, NIL, PTR | t, p->dimoff, p->sizoff);
	r->tn.rval = 0;	/* R0 */
	r->tn.lval = 0;
	r = buildtree(UNARY MUL, r, NIL);

	l = buildtree(ASSIGN, l, r);
	l->in.op = FREE;

#ifndef BUG2
	if(edebug) {
		printf("efcode(): before ecomp()\n");
		fwalk(l->in.left, eprint, 0);
	}
#endif

	ecomp(l->in.left);
	printf("	la	r0,L%d\n", i);

 	/* turn off strftn flag, so return sequence will be generated */
	strftn = 0;
    }
    else {

#ifndef ONEPASS
	printf("%c\n",FEND);
#endif	/* ONEPASS */
#ifndef MPX
	branch(retlab);
#endif
	deflab(retlab);
    }
    p = &stab[curftn];
    t = p->stype;
    t = DECREF(t);

    i = t == DOUBLE ? 2 : (t == UNDEF ? 0 : 1);
    if( (t == STRTY || t == UNIONTY) && tsz <= 2*SZINT) {
	if(tsz <= SZINT)
		i = 1;
	else
		i = 2;
    }

    if ((retstat & (RETVAL | NRETVAL)) == (RETVAL | NRETVAL)) {
	werror("function contains both return and return(expr)");
    }
    if (!(retstat & RETVAL)) {
	if (t != INT && t != UNDEF) {
	    werror("function has a declared type but never returns a value");
	}
	i = 0;
    }

#ifdef MPX
    nm = exname (p->sname, p);
    printf ("\tlf\tr2,2w,sp\n");
    printf ("\ttrsw\tr2\n");
#else
    printf ("	exit	%d,LA%d\n", i, ftnno);
#endif /* MPX */

    {
    int ii;
    ii = (reg_use >= (MINRVAR - 1)) ? reg_use : MINRVAR;
    reg_use = 7;

    dumpstr();

#ifndef ONEPASS
    printf("%c%d\t\n",BEND,ii);
#else	/* not ONEPASS */
    p2bend(ii);
#endif	/* ONEPASS */
    }

    printf("*	.ef #%d %s\n", ftnno, nm);
    fdefflag = 0;
#ifndef BUG2
    if(ddebug) {
	printf("efcode() complete\n");
    }
#endif
}

int         ftlab1, ftlab2;

void bfcode(a, n) int a[], n;
{
 /*
  * code for the beginning of a function;
  * a is an array of indices in stab for the arguments;
  * n is the number
  */
    register    int i;
    register    int temp;
    register struct symtab *p;
    struct symtab *r;
    int         off;
    char       *toreg();
    char        regarg[20];
    char	*nm;	/* external name of symbol */
    int		basemask;

    p = &stab[curftn];
#ifndef BUG2
    if(ddebug) {
	printf("bfcode(): ftnno = %d\n", ftnno);
	prstab(curftn);
	for(i=0; i < n; ++i) {
		printf("arg %d:\n", i);
		prstab(a[i]);
	}
    }
#endif
#ifndef NOCAID
#ifdef XXXX_CAID
    for(i=0; i < n; ++i) {
    	r = &stab[a[i]];
    	printf("*ARG%d.%d .arg %s ", ftnno, i, r->sname);
    	tprint(r->stype);
    	printf(" LA%d+%db\n", ftnno, r->offset/SZCHAR);
    }

#endif
#endif
    nm = exname (p->sname, p);

    locctr(PROG);
#ifdef NOCAID
    printf("*	.bf #%d %s\n", ftnno, nm);
#endif
    printf ("\tbound\t1w\n");
#ifndef NOCAID
    if (p->sclass == EXTDEF) {
    	printf("*	.ebf #%d %s\n", ftnno, nm);
    } else {
    	printf("*	.sbf #%d %s\n", ftnno, nm);
    }
#endif
    defnam(p);

    temp = p->stype;
    temp = DECREF(temp);
    strftn = (temp == STRTY) || (temp == UNIONTY);

    retlab = getlab();

 /* routine prolog */

#ifndef NOCAID
#ifdef DO_LINE_STABS
#ifdef NOT_4_NOCAID
    printf("*.stabd 0x%x,0,%d\n", N_SLINE, lineno);
#endif
#endif
#else
    if (gdebug)
    	printf("	.stabd	0x%x,0,%d\n", N_SLINE, lineno);
#endif

        printf("\ttrr\tsp,r1\n");
#ifndef SECTION_FIX
	printf("\tsumw\tsp,SLA%d\n", ftnno);
#else /* SECTION_FIX */
	printf("\tsumw\tsp,=LA%d\n", ftnno);
#endif /* SECTION_FIX */
	printf("\tstd\tr0,2w,sp\n");
	printf("\tstf\tr4,4w,sp\n");
#ifdef XXXX
    	printf("*X.%d	.beg %s\n", ftnno, nm);
    	printf("X.%d equ $\n", ftnno);
#endif

    off = ARGINIT;
    i = 0;

    if (proflg) {		/* profile code */
	temp = getlab();

	basemask = 0; /* Initially clear the "basemask" value */

	printf("\
	la	r1,L%d\n\
	call	mcount,x'%x',0\n\
L%d	farlcommon	L%d(1)\n",
		temp,
		basemask,
		temp, temp);
	psline();

    }
    else {
	if (n >0) {
	    p = &stab[a[0]];

	    if (p->stype == STRTY || p->stype == UNIONTY) {
		if (SAflag)
		    werror ("First arg of funct is struct");
	    }
	}
    }

#ifndef ONEPASS
    p = &stab[curftn];		/* (MEY) NP1 code above clobbers p */
    printf("%c%s\n",FBEGIN,p->sname);
    printf("%c%d\t\n", PFHERE, ftnno); /* Optimizer to put param fetches here */

    if (n>0) {
        p = &stab[a[0]];  	/* (MEY) (22-Jan-87) Fixed for PCO */
        StabInfoPrint(p);
    }
#endif /* ONEPASS */


    for (; i < n; ++i) {
	p = &stab[a[i]];
#ifndef ONEPASS
	StabInfoPrint(p);
#endif
	if (p->sclass == REGISTER) {
	    temp = p->offset;		/* save register number */
	    p->sclass = PARAM;	/* forget that it is a register */
	    p->offset = NOOFFSET;
	    oalloc(p, &off);
#ifdef ONEPASS
   	    ParamFetch(temp, p->offset/SZCHAR, p->stype, ftnno);
#else
	    printf("%c%d\t%d\t%d\t\n", PFETCH, temp,
		p->offset/SZCHAR, p->stype);
#endif
	    p->offset = temp;		/* remember register number */
	    p->sclass = REGISTER;	/* remember that it is a register */
	}
	else {
	    if (p->stype == STRTY || p->stype == UNIONTY) {
		p->offset = NOOFFSET;
		if (oalloc(p, &off))
		    uerror("bad argument");
		SETOFF(off, ALSTACK);
	    }
	    else {
		if (oalloc(p, &off))
		    uerror("bad argument");
	    }
	}

    }

/*
 *	Add farscan hook here when "func:variable" implemented.
 *	If p->sflags & SGERRYREF then rescan farlist file,
 *	and make SGERRYMANDER entries for all variables that
 *	are qualified with this function's name.
 *	Make the entries at blevel 2 so they will be ripped
 *	out automatically at the end of the function.
 *	Modify farscan1() to create the SGERRYREF entries.
 */

#ifndef ONEPASS
    printf("%c%d\t\n", PSAVE, 42/*filler*/);
#endif
    fdefflag = 1;
}

void bccode()
{	/* called just before the first executable statment */
 /* by now, the automatics and register variables are allocated */
#ifdef MPXTEMP
    SETOFF(autooff, SZDOUBLE);
#else
    SETOFF(autooff, SZINT);
#endif
 /* set aside store area offset */

    locctr(PROG);

#ifndef ONEPASS
    printf("%c%d\t%d\t%d\t\n",BBEG,ftnno,autooff,regvar);
#else
    p2bbeg(autooff, regvar);
#endif

    reg_use = (reg_use >regvar ? regvar : reg_use);
}

int extflg;
char *extfun[EXTFUNS] = {
    "_cvtld",		/* C_LD */
    "_cvtdl",		/* C_FL */
    "_cvtuld",		/* C_ULD */
    "_cvtdul",		/* C_DUL */
    "_cvtif",		/* C_IF */
    "_cvtfi",		/* C_FI */
    "_cvtuif",		/* C_UIF */
    "_cvtfui",		/* C_FUI */
    "_f.call",		/* C_FC */
    "_f.calld",		/* C_FCD */
};

void ejobcode(flag) int flag;
{
    /* called just before final exit */
    /* flag is 1 if errors, 0 if none */
    int i;
    register int isfunct;
    register char *name;
    register struct symtab *p;

    dumpstr();

#ifdef TWOPASS
    printf("%c\n",EOJFLG);
#endif

    /* print 'EXT' declarations for undefined external functions */

    for (i = 0; i < SYMTSZ; i++){
    	if( stab[i].stype == TNULL) continue;
    	p = &stab[i];
    	name = exname (p->sname, p);
    	isfunct = ISFTN( stab[i].stype );
    	switch( stab[i].sclass ){
    	    case EXTERN:
    	    case FORTRAN:
    	    case UFORTRAN:
    		if ( isfunct ) {
    		    if( stab[i].suse >0 )
    			break;  /* declared but not used */
    		    printf("	ext	%s\n", name);
    		} else {
    		    if( stab[i].suse >0 )
    			break;  /* declared but not used */
    		    printf("	ext	%s\n", name);
    		/*  commdec( i ); */
    		}
    		break;
    	    case EXTDEF:	/* external definition */
    		/* output all def's, referenced or not */
    		printf("	def	%s\n", name);
    		break;
    	}
    }
    /* now print out external functions called */
    if (extflg) {
    	for( i = 0; i < EXTFUNS; i++)
    	    if (extflg & (1 << i))
		if (_flag)
		    printf("	ext	%s\n", &extfun[i][1]);
		else
		    printf("	ext	%s\n", extfun[i]);
    }

  if(handopt) {
    locctr (DATA);
/*     printf ("	dsect\n	end\n"); */
    printf ("	end\n");
  } else {
    locctr (PROG);
/*     printf ("	csect\n	end\n"); */
    printf ("	end\n");
  }
}

void aobeg()
{
 /* called before removing automatics from stab */
}

void aocode(p) struct symtab    *p;
{
 /* called when automatic p removed from stab */
}

void aoend()
{
 /* called after removing all automatics from stab */
}

void defnam(p) register struct symtab   *p;
{
 /* define the current location as the name p->sname */
    register char *nm;

    if (p->sclass == STATIC && p->slevel >1)
	deflab(p->offset);
    else {
	nm = exname(p->sname, p);
    if( lastloc == PROG )
	printf("%s cequ  $\n", nm);
    else
/*	printf("%s equ  $\n", nm); */
	printf("%s dequ  $\n", nm);
    }
}

struct	tstrngs *begstrng = NULL; 	/* beginning list of init strings */
struct	tstrngs *currstng = NULL; 	/* current entry of init string */

static int putting = 0;

void putstring(s,i,ct)
char *s;
int  i, ct;
{
	char    *ss = s+ct;
	int	ii;

	i--;		/* so we dont put out the terminating null byte */
	if(ct == 0)
	{			/* unbounded -- normal -- string */
		putting = 0;
		printf("\tdatab\tc'");
		for(ii = 0; ii < i; ii++)
			putabyte( *s++);
		printf("\"@'\n");
		inoff += SZCHAR;	/* MON */
	}
	else
	{       		/* a constrained string */
		if(i >0)	/* not a null string	*/
		{
			int lim = i < ct ? i : ct;
			putting = 0;
			printf("\tdatab\tc'");
			for(ii = 0; ii < lim; ii++)
				putabyte( *s++);
			printf("'\n");
		}
	}
}

void putabyte(v)
char    v;
{
	inoff += SZCHAR;
	if(++putting >= 32)
	{       /* break string onto several lines */
		putting = 1;
		printf("'\n\tdatab\tc'");
	}

	if (v < ' ') {
		putchar('"');
		putchar(v+64);
		putting++;	/* for extra char */
		return;
	}

	if (v > '~') {
		printf("',x'%x',c'",v);
		putting += 12;	/* for extra chars */
		return;
	}

	/* undo funny characters */
	switch(v)
	{
	case '%':
	case '"':
	case '\'':
	case ';':
		putchar('"');
		putting++;	/* for extra char */
	default:
		putchar(v);
	}
}

void dumpstr()
{
	char *strptr;
    	int xz = 0;

    	if (begstrng) {
	    locctr(DATA);
    	    xz = 1;
    	}
	while (begstrng)
	{
		char *p;
		int  lim, i;

	    if (begstrng->slabel >= 0) {
		deflab(begstrng->slabel);
		putting = 0;
		printf("\tdatab\tc'");
		p = begstrng->strng;
		lim = begstrng->length - 1;
		/* -1 so we dont put out the null byte */
		for(i = 0; i < lim; i++,p++)
			putabyte( *p);
		printf("\"@'\n");
	    } else {
		printf("L%d\tdata%s\n",-begstrng->slabel, begstrng->strng);
	    }
		free(begstrng->strng);  /* string area is removed */
		currstng = begstrng;    /* so free will work      */
		begstrng = begstrng->next;
		free(currstng);         /* string struct is gone  */
	}
    	if(xz)
	    SETOFF(inoff,SZINT);	/* MON */
	currstng = NULL;
	begstrng = NULL;
    	if(xz)
	    locctr(PROG);
}

void zecode(n) int n;
{
    /* n integer words of zeros */
    OFFSZ       temp;
    if (n <= 0)
	return;
    printf("\trez\t%d\n", (SZINT / SZCHAR) *n);
    temp = n;
    inoff += temp * SZINT;
}

int fldal(t) unsigned int  t;
{		/* return the alignment of field of type t */
    uerror("illegal field type");
    return(ALINT);
}

void fldty(p) struct symtab *p;
{		/* fix up type of field p */
    ;
}

void where(c) int c;
{		/* print location of error  */
 /* c is either 'u', 'c', or 'w' */
    fprintf(stderr, "%s, line %d: ", ftitle, lineno);
}

void swepilog( p, n )
	register struct sw *p;
	register int n;
{
	/* p points to an array of structures, each consisting
	 * of a constant value and a label.
	 * The first is >=0 if there is a default label;
	 * its value is the label number
	 * The entries p[1] to p[n] are the nontrivial cases
	 */

#ifdef ONEPASS
	genswitch( p, n, 0 );	/* someday this 0 will be a register number */

#else /* TWOPASS */

	register int i;

#ifdef OPTIMIZER
	/* front end opt cannot have switch fall through */
	if(p[0].slab < 0 )
		p[0].slab = brklab;
#endif

	printf("%c%d\t%d\t%d\t\n", ESWITCH, n, 0, p[0].slab); /* this 0 too */
	for( i = 1; i <= n; i++ )
	{
		printf(CONFMT, p[i].sval );
		printf("\t%d\t\n", p[i].slab );
	}
#endif
}

int main(argc, argv) int argc; char  *argv[];
{
#ifdef BUFSTDERR
    char        errbuf[BUFSIZ];
    setbuf(stderr, errbuf);
#endif
#ifdef TESTING
    setbuf(stdout, NULL);
#endif
    return(mainp1(argc, argv));
}

void p1init()
{
    char *cp1, *cp2;
    int pcnt = 0;

    strcpy(currprog, ftitle);
    for(cp1=cp2=ftitle; *cp2; cp2++)
    	if(*cp2 == '/' || *cp2 == ')') cp1 = cp2+1;
    printf("	program	");
    for (cp2 = cp1; *cp2; cp2++) {
    	if (*cp2 == '\"') continue;
    	if (*cp2 == '.') break;
    	printf("%c", *cp2 < 'a' ? *cp2 : *cp2 - ('a' - 'A'));
    	progname[pcnt++] = *cp2;
    }
    progname[pcnt] = '\0';
    printf("\n");
#ifdef MYATOF
    printf("	list	mac,nong\n");
#else
    printf("	list	mac,nong,nodata\n");
#endif
    printf("*\n");
#ifdef NASA
    printf("r0	equ	0\n");
    printf("r1	equ	1\n");
    printf("r2	equ	2\n");
    printf("r3	equ	3\n");
    printf("r4	equ	4\n");
    printf("r5	equ	5\n");
    printf("r6	equ	6\n");
    printf("r7	equ	7\n");
/*    printf("*\n"); */
    printf("sp	equ	3\n");
#else
    printf("r0	dequ	0\n");
    printf("r1	dequ	1\n");
    printf("r2	dequ	2\n");
    printf("r3	dequ	3\n");
    printf("r4	dequ	4\n");
    printf("r5	dequ	5\n");
    printf("r6	dequ	6\n");
    printf("r7	dequ	7\n");
/*    printf("*\n"); */
    printf("sp	dequ	3\n");
#endif
    printf("*\n");
#ifdef SECTION_FIX
    if (handopt)
    	locctr(DATA);
/*  printf("\tdsect\n"); */
    else
    	locctr(PROG);
/*  printf("\tcsect\n"); */
/* locctr(PROG); */
    if (!handopt)
    	printf("	dataw	x'2243223a'\n");  /* magic number */
/*    	printf("	slad	r4,3\n	srld	r4,26\n");  /* magic number */
#endif /* SECTION_FIX */
}
