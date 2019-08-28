/*~!pause*/
/* Name:  pause.c Part No.: _______-____r
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

#ident	"@(#)nbclib:pause.c	1.0"

#include <errno.h>

pause(tunits)  /* dummy entry, really does MPX anywait */
int tunits;	/* timer uits to wait */
{
	int reg[8];

/*	reg[6] = -60;		/* neg time val  */
	reg[6] = -tunits;		/* neg time val  */
	mpxsvc(0x107c,reg,reg);         /* call m.anywait service */
	errno = EINTR;
	return(-1);	/* good return */
}

