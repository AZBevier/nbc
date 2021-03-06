/*~!bsearch.c*/
/* Name:  bsearch.c Part No.: _______-____r
 *
 * Copyright 1992 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:bsearch.c	1.1"

/*
 * Binary search algorithm, generalized from Knuth (6.2.1) Algorithm B.
 *
 */

typedef char *POINTER;

POINTER
bsearch(key, base, nel, width, compar)
POINTER	key;			/* Key to be located */
POINTER	base;			/* Beginning of table */
unsigned nel;			/* Number of elements in the table */
unsigned width;			/* Width of an element (bytes) */
int	(*compar)();		/* Comparison function */
{
	int two_width = width + width;
	POINTER last = base + width * (nel - 1); /* Last element in table */

	while (last >= base) {

		register POINTER p = base + width * ((last - base)/two_width);
		register int res = (*compar)(key, p);

		if (res == 0)
			return (p);	/* Key found */
		if (res < 0)
			last = p - width;
		else
			base = p + width;
	}
	return ((POINTER) 0);		/* Key not found */
}
