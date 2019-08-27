/*~!string.h*/
/* Name:  string.h Part No.: _______-____r
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

#ifndef STRING_H
#define STRING_H

#ident	"@(#)nbinclude:string.h	1.0"

extern char
	*index(),
	*memccpy(),
	*memchr(),
	*memcpy(),
	*memset(),
	*rindex(),
	*str2up(),
	*stradd(),
	*strcat(),
	*strccpy(),
	*strchr(),
	*strcpy(),
	*strdup(),
	*strecnt(),
	*strecpy(),
	*strncat(),
	*strncpy(),
	*strpbrk(),
	*strrchr(),
	*strrpbrk(),
	*strtok();

extern int
	bcmp();
	strcmp(),
	strcspn(),
	stricmp(),
	strlen(),
	strncmp(),
	strnicmp(),
	strnlen(),
	strpos(),
	strrpos(),
	strspn(),
	memcmp();

extern long
	strtol();

extern double
	atof(),
	strtod();

extern void
	unix2mpx(),
	bcopy(),
	bzero();
#endif
