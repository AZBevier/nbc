/*~!scanf.c*/
/* Name:  scanf.c Part No.: _______-____r
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

#ident	"@(#)nbclib:scanf.c	1.1"

#include <stdio.h>
#include <varargs.h>

extern int _doscan();

/*VARARGS1*/
int
scanf(fmt, va_alist)
char *fmt;
va_dcl
{
	va_list ap;

	va_start(ap);
	return(_doscan(stdin, fmt, ap));
}

/*VARARGS2*/
int
fscanf(iop, fmt, va_alist)
FILE *iop;
char *fmt;
va_dcl
{
	va_list ap;

	va_start(ap);
	return(_doscan(iop, fmt, ap));
}

/*VARARGS2*/
int
sscanf(str, fmt, va_alist)
register char *str;
char *fmt;
va_dcl
{
	va_list ap;
	FILE strbuf;

	va_start(ap);
	strbuf._flag = _IOREAD;
	strbuf._ptr = strbuf._base = (unsigned char*)str;
	strbuf._cnt = strlen(str);
	strbuf._file = _NFILE;
	return(_doscan(&strbuf, fmt, ap));
}
