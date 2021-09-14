/*~!strrpbrk.c*/
/* Name:  strrpbrk.c Part No.: _______-____r
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

#ident	"@(#)nbclib/strrpbrk.c	1.0"

/*
 * Return ptr to last occurance of any character from `brkset'
 * in the character string `string'; NULL if none exists.
 */

#ifndef NULL
#define	NULL	(char *) 0
#endif

/* strrpbrk function */
char *
strrpbrk(string, brkset)
register char *string, *brkset;
{
	register char *p;
	register char *p1 = NULL;

	do {
		for(p=brkset; *p; ++p)
			if (*p == *string) p1 = string;
	}
	while(*string++);
	return(p1);
}
