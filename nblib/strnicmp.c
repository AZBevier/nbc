/*~!strnicmp.c*/
/* Name:  strnicmp.c Part No.: _______-____r
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

#ident	"@(#)nbclib/strnicmp.c	1.0"

/*
 * Compare translated upercase strings (at most n bytes)
 *	returns: s1>s2; >0  s1==s2; 0  s1<s2; <0
 */

#ifdef unix
#include <sys/types.h>
#else
#include <types.h>
#endif
#include <ctype.h>

int
strnicmp (s1, s2, n)
register char *s1;
register char *s2;
register size_t n;
{
	n++;
	if(s1 == s2)
		return(0);
	while(--n > 0 && toupper(*s1) == toupper(*s2++))
		if(*s1++ == '\0')
			return(0);
	return((n == 0)? 0: (*s1 - *--s2));
}
