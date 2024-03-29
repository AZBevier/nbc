/*~!param.h*/
/* Name:  param.h Part No.: _______-____r
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

#ifndef PARAM_H
#define PARAM_H

#ident	"@(#)nbinclude:param.h	1.0"

/*
 * fundamental variables
 */

#define	MAXPID	30000		/* max process id */
#define	MAXUID	60000		/* max user id */
#define	MAXLINK	1000		/* max links */

#define	USIZE	3		/* size of user block (*2048 bytes) */

#define	CANBSIZ	256		/* max size of typewriter line	*/
#define	HZ	60		/* 100 ticks/second of the clock */

#define	NCARGS	768		/* # characters in exec arglist */
				/*   must be multiple of NBPW.  */

/*	The following define is here for temporary compatibility
**	and should be removed in the next release.  It gives a
**	value for the maximum number of open files per process.
**	However, this value is no longer a constant.  It is a
**	configurable parameter, NOFILES, specified in the kernel
**	master file and available in v.v_nofiles.  Programs which
**	include this header file and use the following value may
**	not operate correctly if the system has been configured
**	to a different value.
*/

#define	NOFILE	20

/*	The following represent the minimum and maximum values to
**	which the paramater NOFILES in the kernel master file may
**	be set.
*/

#define	NOFILES_MIN	 20
#define	NOFILES_MAX	100

/*	The following defines apply to the kernel virtual
**	address space.
*/

#define	SYSSEGSZ 1024	/* The size of the kernel segment	*/
			/* sysseg in pages.  The starting	*/
			/* address comes from the vuifile.	*/
#define	NS0SDE	0x120	/* Nbr of kernel segments in section 0.	*/
#define	NS1SDE	0x38	/* Nbr of kernel segments in section 1.	*/
#define	NS2SDE	0x0	/* Nbr of kernel segments in section 2.	*/
#define	NS3SDE	0x1	/* Nbr of kernel segments in section 3.	*/

/*	To avoid prefetch errors at the end of a region, it must
**	be padded with the following number of bytes.
*/

#define	PREFETCH	12

/*
 * priorities
 * should not be altered too much
 */

#define	PMASK	0177
#define	PCATCH	0400
#define	PNOSTOP	01000
#define	PSWP	0
#define	PINOD	10
#define	PRIBIO	20
#define	PZERO	25
#define PMEM	0
#define	NZERO	20
#define	PPIPE	26
#define	PWAIT	30
#define	PSLEP	39
#define	PUSER	60
#define	PIDLE	127

/*
 * fundamental constants of the implementation--
 * cannot be changed easily
 */

#define NBPS	0x20000		/* Number of bytes per segment */
#define	NBPW	sizeof(int)	/* number of bytes in an integer */
#define	NCPS	64		/* Number of clicks per segment */
#define	CPSSHIFT	6	/* LOG2(NCPS) if exact */
#define	NBPC	2048		/* Number of bytes per click */
#define	BPCSHIFT	11	/* LOG2(NBPC) if exact */
#define	NULL	0
#define	CMASK	0		/* default mask for file creation */
#define	CDLIMIT	(1L<<11)	/* default max write address */
#define	NODEV	(dev_t)(-1)
#define	NBPSCTR		768	/* Bytes per disk sector.	*/
#define SCTRSHFT	9	/* Shift for BPSECT.		*/

#define	lobyte(X)	(((unsigned char *)&X)[1])
#define	hibyte(X)	(((unsigned char *)&X)[0])
#define	loword(X)	(((ushort *)&X)[1])
#define	hiword(X)	(((ushort *)&X)[0])

/*
 *  Interrupt stack size in STKENT units
 */
#define QSTKSZ	1000
#define ISTKSZ	1000

#define	MAXSUSE	255

/* REMOTE -- whether machine is primary, secondary, or regular */
#define SYSNAME 9		/* # chars in system name */
#define PREMOTE 39

/*
 * Machine dependent constants for Concept.
 */
#define	NBPG	8192		/* bytes/page */
#define	PGOFSET	(NBPG-1)	/* byte offset into page */
#define	PGSHIFT	13		/* LOG2(NBPG) */

#define	CLSIZE		1
#define	CLSIZELOG2	0

#define	SSIZE	3		/* initial stack size/NBPG */
#define	SINCR	2		/* increment of stack/NBPG */
/* N.B. Concept architecture prevents from using SINCR */

#define	UPAGES	1		/* pages of u-area */

/*
 * Some macros for units conversion
 */
/* Core clicks (8192 bytes) to segments and vice versa */
#define	ctos(x)	(x)
#define	stoc(x)	(x)

/* Core clicks (8192 bytes) to disk blocks */
#define	ctod(x)	((x)<<3)
#define	dtoc(x)	((x)>>3)

/* Disk blocks to bytes */
#define	dtob(x)	((x)<<10)

/* clicks to bytes */
#define	ctob(x)	((x)<<13)

/* bytes to clicks */
#define	btoc(x)	((((unsigned)(x)+8191)>>13))

/* map block (8192-byte-page number) to address */
#define mtoa(x) ((x) << 13 & PSD0_PCMSK)

/*
 * Macros to decode processor status word.
 *
 *      SEL USERMODE macro takes pc (PSD0) argument.
 */
#define	USERMODE(psd0) ( \
((((int)(psd0)) & PSD0_PRV) == 0) || ((((int)(psd0)) & PSD0_PCMSK) >= SYSTOP))

/*
 * These are the same on Gould
 */
#define fuibyte		fubyte
#define suibyte		subyte
#define fuiword		fuword
#define suiword		suword
#define copyiin		copyin
#define copyiout	copyout

#define	DELAY(n)	{ register int N = (n); while (--N > 0); }

/*
 * Miscellaneous memory allocation defines.
 * Used for various device driver arrays and file
 * system cylinder group info.
 * Used by wmemall, zmemall, and wmemfree.
 */

#define	NMISCMAP	400

#define PAGESIZE	NBPG

/*  
 * Bit 0 in MSD 1 and following means to omit 
 * reloading the BPIX (MSD 0) Map Blocks.
 * In MSD 0 it means to suppress the loading of any Map Blocks.  
 */

#define SKIPBPIX	0x80000000

/*  
 * the current sizes (in words) of all SEL SCRATCHPAD Elements  
 */

#define SCR_SIZE 256
#define DVC_NBR 128
#define INT_NBR 112
#define TTB_SIZE 24
#define ITB_SIZE 128
#define SCREND_SIZE 16
#define NBR_SVCS 16
#define NBR_PROCS 32
#define NBR_MIDLS 256
#define NBR_BASEREGS 8
#define KSTAKNUM 320

/*  
 * The following, since it refers to an IOCL 
 * (which contains IOCD'S), is stated
 * in Doublewords rather than in Words  
 */

#define IOC_SIZE 16

/******************************************************************************
*
*  SEL 32/Series LOW CORE Layout:
*
* This file contains the actual addresses for the various 
* system elements which are located in low memory
* and are pointed to by the SCRATCHPAD.  
* These elements consist of:
*
*      The Trap Vector Table
*      The Interrupt Vector Table
*      The Memory Image of the SCRATCHPAD
*      The Class E IOCD List
*      The Master Process List 
*      The Map Image Descriptor List
*      The Base Register List (not a SCRATCHPAD-oriented value)
*      The Kernel Stack (not a SCRATCHPAD-oriented value)
*
******************************************************************************/

#define ITTBLADDR 0x0020	/* IPU Trap Table Base Address */
#define TTBLADDR 0x0080		/* CPU Trap Table Base Address */
#define ITBLADDR 0x0100		/* Interrupt Table Base Address */
#define SCRPADDR 0x0300		/* Memory image of scratchpad address */
#define IOCLADDR 0x0780		/* IOC List base address for class E i/o */
#define MPLADDR  0x0800		/* Master Process list address */
#define MIDLADDR 0x0900		/* (BPIX) Map image descriptor list address */

/* 
 * The Kernel Stack pointer initial value 
 * is at the high end of the stack, which then works backward,
 * hopefully not to go past the low end (at location 0B20)  
 */

#define KSTKADDR 0x1000

#endif	/* PARAM_H */
