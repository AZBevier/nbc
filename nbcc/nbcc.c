/*~!nbcc.c*/
/* Name:  nbcc.c Part No.: _______-____r
 *
 * Copyright 1995 - J B Systems, Morrison, CO
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

#ident	"$Id: nbcc.c,v 1.18 2019/03/10 19:36:46 jbev Exp $"

/*
 * $Log: nbcc.c,v $
 * Revision 1.18  2019/03/10 19:36:46  jbev
 * correct conditional include logic
 *
 * Revision 1.17  2019/03/10 18:34:17  jbev
 * comment out #define TESTING flag
 *
 * Revision 1.16  2019/02/28 00:29:59  jbev
 * Correct conditionals for running on mpx.
 *
 * Revision 1.15  2019/01/10 22:38:01  jbev
 * Correct warning errors for Linux port
 *
 * Revision 1.14  1996/03/22 20:45:55  jbev
 * Back out mode for name being nbasm on linux and alpha.
 * The name will be nbcas on those systems.
 *
 * Revision 1.13  1996/03/19 00:38:05  jbev
 * Use nbasm for linux and alpha.
 *
 * Revision 1.12  1996/03/18 23:29:33  jbev
 * Fix Alpha include path.
 *
 * Revision 1.11  1996/03/18 23:17:52  jbev
 * Mods for Alpha port.
 *
 * Revision 1.10  1995/10/18 21:35:37  jbev
 * Print out name of cataloger when error.  Was always NBCAT.
 *
 * Revision 1.9  1995/08/04  20:38:44  jbev
 * Define ieee when -F flag is set.
 * Correctly set library prefix.
 *
 * Revision 1.8  1995/04/14  21:59:45  jbev
 * Fix the syntax errors.
 *
 * Revision 1.7  1995/04/14  21:56:11  jbev
 * Fix test for mpxlib and add option 'OF' to specify fortran.
 *
 * Revision 1.6  1995/04/06  16:24:10  jbev
 * Added ifdef NBASM to use my assembler.
 *
 * Revision 1.5  1995/03/13  21:03:36  jbev
 * Disable debug flag.
 *
 * Revision 1.4  1995/03/09  21:51:39  jbev
 * Add corrections when debugging fortran file support.
 *
 * Revision 1.3  1995/03/08  17:26:40  jbev
 * Fortran is a reserved word on nbcc.  Use fort77 instead.
 *
 * Revision 1.2  1995/03/06  23:59:57  jbev
 * Add support for Fort77 files (.f).
 * Add option J to surpress _ on C names. Option XJ and X2J.
 *
 * Revision 1.1  1995/03/06  16:33:24  jbev
 * Initial revision
 *
 */

/*
 * cc - Driver for C/Fortran/Cataloger
 */

/*#define TESTING */

#ifdef mpx
#include <param.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>

#else /* mpx */

/* #include <sys/param.h> */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>
#include <wait.h>
#include <string.h>

#if defined(linux) || defined(__alpha)
    #include <dirent.h>
    #ifndef MAXNAMLEN
        #define MAXNAMLEN 256
    #endif
#else
    #include <sys/ndir.h>
    #define PATH_MAX 128
#endif 
#endif /* !mpx */

extern char *getcwd();
static char *cvtfname();
static char *pathname();
static void crunch();

#ifdef mpx
extern char curvol[];
extern char curdir[];
extern char *getcwvd();
extern char *str2lc();
static void conv2unix();
static void blcpy();
static void strlcpy();
#endif

/* forward definitions */
extern int readbb();
extern void dexit();
extern void error();
extern int getsuf();
extern int nodup();
extern void prexec();
extern int callsys();
extern int copyobj();

/* #define TESTING */

#define	MAXN	128
#define BLKSIZE    768

#ifndef mpx
#define O_UNBLK	0
#define O_BIN	0
int mpxbb();
int bin = 0;
unsigned char si[BLKSIZE];
#endif

char *dorrs1();
char *dorrs3();
char *dorrs4();

static char obuf[BLKSIZE];
static char ibuf[MAXN];
static char tbuf[MAXN];

#ifdef mpx
#ifdef MPX1X
char *basedir = "";
#else
char *basedir = "/system/bin/";
#endif /* MPX1X */
#else
char *basedir = "/system/bin/";
#endif

char *cpp = "nbcpp";
char *ccom = "nbccom";
char *cp1 = "nbcp1";
char *cp2 = "nbcp2";
#if defined(NBASM)
char *as = "nbasm";	/* My assembler */
#else
char *as = "nbcas";	/* default Encore assembler */
#endif
char *ld = "nbcat";
char *fld = "catalog";
char *f77 = "fort77";
char basepath[PATH_MAX];
char temppath[PATH_MAX];
char binpath[PATH_MAX];

char *savestr(), *strspl(), *setsuf(), *strip(), *lastfield();
#if defined(linux) || defined(__alpha)
void idexit();
#else
int idexit();
#endif

/* define arg list pointers */
char **av, **alist, **clist, **llist, **plist, **tlist, **olist;

/*
 *   arrange to pass options directly to the preprocessor via -P
 *   arrange to pass options directly to the compiler via -X
 *   arrange to pass options directly to the assembler via -A
 */

char 	*input;		/* input file pointer */
char	*output;	/* output file pointer */
char	*outfile;	/* load module output file pointer */
char	TMPname[12];	/* sgo filename for nbcat */
char	*SGOname = "SGOXXXXXX";	/* sgo filename for nbcat */
char	*sgoname;	/* sgo filename for nbcat */
char	*SYCname = "SYCXXXXXX";	/* syc filename for nbcat */
char	*sycname;	/* syc filename for nbcat */
char	*usersgo;	/* user sgo filename for nbcat */
char	*userslo;	/* user slo filename for nbcat */
char	*fortbo;	/* BO filename for fort77 */
char	*fortsi;	/* SI filename for fort77 */
char	*fortlo;	/* LO filename for fort77 */
char	*dirsname;	/* catalog directives file */
int	exfail = 0;	/* execv failed flag */
int	errflag = 0;	/* error detected flag */
int	oflag = 0;	/* output object to linker */
int	cflag = 0;	/* output object to prog.o */
int	ucflag = 0;	/* output object to user specified prog.o */
#ifdef TESTING
int	debug = 1;	/* work in verbose mode */
#else
int	debug = 0;	/* work in verbose mode */
#endif
int	exflag = 1;	/* pass output to linker */
int	f77flag = 0;	/* program is fortran source */
int	_flag = 0;	/* do not generate _ for names */
int	eflag = 0;	/* -E flag, run cpp only, output to prog.i */
int	fflag = 0;	/* -F flag, use IEEE 754 floating point */
int	gflag = 0;	/* -G flag, debug symbols from assembler */
int	hflag = 0;	/* -H flag, tell BBCCOM no csect directives */
int	kflag = 0;	/* assign libraries for NBCAT */
int	pflag = 0;	/* assign prefile to assembler */
int	rflag = 0;	/* user defined catalog directives */
int	sflag = 0;	/* generate ccom output into file prog.s */
int	tflag = 0;	/* assign tempfile to assembler */
int	mflag = 0;	/* assign macro library to assembler */
int	nflag = 0;	/* do not use reg-reg floating instructions */
int	wflag = 0;	/* suppress ccom warnings */
int	lflag = 0;	/* generate assembler listing */
int	yflag = 0;	/* user defined SLO for NBCAT */
int	zflag = 0;	/* user defined SGO for NBCAT */
int	p2flag = 0;	/* use 2 pass compiler in set */
#ifdef MPX1X
int	mpx1xflag = 1;	/* output mpx 1x object code */
#else
int	mpx1xflag = 0;	/* output mpx 1x object code */
#endif /* MPX1X */
char	*prefile = 0;	/* prefile to use */
char	*listfile = 0;	/* listing file for assembler */
char	list[PATH_MAX + 3];
char	obj[PATH_MAX + 3];
int	na = 0;		/* number of items in alist */
int	nl = 0;		/* number of items in llist */
int	np = 0;		/* number of items in plist */
int	nc = 0;		/* number of items in clist */
int	no = 0;		/* number of items in olist */
int	nt = 0;		/* number of items in tlist */
int	nv = 0;		/* number of items in av */
int	inx = 0;	/* save of loop index, if a break occurs */

/* nbcat activation data */

#ifdef mpx
asm(" bound 1d");	/* double word bound */
#else
static double dummy;		/* double word bound */
#endif
/*
 *        PTASK Activation Block
 */
struct pta {
    char flag;
    char nrrs;		/* number of rrs's */
    char allo;
    char mems;

    char nbuf;
    char nfil;
    char prio;
    char segs;

    int  nm0;		/* wd 1 of name, 0 for path in wd 2 */
    char *catpath;	/* wd 2 of name, load module pathname */

    char psn[8];
    char on[8];
    char proj[8];

    char vat;
    char flg2;		/* expanded ptask block */
    short extd;

    int optw;		/* option wd 1 */
    int tsw;
    char *rptr;		/* rrs definitions */
    int pgo2;
    short fsiz;		/* fixed size is 80 bytes */
    short rsiz;
    int res[4];		/* 4 words spare */
    /* end of fixed part of ptask block */
};

static struct pta pta = {
    0,
    0,
    0,
    0,

    0,
    0,
    0,
    0,

    0,		/* wd 1 of name, 0 for path in wd 2 */
    0,		/* wd 2 of name, load module pathname */

    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,

    0,
    0x08,	/* expanded ptask block */
    0,
    0,
    0,
    0,		/* rrs definitions */
    0,

    80,		/* fixed size is 80 bytes */
    0,
    0,0,0,0,
    /* end of fixed part of ptask block */
};

struct rrs1 {		/* assign to file */
    char zero;		/* not used */
    char lfc0;		/* three char LFC */
    char lfc1;
    char lfc2;
    char type;		/* rrs type */
    char size;		/* size of rrs in words */
    char plen;		/* pathname length */
    char rez;		/* not used */
    int accs;		/* access bits */
    int opts;		/* options */
    char path[56];	/* pathname of file, 51 bytes max */
};

struct rrs3 {		/* assign to device */
    char zero;		/* not used */
    char lfc0;		/* three char LFC */
    char lfc1;
    char lfc2;
    char type;		/* rrs type */
    char size;		/* size of rrs in words */
    char dens;		/* pathname length */
    char rez;		/* not used */
    int accs;		/* access bits */
    int opts;		/* options */
    char dt3;		/* device type */
    char vlnum;		/* volume number */
    char chn3;		/* channel number */
    char schn3;		/* sub-channel number */
    int unfid;		/* unformatted ID */
};

struct rrs4 {		/* assign to lfc */
    char zero;		/* not used */
    char lfc0;		/* three char LFC */
    char lfc1;
    char lfc2;
    char type;		/* rrs type */
    char size;		/* size of rrs in words */
    short rez;		/* not used */
    char zero1;		/* not used */
    char sfc0;		/* three char LFC */
    char sfc1;
    char sfc2;
    int opts;		/* options */
};

/* BOUND     1D */
double junk;
/* variable rrs table, 1536 bytes */
static int var_rrs[384];		/* start of variable rrs */

/* Parameter Send Block for PTASK */
struct psb {
    int  blk;	/* wd 0 of lmname, 0 if path in wd 2 */
    char *path;	/* load module pathname */
    int  squa;	/* bytes to be send in rt hw */
    char *sba;	/* send buffer address */
    short rpbl;	/* return buffer length */
    short acrp;	/* actual bytes returned */
    char *rba;	/* return buffer address */
    char *eaa;	/* end action address */
    char cst;	/* completion status */
    char ist;	/* initial status */
    char ust;	/* user status */
    char opt;	/* options */
};

static int ret_rba[2];		/* return buffer */
static struct psb psb = {
/* Parameter Send Block for PTASK */
	0,	/* wd 0 of lmname, 0 if path in wd 2 */
	0,	/* load module pathname */
	0,	/* bytes to be send in rt hw */
	0,	/* send buffer address */
	8,	/* return buffer length */
	0,	/* actual bytes returned */
	(char *)ret_rba,	/* return buffer address */
	0,	/* end action address */
	0,	/* completion status */
	0,	/* initial status */
	0,	/* user status */
	0,	/* options */
};

#define cunlink(s) if (s) unlink(s)

int main(argc, argv)
int argc;
char **argv;
{
  char *t;
  int i, j, c;

  strcpy(basepath, basedir); 	/* default path to processors */
  av = (char **)calloc(argc+15, sizeof (char **));
  alist = (char **)calloc(argc, sizeof (char **));
  clist = (char **)calloc(argc, sizeof (char **));
  llist = (char **)calloc(argc, sizeof (char **));
  olist = (char **)calloc(argc, sizeof (char **));
  plist = (char **)calloc(argc, sizeof (char **));
  tlist = (char **)calloc(argc, sizeof (char **));

#ifdef TESTING
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);
#endif
  /* if no args, display options */
  if (argc <= 1 ) {
    fprintf(stderr, "NBCC Options:\n");
    fprintf(stderr, "-Q[option]   send option to NBCPP\n");
    fprintf(stderr, "-X[option]   send option to NBCCOM\n");
    fprintf(stderr, "-A[option]   send option to NBCAS\n");
#ifdef MPX1X
    fprintf(stderr, "-B/VOL/DIR/  base pathname for processors; default /SYSTEM/SYSTEM/\n");
#else
    fprintf(stderr, "-B/VOL/DIR/  base pathname for processors; default /SYSTEM/BIN/\n");
#endif /* MPX1X */

    fprintf(stderr, "-1           output MPX1X object code\n");
    fprintf(stderr, "-2           use 2 pass version of the compiler\n");
    fprintf(stderr, "-N           Do not generate reg-reg floating instructions\n");
    fprintf(stderr, "-V           echo commands from NBCC during processing\n");

    fprintf(stderr, "-Dsym        define sym to NBCPP during processing\n");
    fprintf(stderr, "-Usym        undefine sym to NBCPP during processing\n");
    fprintf(stderr, "-Idir        search dir for include files in NBCPP\n");
    fprintf(stderr, "-E           send output from NBCPP to prog.i\n");
    fprintf(stderr, "-F           use IEEE 754 floating point\n");

    fprintf(stderr, "-H           MPX handler, emit dsect only from NBCCOM\n");
    fprintf(stderr, "-S           keep output from NBCCOM in prog.s, do not run NBCAS\n");
    fprintf(stderr, "-W           suppress NBCCOM warning messages\n");
    fprintf(stderr, "-J           delete '_' from names\n");
    fprintf(stderr, "-C           output object to prog.o from NBCAS\n");
    fprintf(stderr, "-G           output debug symbols from NBCAS/NBCAT\n");
    fprintf(stderr, "-L[file]     assign file as listing file for NBCAS, default prog.l\n");
    fprintf(stderr, "-Mlib        assign lib as macro library for NBCAS\n");
    fprintf(stderr, "-Pfile       assign file as prefile for NBCAS\n");
    fprintf(stderr, "-Tfile       assign file as tempfile for NBCAS/NBCAT\n");

    fprintf(stderr, "-O lmname    catalog load module 'lmname' using NBCAT\n");
    fprintf(stderr, "-Kprefix     library prefix, i.e. 'C' for CLIB/CDIR\n");
    fprintf(stderr, "-Rfile       cataloger directives file, CDIRS is default\n");
    fprintf(stderr, "-Yfile       cataloger SLO file, default is NULL\n");
    fprintf(stderr, "-Zfile       file containing compressed objects\n");
    
    exit(0);
  }
  for (i = 1; i < argc; i++) {
    if (*argv[i] == '-') switch (argv[i][1]) {

    case 'b':
    case 'B':	/* use new directory base */
      if (argv[i][2] == '\0') {
        error("Base directory not given for -B option", 0);
        continue;
      } else {
        strcpy(basepath, &argv[i][2]); 	/* new path to processors */
      }
      continue;

    case '1':	/* output mpx 1x object code */
      mpx1xflag++;
      continue;

    case '2':	/* use 2 pass version of compiler */
      p2flag++;
      continue;

    case 'n':
    case 'N':	/* do not output reg-reg instructions */
      nflag++;
      continue;

    case 's':
    case 'S':	/* generate assembler output from ccom */
      sflag++;
      cflag = 0;
      continue;

    case 'q':
    case 'Q':	/* cpp specific flags */
      if (argv[i][2] == '\0')
      {
        continue;
      }
      argv[i][1] = '-';
      plist[np++] = &argv[i][1];
      continue;

    case 'x':
    case 'X':	/* ccom specific flags */
      if (argv[i][2] == '\0')
      {
        continue;
      }
      tlist[nt++] = argv[i];
      continue;

    case 'a':
    case 'A':	/* as specific flags */
      if (argv[i][2] == '\0')
      {
        continue;
      }
      argv[i][1] = '-';
      alist[na++] = &argv[i][1];
      continue;

    case 'o':
    case 'O':
      if (((argv[i][2] == 'F') || (argv[i][2] == 'f')) && argv[i][3] == '\0') {
	f77flag++;
	goto fortcase;
     }
      if (argv[i][2] != '\0') {
    	outfile = &argv[i][2];
      } else {
fortcase:
    	if (i+1 < argc) {
    	  if (*argv[i+1] != '-') {
            outfile = argv[i+1];
    	    ++i;
    	  } else {
    	    error("filename not given for -O option", 0);
    	    continue;
    	  }
    	} else {
    	  error("filename not given for -O option", 0);
    	  continue;
    	}
      }
      switch (getsuf(outfile)) {
        case 's':
        case 'S':
        case 'c':
        case 'C':
        case 'f':
        case 'F':
#ifdef NOT_ANYMORE
        case 'o':
        case 'O':
#endif
          error("-o would overwrite %s", outfile);
          exit(8);
      }
#ifdef mpx
      str2up(outfile);
#endif
#ifndef NOT_ANYMORE
      switch (getsuf(outfile)) {
        case 'o':
        case 'O':
      ++cflag;		/* need objects for .s & .c file */
      sflag = 0;
      ++ucflag;		/* user specified object file */
      continue;
      }
#endif
      ++oflag;
      ++cflag;		/* need objects for .s & .c file */
      continue;

    case 'g':
    case 'G':	/* output debug symbols from assembler */
      gflag++;
      continue;

    case 'h':
    case 'H':	/* surpress csect directives */
      hflag++;
      continue;

    case 'j':
    case 'J':	/* remove _ from variable names */
      _flag++;
      continue;

    case 'w':
    case 'W':	/* surpress ccom warning messages */
      wflag++;
      continue;

    case 'e':
    case 'E':	/* output cpp output to file.i */
      eflag++;
      continue;

    case 'f':
    case 'F':	/* use IEEE 754 floating point */
      fflag++;
      plist[np++] = "-Dieee";	/* define for nbcpp */
      continue;

    case 'l':
    case 'L':	/* output listing file */
      lflag++;
      if (argv[i][2] == '\0') {
        continue;
      }
      alist[na++] = argv[i];
      listfile = &argv[i][2];
      continue;

    case 'p':
    case 'P':	/* use prefile */
      if (argv[i][2] == '\0') {
        error("Prefile not given for -P option", 0);
        continue;
      } else {
        pflag++;
        prefile = &argv[i][2];
      }
      continue;

    case 'c':
    case 'C':	/* generate object in prog.o */ 
      cflag++;
      sflag = 0;
      continue;

    case 'm':
    case 'M':	/* assign macro library */
      if (argv[i][2] == '\0') {
        error("Macro library not given for -M option", 0);
        continue;
      }
      mflag++;
      alist[na++] = argv[i];
      continue;

    case 't':
    case 'T':	/* assign temp asm file */
      if (argv[i][2] == '\0') {
        error("temp filename not given for -T option", 0);
        continue;
      }
      tflag++;
      sgoname = &argv[i][2];	/* save for nbcat also */
      close(open(sgoname, O_CREAT | O_WRONLY, 0666));
      alist[na++] = argv[i];
      continue;

    case 'r':
    case 'R':	/* assign catalog directives file */
      if (argv[i][2] == '\0') {
        error("directives filename not given for -R option", 0);
        continue;
      }
      rflag++;
      dirsname = &argv[i][2];	/* save for nbcat */
      continue;

    case 'k':
    case 'K':	/* assign catalog library files */
      if (argv[i][2] == '\0') {
        error("library name not given for -K option", 0);
        continue;
      }
      kflag++;
      llist[nl++] = &argv[i][2];	/* save for nbcat */
      continue;

    case 'y':
    case 'Y':	/* assign user defined SLO file */
      if (argv[i][2] == '\0') {
        error("SLO file name not given for -Y option", 0);
        continue;
      }
      yflag++;
      userslo = &argv[i][2];	/* save for nbcat */
      close(open(userslo, O_CREAT | O_WRONLY, 0666));
      continue;

    case 'z':
    case 'Z':	/* assign user defined SGO file */
      if (argv[i][2] == '\0') {
        error("object file name not given for -Z option", 0);
        continue;
      }
      zflag++;
      usersgo = &argv[i][2];	/* save for nbcat */
#ifdef NASA_FIX_120694
      close(open(usersgo, O_CREAT | O_WRONLY, 0666));
#endif
      continue;

    case 'D':	/* define for cpp */
    case 'd':
    case 'I':	/* dir search path for cpp */
    case 'i':
    case 'U':	/* undefine for cpp */
    case 'u':
      if (argv[i][2] == '\0') {
        error("Entry not provided for -%c option", argv[i][1]);
        continue;
      } else {
        plist[np++] = argv[i];
        continue;
      }

    case 'v':
    case 'V':   /* Use -v for debugging */
      debug = 1;
      continue;

    }	/* end of option switch */

    /* now process file names */
    t = argv[i];
    c = getsuf(t);
    if (!c)
      error("File does not have valid suffix: %s", t);
    if (c=='c' || c=='s' || c=='i' || c=='f') {
      clist[nc++] = t;
      t = setsuf(t, 'o');
      /* set object name in case we are to catalog */
      olist[no++] = t;
    } else {
      /* set object name in case we are to catalog */
      if (c == 'o')
    	olist[no++] = t;
    }
  }

  /* Now start the real work */
  /* if no files given, exit */
  if (nc == 0 && no == 0 && !zflag)
    goto nocom;
#ifndef mpx
  if (signal(SIGINT, SIG_IGN) != SIG_IGN)
    signal(SIGINT, idexit);
  if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
    signal(SIGTERM, idexit);
  if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
    signal(SIGHUP, idexit);
#endif

/* now process all files in clist */
  for (i=0; i<nc; i++) {
    inx = i;
    if (nc > 1) {
      printf(" Processing %s:\n", clist[i]);
      fflush(stdout);
    }
#ifdef FUTURE
    if (getsuf(clist[i]) == 'y') {
      input = clist[i];
      goto yacc;
    }

#endif
    if (getsuf(clist[i]) == 's') {
      input = clist[i];
      goto assemble;
    }

    if (getsuf(clist[i]) == 'i') {
      input = clist[i];
      goto compile;
    }

    if (getsuf(clist[i]) == 'f') {
      input = clist[i];
      f77flag++;
      goto fort77;
    }

    /* do the cpp work for .c files */
    av[0] = "nbcpp"; 
    av[1] = clist[i]; 
    output = setsuf(clist[i], 'i');
    av[2] = output;
    nv = 3;
    /* if listing or debugging required, leave comments */
#ifdef MAYBE
    if (lflag || gflag)
      av[nv++] = "-C";
#endif
    for (j = 0; j < np; j++)
      av[nv++] = plist[j];
    av[nv++] = 0;
    strcpy(temppath, basepath);	/* copy base directory */
    strcat(temppath, cpp);	/* name of processor */
    if (callsys(temppath, av)) {
      exfail++;
      errflag++;
      if (!eflag)
        cunlink(output); 
      continue;
    }

    /* if -E flag, skip to next file */
    if (eflag) {
      continue;
    }

    /* prog.i becomes input to ccom */
    /* output is to prog.z or prog.s depending on sflag */
    /* output is to prog.z or prog.a depending on p2flag */
    input = output;
compile:	/* enter here if .i file specified */
    if (sflag) {
    	if (p2flag)
    	    output = setsuf(clist[i], 'a');
    	else
    	    output = setsuf(clist[i], 's');
    } else {
    	if (p2flag)
    	    output = setsuf(clist[i], 'a');
    	else
    	    output = setsuf(clist[i], 'z');
    }
    if (p2flag)
    	av[0] = "nbcp1"; 
    else
    	av[0] = "nbccom"; 
    av[1] = input; 
    av[2] = output; 
    nv = 3;
    if (lflag)
      av[nv++] = "-Xl";
    /* set input file name for ccom */
    av[nv++] = "-XF";
    av[nv++] = strip(lastfield(clist[i]));
    if (gflag)
      av[nv++] = "-Xg";
    if (_flag)
      av[nv++] = "-XJ";
    if (hflag)
      av[nv++] = "-XH";
    if (nflag)
      av[nv++] = "-X2N";
    if (wflag)
      av[nv++] = "-w";
    if (debug)
      av[nv++] = "-Xr";		/* show revision information */
    for (j = 0; j < nt; j++)
      av[nv++] = tlist[j];
    av[nv] = 0;
    strcpy(temppath, basepath);	/* copy base directory */
    if (p2flag)
    	strcat(temppath, cp1);	/* name of processor */
    else
    	strcat(temppath, ccom);	/* name of processor */
    if (callsys(temppath, av)) {
      exflag++;
      errflag++;
      if (!sflag)
	cunlink(output);
      if (getsuf(clist[i]) != 'i')
        cunlink(input); 
      continue;
    }

#ifdef TESTING
if(debug)
printf("NBCC: return from NBCCOM\n");
#endif
    /* unlink prog.i file */
    if (getsuf(clist[i]) != 'i')
      cunlink(input); 

    if (p2flag) {

    	input = output;
    	if (sflag)
    	    output = setsuf(clist[i], 's');
    	else
    	    output = setsuf(clist[i], 'z');
    	av[0] = "nbcp2"; 
    	av[1] = input; 
    	av[2] = output; 
    	nv = 3;
    	if (lflag)
    	    av[nv++] = "-X2l";
    	if (gflag)
    	    av[nv++] = "-X2g";
    	if (_flag)
    	    av[nv++] = "-X2J";
    	if (hflag)
    	    av[nv++] = "-X2H";
    	if (nflag)
    	    av[nv++] = "-X2N";
    	if (wflag)
    	    av[nv++] = "-X2w";
    	for (j = 0; j < nt; j++)
    	    av[nv++] = tlist[j];
    	av[nv] = 0;
    	strcpy(temppath, basepath);	/* copy base directory */
    	strcat(temppath, cp2);		/* name of processor */
    	if (callsys(temppath, av)) {
    	    exflag++;
    	    errflag++;
    	    if (!sflag)
    		cunlink(output);
    	    cunlink(input); 
    	    continue;
    	}
    	/* unlink prog.a file */
    	cunlink(input); 
    }

    input = output;
    /* if -S specified, skip to next program */
    if (sflag)
      continue;
assemble:
    av[0] = "nbcas"; 
    nv = 1;
    if (fflag)
/*      av[nv++] = "-F"; 08/01/94 fix */
      av[nv++] = "-E";	/* 08/01/94 fix */
    if (gflag)
      av[nv++] = "-G";
    if (mpx1xflag)
      av[nv++] = "-1";
    if (lflag) {
      av[nv++] = "-X";	/* do xref with listing */
      if (!listfile) {
        strcpy(list, "-L");
        strcat(list, setsuf(clist[i], 'L'));
        av[nv++] = list;
      }
    }
    if (cflag) {
      strcpy(obj, "-O");
      strcat(obj, setsuf(clist[i], 'o'));
      av[nv++] = obj;
    }
    /* assign user options */
    for (j = 0; j < na; j++)
      av[nv++] = alist[j];
    /* assign prefile, if present */
    if (pflag)
      av[nv++] = prefile;
    /* and finally, the input file */
    av[nv++] = input;
    av[nv] = 0;
/*
 *   assembler usually returns 1 on most errors.
 */
    strcpy(temppath, basepath);	/* copy base directory */
    strcat(temppath, as);	/* name of processor */
    if (callsys(temppath, av) != 0) {
      exflag++;
      errflag++;
      if (getsuf(clist[i]) != 's')
        cunlink(input); 
      continue;
    }
#ifdef TESTING
if(debug)
printf("NBCC: return from NBCAS\n");
#endif
    if (getsuf(clist[i]) != 's') 
      /* unlink prog.z file */
      cunlink(input); 

    /* this file done, do next */
    continue;

fort77:
   {
    int reg[8];
    struct psb *psbp = &psb;
    struct pta *ptap = &pta;
    char *rrsptr = (char *)var_rrs;	/* where we build rrs's for cataloger */

    /* for fortran, set option 1 2 3 4 */
    /* option 19 51 52 if -G */
    /* option 53 55 if -F */
    /* if no listing, set option 1. Output is to LCF=LO, file.L */
    /* if no object, set option 2. Output is to LFC=BO, file.O */
    ptap->optw = 0x0000000f;
    ptap->pgo2 = 0x00000000;
    if (fflag)			/* see if ieee wanted */
      ptap->pgo2 |= 0x00500000;	/* set options 53 & 55 */
    if (gflag) {		/* see if debugging */
      ptap->optw |= 0x00040000;	/* set option 19 */
      ptap->pgo2 |= 0x000c0000;	/* set options 51 & 52 */
    }

    if (cflag) {	/* user wants object */
      fortbo = setsuf(clist[i], 'o');
      ptap->optw |= 0x00000010;		/* set option 5, output to go */
      fortbo = cvtfname(fortbo);	/* get bo pathname */
#ifdef mpx
      unix2mpx(fortbo);			/* make mpx pathname */
#endif
      /* create bo file for object */
      close(open(fortbo, O_CREAT | O_WRONLY, 0666));
      if ((rrsptr = dorrs1(rrsptr, "GO ", fortbo)) == (char *)0) {
        error("can't create rrs entry for file %s", fortbo);
        dexit();
      }
      ptap->nrrs++;		/* cnt of rrs's built */
    } else {
      /* no binary file so assign to NULL */
      if ((rrsptr = dorrs3(rrsptr, "GO ", "NULL")) == (char *)0) {
        error("can't create rrs entry for file %s", "NULL");
        dexit();
      }
      ptap->nrrs++;		/* cnt of rrs's built */
    }

    if (lflag) {
      if (listfile) {
        fortlo = listfile;
      } else {
        fortlo = setsuf(clist[i], 'L');
      }
      ptap->optw &= ~0x0000000d;	/* clear option 1,3 & 4 */
      fortlo = cvtfname(fortlo);	/* get lo pathname */
#ifdef mpx
      unix2mpx(fortlo);			/* make mpx pathname */
#endif
      if (!listfile) {
	/* create lo file for listing */
        close(open(fortlo, O_CREAT | O_WRONLY, 0666));
      }
      if ((rrsptr = dorrs1(rrsptr, "LO ", fortlo)) == (char *)0) {
        error("can't create rrs entry for file %s", fortlo);
        dexit();
      }
      ptap->nrrs++;			/* cnt of rrs's built */
    } else {
      /* no list file so assign to NULL */
      if ((rrsptr = dorrs3(rrsptr, "LO ", "NULL")) == (char *)0) {
        error("can't create rrs entry for file %s", "NULL");
        dexit();
      }
      ptap->nrrs++;		/* cnt of rrs's built */
    }

    /* Now assign input file */
    fortsi = cvtfname(input);		/* get si pathname */
#ifdef mpx
    unix2mpx(fortsi);			/* make mpx pathname */
#endif
    if ((rrsptr = dorrs1(rrsptr, "SI ", fortsi)) == (char *)0) {
      error("can't create rrs entry for file %s", fortsi);
      dexit();
    }
    ptap->nrrs++;			/* cnt of rrs's built */

    /* assign BO to NULL device */
    if ((rrsptr = dorrs3(rrsptr, "BO ", "NULL")) == (char *)0) {
      error("can't create rrs entry for file %s", "NULL");
      dexit();
    }
    ptap->nrrs++;		/* cnt of rrs's built */

    /* assign UT to NULL device */
    if ((rrsptr = dorrs3(rrsptr, "UT ", "NULL")) == (char *)0) {
      error("can't create rrs entry for file %s", "NULL");
      dexit();
    }
    ptap->nrrs++;		/* cnt of rrs's built */

    /* assign the pathname for f77 */
    strcpy(temppath, basepath);		/* copy base directory */
    strcat(temppath, f77);		/* name of processor */
#ifdef mpx
    unix2mpx(temppath);			/* make mpx pathname */
#endif
    ptap->catpath = (char *)((strlen(temppath) << 24) | ((int)temppath));
    psbp->path = ptap->catpath;		/* psb pathname */
    ptap->rptr = (char *)var_rrs;	/* rrs definitions */
    ptap->rsiz = (rrsptr - ptap->rptr);	/* size of rrs in bytes */

    /* now activate fort77 for the users */
#ifdef mpx
    reg[1] = (int)ptap;		/* parameter activation block */
    reg[2] = (int)psbp;		/* parameter send block */
    mpxsvc(0x105f, reg, reg);	/* activate the compiler */
    /* see if fort77 activated O.K. */
    if (reg[6] != 0) {
      error("unable to activate FORT77: reason %d", reg[6]);
      dexit();
    }

    /* see if fort77 initial status O.K. */
    if (psbp->ist != 0) {
      error("unable to activate FORT77: status X%x", psbp->ist);
      dexit();
    }

    /* see if fort77 completed without error */    
    if (psbp->cst != 0) {
      error("FORT77 aborted: reason %d", psbp->cst);
      dexit();
    }
    
#else
    error("can't activate fort77 on unix", 0);
#endif
   }
   /* do next file */
  }

  /* now process all files in olist */
  /* for cataloging with NBCAT */
  if (oflag) {
    int reg[8];
    int ifd, ofd, cffd, rv, ic;
    int found = 0;
    char *tip, *top;
    struct psb *psbp = &psb;
    struct pta *ptap = &pta;
    char *rrsptr = (char *)var_rrs;	/* where we build rrs's for cataloger */

    ptap->nrrs = 0;			/* cnt of rrs's built */
    /* define SYC file assignment */
    /* define directives file */
    if (rflag) {			/* use user defined file */
    	strcpy(binpath, dirsname);	/* copy user's name */
    } else {
      /* path to cdirs in bin */
      strcpy(binpath, basepath);	/* copy base directory */
      if(f77flag)
	strcat(binpath, "fdirs");	/* name of directives file */
      else
	strcat(binpath, "cdirs");	/* name of directives file */
    }

#ifdef TESTING
if (debug)
printf("NBCAT processing: looking for cdirs in %s\n", binpath);
#endif
    /* binpath has name of user or default directives */
    /* create a temp file and copy in the directives, replacing */
    /* catalog/build command with name from -o option, (outfile) */
#ifdef TESTING
if (debug)
printf("NBCAT processing: created temp sys file %s\n", sycname);
#endif
#ifndef XXX
    strcpy(TMPname, SYCname);	/* copy in name */
    sycname = (char *)mktemp(TMPname);	/* make the name */
#else
    sycname = "SYC123456";	/* make the name */
#endif
#ifdef TESTING
if (debug)
printf("NBCAT processing: created temp sys file %s\n", sycname);
#endif
    /* create syc file for cataloger commands */
    if ((ofd = creat(sycname, 0666)) < 0) {
      error("can't create temp syc file %s", sycname);
      dexit();
    }
#ifdef mpx
    unix2mpx(binpath);			/* make mpx pathname */
#endif
#ifdef TESTING
if (debug)
printf("NBCAT processing: created temp sys file %s\n", sycname);
#endif
    /* now open directives file */
    if ((ifd = open(binpath, O_RDONLY)) < 0) {
      error("can't open directives file %s", binpath);
      close(ofd);		/* close temp file */
      cunlink(sycname);		/* unlink temp file */
      dexit();
    }
    /* now copy the directives file and replace LMNAME */
diread:
#ifdef mpx
    rv = readraw(ifd, ibuf, MAXN);
#else
#ifdef TESTING
if (debug)
printf("NBCAT processing: reading cdirs in %s\n", binpath);
#endif
    for (ic=0; ic<MAXN; ic++) {
      rv = read(ifd, &ibuf[ic], 1);
      if (rv <= 0)
        break;
      if (ibuf[ic] == '\n') {
        rv = ic;
        break;
      }
    }
#endif
    if (rv <= 0) {		/* we are at EOF on dir file */
      if (!found) {
gotbcerr:
    	error("can't find build/catalog directive in file %s", binpath);
    	close(ifd);		/* close input file */
    	close(ofd);		/* close temp file */
    	cunlink(sycname);	/* unlink temp file */
    	dexit();
      }
      goto dosycrrs;
    }
ibuf[rv] = '\0';		/* null terminate */
#ifdef TESTING
if (debug)
printf("NBCAT processing: cdirs line %d:%s\n", rv, ibuf);
#endif
    /* look for catalog/build directive */
    if (rv > 4) {		/* at least 4 char for build/catalog */
      ibuf[rv] = '\0';		/* null terminate */
      if ((strncmp(ibuf, "CATA", 4) == 0) || (strncmp(ibuf, "BUIL", 4) == 0)) {
    	/* found it, now skip to filename and replace */
    	if ((tip = strchr(ibuf, ' ')) == (char *)0)
    	  /* blank not found, give error and quit */
    	  goto gotbcerr;
    	tip++;			/* past blank */
    	memset(tbuf, '\0', MAXN);	/* clear buffer */
    	/* copy directive to temp buf with following blank */
    	strncpy(tbuf, ibuf, (tip - ibuf));
    	strcat(tbuf, outfile);	/* put in the current name */
    	/* backup and skip blanks until start of name */
    	for (tip--; *tip == ' '; tip++);
    	/* now skip name to eol or blank */
    	for ( ; *tip && *tip != ' '; tip++);
    	/* tip points to blank or eol(0) */
    	if (*tip) {		/* more text, copy it */
    	  strcat(tbuf, tip);	/* add in user text */
    	}
    	strcpy(ibuf, tbuf);	/* copy back to original buffer */
    	rv = strlen(ibuf);	/* set new length */
    	found = 1;		/* show we found it */
      }
/*      ibuf[rv] = '\n';		/* put l/f back on for unix */
    }
    ibuf[rv] = '\n';		/* put l/f back on for unix */
    ibuf[rv+1] = '\0';		/* Null terminate for unix */
#ifdef TESTING
if(debug)
printf("NBCAT processing 2: cdirs line %d:%s", rv, ibuf);
#endif

    /* write out the line */
#ifdef mpx
    rv = writraw(ofd, ibuf, rv);
#else
    rv = write(ofd, ibuf, rv+1);
#endif
    goto diread;		/* go read more input */

dosycrrs:			/* copy complete */
    sycname = cvtfname(sycname);	/* get syc pathname */
    close(ifd);			/* close input file */
    close(ofd);			/* close temp file */
#ifdef mpx
    unix2mpx(sycname);		/* make mpx pathname */
#endif
#ifdef TESTING
if(debug)
printf("NBCAT processing SYC file %s\n", sycname);
#endif
    if ((rrsptr = dorrs1(rrsptr, "SYC", sycname)) == (char *)0) {
      error("can't create rrs entry for file %s", sycname);
      cunlink(sycname);		/* unlink temp file */
      dexit();
    }
    ptap->nrrs++;		/* cnt of rrs's built */

#ifdef TESTING
if(debug)
printf("NBCAT processing UT file %s\n", "NULL");
#endif
    if ((rrsptr = dorrs3(rrsptr, "UT ", "NULL")) == (char *)0) {
    	error("can't create rrs entry for file %s", "NULL");
    	if (!tflag && no > 0)	/* unlink temp file */
    	  cunlink(sgoname);
    	cunlink(sycname);	/* unlink temp file */
    	dexit();
    }
    ptap->nrrs++;		/* cnt of rrs's built */

    /* define SGO file assignment */
    /* get name of file to use for objects */
    if(!tflag && no > 0) {	/* if not user specified, make name */
      /* we have command line objects and no user temp file */
#ifndef XXX
      strcpy(TMPname, SGOname);	/* copy in name */
      sgoname = (char *)mktemp(TMPname);	/* make the name */
#else
      sgoname = "SGO123456";	/* make the name */
#endif
      /* create sgo file for compressed object */
      if ((ofd = creat(sgoname, 0666)) < 0) {
    	error("can't create temp sgo file %s", sgoname);
    	cunlink(sycname);	/* unlink syc temp file */
    	dexit();
      }
      close(ofd);		/* close, so we can open in binary mode */
    }

#ifdef TESTING
if(debug)
printf("NBCAT processing SGO file %s\n", sgoname);
#endif
    /* if we have command line objects, open temp file */
    if (no > 0) {
      /* see if we can open user or temp file in binary mode */
      if ((ofd = open(sgoname, O_BIN | O_WRONLY)) < 0) {
        error("can't open temp sgo file %s", sgoname);
        if (!tflag && no > 0)	/* unlink temp file */
    	  cunlink(sgoname);
        cunlink(sycname);	/* unlink syc temp file */
        dexit();
      }
      /* copy object files to output */
      /* do any files on command line */
      for (ic = 0; ic < no; ic++) {
        if((cffd = open(olist[ic], O_BIN | O_RDONLY)) < 0) {
    	  error("can't open object file %s", olist[ic]);
    	  /* just ignore */
    	  continue;
        }
#ifdef TESTING
if(debug)
printf("NBCAT processing object file %s\n", olist[ic]);
#endif
        copyobj(cffd, ofd, olist[ic]);	/* copy the file */
      }
      /* now see if user also specified a compressed object file */
      /* copy it also */
      if (zflag) {
        if((cffd = open(usersgo, O_BIN | O_RDONLY)) < 0) {
    	  error("can't open object file %s", usersgo);
    	  /* just ignore */
        } else {
#ifdef TESTING
if(debug)
printf("NBCAT processing compressed object file %s\n", usersgo);
#endif
          copyobj(cffd, ofd, usersgo);	/* copy the file */
        }
      }
#ifndef mpx
      mpxbb(ofd, obuf, 120, 1);		/* last write to output */
#endif
      close(ofd);			/* close output */
      /* at this point, sgoname points to file containing *
      /* all of the object, go assign sgo rrs */
    } else {			/* no cmd line obj, see if user sgo */
      if (!zflag) {		/* if no sgo, we got no object */
        error("no object files specified", 0);
        if (!tflag && no > 0)	/* unlink temp file */
    	  cunlink(sgoname);
        cunlink(sycname);	/* unlink syc temp file */
        dexit();
      }
      /* set sgoname to point to usersgo */
      sgoname = usersgo;
    }
    sgoname = cvtfname(sgoname);	/* get sgo pathname */
#ifdef mpx
    unix2mpx(sgoname);		/* make mpx pathname */
#endif
#ifdef TESTING
if(debug)
printf("NBCAT processing SGO object file %s\n", sgoname);
#endif
    if ((rrsptr = dorrs1(rrsptr, "SGO", sgoname)) == (char *)0) {
      error("can't create rrs entry for file %s", sgoname);
      if (!tflag && no > 0)	/* unlink temp file */
    	cunlink(sgoname);
      cunlink(sycname);		/* unlink temp file */
      dexit();
    }
    ptap->nrrs++;		/* cnt of rrs's built */

    /* now assign SLO to NULL or user specified SLO file */
    if (yflag) {		/* do user specified file */
    userslo = cvtfname(userslo);	/* get sgo pathname */
#ifdef mpx
    unix2mpx(userslo);		/* make mpx pathname */
#endif
#ifdef TESTING
if(debug)
printf("NBCAT processing SLO file %s\n", userslo);
#endif
      if ((rrsptr = dorrs1(rrsptr, "SLO", userslo)) == (char *)0) {
    	error("can't create rrs entry for file %s", userslo);
        if (!tflag && no > 0)	/* unlink temp file */
    	  cunlink(sgoname);
    	cunlink(sycname);	/* unlink temp file */
    	dexit();
      }
      ptap->nrrs++;		/* cnt of rrs's built */
    } else {			/* do null assignment */
#ifdef TESTING
if(debug)
printf("NBCAT processing SLO file %s\n", "NULL");
#endif
      if ((rrsptr = dorrs3(rrsptr, "SLO", "NULL")) == (char *)0) {
    	error("can't create rrs entry for file %s", "NULL");
    	if (!tflag && no > 0)	/* unlink temp file */
    	  cunlink(sgoname);
    	cunlink(sycname);	/* unlink temp file */
    	dexit();
      }
      ptap->nrrs++;		/* cnt of rrs's built */
    }

    /* now assign any libs for user */
    for (ic = 0; ic < nl; ic++) {
      char lfc[4];

      sprintf(lfc, "L%2.2d", ic);	/* make lfc */
      strcpy(ibuf, llist[ic]);		/* copy the file name */
      if(!strcasecmp(lastfield(ibuf), "mpx"))f77flag++;
      strcat(ibuf, "lib");		/* lib to prefix */
#ifdef mpx
      unix2mpx(ibuf);			/* make mpx pathname */
#endif
#ifdef TESTING
if(debug)
printf("NBCAT processing %s library file %s\n", lfc, ibuf);
#endif
      if ((rrsptr = dorrs1(rrsptr, lfc, ibuf)) == (char *)0) {
    	error("can't create rrs entry for file %s", ibuf);
    	if (!tflag && no > 0)	/* unlink temp file */
    	  cunlink(sgoname);
    	cunlink(sycname);	/* unlink temp file */
    	dexit();
      }
      ptap->nrrs++;		/* cnt of rrs's built */
      sprintf(lfc, "D%2.2d", ic);	/* make lfc */
      strcpy(ibuf, llist[ic]);	/* copy the file name */
      strcat(ibuf, "dir");	/* dir to prefix */
#ifdef mpx
      unix2mpx(ibuf);		/* make mpx pathname */
#endif
#ifdef TESTING
if(debug)
printf("NBCAT processing %s directory file %s\n", lfc, ibuf);
#endif
      if ((rrsptr = dorrs1(rrsptr, lfc, ibuf)) == (char *)0) {
    	error("can't create rrs entry for file %s", ibuf);
    	if (!tflag && no > 0)	/* unlink temp file */
    	  cunlink(sgoname);
    	cunlink(sycname);	/* unlink temp file */
    	dexit();
      }
      ptap->nrrs++;		/* cnt of rrs's built */
    }

    /* now assign CLIB/CDIR */
    /* path to clb in bin */
    strcpy(ibuf, basepath);	/* copy base directory */
    strcat(ibuf, "clb");	/* name of lib file */
#ifdef mpx
    unix2mpx(ibuf);		/* make mpx pathname */
#endif
#ifdef TESTING
if(debug)
printf("NBCAT processing %s library file %s\n", "LIS", ibuf);
#endif
    if ((rrsptr = dorrs1(rrsptr, "LIS", ibuf)) == (char *)0) {
      error("can't create rrs entry for file %s", ibuf);
      if (!tflag && no > 0)	/* unlink temp file */
    	cunlink(sgoname);
      cunlink(sycname);	/* unlink temp file */
      dexit();
    }
    ptap->nrrs++;		/* cnt of rrs's built */

    /* path to cdr in bin */
    strcpy(ibuf, basepath);	/* copy base directory */
    strcat(ibuf, "cdr");	/* name of lib file */
#ifdef mpx
    unix2mpx(ibuf);		/* make mpx pathname */
#endif
#ifdef TESTING
if(debug)
printf("NBCAT processing %s directory file %s\n", "LID", ibuf);
#endif
    if ((rrsptr = dorrs1(rrsptr, "LID", ibuf)) == (char *)0) {
      error("can't create rrs entry for file %s", ibuf);
      if (!tflag && no > 0)	/* unlink temp file */
    	cunlink(sgoname);
      cunlink(sycname);	/* unlink temp file */
      dexit();
    }
    ptap->nrrs++;		/* cnt of rrs's built */

    /* assign the pathname for nbcat */
    strcpy(temppath, basepath);		/* copy base directory */
    if(f77flag)
      strcat(temppath, fld);		/* name of processor */
    else
      strcat(temppath, ld);		/* name of processor */
#ifdef mpx
    unix2mpx(temppath);			/* make mpx pathname */
#endif
    ptap->catpath = (char *)((strlen(temppath) << 24) | ((int)temppath));
    psbp->path = ptap->catpath;		/* psb pathname */

    /* set the option word to 19 25 */
    ptap->optw = 0x01040000;
    ptap->pgo2 = 0x00000000;
    ptap->rptr = (char *)var_rrs;		/* rrs definitions */
    ptap->rsiz = (rrsptr - ptap->rptr);		/* size of rrs in bytes */

#ifdef TESTING
if(debug)
printf("%d rrs's defined, 0x%x bytes of rrs's.\n", ptap->nrrs, ptap->rsiz);
#endif
    /* now activate nbcat for the users */
#ifdef mpx
    reg[1] = (int)ptap;		/* parameter activation block */
    reg[2] = (int)psbp;		/* parameter send block */
    mpxsvc(0x105f, reg, reg);	/* activate the cataloger */
    /* see if nbcat activated O.K. */
    if (reg[6] != 0) {
      error("unable to activate %s: reason %d", temppath, reg[6]);
      if (!tflag && no > 0)	/* unlink temp file */
    	cunlink(sgoname);
      cunlink(sycname);		/* unlink temp file */
      dexit();
    }
    /* see if nbcat initial status O.K. */
    if (psbp->ist != 0) {
      error("unable to activate NBCAT: status X%x", psbp->ist);
      if (!tflag && no > 0)	/* unlink temp file */
    	cunlink(sgoname);
      cunlink(sycname);		/* unlink temp file */
      dexit();
    }
    /* see if nbcat completed without error */    
    if (psbp->cst != 0) {
      error("NBCAT aborted: reason %d", psbp->cst);
      if (!tflag && no > 0)	/* unlink temp file */
    	cunlink(sgoname);
      cunlink(sycname);		/* unlink temp file */
      dexit();
    }
    
#else
    error("can't activate cataloger on unix", 0);
#endif
    if (!tflag && no > 0)	/* unlink temp file */
      cunlink(sgoname);
    cunlink(sycname);		/* unlink temp file */

#ifdef TESTING
if(debug)
printf("NBCAT processing completed %s\n", temppath);
#endif
    /* WE IS DONE!!!!! */
  }

nocom:
  dexit();
}

/* build an rrs type 1 entry */
/* doubleword bound output pointer on return */
char *dorrs1(rrsp, lfc, fnp)
struct rrs1 *rrsp;
char *lfc;
char *fnp;
{
    int sl = strlen(fnp);	/* length of pathname */
    char *retp = (char *)(rrsp);	/* char pointer to be returned */

    memset((char *)rrsp, '\0', 4*6);	/* clear 6 wds of rrs */
    rrsp->lfc0 = lfc[0];	/* insert lfc */
    rrsp->lfc1 = lfc[1];
    rrsp->lfc2 = lfc[2];
    rrsp->type = 1;		/* type 1 rrs */
    rrsp->size = 4 + ((sl + 7)/8) * 2;  /* dw bounded size */
    rrsp->plen = sl;		/* pathname length */
    memset(rrsp->path, ' ', ((sl + 7) / 8) * 8);	/* clear pathname */
    memcpy(rrsp->path, fnp, sl);	/* copy in name */
#ifdef TESTING
    if (debug) {
    	printf("RRS type 1\n");
    	printf("lfc = %c%c%c\n", rrsp->lfc0, rrsp->lfc1, rrsp->lfc2);
    	printf("type = %d size = %x plen = %x\n", rrsp->type, rrsp->size, rrsp->plen);
    	printf("access = %x\n", rrsp->accs);
    	printf("options = %x\n", rrsp->opts);
    	printf("path = %s\n", fnp);
    }
#endif
    return retp + (rrsp->size * 4);
}

/* build an rrs type 4 entry */
/* doubleword bound output pointer on return */
char *dorrs4(rrsp, lfc, lfc2)
struct rrs4 *rrsp;
char *lfc;
char *lfc2;
{
    char *retp = (char *)rrsp;	/* char pointer to be returned */

    memset((char *)rrsp, '\0', 4*4);	/* clear rrs */
    rrsp->lfc0 = lfc[0];	/* insert first lfc */
    rrsp->lfc1 = lfc[1];
    rrsp->lfc2 = lfc[2];
    rrsp->sfc0 = lfc2[0];	/* insert second lfc */
    rrsp->sfc1 = lfc2[1];
    rrsp->sfc2 = lfc2[2];
    rrsp->type = 4;		/* type 4 rrs */
    rrsp->size = 4;		/* dw bounded size */
    return retp + (rrsp->size * 4);
}

/* build an rrs type 3 entry */
/* doubleword bound output pointer on return */
char *dorrs3(rrsp, lfc, fnp)
struct rrs3 *rrsp;
char *lfc;
char *fnp;
{
    char *retp = (char *)rrsp;	/* char pointer to be returned */

    if (strcmp(fnp, "NULL"))	/* if not null, can't handle */
    	return (char *)0;	/* return error */
    memset((char *)rrsp, '\0', 4*6);	/* clear rrs */
    rrsp->lfc0 = lfc[0];	/* insert lfc */
    rrsp->lfc1 = lfc[1];
    rrsp->lfc2 = lfc[2];
    rrsp->type = 3;		/* type 3 rrs */
    rrsp->size = 6;		/* dw bounded size */
    rrsp->dt3 = 15;		/* null device */
#ifdef TESTING
    if (debug) {
    	printf("RRS type 3\n");
    	printf("lfc = %c%c%c\n", rrsp->lfc0, rrsp->lfc1, rrsp->lfc2);
    	printf("type = %d size = %x den = %x\n", rrsp->type, rrsp->size, rrsp->dens);
    	printf("access = %x\n", rrsp->accs);
    	printf("options = %x\n", rrsp->opts);
    	printf("dt = %d vol = %x chn = %x subc = %x\n", rrsp->dt3, rrsp->vlnum, rrsp->chn3, rrsp->schn3);
    	printf("unit id = %x\n", rrsp->unfid);
    }
#endif
    return retp + (rrsp->size * 4);
}

#if defined(linux) || defined(__alpha)
void idexit()
#else
idexit()
#endif
{

  if (eflag)
    cunlink(setsuf(clist[inx], 'i'));
  if (cflag)
    cunlink(setsuf(clist[inx], 'o'));
  if (lflag)
    cunlink(setsuf(clist[inx], 'L'));
  if (p2flag)
    cunlink(setsuf(clist[inx], 'a'));
  if (sflag)
    cunlink(setsuf(clist[inx], 's'));
  else
    cunlink(setsuf(clist[inx], 'z'));
  if (oflag) {
    if (!tflag && no > 0)	/* unlink temp file */
      cunlink(sgoname);
    cunlink(sycname);		/* unlink temp file */
  }
  errflag = 100;
  dexit();
}

void dexit()
{
  exit(errflag);
}

void error(s, x)
char *s, *x;
{
  FILE *diag = exflag ? stderr : stdout;

  fprintf(diag, "nbcc: ");
  fprintf(diag, s, x);
  putc('\n', diag);
  exfail++;
  errflag++;
}

/* get suffix of the filename, c or s */
int getsuf(s)
register char *s;
{
  register int c;
  register int t;

  c = 0;
  while (t = *s++)
    switch (t) {
      case '@':
      case '^':
      case '(':
      case ')':
      case '/':
        c = 0;
	continue;
      default:
        c++;
    }
  s -= 3;
  if (c <= MAXNAMLEN && c > 2 && *s++ == '.')
    return (tolower(*s));
  return (0);
}

char *
setsuf(pas, ch)
char *pas;
char ch;
{
  register char *s, *s1;
  register char c;

  s = s1 = savestr(pas);
  while (*s)
    if ((c = *s++) == '/' || c == ')')
      s1 = s;
  s[-1] = ch;
/*  s[-1] = tolower(ch); */
  return (s1);
}

int callsys(f, v)
char *f, **v;
{
  int t, status;

  if(debug)
    prexec(f, v, 0, 0);

#ifndef mpx
  t = fork();
  if (t == -1) {
    printf("No more processes\n");
    return (100);
  }
  if (t == 0) {
    execv(f, v);
    printf("Can't find %s\n", f);
    fflush(stdout);
    _exit(100);
  }
  while (t != wait(&status))
    ;
  if ((t=(status&0377)) != 0 && t!=14) {
    if (t!=2) {
      printf("Fatal error in %s\n", f);
      errflag = 8;
    }
    return(1);
  }
  return ((status>>8) & 0377);
#else
  if ((t = vexecv(f, v)) == -1) {
    printf("Can't find %s\n", f);
    fflush(stdout);
    idexit(1);
  }
  if (t == 0) {
    return (0);	/* all was a ok */
  }
  printf("Fatal error in %s\n", f);
  errflag = 8;
  return (1);	/* to shutup warnings */

#endif
}

int nodup(l, os)
char **l, *os;
{
  register char *t, *s;
  register int c;

  s = os;
  if (getsuf(s) != 'o')
    return (1);
  while (t = *l++) {
    while (c = tolower(*s++))
      if (c != tolower(*t++))
        break;
    if (*t==0 && c==0)
      return (0);
    s = os;
  }
  return (1);
}

#define NSAVETAB 1024
char *savetab;
int saveleft;

char *
savestr(cp)
register char *cp;
{
  register int len;

  len = strlen(cp) + 1;
  if (len > saveleft) {
    saveleft = NSAVETAB;
    if (len > saveleft)
      saveleft = len;
    savetab = (char *)malloc(saveleft);
    if (savetab == 0) {
      fprintf(stderr, "ran out of memory (savestr)\n");
      idexit(1);
    }
  }
  strncpy(savetab, cp, len);
  cp = savetab;
  savetab += len;
  saveleft -= len;
  return (cp);
}

char *
strspl(left, right)
char *left, *right;
{
  char buf[BUFSIZ];

  strcpy(buf, left);
  strcat(buf, right);
  return (savestr(buf));
}

void prexec(f, v, si, so)
char f[], *v[], *si, *so;
{
  int i;

  printf("%s ", f);
  for(i=1; v[i]; i++) {
    printf("%s ", v[i]);
  }
  if(si) printf(" <%s ", si);
  if(so) printf(" >%s ", so);
  printf("\n");
  fflush(stdout);
}

char *
strip(s)
char *s;
{
    register char *ns;
    register char *t, *dot;

    ns = savestr(s);
    for (t = ns; *t ; ++t)
    	if (*t == '.')
    	    dot = t;
    *dot = '\0';
    return ns;
}

char *
lastfield(s)
register char *s;
{
    register char *t;
    for (t = s; *s ; ++s)
    	if (*s == '/' || *s == ')')
    	    t = s+1;
    return(t);
}

/* copy object file */
int copyobj(infd, outfd, file)
int infd;
int outfd;
char *file;
{
    int dffound;
    int nr;
    char *dp;

    dffound = 0;		/* no df record yet */
#ifndef mpx
    bin = 0;			/* starting new file */
#endif

    /* copy object to output */
readobj:
    dp = obuf;
#ifdef mpx
    nr = readraw(infd, dp, 120);
#else
    nr = readbb(infd, dp, 120);
#endif
    if(nr <= 0) {		/* if eof, we done */
    	close(infd);
    	if(dffound) {
    	    return(0);
    	} else {
    	    error("unexpected EOF on file %s", file);
    	    return(-1);
    	}
    }
    if(((*dp & 0xff) != 0xdf) && ((*dp & 0xff) != 0xff)) {
    	error("bad object file %s", file);
    	close(infd);
    	/* just ignore */
    	return(-1);
    }
    if((*dp & 0xff) == 0xdf)	/* last record */
    	dffound = 1;		/* df record found */
    else
    	dffound = 0;		/* df record not found */
#ifdef mpx
    nr = writraw(outfd, dp, 120);
#else
    nr = mpxbb(outfd, dp, 120, 0);
#endif
    if(nr <= 0) {
    	error("error writing object output file");
    	close(infd);
    	close(outfd);
    	idexit(2);		/* we done */
    }
    /* record exhausted, get next record */
    goto readobj;
    /*NOREACHED*/
}

#ifndef mpx
static	unsigned  char	bb[BLKSIZE];	/* blocking buffer */
static	char	first = 0;		/* 1st time thru flag */

/*
 * mpxbb - make up mpx block file output
 * input - buffer address
 *	 - byte count
 */

int
mpxbb(fd, buf, cnt, last)
int	fd;
unsigned char	*buf;
int	cnt;
int	last;
{
    int	boff;			/* next write address offset */

    if (!first) {			/* is this 1st time thru */
    	first = 1;			/* set the flag */
    	memset (bb, '\0', BLKSIZE);	/* zero the buffer */
    	bb[3] = 4;			/* next write byte offset */
    	bb[4] = 0x60;			/* set beg/end of block */
    	bb[5] = 0;			/* 1st block count is 0 bytes */
    }
    boff = (bb[2] << 8) | (bb[3]);	/* get next write address offset */
    if (last)
    	goto alldone;			/* close out the file */
    /* see if enough room in buffer for this record */
    /* add current offset + 2 (for last record info) plus new */
    /* record size plus 4 (2 for this rec, 2 for last) */
    if ((boff + 2 + cnt + 4) >= BLKSIZE) {
    	/* not enough space, write out this record */
    	if (write(fd, bb, BLKSIZE) < 0)
    	    return(-1);
    	memset (bb, '\0', BLKSIZE);	/* zero the buffer */
    	bb[4] = 0x60;			/* set beg/end of block */
    	bb[5] = 0;			/* 1st block count is 0 bytes */
					/* after 1st write */
    	boff = 4;			/* init count at 4 bytes */
    }
    /* we have enough room, move in the record */
    /* clear last record end of block flag, set up this record *
    /* info and last rec info at end of data, and update cnt */
    bb[boff] &= ~0x20;			/* clear end of block flag */
    bb[boff+2] = 0x00;			/* clear this blocks flags */
    bb[boff+3] = cnt;			/* set this record count */
    memcpy(&bb[boff+4], buf, cnt);	/* copy in the data */
    boff += (cnt+4);			/* update count */
    bb[boff] = 0x20;			/* set eob status flag */
    bb[boff+1] = cnt;			/* set last rec byte count */
    bb[2] = (boff & 0xff00) >> 8;	/* set hi byte of count */
    bb[3] = (boff & 0xff);		/* set lo byte of count */
    return(cnt);			/* done */

alldone:
    /* that was the last record, set eof flag in bb, write it and exit */
    /* see if enough room in buffer for EOM record */
    /* add current offset + 2 (for last record info) plus new */
    /* EOF record size of 4 (2 for this rec, 2 for last) */
    if ((boff + 2 + 4) >= BLKSIZE) {
    	/* not enough space, write out this record */
    	if (write(fd, bb, BLKSIZE) < 0)
    	    return(-1);
    	memset (bb, '\0', BLKSIZE);	/* zero the buffer */
    	bb[4] = 0x60;			/* set beg/end of block */
    	bb[5] = 0;			/* 1st block count is 0 bytes */
					/* after 1st write */
    	boff = 4;			/* init count at 4 bytes */
    }
    bb[boff] &= ~0x20;			/* clear end of block flag */
/*  bb[boff+2] = 0x80;			/* clear this blocks flags */
    bb[boff+2] = 0xa0;			/* clear this blocks flags */
    bb[boff+3] = 0;			/* set record count of 0 */
    bb[boff+4] = 0xa0;			/* set EOF/EOB flags */
    boff += 4;				/* 4 more bytes */
    bb[2] = (boff & 0xff00) >> 8;	/* set hi byte of count */
    bb[3] = (boff & 0xff);		/* set lo byte of count */
    /* write out EOF record */
    if (write(fd, bb, BLKSIZE) < 0)
    	return(-1);
    first = 0;				/* reset 1st time flag */
    return(cnt);			/* get out, done */
}

/*
 * This function reads MPX blocked files
 */

int readbb (fd, ip, cnt)
int	fd;
char 	*ip;
int	cnt;
{
    int c;
    int i = 0;

    if (bin == 0) {
    	read(fd, si, BLKSIZE);
    	bin = 6;
    }
    /* check for EOF */
    if (si[bin] & 0x80) {
    	bin = 0;
    	return(0);		/* we have EOF */
    }
    /* check for EOB in last record */
    if (si[bin - 2] & 0x20) {
    	read(fd, si, BLKSIZE);	/* we have EOB */
    	bin = 6;
    }
    if ((c = si[bin+1]) > 0) {
    	for (i = 0; i < c; i++) {
    	    ip[i] = si[bin + 2 + i];
    	    if (i >= cnt)
    		break;
    	}
    	bin += (c + 4);
    	return (i);
    }
    bin = 0;
    return (i);
}
#endif /* mpx */

/* cvtfname
 * convert an arbitrary filename to a qualified unix pathname.
 * return pointer to malloc'd name or null if error.
 */
static char *
cvtfname(path)
char *path;
{
    char *dirp, *retp;

#ifdef mpx
    /* make sure pathname is l/c */
    str2lc(path);
#endif
    /* get default working directory */
    dirp = getcwd(0, MAXN);
    retp = pathname(dirp, path);
    if (dirp)
    	free(dirp);
    return(retp);
}

/* Convert relative to absolute pathnames */

/* Given a working directory and an arbitrary pathname, resolve them into
 * an absolute pathname. Memory is allocated for the result, which
 * the caller must free
 */
static char *
pathname(cd,path)
char *cd;	/* Current working directory */
char *path;	/* Pathname argument */
{
    register char *buf;

    if(cd == (char *)0 || path == (char *)0)
    	return (char *)0;

    /* Strip any leading white space on args */
    while(*cd == ' ' || *cd == '\t')
    	cd++;
    while(*path == ' ' || *path == '\t')
    	path++;

    /* Allocate and initialize output buffer; user must free
     * add fudge factor to malloc size in case user specified
     * just a / and we must replace it with /system/system
     */
    buf = (char *)malloc((unsigned)strlen(cd) + strlen(path) + 16);
    buf[0] = '\0';

    /* Interpret path relative to cd only if it doesn't begin with "/" */
    /* for MPX also see if @, ^, or ( */
    if(*path == '/'
#ifdef mpx
      || *path == '@' || *path == '^' || *path == '('
#endif
      ) {
    	crunch(buf,path);
    } else {
    	crunch(buf,cd);
    	crunch(buf,path);
    }

    /* Special case: null final path means the root directory */
    if(buf[0] == '\0'){
    	buf[0] = '/';
    	buf[1] = '\0';
    }
#ifdef mpx
    /* now convert to a qualified unix name if it was entered
     * as an MPX name
     */
    conv2unix(buf);
#endif

    return buf;
}

/* Process a path name string, starting with and adding to
 * the existing buffer
 */
static void
crunch(buf,path)
char *buf;
register char *path;
{
    register char *cp;
	
    cp = buf + strlen(buf);	/* Start write at end of current buffer */
	
    /* Now start crunching the pathname argument */
    for(;;){
    	/* Strip leading /'s; one will be written later */
    	while(*path == '/')
    	    path++;
    	if(*path == '\0')
    	    break;		/* no more, all done */
    	/* Look for parent directory references, either at the end
    	 * of the path or imbedded in it
    	 */
    	if(strcmp(path,"..") == 0 || strncmp(path,"../",3) == 0) {
    	    /* Hop up a level */
    	    if((cp = strrchr(buf,'/')) == (char *)0)
    		cp = buf;		/* Don't back up beyond root */
    		*cp = '\0';		/* In case there's another .. */
    		path += 2;		/* Skip ".." */
    		while(*path == '/')	/* Skip one or more slashes */
    		    path++;
    		/* Look for current directory references, either at the end
    		 * of the path or imbedded in it
    		 */
    	} else if(strcmp(path,".") == 0 || strncmp(path,"./",2) == 0) {
    	    /* "no op" */
    	    path++;			/* Skip "." */
    	    while(*path == '/')		/* Skip one or more slashes */
    		path++;
    	} else {
    	    /* Ordinary name, copy up to next '/' or end of path */
#ifdef mpx
    if(cp == buf && (*path == '@' || *path == '^' || *path == '(')) {
    } else
#endif
    	    *cp++ = '/';
    	    while(*path != '/' && *path != '\0')
    		*cp++ = *path++;
    	}
    }
    *cp++ = '\0';
}

#ifdef mpx
/* convert unix or mpx filename to unix filename */
/* .'s and multiple /'s will have been removed by crunch above */
/* first char must be /, ., @, ^, or ( to be converted */
/* NOTE: string supplied must be big enough for conversion */

static void
conv2unix(s)
register char *s;
{
    register char *os = s;
    char *tp;

    if (s == 0 || *s == 0)return;
    	switch (*os) {
    	    case '/':		/* path starts with /, leave it */
    		/* check for just a '/', if yes, give /system/system */
    		if (*++os == '\0') {	/* see if just a '/' */
    		    strcat(os, "system/system"); /* copy in root */
    		    return;		/* we are done */
    		}
    		return;		/* done with conversion */

    	    case '^':		/* path starts with ^ put in /curvol */
    		getcwvd();	/* get current working vol, dir */
    		/* move over other "stuff" to make room for vol */
    		bcopy(&os[1], os+strlen(curvol)+1, strlen(os));
    		blcpy(curvol, os+1, strlen(curvol));
    		/* go to process dir name, if any */
    		goto dodir;

    	    case '(':		/* path starts with ( put in /curvol */
    		getcwvd();	/* get current working vol, dir */
    		/* move over other "stuff" to make room for vol */
    		bcopy(os, os+strlen(curvol)+1, strlen(os)+1);
    		blcpy(curvol, os+1, strlen(curvol));
    		/* drop thru to process dir name, if any */

    	    case '@':		/* path starts with @ put in / */
dodir:
    		*os++ = '/';
    		/* check for just an '@', if yes, give /system */
    		if (*os == '\0') {	/* see if just a '@' */
    		    strcat(os, "system/system"); /* copy in root */
    		    return;		/* we are done */
    		}
    		/* check to see if @vol^dir or @vol^(dir) */
    		if (tp = strchr(os, '^')) {       /* got end of vol */
    		    /* check to see if next char is '('.  If yes,
    		     * just delete the ^ and continue
    		     */
    		    if (tp[1] == '(') {		/* see if '(' */
    			bcopy(&tp[1], tp, strlen(tp));
    		    } else {
    			*tp++ = '/';	/* terminate volume name */
    		    }
    		    os = tp;		/* next char in input */
    		}
    		if (tp = strchr(os, '(')) {	/* got end of vol */
    		    *tp++ = '/';	/* terminate volume name */
    		    os = tp;		/* next char in input */
    		    if (tp = strchr(os, ')')) {  /* get end of dir */
    			if (tp[1] == '\0')  /* see if a file name */
    			    *tp = '\0';	/* no, leave off last / */
    			else
    			    *tp++ = '/';    /* terminate directory */
    			os = tp;        /* start of file name or null */
    		    } else {		/* have /vol/, will get error */
    			return;
    		    }
    		} else {		/* have /vol, just wants volume */
    		    return;
    		}
    		return;			/* done with conversion */

    	    case '.' :            /* curr directory? */
    		if (os[1] == '.') { /* have .. now what? */
    		    if (os[2] == '/') { /* have ../ put in cur vol */
    			getcwvd();	/* get current working vol, dir */
    			bcopy(&os[3], os+strlen(curvol)+2, strlen(os) - 1);
    			*os++ = '/';
    			blcpy(curvol, os, strlen(curvol));
    			os += (strlen(curvol)+1);
    			*os++ = '/';
    			return;
    		    }
    		    if (os[2] == 0) { /* have just .. give vol */
    			getcwvd();	/* get current working vol, dir */
    			*os++ = '/';
    			strlcpy (os, curvol);
    			os += strlen(curvol);
    			*os++ = '\0';        /* end of volume */
    			return;          /* return /vol */
    		    }
    		    return;            /* have ..? just an error */
    		}
    		if (os[1] == '/') {  /* have ./, just curr dir */
    		    /* copy down file name */
    		    bcopy(&os[2], os, strlen(os));
    		    return;
    		}
    		if (os[1] == 0) {    /* have just ., return curr dir */
    		    *os++ = '/';
    		    getcwvd();	/* get current working vol, dir */
    		    strlcpy(os, curvol); /* copy in volume */
    		    os += strlen(curvol);
    		    *os++ = '/';        /* start of dir */
    		    strlcpy(os, curdir); /* copy in dir */
    		    os += strlen(curdir);
    		    *os++ = '\0';        /* terminate dir */
    		    return;
    		}
    		return;              /* have .? just an error */
    	    default:
    		return;              /* everything else o.k. */
    	}
}

/*
 * copy string p2 to string p1, converting to l/c as we go.
 */
static void
strlcpy(p1, p2)
char * p1;
char * p2;
{
    int c;
    /* copy p2 to p1 */
    while (c = *p2++) {
    	if (isupper(c))
    	    c = tolower(c);
    	*p1++ = c;
    }
    *p1 = '\0';
}

/*
 * copy string b1 to l/c string b2, with overlap testing
 */
static void
blcpy (b1, b2, length)
     register char *b1;
     register char *b2;
     register int length;
{
    register int c;
    /* handle buffer overlap case */
    if (b1 < b2)	/* possible overlap */
    	for (b1 += length, b2 += length; length--; ) {
    	    c = *--b1;
    	    if (isupper(c))
    		c = tolower(c);
    	    *--b2 = c;
    	}
    else
    	for (;length--;) {
    	    c = *b1++;
    	    if (isupper(c))
    		c = tolower(c);
    	    *b2++ = c;
    	}
}

#endif /* mpx */

