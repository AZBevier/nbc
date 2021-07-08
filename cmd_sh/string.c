/*~!string.c*/
/* Name:  string.c Part No.: _______-____r
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

#ident	"$Id: string.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#include	"defs.h"
#ifdef mpx
#include <ctype.h>
#endif

/* ========	general purpose string handling ======== */

char *movstr(a, b)
register char *a, *b;
{
    while (*b++ = *a++)
    	;
    return(--b);
}


int any(c, s)
char c;
char *s;
{
    char d;

    while (d = *s++) {
    	if (d == c)
    	    return(TRUE);
    }
    return(FALSE);
}


int cf(s1, s2)
register char *s1, *s2;
{
#ifdef mpx
    while ((islower(*s1) ? *s1++ : tolower(*s1++)) ==
     (islower(*s2) ? *s2 : tolower(*s2)))
#else
    while (*s1++ == *s2)
#endif
    	if (*s2++ == 0)
    	    return(0);
    return(*--s1 - *s2);
}


int length(as)
char *as;
{
    register char *s;

    if (s = as)
    	while (*s++)
    	    ;
    return(s - as);
}


char *movstrn(a, b, n)
register char *a, *b;
register int n;
{
    while ((n-- > 0) && *a)
    	*b++ = *a++;

    return(b);
}

