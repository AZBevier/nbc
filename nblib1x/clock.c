/*~!clock.c*/
/* Name:  clock.c Part No.: _______-____r
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

#ident	"@(#)nbclib:clock.c	1.1"

#include <sys/types.h>
#include <sys/times.h>
#include <sys/param.h>	/* for HZ (clock frequency in Hz) */

#define TIMES(B)	(B.tms_utime+B.tms_stime+B.tms_cutime+B.tms_cstime)

extern long times();
static long first = 0L;

long
clock()
{
	struct tms buffer;

	if (times(&buffer) != -1L && first == 0L)
		first = TIMES(buffer);
	return ((TIMES(buffer) - first) * (1000000L/HZ));
}
