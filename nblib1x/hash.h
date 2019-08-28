/*~!hash.h*/
/* Name:  hash.h Part No.: _______-____r
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

#ident	"@(#)nbclib:hash.h	1.1"

#ifndef HASH_H
#define HASH_H

typedef	struct T_NODE {
	struct	T_NODE	*L, *R;		/* pointers to children		*/
	short	deleted;		/* TRUE-deleted; FALSE-not del.	*/
	short	balance_factor;		/* balance factor;		*/
	int	*data;			/* pointer to data;		*/
}	T_NODE;

typedef	struct T_HEAD {
	struct	T_NODE	*head;		/* pointers to children		*/
	short	height;			/* height of the tree		*/
	short	numnodes;		/* number of nodes in the tree	*/
	int	(*compare)();		/* local comparison routine	*/
}	T_HEAD;

typedef	struct	H_ENTRY {
	struct	H_ENTRY	*next;		/* chain link to next member	*/
	int	*data;
}	H_ENTRY;

typedef	struct	H_HEAD {
	struct	H_ENTRY	*head;		/* pointer to the table		*/
	short	numentries;		/* number of active entries	*/
	int	(*compare)();		/* local comparison routine	*/
	unsigned (*getkey)();		/* local key extraction routine	*/
	unsigned m;			/* size of the table		*/
}	H_HEAD;
#endif /* HASH_H */
