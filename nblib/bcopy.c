
/*~!bcopy.c*/
/* Name:  bcopy.c Part No.: _______-____r
 *
 * Copyright 1990 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:ncopy.c	1.0"

/*
 * copy string b1 to string b2, with overlap testing
 */
void
bcopy (b1, b2, length)
     register char *b1;
     register char *b2;
     register int length;
{
/* handle buffer overlap case */
  if (b1 < b2) /* possible overlap */
    for (b1 += length, b2 += length; length--; ) *--b2 = *--b1;
  else
    for (;length--;) *b2++ = *b1++;
}
