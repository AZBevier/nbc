/*~!strncat.c*/
/* Name:  strncat.c Part No.: _______-____r
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

#ident	"@(#)nbclib:strncat.c	1.1"

/*
 * Concatenate s2 on the end of s1.  S1's space must be large enough.
 * At most n characters are moved.
 * Return s1.
 */

#ifdef unix
#include <sys/types.h>
#else
#include <types.h>
#endif

char *
strncat(s1, s2, n)
register char *s1, *s2;
register size_t n;
{
	register char *os1;

	n++;
	os1 = s1;
	while(*s1++)
		;
	--s1;
	while(*s1++ = *s2++)
		if(--n == 0) {
			*--s1 = '\0';
			break;
		}
	return(os1);
}
