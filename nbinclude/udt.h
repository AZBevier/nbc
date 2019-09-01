/*~!udt.h*/
/* Name:  udt.h Part No.: _______-____r
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

#ident	"@(#)nbinclude:udt.h	1.2"

#ifndef UDT_H
#define UDT_H

#include <ioq.h>

struct udt {
    unsigned udti:16;	/* the udt index */
    unsigned cdti:16;	/* the cdt index */

    /* udt.stat */
    unsigned onli:1;	/* if set online */
    unsigned dpdc:1;	/* if set dual ported xio disc */
    unsigned aloc:1;	/* set if allocated */
    unsigned use:1;	/* set if in use */
    unsigned noal:1;	/* set if sys out unable to allocate */
    unsigned shr:1;	/* set if a sharable device */
    unsigned prem:1;	/* set if premounted */
    unsigned tsm:1;	/* set if a tsm device */
    unsigned dtc:8;	/* device type code */
    unsigned chan:8;	/* device channel */
    unsigned suba:8;	/* device subaddres */

    unsigned nu1:8;	/* reserved */
    unsigned dqea:24;	/* dqe address */

    unsigned pchn:8;	/* physical channel */
    unsigned psub:8;	/* logical address */
    unsigned chpl:8;	/* number of characters per line */
    unsigned line:8;	/* number of lines per page */

    /* udt.flgs */
    unsigned fcls:1;	/* Extended I/O device */
    unsigned iout:1;	/* I/O outstanding */
    unsigned rmdv:1;	/* Removable disc pack */
    unsigned logo:1;	/* Terminal user logged on */
    unsigned bslo:1;	/* Auto selectable for batch SLO */
    unsigned bsbo:1;	/* Auto selectable for batch SBO */
    unsigned rslo:1;	/* Auto selectable for realtime SLO */
    unsigned rsbo:1;	/* Auto selectable for realtime SBO */
    unsigned spt:8;	/* sectors per track or line count */
    unsigned mbx:16;	/* max byte transfer */

    unsigned secs;	/* sectors on the disk */

    unsigned ssiz:16;	/* sector size, or tab settint */
    unsigned nhds:16;	/* sector size, or tab setting */

    unsigned sern;	/* serial number if tape*/

    unsigned ptov;	/* time out value */

    int *dcaa;		/* dca address */

    /* udt.bit2 */
    unsigned dial:1;	/* port is private, else switched */
    unsigned modm:1;	/* connected to a modem */
    unsigned grfc:1;	/* graphic port */
    unsigned fdux:1;	/* full duplex port */
    unsigned mdra:1;	/* multi drop port */
    unsigned vol:1;	/* volume mounted on device */
    unsigned echo:1;	/* echo by computer */
    unsigned dead:1;	/* device has failed */
    unsigned cac:1;	/* cache device */
    unsigned nrap:1;	/* inhibit auto line wrap */
    unsigned feop:1;	/* initial form feed inhibited */
    unsigned qitd:1;	/* quarter inch cart tape */
    unsigned rxon:1;	/* software read flow control */
    unsigned wxon:1;	/* software write flow control */
    unsigned rhwf:1;	/* hardware read flow control */
    unsigned whwf:1;	/* hardware write flow control */
    unsigned arti:16;	/* art index */

    unsigned siha;	/* interrupt handler address */

    unsigned hist;	/* device historical address */

    struct ioq *fioq;	/* start of ioqs */

    struct ioq *bioq;	/* back of ioqs  */

    unsigned lpr1:8;	/* link priority */
    unsigned ioct:8;	/* count of i/o outstanding */
    /* udt.sta2 */
    unsigned ioq:1;	/* IOQ linked from UDT */
    unsigned iop:1;	/* IOP device */
    unsigned malf:1;	/* device malfunction */
    unsigned intv:1;	/* operator intervention applicable */
    unsigned sxio:1;	/* use standard XIO interface */
    unsigned flop:1;	/* floppy disc */
    unsigned cart:1;	/* cartridge module drive */
    unsigned mhfh:1;	/* moving head disc with fixed head option */
    unsigned rdtr:1;	/* use DTR line, else RTS; if RXON set */
    unsigned md:1;	/* memory disk */
    unsigned mdal:1;	/* memory allocated for memory disk */
    unsigned mdst:1;	/* starting address of mem disc set at sysgen */
    unsigned ppv:1;	/* multiport device is shared */
    unsigned ansi:1;	/* device is exclusive ANSI */
    unsigned slpr:1;	/* serial printer */
    unsigned dcxr:1;	/* port is switched and CXR=N specified */
};
#endif /* UDT_H */
