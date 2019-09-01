/*~!dca.h*/
/* Name:  dca.h Part No.: _______-____r
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

#ident	"@(#)nbinclude:dca.h	1.0"

#ifndef DCA_H
#define DCA_H

#include <ioq.h>
#include <udt.h>

struct dca {
    unsigned	size;		/* dca size */
    unsigned	uadd:16;	/* device address */
    unsigned	notu1:16;	/* reserved */
    int *	chta;		/* cht address */
    int *	cdta;		/* cdt address */
    int *	udta;		/* udt address */
    struct ioq *ioqa;		/* ioq address */
    int		linc;		/* lost int count */
    int		sinc;		/* spurious int count */
    int		retc;		/* retry count */
    /* dca.flag */
    unsigned	flag:24;	/* flags */
/*    unsigned	ine:1;		/* int not expected */
/*    unsigned	hioi:1;		/* hio issued at li.xio */
/*    unsigned	hior:1;		/* hio needs to be reissued */
/*    unsigned	drs:1;		/* device rewinding or seeking */
/*    unsigned	snioq:1;	/* sense issued without an IOQ */
/*    unsigned	xiomt:1;	/* device is an xio mag tape */
/*    unsigned	rxsu:10;	/* reserved for common sub usage */
/*    unsigned	rddhu:8;	/* reserved for dev dep handler usage */
    unsigned	rcnt:8;		/* retry count this request */    
    int *	nudt;		/* current udt address for this request */
    int		wst1;		/* status word 1 */
    int		wst2;		/* status word 2 */
    int		resc;		/* number of reserves outstanding */
    int		tim0;		/* timeout value for opcode 0 */
    int		tim1;		/* timeout value for opcode 1 */
    int		tim2;		/* timeout value for opcode 2 */
    int		tim3;		/* timeout value for opcode 3 */
    int		tim4;		/* timeout value for opcode 4 */
    int		tim5;		/* timeout value for opcode 5 */
    int		tim6;		/* timeout value for opcode 6 */
    int		tim7;		/* timeout value for opcode 7 */
    int		tim8;		/* timeout value for opcode 8 */
    int		tim9;		/* timeout value for opcode 9 */
    int		tima;		/* timeout value for opcode a */
    int		timb;		/* timeout value for opcode b */
    int		timc;		/* timeout value for opcode c */
    int		timd;		/* timeout value for opcode d */
    int		time;		/* timeout value for opcode e */
    int		timf;		/* timeout value for opcode f */
    int		seni;		/* iocd sense status wd 1 */
    int		seni2;		/* iocd sense status wd 2 */
    int		sens;		/* sense buffer */
    int		wd33;		/* wd 33 */
    int		wd34;		/* wd 34 */
    struct udt *cudt;		/* companion udt */
};
#endif
