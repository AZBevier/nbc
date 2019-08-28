
/*~!bcmp.c*/
/* Name:  bcmp.c Part No.: _______-____r
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

#ident	"@(#)nbclib:bcmp.c	1.0"

int
bcmp (b1, b2, length)	/* This could be a macro! */
     register char *b1;
     register char *b2;
     register int length;
 {
   while (length-- > 0)
     if (*b1++ != *b2++)
       return 1;

   return 0;
}

