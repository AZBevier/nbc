/*~!tmpnam.c*/
/* Name:  tmpnam.c Part No.: _______-____r
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

#ident	"@(#)nbclib:tmpnam.c	1.1"

#include <stdio.h>

extern char *mktemp(), *strcpy(), *strcat();
static char str[L_tmpnam], seed[] = { 'a', 'a', 'a', '\0' };

static char Xs[] = "XXXXXX";

char *
tmpnam(s)
char	*s;
{
    register char *p, *q;

    p = (s == NULL)? str: s;
    (void) strcpy(p, P_tmpdir);
    (void) strcat(p, seed);
    (void) strcat(p, Xs);

    q = seed;
    while(*q == 'z')
      *q++ = 'a';
    if (*q != '\0')
      ++*q;

    (void) mktemp(p);
    return(p);
}
