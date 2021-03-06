/*~!fat.h*/
/* Name:  fat.h Part No.: _______-____r
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

#ifndef FAT_H
#define FAT_H

#ident	"@(#)nbinclude:fat.h	1.0"

typedef struct fat {  /* FAT structure */

/*** word 0 ***/
    char  stb;     /* status bits */
                   /* bit 0 - file open */
                   /*     1 - file opened read/write */
                   /*     2 - permanent file */
                   /*     3 - blocking buffer output active */
                   /*     4 - unformatted medium */
                   /*     5 - volume resource */
                   /*     6 - read only access */
                   /*     7 - TSM associated FAT */
    char  acf;     /* access flags */
                   /* for volume resource : */
                   /* bit 0-1 - unused */
                   /*     2   - "$" read on SYC */
                   /*     3-4 - unused */
                   /* for unformatted medium only: */
                   /* bit 0 - mount message inhibited */
                   /*     1 - multivolume tape */
                   /*     2 - mount message has been output */
                   /*     3 - tape at EOT */
                   /*     4 - tape at BOT */
                   /* for volume resources bits 5-7 equal: */
                   /* value = 0 - not system file */
                   /*       = 1 - SYC file */
                   /*       = 2 - SGO file */
                   /*       = 3 - SLO file */
                   /*       = 4 - SBO file */
    short cdtx:16; /* UDT index */

/*** word 1 ***/
    int  flgs:8;   /* flags */
                   /* bit 0 - blocking buffer present */
                   /*     1 - SMAP or DMAP assignment */
                   /*     2 - reserved (set RM in use) */
                   /*     3 - file assigned to NULL device */
                   /*     4 - fat entry not in use */
                   /*     5 - TSM i/o (task swappable) */
                   /*     6 - reserved */
                   /*     7 - reserved */
    int nas:8;     /* number of FPT's assigned */
    short udtx:16; /* UDT index */

/*** word 2 ***/
    union  {        /* word 2 */
    int  sega;     /* current segment position in file */
    int  vnam;     /* volume name for dismount message */
    } wd2  ;

/*** word 3 ***/
    int  pos;      /* relative file block position */

/*** word 4 ***/
    int reom;      /* relative EOM block */

/*** word 5 ***/
    int reof;      /* relative EOF block */

/*** word 6 ***/
    short cseg;    /* current segment position in file */
    short nseg;    /* number of segments in file */

/*** word 7 ***/
    short sege;    /* relative end block of current segment */
    short arec;    /* append record pointer */

/*** word 8 ***/
    int  attr;     /* file attributes field */
                   /* bit 0 - file is automatically extendable */
                   /*     1 - file is implicitly shared */
                   /*     2 - file data has been modified */
                   /*     3 - unblocked specified at assignment */
                   /*     4 - file opened for random access */
                   /*     5 - file opened in blocked mode */
                   /*     6 - expanded fcb */
                   /*     7 - resource descriptor opened for modify */
                   /*     8 - current access mode specified at assign */
                   /*     9 - resource to be marked blocked at close */
                   /*    10 - enqueue inhibit */
                   /*    11 - spool option requested */
                   /*    12 - EOF update required */
                   /*    13 - reserved for iocs */
                   /*    14 - file assigned to non-public volume */
                   /*    15 - seqmented file */
                   /*    16 - task in resource queue when deleted */
                   /*    17 - RD not to be updated on close */
                   /*    18-31 - reserved */

/*** word 9 ***/
    int ablk;      /* append block number */

/*** word 10***/
    char *bbad;    /* blocking buffer address */

/*** word 11***/
    int vatx:8;    /* associated VAT index */
    int opct:8;    /* number of opens on this FAT */
    int cacm:8;    /* current access mode */
    int type:8;    /* resource type code */

/*** word 12***/
    int pdir;      /* address of parent directory RD */

/*** word 13***/
    int doff;      /* relative offset of parent dir entry */

/*** word 14***/
    char *arta;    /* ART entry pointer */

/*** word 15***/
    int accs;      /* assigned access restrictions */
} ;
#endif
