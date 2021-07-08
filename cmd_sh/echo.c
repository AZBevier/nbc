/*~!echo.c*/
/* Name:  echo.c Part No.: _______-____r
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

#ident	"$Id: echo.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#include	"defs.h"

extern void exitsh();
extern void prc_buff();
extern int exitval;
extern void flushb();

#define	exit(a)	flushb();return(a)

int echo(argc, argv)
int argc;
char **argv;
{
    register char *cp;
    register int i, wd;
    int j;

#ifdef NOTNOW
printf("echo: argc = %d argv = %s\n", argc, *argv);
#endif
    if (--argc == 0) {
    	prc_buff('\n');
    	exit(0);
    }

    for (i = 1; i <= argc; i++) {
    	sigchk();
    	for (cp = argv[i]; *cp; cp++) {
    	    if (*cp == '\\')
    	    	switch (*++cp) {
    	    	case 'b':
    	    	    prc_buff('\b');
    	    	    continue;

    	    	case 'c':
    	    	    exit(0);

    	    	case 'f':
    	    	    prc_buff('\f');
    	    	    continue;

    	    	case 'n':
    	    	    prc_buff('\n');
    	    	    continue;

    	    	case 'r':
    	    	    prc_buff('\r');
    	    	    continue;

    	    	case 't':
    	    	    prc_buff('\t');
    	    	    continue;

    	    	case 'v':
    	    	    prc_buff('\v');
    	    	    continue;

    	    	case '\\':
    	    	    prc_buff('\\');
    	    	    continue;
    	    	case '0':
    	    	    j = wd = 0;
    	    	    while ((*++cp >= '0' && *cp <= '7') && j++ < 3) {
    	    	    	wd <<= 3;
    	    	    	wd |= (*cp - '0');
    	    	    }
    	    	    prc_buff(wd);
    	    	    --cp;
    	    	    continue;

    	    	default:
    	    	    cp--;
    	    	}
    	    prc_buff(*cp);
    	}
    	if (i != argc)
    	    prc_buff(' ');
    }
    prc_buff('\n');
    exit(0);
}

