/*~!print.h*/
/* Name:  print.h Part No.: _______-____r
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

#ident	"@(#)nbclib:print.h	1.1"

#ifndef PRINT_H
#define PRINT_H

/* Maximum number of digits in any integer representation */
#define MAXDIGS 11

/* Maximum total number of digits in E format */
#define MAXECVT 17

/* Maximum number of digits after decimal point in F format */
#define MAXFCVT 60

/* Maximum significant figures in a floating-point number */
#define MAXFSIG MAXECVT

/* Maximum number of characters in an exponent */
#define MAXESIZ 4

/* Maximum (positive) exponent */
#define MAXEXP 40

/* Data type for flags */
typedef char bool;

/* Convert a digit character to the corresponding number */
#define tonumber(x) ((x)-'0')

/* Convert a number between 0 and 9 to the corresponding digit */
#define todigit(x) ((x)+'0')

/* Max and Min macros */
#define max(a,b) ((a) > (b)? (a): (b))
#define min(a,b) ((a) < (b)? (a): (b))
#endif /* PRINTF_H */
