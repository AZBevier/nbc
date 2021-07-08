/*~!types.h*/
/* Name:  types.h Part No.: _______-____r
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

#ident	"@(#)nbinclude:types.h	1.0"

#ifndef TYPES_H
#define TYPES_H

typedef	struct { int r[1]; } *	physadr;
typedef	long		daddr_t;	/* <disk address> type */
typedef	char *		caddr_t;	/* ?<core address> type */
typedef	char	int8;
typedef	short	int16;
typedef	int	    int32;
typedef	long	int64;
typedef	unsigned char	uchar;
typedef	unsigned char	uint8;
typedef	unsigned short	ushort;
typedef	unsigned short	uint16;
typedef	unsigned int	uint;
typedef	unsigned int	uint32;
typedef	unsigned long	ulong;
typedef	unsigned long	uint64;
typedef	ushort		ino_t;		/* <inode> type */
typedef	short		cnt_t;		/* ?<count> type */
typedef	long		time_t;		/* <time> type */
typedef	int		label_t[10];
typedef	short		dev_t;		/* <old device number> type */
typedef	long		off_t;		/* ?<offset> type */
typedef	long		paddr_t;	/* <physical address> type */
typedef	int		key_t;		/* IPC key type */
typedef	unsigned char	use_t;		/* use count for swap.  */
typedef	short		sysid_t;
typedef	short		index_t;
typedef	short		lock_t;		/* lock work for busy wait */

/*typedef	unsigned int	size_t;*/	/* len param for string funcs */
#ifndef size_t
typedef	unsigned long	size_t;		/* len param for string funcs */
#endif

#endif
