/*~!getpid.c*/
/* Name:  getpid.c Part No.: _______-____r
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

#ident	"@(#)nbclib:getpid.c	1.1"

#include <tsa.h>
#define TSAP (*(struct tsa **)C_TSAD)

#ifdef MPX1X			/* MAC */
static int data[12];		/* MAC */
#endif				/* MAC */

getpid()    /* get program number*/
{
#ifndef MPX1X			/* MAC */
	int data[12];		/* MAC */
#endif				/* MAC */
	int reg[8], cc;

	reg[5] = 0x80000000 ;
	reg[7] = (int)(&data[0]);
	cc = mpxsvc(0x1064,reg,reg);
	return (data[0]);		/*return task number */
}

getpgrp()	/* get process group */
{
	return (0);	/* return root process group */
}

getppid()    /* get parent process id */
{
	return (TSAP->parent);	/* return parent task number */
}

