/*~!dqe.h*/
/* Name:  dqe.h Part No.: _______-____r
 *
 * Copyright 1994 - J B Systems, Morrison, CO
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

#ifndef DQE_H
#define DQE_H

#ident	"@(#)nbinclude:dqe.h	1.1"

/*
 * to access a dqe do the following defines:
 *
 * following macro to get dqe addr given dqe num
 * #define DQEP(n) (((struct adat *)C_ADAT)->dqe[n])
 *
 * following macro to get current dqe address from C.CURR
 * #define CDQE ((struct dqe *)(CDOTP->curr.sf))
 *
 * then to use them to let's say get the task number (DQE.TAN)
 * for dqe number 3:
 *
 * int tnum = DQEP(3)->tan;  get the task num from 3rd dqe
 *
 * to get task number from current task in cpu:
 * int tnum = CDQE->tan;     get the task num from curr cpu task
 *
 */

/*
 * state chain equates -
 * valid values for dqe.us
 *
 */

#define     FREE    0x00
#define     PREA    0x01
#define     CURR    0x02
#define     SQRT    0x03
#define     SQ55    0x04
#define     SQ56    0x05
#define     SQ57    0x06
#define     SQ58    0x07
#define     SQ59    0x08
#define     SQ60    0x09
#define     SQ61    0x0a
#define     SQ62    0x0b
#define     SQ63    0x0c
#define     SQ64    0x0d
#define     SWTI    0x0e
#define     SWIO    0x0f
#define     SWSM    0x10
#define     SWSR    0x11
#define     SWLO    0x12
#define     SUSP    0x13
#define     RUNW    0x14
#define     HOLD    0x15
#define     ANYW    0x16
#define     SWDC    0x17
#define     SWDV    0x18
#define     SWFI    0x19
#define     MRQ     0x1a
#define     SWMP    0x1b
#define     SWGQ    0x1c
#define     CIPU    0x1d
#define     RIPU    0x1e

struct adat {
    struct dqe ** dqe;      /* definition for array of dqe addresses */
};

struct  dqe {
        struct dqe* sf;     /* string forward pointer */
        struct dqe* sb;     /* string back pointer */
        char    cup;    /* current user priorioty */
        char    bup;    /* base priority of task */
        char    iop;    /* i/o priority */
        char    us;     /* state chain index (0->x'1e') */
        int     tan;    /* task number, byte 0 = dqe number */
        union   {
        double  on;     /* ownername as a double word */
        char    onb[8]; /* ownername as 8 bytes */
        }onu;
        double  lmn;    /* load module name */
        double  psn;    /* pseudonym associated with task */
        int     usw;    /* user status word */
        int     ushf;   /* scheduling flags */
        int*    msd;    /* physical address of midl in tsa */
        int     dctr;   /* kill/abort timer */
        char    mmsg;   /* max num of no-wait messages */
        char    mrun;   /* max num of no-wait run requests */
        char    mnwi;   /* max num of no-wait i/o requests */
        char    cqfn;   /* generalized queue function code */
        char    uf2;    /* scheduling flags */
        char    ipuf;   /* IPU flags */
        char    nwio;   /* num of no-wait i/o requests */
        char    sopo;   /* priority bias only swapping flags */
        int     cqc;    /* current quantum count */
        char    sh;     /* used by j.swapr to swap shadow memory */
        char    shf;    /* shadow memory flags */
        char    tifc;   /* timer function code */
        char    rilt;   /* request interrupt level for timer */
        int     uts1;   /* user timer slot word 1 */
        int     uts2;   /* user timer slot word 2 */
        int     dsw;    /* base mode debugger status word */
        int     prs;    /* peripheral requirements specification */
        int     prm;    /* peripheral requirements mask */
        char    freeb1; /* free byte 1 */
        char    tskf;   /* task flags */
        char    mspn;   /* TSA maps required to span MIDL's & MEML's */
        char    mst;    /* static memory type specification */
        int*    pssf;   /* pre-emptive system service head cell sf ptr */
        int*    pssb;   /* pre-emptive system servive head cell sb ptr */
        char    pspr;   /* pre-emptive system service priority (0) */
        char    psct;   /* pre-emptive system service entry count */
        char    iln;    /* interrupt level number for int conn tasks */
        char    resu;   /* reserved usage index */
        int*    tisf;   /* task int head cell sf ptr */
        int*    tisb;   /* task int head cell sb ptr */
        char    tipr;   /* task int head cell priority (0) */
        char    tict;   /* task int head cell entry count */
        char    swif;   /* swap inhibit flags */
        char    ubio;   /* num of unbuffered i/o req's outstanding */
        int*    rrsf;   /* run recvr head cell sf ptr */
        int*    rrsb;   /* run recvr head cell sb ptr */
        char    rrpr;   /* run recvr head cell priority (0) */
        char    rrct;   /* run recvr head cell entry count */
        short   nsct;   /* num of map blocks outswapped */
        int*    mrsf;   /* msg recvr head cell sf ptr */
        int*    mrsb;   /* msg recvr head cell sb ptr */
        char    mrpr;   /* msg recvr head cell priority (0) */
        char    mrct;   /* msg recvr head cell entry count */
        char    nwrr;   /* num of no-wait run req's outstanding */
        char    nwmr;   /* num of no-wait msg req's outstanding */
        char    rti;    /* requested task interrupt flags */
        char    nwlm;   /* no-wait run request limit */
        char    ati;    /* active task interrupt flags */
        char    freeb2; /* free byte 2 */
        int     tad;    /* tsa address (logical) byte 0 is system */
                        /* action task interrupt request */
        int     abc[3]; /* abort code (12 chars) */
        int     tsap;   /* reserved for future use */
        int     srid[2];/* used swap space linked list */
        int     cdir[8];/* load mod RID at activation.  also */
                        /* curr working volume at activation */
        char    gid;    /* group swap identification */
        char    fb3[3]; /* 3 free bytes */
        int     acx2;   /* adv comm word */
        char    mrq;    /* mem req double word 1st byte */
        char    mem;    /* type of mem req */
        short   memr;   /* num of mem blocks req'd */
        char    mrt;    /* mem req type code */
        char    fb4;    /* reserved */
        short   rmmr;   /* map reg for req mem */
        short   mapn;   /* includive span of maps in use */
        short   cme;    /* num of swappable E class maps */
        short   cmh;    /* num of swappable H class maps */
        short   cms;    /* num of swappable S class maps */
	int     fw[6];	/* reserved */
 };
#endif
