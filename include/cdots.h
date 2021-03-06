/*~!cdots.h*/
/* Name:  cdots.h Part No.: _______-____r
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

#ifndef CDOTS_H
#define CDOTS_H

#ident	"@(#)nbinclude:cdots.h	1.1"

/* cdots.h - Gould communication region */

#define CDOTS 0x800
#ifndef CDOTP
#define CDOTP ((struct c *)CDOTS)
#endif

/*
 * to get a c dot variable define the following pointer:
 * #define CDOTP ((struct c *)CDOTS)
 *
 * the to reference a cdot variable:
 *
 * to get C.MSD do:
 * CDOTP->msd
 *
 * following macro to get current dqe address from C.CURR
 * #define CDQE ((struct dqe *)(CDOTP->curr.sf))
 *   or
 * to get C.CURR do:
 * (struct dqe *)CDOTP->curr.sf
 *
 */

/* standard linked list head cell */
struct  hc {
    struct  hc*     sf;     /* string forward addr */
    struct  hc*     sb;     /* string back addr */
    char    pri;            /* priority */
    char    cnt;            /* number of entries in list */
    short   fill;           /* fill out to 3wd's */
};

struct c {
    char    date[8];    /* current date as input by operator */
/* next 4 bytes are c.cal */
    char    cent;       /* curr century */
    char    year;       /* curr year */
    char    month;      /* curr month */
    char    day;        /* curr day */
    int     intc;       /* interrupt counter */
    int     time[2];    /* start-up time (c.btime, c.bdate) */
    char    lodc[8];    /* slo device in ascii */
    char    symtab[8];  /* symbol table file name */
    char    podc[8];    /* sbo device in ascii */
    int     sbuf[2];    /* addr of mem pool & length in words */
    char    sidv[8];    /* syc device in ascii */
    short   tmac;       /* tot mem modules available */
    short   emac;       /* E mem modules available */
    short   hmac;       /* H mem modules available */
    short   smac;       /* S mem modules available */
    short   tmcc;       /* tot mem modules configured */
    short   emcc;       /* E mem modules configured */
    short   hmcc;       /* H mem modules configured */
    short   smcc;       /* S mem modules configured */
    char    system[8];  /* name [file] of curr system image */
    char    sypath[16]; /* system pathname prototype */
    char    pchfle[8];  /* patch file name */
    int     trace[2];   /* system trace control word */
    char    dbglm[8];   /* debugger load module name */
    int     swprd;      /* abs blk num of the res descr for swap file */
    int*    swpdev;     /* MVTE address of the actual swap volume */
    int*    iregs;      /* logical addr of tsa reg save area for ipu tasks */
    int*    itsad;      /* logical addr of tsa for ipu tasks */
    int*    losend;     /* logical end of mpx + 1 byte for curr task */
    int*    posend;     /* physical end of non-split mpx + 1 byte */
/*    int     sprdw[6];   /* 3 spare double words dw bounded */
    char    hlpvol[16]; /* help volume name */
    char    hlpdir[16]; /* help volume directory */
    struct hc cipu;     /* standard 3w head cell */
    struct hc ripu;     /* standard 3w head cell */
    struct hc free;     /* standard 3w head cell */
    struct hc prea;     /* standard 3w head cell */
    struct hc curr;     /* standard 3w head cell */
    struct hc sqrt;     /* standard 3w head cell */
    struct hc sq55;     /* standard 3w head cell */
    struct hc sq56;     /* standard 3w head cell */
    struct hc sq57;     /* standard 3w head cell */
    struct hc sq58;     /* standard 3w head cell */
    struct hc sq59;     /* standard 3w head cell */
    struct hc sq60;     /* standard 3w head cell */
    struct hc sq61;     /* standard 3w head cell */
    struct hc sq62;     /* standard 3w head cell */
    struct hc sq63;     /* standard 3w head cell */
    struct hc sq64;     /* standard 3w head cell */
    struct hc swti;     /* standard 3w head cell */
    struct hc swio;     /* standard 3w head cell */
    struct hc swsm;     /* standard 3w head cell */
    struct hc swsr;     /* standard 3w head cell */
    struct hc swlo;     /* standard 3w head cell */
    struct hc susp;     /* standard 3w head cell */
    struct hc runw;     /* standard 3w head cell */
    struct hc hold;     /* standard 3w head cell */
    struct hc anyw;     /* standard 3w head cell */
    struct hc swdc;     /* standard 3w head cell */
    struct hc swdv;     /* standard 3w head cell */
    struct hc swfi;     /* standard 3w head cell reserved */
    struct hc mrq;      /* standard 3w head cell */
    struct hc swmp;     /* standard 3w head cell */
    struct hc swgq;     /* standard 3w head cell */
    int     spch[21];   /* 21 spare words */
    int*    tsad;       /* tsa address pointer */
    int     actseq;     /* activation sequence number */
    int*    adat;       /* address of dqe address table */
    int     bit[2];     /* bit variables */
    int*    cdta;       /* addr of cdt's */
/*  int     cpri;   */  /* task execution bytes */
    char    cup;        /* curr execution priority */
    char    bup;        /* curr base priority */
    char    iop;        /* curr i\o priority */
    char    us;         /* curr stat chain index */
    int*    dque;       /* addr of dispatch queues */
    int*    dtta;       /* addr of device type table */
    int     fadr;       /* unused */
    int     fgonr;      /* unused */
    int     gint;       /* global interrupt counter */
    int     idla;       /* cpu idle time in secs */
    int     idlc;       /* cpu idle time countdown value */
    int*    itlt;       /* address of indirectly conn int table */
    int     batseq;     /* batch sequence number */
    int     jobn;       /* num of concurrent batch jobs */
    int     mgran;      /* bytes per map on this machine */
    short*  midl;       /* addr of o/s midl's */
    int*    miop;       /* addr of miop jump table */
    int**   modd;       /* addr of module addr table */
    int*    mpl;        /* addr of master process list */
    char    msd;        /* byte count of num of maps in o\s (midl count) */
    unsigned midla:24;  /* 24 bit addr of map seg descr (points to c.midl) */
    int     mtim;       /* clock ints per second */
    int     ntim;       /* clock ints per timer unit */
    int*    patch;      /* addr of system debug patch area */
    int*    pool;       /* addr of memory pool */
    int     sgos;       /* default sgo size in blocks */
    int*    sictd;      /* addr of miop td status processor */
    int*    smta;       /* addr of shared memory table */
    int*    arta;       /* addr of allocated resource table */
    int*    spad;       /* addr of cpu scratchpad image */
    int*    svta;       /* addr of svc 1 table */
    int*    svta2;      /* addr of svc 2 table */
    int     swap;       /* swapper status & dqe address */
    int     sycs;       /* default syc size in blocks */
/* byte zero is c.prno */
    int     tskn;       /* task number of current cpu task */
    int*    tsmdqa;     /* dqe addr of tsm */
    int     ttbt[8];    /* task timer bit table. 1 bit/dqe */
    int*    udta;       /* addr of unit definition table */
    int*    ttab;       /* addr of timer table */
    int*    mata;       /* addr of memory table */
    int*    mpaa;       /* low addr of patch area */
    int*    mpac;       /* current addr of patch area */
    int*    mpah;       /* high addr of patch area */
    int*    rmta;       /* addr of resourcemake table */
    int*    emta;       /* addr of eventmark table */
    int     rev;        /* mpx release number */
    int*    debug;      /* address of system debugger */
    int     tdq1;       /* time dist quantum stage 1 */
    int     tdq2;       /* time dist quantum stage 2 */
    int     tdq3;       /* time dist full quantum value */
    int*    regs;       /* tsa addr of curr cpu task */
    int*    mvta;       /* addr of mounted volume table */
    int*    acta;       /* addr of activation table */
    int*    seqa;       /* addr of sequence table */
    int*    scdipu;     /* addr of ipu scheduling task */
    int*    chta;       /* addr of channel definition table */
    int*    etloc;      /* address of event trace logic */
    int     admask;     /* max addr bit mas for machine */
    int     idla1;      /* ipu idle time in seconds */
    int     idlc1;      /* ipu idle time countdown value */
    int*    ipuit1;     /* addr of ipu acct routine */
    int*    ipuit2;     /* addr of ipu acct routine */
    int     btime;      /* binary time in 100 microsec units */
    int     bdate;      /* curr date in days since Jan 1, 1960 */
    int     tcorr;      /* correction factore in 100us (sub from btime) */
    int*    fssp;       /* file system stack ptr */
    int     dptimo;     /* default dual port time out value */
    int*    mdta;       /* addr of mem res descr table */
    int*    mdte;       /* ending addr of mdt */
    int     swplim;     /* min num maps to swap */
    int*    pdqe;       /* dqe addr of partially swapped task */
    int     mpxbr[8];   /* base reg save area */
    int     mpxbrd;     /* default base reg logical map addr */
    int*    ip00;       /* addr of h.ip00 module */
    int     psdbre[2];  /* break entered psd */
    int     psdbrx[2];  /* break exited psd */
    int     psdmse[2];  /* msg entered psd */
    int     psdmsx[2];  /* msg exited psd */
    int     psdeae[2];  /* end act entered psd */
    int     psdeax[2];  /* end act exited psd */
    int*    dsect;      /* addr of dsect for ext mpx */
    int*    adapt;      /* addr of adapter for ext mpx */
    int*    tdefa;      /* addr of termpart if present */
    int*    swiocl;     /* swappers iocl address */
    int*    crdump;     /* addr of crash dump routine */
    int*    hstadr;     /* addr of cpu/ipu state chain history buf */
    short   cdtn;       /* num of cdt entries */
    short   itrs;       /* interval timer resolution in 1/10 microsecs */
    short   smvti;      /* mvt index for swap device */
    short   svtn;       /* num of svc 1 table entries */
    short   udtn;       /* num of udt entries */
    short   rmtm;       /* num of resourcemarks */
    short   emtm;       /* num of eventmarks */
    short   nos;        /* num of blocks for SYSGEN code */
    short   nrst;       /* num of blocks for restart code */
    short   mvtn;       /* num of mounted vol table entries */
    short   artn;       /* num of allocated resource table entries */
    short   chtn;       /* num of chan def table entries */
    short   himap;      /* last locical map blk num avail to task */
    short   svct2;      /* num of svc 2 table entries */
    short   mdtn;       /* num of entries in mem descr table */
    short   mdtav;      /* num of entries available in mdt */
    int     rms[2];     /* 2 words reserved for rms */
    int     gslemc;     /* group swap limit exceeded map count */
    int*    ptrint;     /* PTRACE task activ control addr */
    char    bdbug[8];   /* base task debugger name */
    int*    pet;        /* pet patch addr tab ptr */
    struct hc tsmir;    /* tsm input req head cell */
    struct hc tsmia;    /* tsm input act head cell */
    int     sbufa[2];   /* ioq mem pool addr & size in wds */
    int     sbufb[2];   /* msg mem pool addr & size in wds */
    int*    ipuae;      /* addr of arith exception handler */
    int*    hlpdqa;     /* dqe addr of j.hlp */
/*    short   sprh[8];    /* spare halfwords (8) */
    int     nodeid;     /* RMSS node identifier */
    int*    pmsa;       /* address of PSM table */
    int     rmss;       /* reserved for RMSS */
    short   rcasiz;     /* size of remote context area */
    short   psmsiz;     /* number of context areas */
    short   dptry;      /* dual port retry count */
    short   smaps;      /* num of maps used by system */
    char    bpri;       /* default batch priority */
    char    dttn;       /* num dev type tab entries */
    char    fsflgs;     /* spare byte */
    char    modn;       /* num of mod addr tab entries */
    char    niti;       /* num of itlt entries */
    char    nque;       /* num of dqe entries */
    char    rrun;       /* mem release events counter */
    char    smtn;       /* num of shared mem tbl entries */
    char    tsmcnt;     /* num of active tsm devices */
    char    tsmpri;     /* default tsm task priority */
    char    tsmtot;     /* num of tm devices */
    char    tent;       /* num of timer table entries */
    char    rmtl;       /* low addr of resourcemark area */
    char    emtl;       /* low addr of eventmark area */
    char    conf;       /* configuration flags */
    char    mach;       /* this machine type */
    char    actn;       /* num activ tbl entries */
    char    dbtlc;      /* tlc addr for system debugger */
    char    smts;       /* shared mem tbl size in bytes */
    char    seqn;       /* num of seq tbl entries */
    int*    ipuhis;     /* addr of ipu history buffer */
    int     shrhi;      /* interprocessor mem high bound */
    char    maxswp;     /* max swap size in megabytes */
    char    nload2;     /* sysgen error code */
    char    pdpend;     /* num of public dismounts pending */
/*    char    spb1[9];    /* 9 spare bytes */
    char    psmn;       /* number of PSM table entries */
    char    cdtsiz;     /* size of CDT table in bytes */
    char    dftsiz;     /* size of DFT table in bytes */
    char    dttsiz;     /* size of DTT table in bytes */
    char    fptsiz;     /* size of FPT table in bytes */
    char    ioqsiz;     /* size of IOQ table in bytes */
    char    dpgpri;     /* demand page base priority */
    char    nframe;     /* number of frames in TSA reg stack */
    char    mrglen;     /* length in bytes of the MRRQ fixed hdr area */
    char    mmsg;       /* non-priv max msg cnt */
    char    mrun;       /* non-priv max run req cnt */
    char    mnwi;       /* non-priv max no-wait i/o cnt */
    char    gslegi;     /* group id of task exceeding outswap limits */
    char    gslepr;     /* priority of task exceeding outswap limits */
    char    adafl;      /* flags for ada run-time system */
    char    tkill;      /* num of sec before abort becomes kill */
    char    delta;      /* delta val for ipu tasks */
    char    mpxbrn;     /* num of base regs to load */
    char    dbmaps;     /* num of maps used by system debugger */
    short   swapsz;     /* swapfile size in megabytes */
    int     dtsave;     /* elapsed time before j.dtsave resumes */
    int     shcpu;      /* cpu shadow mem starting map num & count */
    int     shipu;      /* ipu shadow mem starting map num & count */
    int     updt;       /* mpx patch rel revision info */
    int     swpbuf;     /* locical addr of j.swapr's sys buffer */
    int     mrqtmr;     /* timer used by j.swapr */
/*  int     spare;      /* spare word */
    int     shbth;      /* shadow mem in cpu/ipu. strt blk # and # blks */
    int*    tables;     /* where system tables start */
    int*    user;       /* where user cdots start */
    /* new for mpx 3.5 */
    int     dints[31];	/* 31 unused words */
    int*    userva;     /* address of variable size user region */
    int*    tpva;       /* address of 16 word 3rd party vendor area */
    short   exend;      /* address of end of executable memory */
    short   frame;      /* size of each stack frame in TSA non-base area */
    int     scofdq;     /* cpu/ipu spad offset for task dqe address */
    int*    ctsad;      /* logical addr of TSA for CPU task */
    int     age;        /* virtual time before page considered aged */
    int*    efrpg;      /* free page head cell for E class */
    int*    hfrpg;      /* free page head cell for H class */
    int*    sfrpg;      /* free page head cell for S class */
    int*    dfrpg;      /* free page head cell for D class */
    int*    mpfrpg;     /* free page head cell for multi-proc mem */    
    int*    mptla;      /* phy mem alloc ptr list addr */
    int*    cregs;      /* log addr of TSA stack for curr CPU task */
    int*    ptea;       /* phy page tbl entry addr */
    int*    psta;       /* phy page tbl state addr */
    short   chtsiz;     /* size of CHT table in bytes */
    short   dqesiz;     /* size of DQE entry in bytes */
    short   rdsiz;      /* size of RD in bytes */
    short   mpmac;      /* total valid conf'd multi-proc memory */
    short   begpgo;     /* num of map blks to page out */
    short   endpgo;     /* num of map blks to stop page out */
    short   dmcc;       /* tot conf DRAM */
    short   dmac;       /* tot avail DRAM */
    int     bit1[2];    /* 64 bit variables */
    short   spgol[4];   /* shared page table queue head cell */
    int     comm[2];    /* reserved for comm-32 */
    int     sprwx[60];  /* 60 spare words for MPX */
    short   rhwx;       /* reserved hw */
    short   tpgoc;      /* tot num of pages in system ready to pageout */
    short   mvtsiz;     /* size of MVT table in bytes */
    short   dcasiz;     /* size of DCA table in bytes */
    char    rcbsiz;     /* size of RCB table in bytes */
    char    udtsiz;     /* size of UDT table in bytes */
    char    dptsiz;     /* size of DPT table in bytes */
    char    tiqsiz;     /* size of TIQ table in bytes */
    char    mrqsiz;     /* size of MRQ table in bytes */
    char    rbx1;       /* reserved */
    char    pcbsiz;     /* size of PCB block in bytes */
    char    artsiz;     /* size of ART table in bytes */
    char    detsiz;     /* size of DET table in bytes */
    char    bbhsiz;     /* size of BB head cell bytes */
    char    vatsiz;     /* size of VAT table in bytes */
    char    rbx2;       /* reserved */
    int     r4mpx[5];   /* 5 spare words */
    /* 0xf00 in size */
};
#endif
