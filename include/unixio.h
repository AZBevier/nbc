/*~!unixio.h*/
/* Name:  unixio.h Part No.: _______-____r
 *
 * Copyright 1992 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:unixio.h	1.1"

#ifndef UNIXIO_H
#define UNIXIO_H

#include   <mosde.h>		/* machine and o/s equates */
#include   <stdio.h>		/* now included to get _NFILE */

/*  function declarations     */

int  open();
int  close();
int  creat();
int  read();
int  write();
int  seek();
int  isatty();
int  _cassg();
int  __isblk();

static int assn();
static int cnpo();
static int exist();
static int getfd();
static int prspn();
static int _skbl(),_skub(),_skdv();
static int _rbl(),_rub();
static int _wbl(),_wub();
static int _getrec();
static int _putrec();

struct fcbtag  *fcbadr();
int  readraw();
int  writraw();
int  delete();

/*   static data   */

static int PNBWRDX;
static int PNBVCTOR;
extern struct rrstag _rrs;
static struct filtag *curfil;
static struct fcbtag *curfcb;
static struct flprmtag *curfprm;
static int carcont = 1;
static int ieofbl;      /* initial eof block(from rd) */
static int iofd;	/* current fd */

/* macros */

#define BUFVALID curfprm->bufvalid
#define BUFALTER curfprm->bufalter
#define PUTR {int i;if(i=_putrec(BUFSIZ,curfil->line))return(i);}
#define GETR {int i;if(i=_getrec(BUFSIZ,curfil->line))return(i);BUFALTER = 0;}
#define CURFIL curfil=filtabl+fd
#define CURFCB curfcb= &(curfil->fcb)
#define CURFPRM curfprm= &(curfil->filparm)
#define INIT CURFIL;CURFCB;CURFPRM; iofd = fd;

#ifdef MPX1X
/* added for MPX1X */
#define CPYNAME(SRC,DST) {char *s=(char *)(SRC);char *d=(char *)(DST);\
int i;for(i=0;i<8;i++,s++)*d++=((*s)!=' ')?*s:'\0';}
#endif

#ifndef MPX1X
/*    struct tags for RRS building  */
struct accspec {    /* access specifications */
    unsigned read  :        1;
    unsigned write :        1;
    unsigned modfy :        1;
    unsigned updat :        1;
    unsigned appnd :        1;
    unsigned       :       11;
    unsigned shar  :        1;
    unsigned excl  :        1;
    unsigned       :       14;
    };

struct optspec {   /* options specifications */
    unsigned syc   :        1;
    unsigned sgo   :        1;
    unsigned slo   :        1;
    unsigned sbo   :        1;
    unsigned blk   :        1;
    unsigned unblk :        1;
    unsigned nomsg :        1;
    unsigned       :        1;
    unsigned open  :        1;
    unsigned buff  :        1;
    unsigned       :        3;
    unsigned publc :        1;
    unsigned       :       18;
    };
#endif

#ifdef MPX1X
struct rrstag {    /* RRS structure */
    char	flags;
/*  flag settings
    bit 0	set if assign type 1
	1	set if assign type 2 SLO or SBO
	2	set if assign type 2 SGO or SYC
	3	set if assign type 3
	4	set if assign type 4
	5	set if unblocked is specified for type 1 or 3
	6	set if mount message inhibited
	7	set if system file allocation
*/
    char	lfc[3];
    int		wd2;
/* wd2 can of the form /*
/* type 1	short password
		short filename[3] - 6bit compressed code 0-3f = 20-5f
   type 2	char  unused
		char  sfc[3] - system file code (SLO, SBO, SGO, or SYC)
		int   size - size in 192w blocks (SLO & SBO only)
   type 3       char  device type code (bit zero set if chan field present)
		char  volume number
		char  channel number (bit zero set if sub address present)
		char  subaddress
		int   size or reel id (disk - # 192w blocks, tape ascii id)
   type 4	char  unused
		char  lfc[3] - lfc to be assigned
*/
    int       size;
   };

#else

struct rrstag {    /* RRS structure */
    unsigned      :    8;
    char    lfc[3];
    char      type;
    char      size;
    short    spec ;
    struct accspec  accs ;
    struct optspec  opts ;
    char   name[44];
   };
#endif

/*     struct tags for fcb,fat and fpt building    */
struct fcbbit {    /* control bits */
    unsigned nowait :        1;
    unsigned noerr  :        1;
    unsigned dfi    :        1;
    unsigned nst    :        1;
    unsigned ran    :        1;
    unsigned bl     :        1;
    unsigned exp    :        1;
    unsigned iec    :        1;
    unsigned dfd    :        1;
    unsigned specctl:        4;
    unsigned racc   :       19;
    };

struct fattag {  /* fat structure */
    unsigned open   :        1;   /* word 0 of FAT */
    unsigned opron  :        1;
    unsigned  perm  :        1;
    unsigned  bbuf  :        1;
    unsigned unfor  :        1;   /* dft.stb */
    unsigned volmr  :        1;
    unsigned  rom   :        1;
    unsigned  tsm   :        1;
    unsigned acf    :        8;
    unsigned cdtx   :       16; /* cdt index */

    unsigned blbuff :        1;   /* word 1 of FAT */
    unsigned   mapa :        1;
    unsigned        :        1;
    unsigned   null :        1;
    unsigned  fatus :        1;
    unsigned  tsmio :        1;
    unsigned        :        2;
    char      nas;
    unsigned udtx   :       16; /* udt index */
    int               vnam;
    int           pos;
    int           eom;
#ifdef MPX1X
    char	  opc;		/* open count */
    unsigned  bbufa: 24;	/* blocking buffer address */
#else
    int           eof;
    int           cseg[2];
    int           attr;
    int           ablk[6];
    int           dftaccs;
#endif
};

/*  defines for attr  */

#define UNBLASS 0x10000000

struct fcbtag {  /* FCB structure */
    unsigned opcode :4 ;
    char         lfc[3];
    char           *tcw;
    struct fcbbit  cntl;
    int         devstat;
    int            recl;
    int             ioq;
    int          errrtn;
    char       *fataddr;
    char       *bufaddr;
    int         excount;
    int          exracc;
    int          statw1;
    int          statw2;
    int          nwnorm;
    int         nwerrtn;
    int        *blkbuff;	/* not used on MPX1X */
};

struct fpttag  {
    unsigned           :     8;
    char       lfc[3]         ;
    struct fptflgs { /* FPT flag bits */
        unsigned       :     1;
        unsigned  mult :     1;
        unsigned       :     1;
        unsigned  open :     1;
        unsigned  nuse :     1;
        unsigned  psyc :     1;
        unsigned  pfpt :     1;
        unsigned       :     1;
        };
     };

#ifndef MPX1X
/*    struct tags for cnp's and rcb's    */
struct cnptag {        /* CNP structure */
    int         timeout;
    int           abrtn;
    short      options ;
    short      status  ;
    int        resvd[3];
};

/*    defines for options field     */

#define OBL 0x10
#define OUB 0x20
#define OUPD 0x0400
#ifndef NOBBS
#define OUBBS 0x28	/* unblocked and blocked data */
#endif

/*   struct tags for rd   */
struct rdsflgs { /* Resource Descriptor Space definition flags */
    char        rtype         ;
    unsigned           :     3;
    unsigned     eofm  :     1;
    unsigned           :     5;
    unsigned    ownid  :     1;
    unsigned    usrid  :     1;
    unsigned           :    12;
    unsigned    block  :     1;
    };
    union typet { short vol   ;
            short resrc       ;
            short dmap        ;
            short smap        ;
            short root        ;
            short image       ;
            short bdblk       ;
            short spool       ;
            short file        ;
            short dir         ;
            short tfile       ;
            short tdir        ;
            short mem         ;
            short tmem        ;
            short devc        ;
            short bdmap       ;
            short bsmap       ;
                 };
struct rdtag   { /* Resource Descriptor */
    char     idnam[16]        ;
    int          date         ;
    int          time         ;
    int          doff         ;
    short       rdflg         ;
    short        type         ;
    int         _datgrp[56]   ;
    int         _other[63]    ;
    int         _eofpos       ;
   };


struct rlbtag {
    char      *pnbvctor[4]    ;
    unsigned           :    20;
    char      *fcbaddr[4]     ;
    unsigned           :     4;
    };

/*   struct tags for rcb    */

struct rcbflg {        /* RCB FLAGS */
    unsigned   _ftyp   :     8;
    unsigned           :     3;
    unsigned   _eofm   :     1;
    unsigned   _fstf   :     1;
    unsigned   _nsav   :     1;
    unsigned           :     9;
    unsigned   _zero   :     1;
    unsigned   _auto   :     1;
    unsigned   _manu   :     1;
    unsigned   _cont   :     1;
    unsigned   _shar   :     1;
    unsigned           :     3;
    unsigned  _block   :     1;
};

#define _RACC 0X80000000
#define _WACC 0X40000000
#define _MACC 0X20000000
#define _UACC 0X10000000
#define _AACC 0X08000000
#define _DACC 0X00400000

#define _OWNA 0X80000000
#define _USNA 0X40000000
#define _OTNA 0X20000000

struct rcbtag {        /* RCB structure for permanent file */
    char          _ownr[8];
    char          _user[8];
    int              _owri;
    int              _ugri;
    int              _otri;
    struct rcbflg   _flags;
    int              _mxei;
    int              _mnei;
    int              _mxsz;
    int              _osiz;
    int              _addr;
    int              _fast;
    int              _opts;
    struct rcbflg    _free;
};
#endif

/*   struct tag for filtabl parameters    */

struct flprmtag {
   int   mode;          /* UNUSED,READ,WRITE,UPDATE */
   short device;        /* terminal,perm file, device */
#ifndef NOBBS
   unsigned junk:     5;	/* unused bits */
   unsigned bbs:      1;	/* use big blocking subroutines */
#else
   unsigned junk:     6;
#endif
   unsigned eom:      1;      /* yes,no */
   unsigned oneln:    1;      /* set if reading 1 mpx record at a time */
   unsigned crlf:     1;      /* c/r l/f flag */
   unsigned binary:   1;      /* yes,no */
   unsigned cmpop:    1;      /* set if we tested for compressed file */
   unsigned cmpflg:   1;      /* set if reading compressed file */
   unsigned block:    1;      /* yes,no */
   unsigned eof:      1;      /* yes,no */
   unsigned bufvalid: 1;      /* yes,no */
   unsigned bufalter: 1;      /* yes,no */
   int   linptr;        /* current byte in random access block buffer */
   int   blkptr;        /* current block in random access file */
   int   eofptr;        /* last valid byte in random access file */
   int	 bcnt;		/* compressed rec current count */
   char *bptr;		/* compressed record pointer */
   int   blanks;	/* current count of blanks to output */
   int   charcnt;	/* current count of chars to output */
   int   state;		/* current compressed record state */
#define CBLANKS 1	/* processing blanks */
#define CCHARS 2	/* processing characters */
};

/*   the filtabl struct    */

extern char *bufrsio;

#ifdef MPX1X
/* finfo structure defines the current file assigned */
struct finfo {
 int	username[2];	/* Username associated with file */
 int	userkey[2];	/* key, if any associated with username */
 int	filename[2];	/* file name */
 int	password[2];	/* password, if any associate with file */
 short  key;		/* compressed key for username if any */
 short	passwd;		/* compressed file password if any */
};
#endif

struct filtag  {
 struct  fcbtag   fcb;
 struct  flprmtag filparm;
/* int    dwbound; */	/* filparm is dw bounded now */
#ifdef MPX1X
 struct  finfo	fib;	/* file information block */
#else
 int    _pnb[18];
 int    pnbw;
#endif
 char   *line;
};

#ifndef CASSG
 double bound1d;
 struct filtag filtabl [_NFILE] =
                       {{{0,'U','X','0'},{0x10000}},
                       {{0,'U','X','1'},{0x10000}},
                       {{0,'U','X','2'},{0x10000}},
                       {{0,'U','X','3'},{0x10000}},
                       {{0,'U','X','4'},{0x10000}},
                       {{0,'U','X','5'},{0x10000}},
                       {{0,'U','X','6'},{0x10000}},
                       {{0,'U','X','7'},{0x10000}},
                       {{0,'U','X','8'},{0x10000}},
                       {{0,'U','X','9'},{0x10000}},
                       {{0,'U','X',0X3A},{0x10000}},
                       {{0,'U','X',0X3B},{0x10000}},
                       {{0,'U','X',0X3C},{0x10000}},
                       {{0,'U','X',0X3D},{0x10000}},
                       {{0,'U','X',0X3E},{0x10000}},
                       {{0,'U','X',0X3F},{0x10000}},
                       {{0,'U','X',0X40},{0x10000}},
                       {{0,'U','X',0X41},{0x10000}},
                       {{0,'U','X',0X42},{0x10000}},
                       {{0,'U','X',0X43},{0x10000}}};
#else
extern struct filtag filtabl[];
#endif

/*    Device equates     */

#define  DISCFILE 0
#define  SPOOLFILE 1
#define  NULLFILE 2
#define  TERMINAL 3
#define  PIPE 4
#define  EOF        (-1)
#define  EOM        (-2)
#define  LINEPTR      1

/*    Mode equates       */

#define  NOTUSED     0x10000

/*    Blocked equates       */

#define  UNBLOCK      0
#define  BLOCKED      1

/*    macros      */

#define BADFD(d,r)  if(d<0||d>=_NFILE){errno=EBADF;mpxerr=E027;return(r);}
#define ZREG(ari,sz)  {int i;for(i=0;i<sz;i++)ari[i]=0;}
#define ZINT(ptr,sz)  {int i,*p=(int*)(ptr);for(i=0;i<sz;i++)*p++ =0;}

/*    other defines    */

#define PNLENGTH 200
#define CUBFIL 0xcf
#define CBLFIL 0xce
#define CUBFL1 173
#define CUBFL2 174
#define CUBFUS 160
#define REOFBL 68
#endif /* UNIXIO_H */
