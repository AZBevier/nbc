/*~!errno.h*/
/* Name:  errno.h Part No.: _______-____r
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

#ifndef ERRNO_H
#define ERRNO_H

#ident	"@(#)nbinclude:errno.h	1.0"

#ifdef _ERRNODEF
int errno;   /* holds the UNIX error code */
int mpxerr;  /* this holds an MPX specific error code in some cases */
#undef _ERRNODEF
#else
extern int errno;
extern int mpxerr;
#endif

/*
* Error codes                MPX C version
*/

#define  E000 0         /* not used(couldn't tell it from good status) */
#define  E001 101       /* attempt to open terminal or SLO in update mode */
#define  E002 102       /* unable to create. see mpxerr */
#define  E003 103       /* close error        "    "    */
#define  E004 104       /* assign error       "    "    */
#define  E005 105       /* no FAT for resource */
#define  E006 106       /* open error        see mpxerr */
#define  E007 107       /* pathname too long */
#define  E008 108       /* pathname too short */
#define  E009 109       /* PNB creation failure. see mpxerr */
#define  E010 110       /* attempt to write to unopened stream */
#define  E011 111       /* attempt to write to readonly stream */
#define  E012 112       /* attempt to read from unopened stream */
#define  E013 113       /* attempt to read from writeonly stream */
#define  E014 114       /* bad seek mode */
#define  E015 115       /* attempt to seek into unopened stream */
#define  E016 116       /* attempt to seek to illegal pos on blocked stream */
#define  E017 117       /* MPX read error */
#define  E018 118       /* MPX EOM on read */
#define  E019 119       /* MPX EOF on read */
#define  E020 120       /* MPX write error */
#define  E021 121       /* MPX EOF on write */
#define  E022 122       /* MPX EOM on write */
#define  E023 123       /* EOF already set on this stream */
#define  E024 124       /* attempt to seek to before BOF */
#define  E025 125       /* parse or assign error from open */
#define  E026 126       /* parse or assign error from creat */
#define  E027 127       /* bad file descriptor */
#define  E028 128       /* unable to get memory for I/O buffer */
#define  E029 129       /* unable to delete file */
#define  E030 130       /* append or write mode specified with direct access */
#define  E031 131       /* record length cannot be specified with seq access */
#define  E032 132       /* record length needed with direct access */
#define  E033 133       /* attempt to create already existent file */
#define  E034 134       /* pathname reconstruction error.  see mpxerr. */
#define  E035 135       /* sequential files must be blocked */
#define  E036 136       /* direct access files must be unblocked */
#define  E037 137       /* inquire error.  see mpxerr. */
#define  E038 138       /* unopened stream. */
#define  E039 139       /* read descriptor error */
#define  E040 140       /* bad address in signal */
#define  E041 141       /* rename error.  see mpxerr. */

#define  E042 142
#define  E043 143
#define  E044 144
#define  E045 145
#define  E046 146
#define  E047 147
#define  E048 148
#define  E049 149

extern char * sys_errlist[];
void perror ();

/*
 * Error codes UNIX SYSTEM V VERSION
 */

#define	EPERM	1	/* Not super-user			*/
#define	ENOENT	2	/* No such file or directory		*/
#define	ESRCH	3	/* No such process			*/
#define	EINTR	4	/* interrupted system call		*/
#define	EIO	5	/* I/O error				*/
#define	ENXIO	6	/* No such device or address		*/
#define	E2BIG	7	/* Arg list too long			*/
#define	ENOEXEC	8	/* Exec format error			*/
#define	EBADF	9	/* Bad file number			*/
#define	ECHILD	10	/* No children				*/
#define	EAGAIN	11	/* No more processes			*/
#define	ENOMEM	12	/* Not enough core			*/
#define	EACCES	13	/* Permission denied			*/
#define	EFAULT	14	/* Bad address				*/
#define	ENOTBLK	15	/* Block device required		*/
#define	EBUSY	16	/* Mount device busy			*/
#define	EEXIST	17	/* File exists				*/
#define	EXDEV	18	/* Cross-device link			*/
#define	ENODEV	19	/* No such device			*/
#define	ENOTDIR	20	/* Not a directory			*/
#define	EISDIR	21	/* Is a directory			*/
#define	EINVAL	22	/* Invalid argument			*/
#define	ENFILE	23	/* File table overflow			*/
#define	EMFILE	24	/* Too many open files			*/
#define	ENOTTY	25	/* Not a typewriter			*/
#define	ETXTBSY	26	/* Text file busy			*/
#define	EFBIG	27	/* File too large			*/
#define	ENOSPC	28	/* No space left on device		*/
#define	ESPIPE	29	/* Illegal seek				*/
#define	EROFS	30	/* Read only file system		*/
#define	EMLINK	31	/* Too many links			*/
#define	EPIPE	32	/* Broken pipe				*/

#define	EDOM	33	/* Math arg out of domain of func	*/
#define	ERANGE	34	/* Math result not representable	*/
#define	ENOMSG	35	/* No message of desired type		*/
#define	EIDRM	36	/* Identifier removed			*/
#define	ECHRNG	37	/* Channel number out of range		*/
#define	EL2NSYNC 38	/* Level 2 not synchronized		*/
#define	EL3HLT	39	/* Level 3 halted			*/
#define	EL3RST	40	/* Level 3 reset			*/
#define	ELNRNG	41	/* Link number out of range		*/
#define	EUNATCH 42	/* Protocol driver not attached		*/
#define	ENOCSI	43	/* No CSI structure available		*/
#define	EL2HLT	44	/* Level 2 halted			*/
#define	EDEADLK	45	/* Deadlock condition.			*/
#define	ENOLCK	46	/* No record locks available.		*/

/* TCP/IP Error Returns */
#define EBADE	50	/* invalid exchange			*/
#define EBADR	51	/* invalid request descriptor		*/
#define EXFULL	52	/* exchange full			*/
#define ENOANO	53	/* no anode				*/
#define EBADRQC	54	/* invalid request code			*/
#define EBADSLT	55	/* invalid slot				*/
#define EDEADLOCK 56	/* file locking deadlock error		*/

#define EBFONT	57	/* bad font file fmt			*/

/* stream problems */
#define ENOSTR	60	/* Device not a stream			*/
#define ENODATA	61	/* no data (for no delay io)		*/
#define ETIME	62	/* timer expired			*/
#define ENOSR	63	/* out of streams resources		*/

#define ENONET	64	/* Machine is not on the network	*/
#define ENOPKG	65	/* Package not installed                */
#define EREMOTE	66	/* The object is remote			*/
#define ENOLINK	67	/* the link has been severed */
#define EADV	68	/* advertise error */
#define ESRMNT	69	/* srmount error */

#define	ECOMM	70	/* Communication error on send		*/
#define EPROTO	71	/* Protocol error			*/
#define	EMULTIHOP 74	/* multihop attempted */
#define	EDOTDOT 76	/* Cross mount point (not really error)*/
#define EBADMSG 77	/* trying to read unreadable message	*/

#define ENOTUNIQ 80	/* given log. name not unique */
#define EBADFD	 81	/* f.d. invalid for this operation */
#define EREMCHG	 82	/* Remote address changed */

/* shared library problems */
#define ELIBACC	83	/* Can't access a needed shared lib.	*/
#define ELIBBAD	84	/* Accessing a corrupted shared lib.	*/
#define ELIBSCN	85	/* .lib section in a.out corrupted.	*/
#define ELIBMAX	86	/* Attempting to link in too many libs.	*/
#define ELIBEXEC	87	/* Attempting to exec a shared library.	*/

#endif
