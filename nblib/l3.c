/*~!l3.c.c*/
/* Name:  l3.c.c Part No.: _______-____r
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

#ident	"@(#)nbclib:l3.c	1.1"

/*
 * Convert longs to and from 3-byte disk addresses
 */

void
ltol3(cp, lp, n)
char	*cp;
long	*lp;
int	n;
{
    register i;
    register char *a, *b;

    a = cp;
    b = (char *)lp;
    for (i=0; i < n; i++) {
      b++;
      *a++ = *b++;
      *a++ = *b++;
      *a++ = *b++;
    }
}

void
l3tol(lp, cp, n)
long	*lp;
char	*cp;
int	n;
{
    register i;
    register char *a, *b;

    a = (char *)lp;
    b = cp;
    for (i=0; i < n; i++) {
      *a++ = 0;
      *a++ = *b++;
      *a++ = *b++;
      *a++ = *b++;
    }
}
