/*~!memcmp.c*/
/* Name:  memcmp.c Part No.: _______-____r
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

#ident	"@(#)nbclib:memcmp.c	1.1"

/*
 * Compare n bytes:  s1>s2: >0  s1==s2: 0  s1<s2: <0
 */

int
memcmp(s1, s2, n)
register char *s1, *s2;
register int n;
{
    int diff;

    if (s1 != s2)
      while (--n >= 0)
    	if (diff = *s1++ - *s2++)
    	  return (diff);
    return (0);
}
