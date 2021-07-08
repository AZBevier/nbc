/*~!sum.c*/
/* Name:  sum.c Part No.: _______-____r
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

#ident	"Make4MPX $Id: sum.c,v 1.2 2021/07/05 20:47:50 jbev Exp $"

/*
 * $Log: sum.c,v $
 * Revision 1.2  2021/07/05 20:47:50  jbev
 * Fix warnings.
 *
 * Revision 1.1  1995/03/14 03:13:37  jbev
 * Initial revision
 *
 */

#include <stdio.h>
#ifndef mpx
#include <stdlib.h>
#include <unistd.h>
#endif

/*
 * Sum bytes in file mod 2^16
 */

#define WDMSK 0177777L
#define BUFSIZE 512
#include <stdio.h>
struct part {
    short unsigned hi, lo;
};

union hilo { /* this only works right in case short is 1/2 of long */
    struct part hl;
    long lg;
} tempa, suma;

int main(argc, argv)
int argc;
char **argv;
{
    register unsigned sum;
    register int i, c;
    register FILE *f;
    register long nbytes;
    int alg, ca, errflg = 0;
    unsigned lsavhi, lsavlo;

    alg = 0;
    i = 1;
    if ((argc > 1) && (argv[1][0] == '-' && argv[1][1] == 'r')) {
    	alg = 1;
    	i = 2;
    }

    do {
    	if (i < argc) {
    	    if ((f = fopen(argv[i], "r")) == NULL) {
    	    	(void) fprintf(stderr, "sum: Can't open %s\n", argv[i]);
    	    	errflg += 10;
    	    	continue;
    	    }
    	} else
    	    f = stdin;
    	sum = 0;
    	suma.lg = 0;
    	nbytes = 0;
    	if (alg == 1) {
    	    while ((c = getc(f)) != EOF) {
    	    	nbytes++;
    	    	if (sum & 01)
    	    	    sum = (sum >> 1) + 0x8000;
    	    	else
    	    	    sum >>= 1;
    	    	sum += c;
    	    	sum &= 0xFFFF;
    	    }
    	} else {
    	    while ((ca = getc(f)) != EOF) {
    	    	nbytes++;
    	    	suma.lg += ca & WDMSK;
    	    }
    	}
    	if (ferror(f)) {
    	    errflg++;
    	    (void) fprintf(stderr, "sum: read error on %s\n", argc > 1 ? argv[i]
    	      : "-");
    	}
    	if (alg == 1)
    	    (void) printf("%.5u%6ld", sum, (nbytes + BUFSIZE - 1) / BUFSIZE);
    	else {
    	    tempa.lg = (suma.hl.lo & WDMSK) + (suma.hl.hi & WDMSK);
    	    lsavhi = (unsigned) tempa.hl.hi;
    	    lsavlo = (unsigned) tempa.hl.lo;
    	    (void) printf("%u %ld", (unsigned)(lsavhi + lsavlo), (nbytes + BUFSIZE
    	      -1) / BUFSIZE);
    	}
    	if (argc > 1)
    	    (void) printf(" %s", argv[i] == (char *)0 ? "" : argv[i]);
    	(void) printf("\n");
    	(void) fclose(f);
    } while (++i < argc);
    exit(errflg);
}


