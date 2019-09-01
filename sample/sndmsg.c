/*~!sndmsg.c*/
/* Name:  sndmsg.c Part No.: _______-____r
 *
 * Copyright 1993 - J B Systems, Morrison, CO
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

#ident	"@(#)sample:sndmsg.c	1.0"

#include <stdio.h>
#include <sys/types.h>
#include <psb.h>

static char conbuf[80];

static int tcpb[3] = {0,0,0};
static char lstr[120];

/* routine to type a message on the console */
void contyp(str)
char *str;
{
    int i;

    strcpy (lstr, str);
    i=strlen(str);
    tcpb[0]= (((unsigned)i << 20) | 0x00080000) |  (int)lstr;
    asm(" la r1,_tcpb");
    asm(" svc 1,x'3f'");
}

static int sendbuf[36];		/* parameter send block */
static int retbuf[8];		/* parameter return block */
static struct psb psb;		/* message block */

/* send a message to a waiting task */
sndmsg(usaddr,count,reason,pid)
int *usaddr;		/* shared memory address */
int count;		/* buffer count */
int reason;    		/* reason to wake task */
int pid;		/* task to wake */
{
    register int *pp = (int *)&psb;	/* must be 1st reg var (r7) */
    register int status = 0;		/* must be 2nd reg var (r6) */
    int* sbp = sendbuf;
    int i;

    /* now send the wakeup to the client task */
    for (i=0; i<(sizeof(psb)/sizeof(int)); i++)
      pp[i] = 0;		/* clear psb */
    psb.lmn = pid;		/* process to wake */

    sendbuf[0] = reason;	/* our reason for msg */
    sendbuf[1] = (int)usaddr;	/* user address */
    sendbuf[2] = count;		/* buffer size */

    psb.pnv = 0;
    psb.opt = 0x00;		/* send wait, 0x80 for no wait */
    psb.squa = 3*sizeof(int);	/* send count */
    psb.sba = (int *)sbp;	/* send buffer address */
    psb.rpbl = 8;		/* 8 bytes to return max */
    psb.rba = (int *)retbuf;	/* return buffer */
    psb.eaa = 0;		/* no end action routine for now */

    /* note parameter send block address is FIRST register variable
     * and address will be in r7
     * status is SECOND register variable
     * and address will be in r6
     */
    asm (" trr r7,r2");		/* psb address */
    asm (" svc 1,x'6c'");	/* send message M.SMSGR */

    /* see if error.  This should not happen */
    if (status) {		/* if non zero, we have an error */
        if (status == 1) {
    	    sprintf(conbuf,"\rsndmsg - client died. pid = %x\n",
    		psb.lmn);
    	    contyp(conbuf);
    	}
    	return (-1);		/* return an error */
    }
    /* if msg sent O.K., the return status and errno value
     * will be returned in the retbuf
     */
    if (psb.acrp == 0) {
    	/* if no bytes returned, we have an error */
#ifdef DEBUG
    printf("sndmsg: no bytes: status = %x, cst = %x\n", status, psb.cst);
#endif
    	return (-1);		/* return an error */
    }
    return (retbuf[0]);		/* return the user status */
}
