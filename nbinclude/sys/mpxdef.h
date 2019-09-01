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
    int           eof;
    int           cseg[2];
    int           attr;
    int           ablk[6];
    int           dftaccs;
};

/*  defines for attr  */

#define UNBLASS 0x10000000

struct fcbtag {  /* FCB structure */
    unsigned   :4      ;
    unsigned opcode :4 ;
    char         lfc[3];
    char           *tcw;
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
    int         devstat;
    int            recl;
    int             ioq;
    int          errrtn;
    struct fattag *fata;
    char       *bufaddr;
    int         excount;
    int          exracc;
    int          statw1;
    int          statw2;
    int         (*nwnorm)();
    int         (*nwerrtn)();
    char       *blkbuff;
};
struct fpttag  {
    unsigned           :     8;
    char       lfc[3]         ;
    struct         { /* FPT flag bits */
        unsigned       :     1;
        unsigned  mult :     1;
        unsigned       :     1;
        unsigned  open :     1;
        unsigned  nuse :     1;
        unsigned  psyc :     1;
        unsigned  pfpt :     1;
        unsigned       :     1;
        }fptlfgs;
     };
struct udttag {
       unsigned   udti:16;  /* the udt index */
       unsigned   cdti:16;  /* the cdt index */

       unsigned onli:1;     /*if set online */
       unsigned dpdc:1;     /* if set dual ported xio disc*/
       unsigned aloc:1;     /* set if allocated */
       unsigned use:1;      /* set if in use */
       unsigned noal:1;     /* set if sys out unable to allocate*/
       unsigned shr:1;      /* set if a sharable device */
       unsigned prem:1;     /* set if premounted */
       unsigned tsm:1;      /* set if a tsm device */
       unsigned dtc:8;      /* device type code */
       unsigned chan:8;     /* device channel */
       unsigned suba:8;     /* device subaddres */
       unsigned : 8;        /* reserved */
       unsigned dqea :24;   /* dqe address */
       unsigned pchn:8;     /* physical channel */
       unsigned psub:8;     /* logical address */
       unsigned char:8;     /* number of characters per line */
       unsigned line:8;     /* number of lines per page */
       unsigned flgs:8;     /* *I* don't need all the different flags*/
       unsigned spt:8;      /* sectors per track or line count */
       unsigned mbx:16;     /* max byte transfer */
       unsigned secs ;      /* sectors on the disk */
       unsigned ssiz:16;    /* sector size, or tab settint */
       unsigned nhds:16;    /* sector size, or tab setting*/
       unsigned sern;      /* serial number if tape*/
       unsigned ptov;      /* time out value */
       int *dcaa;           /* dca address */
       unsigned dial :1;
       unsigned modm :1;   /* connected to a modem */
       unsigned grfc :1;   /* graphic port */
       unsigned fdux :1;   /* full duplex port */
       unsigned mdra :1;   /* multi drop port */
       unsigned vol  :1;   /* volume mounted on device */
       unsigned echo :1;
       unsigned whocares :9;
       unsigned arti:16;      /* art index */
       unsigned siha   ;      /* interrupt handler address*/
       unsigned hist ;     /* device historical address */
       struct ioqtag *fioq;   /* start of ioqs */
       struct ioqtag *bioq;   /* back of ioqs  */
       unsigned lpr1:8;       /* link priority */
       unsigned ioct:8;       /* count of i/o outstanding */
       unsigned sta2:16;      /* stat 2, I dont need these either */
      }  ;
struct ioqtag {
       struct ioqtag *sfa;    /* string forward to next ioq */
       struct ioqtag *sba;    /* string back */
       unsigned pri:8;        /* que priority */
       unsigned type:8;       /* ioq type */
       unsigned chno:8;       /* channlel number */
      unsigned subai:8;       /* subaddres */
      unsigned rtn;           /* reserved */
      unsigned psd   ;        /* psd1 of task interrup routine */
      unsigned psd2  ;        /* psd2 of task interrupt routine */
      unsigned stat:8;        /* status of ioq */
      unsigned fcba:24;       /* address of ioq */
      unsigned prgn:8;        /* program number */
      unsigned cdta:24;       /* cdt address */
      unsigned fct1b:8;       /* to get at the first 8 words */
      unsigned fct1:24;       /* the rest  */
      unsigned fct2;       /* function word 2 */
      int      fct3;       /* function word 3 */
      unsigned fct4;       /* function word 4 */
      unsigned flgs    ;       /* flags */
      unsigned fata   ;       /* fat address */
      unsigned utrn:16;       /* the number of bytes transfered */
      unsigned wosb:16;       /* the number of words in the os buffer*/
      unsigned fbuf   ;       /* user buffer address */
      unsigned tbuf   ;       /* os buffer address */
      unsigned iost   ;       /* status word 1 */
      unsigned ist1   ;       /* status word 2 */
      unsigned ist2   ;       /* status word 3 */
      unsigned udta   ;       /* udt address */
      unsigned cont   ;       /* info from word 2 of fcb */
      unsigned dcaai   ;       /* address of dca */
      unsigned mode:8;        /* mode bits */
      unsigned psav:8;        /* queue prio tem storage */
      unsigned xtra:16;       /* number of extra words in ioq */
      unsigned inop   ;       /* error processing addres */
      unsigned iocd   ;       /* addres of iocd list */
};

struct dcatag {
       unsigned fill[35];     /* I really dont care about any of this */
       struct udttag *cudt;
     };

#define C_UDTA  (struct udttag **) 0XB38
#define C_UDTN (short *) 0XC38
#define C_ARTA  (struct arttag **) 0xAF8
#define C_ARTN  (short *) 0xc44
#define C_REV   0xb58
#define C_NTIM  0xadc
#define C_MTIM  0xae0
#define C_CURR  (struct dqetag ** ) 0x8e8

 struct dqetag {
        int blahblah[3];    /* this may need some work for other uses!!*/
        int pid;            /* the process id */
        int clahblah[4];    /* skip */
        int pseudo[2];      /* pseudonym */
        int ustat;          /* user status word */
        int schflag;        /* scheduling flags */
        int alahblah[20];   /* not the right number but I dont care now */
       };

 struct arttag {
        int block;
        struct udttag *udta;
        unsigned exshr: 1;     /* allocated for shared use */
        unsigned imshr: 1;     /* allocated for implicit shared use*/
        unsigned mnt:1;        /* allocated as mount device */
        unsigned delet:1;      /* marked for deletion */
        unsigned space:1;      /* segment definition */
        unsigned part :1;         /* memory partition */
        unsigned devc :1;      /* is a device */
        unsigned actv :1;      /* active entry */
        unsigned trunc:1;      /* marked for truncation */
        unsigned :2;           /* reserved */
        unsigned wown2:1;      /* dual processor is being appended */
        unsigned dplk:1;       /* dual processor lock */
        unsigned wown:1;       /* dual processor being written */
        unsigned dualp:1;      /* dual processor */
        unsigned port:1;        /* port desi for lock owner */
        char xrl;              /* index of lock */
        char srl;              /* index of synchronous lock */
        char assns;            /* number of active assignments */
        char users;            /* number of users */
        char que;              /* number of readers */
        char rdrs;
        int eof;               /* eof on this file */
        int eom;               /* eom on this file */
    };


