/*~!errusage.c*/
/* Name:  errusage.c Part No.: _______-____r
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

#ident	"@(#)nbclib:errusage.c	1.1"

#include  "errmsg.h"
#include  <stdio.h>
#include  <varargs.h>

#define   USAGENO  255	/* exit value for usage messages */

/* This routine prints the standard command usage message.
*/

void
errusage(va_alist)
va_dcl
{
    va_list	ap;
    char	*format;

    va_start (ap);
    format = va_arg (ap, char *);
    va_end (ap);

    fputs ("Usage:  ", stderr);
    if(Err.vsource  &&  Err.source) {
      fputs (Err.source, stderr);
      fputc (' ', stderr);
    }
    vfprintf (stderr, format, ap);
    fputc ('\n', stderr);

    errexit (USAGENO);
    erraction (EEXIT);
}
