/*~!memccpy.c*/
/* Name:  memccpy.c Part No.: _______-____r
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

#ident	"@(#)nbclib:memccpy.c	1.1"

/*
 * Copy s2 to s1, stopping if character c is copied.
 * Copy no more than n bytes.
 * Return a pointer to the byte after character c in the copy,
 * or NULL if c is not found in the first n bytes.
 */

char *
memccpy(s1, s2, c, n)
register char *s1, *s2;
register int c, n;
{
    while (--n >= 0)
      if ((*s1++ = *s2++) == c)
        return (s1);
    return (0);
}
