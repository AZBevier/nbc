/*~!stat.h*/
/* Name:  stat.h Part No.: _______-____r
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

#ifndef STAT_H
#define STAT_H

#ident	"@(#)nbinclude:stat.h	1.0"

#include <types.h>

/*
 * stat structure, used by stat(2) and fstat(2)
 */

struct	stat {
	dev_t	st_dev;		/* ID of device containing the directory entry*/
/*	ushort	st_ino;		/* inode number */
	long	st_ino;		/* inode number */
	ushort	st_mode;	/* file mode */
	short	st_nlink;	/* number of links */
	ushort	st_uid;		/* user ID of the file's owner */
	ushort	st_gid;		/* group ID of the file's group */
	dev_t	st_rdev;	/* ID of device (block and char devices only) */
	off_t	st_size;	/* file size in bytes */
	time_t	st_atime;	/* time of last access */
	time_t	st_mtime;	/* time of last data modification */
	time_t	st_ctime;	/* time of last file status change */
	long	st_blksize;	/* size of the disk blocks */
	long	st_blocks;	/* number of disk blocks */
};

#define	S_IFMT	0170000		/* type of file */
#define	S_IFIFO	0010000		/* fifo */
#define	S_IFCHR	0020000		/* character special */
#define	S_IFDIR	0040000		/* directory */
#define	S_IFBLK	0060000		/* block special */
#define	S_IFSOCK 0140000	/* socket */
#define	S_IFREG	0100000		/* regular */

#define	S_ISUID	04000		/* set user id on execution */
#define	S_ISGID	02000		/* set group id on execution */
#define	S_ISVTX	01000		/* save swapped text even after use */

#define	S_IREAD	0000400		/* read permission, owner */
#define	S_IWRITE 0000200	/* write permission, owner */
#define	S_IEXEC	0000100		/* execute/search permission, owner */

#define	S_ENFMT	S_ISGID		/* record locking enforcement flag */

#define	S_IRWXU	00700		/* read, write, execute: owner */
#define	S_IRUSR	00400		/* read permission: owner */
#define	S_IWUSR	00200		/* write permission: owner */
#define	S_IXUSR	00100		/* execute permission: owner */
#define	S_IRWXG	00070		/* read, write, execute: group */
#define	S_IRGRP	00040		/* read permission: group */
#define	S_IWGRP	00020		/* write permission: group */
#define	S_IXGRP	00010		/* execute permission: group */
#define	S_IRWXO	00007		/* read, write, execute: other */
#define	S_IROTH	00004		/* read permission: other */
#define	S_IWOTH	00002		/* write permission: other */
#define	S_IXOTH	00001		/* execute permission: other */

#endif
