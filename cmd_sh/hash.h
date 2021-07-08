/*~!hash.h*/
/* Name:  hash.h Part No.: _______-____r
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

#ident	"$Id: hash.h,v 1.3 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#ifndef HASH_H
#define HASH_H

#define	HASHZAP		0x03FF
#define	CDMARK		0x8000

#define	NOTFOUND	0x0000
#define	BUILTIN		0x0100
#define	FUNCTION	0x0200
#define	COMMAND		0x0400
#define	REL_COMMAND	0x0800
#define	PATH_COMMAND	0x1000
#define	DOT_COMMAND	0x8800		/* CDMARK | REL_COMMAND */

#define	hashtype(x)	(x & 0x1F00)
#define	hashdata(x)	(x & 0x00FF)


typedef struct entry {
    char *key;
    short data;
    char hits;
    char cost;
    struct entry *next;
} ENTRY;

extern ENTRY	*hfind();
extern ENTRY	*henter();
/*extern void hcreate();*/

#endif /*HASH_H*/
