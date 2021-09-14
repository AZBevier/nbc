/*~!mpxsvc.c*/
/* Name:  mpxsvc.c Part No.: _______-____r
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

#ident	"@(#)nbclib:mpxsvc.c	1.0"

/* This is the re-entrant version of mpxsvc.  It allows multiple svc's
 * to be called from no-wait end-action processing.
 *
 * calling sequence [ cc = mpcsvc(svcno, inreg, outreg) ]
 * cc is an int returning cc's right justified
 * inreg is 8 word integer array of register values for svc
 * outreg is 8 word integer array of register values from the svc
 * svcno is in form of 0x2023 for svc 2,x'23'
 * -1 is returned if out of storage space
 */

#define	MAXSVCS 20	/* max of 20 nested svc's */

asm ("	bound	1f");
static struct xeqer {
	int regs[8];	/* in/out regs */
	/* non zero when in use */
	int ins0;	/* lf r0,regs */
        int svc;	/* svc to xeq */
	int ins1;	/* stf r0,regs */
	int getcc;	/* bl $+1w */
	int ins2;	/* lw r3,spsave */
	int ins3;	/* la r7,regs */
        int brback;	/* bu goon (in csect) */
	int spsave;	/* curr sp */
} pstack [MAXSVCS] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

static	int	stfi	= 0xdc000000;
static	int	lfi	= 0xcc000000;
static	int	svci	= 0xc8060000;
static	int	lw3i	= 0xad800000;
static	int	la7i	= 0x37800000;
static	int	bli	= 0xf8800001;

int mpxsvc(svcno, inreg, outreg)
int svcno;
int *inreg;
int *outreg;
{
register struct xeqer *ps = pstack;
register int temp = 0;
int i, j;

  for (i = 0; i < MAXSVCS; i++, ps++) {
    if (ps->ins0)continue;	/* used as busy cell */
    ps->ins0 = lfi | (int)(ps);
    ps->svc = svci | (svcno & 0xffff);
    ps->ins1 = stfi | (int)(ps);
    ps->getcc = bli | (int)(&ps->ins2);
    ps->ins2 = lw3i | (int)(&ps->spsave);
    ps->ins3 = la7i | (int)(ps);
    for (j = 0; j < 8; j++)ps->regs[j] = inreg[j];
    asm("	trr	r3,r6");
    ps->spsave = temp;	/* save current stack pointer */
    asm("	trr	r7,r1");
    asm("	lw      r0,bugo");
    asm("	stw     r0,14w,r1");	/* set brback */
    asm("	bu	8w,r1");	/* go xeq svc code */

    asm("bugo	bu	goon");

    asm("goon	cequ	$");	/* where we return */
    /* here, r0 has cc's, r7 has ps again, r3 has sp again */
    asm("	trr	r0,r6");
    asm("	sll	r6,1");
    asm("	srl	r6,28");
    for (j = 0; j < 8; j++)outreg[j] = ps->regs[j];
    ps->ins0 = 0;	/* set not busy */
    return(temp);	/* return cc's */
  }
  return(-1);	/* error, ran out of buffers */
}
