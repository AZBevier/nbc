/*~!getcwvd.c*/
/* Name:  getcwvd.c Part No.: _______-____r
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

#ident	"@(#)nbclib:getcwvd.c	1.0"

#include <mosde.h>
#include <stdio.h>

extern char curvol[];
extern char curdir[];
#ifdef MPX1X
extern int curwdir[];
extern short userkey;
#endif

/* get current working vol/dir */
/* will be put in curvol, curdir */

void
getcwvd()
{
    int *tsa;
    char *p;
    char *vol;
    char *dir;
    int i,j;
    int reg[8];             /* jcb */

#ifdef MPX1X
#ifdef JUNK
    /* update to current ownername */
    reg[5] = 0x80000000;
    reg[7] = (int) &_myid;
    mpxsvc(0x1064,reg,reg);	/* M.ID */
#endif

    strcpy(curvol,"SYSTEM");		/* default to system volume */
    p = (char *)curwdir;		/* curr dir in word format */
    tsa = (int *)(*((int *)0xa80));  /* c.tsad */
    dir = (char *)(&tsa[0x528/sizeof(int)]); /* username pointer */
    for(i=0; i<8; i++) {
      curdir[i] = ((j = dir[i]) != ' ') ? j : '\0';
/*      curdir[i] = ((j = _myid._cd[i]) != ' ') ? j : '\0'; */
      p[i] = j;
    }
    curdir[8] = '\0';
    userkey = (tsa[0x604/sizeof(int)] & 0xffff); /* save userkey if any */
/*    userkey = _myid._key;		/* save userkey if any */
    asm (" lw 0,x'a80'");      /* if txpm turn off tsa biasing */
    asm (" camw 0,x'a80'");
    asm (" beq $+2w");
    asm (" svc 1,3");
#else
#ifdef MPX35
    mpxsvc(0x207d, reg, reg);       /* jcb */
    tsa = (int*)reg[1];             /* jcb */
#else
    tsa = (int *)(*((int *)0xa80));  /* c.tsad */
#endif
    vol = (char *)(&tsa[0x7b0/sizeof(int)]); /* vol name pointer */
    for (p=curvol, i=0; i<16 && vol[i] != ' '; i++)
      p[i] = vol[i];
    p[i] = NULL;
    dir = (char *)(&tsa[0x7a0/sizeof(int)]); /* dir name pointer */
    for (p=curdir, i=0; i<16 && dir[i] != ' '; i++)
      p[i] = dir[i];
    p[i] = NULL;

    asm (" lw 0,x'a80'");      /* if txpm turn off tsa biasing */
    asm (" camw 0,x'a80'");
    asm (" beq $+2w");
    asm (" svc 1,3");
#endif
}

