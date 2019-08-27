/*~!mpxsvc.h*/
/* Name:  mpxsvc.h Part No.: _______-____r
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

#ifndef MPXSVC_H
#define MPXSVC_H

#ident	"@(#)nbinclude:mpxsvc.h	1.0"

/*
 *  MPX svc assignments
 */

#define M_ABORT         mpxsvc(0x1057,reg,reg)
#define M_ASSN          mpxsvc(0x2052,reg,reg)
#define M_BACK          mpxsvc(0x1035,reg,reg)
#define M_BATCH         mpxsvc(0x2055,reg,reg)
#define M_BORT          mpxsvc(0x1056,reg,reg)
#define M_CONBAH        mpxsvc(0x102b,reg,reg)
#define M_CREATE        mpxsvc(0x2020,reg,reg)
#define M_DEASSN        mpxsvc(0x2053,reg,reg)
#define M_DELETER       mpxsvc(0x2024,reg,reg)
#define M_DELTSK        mpxsvc(0x105a,reg,reg)
#define M_DEVID         mpxsvc(0x1014,reg,reg)
#define M_EXIT          mpxsvc(0x1055,reg,reg)
#define M_EXTENDFILE    mpxsvc(0x2025,reg,reg)
#define M_FREMEMBYTES   mpxsvc(0x204c,reg,reg)
#define M_FWRD          mpxsvc(0x1034,reg,reg)
#define M_GETBLOCKS     mpxsvc(0x204b,reg,reg)
#define M_GETMEMBYTES   mpxsvc(0x204b,reg,reg)
#define M_GETTIME       mpxsvc(0x2050,reg,reg)
#define M_GRUNP         mpxsvc(0x107b,reg,reg)
#define M_INCLUDE       mpxsvc(0x2040,reg,reg)
#define M_INQUIRER      mpxsvc(0x2048,reg,reg)
#define M_LOC           mpxsvc(0x202c,reg,reg)
#define M_LOGR          mpxsvc(0x2029,reg,reg)
#define M_MOD           mpxsvc(0x202a,reg,reg)
#define M_MODU          mpxsvc(0x2031,reg,reg)
#define M_MYID          mpxsvc(0x1064,reg,reg)
#define M_OPENR         mpxsvc(0x2042,reg,reg)
#define M_PNAM          mpxsvc(0x202f,reg,reg)
#define M_PNAMB         mpxsvc(0x202e,reg,reg)
#define M_READ          mpxsvc(0x1031,reg,reg)
#define M_READD         mpxsvc(0x202c,reg,reg)
#define M_RENAME        mpxsvc(0x202d,reg,reg)
#define M_REWIND        mpxsvc(0x1037,reg,reg)
#define M_REWRIT        mpxsvc(0x202b,reg,reg)
#define M_REWRTU        mpxsvc(0x2032,reg,reg)
#define M_SRUNR         mpxsvc(0x106d,reg,reg)
#define M_SUAR          mpxsvc(0x1060,reg,reg)
#define M_TSCAN         mpxsvc(0x105b,reg,reg)
#define M_TYPE          mpxsvc(0x103f,reg,reg)
#define M_WEOF          mpxsvc(0x1038,reg,reg)
#define M_WRIT          mpxsvc(0x1032,reg,reg)
#define M_XRUNR         mpxsvc(0x107d,reg,reg)

#endif
