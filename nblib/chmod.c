/*~!chmod.c*/
/* Name:  chmod.c Part No.: _______-____r
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

#ident	"@(#)nbclib:chmod.c	1.1"

#include <errno.h>
#include <limits.h>

/*
 * Set new file access modes
 */

/* place for storing default access rights */
extern unsigned int fileacc[];

/* do not move this definition, must be 2w bounded */
asm (" bound 1d");
static int rdbuf[192];		/* resource descriptor buffer 2w bounded */

chmod(file, mode)  	/* entry */
char *file;
int mode;
{
    int reg[8];
    char path[PATH_MAX];
    int owner, group, other;
    char own, pro, oth;

    if (!(file != 0 && *file != 0)) {
      errno = ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }

    strcpy(path, file);		/* make a local copy */
    unix2mpx(path);		/* convert to MPX path */
    
    /* now read the file rd for modification */
    reg[1] = (int)path;		/* get pnv */
    reg[1] |= (strlen(path) << 24);	/* get pnv */
    reg[6] = (int)rdbuf;	/* rd buffer address */
    reg[7] = 0;			/* no cnp */
    mpxsvc (0x202a, reg, reg);	/* m.mod service */
    if (reg[7] != 0) {
      errno = ENOENT;		/* set file not found error */
      return(-1);		/* error return value */
    }

    /* modify the rd */
    /* set defaults in rcb */
    owner = ((fileacc[0] << 26) | ((fileacc[0] & 1)?0x400000:0));
    group = ((fileacc[1] << 26) | ((fileacc[1] & 1)?0x400000:0));
    other = ((fileacc[2] << 26) | ((fileacc[2] & 1)?0x400000:0));

    /* MPX access rights R W M U A D done here */
    /* UNIX are R W X */
    /* if mode & ~0x1ff is not zero, them MPX, else */
    /* assume UNIX flags given and translate to MPX */

    /* only modify if a mode is specified, else use default */
    if (mode) {
    	if((mode & ~0x1ff) == 0) {
    	    /* simulate UNIX */
    	    if((oth = (mode & 6) << 3) & 0x10)
    		oth |= 0x3f;	/* if write, allow RWMUAD */
    	    if((pro = ((mode >> 3) & 6) << 3) & 0x10)
    		pro |= 0x3f;	/* if write, allow RWMUAD */
    	    if((own = ((mode >> 6) & 7) << 3) & 0x10)
    		own |= 0x3f;	/* if write, allow RWMUAD */
	    own |= 0x21;	/* allow owner read/delete access */
    	} else {
    	    oth = mode & 63;
    	    pro = (mode >> 8) & 63;
    	    own = (mode >> 16) & 63;
	    own |= 0x21;	/* allow owner read/delete access */
    	}
    	other = (((unsigned)(oth & 62)) << 26);
    	if(oth & 1)		/* set proper delete bit */
    	    other |= 0x400000;
    	group = (((unsigned)(pro & 62)) << 26);
    	if(pro & 1)		/* set proper delete bit */
    	    group |= 0x400000;
    	owner = (((unsigned)(own & 62)) << 26);
    	if(own & 1)		/* set proper delete bit */
    	    owner |= 0x400000;
    }

    /* change the rd */
    rdbuf[30] &= ~0xf8400000;	/* leave the other bits */
    rdbuf[30] |= owner;		/* set new access */
    rdbuf[31] &= ~0xf8400000;	/* leave the other bits */
    rdbuf[31] |= group;		/* set new access */
    rdbuf[32] &= ~0xf8400000;	/* leave the other bits */
    rdbuf[32] |= other;		/* set new access */

    /* now write the file rd after modification */
    reg[6] = (int)rdbuf;	/* rd buffer address */
    reg[7] = 0;			/* no cnp */
    mpxsvc (0x202b, reg, reg);	/* m.rewrit service */
    if (reg[7] != 0) {
      errno = EPERM;		/* set access error */
      return(-1);		/* error return value */
    }
    return (0);			/* return o.k. */
}

