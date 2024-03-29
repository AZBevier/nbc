/*~!dirent.h*/
/* Name:  dirent.h Part No.: _______-____r
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

#ifndef DIRENT_H
#define DIRENT_H

#ident	"@(#)nbinclude:dirent.h	1.0"

/*
* A directory consists of some number of blocks of DIRBLKSIZ
* bytes, where DIRBLKSIZ is chosen such that it can be transferred
* to disk in a single atomic operation (e.g. 768 bytes on Gould machine).
*
* Each DIRBLKSIZ byte block contains twelve directory entry
* structures, which are of 64 bytes long.
* All names are maximum of 16 characters and blank filled.
* The maximum length of a name in a directory is MAXNAMLEN.
*
* The macro DIRENTSIZ(dp) gives the amount of space required to represent
* a directory entry.  Free space in a directory is represented by
* entries which have bit zero cleared in d_flags.
*/

#define DIRBLKSIZ 768
#define DIRBUF		768	/* buffer size for fs-indep. dirs */
#define MAXNAMLEN 16
#ifndef	DIRSIZ
#define	DIRSIZ	16		/* this is for UNIX compatibility */
#endif
#ifndef DIR_MAX
#define DIR_MAX 36		/* directory name storage */
#endif

struct dirent {
  char  d_name[MAXNAMLEN];      /* entry name blank filled */
  int   d_date;                 /* binary creation date */
  int   d_time;                 /* binary creation time */
  int   d_ino;                  /* inode number of rd for entry */
  short d_rdflg;                /* resource ID flags */
  short d_rtype;                /* resource type */
                                /* 01 - volume type */
                                /* 02 - resource descr descr */
                                /* 03 - descr map descr */
                                /* 04 - space map descr */
                                /* 05 - root dir descr */
                                /* 06 - system image descr */
                                /* 07 - bad block descr */
                                /* 08 - spool file descr */
                                /* 09 - extra seg def descr */
                                /* 10 - perm file */
                                /* 11 - perm dir */
                                /* 12 - temp file */
                                /* 13 - temp dir */
                                /* 14 - static mem part */
                                /* 15 - dynam mem part */
                                /* 16 - device descr */
                                /* 17 - rd for DMAP */
                                /* 18 - rd for SMAP */
  int   d_colct;                /* collision count */
  int   d_hshct;                /* hash count for entry */
  int   d_flags;                /* flags - bit zero set means active entry */
  int   d_diri;                 /* directory entry index */
  char  d_ownr[8];              /* owner name of entry creator */
  char  d_fill[8];              /* filler */
  };

/*
* The DIRENTSIZ macro gives the record length which will hold
* the directory entry.
*/

#undef DIRENTSIZ
#define DIRENTSIZ(dp) (sizeof (struct dirent))

/*
* Definitions for library routines operating on directories.
*/

typedef struct _dirdesc {
  int  dd_fd;           /* file descriptor used to read dir */
  long dd_loc;          /* current entry number */
  long dd_size;         /* directory size in bytes (DIRBLKSIZ) */
  char *dd_buf;		/* buffer to read directory into */
  char dd_dir[DIR_MAX];	/* directory name */
} DIR;			/* stream data from opendir() */

#ifndef NULL
#define NULL 0
#endif

extern struct dirent	*readdir ();       /* unix interface */
extern struct dirent	*readmdir ();      /* mpx interface */
extern DIR		*opendir();
extern long		telldir();
extern void		seekdir();
extern int		closedir();
extern void		rewinddir();

#endif
