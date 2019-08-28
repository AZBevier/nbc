/*~!memchr.c*/
/* Name:  memchr.c Part No.: _______-____r
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

#ident	"@(#)nbclib:memchr.c	1.1"

/*
 * Return the ptr in sp at which the character c appears;
 *   NULL if not found in n chars; don't stop at \0.
 */

char *
memchr(sp, c, n)
register char *sp, c;
register int n;
{
    while (--n >= 0)
      if (*sp++ == c)
        return (--sp);
    return (0);
}
