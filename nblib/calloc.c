/*~!calloc.c*/
/* Name:  callo.c Part No.: _______-____r
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

#ident	"@(#)nbclib:calloc.c	1.0"

/*	calloc - allocate and clear memory block */

extern char *malloc();
extern void free();

#define CHARPERINT (sizeof(int)/sizeof(char))
#define NULL 0

char *
calloc(num, size)
unsigned num, size;
{
	register char *mp;
	register int *q;
	register m;

	num *= size;
	mp = malloc(num);
	if(mp == NULL)
		return(NULL);
	q = (int *) mp;
	m = (num+CHARPERINT-1)/CHARPERINT;
	while(--m>=0)
		*q++ = 0;
	return(mp);
}

/*ARGSUSED*/
void
cfree(p, num, size)
char *p;
unsigned num, size;
{
	free(p);
}
