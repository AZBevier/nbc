/*~!echo.c*/
/* Name:  echo.c Part No.: _______-____r
 *
 * Copyright 1995 - J B Systems, Morrison, CO
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

#ident	"Makef4MPX $Id: echo.c,v 1.2 2021/07/04 02:51:56 jbev Exp $"

/*
 * $Log: echo.c,v $
 * Revision 1.2  2021/07/04 02:51:56  jbev
 * Correct warnings.
 *
 * Revision 1.1  1995/03/14 01:50:57  jbev
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#ifndef mpx
#include <stddef.h>
#endif

int main(argc, argv)
int argc;
char **argv;
{
    char *cp;
    int i, j, cv;

    if (--argc == 0) {
    	putchar('\n');
    	exit(0);
    }
    for (i = 1; i <= argc; i++) {
    	for (cp = argv[i]; *cp; cp++) {
    	    if (*cp == '\\')
    	    	switch (*++cp) {
    	    	case 'B':
    	    	case 'b':
    	    	    putchar('\b');
    	    	    continue;

    	    	case 'C':
    	    	case 'c':
    	    	    exit(0);

    	    	case 'F':
    	    	case 'f':
    	    	    putchar('\f');
    	    	    continue;

    	    	case 'N':
    	    	case 'n':
    	    	    putchar('\n');
    	    	    continue;

    	    	case 'R':
    	    	case 'r':
    	    	    putchar('\r');
    	    	    continue;

    	    	case 'T':
    	    	case 't':
    	    	    putchar('\t');
    	    	    continue;

    	    	case 'V':
    	    	case 'v':
    	    	    putchar('\v');
    	    	    continue;

    	    	case '\\':
    	    	    putchar('\\');
    	    	    continue;

    	    	case '0':
    	    	    j = cv = 0;
    	    	    while ((*++cp >= '0' && *cp <= '7') && j++ < 3) {
    	    	    	cv <<= 3;
    	    	    	cv |= (*cp - '0');
    	    	    }
    	    	    putchar(cv);
    	    	    --cp;
    	    	    continue;

    	    	default:
    	    	    cp--;
    	    	}
    	    putchar(*cp);
    	}
    	putchar(i == argc ? '\n' : ' ');
    }
    exit(0);
}

