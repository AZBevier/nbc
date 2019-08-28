/*~!setuid.c*/
/* Name:  setuid.c Part No.: _______-____r
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

#ident	"@(#)nbclib:setuid.c	1.0"

int setuid(uid)		/* set user id */
int uid;
{
	return (0);	/* return root id */
}

int getuid(gid)		/* get group id */
int gid;
{
	return (0);	/* return root group */
}

int setgid(uid)		/* set user id */
int uid;
{
	return (0);	/* return root id */
}

int getgid(gid)		/* get group id */
int gid;
{
	return (0);	/* return root group */
}

int geteuid(gid)	/* get effective group id */
int gid;
{
	return (0);	/* return root group */
}

int getegid(gid)		/* set group id */
int gid;
{
	return (0);	/* return root group */
}

