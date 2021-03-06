/*~!memset.c*/
/* Name:  memset.c Part No.: _______-____r
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

#ident	"@(#)nbclib:memset.c	1.1"

/*
 * Set an array of n chars starting at sp to the character c.
 * Return sp.
 */
char *
memset(dst, c, n)
#ifndef MPX
register char *dst, c;
register int n;
#else
char *dst, c;
int n;
#endif
{
#ifndef MPX
    register char *old = dst;

    while (--n >= 0)
    	*dst++ = c;
    return (old);
#else
    /* Do fast memory set on MPX */
    asm(" lw r2,16w,sp");	/* get dest address */
    asm(" lw r1,17w,sp");	/* get the char */
    asm(" bz BZR");		/* skip ahead if a zero */
    asm(" trr r1,r0");		/* copy it */
    asm(" sll r1,8");		/* move it over */
    asm(" orr r0,r1");		/* now two copies */
    asm(" trr r1,r0");		/* copy it */
    asm(" sll r1,16");		/* move it over */
    asm(" orr r0,r1");		/* now four copies */
    asm("BZR lw r5,18w,sp");	/* get length */
    asm(" ble RET");		/* must be positive */
    /* see what out boundry is */
    asm(" tbr r2,31");		/* target byte bound? */
    asm(" bs DOB");		/* yes, move byte */
    asm("SDW tbr r2,30");	/* target hw bound? */
    asm(" bns DOW");		/* no, move as words's */
    asm(" sui r5,2");		/* at least 1 hw to set? */
    asm(" blt DOB");		/* no, move one byte */
    asm(" sth r1,0h,r2");	/* set a hw to allign */
    asm(" adi r2,1h");		/* bump the address */
    asm(" bu DOW");		/* set rest as words */
    /* move words till no wds left to move */
    asm("MWD stw r1,0w,r2");	/* put dst wd */
    asm(" adi r2,1w");		/* next wd addr */
    /* destination word bounded, move words */
    asm("DOW sui r5,1w");	/* reduce count to move */
/*    asm(" bgt MWD");		/* loop for all wd's */
    asm(" bge MWD");		/* loop for all wd's */
    asm(" adi r5,1w");		/* how many bytes left */
    asm(" bz RET");		/* none, return */
    asm("MBY stb r1,0b,r2");	/* put dst byte */
    asm(" adi r2,1");		/* next byte addr */
    asm(" sui r5,1");		/* decr count */
    asm(" bgt MBY");		/* go try hw or wd store */
    asm(" bu RET");		/* none, return */
    /* destination byte bounded set one byte */
    asm("DOB stb r1,0b,r2");	/* put dst byte */
    asm(" adi r2,1");		/* next byte addr */
    asm(" sui r5,1");		/* decr count */
    asm(" bgt SDW");		/* go try hw or wd store */
    asm("RET cequ $");		/* return dest address */
    return(dst);
#endif
}
