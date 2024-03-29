/*~!args.c*/
/* Name:  args.c Part No.: _______-____r
 *
 * Copyright 1994 - J B Systems, Morrison, CO
 *
 * The recipient of this product specifically agrees not to distribute,
 * disclose, or disseminate in any way, to any one, nor use for its own
 * benefit, or the benefit of others, any information contained  herein
 * without the expressed written consent of J B Systems.
 *
 *                     RESTRICTED RIGHTS LEGEND
 *
 * Use, duplication, or disclosure by the Government is  subject  to
 * restriction  as  set forth in paragraph (b) (3) (B) of the Rights
 * in Technical Data and Computer Software  Clause  in  DAR  7-104.9
 * (a).
 */

#ident	"$Id: args.c,v 1.4 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

/* #define NOTNOW */

#include	"defs.h"
#ifndef mpx
#include <stdlib.h>
#endif

extern int poptemp();
extern int pop();
extern int any();
extern int cf();

extern void failed();

static struct dolnod *copyargs();
static void freedolh();
extern struct dolnod *freeargs();
static struct dolnod *dolh;

char flagadr[14];

char flagchar[] = 
{
    'x','n','v','t',STDFLG,'i','e','r','k','u','h','f','a',0
};


long flagval[]  = 
{
    execpr, noexec, readpr, oneflg, stdflg, intflg, errflg, rshflg, 	
    keyflg, setflg, hashflg, nofngflg, exportflg, 0
};


/* ========	option handling	======== */


int options(argc, argv)
char **argv;
int argc;
{
    register char *cp;
    register char **argp = argv;
    register char *flagc;
    char *flagp;

    if (argc > 1 && *argp[1] == '-') {
    	/*
	 * if first argument is "--" then options are not
	 * to be changed. Fix for problems getting 
	 * $1 starting with a "-"
	 */

    	cp = argp[1];
    	if (cp[1] == '-') {
    	    argp[1] = argp[0];
    	    argc--;
    	    return(argc);
    	}
    	if (cp[1] == '\0')
    	    flags &= ~(execpr | readpr);

    	/*
	 * Step along 'flagchar[]' looking for matches.
	 * 'sicr' are not legal with 'set' command.
	 */

#ifdef smpx
    	str2lc(cp);		/* make lower case */
#endif
    	while (*++cp) {
    	    flagc = flagchar;
    	    while (*flagc && *flagc != *cp)
    	    	flagc++;
    	    if (*cp == *flagc) {
    	    	if (eq(argv[0], setstr) && any(*cp, sicrstr))
    	    	    failed(argv[1], badopt);
    	    	else
    	    	 {
    	    	    flags |= flagval[flagc-flagchar];
    	    	    if (flags & errflg)
    	    	    	eflag = errflg;
    	    	}
    	    } else if (*cp == 'c' && argc > 2 && comdiv == 0) {
    	    	comdiv = argp[2];
    	    	argp[1] = argp[0];
    	    	argp++;
    	    	argc--;
    	    } else
    	    	failed(argv[1], badopt);
    	}
    	argp[1] = argp[0];
    	argc--;
    } else if (argc > 1 && *argp[1] == '+') {
	/* unset flags x, k, t, n, v, e, u */
    	cp = argp[1];
#ifdef smpx
    	str2lc(cp);		/* make lower case */
#endif
    	while (*++cp) {
    	    flagc = flagchar;
    	    while (*flagc && *flagc != *cp)
    	    	flagc++;
    	    /*
    	     * step through flags
    	     */
    	    if (!any(*cp, sicrstr) && *cp == *flagc) {
    	    	/*
		 * only turn off if already on
		 */
    	    	if ((flags & flagval[flagc-flagchar])) {
    		    flags &= ~(flagval[flagc-flagchar]);
    	    	    if (*cp == 'e')
    	    	    	eflag = 0;
    	    	}
    	    }
    	}
    	argp[1] = argp[0];
    	argc--;
    }
    /*
     * set up $-
     */
    flagp = flagadr;
    if (flags) {
    	flagc = flagchar;
    	while (*flagc) {
    	    if (flags & flagval[flagc-flagchar])
    	    	*flagp++ = *flagc;
    	    flagc++;
    	}
    }
    *flagp = 0;
    return(argc);
}


/*
 * sets up positional parameters
 */
void setargs(argi)
char *argi[];
{
    register char **argp = argi;	/* count args */
    register int argn = 0;
#ifdef NOTNOW
printf("setargs entry\n");
#endif

    while (Rcheat(*argp++) != ENDARGS)
    	argn++;
    /*
     * free old ones unless on for loop chain
     */
    freedolh();
    dolh = copyargs(argi, argn);
    dolc = argn - 1;
#ifdef NOTNOW
printf("setargs exit\n");
#endif
}


static void freedolh()
{
    register char **argp;
    register struct dolnod *argblk;

    if (argblk = dolh) {
    	if ((--argblk->doluse) == 0) {
    	    for (argp = argblk->dolarg; Rcheat(*argp) != ENDARGS; argp++)
    	    	free(*argp);
    	    free(argblk);
    	}
    }
}


struct dolnod *freeargs(blk)
struct dolnod *blk;
{
    register char **argp;
    register struct dolnod *argr = 0;
    register struct dolnod *argblk;
    int cnt;

    if (argblk = blk) {
    	argr = argblk->dolnxt;
    	cnt  = --argblk->doluse;

    	if (argblk == dolh) {
    	    if (cnt == 1)
    	    	return(argr);
    	    else
    	    	return(argblk);
    	} else
    	 {
    	    if (cnt == 0) {
    	    	for (argp = argblk->dolarg; Rcheat(*argp) != ENDARGS; argp++)
    	    	    free(*argp);
    	    	free(argblk);
    	    }
    	}
    }
    return(argr);
}


static struct dolnod *copyargs(from, n)
char *from[];
int n;
{
    register struct dolnod *np = 
      (struct dolnod *)alloc(sizeof(char**) *n + 3 *BYTESPERWORD);
    register char **fp = from;
    register char **pp;

    np->doluse = 1;	/* use count */
    pp = np->dolarg;
    dolv = pp;

    while (n--)
    	*pp++ = make(*fp++);
    *pp++ = ENDARGS;
    return(np);
}


struct dolnod *clean_args(blk)
struct dolnod *blk;
{
    register char **argp;
    register struct dolnod *argr = 0;
    register struct dolnod *argblk;

    if (argblk = blk) {
    	argr = argblk->dolnxt;

    	if (argblk == dolh)
    	    argblk->doluse = 1;
    	else
    	 {
    	    for (argp = argblk->dolarg; Rcheat(*argp) != ENDARGS; argp++)
    	    	free(*argp);
    	    free(argblk);
    	}
    }
    return(argr);
}


void clearup()
{
    /*
     * force `for' $* lists to go away
     */
    while (argfor = clean_args(argfor))
    	;
    /*
     * clean up io files
     */
    while (pop())
    	;

    /*
     * clean up tmp files
     */
    while (poptemp())
    	;
}


struct dolnod *useargs()
{
    if (dolh) {
    	if (dolh->doluse++ == 1) {
    	    dolh->dolnxt = argfor;
    	    argfor = dolh;
    	}
    }
    return(dolh);
}

