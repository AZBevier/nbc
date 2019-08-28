/*~!str2up.c*/
/* Name:  str2up.c Part No.: _______-____r
 *
 * Copyright 1994 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:str2up.c	1.1

/* convert string to upper case */
/* The provided string is converted "in place" to upper case */
/* This is an extension of Sys V libc for MPX integration */

#include <ctype.h>

char *str2up(s)
char *s;
{
	register char *orig_s = s;

	s--;
	while (*++s != '\000')
		if(islower(*s))*s = toupper(*s);
	return(orig_s);
}

#ifndef FIX_040494
/* convert string to lower case */
/* The provided string is converted "in place" to lower case */
/* This is an extension of Sys V libc for MPX integration */

char *str2lc(s)
char *s;
{
	register char *orig_s = s;

	s--;
	while (*++s != '\000')
		if(isupper(*s))*s = tolower(*s);
	return(orig_s);
}
#endif
