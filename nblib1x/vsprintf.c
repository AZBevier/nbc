/*~!vsprintf.c*/
/* Name:  vsprintf.c Part No.: _______-____r
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

#ident	"@(#)nbclib:vssprintf.c	1.1"

#include <stdio.h>
#include <varargs.h>
#include <values.h>

extern int _doprnt();

/*VARARGS2*/
int
vsprintf(string, format, ap)
char *string, *format;
va_list ap;
{
    register int count;
    FILE siop;

    siop._cnt = MAXINT;
    siop._base = siop._ptr = (unsigned char *)string;
    siop._flag = _IOWRT;
    siop._file = _NFILE;
    count = _doprnt(format, ap, &siop);
    *siop._ptr = '\0';		/* insert terminating null character */
    return(count);
}
