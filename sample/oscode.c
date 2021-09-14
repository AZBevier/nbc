/*~!oscode.c*/
/* Name:  oscode.c Part No.: _______-____r
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

#ident	"@(#)nbsamp:oscode.c	1.0"

/* this routine shows how to generate a handler for MPX.  It show how
 * to interact with the system and also how to define SVC's.  All code
 * must be in DSECT.  Use the -H option to nbcc.  Notice use of function
 * and inline assembler to make the calls.
 */

/*
 ********************************************************************
 *
 *  Functional description:
 *  -----------------------
 *
 *  This module is the interface between client program that talks to
 *  the user, and the tasks running in the system.  A client task places
 *  requests in the static partition, and then go to sleep.  This handler
 *  will wake up on each clock tick and process these requests, then go
 *  to sleep itself.
 *     The requests are:
 *       get data from a task or partition
 *       store data in a task or parition
 *       wake up another client task
 *       break a task
 *
 *  Program definition:
 *  -------------------
 *
 *  H.OSCODE is an MPX system module, and is called via a HAT entry.
 *  We have the initialization entry point of H.OSCODE share the
 *  real-time clock interrupt.
 *
 *  Commons:
 *  --------
 *  H.OSCODE uses the OSPART common that client programs use.
 *
 *******************************************************************************
 */

/*
 *******************************************************************************
 * this is an mpx handler written in 'c'
 *******************************************************************************
 */

asm ("hat dataw 1");            /* sysgen needs a hat */
asm (" acw sg.ini");            /* tell sysgen where to go */

/* include system table definitions */
#define MPX3X		/* this is code for MPX 3.X */
#include <mosde.h>
#include <cdots.h>
#include <dqe.h>
#include <tsa.h>
#include <smt.h>

#define TRUE    1
#define FALSE   0
#define LOGPADR 0xc0000

/*
 * local subroutines
 */

static int *xlear();
static int *lear();
static void goumap();
static void gomap();

#define MAXCL 8		/* maximum number of clients */
#define NodeInactive 0
#define NodeActive 1
#define ShutDown 1

/* client task communication area */
struct client {
    int taskNum;	/* client task number */
    int nodeNum;	/* node of client */
    int Status;		/* client status */
#define stPending 1	/* waiting for request */
#define stBeingProcessed 2 /* being worked on */
#define stComplete 4	/* request complete */
    int ReqCode;	/* request code */
#define reqGet 1	/* get task data */
#define reqPut 2	/* put task data */
#define reqWakeup 3	/* wakeup a task */
#define reqBreak 4	/* send break to a task */
    unsigned int TaskNo;  /* requested task/partition number */
    int LogAddr;	/* logical address */
    int Len;		/* request length */
    int Data[8];	/* data I/O area */
};

/* partition layout for our node */
struct node {
    int	NodeNum;	/* our node number */
    int Flag;		/* node status flags */
    int Active;		/* state */
    struct client client[MAXCL];	/* client structures */
};

/*
 * Local variables
 */

static  int     initDone = FALSE; /* set non zero when init is all done */
static  int     nodenum = 0;      /* local node number */
static  int     ticksx1;          /* clock ticks in 1 seconds */
static  int     ticksx5;          /* clock ticks in 5 seconds */
static  int     ticksday;         /* clock ticks in a day (86400 secs) */
static  int     strtclk = 0;      /* starting clock ticks */
static  int     spsave;           /* save sp during resume call */
static  int*    realpadr;         /* real partition address */
/* logical partition address */
static  struct node *laddr = (struct node *)LOGPADR;
static	struct node *nodep;       /* physical partition address */
static	struct client *clp;       /* current client table pointer */
static  struct dqe * dqeptr;      /* static pointer to dqe */
static  int     dqen;             /* temp dqe number */
static  struct tsa * tsaptr;      /* static pointer to tsa */
static  struct smt * smtptr;      /* static pointer to smt */

/* c defined in cdots.h include file as structure for cdot region*/
#define CDOTP ((struct c *)CDOTS)

/* t defined in tsa.h include file as structure for task tsa (c.tsad) */
#define TSAP (*(struct tsa **)C_TSAD)

/* smt defined in smt.h include file as structure for smt (c.smta) */
#define SMTP (*(struct smt **)C_SMTA)
/* smt entry size in bytes */
#define SMTS (*(char *)C_SMTS)
/* number of smt entries */
#define SMTN (*(char *)C_SMTN)

/* dqe defined in dqe.h include file as structure for task dqe */
/* following macro to get dqe addr given dqe num */
#define DQEP(n) (((struct adat *)C_ADAT)->dqe[n])
/* following macro to get current dqe address from C.CURR */
#define CDQE ((struct dqe *)(CDOTP->curr.sf))

/* routine to handle clock interrupts */
/* entered at each clock int */
void rtclk()
{
  int     progn;           /* client program index */
  int     index;           /* index to first entry */

  if (!initDone)return;   /* exit if not ready to run yet */

  /* see if we have been requested to shutdown */
  /* if so, go inactive */
  if (nodep->Flag & ShutDown) {
    nodep->Active = NodeInactive;	/* set us inactive */
    nodep->Flag &= !ShutDown;		/* shut off shutdown flag */
    for (progn = 0; progn < MAXCL; progn++) {
      clp = &nodep->client[progn];	/* curr client */
      /* see if client assigned to us */
      if ((clp->nodeNum == nodenum) && clp->taskNum) {
        /* get task number & see if active */
        /* get dqe addr */
        dqeptr = DQEP(clp->taskNum >> 24);
        /* if task executing, abort it */
        if (dqeptr->us >= CURR) {
          asm (" stw  sp,_spsave");	/* save stack pointer */
          asm (" ext  S.EXEC18");	/* exec resume routine */
          asm (" lw   r1,_dqeptr");	/* get dqe addr in r2 */
          asm (" lw   r5,=C'OSCO'");
          asm (" lw   r6,=C'DEXI'");
          asm (" lw   r7,=C'TING'");
          asm (" bl   S.EXEC18");	/* go to exec */
          asm (" lw   sp,_spsave");	/* get back our sp */
        }
      }
    }
    initDone = FALSE;
    return;
  }

  /*
   * recover lost entries 
   */

  for (progn = 0; progn < MAXCL; progn++) {
    clp = &nodep->client[progn];		/* curr client */
    /* see if client assigned to us */
    if ((clp->nodeNum == nodenum) && clp->taskNum) {
      /* get task number & see if active */
      /* get dqe addr */
      dqeptr = DQEP(clp->taskNum >> 24);
      /* if task executing, continue */
      if ((dqeptr->tan != clp->taskNum) || (dqeptr->us < CURR)) {
        /* task has aborted, clean up */
        clp->taskNum = 0;
      }
    }
  }

  /* handle client requests */

  for (progn = 0; progn < MAXCL; progn++) {
    clp = &nodep->client[progn];		/* curr client */
    if ((clp->Status == stPending) ||
      (clp->Status == stBeingProcessed)) {
          if(clp->nodeNum == nodenum) {

            /* an entry has been found for me to process */
            int getput = 0;     /* flag for get and put */

            switch (clp->ReqCode) {

              case reqGet:
                getput = 1;

              case reqPut:
                /* see if task or partition */
                if (dqen = (clp->TaskNo >> 24)) {
                  /* we have a task number */
                  /* data addr map start */
                    int das = (int)clp->LogAddr;
                  /* data addr map start */
                    int dae = das + clp->Len - 1;
                    int cntr;
                    dqeptr = DQEP(dqen);
                    if (dqeptr->us < CURR)continue;
                  /* get real tsa address of requested task */
                    tsaptr = (struct tsa *)(((int)(dqeptr->msd)) & 0xffe000);
                  /* loop for each data byte requested */
                    for (cntr=0; cntr < clp->Len; cntr++) {
                    /* calc logical map number */
                      int curlmap = ((das + cntr) >> 13) - CDOTP->msd;
                      short * midlptr = (short *)dqeptr->msd;
                    /* look for valid map */
/*                    if (midlptr[curlmap] & 0x8000) */
                    /* get physical map num & calc real addr */
                      int phyadr = (((int)(midlptr[curlmap]) << 13) &
                         0xffe000) | ((das + cntr) & 0x1fff);
                      if (getput)
                    /* get data from memory */
                        clp->Data[cntr] = (*(char *)phyadr);
                      else
                    /* put data in memory */
                        *(char *)phyadr = clp->Data[cntr];
                    }
                } else {
                  /* we have a partition index */
                  /* data addr map start */
                    int das = (int)clp->LogAddr;
                  /* data addr map start */
                    int dae = das + clp->Len - 1;
                    int cntr;
                    int psla;
                  /* get smt addr of requested partition */
                    smtptr = (struct smt *)((int)SMTP +
                      (SMTS * clp->TaskNo));
                  /* set logical starting address */
                    psla = smtptr->page << 11;
                  /* loop for each data byte requested */
                    for (cntr=0; cntr < clp->Len; cntr++) {
                    /* calc logical map offset number */
                      int mapoff = (das - psla + cntr) >> 13;
                    /* get physical map num & calc real addr */
                      int phyadr = (((int)(smtptr->midl[mapoff]) << 13) &
                         0xffe000) | ((das - psla + cntr) & 0x1fff);
                      if (getput)
                    /* get data from memory */
                        clp->Data[cntr] = (*(char *)phyadr);
                      else
                    /* put data in memory */
                        *(char *)phyadr = clp->Data[cntr];
                    }
                }
                clp->Status = stComplete;  /* all done now */
                break;

    	      /* wakeup a suspended task */
              case reqWakeup:
                /* get dqe addr */
                dqeptr = DQEP(clp->TaskNo >> 24);
                /* if task suspended, resume it; else wait till later */
                if (dqeptr->us == SUSP) {
                  asm (" stw  sp,_spsave");	/* save stack pointer */
                  asm (" ext  S.EXEC14");	/* exec resume routine */
                  asm (" lw   r2,_dqeptr");	/* get dqe addr in r2 */
                  asm (" bl   S.EXEC14");	/* go to exec */
                  asm (" lw   sp,_spsave");	/* get back our sp */
                  clp->Status = stComplete;	/* all done now */
                }
                break;

    	      /* break specified task */
              case reqBreak:
                /* get dqe addr */
                dqeptr = DQEP(clp->TaskNo >> 24);
                /* send break to specified task */
                asm (" stw  sp,_spsave");	/* save stack pointer */
                asm (" ext  S.EXEC13");		/* exec break routine */
                asm (" lw   r2,_dqeptr");	/* get dqe addr in r2 */
                asm (" bl   S.EXEC13");		/* go to exec */
                asm (" lw   sp,_spsave");	/* get back our sp */
                clp->Status = stComplete;	/* all done now */
                break;

              default:
                break;

            } /* end switch */
          } /* if our node */
      } /* if status pending or being processed */
  } /* for each client index */
}

/* routine to handle svc 1,6 init start processing */
/* r7 has node number to save */
instrt()
{

    nodenum = TSAP->regp->reg[7];   /* get node num from callers r7 */
    initDone = FALSE;               /* set init not done yet */
}

/* init done SVC */
/* routine to handle svc 1,7 init complete processing */
void indone()
{
    if (initDone == FALSE)
        initDone = TRUE;		/* show init done now */
    TSAP->regp->reg[7] = initDone;	/* return initDone status to user r7 */
    strtclk = CDOTP->intc;		/* get starting time */
    realpadr = lear(laddr);		/* get real partition address */
    nodep = (struct node *)realpadr;	/* set OSPART part real addr */
    laddr->Active = NodeActive;		/* set us active */
    laddr->Flag &= !ShutDown;		/* shut off shutdown flag */
}

/* routine to handle svc 1,8 Task init processing */
/* r7 returns current node number */
/* r6 returns timer ticks per second */

void intask()
{
    if (initDone) {
        TSAP->regp->reg[6] = ticksx1;   /* return ticks per second in r6 */
        TSAP->regp->reg[7] = nodenum;   /* return nodenum to user r7 */
    } else {
        TSAP->regp->reg[6] = ticksx1;   /* return ticks per second in r6 */
        TSAP->regp->reg[7] = FALSE;     /* return FALSE status to user r7 */
    }
}

/* local subroutines */
/* routine to get real address from tsa */
static int *xlear(addr)
int *addr;
{
    int     mapnum;

    /* get map number */
    mapnum = (((int)addr & 0xffffff) >> 13) - CDOTP->msd;

    /* return real variable address */
    return ((int *)(((TSAP->midla[mapnum] << 13)
        | ((int)addr & 0x1fff)) & 0xffffff));
}

/* routine to get real address */
static int *lear(addr)
int *addr;
{
    asm (" lw   r1,3W,sp");       /* get old stack pointer */
    asm (" lw   r1,8W,r1");       /* get callers parameter */
    asm (" lear r0,0w,r1");       /* make it real */
}

/* routine to go unmapped */
static void goumap()
{
    asm ("     lpsd  psd1");
    asm ("     bound 1d");
    asm ("psd1 gen   8/x'84',24/goon");
    asm ("     dataw x'00018000'");
    asm ("goon equ   $");
}

/* routine to go mapped */
static void gomap()
{
    asm ("      lpsd  psd2");
    asm ("      bound 1d");
    asm ("psd2  gen   8/x'84',24/gmon");
    asm ("      dataw x'80018000'");
    asm ("gmon  equ   $");
}

/* this is the interface code to the clock int */
/* it is entered at each clock interrupt */
    asm (" bound 1w");             /* word bound */
    asm ("clki  equ $");           /* entry */
    asm (" stf  r0,lclstk");       /* save regs */
    asm (" la   sp,lclstk");       /* get local stack address */
    asm (" bl   _rtclk");          /* call real time clock int rtn */
    asm (" lf   r0,0w,sp");        /* restore regs */
    asm ("rtci  nop");             /* execute replaced h.ipcl instr */
    asm ("reti  bu $-$");          /* return to h.ipcl */
    asm (" res  8f");              /* local stack */
    asm ("lclstk res 1f");         /* local save area */

/* this is the interface code for svc 1,6 Init start svc */
/* the svc's use t.fssp stack area in the tsa */
    asm (" bound 1w");             /* word bound */
    asm ("svc1_6 equ $");          /* entry */
    asm (" lw   r3,x'a80'");       /* get tsa address C.TSAD */
    asm (" lw   sp,x'5bc',r3");    /* get T.FSSP pointer from tsa */
    asm (" bl   _instrt");         /* call init svc routine */
    asm (" ext  S.EXEC20");        /* svc return address */
    asm (" bu   S.EXEC20");        /* return from svc */

/* this is the interface code for svc 1,7 Init Done svc */
/* the svc's use t.fssp stack area in the tsa */
    asm (" bound 1w");             /* word bound */
    asm ("svc1_7 equ $");          /* entry */
    asm (" lw   r3,x'a80'");       /* get tsa address C.TSAD */
    asm (" lw   sp,x'5bc',r3");    /* get T.FSSP pointer from tsa */
    asm (" bl   _indone");         /* call init done svc routine */
    asm (" ext  S.EXEC20");        /* svc return address */
    asm (" bu   S.EXEC20");        /* return from svc */

/* this is the interface code for svc 1,8 Taskinit svc */
/* the svc's uses t.fssp stack area in the tsa */
    asm (" bound 1w");             /* word bound */
    asm ("svc1_8 equ $");          /* entry */
    asm (" lw   r3,x'a80'");       /* get tsa address C.TSAD */
    asm (" lw   sp,x'5bc',r3");    /* get T.FSSP pointer from tsa */
    asm (" bl   _intask");         /* call taskinit svc routine */
    asm (" ext  S.EXEC20");        /* svc return address */
    asm (" bu   S.EXEC20");        /* return from svc */

static int tcpb[3] = {0,0,0};

/* routine to type a message on the console */
static void typ(str)
char *str;
{
    int i;
    for(i = 1; str[i] != 0; i++);
        tcpb[0] = i << 20 | 0x00080000 | (int)str;
    asm(" la  r1,_tcpb");
    asm(" svc 1,x'3f'");
}

/* this is the sysgen initialization entry */
    asm (" lpool");
    /* save regs and use as parameters to function sgent */
    asm ("sg.ini stf r0,stack-1f");
    asm (" la sp,stack-2f");
    asm (" bl _sgent");
    asm (" lf r0,stack-1f");
    asm (" trsw r0");
    /* stack space for iniialization */
    asm (" res 12f");
    asm ("stack equ $");

/* instructions used during sysgen */
    asm ("bri bu clki");            /* br instruction put in h.ipcl */

sgent(reg0,reg1,reg2,reg3,reg4,reg5,reg6,reg7)
int reg0, reg1, reg2, reg3, reg4, reg5, reg6, reg7;
{
    /* sysgen init code here */

    asm (" ext  IPCL.ICB");        /* connect to rtc code */
    asm (" la   r1,IPCL.ICB");     /* get clock icb address */
    asm (" lw   r1,2w,r1");        /* get new psd wd 1 */
    asm (" adi  r1,2w");           /* skip abm & stf instrs */
    asm (" anmw r1,=x'ffffff'");   /* keep address only */
    asm (" lw   r0,=x'ec000000'"); /* get bu instruction */
    asm (" orr  r1,r0");           /* or in return address */
    asm (" adi  r0,1w");           /* location to return to */
    asm (" stw  r0,reti");         /* set return instr in code */
    asm (" lw   r0,0w,r1");        /* get instr from h.ipcl */
    asm (" stw  r0,rtci");         /* put instr in local code */
    asm (" lw   r0,bri");          /* get branch to us instruction */
    asm (" stw  r0,0w,r1");        /* put in h.ipcl code */

    asm (" lw   r1,x'b00'");       /* get C.SVTA address */
    asm (" la   r0,svc1_6");       /* get svc 1,6 routn address */
    asm (" stw  r0,6w,r1");        /* put address in svc 1 table */
    asm (" la   r0,svc1_7");       /* get svc 1,7 routn address */
    asm (" stw  r0,7w,r1");        /* put address in svc 1 table */
    asm (" la   r0,svc1_8");       /* get svc 1,8 routn address */
    asm (" stw  r0,8w,r1");        /* put address in svc 1 table */

    asm (" li   r7,1");            /* calculate 1 secs of ticks */
    asm (" mpmw r6,x'adc'");       /* ..times C.MTIM */
    asm (" dvmw r6,x'ae0'");       /* ..divided by C.NTIM */
    asm (" stw  r7,_ticksx1");      /* save ticks in 1 secs */

    asm (" li   r7,5");            /* calculate 5 secs of ticks */
    asm (" mpmw r6,x'adc'");       /* ..times C.MTIM */
    asm (" dvmw r6,x'ae0'");       /* ..divided by C.NTIM */
    asm (" stw  r7,_ticksx5");      /* save ticks in 5 secs */

    asm (" lw   r7,=86400");       /* calc 1 day (86400 secs) of ticks */
    asm (" mpmw r6,x'adc'");       /* ..times C.MTIM */
    asm (" dvmw r6,x'ae0'");       /* ..divided by C.NTIM */
    asm (" stw  r7,_ticksday");     /* save ticks in a day */

        return;                    /* return to SYSGEN */
}
