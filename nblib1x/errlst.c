/*~!errlst.h*/
/* Name:  errlst.h Part No.: _______-____r
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

#ident	"@(#)nbclib:errcodes.h	1.0"

char	*sys_errlist[] = {
	"Error 0",
	"Not owner",
	"No such file or directory",
	"No such process",
	"Interrupted system call",
	"I/O error",
	"No such device or address",
	"Arg list too long",
	"Exec format error",
	"Bad file number",
	"No child processes",
	"No more processes",
	"Not enough space",
	"Permission denied",
	"Bad address",
	"Block device required",
	"Device busy",
	"File exists",
	"Cross-device link",
	"No such device",
	"Not a directory",
	"Is a directory",
	"Invalid argument",
	"File table overflow",
	"Too many open files",
	"Not a typewriter",
	"Text file busy",
	"File too large",
	"No space left on device",
	"Illegal seek",
	"Read-only file system",
	"Too many links",
	"Broken pipe",
	"Argument out of domain",
	"Result too large",
	"No message of desired type",
	"Identifier removed",
	"Channel number out of range",
	"Level 2 not synchronized",
	"Level 3 halted",
	"Level 3 reset",
	"Link number out of range",
	"Protocol driver not attached",
	"No CSI structure available",
	"Level 2 halted",
	"Deadlock situation detected/avoided",
	"No record locks available",
	"Error 47",
	"Error 48",
	"Error 49",
	"Bad exchange descriptor",		/* 50 */
	"Bad request descriptor",		/* 51 */
	"Message tables full",			/* 52 */
	"Anode table overflow",			/* 53 */
	"Bad request code",			/* 54 */
	"Invalid slot",				/* 55 */
	"File locking deadlock",		/* 56 */
	"Bad font file format",			/* 57 */
	"Error 58",
	"Error 59",
	"Not a stream device",			/* 60 */
	"No data available",
	"Timer expired",
	"Out of stream resources",
	"Machine is not on the network",
	"Package not installed",
	"Object is remote",
	"Link has been severed",
	"Advertise error",
	"Srmount error",
	"Communication error on send",		/* 70 */
	"Protocol error",
	"Error 72",
	"Error 73",
	"Multihop attempted",
	"Error 75",
	"Error 76",
	"Not a data message",			/* 77 */
	"Error 78",
	"Error 79",
	"Name not unique on network",
	"File descriptor in bad state",
	"Remote address changed",
	"Can not access a needed shared library",	/* 83 */
	"Accessing a corrupted shared library",
	".lib section in a.out corrupted",
	"Attempting to link in more shared libraries than system limit",
	"Can not exec a shared library directly",
	"Error 88",
	"Error 89",
	"Error 90",
	"Error 91",
	"Error 92",
	"Error 93",
	"Error 94",
	"Error 95",
	"Error 96",
	"Error 97",
	"Error 98",
	"Error 99",

/* following are the MPX errors, starting at errno == 100 */

    "unused error code",
    "attempt to open terminal or SLO in update mode",
    "unable to create file",
    "close error.",
    "assign error.",
    "no FAT for resource",
    "open error.",
    "pathname too long",
    "pathname too short",
    "PNB creation failure.",
    "attempt to write to unopened stream",
    "attempt to write to readonly stream",
    "attempt to read from unopened stream",
    "attempt to read from writeonly stream",
    "bad seek mode",
    "attempt to seek into unopened stream",
    "attempt to seek to illegal pos on blocked stream",
    "MPX read error",
    "MPX EOM on read",
    "MPX EOF on read",
    "MPX write error",
    "MPX EOF on write",
    "MPX EOM on write",
    "EOF already set on this stream",
    "attempt to seek to before BOF",
    "parse or assign error from open",
    "parse or assign error from creat",
    "bad file descriptor",
    "unable to get buffer for file descriptor",
    "unable to delete file",
    "append or write mode specified with direct access",
    "record length cannot be specified with sequential access",
    "record length needed with direct access",
    "attempt to create already existent file",
    "pathname reconstruction error.",
    "sequential files must be blocked",
    "direct access files must be unblocked",
    "inquire error.",
    "unopened stream",
    "bad address in signal",
    "rename error.",

};
int	sys_nerr = { sizeof(sys_errlist)/sizeof(sys_errlist[0]) };

