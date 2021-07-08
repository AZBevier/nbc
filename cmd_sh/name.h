/*~!name.h*/
/* Name:  name.h Part No.: _______-____r
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

#ident	"$Id: name.h,v 1.2 1995/04/04 22:39:21 jbev Exp $"

/*	$Log $
 */

#ifndef NAME_H
#define NAME_H

#define	N_ENVCHG 0020
#define N_RDONLY 0010
#define N_EXPORT 0004
#define N_ENVNAM 0002
#define N_FUNCTN 0001

#define N_DEFAULT 0

struct namnod {
    struct namnod *namlft;
    struct namnod *namrgt;
    char *namid;
    char *namval;
    char *namenv;
    int namflg;
};

#endif /*NAME_H*/
