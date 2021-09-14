/*~!mkdir.c*/
/* Name:  mkdir.c Part No.: _______-____r
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

#ident	"@(#)nbclib:mkdir.c	1.1"

/*
 * create a directory with the specified attributes
 */
mkdir(path, mode)
char *path;
int mode;
{
return (creatd(path,mode));
}

/*
 * delete a directory from the system
 */
rmdir(path)
char *path;
{
return (unlink(path));
}
