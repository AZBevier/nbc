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
 * Compare translated upercase strings
 *	returns: s1>s2; >0  s1==s2; 0  s1<s2; <0
 */

#include <ctype.h>

int
stricmp (s1, s2)
register char *s1, *s2;
{

	if(s1 == s2)
		return(0);
	while(toupper(*s1) == toupper(*s2++))
		if(*s1++ == '\0')
			return(0);
	return(*s1 - *--s2);
}
