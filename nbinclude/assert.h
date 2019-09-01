/*~!assert.h*/
/* Name:  assert.h Part No.: _______-____r
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

#ident	"@(#)nbinclude:assert.h	1.0"

#ifndef ASSERT_H
#define ASSERT_H

#ifdef NDEBUG
#define assert(EXP)
#else
extern void _assert();
#define assert(EXP) if (EXP) ; else _assert("EXP", __FILE__, __LINE__)
#endif
#endif
