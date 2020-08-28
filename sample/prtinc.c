/*~!prtinc.c*/
/* Name:  prtinc.c Part No.: _______-____r
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

#ident	"@(#)sample:prtinc.c	1.0"

#include <stdio.h>
#include <sys/types.h>
#include <mosde.h>
#include <param.h>
#include <cdots.h>
#include <smt.h>

#include <sys/errno.h>

/* address of shared memory table */
#define SMTP (*(struct smt **)C_SMTA)

/* smt size in bytes */
#define SMTS (*(char *)C_SMTS)
#define SMTN (*(char *)C_SMTN)
static struct smt* smtptr;	/* smt pointer */
static int  partsize;		/* size of partition in bytes */
static int *paddr;		/* partition address */
static int estat;
int * prtincl();

/* Include a memory partition into our program.
 * return size.  Starting address in addr.
 */

unsigned long
prtinc(addr)
int *addr;
{
#ifdef MPX1X
    /* on MPX 1X, we must reserve malloc space before including
     * our shared partition, else it will not be contiguous
     * with the stack, YUCK!!!
     */
    free( malloc (0x8000));	/* get and free space */
#endif
    /* now include the partition */
    /* address is returned, partsize will have size in bytes */
    if ((int)(paddr = prtincl("@system(system)shmemprt", "rw")) < 0) {
        printf ("Cannot include SHMEMPRT, status = %d\n", estat);
        exit (0);
    }
    *addr = (int)paddr;	/* return partition address */
    return partsize;	/* and size in bytes */
}

char * rtdnp;
int rtdpp;

#ifdef MPX1X
static int errtn;
static int reg0, reg1, reg2, reg3, reg4, reg5, reg6, reg7;
#endif

#ifdef MPX1X
#include <finfo.h>
struct finfo *pn2fib();
#endif

/* routine to include a partition */
int * prtincl(pname, access)
char * pname;
char * access;
{
    int     reg[8];
    int     cnp[6];
    char    path[64];
    int     i;
#ifdef MPX1X
    struct finfo * foo;		/* file info block pointer */
#endif

    if (pname == 0 || *pname == 0) {
    	errno = ENOENT;        /* set file not found error */
    	return((int *)(-1)); /* error return value */
    }
    strcpy(path, pname);
    unix2mpx(path);

    cnp[0] = 0;		/* wait for resource */
    cnp[1] = 0;         /* no error return address */
    cnp[2] = 0;         /* assume read only */
    cnp[3] = 0;
    cnp[4] = 0;
    cnp[5] = 0;

    while (*access) {
        switch (*access++) {

        default:
            continue;

        case 'W':
        case 'w':
            cnp[2] |= 0x80000000;       /* set read/write access */
            continue;
        }
    }

#ifdef MPX1X
    if ((foo = pn2fib(path)) == NULL) {
      errno = ENOENT;			/* set file not found error */
      return((int *)(-1));		/* error return value */
    }

    reg2 = foo->username[0];	  	/* first part of ownername */
    reg3 = foo->username[1];		/* second part of ownername */
    reg6 = foo->filename[0];		/* first part of filename */
    reg7 = foo->filename[1];		/* second part of filename */
    reg4 = 0;				/* no password */
    reg5 = 0;
    reg1 = 0;				/* O.K. return value */
    asm (" la r0,altret");		/* set error ret addr */
    asm (" stw r0,_errtn");		/* set error return address */
    reg0 = errtn | cnp[2];		/* set addr and access */
    asm (" trr r3,r1");			/* save stack pointer */
    asm (" lw r0,_reg0");		/* load the reg */
    asm (" lw r2,_reg2");		/* load the reg */
    asm (" lw r3,_reg3");		/* load the reg */
    asm (" lw r4,_reg4");		/* load the reg */
    asm (" lw r5,_reg5");		/* load the reg */
    asm (" lw r6,_reg6");		/* load the reg */
    asm (" lw r7,_reg7");		/* load the reg */
    asm (" svc 1,x'72'");		/* M.INCL */
    asm (" li r6,0");			/* o.k. return */
    asm (" bu altmrg");
    asm ("altret li r6,-1");		/* set error code */
    asm ("altmrg stw r6,_reg1");	/* save error code */
    asm (" stw r3,_reg3");		/* save error code */
    asm (" trr r1,r3");			/* restore stack pointer */
    if (reg1 == -1) {			/* see if error */
    	errno = ENOENT;			/* set part not found error */
    	return((int *)(-1));		/* error return value */
    }
    reg[3] = reg3;
    /* here we need to search the SMT and find the SMT entry address */
    /* From there, we can get the SMT size */
    for (i = 0; i < (SMTN); i++) {
      smtptr = (struct smt *)((int)(SMTP) + ((int)(SMTS) * i));
      if ((smtptr->name[0] == foo->filename[0]) &&
        (smtptr->name[1] == foo->filename[1]))
        break;		/* we found it */
    }

#else

    reg[1] = (int)path;                 /* get pnv */
    reg[1] |= (strlen(path) << 24);     /* get pnv */
    reg[4] = 0;                         /* default ownername */
    reg[5] = 0;
    reg[7] = (int)cnp;                  /* cnp address */
    mpxsvc (0x2040, reg, reg);          /* m.include service */
    if ((estat = (cnp[2] & 0xffff)) != 0) {
    	errno = ENOENT;			/* set part not found error */
    	return((int *)(-1));		/* error return value */
    }

    /* get partition size */
    smtptr = (struct smt *)((int)(SMTP) +
      ((int)(SMTS) * ((reg[5] >> 24)-1)));

#endif
    /* get size of partition in bytes */
    /* each protection page is 512 words or 2048 bytes */
    partsize = smtptr->ptot * 2048;
#ifdef JUNK
    printf ("IPartition start address: %x\n", reg[3]);
    printf ("IPartition allocation index: %x\n", reg[5]);
    printf ("IPartition address: %x\n", (int)smtptr);
    printf ("IPartition size in bytes: %x\n", partsize);
#endif
    return((int *)reg[3]);              /* return starting address */
}

