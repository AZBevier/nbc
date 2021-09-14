/*~!sbrk.c*/
/* Name:  sbrk.c Part No.: _______-____r
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

#ident	"@(#)nbclib:sbrk.c	1.0"

extern char *eas;
extern int  brk();

char *
sbrk(incr)                         /* allocate incr more storage */
int incr;

{
    int neweas, oldeas;

    oldeas = (int)eas;       /* save eas to be returned */
    if (incr != 0) {
        neweas = (int)eas + incr;     /* shift pointer incr amount */
        if (brk(neweas) == -1)return((char *)(-1));
    }
    return((char *)oldeas);                 /* return old pointer */
}
