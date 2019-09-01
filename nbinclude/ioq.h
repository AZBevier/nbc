/*~!ioq.h*/
/* Name:  ioq.h Part No.: _______-____r
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

#ifndef IOQ_H
#define IOQ_H

#ident	"@(#)nbinclude:ioq.h	1.0"

struct ioq {
    struct ioq *sfa;	/* string forward to next ioq */
    struct ioq *sba;	/* string back */
    unsigned pri:8;	/* que priority */
    unsigned type:8;	/* ioq type */
    unsigned chno:8;	/* channlel number */
    unsigned subai:8;	/* subaddres */
    unsigned rtn;	/* reserved */
    unsigned psd;	/* psd1 of task interrup routine */
    unsigned psd2;	/* psd2 of task interrupt routine */
    unsigned stat:8;	/* status of ioq */
    unsigned fcba:24;	/* address of ioq */
    unsigned prgn:8;	/* program number */
    unsigned cdta:24;	/* cdt address */
    unsigned fct1b:8;	/* to get at the first 8 bits */
    unsigned fct1:24;	/* the rest  */
    unsigned fct2;	/* function word 2 */
    int      fct3;	/* function word 3 */
    unsigned fct4;	/* function word 4 */
    unsigned flgs;	/* flags */
    unsigned fata;	/* fat address */
    unsigned utrn:16;	/* the number of bytes transfered */
    unsigned wosb:16;	/* the number of words in the os buffer*/
    unsigned fbuf;	/* user buffer address */
    unsigned tbuf;	/* os buffer address */
    unsigned iost;	/* status word 1 */
    unsigned ist1;	/* status word 2 */
    unsigned ist2;	/* status word 3 */
    unsigned udta;	/* udt address */
    unsigned cont;	/* info from word 2 of fcb */
    unsigned dcaai;	/* address of dca */
    unsigned mode:8;	/* mode bits */
    unsigned psav:8;	/* queue prio tem storage */
    unsigned xtra:16;	/* number of extra words in ioq */
    unsigned inop;	/* error processing addres */
    unsigned iocd;	/* addres of iocd list */
};
#endif /* IOQ_H */
