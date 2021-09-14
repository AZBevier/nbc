/*~!floor.c*/
/* Name:  floor.c Part No.: _______-____r
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

#ident	"@(#)nbclib:floor.c	1.1"

/*
 *	floor(x) returns the largest integer (as a double-precision number)
 *	not greater than x.
 *	ceil(x) returns the smallest integer not less than x.
 */

extern double modf();

double
floor(x)
double x;
{
    double y;	/* can't be in register because of modf() below */

    return (modf(x, &y) < 0 ? y - 1.0 : y);
}

double
ceil(x)
double x;
{
    double y;	/* can't be in register because of modf() below */

    return (modf(x, &y) > 0 ? y + 1.0 : y);
}
