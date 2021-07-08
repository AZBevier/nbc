/*~!word.c*/
/* Name:  word.c Part No.: _______-____r
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

#ident	"$Id: word.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#include	"defs.h"
#include	"sym.h"
#ifndef mpx
#include <unistd.h>
#endif

#ifdef NOTNOW
#define printf(c)
#endif

extern void chkpr();
extern void chktrap();
extern void clearup();
extern void copy();
extern void exitsh();
extern void prc();

extern int syslook();
extern int estabf();

static int readb();
char readc();
char nextc();

/* ========	character handling for command lines	========*/

int word()
{
#ifdef mpx
    char c, d;
#else
    register char c, d;
#endif
    struct argnod *arg = (struct argnod *)locstak();
    register char *argp = arg->argval;
    int alpha = 1;
#ifdef TILDE_SUB
    char *save;
#endif
#ifdef NOTNOW
printf("word: entry\n");
#endif

    wdnum = 0;
    wdset = 0;

    while (1) {
#ifdef NOTNOW
printf("word: before while, nextc, space\n");
#endif
    	while (c = nextc(0), space(c))		/* skipc() */
    	    ;
#ifdef NOTNOW
printf("word: after while, nextc, space\n");
#endif

    	if (c == COMCHAR) {
    	    while ((c = readc()) != NL && c != WEOF)
    	    	;
#ifdef NOTNOW
printf("word: after while readc\n");
#endif
    	    peekc = c;
    	} else
    	 {
    	    break;	/* out of comment - white space loop */
    	}
    }
#ifdef NOTNOW
printf("word: after while(1)\n");
#endif
#ifdef TILDE_SUB
    save = argp;	/* save start of word */
#endif
    if (!eofmeta(c)) {
    	do
    	 {
    	    if (c == LITERAL) {
    	    	*argp++ = (DQUOTE);
    	    	while ((c = readc()) && c != LITERAL) {
    	    	    *argp++ = (c | QUOTE);
    	    	    if (c == NL)
    	    	    	chkpr();
    	    	}
    	    	*argp++ = (DQUOTE);
    	    } else
    	     {
    	    	*argp++ = (c);
    	    	if (c == '=')
    	    	    wdset |= alpha;
    	    	if (!alphanum(c))
    	    	    alpha = 0;
    	    	if (qotchar(c)) {
    	    	    d = c;
    	    	    while ((*argp++ = (c = nextc(d))) && c != d) {
    	    	    	if (c == NL)
    	    	    	    chkpr();
    	    	    }
    	    	}
#ifdef TILDE_SUB
    	    	/*
		 * check for ~login_name
		 */
    	    	else if ( c == SQUIGGLE && validtilde( save, argp ) ) {
    	    	    char *home, *name;

    	    	    name = argp;
    	    	    while ( (c = nextc( 0 )) != '/'
    	    	       && !eofmeta( c )
    	    	      )
    	    	    	*name++ = c;
    	    	    peekc = c;
    	    	    *name = '\0';
    	    	    home = homedir( argp );
    	    	    if ( *home )
    	    	    	movstr( home, --argp );
    	    	    argp += length( argp ) - 1;
    	    	}
#endif

    	    }
    	} while ((c = nextc(0), !eofmeta(c)));
#ifdef NOTNOW
printf("word: before endstak call argp = %x\n", argp);
#endif
    	argp = endstak(argp);
#ifdef NOTNOW
printf("word: after endstak call argp = %x\n", argp);
#endif
    	if (!letter(arg->argval[0]))
    	    wdset = 0;

    	peekn = c | MARK;
#ifdef NOTNOW
printf("word: after peekn1 MARK peekn = %x, c = %x\n", peekn, c);
#endif
    	if (arg->argval[1] == 0 && 
    	  (d = arg->argval[0], digit(d)) && 
    	  (c == '>' || c == '<')) {
    	    word();
    	    wdnum = d - '0';
    	} else { /* check for reserved words */
    	    if (reserv == FALSE ||
    	      (wdval = syslook(arg->argval, reserved, no_reserved)) == 0) {
    	    	wdarg = arg;
    	    	wdval = 0;
    	    }
    	}
    } else if (dipchar(c)) {
    	if ((d = nextc(0)) == c) {
    	    wdval = c | SYMREP;
    	    if (c == '<') {
    	    	if ((d = nextc(0)) == '-')
    	    	    wdnum |= IOSTRIP;
    	    	else {
    	    	    peekn = d | MARK;
#ifdef NOTNOW
printf("word: after peekn2 MARK peekn = %x, c = %x d = %x\n", peekn, c, d);
#endif
    		}
    	    }
    	} else
    	 {
    	    peekn = d | MARK;
#ifdef NOTNOW
printf("word: after peekn3 MARK peekn = %x, c = %x d = %x\n", peekn, c, d);
#endif
    	    wdval = c;
    	}
    } else {
    	if ((wdval = c) == WEOF)
    	    wdval = EOFSYM;
    	if (iopend && eolchar(c)) {
    	    copy(iopend);
    	    iopend = 0;
    	}
    }
    reserv = FALSE;
#ifdef NOTNOW
printf("word: returns wdval = %x\n", wdval);
#endif
    return(wdval);
}


char skipc()
{
#ifdef mpx
    char c;
#else
    register char c;
#endif

    while (c = nextc(0), space(c))
    	;
    return(c);
}


char nextc(quote)
char quote;
{
#ifdef mpx
    char c, d;
#else
    register char c, d;
#endif

#ifdef NOTNOW
printf("nextc: entry quote = %x\n", quote);
#endif
retry:
    if ((d = readc()) == ESCAPE) {
#ifdef NOTNOW
printf("nextc: ESCAPE d = %x\n", d);
#endif
    	if ((c = readc()) == NL) {
    	    chkpr();
    	    goto retry;
    	} else if (quote && c != quote && !escchar(c)) {
    	    peekc = c | MARK;
#ifdef NOTNOW
printf("nextc: MARK peekc = %x, c = %x\n", peekc, c);
#endif
    	} else {
    	    d = c | QUOTE;
#ifdef NOTNOW
printf("nextc: QUOTE d = %x, c = %x\n", d, c);
#endif
    	}
    }
#ifdef NOTNOW
printf("nextc: exit d = %x\n", d);
#endif
    return(d);
}


char readc()
{
    register char c;
    register int len;
    register struct fileblk *f;

#ifdef NOTNOW
printf("readc: entry, peekc = %x, peekn = %x\n", peekc, peekn);
#endif
    if (peekn) {
    	peekc = peekn;
    	peekn = 0;
    }
    if (peekc) {
    	c = peekc;
    	peekc = 0;
#ifdef NOTNOW
printf("readc: return, c = %x\n",c);
#endif
#ifdef mpx
    	return(c&0xff);
#else
    	return(c);
#endif
    }
    f = standin;
#ifdef NOTNOW
printf("readc: standin = %x\n", f->fdes);
#endif
retry:
    if (f->fnxt != f->fend) {
    	if ((c = *f->fnxt++) == 0) {
    	    if (f->feval) {
    	    	if (estabf(*f->feval++))
    	    	    c = WEOF;
    	    	else
    	    	    c = SP;
    	    } else
    	    	goto retry;	/* = c = readc(); */
    	}
    	if (flags & readpr && standin->fstak == 0)
    	    prc(c);
    	else
    	    if ((flags & prompt) && standin->fstak == 0)
    		if (c == NL)
    		    newline();
    	if (c == NL)
    	    f->flin++;
    } else if (f->xfeof || f->fdes < 0) {
    	c = WEOF;
    	f->xfeof++;
    } else if ((len = readb()) <= 0) {
    	    close(f->fdes);
    	    f->fdes = -1;
    	    c = WEOF;
    	    f->xfeof++;
    } else
     {
    	f->fend = (f->fnxt = f->fbuf) + len;
    	goto retry;
    }
#ifdef NOTNOW
printf("readc: exit c = %x\n", c);
#endif
    return(c);
}


static int readb()
{
    register struct fileblk *f = standin;
    register int len;

    do
     {
    	if (trapnote & SIGSET) {
    	    newline();
    	    sigchk();
    	} else if ((trapnote & TRAPSET) && (rwait > 0)) {
    	    newline();
    	    chktrap();
    	    clearup();
    	}
    } while ((len = read(f->fdes, f->fbuf, f->fsiz)) < 0 && trapnote);
    return(len);
}
