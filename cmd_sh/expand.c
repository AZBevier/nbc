/*~!expand.c*/
/* Name:  expand.c Part No.: _______-____r
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

#ident	"$Id: expand.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#include	"defs.h"
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<dirent.h>
#ifndef mpx
#include <stdlib.h>
#include <unistd.h>
#endif

void makearg();
static int addg();
int gmatch();

#define	entry		e->d_name

/*
 * globals (file name generation)
 *
 * "*" in params matches r.e ".*"
 * "?" in params matches r.e. "."
 * "[...]" in params matches character class
 * "[...a-z...]" in params matches a through z.
 *
 */

int expand(as, rcnt)
char *as;
int rcnt;
{
    int one = 1;
    int count;
    DIR	 * dirf;
    BOOL	dir = 0;
    char *rescan = 0;
    register char *s, *cs;
    struct argnod *schain = gchain;
    struct stat statb;
    BOOL	slash;

#ifdef NOTNOW
printf("expand: entry: as(%s) rcnt(%d)\n", *as ? as : pdstr, rcnt);
#endif
    if (trapnote & SIGSET)
    	return(0);
    s = cs = as;

    /*
     * check for meta chars
     */
     {
    	register BOOL open;

    	slash = 0;
    	open = 0;
    	do
    	 {
    	    switch (*cs++) {
    	    case 0:
    	    	if (rcnt && slash)
    	    	    break;
    	    	else
    	    	    return(0);

    	    case '/':
    	    	slash++;
    	    	open = 0;
    	    	continue;

    	    case '[':
    	    	open++;
    	    	continue;

    	    case ']':
    	    	if (open == 0)
    	    	    continue;

    	    case '?':
    	    case '*':
    	    	if (rcnt > slash)
    	    	    continue;
    	    	else
    	    	    cs--;
    	    	break;


    	    default:
    	    	continue;
    	    }
    	    break;
/*  	} while (TRUE);*/
    	} while (one);
    }

    for (; ; ) {
    	if (cs == s) {
    	    s = nullstr;
    	    break;
    	} else if (*--cs == '/') {
    	    *cs = 0;
    	    if (s == cs)
    	    	s = slstr;
    	    break;
    	}
    }

#ifdef NOTNOW
printf("expand: opening dir %s\n", *s ? s : pdstr);
#endif
    if (dirf = opendir(*s ? s : pdstr)) {
#ifdef NOTNOW
printf("expand: we opened dir %s\n", *s ? s : pdstr);
#endif
#ifdef mpx
    	if (fstat(dirf->dd_fd, &statb) != -1 && 
    	  (statb.st_mode & S_IFMT) == S_IFDIR)
#else
        /* this is only to make cc happy, we do not run this ls on Linux */
    	if (fstat(dirfd(dirf), &statb) != -1 && 
    	  (statb.st_mode & S_IFMT) == S_IFDIR)
#endif
    	    dir++; 
    	else
    	    closedir(dirf); 
    }

#ifdef NOTNOW
printf("expand: after opening (%s), dir = %x\n", *s ? s : pdstr, dir);
#endif
    count = 0; 
    if (*cs == 0)
    	*cs++ = 0200; 
    if (dir) {		/* check for rescan */
    	register char *rs; 
    	struct dirent *e; 

    	rs = cs; 
    	do {
    	    if (*rs == '/') {
    		rescan = rs; 
    		*rs = 0; 
    		gchain = 0; 
    	    }
    	} while (*rs++); 

    	while ((e = readdir(dirf)) && (trapnote & SIGSET) == 0) {
#ifdef NOTNOW
printf("expand: found %s in dir %s\n", entry, *s ? s : pdstr);
#endif
    	    if (entry[0] == '.' && *cs != '.')
    		continue; 

    	    if (gmatch(entry, cs)) {
    		addg(s, entry, rescan); 
    		count++; 
    	    }
    	}
    	closedir(dirf); 

    	if (rescan) {
    	    register struct argnod *rchain; 

    	    rchain = gchain; 
    	    gchain = schain; 
    	    if (count) {
    		count = 0; 
    		while (rchain) {
    		    count += expand(rchain->argval, slash + 1); 
    		    rchain = rchain->argnxt; 
    		}
    	    }
    	    *rescan = '/'; 
    	}
    } 
    {
#ifdef mpx
    	char c; 
#else
    	register char c; 
#endif

    	s = as; 
    	while (c = *s)
    	    *s++ = (c & STRIP ? c : '/'); 
    }
    return(count); 
} 


int gmatch(s, p)
register char *s, *p; 
{
    register int scc; 
#ifdef mpx
    char c; 
#else
    register char c; 
#endif

    if (scc = *s++) {
    	if ((scc &= STRIP) == 0)
    	    scc = 0200; 
    }
    switch (c = *p++) {
    	case '[':
    	    {
    		BOOL ok; 
    		int lc; 
    		int notflag = 0; 

    		ok = 0; 
    		lc = 077777; 
    		if (*p == '!') {
    		    notflag = 1; 
    		    p++; 
    		}
    		while (c = *p++) {
    		    if (c == ']')
    			return(ok ? gmatch(s, p) : 0); 
    		    else if (c == MINUS) {
    			if (notflag) {
    			    if (scc < lc || scc > *(p++))
    				ok++; 
    			    else
    				return(0); 
    			} else {
    			    if (lc <= scc && scc <= (*p++))
    				ok++; 
    			}
    		    } else {
    			lc = c & STRIP; 
    			if (notflag) {
    			    if (scc && scc != lc)
    				ok++; 
    			    else
    				return(0); 
    			} else {
    			    if (scc == lc)
    				ok++; 
    			}
    		    }
    		}
    		return(0); 
    	    } 
    	default:
    	    if ((c & STRIP) != scc)
    		return(0); 

    	case '?':
    	    return(scc ? gmatch(s, p) : 0); 

    	case '*':
    	    while (*p == '*')
    		p++; 

    	    if (*p == 0)
    		return(1); 
    	    --s; 
    	    while (*s) {
    		if (gmatch(s++, p))
    		    return(1); 
    	    } return(0); 

    	case 0:
    	    return(scc == 0); 
    }
} 


static int addg(as1, as2, as3)
char *as1, *as2, *as3; 
{
    register char *s1, *s2; 
    register int c; 

    s2 = locstak() + BYTESPERWORD; 
    s1 = as1; 
    while (c = *s1++) {
    	if ((c &= STRIP) == 0) {
    	    *s2++ = '/'; 
    	    break; 
    	}
    	*s2++ = c; 
    }
    s1 = as2; 
    while (*s2 = *s1++)
    	s2++; 
    if (s1 = as3) {
    	*s2++ = '/'; 
    	while (*s2++ = *++s1); 
    }
    makearg(endstak(s2)); 
} 


void makearg(args)
register struct argnod *args; 
{
    args->argnxt = gchain; 
    gchain = args; 
} 
