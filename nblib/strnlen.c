/*~!strnlen.c*/
/* Name:  strnlen.c Part No.: _______-____r
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

#ident	"@(#)nbclib:strnlen.c	1.1"

/*
 * Returns the number of
 * non-NULL bytes in string argument
 * but no more than n.
 */

#include	"libgen.h"

int
strnlen(s, n)
char	*s;
int	n;
{
	register char	*sp = s;
	register char	*send = sp + n;

	for( ;  sp < send  &&  *sp != '\0';  sp++ )
		;
	return (sp - s);
}
