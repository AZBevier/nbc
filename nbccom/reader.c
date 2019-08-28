/* reader.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid = "$Id: reader.c,v 1.12 2019/02/24 19:24:28 jbev Exp $";
#endif

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

/*
 * $Log: reader.c,v $
 * Revision 1.12  2019/02/24 19:24:28  jbev
 * Remove stdlib.h include for mpx
 *
 * Revision 1.11  2019/01/31 22:02:16  jbev
 * Update for Linux
 *
 * Revision 1.10  1997/01/22 18:28:07  jbev
 * Correct pointer/integer problem with error messages.
 * Only on Alpha because of 64 bit pointers and 32 bit ints.
 *
 * Revision 1.9  1996/10/26 22:29:03  jbev
 * Fix for Alpha Port
 * l.
 *
 * Revision 1.8  1996/03/20 23:43:30  jbev
 * Use O/S malloc function for alpha, not internal function.
 * More mods for alpha port.
 *
 * Revision 1.7  1996/03/20 22:00:18  jbev
 * Use unbuffered stdout for alpha machines.
 *
 * Revision 1.6  1996/03/19 00:14:41  jbev
 * Mods for Alpha port.
 *
 * Revision 1.5  1995/03/06 22:14:41  jbev
 * Correct xdebug, edebug definitions for 1 pass operation.
 *
 * Revision 1.4  1995/03/06  19:18:32  jbev
 * Malloc tree node table instead of hard coding size.
 * Allow XTTval  and X2TTval to set node tree table size.
 * Add new option XJ and X2J to inhibit _ being prepended to names.
 * Correct XT[DS]val options for setting table sizes.
 *
 */

#include "mfile2.h"
#ifndef mpx
#include <stdlib.h>
#endif

/*	some storage declarations */

#ifdef TWOPASS
#ifdef NOW_MALLOCED
NODE	node[TREESZ];
#else
NODE	*nodep;
int	TREESIZE;
#endif
char	filename[100] = "";		/* the name of the file */
int	ftnno;				/* number of current function */
int	lineno;
int	fdefflag = 0;			/* we are in a function */
int	handopt;			/* this is an MPX handler */
int	_flag;				/* Don't prepend _ to names */
#else /* TWOPASS */
extern int  handopt;			/* this is an MPX handler */
extern int _flag;			/* Don't prepend _ to names */
#endif

#ifdef ONEPASS
#define NOMAIN
#endif

int divflag = 0;

int	noreg;		/* set non zero for no reg-reg instrs */
int         nrecur;
extern int  Wflag;

#ifndef BUG1
#ifdef TWOPASS
int         edebug = 0;
int         xdebug = 0;
#else
extern  int edebug;
#endif
int         udebug = 0;
int         vdebug = 0;
#endif

/* offset for first temporary, in bits for current block */
OFFSZ       tmpoff;
/* maximum temporary offset over all blocks in current ftn, in bits */
OFFSZ       maxoff;
int         maxtreg;

NODE       *stotree;
int         stocook;

OFFSZ       baseoff = 0;
OFFSZ       maxtemp = 0;

int p2init(argc, argv) int argc; char    *argv[];
{
   /* set the values of the pass 2 arguments */
    register int    c;
    register char  *cp;
    register    int files;

    allo0();		/* free all regs */
    files = 0;

    TREESIZE = TREESZ;	/* set default tree size */

    for (c = 1; c < argc; ++c) {
	if (*(cp = argv[c]) == '-') {
	    if(!( *(cp+1) == 'X' && *(cp+2) == '2'))
		continue;

	    cp +=2;
	    while (*++cp) {
		switch (*cp) {

		    case 'J':	/* Don't prepend _ to names */
			_flag = 1;
			break;

		    case 'H':	/* this an MPX handler */
			handopt = 1;
			break;

    		    case 'N':	/* no reg reg instructions */
    			noreg = 1;
    			break;

		    case 'l': 	/* linenos */
			++lflag;
			break;

#ifndef BUG1
		    case 'e': 	/* expressions */
			++edebug;
			break;

		    case 'o': 	/* orders */
			++odebug;
			break;

		    case 'r': 	/* register allocation */
			++rdebug;
			break;

		    case 'a': 	/* rallo */
			++radebug;
			break;

		    case 'v': 
			++vdebug;
			break;

		    case 't': 	/* ttype calls */
			++tdebug;
			break;

		    case 's': 	/* shapes */
			++sdebug;
			break;

		    case 'u': 	/* Sethi-Ullman testing (machine dependent) */
			++udebug;
			break;

		    case 'x': 	/* general machine-dependent debugging flag */
			++xdebug;
			break;

		    case 'D': 	/* debug all */
			++edebug;
			++odebug;
			++radebug;
			++rdebug;
			++sdebug;
			++tdebug;
			++udebug;
			++vdebug;
			++xdebug;
			break;
#endif

		    case 'w': 
		    case 'W': 	/* shut up warnings */

			++Wflag;
			break;
		    case 'g':
			break;

		    case 'T':
			switch(*++cp) {
				case 'T':
				{
					int size;
					size = atoi(++cp);
					if (size >TREESZ) {
					    TREESIZE = size;
					    fprintf(stderr,
"Warning: Tree Node Table Size is %d (default is %d)\n",TREESIZE, TREESZ);
					} else
					    fprintf(stderr,
"Warning: Invalid Tree Node Table Size (Using Default)\n");
					continue;
				}
				default:
		werror("illegal -T[DST]VALUE option ignored");
					continue;
			}
		    default: 
			wderror("bad option: %c", *cp);

		    } /* end switch */
		} /* end while */
	}
	else
	    files++;		/* assumed to be a filename */

    } /* end for */

    nodep = (NODE *)domalloc(sizeof(NODE) * TREESIZE);
    if ((int)nodep <= 0)
       cerror("Out of memory: Can not alloc Node Tree Table");
    mkdope();
    setrew();
    return(files);
}

#ifndef NOMAIN

#ifdef TWOPASS
void
CopyLine()	/* Copy rest of intermediate code line to stdout */
{
	int c;

	while( (c=getchar()) > 0 ){
		PUTCHAR(c);
		if( c == '\n' ) break;
	}
	return;
}
#endif

unsigned int caloff();

#ifdef TWOPASS
extern unsigned int offsz;
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

#else /* TWOPASS */

unsigned int offsz;
#endif /* TWOPASS */

int mainp2( argc, argv ) int argc; char *argv[]; {
	int files, i;
	register int temp;
	register int c;
	register char *cp;
	register NODE *p;
    static int  myftn = -1;
	int swreg, temp_label;
#ifdef TWOPASS
    char ftmpname[30];
#endif

	files = p2init( argc, argv );
	tinit();
	if( files ){
	    files = 0;
	    for (i = 1; i < argc; ++i) {
		if (*argv[i] != '-') {
			switch (files++) {
			case 0:
				if (!(freopen(argv[i],"r",stdin))) {
					fprintf(stderr,"c1: can't open input file %s\n",argv[i]);
					exit(1);
				}
				break;
			case 1:
				if (!(freopen(argv[i],"w",stdout))) {
					fprintf(stderr,"c1: can't open output file %s\n",argv[i]);
					exit(1);
				}
				break;
			default: ;
			} /* end switch */
		} /* end if */
		} /* end for */
	} /* end if */

#ifdef __alpha_NOMORE
	/* alpha core dumps with buffered stdout */
	setbuf(stdout,NULL);
#endif
#ifdef SLOWWAY
setbuf(stdout,NULL); /*XXX*/
#endif
	offsz = caloff();
	while( (c=getchar()) > 0 ) switch( c ){

	case '\n': continue;	/* ignore blank line */

	case ITEXT:	/* text/data indicator used by optimizer. */
    		locctr2(ITEXT);
		LookForEOL();
		continue;

	case IDATA:
    		locctr2(IDATA);
		LookForEOL();
		continue;

	case ASM_CCHAR: /* PCO comment.  Replace with -- */
		PUTCHAR('-'); PUTCHAR('-');
		CopyLine();
		continue;

	case IASM:      /* ASM() output. */
		CopyLine();	/* strip first character */
		continue;

	default:	/* who knows? */
		/* copy line unchanged */
		PUTCHAR( c );  /*  initial character */
		CopyLine();
		continue;

	case EXPR:
		/* compile code for an expression */
		lineno = rdin( 10 );
    		/* VOID, reads filename */
		for( cp=filename; (*cp=getchar()) != '\n'; ++cp ) ;
		*cp = '\0';
		if( lflag ) lineid( lineno, filename );

		tmpoff = baseoff;  /* expression at top level reuses temps */
		p = eread();

#ifndef BUG4
		if( edebug ) fwalk( p, eprint, 0 );
#endif

		treeinit(p);
#ifdef MYREADER
		MYREADER(p);  /* do your own laundering of the input */
#endif

		nrecur = 0;
		delay( p );  /* expression statement  throws out results */
		reclaim( p, RNULL, 0 );

		allchk();
		tcheck();
		continue;

	case BBEG:
		/* beginning of a block */
		temp = rdin(10); /* ftnno */
		/* autooff for block gives max offset of autos in block */
		tmpoff = baseoff = (unsigned int) rdin(10); 
		maxtreg = rdin(10);
		if(getchar() != '\n') cerror( "intermediate file format error");

    		if (myftn != temp) {	/* beginning of function */
			maxoff = baseoff;
			ftnno = temp;
    			myftn = ftnno;
			maxtemp = 0;
    			fdefflag = 1;		/* start of a function */
		} else {
			if( baseoff > maxoff ) maxoff = baseoff;
			/* maxoff at end of ftn is max of autos and temps
			   over all blocks in the function */
		}
		setregs();
		continue;

	case BEND:  /* end of block */
    		dumpstr();		/* dump any delayed strings */
    		fdefflag = 0;		/* end of a function */
		p2bend(rdin(10));	/* Read nregs from pass1     */
		while( (c=getchar()) != '\n' ){
			if( c <= 0 ) cerror( "intermediate file format eof" );
		}
		continue;

	case STABINFO:		/* Symbol table information for the optimizer.
				 * We just throw it away.
				 */
		LookForEOL();
		continue;

	case FBEGIN:	/* start of code indicator for global optimizer */

		LookForEOL();
		continue;
		

	case FEND:	/* end of code indicator */
		LookForEOL();
		continue;	/* We just want to throw these away	*/

	case PFHERE:	/* "Put param fetches here" indicator for opt */
		ftnno = rdin(10);	/* for ParamFetch function */
    		sprintf(ftmpname, "FTMP%d", ftnno);  
		LookForEOL();
		continue;	/* We just want to throw these away	*/

	case PFETCH:		/* put a parameter into a register */
		{
			int off;
			TWORD ty;

			temp = rdin(10);
			off = rdin(10);
			ty = rdin(10);
			ParamFetch(temp, off, ty, ftnno);
		}
		LookForEOL();
		continue;

	case PSAVE:	/* "Param Save" indicator for opt */
		(void) rdin(10);
		LookForEOL();
		continue;	/* We just want to throw these away    */

	case ILABEL:	/* Label */
		temp_label = rdin(10);
		LookForEOL();
		deflab(temp_label);
		continue;
		
	case IBRANCH:	/* Unconditional Branch */
		temp_label = rdin(10);
		LookForEOL();
#ifndef NOCAID
		if( lflag ) lineid( lineno, filename );
#endif
		cbgen(0, temp_label, 0);
		continue;

	case IRETURN:	/* A return from a function */
		LclReturn();
		LookForEOL();
		continue;

	case ESWITCH:
		i = rdin(10);
		swreg = rdin(10);
		swtab[0].slab = rdin(10);
		LookForEOL();
		for( temp = 1; temp <= i; temp++ )
		{
			swtab[temp].sval = rdin(10);
			swtab[temp].slab = rdin(10);
			LookForEOL();
		}
		genswitch( swtab, i, swreg);
		continue;

	case EOJFLG:	/* end of job indicator	*/
		LookForEOL();
#if 1
		locctr2(IDATA);
#endif
    		dumpstr();	/* dump any delayed strings */
    		/* now print out external functions called */
    		if (extflg) {
    		    for( i = 0; i < EXTFUNS; i++)
    			if (extflg & (1 << i))
			    if (_flag)	/* don't prepend _ to names */
				printf("	ext	%s\n", &extfun[i][1]);
			    else
				printf("	ext	%s\n", extfun[i]);
    		}
		continue;	/* We just want to throw these away	*/
	    }

	/* EOF */
	return(nerrors);

	}

void LookForEOL()
{
	register int c;

	while( (c=getchar()) != '\n') {
		if (c <= 0) cerror("intermedate file format eof");
	}
}
# endif /* NOT NOMAIN */

#ifdef ONEPASS

void p2compile(p) NODE  *p;
{

    if (lflag)
	lineid(lineno, filename);
    tmpoff = baseoff;	/* expression at top level reuses temps */
#ifndef BUG4
    if (edebug) {
	printf("p2compile(0x%x):\n", p);
	fwalk(p, eprint, 0);
    }
#endif

    /* generate code for the tree p */
    treeinit(p);
#ifdef MYREADER
    MYREADER(p);	/* do your own laundering of the input */
#endif
    nrecur = 0;
    delay(p);		/* do the code generation */
    reclaim(p, RNULL, 0);
    allchk();
}

void p2bbeg(aoff, myreg) int aoff, myreg;
{
    static int  myftn = -1;

    tmpoff = baseoff = (unsigned int) aoff;
    maxtreg = myreg;
    if (myftn != ftnno) {	/* beginning of function */
	maxoff = baseoff;
	myftn = ftnno;
	maxtemp = 0;
    } else {
	if (baseoff > maxoff)
	    maxoff = baseoff;
    /* maxoff at end of ftn is max of autos and temps over all blocks */
    }
    setregs();
}

#endif /* ONEPASS */

void p2bend(nregs) int nregs;
{
    SETOFF(maxoff, ALSTACK);
    eobl2(nregs);
}

/*
 *	Initialize a tree that may have been massaged
 *	by PCO.  This routine must NOT be called from
 *	codgen, store, order or their descendants.
 */

void treeinit(p)
register NODE *p;
{
	register int o;

#ifndef BUG1
	if(edebug) {
		printf("treeinit(%x) entered:\n", p);
		fwalk(p, eprint, 0);
	}
#endif

	o = p->in.op;

#ifdef OPTIMIZER
if (p->in.op == ASSIGN && (p->in.left && p->in.left->in.op == REG) &&
  (p->in.right && p->in.right->in.op == REG) &&
  (isfakereg(p->in.right->tn.rval))) { 
    NODE *x = p->in.right;
    register NODE	*p1, *p2;

    /* Convert tree at p into U& U* original tree */
    /* Dont disturb descendants of p */

    p1 = talloc();

    *p1 = *x;		/* copy original node */

    p1->in.op = OREG;
    p1->in.type = DECREF(x->in.type);
    p1->in.name = "";
    p1->in.left = x->in.left;
    p1->in.right = x->in.right;
    p1->tn.lval = x->tn.lval;

    x->in.op = UNARY AND;  /*UNARY MUL;*/
    x->in.type = x->in.type;
    x->in.name = "";
    x->in.left = p1;

}
#endif

	switch(o) {	/* we may add additional cases later */

	case REG:

		p->tn.lval = 0;		/* clobber PCO cookie */
		if(isfakereg(p->tn.rval)) {
			p->in.op = OREG;
			break;
		}
	    	rbusy(p->tn.rval, p->in.type);
		break;

	case ADDR:
		p->in.op = ICON;
		break;

	}  /* end switch */

	/* visit right, then left, as appropriate */

	o = p->in.op;			/* in case we modified it */

	if(optype(o) == BITYPE)
		treeinit(p->in.right);

	if(optype(o) != LTYPE)
		treeinit(p->in.left);

#ifndef BUG1
	if(edebug) {
		printf("treeinit(%x) returning:\n", p);
		fwalk(p, eprint, 0);
	}
#endif
	return;
}

NODE       *deltrees[DELAYS];
int         deli;

void delay(p) register NODE *p;
{
 /* 
  * look in all legal places for COMOP's and ++ and -- ops to delay
  * note; don't delay ++ and -- within calls or things like 
  * getchar (in their macro forms) will start behaving strangely
  */
    register    int i;

#ifndef BUG1
    if(odebug) {
	printf("delay(%x):\n", p);
	fwalk(p, eprint, 0);
    }
#endif

    /* look for visible COMOPS, and rewrite repeatedly */

    while (delay1(p)) {		/* VOID */
    }

    /* look for visible, delayable ++ and -- */

    deli = 0;
    /* delay2(p);  Dont delay ++, --.  This routine is very suspect. */
    /*			It seems that this routine hardly ever delays, */
    /*			and when it does, it is wrong.  Screws up      */
    /*			things like ((p++ ==a) || p == a)		*/
#ifndef BUG1
    if(odebug) {
	printf("delay() after delay2(), p = %x\n", p);
	fwalk(p, eprint, 0);
    }
#endif
    codgen(p, FOREFF);			/* do what is left */
    for (i = 0; i < deli; ++i) {
#ifndef BUG1
	if(odebug) {
		printf("delay(): deltrees[%d] = 0x%x\n:", i, deltrees[i]);
		fwalk(deltrees[i], eprint, 0);
	}
#endif
	codgen(deltrees[i], FOREFF);	/* do the rest */
    }
}

int delay1(p) register NODE    *p;
{				/* look for COMOPS */
    register    int o, ty;

    o = p->in.op;
    ty = optype(o);
    if (ty == LTYPE)
	return(0);
    else
	if (ty == UTYPE)
	    return(delay1(p->in.left));

    switch (o) {

	case QUEST: 
	case ANDAND: 
	case OROR: 
        /* don't look on RHS */
	    return(delay1(p->in.left));

	case COMOP: 		/* the meat of the routine */
	    delay(p->in.left); /* completely evaluate the LHS */
        /* rewrite the COMOP */
	    {
		NODE       *q;		/* TMK removed register */
		q = p->in.right;
		ncopy(p, p->in.right);
		q->in.op = FREE;
	    }
	    return(1);
    }

    return(delay1(p->in.left) || delay1(p->in.right));
}

void delay2(p) register NODE    *p;
{

 /* look for delayable ++ and -- operators */

    register    int o, ty;
    o = p->in.op;
    ty = optype(o);

    switch (o) {

	case NOT: 
	case QUEST: 
	case ANDAND: 
	case OROR: 
	case CALL: 
	case UNARY CALL: 
	case STCALL: 
	case UNARY STCALL: 
	case FORTCALL: 
	case UNARY FORTCALL: 
	case COMOP: 
	case CBRANCH: 
    /* 
     * for the moment, don't delay past a conditional context, or
     * inside of a call
     */
	    return;

	case UNARY MUL: 
	    /* if *p++, do not rewrite */
	    if (autoincr(p))
		return;
	    break;

	case INCR: 
	case DECR: 
	    if (deltest(p)) {
		if (deli < DELAYS) {
		    NODE       *q;		/* removed register */
		    deltrees[deli++] = tcopy(p);
		    q = p->in.left;
		    p->in.right->in.op = FREE;      /* zap constant */
		    ncopy(p, q);
		    q->in.op = FREE;
		    return;
		}
	    }

    }

    if (ty == BITYPE)
	delay2(p->in.right);
    if (ty != LTYPE)
	delay2(p->in.left);
}

void codgen(p, cookie) NODE *p;
int cookie;
{

 /* generate the code for p; order may call codgen recursively */
 /* cookie is used to describe the context */

    for (;;) {
	canon(p);	/* creats OREG from * if possible and does sucomp */
	stotree = NIL;
#ifndef BUG4
	if (edebug) {
	    printf("codgen(): store called on:\n");
	    fwalk(p, eprint, 0);
	}
#endif
	store(p);
	if (stotree == NIL)
	    break;

	/* because it's minimal, can do w.o. stores */

#ifndef BUG1
	if (edebug) {
	    printf("codgen(): calling order in for loop:\n");
	}
#endif
	order(stotree, stocook);
    }

#ifndef BUG1
    if (edebug) {
        printf("codgen(): calling order:\n");
    }
#endif
    order(p, cookie);

}

#ifndef BUG1
int         odebug = 0;
#endif

void order(p, cook) NODE    *p;
int cook;
{
    register    int o, ty, m;
    int         m1;
#ifndef FORT
    int         cookie;
#else /* FORT */
    int         cookie, orig_cook = cook;
#endif /* FORT */
    NODE       *p1, *p2;
    int		my_nrecur;

    cookie = cook;
    rcount();
    my_nrecur = nrecur;

#ifndef BUG4
    if (odebug) {
	printf("order1( %x, ", p);
	print("cookie", cookie);
	printf(" ):  my_nrecur = %d\n", my_nrecur);
	fwalk(p, eprint, 0);
	prbusy();
    }
#endif
    canon(p);
    rallo(p, p->in.rall);
    goto first;
 /* 
  * by this time, p should be able to be generated without stores;
  * the only question is how
  */
again: 

#ifndef BUG4
    if (odebug) {
	printf("order2( %x, ", p);
	print("cookie", cookie);
	printf(" ):  again:  my_nrecur = %d\n", my_nrecur);
	prbusy();
	fwalk(p, eprint, 0);
    }
#endif
    if (p->in.op == FREE)
	goto out;	/* whole tree was done */
    cookie = cook;
    rcount();
    canon(p);
    rallo(p, p->in.rall);
 /* 
  * if any rewriting and canonicalization has put
  * the tree (p) into a shape that cook is happy
  * with (exclusive of FOREFF, FORREW, and INTEMP)
  * then we are done.
  * this allows us to call order with shapes in
  * addition to cookies and stop short if possible.
  */
 /* note: SANY == FOREFF */
    if (tshape(p, cook & (~(FOREFF | FORREW | INTEMP))))
	goto out;

first: 
#ifndef BUG4
    if (odebug) {
	printf("order3( %x, ", p);
	print("cookie", cookie);
	printf(" ): first: my_nrecur = %d\n", my_nrecur);
	fwalk(p, eprint, 0);
    }
#endif

    o = p->in.op;
    ty = optype(o);

 /* first of all, for most ops, see if it is in the table */

 /* look for ops */

    switch (m = p->in.op) {

	default: 
	    /* look for op in table */
	    for (;;) {
		if ((m = match(p, cookie)) == MDONE)
		    goto cleanup;
		else
		    if (m == MNOPE) {
			if (!(cookie = nextcook(p, cookie)))
			    goto nomat;
			continue;
		    }
		    else
			break;
	    }
	    break;

	case COMOP: 
	case FORCE: 
	case CBRANCH: 
	case QUEST: 
	case ANDAND: 
	case OROR: 
	case NOT: 
	case UNARY CALL: 
	case CALL: 
	case UNARY STCALL: 
	case STCALL: 
	case UNARY FORTCALL: 
	case FORTCALL: 
    /* don't even go near the table... */
	    ;

    }
    /* get here to do rewriting if no match 
     * or fall through from above for hard ops */

    p1 = p->in.left;
    if (ty == BITYPE)
	p2 = p->in.right;
    else
	p2 = NIL;

#ifndef BUG4
    if (odebug) {
	printf("order4( %x, ", p);
	print("cookie", cook);
	printf(" ), cookie ");
	print("cookie", cookie);
	printf(", rewrite %s, my_nrecur = %d\n", opst[p->in.op], my_nrecur);
	fwalk(p, eprint, 0);
	prbusy();
    }
#endif
    switch (m) {
	default: 
    nomat: 
	    if(lastditch(p, cook))
		goto again;
	    
                cerror("no table entry for op %s", opst[p->in.op]);

	case UMULP:
	    if (p1->in.op == UNARY MUL) {
		order (p1->in.left, INAREG);
		canon (p1);
		goto again;
	    }
	    goto nomat;

	case COMOP: 
	    codgen(p1, FOREFF);
	    p2->in.rall = p->in.rall;
	    codgen(p2, cookie);
	    ncopy(p, p2);
	    p2->in.op = FREE;
	    goto cleanup;

	case FORCE: 
	    /* recurse, letting the work be done by rallo */
	    p = p->in.left;
	    cook = INTAREG | INTBREG;
	    goto again;

	case CBRANCH: 
#ifndef BUG1
	if (odebug) {
	printf ("in order @ CBRANCH\n");
	fwalk(p, eprint, 0);
	}
#endif
	    o = p2->tn.lval;
	    cbranch(p1, -1, o);
	    p2->in.op = FREE;
	    p->in.op = FREE;
#ifndef BUG1
	if (odebug) {
	printf ("in order @ CBRANCH after call to cbranch\n");
	fwalk(p, eprint, 0);
	}
#endif
	    goto out;

	case QUEST: 
	    cbranch(p1, -1, m = get2lab());
	    p2->in.left->in.rall = p->in.rall;
	    codgen(p2->in.left, INTAREG | INTBREG);
	    /* force right to compute result into same reg used by left */
	    p2->in.right->in.rall = p2->in.left->tn.rval | MUSTDO;
	    reclaim(p2->in.left, RNULL, 0);
	    cbgen(0, m1 = get2lab(), 'I');
	    deflab(m);
	    codgen(p2->in.right, INTAREG | INTBREG);
	    deflab(m1);
	    p->in.op = REG;	/* set up node describing result */
	    p->tn.lval = 0;
	    p->tn.rval = p2->in.right->tn.rval;
	    p->in.type = p2->in.type;	/* DJK: used to be right type */
	    tfree(p2->in.right);
	    p2->in.op = FREE;
	    goto cleanup;

	case ANDAND: 
	case OROR: 
	case NOT: 		/* logical operators */
	    /* if here, must be a logical operator for 0-1 value */
	    cbranch(p, -1, m = get2lab());
	    p->in.op = CCODES;
	    p->bn.label = m;
	    order(p, INTAREG);
	    goto cleanup;

	case FLD: 		/* fields of funny type */
	    if (p1->in.op == UNARY MUL) {
		offstar(p1->in.left, cook);
		goto again;
	    }

	case UNARY MINUS: 
	    order(p1, INBREG | INAREG);
	    goto again;

	case NAME:	 /* all leaves end up here ... */
	  { int	savetype;

#ifndef BUG1
	    if(odebug) {
		printf("order(0x%x), case NAME:\n", p);
		fwalk(p, eprint, 0);
	    }
#endif
	    if (p->in.op == REG)
		goto nomat;
	
	    if(ISPTR(p->in.type)) {
		savetype = p->in.type;
		p->in.type = INT;
	    	order(p, INTAREG | INTBREG);
		p->in.type = savetype;
		goto again;
	    }

#ifdef FORT
	    /* avoid endless recursion */
	    if (orig_cook == (INTAREG | INTBREG))
		goto nomat;
#endif /* FORT */
	    order(p, INTAREG | INTBREG);
	    goto again;
	  }

	case INIT: 
	    uerror("illegal initialization");
	    goto out;

	case UNARY FORTCALL: 
	    p->in.right = NIL;
	case FORTCALL: 
	    o = p->in.op = UNARY FORTCALL;
	    if (genfcall(p, cookie))
		goto nomat;
	    goto cleanup;

	case UNARY CALL: 
	    p->in.right = NIL;
	case CALL: 
	    o = p->in.op = UNARY CALL;
	    if (gencall(p, cookie))
		goto nomat;
	    goto cleanup;

	case UNARY STCALL: 
	    p->in.right = NIL;
	case STCALL: 
	    o = p->in.op = UNARY STCALL;
	    if (genscall(p, cookie))
		goto nomat;
	    goto cleanup;

    /* 
     * if arguments are passed in register, care must be taken that reclaim 
     * not throw away the register which now
     *  has the result...
     */
	case UNARY MUL: 
	    if (cook == FOREFF) {
	/* do nothing */
		order(p->in.left, FOREFF);
		p->in.op = FREE;
		goto out;
	    }

	    if( p->in.type != STRTY) {
		oreg2(p);
		if(p->in.op != UNARY MUL)
			goto again;
	    }

	    /* end of TCON/HCON hook */

	    if(delincr(p, cook))	/* check for incr/decr ops */
		goto again;		/* and possibly optimize   */
	    offstar(p->in.left, cook);
	    goto again;

	case INCR: 			/* INCR and DECR */
	    if (setincr(p, cook))
		goto again;

	    if(p->in.type != DOUBLE && p->in.type != LONG)
	    	if(delincr(p, cook))
		    goto again;

	    if (cook & FOREFF) {			
                /* result not needed so inc or dec and be done with it */
	        /* x++ => x += 1 */
		p->in.op = (p->in.op == INCR) ? ASG PLUS : ASG MINUS;
		goto again;
	    }

	    if( ISUNSIGNED(p->in.type) ) {
		/* avoid sign extension problems by saving the */
		/* old value and doing the inc/dec separately. */

		NODE *p3;

		p3 = tcopy(p);		/* copy of p to be rewritten */
					/* as LHS += 1 or LHS -= 1   */
		if(p3->in.op == INCR)
			p3->in.op = ASG PLUS;
		else
			p3->in.op = ASG MINUS;


		order(p1, INAREG);	/* save old value.  p1 is LHS of p */
		tfree(p2);		/* free RHS of p */
		*p = *p1;		/* structure assignment */
		tfree(p1);

		if(p3->in.op != REG && busy[R0] && busy[R1] 
		    && busy[R2] ) {
			order(p, INTEMP);	/* free up a register */
		}

		order(p3, FOREFF);	/* do the increment or decrement */
		goto again;
	    }

	    /* Not unsigned, so x++ becomes (x += 1) -1; */

	    p1 = tcopy(p);
	    reclaim(p->in.left, RNULL, 0);
	    p->in.left = p1;
	    p1->in.op = (p->in.op == INCR) ? ASG PLUS : ASG MINUS;
	    p->in.op = (p->in.op == INCR) ? MINUS : PLUS;
	    goto again;

	case STASG: 
	    if (setstr(p, cook))
		goto again;
	    goto nomat;

	case ASG PLUS: 		/* and other assignment ops */
	    if (setasop(p, cook))
		goto again;

    /* there are assumed to be no side effects in LHS */

	    p2 = tcopy(p);
	    p->in.op = ASSIGN;
	    reclaim(p->in.right, RNULL, 0);
	    p->in.right = p2;
    /* 
     * DJK: botch to take care of [reg] op= treg
     */
	    if (dope[o] & MULFLG || p->in.type == FLOAT ||
		 p->in.type == DOUBLE || p->in.type == LONG) {
		if (p->in.left->in.op == OREG) {
		    if (istreg(p->in.left->tn.rval) &&
			    (p2->in.right->in.op == REG ||
				p2->in.right->in.op == OREG)) {
			order(p2->in.right, INTEMP);
		    }
		}
	    }
	    canon(p);
	    rallo(p, p->in.rall);

#ifndef BUG4
	    if (odebug)
		fwalk(p, eprint, 0);
#endif

	    /* order(p2->in.left, INTBREG | INTAREG);  old */
	    p2->in.op = NOASG p2->in.op;

	    order(p2, INTBREG | INTAREG);
	    goto again;

	case ASSIGN: 
	    if (setasg(p, cook)) {
#ifndef BUG4
    if (odebug) {
	printf("setasg call( %x, ", p);
	print("cookie", cookie);
	printf(" ):  after setasg call, doing again\n");
	prbusy();
	fwalk(p, eprint, 0);
    }
#endif
	    if (p->in.right->in.op == REG && 
		(p->in.left->in.op != OREG &&
		 p->in.left->in.op != UNARY MUL) &&
		(p->in.left->in.su >= 3) &&
		(busy[R0] && busy[R1]) ) 
			order(p->in.right, INTEMP);

	    if (p->in.right->in.op == UNARY MUL &&
		p->in.left->in.op == UNARY MUL &&
		p->in.left->in.left->in.op == REG &&
		p->in.right->in.su >= 3 &&
		(busy[R0] || busy[R1]) )
			order(p->in.left->in.left, INAREG);
		goto again;
	    } else {
#ifndef BUG4
    if (odebug) {
	printf("setasg call( %x, ", p);
	print("cookie", cookie);
	printf(" ):  after setasg call, going to nomat\n");
	prbusy();
	fwalk(p, eprint, 0);
    }
#endif
	    goto nomat;
	    }


	case BITYPE: 
#ifndef BUG4
    if (odebug) {
	printf("at BITYPE before oreg2 call ( %x, ", p);
	print("cookie", cookie);
	printf(" ):  before oreg2 call\n");
	prbusy();
	fwalk(p, eprint, 0);
    }
#endif
	    if (setbin(p, cook)) {
#ifndef BUG4
    if (odebug) {
	printf("setbin call( %x, ", p);
	print("cookie", cookie);
	printf(" ):  after setbin call, doing again\n");
	prbusy();
	fwalk(p, eprint, 0);
    }
#endif
		goto again;
	    }
#ifndef BUG4
    if (odebug) {
	printf("setbin call( %x, ", p);
	print("cookie", cookie);
	printf(" ):  after setbin call, doing binop replace\n");
	prbusy();
	fwalk(p, eprint, 0);
    }
#endif
    /* try to replace binary ops by =ops */
	    switch (o) {

		case PLUS: 
		case MINUS: 
		case AND: 
		case OR: 
		case ER: 
		case LS: 
		case RS: 
		case SRA:
		case SLA:
		case MOD:
		case MUL:
		case DIV:
		    p->in.op = ASG o;
		    goto again;
	    }
	    goto nomat;

    }

cleanup: 

 /* if it is not yet in the right state, put it there */

#ifndef BUG4
    if (odebug) {
	printf("order5( %x, ", p);
	print("cookie", cookie);
	printf(" ):  cleanup: my_nrecur = %d\n", my_nrecur);
	prbusy();
	fwalk(p, eprint, 0);
    }
#endif

    if (cook & FOREFF) {
	reclaim(p, RNULL, 0);
	goto out;
    }

    if (p->in.op == FREE)
	goto out;

    if (cook & SANY || tshape(p, cook))
	goto out;
    if (cook & SOREG && tshape(p, SNAME | SCON)) {
	goto out;
    }

    if ((m = match(p, cook)) == MDONE)
	goto out;

 /* we are in bad shape, try one last chance */
    if (lastchance(p, cook))
	goto again;

    goto nomat;

  out:	/* final return point */
	nrecur = my_nrecur - 1;
	return;
}

int         callflag;
int         fregs;

void store(p) register NODE *p;
{

 /* find a subtree of p which should be stored */

    register    int o, ty;

    o = p->in.op;
    ty = optype(o);

    if (ty == LTYPE)
	return;

    switch (o) {

	case UNARY CALL: 
	case UNARY FORTCALL: 
	case UNARY STCALL: 
	    ++callflag;
	    break;

	case UNARY MUL: 
	    if (asgop(p->in.left->in.op))
		stoasg(p->in.left, UNARY MUL);
	    break;

	case CALL: 
	case FORTCALL: 
	case STCALL: 
#ifndef NESTCALLS		/* DJK */
	    stoarg(p->in.left, o, 0);
#else
	    store(p->in.left);
#endif

	    stoarg(p->in.right, o, 1);
	    ++callflag;
	    return;

	case COMOP: 
	    markcall(p->in.right);
	    if (p->in.right->in.su > fregs)
		SETSTO(p, INTEMP);
	    store(p->in.left);
	    return;

	case ANDAND: 
	case OROR: 
	case QUEST: 
	    markcall(p->in.right);
	    if (p->in.right->in.su > fregs)
		SETSTO(p, INTEMP);
	case CBRANCH: 	/* to prevent complicated expressions on the LHS 
			 * from being stored */
	case NOT: 
	    constore(p->in.left);
	    return;

    }

    if (ty == UTYPE) {
	store(p->in.left);
	return;
    }

    if (asgop(p->in.right->in.op))
	stoasg(p->in.right, o);

    if (p->in.su > fregs) {	/* must store */
	mkadrs(p);		/* set up stotree and stocook to subtree
				 * that must be stored */
    }
    /* this is to make unsigned UGT and ULT work */
    if (logop(p->in.op) && p->in.right->in.type == LONG &&
      p->in.right->in.op == SCONV) {
	SETSTO(p->in.right, INTEMP);
	return;
    }

    store(p->in.right);
    store(p->in.left);
}

void constore(p) register NODE  *p;
{
 /* 
  * store conditional expressions. The point is,
  * avoid storing expressions in conditional conditional context,
  * since the evaluation order is predetermined
  */

    switch (p->in.op) {

	case ANDAND: 
	case OROR: 
	case QUEST: 
	    markcall(p->in.right);
	case NOT: 
	    constore(p->in.left);
	    return;

    }

    store(p);
}

void markcall(p) register NODE  *p;
{			/* mark off calls below the current node */

again: 
    switch (p->in.op) {

	case UNARY CALL: 
	case UNARY STCALL: 
	case UNARY FORTCALL: 
	case CALL: 
	case STCALL: 
	case FORTCALL: 
	    ++callflag;
	    return;

    }

    switch (optype(p->in.op)) {

	case BITYPE: 
	    markcall(p->in.right);
	case UTYPE: 
	    p = p->in.left;
    /* eliminate recursion (aren't I clever...) */
	    goto again;
	case LTYPE: 
	    return;
    }

}

void stoarg(p, calltype, firstarg) register NODE    *p;
int calltype, firstarg;
{
 /* arrange to store the args */

    if (p->in.op == CM) {
	stoarg(p->in.left, calltype, p->in.left->in.op != CM);
	firstarg = 0;
	p = p->in.right;
    }
    if (calltype == CALL) {
	STOARG(p);
    }
    else
	if (calltype == STCALL) {
	    STOSTARG(p);
	}
	else {
	    STOFARG(p);
	}
    callflag = 0;
    store(p);
#ifndef NESTCALLS
	/* prevent two calls from being active at once  */
    if (callflag && p->in.op == STARG) {
	int lo = p->in.left->in.op;
	if(lo == STCALL || lo == CALL) {
		SETSTO(p, INTEMP);
		store(p);	/* do again to preserve bottom-up nature */
		return;
	}
    }
    if (callflag && !firstarg) {
	SETSTO(p, INTEMP);
	store(p);	/* do again to preserve bottom up nature....  */
    }
#endif
}

int         negrel[] =
{
    NE, EQ, GT, GE, LT, LE, UGT, UGE, ULT, ULE
};		/* negatives of relationals */

void cbranch(p, true, false) NODE   *p;
int true, false;
{
 /* 
  * evaluate p for truth value, and branch to true or false 
  * accordingly: label <0 means fall through
  */
    register    int o, lab, flab, tlab;

    lab = -1;

    switch (o = p->in.op) {

	case ULE: 
	case ULT: 
	case UGE: 
	case UGT: 
	case EQ: 
	case NE: 
	case LE: 
	case LT: 
	case GE: 
	case GT: 
	    if (true < 0) {
		o = p->in.op = negrel[o - EQ];
		true = false;
		false = -1;
#ifndef BUG1
	if (odebug) {
	printf ("in cbranch after reverse\n");
	fwalk(p, eprint, 0);
	}
#endif
	    }
	    if (p->in.right->in.op == ICON
		    && p->in.right->tn.lval == 0
		    && p->in.right->in.name[0] == '\0') {
		if (ISUNSIGNED(p->in.left->in.type)) {
		    if (o == LT) {
			o = ULT;
		    }
		    if (o == GE) {
			o = UGE;
		    }
		}
		switch (o) {

		    case UGT: 
		    case ULE: 
			o = p->in.op = (o == UGT) ? NE : EQ;
		    case EQ: 
		    case NE: 
		    case LE: 
		    case LT: 
		    case GE: 
		    case GT: 
#ifndef BUG1
	if (odebug) {
	printf ("in cbranch after switch\n");
	fwalk(p, eprint, 0);
	}
#endif
			if (logop(p->in.left->in.op)) {
		    /* 
		     * strange situation: e.g., (a!=0) == 0
		     * must prevent reference to p->in.left->label,
		     * so get 0/1. we could optimize, but why bother
		     */
			    codgen(p->in.left, INAREG | INBREG);
			}

    			/* the test here is to see if we are comparing
    			 * a char to zero and if so, getting this value
    			 * into a register for the comparison.  Because
    			 * chars can never be less than zero, we should
    			 * optimize this code away.  JCB 03/11/94
    			 */
			/* do this code always for chars and others */
    			codgen(p->in.left,
    			    (o == EQ || o == NE) ? FORZCC | FORCC : FORCC);
			cbgen(o, true, 'I');
			break;

		    case UGE: 
			werror("unsigned < 0 never true");
			codgen(p->in.left, FORCC);
			cbgen(0, true, 'I');	/* unconditional branch */
			break;
		    case ULT: 
			werror("unsigned >= 0 always true");
			codgen(p->in.left, FORCC);
		}
	    }
	    else {
		p->bn.label = true;
		codgen(p, (o == EQ || o == NE) ? FORZCC | FORCC : FORCC);
	    }
	    if (false >= 0)
		cbgen(0, false, 'I');
	    reclaim(p, RNULL, 0);
	    return;

	case ANDAND: 
	    lab = false < 0 ? get2lab() : false;
	    cbranch(p->in.left, -1, lab);
	    cbranch(p->in.right, true, false);
	    if (false < 0)
		deflab(lab);
	    p->in.op = FREE;
	    return;

	case OROR: 
	    lab = true < 0 ? get2lab() : true;
	    cbranch(p->in.left, lab, -1);
	    cbranch(p->in.right, true, false);
	    if (true < 0)
		deflab(lab);
	    p->in.op = FREE;
	    return;

	case NOT: 
	    cbranch(p->in.left, false, true);
	    p->in.op = FREE;
	    break;

	case COMOP: 
	    codgen(p->in.left, FOREFF);
	    p->in.op = FREE;
	    cbranch(p->in.right, true, false);
	    return;

	case QUEST: 
	    flab = false < 0 ? get2lab() : false;
	    tlab = true < 0 ? get2lab() : true;
	    cbranch(p->in.left, -1, lab = get2lab());
	    cbranch(p->in.right->in.left, tlab, flab);
	    deflab(lab);
	    cbranch(p->in.right->in.right, true, false);
	    if (true < 0)
		deflab(tlab);
	    if (false < 0)
		deflab(flab);
	    p->in.right->in.op = FREE;
	    p->in.op = FREE;
	    return;

	case ICON: 
	    if (p->in.type != FLOAT && p->in.type != DOUBLE &&
		p->in.type != LONG) {

		if (p->tn.lval || p->in.name[0]) {
	    /* addresses of C objects are never 0 */
		    if (true >= 0)
			cbgen(0, true, 'I');
		}
		else
		    if (false >= 0)
			cbgen(0, false, 'I');
		p->in.op = FREE;
		return;
	    }
	    /* fall through to default with other strange constants */

	default: 
	    /* get condition codes */
	    if (p->in.type == STRTY || p->in.type == UNIONTY) {
		uerror("structures do not have condition codes");
		return;
	    }
	    codgen(p, FORZCC | FORCC);
	    if (true >= 0)
		cbgen(NE, true, 'I');
	    if (false >= 0)
		cbgen(true >= 0 ? 0 : EQ, false, 'I');
	    reclaim(p, RNULL, 0);
	    return;

    }

}

void rcount()
{			/* count recursions */
    if (++nrecur > NRECUR) {
	cerror("expression causes compiler loop: try simplifying");
    }
}

#ifndef BUG4
void eprint(p, down, a, b) NODE *p;
int        *a, *b, down;
{
    char *s;
    int  szrnames = 19; /* nbr entries in rnames[] per local2.c */

    *a = *b = down + 1;
    while (down >= 2) {
	printf("\t");
	down -= 2;
    }
    if (down--)
	printf("    ");


    s = opst[p->in.op];
    if( !s )
	s = "???";
    printf("%x) %s", p, s);

    switch (p->in.op) {		/* special cases */

	case REG: 
	    if(p->tn.rval < szrnames)
	    	printf(" %s", rnames[p->tn.rval]);
	    else
		printf(" rval: 0x%x", p->tn.rval);
	    printf(", lval: 0x%x", p->tn.lval);
	    break;

	case OREG: 
	    if(p->tn.rval < szrnames)
	    	printf(" %s =>", rnames[p->tn.rval]);
	    else
		printf(" rval: 0x%x => ", p->tn.rval);
	    adrput(p);
	    printf(", lval: 0x%x", p->tn.lval);
	    break;

	case ICON: 
	case NAME: 
	    printf(" ");
	    adrput(p);
	    break;

	case LADDR:
	    printf(" lval: 0x%x, rval: 0x%x\n", p->tn.lval, p->tn.rval);
	    break;

	case STCALL: 
	case UNARY STCALL: 
	case STARG: 
	case STASG: 
	case CM:
	    printf(" size=%d", p->stn.stsize);
	    printf(" align=%d", p->stn.stalign);
	    break;
    }

    printf(", ");
    tprint(p->in.type);
    printf(", ");
    print("rall", p->in.rall);
    printf(", SU= %d\n", p->in.su);

}
#endif

#ifndef NOMAIN
NODE * eread(){

	/* call eread recursively to get subtrees, if any */

	register NODE *p;
	register int i, c;
	register char *pc;
	register int j;

	i = rdin( 10 );

	p = talloc();
	p->in.rall = NOPREF;  /* register allocation information */
	p->in.op = i;
	p->in.type = rdin( 8 );

	i = optype(i);

	if(p->in.op == FCON ) {
		fltread(p);	/* read fp numbers in machdep part */
		return(p);	/* oh my - take notice here */
	} else {
		if( i == LTYPE ) p->tn.lval = rdin( 10 );
		if( i != BITYPE ) p->tn.rval = rdin( 10 );
	}

	if( p->in.op == STASG || p->in.op == STARG || 
		p->in.op == STCALL || p->in.op == UNARY STCALL ){
		p->stn.stsize = (rdin( 10 ) + (SZCHAR-1) )/SZCHAR;
		p->stn.stalign = rdin(10) / SZCHAR;
		if( getchar() != '\n' ) cerror( "illegal \n" );
		}
	else {   /* usual case */
		/* Rev G change - rbusy of REG nodes moved to treeinit(). */
		{ char buf[BUFSIZ];
		for( pc=buf,j=0; ( c = getchar() ) != '\n'; ++j ){
			if( j < BUFSIZ ) *pc++ = c;
			}
		if( j < BUFSIZ ) *pc = '\0';
		p->in.name = tstr(buf);
		}
	}

	/* now, recursively read descendents, if any */

	if( i != LTYPE ) p->in.left = eread();
	if( i == BITYPE ) p->in.right = eread();

	return( p );

}

CONSZ rdin(base)
int base;
{
	register int sign, c;
	CONSZ val;

	sign = 1;
	val = 0;

	while( (c=getchar()) > 0 ) {
		if( c == '-' ){
			if( val != 0 ) cerror( "illegal -");
			sign = -sign;
			continue;
			}
		if( c == '\t' || c == ' ') break;
		if( c>='0' && c<='9' ) {
			val *= base;
			if( sign > 0 )
				val += c-'0';
			else
				val -= c-'0';
			continue;
			}
		if(( c>='a' && c<='f') && base == 16 ) {
			val *= base;
			if( sign > 0 )
				val += c-'a'+10;
			else
				val -= c-'a'+10;
			continue;
			}
		cderror( "illegal character `%c' on intermediate file", c );
		break;
		}

	if( c <= 0 ) {
		cerror( "unexpected EOF");
		}
	return( val );
	}
# endif

#ifndef FIELDOPS
 /* do this if there is no special hardware support for fields */

void ffld(p, down, down1, down2) NODE   *p;
int  down, *down1, *down2;
{
 /* look for fields that are not in an lvalue context, and rewrite them... */
    register NODE  *shp;
    register    int s, o, v, ty;

    *down1 = asgop(p->in.op);
    *down2 = 0;

    if (!down && p->in.op == FLD) {		/* rewrite the node */

	if (!rewfld(p))
	    return;

	ty = p->in.type;
	if (UNSIGNABLE(ty)) {
	    ty = ENUNSIGN(ty);
	}
	v = p->tn.rval;
	s = UPKFSZ(v);
#ifdef RTOLBYTES
	o = UPKFOFF(v);			/* amount to shift */
#else
	o = SZINT - s - UPKFOFF(v);
 /* amount to shift */
#endif
	if (s == SZINT) {
	    NODE       *r = p->in.left;
	    ncopy(p, r);
	    r->in.op = FREE;
	    p->in.type = UNSIGNED;
	    return;
	}
	if (ty == SHORT || ty == USHORT) {
	    if (o >= SZSHORT) {
		o -= SZINT - SZSHORT;
	    }
	    else {
		moveaddr(p->in.left, 2);
	    }
	}
	if (ty == CHAR || ty == UCHAR) {
	    if (o >= (SZINT - SZCHAR)) {
		o -= SZINT - SZCHAR;
	    }
	    else {
		moveaddr(p->in.left, 3 - (o / SZCHAR));
		o %= SZCHAR;
	    }
	}

	/* make & mask part */

	p->in.left->in.type = ty == USHORT ? SHORT : ty;

	p->in.op = AND;
	p->in.right = talloc();
	p->in.right->in.op = ICON;
	p->in.right->in.rall = NOPREF;
	p->in.right->in.type = ty;
	p->in.right->tn.lval = 1;
	p->in.right->tn.rval = 0;
	p->in.right->in.name = "";
	p->in.right->tn.lval = (unsigned)p->in.right->tn.lval << (unsigned)s;
	p->in.right->tn.lval--;

	/* now, if a shift is needed, do it */

	if (o != 0) {
	    shp = talloc();
	    shp->in.op = RS;
	    shp->in.rall = NOPREF;
	    shp->in.type = ty;
	    shp->in.left = p->in.left;
	    shp->in.right = talloc();
	    shp->in.right->in.op = ICON;
	    shp->in.right->in.rall = NOPREF;
	    shp->in.right->in.type = ty;
	    shp->in.right->tn.rval = 0;
	    shp->in.right->tn.lval = o;		/* amount to shift */
	    shp->in.right->in.name = "";
	    p->in.left = shp;
	    /* whew! */
	}
    }
}
#endif

#ifndef BUG1
void oreg2db(p)	/* special oreg2(), for debugging */
register NODE *p;
{
	printf("oreg2db(%x): before oreg2\n", p);
	fwalk(p, eprint, 0);
	oreg2(p);
	printf("oreg2db(%x): after oreg2\n", p);
	fwalk(p, eprint, 0);
}
#endif


void oreg2(p) register NODE *p;
{

    /* look for situations where we can turn * into OREG */

    NODE       *q;
    register    int i;
    register    int r;
    register char  *cp;
    register NODE  *ql, *qr;
    CONSZ       temp;

#ifdef R2REGS
    if(p->in.op == PLUS && ISPTR(p->in.type) ){
	    ql = p->in.left;
	    qr = p->in.right;

	    if ((r = base(ql)) >= 0 && (i = offset(qr, tlen(p))) >= 0) {
		stuffuand(p);
		makeor2(p->in.left, ql, r, i);
		return;
	    }
	    else
		if ((r = base(qr)) >= 0 && (i = offset(ql, tlen(p))) >= 0) {
		    stuffuand(p);
		    makeor2(p->in.left, qr, r, i);
		    return;
		}
    }
#endif /* R2REGS */

    if (p->in.op == UNARY MUL) {
	q = p->in.left;

	if (q->in.op == REG) {
#ifndef BUG1
        if (odebug) {
	    printf("oreg2(): got UNARY MUL with left REG\n");
	    fwalk ( p, eprint, 0);
	}
#endif
	    temp = q->tn.lval;
	    r = q->tn.rval;
	    cp = q->in.name;
	    goto ormake;
	}

#ifndef BUG1
        if (odebug) {
	    printf("oreg2(): looking for PLUS or MINUS\n");
	    fwalk ( p, eprint, 0);
	}
#endif
	if (q->in.op != PLUS && q->in.op != MINUS)
	    return;
	ql = q->in.left;
	qr = q->in.right;

#ifndef BUG1
        if (odebug) {
	    printf("oreg2(): before R2REGS\n");
	    fwalk ( p, eprint, 0);
	}
#endif

#ifdef R2REGS

 /* look for doubly indexed expressions */

	if (q->in.op == PLUS) {
	    if ((r = base(ql)) >= 0 && (i = offset(qr, tlen(p))) >= 0) {
		makeor2(p, ql, r, i);
		return;
	    }
	    else
		if ((r = base(qr)) >= 0 && (i = offset(ql, tlen(p))) >= 0) {
		    makeor2(p, qr, r, i);
		    return;
		}
	}

	if(q->in.op == PLUS) {
		ql = q->in.left;
		qr = q->in.right;
		if(ql->in.op == REG && qr->in.op == HCON) {
		    p->in.op = OREG;
		    p->tn.rval = ql->tn.rval;
		    p->tn.lval = qr->tn.lval;
		    p->in.name = qr->in.name;
		    tfree(q);
		    return;
		}
		if(qr->in.op == REG && ql->in.op == HCON) {
		    p->in.op = OREG;
		    p->tn.rval = qr->tn.rval;
		    p->tn.lval = ql->tn.lval;
		    p->in.name = ql->in.name;
		    tfree(q);
		    return;
		}
	}

#endif

#ifndef BUG1
        if (odebug) {
	    printf("oreg2(): after R2REGS\n");
	    fwalk ( p, eprint, 0);
	}
#endif

	if (q->in.op == PLUS && ql->in.op == ICON) {
	    NODE       *t;
	    t = ql, ql = qr, qr = t;
	}
	if (qr->in.op == ICON
		&& qr->in.name[0] == '\0'
		&& ql->in.op == REG
		&& szty(qr->in.type) == 1) {
	    temp = qr->tn.lval;
	    if (q->in.op == MINUS)
		temp = -temp;
	    r = ql->tn.rval;
	    temp += ql->tn.lval;
	    cp = qr->in.name;
	    if(cp)
	   	 if (*cp && (q->in.op == MINUS || *ql->in.name))
			return;
	    if(!cp)
		cp = ql->in.name;
	    else
	    	if (!*cp)
			cp = ql->in.name;

#ifndef BUG1
        if (odebug) {
	    printf("oreg2(): before ormake\n");
	    fwalk ( p, eprint, 0);
	}
#endif
    ormake: 
	    if (notoff(p->in.type, r, temp, cp))
		return;
	    p->in.op = OREG;
	    p->tn.rval = r;
	    p->tn.lval = temp;
	    p->in.name = cp;
#ifndef BUG1
        if (odebug) {
	    printf("oreg2(): after ormake\n");
	    fwalk ( p, eprint, 0);
	}
#endif
	    tfree(q);
	    return;
	}
    }

	/*  patch PLUS code was here. */

}

void stuffuand(p)
NODE *p;
{
	/* Convert tree at p into U& U* original tree */
	/* Dont disturb descendants of p */

	register NODE	*p1, *p2;

	p1 = talloc();
	p2 = talloc();

	*p2 = *p;	/* copy original root */

	p1->in.op = UNARY MUL;
	p1->in.type = INCREF(p->in.type);
	p1->in.name = "";
	p1->in.left = p2;
	p1->in.right = 0;

	p->in.op = UNARY AND;
	p->in.name = "";
	p->in.left = p1;
	p->in.right = 0;

#ifndef BUG1
	if(odebug) {
		printf("stuffuand(): returning:\n");
		fwalk(p, eprint, 0);
	}
#endif
}

int isregvar(r)
register int r;
{
	if(r >= R4 && r <= R7)
		return(1);
	return(0);
}

void canon(p) NODE  *p;
{
 /* put p in canonical form */
    void oreg2(), sucomp();
    void oreg2db();

#ifndef FIELDOPS
    void ffld();
#ifndef BUG1
    if (odebug) {
        printf("canon(): before fwalk ffld\n");
        fwalk(p, eprint, 0);
    }
#endif
    fwalk(p, ffld, 0);		/* look for field operators */

#ifndef BUG1
    if (odebug) {
        printf("canon(): after fwalk ffld\n");
        fwalk(p, eprint, 0);
    }
#endif
#endif

#ifndef BUG1
    if(odebug)
	walkf(p, oreg2db);
    else
#endif
	walkf(p, oreg2);	/* look for and create OREG nodes */

#ifndef BUG1
    if (odebug) {
        printf("canon(): after fwalk oreg2\n");
        fwalk(p, eprint, 0);
    }
#endif
#ifdef MYCANON
    MYCANON(p);		/* your own canonicalization routine(s) */
#endif
    walkf(p, sucomp);	/* do the Sethi-Ullman computation */
#ifndef BUG1
    if (odebug) {
        printf("canon(): after fwalk sucomp\n");
        fwalk(p, eprint, 0);
    }
#endif
}

NODE       *mkcon(v)
int v;
{
    register NODE  *t = talloc();
    t->in.op = ICON;
    t->tn.lval = v;
    t->tn.rval = 0;
    t->in.name = "";
    t->in.type = INT;
    return(t);
}

void moveaddr(p, amt) register NODE *p; int amt;
{
    register    int o = p->in.op;
    if (o == NAME || o == OREG) {
	p->tn.lval += amt;
	return;
    }
    if (o == UNARY MUL) {
	register NODE  *t, *l = p->in.left;
	if (l->in.op == PLUS && l->in.right->in.op == ICON) {
	    l->in.right->tn.lval += amt;
	    return;
	}
	t = talloc();
	ncopy(t, l);
	l->in.left = t;
	l->in.op = PLUS;
	l->in.right = mkcon(amt);
	return;
    }
    cerror("Can't move address\n");
}

#ifndef BUG1
void treeprint(p)	/* for debugging with dbx */
NODE *p;
{
	fwalk(p, eprint, 0);
}
#endif

/* 2nd pass print routines */
#include "print.h"

