/*~!uniq.c*/
/* Name:  uniq.c Part No.: _______-____r
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

#ident	"Make4MPX $Id: uniq.c,v 1.3 2021/07/05 21:24:11 jbev Exp $"

/* $Log: uniq.c,v $
 * Revision 1.3  2021/07/05 21:24:11  jbev
 * Correct warning errors.
 *
 * Revision 1.2  1995/03/14 03:13:37  jbev
 * Initial file checkin.
 *
 */

/*
 * Deal with duplicated lines in a file
 */

#include <stdio.h>
#include <ctype.h>
#ifndef mpx
#include <stdlib.h>
#include <unistd.h>
#endif

int gline();
void pline();
int equal();
void printe();

int fields;
int letters;
int linec;
char mode;
int uniq;
char *skip();

int main(argc, argv)
int argc;
char *argv[];
{
    static char b1[1000], b2[1000];
    FILE * temp;

    while (argc > 1) {
    	if (*argv[1] == '-') {
    	    if (isdigit(argv[1][1]))
    	    	fields = atoi(&argv[1][1]);
    	    else
    	    	mode = argv[1][1];
    	    argc--;
    	    argv++;
    	    continue;
    	}
    	if (*argv[1] == '+') {
    	    letters = atoi(&argv[1][1]);
    	    argc--;
    	    argv++;
    	    continue;
    	}
    	if ( (temp = fopen(argv[1], "r")) == NULL)
    	    printe("cannot open %s\n", argv[1]);
    	else {
    	    fclose(temp);
    	    freopen(argv[1], "r", stdin);
    	}
    	break;
    }
    if (argc > 2 && freopen(argv[2], "w", stdout) == NULL)
    	printe("cannot create %s\n", argv[2]);

    if (gline(b1))
    	exit(0);
    for (; ; ) {
    	linec++;
    	if (gline(b2)) {
    	    pline(b1);
    	    exit(0);
    	}
    	if (!equal(b1, b2)) {
    	    pline(b1);
    	    linec = 0;
    	    do {
    	    	linec++;
    	    	if (gline(b1)) {
    	    	    pline(b2);
    	    	    exit(0);
    	    	}
    	    } while (equal(b1, b2));
    	    pline(b2);
    	    linec = 0;
    	}
    }
}


int gline(buf)
register char buf[];
{
    register int c;

    while ((c = getchar()) != '\n') {
    	if (c == EOF)
    	    return(1);
    	*buf++ = c;
    }
    *buf = 0;
    return(0);
}


void pline(buf)
register char buf[];
{

    switch (mode) {

    case 'u':
    	if (uniq) {
    	    uniq = 0;
    	    return;
    	}
    	break;

    case 'd':
    	if (uniq)
    	    break;
    	return;

    case 'c':
    	printf("%4d ", linec);
    }
    uniq = 0;
    fputs(buf, stdout);
    putchar('\n');
}


int equal(b1, b2)
register char b1[], b2[];
{
    register char c;

    b1 = skip(b1);
    b2 = skip(b2);
    while ((c = *b1++) != 0)
    	if (c != *b2++)
    	    return(0);
    if (*b2 != 0)
    	return(0);
    uniq++;
    return(1);
}


char *skip(s)
register char *s;
{
    register int nf, nl;

    nf = nl = 0;
    while (nf++ < fields) {
    	while (*s == ' ' || *s == '\t')
    	    s++;
    	while ( !(*s == ' ' || *s == '\t' || *s == 0) )
    	    s++;
    }
    while (nl++ < letters && *s != 0)
    	s++;
    return(s);
}


void printe(p, s)
char *p, *s;
{
    fprintf(stderr, p, s);
    exit(1);
}


