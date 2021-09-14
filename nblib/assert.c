/*~!assert.c*/
/* Name:  assert.c Part No.: _______-____r
 *
 * Copyright 1991 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:assert.c	1.1"

/*
 *	called from "assert" macro; prints without printf or stdio.
 */

#define WRITE(s, n)	(void) write(2, (s), (n))
#define WRITESTR(s1, n, s2)	WRITE((s1), n), \
				WRITE((s2), (unsigned) strlen(s2))

static char linestr[] = ", line NNNNN\n";

_assert(assertion, filename, line_num)
char *assertion;
char *filename;
int line_num;
{
	register char *p = &linestr[7];
	register int div, digit;

	WRITESTR("Assertion failed: ", 18, assertion);
	WRITESTR(", file ", 7, filename);
	for (div = 10000; div != 0; line_num %= div, div /= 10)
		if ((digit = line_num/div) != 0 || p != &linestr[7] || div == 1)
			*p++ = digit + '0';
	*p++ = '\n';
	*p = '\0';
	WRITE(linestr, (unsigned) strlen(linestr));
	(void) abort();
}
