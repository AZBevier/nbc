/*~!strpos.c*/
/* Name:  strpos.c Part No.: _______-____r
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

#ident	"@(#)nbclib:strpos.c	1.0"

/*
 * Return the offset position in sp at which the character c appears;
 * -1   if not found
 */

/* strpos function */
int
strpos(sp, c)
register char *sp, c;
{
register int i = 0;

	do {
		if (*sp == c) return(i);
			i++;
	} while (*sp++);
	return(-1);
}
