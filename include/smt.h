/*~!smt.h*/
/* Name:  smt.h Part No.: _______-____r
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

#ifndef SMT_H
#define SMT_H

#ident	"@(#)nbinclude:smt.h	1.0"

#ifndef MPX1X

struct smt {
    int	    rid[8];	/* resource identifier */
    int     name[2];	/* partition name */
    int	    tnum[2];	/* ownername or task # of associated task */
    int     ownr[2];	/* ownername of partition creator */
    int	    proj[2];	/* project group of partition creator */
    int	    srid[2];	/* swap file resource */
    int     comp;       /* compatibility version level */
    int     pnid;       /* pathname identifier */
    int     arta;       /* addr of associated art entry */
                        /* byte zero of smt.arta is smt.ind */
                        /* shared memory table index */
    int     flags;      /* partition flags */
    short   page;       /* starting 512-word page number */
    short   ptot;       /* total number of pages */
    short   maps;       /* starting map number */
    short   mapn;       /* number of map blocks */
    short   dses;       /* start of dsect */
    short   dsen;       /* num of blocks in dsect */
    short   cses;       /* start of csect */
    short   csen;       /* num of blocks in csect */
    char    mty;        /* memory type */
    char    ucnt;       /* num of tasks not outswapped */
    short   pool;       /* num of words in mem pool for midl's */
    short   wbks;       /* file offset within shared image disc file */
    short   notu;       /* not used */
    short*  midl;       /* address of midl in mem pool */
    int     wbkn;       /* size if read/write sect to be written */
    short   cme;        /* num of swappable e-class maps */
    short   cmh;        /* num of swappable h-class maps */
    short   cms;        /* num of swappable s-class maps */
    short   otsw;       /* total num of outswapped maps */
    int     time[2];    /* time when shared csect was linked */
    int     date[2];    /* date when shared csect was linked */
    char    spbt[3];    /* 3 spare bytes */
    char    tuc;        /* swapper trial count */
    int     bias;       /* shared task's bias offset */
    int	    resd[2];	/* reserved */
};

#else

struct smt {
    int     name[2];	/* partition name */

    int	    tnum[2];	/* ownername or task # of associated task */

    short   flags;      /* partition flags */
    char    acnt;	/* # tasks sharing this area */
    char    ucnt;	/* # tasks sharing this area not outswapped */

    char    mapn;       /* number of map blocks */
    char    maps;       /* starting map number */
    char    mty;	/* memory type */
    char    que;	/* num of tasks queued to this table */

    short   page;       /* starting 512-word page number */
    short   ptot;       /* total number of pages */

    short   sctn;	/* sectors in swap file */
    short   pswd;	/* compressed password */

    char    udti;	/* udt index of swap file */
    unsigned scta:24;	/* sector address of swap file */

    char    ind;	/* shared memory table index */
    unsigned resv:24;	/* reserved */

    short   midl[12];	/* midl entries */
};

#endif /* MPX1X */
#endif /* SMT_H */
