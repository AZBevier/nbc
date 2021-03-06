/*~!regerror.c*/
/* Name:  regerror.c Part No.: _______-____r
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

#ident	"@(#)nbclib:regerror.c	1.1"

/*
	return the a message explaining a regexp(5) error code
*/

#include "libgen.h"

char *
regerror(code)
int	code;
{
	switch( code ) {
	case 11:
		return "Range endpoint too large.";
	case 16:
		return "Bad number.";
	case 25:
		return "'\\digit' out of range.";
	case 36:
		return "Illegal or missing delimiter.";
	case 41:
		return "No remembered search string.";
	case 42:
		return "'\\( \\)' imbalance.";
	case 43:
		return "Too many '\\('.";
	case 44:
		return "More than 2 numbers given in \\{ \\}.";
	case 45:
		return "} expected after \\.";
	case 46:
		return "First number exceeds second in \\{ \\}.";
	case 49:
		return "[] imbalance.";
	case 50:
		return "Regular expression too long or too complex.";
	}
	return "Unknown code!";
}
