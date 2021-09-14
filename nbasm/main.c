/* main.c */
/*
 * 	(c) Copyright 1990 J B Systems - Morrison, CO 80465
 * 	    All Rights Reserved.
 */

/*
 *	J B Systems, Non Base Register Assembler
 */

#include "defs.h"
#ifndef DOS
#include <signal.h>
#endif

#ifdef DOS
#include <string.h>
#include <io.h>
#include <process.h>
void	main(int, char**);
void	cpas(char);
void	dexit(int);
void	siexit();
void	error(char *, char *);
int	frprintf(FILE *, char *, char *);
void	getdt();
void	boer();
void	xrer();
void	sker();
void	loer();
void	abortm(char *);
void	abrtm1(char *);
#endif

#ifdef NULL
#undef NULL
#define NULL 0
#endif

char *infile;
char *curfile;
#ifdef mpx
char tmpname[] = "asinXXXXXX";
char ut2name[] = "ut2XXXXXX";
#else
char tmpname[] = "/tmp/asinXXXXXX";
char ut2name[] = "/tmp/ut2XXXXXX";
#endif
char tempname[] = "asXXXXXX";		/* full declaration is in aout.c */
char *tempfile = tempname;		/* full declaration is in aout.c */
char *ut2file = ut2name;		/* full declaration is in aout.c */
char *outfile = (char *) "a.out";
#ifdef DOS
char *macfile = (char *) "mpx.mac";
#else
#ifdef mpx
char *macfile = (char *) "/system/system/m.mpxmac";
#elif defined(linux) || defined(__alpha)
char *macfile = (char *) "/system/bin/m.mpxmac";
#else
char *macfile = (char *) "/u/bin/m.mpxmac";
#endif
#endif
char *listfile;				/* listing file */
char *inputf[100];			/* list of input files, 100 max */
int numinf = 0;				/* number of input files */
int numfproc = 0;			/* number of files processed */
char errfound;				/* set non zero on error */
FILE *outfd;				/* binary output file descriptor */
FILE *tempfd;				/* temporary file descriptor */
FILE *ut2fd;				/* xref file descriptor */
char *xrbuf;				/* xref buffer */
int ut2flag = 0;			/* set if ut2 file */
int tflag = 0;				/* set if temp file */
int32 hwerct = 0;			/* keep count of cumulative errors */
char PASS;				/* pass number 1 = pass 1, 0 = pass 2 */
char bits3;
int32 option;				/* option flags */
int32 optsav;				/* option save flags */
int32 nerrors = 0;
char	pass;
/* extern int deflab(); */
/* extern int checklab(); */

extern int mktemp();
extern struct tval max;			/* defined in io.c */

/*
void prexec(n, v, si, so)
int n;
char *v[], *si, *so;
{
  int i;
  char *f;

  f = v[0];
  printf("%s ", f);
  for(i=1; i < n; i++) {
    printf("%s ", v[i]);
  }
  if(si) printf(" <%s ", si);
  if(so) printf(" >%s ", so);
  printf("\n");
  fflush(stdout);
}
*/

/*
 * main - main procedure for non-base register assembler
 * if no input source file is named, standard input is assumed.
 * A temporary file is created in this case for all input from
 * stdin up to an end of file. At EOF, the file is processed.
 */

int main(argc,argv)
int	argc;
char	**argv;
{
	register char **ap;
	register int c;
/*	char *tp; */	/* temp pointer */
#ifndef DOS
	void	siexit();
#endif

/*
prexec(argc, argv, 0, 0);
*/

#ifndef DEBUG
setbuf(stdout, NULL);
setbuf(stderr, NULL);
#endif

#ifndef DOS
/*    	setbuf(stdout, 0); */
	/* trap signals */
	if (signal (SIGHUP, SIG_IGN) != SIG_IGN)
		signal (SIGHUP, siexit);
	if (signal (SIGINT, SIG_IGN) != SIG_IGN)
		signal (SIGINT, siexit);
	if (signal (SIGTERM, SIG_IGN) != SIG_IGN)
		signal (SIGTERM, siexit);
#endif

#ifdef DOS_DEBUG
#include <malloc.h>
printf("memory available = %u\n", _memavl());
#endif

	/* set default options */
	/* output date and time, and id information */
	option = (DT | ID);
	bits3 = 0;	/* clear loader options */

	/* handle command line arguments */
    for( ap = argv+1; *ap; ap++ ){
	char *cp = *ap;
	if( *cp != '-' ){
	    inputf[numinf++] = cp;	/* set input file name */
	} else {
	    switch( cp[1] ){
		
/* need to handle 
NBCAS -LFILE -G -X -A -D -E -1 -OFILE -TFILE -MFILE INPUT0 INPUT1 .. INPUTN
-Lfile	make listing on "file", no file, go to stdout
-G	output debug information
-X	do cross reference
-D	change csect to dsect
-E	do IEEE floating point
-A	do-auto sectioning
-O	object on sbo or file
-T	temp file definition
-M	macro file definition (m.mpxmac)
-1	1x object (no date & time or program info)
*/

	/* user specified temp file */
	    case 't':
	    case 'T':
/*		tp = tempfile; */		/* save default name */
		if (cp[2] != 0) {
		  tempfile = &cp[2];
    		  tflag++;
    		}
		break;
	    
	/* user specified macro file */
	    case 'm':
	    case 'M':
/*		tp = macfile; */		/* save default name */
		if (cp[2] != 0)
		  macfile = &cp[2];
		break;
	    
	/* user specified object file */
	    case 'o':
	    case 'O':
		if (cp[2] != 0)
		  outfile = &cp[2];
		if (outfile)option |= BO;	/* set binary output */
		break;
	    
	/* see if debug symbols wanted */
	    case 'g':
	    case 'G':
		option |= DBG;	/* debug symbols wanted */
#ifndef CAID
		bits3 |= EXPLFC;	/* expanded loader codes */
#endif
		break;

	/* see if ieee wanted */
	    case 'e':
	    case 'E':
		option |= OPT55;	/* IEEE wanted */
    		fpflag |= 2;		/* set the flag */
		bits3 |= EXPLFC;	/* expanded loader codes */
		break;

	/* see if 1x object wanted */
	    case '1':
		option &= ~(DT|ID);	/* no date/time or program info */
		break;

	/* see if auto sectioning wanted */
	    case 'a':
	    case 'A':
		option |= ASECT;	/* do autosectioning */
		bits3 |= EXPLFC;	/* expanded loader codes */
		break;
	    
	/* see if dsect only */
	    case 'd':
	    case 'D':
		option |= DSO;		/* do dsec only */
		break;
	    
	    case 'l':
	    case 'L':
		if (cp[2] != 0)
		  listfile = &cp[2];
		option |= LO;	/* set listing output */
		break;

	/* see if cross reference wanted */
	    case 'x':
	    case 'X':
		option |= XREF;	/* do cross reference */
		break;
	    
	    case 'h':
	    case 'H':
	    default:
fprintf(stderr,"Usage: NBCAS -LFILE -G -X -A -D -OFILE -TFILE -MFILE INPUT0 INPUT1 ... INPUTN\n\n");
fprintf(stderr,"-Lfile	output listing to file or stdout\n");
fprintf(stderr,"-G	output debug information\n");
fprintf(stderr,"-X	do cross reference\n");
fprintf(stderr,"-A	do-auto sectioning\n");
fprintf(stderr,"-D	change csect to dsect\n");
fprintf(stderr,"-E	use IEEE floating point\n");
fprintf(stderr,"-1	output 1x object (no date/time or prog info)\n");
fprintf(stderr,"-Ofile	object to file or a.out\n");
fprintf(stderr,"-Tfile	temp file definition\n");
#ifdef DOS
fprintf(stderr,"-Mfile	macro file name, default: MPX.MAC\n");
#else
fprintf(stderr,"-Mfile	macro file name, default: m.mpxmac\n");
#endif
		if (cp[1] != 'h' && cp[1] != 'H')
		fprintf(stderr,"bad command line option specified %s\n", cp);
		exit(1);
		break;
	    }
	}
    }

    if (!tflag)
	    mktemp(tempfile);
	inputf[numinf] = '\0';	/* zero terminate file list */
	infile = *inputf;	/* get first to process */

	/* temporary work file from stdin if no input file on command line */
	if (infile == 0) {
	  FILE *hold;
	  mktemp(tmpname);
	  hold = fopen(tmpname,"w");
	  while( (c=getchar()) >=0 ) {
	    putc(c,hold);
	  }
	  fclose(hold);
	  infile = tmpname;
	  *inputf = infile;	/* set file name to tmp file */
	  inputf[1] = '\0';	/* null terminate */
	}

	/* initialization for pass 1 */
	errfound = 0;		/* indicate no errors yet */
	optsav = option;	/* save option word for pass 2 */

/*
  printf("nbasm do opinit\n");
  fflush(stdout);
*/
	/* perform opcode table initialization */
	opinit();		/* initializes base and non base tables */

/*
  printf("nbasm do macinit\n");
  fflush(stdout);
*/
	/* open macro library */
	macinit();

	/* open listing and binary files if required */
	ppt = 0;		/* set default illegal bo */

	/* assemble the first file given */
	infile = inputf[numfproc++];	/* get file to process */
	if (freopen(infile,"r",stdin)==NULL) {
	  perror(infile);
	  error ("Fatal assembler error (input file %s)", infile);
	  abortm(0);		/* abort the assembler */
	  /* no return */
    	}

	curfile = infile;	/* set current file */

	if ((LO & option) && listfile) {	/* is listing required */
	  if ( freopen (listfile, "w+", stdout) == 0) {
	    perror(listfile);
	    error ("Fatal assembler error (listfile file %s)", listfile);
	    loer();
   	  }
	}

	/* open binary output file if required*/
	if (BO & option) {	/* is binary output required */
#ifdef DOS
	  if (outfile && ((outfd = fopen(outfile,"w+b")) <= 0)) {
#else
#ifdef mpx
	  if (outfile && ((outfd = fopen(outfile,"w+u")) <= 0)) {
#else
	  if (outfile && ((outfd = fopen(outfile,"w+")) == 0)) {
#endif
#endif
	    perror(outfile);
	    error ("Fatal assembler error (outfile file %s)", outfile);
	    boer();
   	  }
	  ppt = BRL;		/* set bo rec cnt to 120 */
	}

/*
  printf("nbasm start assemble\n");
  fflush(stdout);
*/

	/* start assembling */
	memset(PBL, '\0', BRL);	/* initialize BO buffer */
	memset(tcwd, ' ', TCWSIZE);	/* initialize LO buffer */
	getdt();	/* set date time information */
	if (XREF & option) {		/* see if xref required */
	    xref_cmd(DOXREF);		/* start xref */
#ifdef NO_XREF_WRITES
	    mktemp(ut2file);		/* create xref file */
#ifdef DOS
	    if ((ut2fd = fopen(ut2file,"w+b")) <= 0) {
#else
#ifdef mpx
	    if ((ut2fd = fopen(ut2file,"w+u")) <= 0) {
#else
	    if ((ut2fd = fopen(ut2file,"w+")) <= 0) {
#endif
#endif
		perror(ut2file);
		error ("Fatal assembler error (ut2file file %s)", ut2file);
		xrer();
	    }
#endif /* NO_XREF_WRITES */
	    ut2flag = 1;		/* ut2 opened */
	    /* get memory for xref storage, default to 153,600 bytes */
#ifdef DOS
	    xrbuf = (char *)_fmalloc(768*200);
#else
	    /* enought for 12800 symbol references */
	    xrbuf = (char *)malloc((unsigned int)(768*200));
#endif
	    if (!xrbuf)		/* if no memory terminate assemble */
		abortm("** UNABLE TO ALLOCATE MEMORY FOR XREF STORAGE **");
	} else
	    xref_cmd(NOXREF);		/* no xref wanted */
	cpas(pass = 1);			/* set up for pass 1 */
	PBLC = 0;			/* clear bo checksum */
	PBLS = 0;			/* set sequence # to zero */

/*
printf ("going to goasm\n");
fflush (stdout);
*/
	/* go start assembling */
	if (goasm((char)PASS)) {	/* returns non zero on EOF, EOM */
/*
printf ("return from goasm\n");
fflush (stdout);
*/
	  /* terminate assembler */
	  if (BO & option)		/* if doing output, close */
	    fclose(outfd);		/* close the output file */
	  if (errfound) abrtm1("AS31");	/* abort with AS31 error */
	  dexit(0);			/* exit with O.K. status */
	} else {			/* no EOF/EOF, do next file */
/*
printf ("return from goasm with no EOF\n");
fflush (stdout);
*/
	  pbp (0xdf);			/* publish last binary object record */
	  if (XREF & option) {		/* see if xref required */
	    writerep(120);		/* do xref with 120 byte printer rec */
	  }
	  if (hwerct)			/* was there an error */
	    errfound = 1;		/* indicate error occurred */
	}

	fclose (tempfd);		/* close the tempfile */
/*
printf ("calling dexit, nerrors = %d\n", nerrors);
fflush (stdout);
*/
	dexit(nerrors!=0);		/* exit */
}

/*
 * cpas (pasnum)
 * set up for the beginning of a pass
 * input - pass number
 */

void	cpas(pasnum)
char	pasnum;
{
	PASS = pasnum;			/* save the pass number */
	lice = 0;			/* set line count to zero */
	max.value = 0;			/* zero max program size */
	max.type = 0;
	max.flags = 0;
	eisreset();			/* force opcodes to REIS mode */
	if (PASS & 1) {			/* see if pass 1 */
	  /* open temp file r/w binary mode */
	  if (tempfile && ((tempfd = fopen(tempfile,"w+")) == 0)) {
	    perror(tempfile);
	    error ("Fatal assembler error (tempfile file %s)", tempfile);
	    sker();
   	  }
	}
	option = optsav;		/* restore original options */
	fseek (tempfd, (int32)0, 0);	/* rewind temp file */
	return;				/* return */
}


/*
 * dexit and siexit - exit gracefully (?)
 * parameter v is the return code for dexit.
 * siexit is called ONLY through the signal handler. it exists only to
 * allow a proper parameter to be passed to dexit.
 * if a temporary file was created for source from stdin, it is unlinked
 * before exiting. creation is done in main.
 * if the code generation temporary file has been created , it is unlinked
 * before exiting on a signal. creation is done in pass2_init of aout.c.
 */

void	dexit(v)
int	v;
{
    if (infile==tmpname) unlink(infile);
    if (tempfile && !tflag) unlink (tempfile);
    if (ut2flag) unlink (ut2file);
/*
    fprintf (stderr,"dexit: assembler returns %d\n", v); 
    fflush (stderr);
*/
    exit(v);
}

void	siexit ()
{
    if (pass == 2 || !tflag) unlink (tempfile);
    if (ut2flag) unlink (ut2file);
    dexit (1);
}

/*
 * error - output error messages
 * parameter f is a character string identical in syntax to a printf format
 * string. parameter arg is any additional information to be printed, again
 * as in a printf call.
 * an error message is set up and printed to standard error.
 * the variable nerrors (number of errors) is incremented.
 */

/*VARARGS1*/
void	error(f, arg)
char	*f;
char	*arg;
{
    extern char *curfile;

    fflush (stdout);
    fprintf(stderr,"\"%s\", line %d: "
	,curfile ? curfile : (char *) "",lict);
    frprintf (stderr, f, arg);
    fprintf(stderr,"\n");
    fflush (stderr);
    nerrors++;
}

/*
 * frprintf - special print routine
 * Equivalent to fprintf, but allows caller to expand parameters that were
 * passed to it.
 * parameter iop is a pointer to the stdio file descriptor, fmt is a pointer
 * to a character string which is the printf-like format string, and arg is
 * a pointer to the stack frame with args.
 * arg is the address of the first parameter TO CALLER after the format.
 * returns:
 *	EOF	If hit end of file
 *	0	If no EOF
 */

/*VARARGS2*/
int	frprintf(iop, fmt, args)
FILE *iop;
char *fmt;
char	*args;
{
	fprintf(iop, fmt, args);
	/*_doprnt(fmt, args, iop);  */
	return(ferror(iop)? EOF: 0);
}

/* routine to setup date and time in header and object */
#include <time.h>

/* char	datetime[16]; */	/* date and time in ascii */
char	FMTD_DT[40];	/* mpx date & time for object */

void	getdt()
{
	struct	tm	*ct;
	time_t	curt;	/* curr time */

	time(&curt);		/* get current time */
	memcpy(TCWDATE, ctime(&curt), 24);	/* set date/time in header */
	ct = localtime(&curt);
	sprintf(FMTD_DT, "%.2d/%.2d/%.2d %.2d:%.2d:%.2d",
		ct->tm_mon+1, ct->tm_mday, ct->tm_year,
		ct->tm_hour, ct->tm_min, ct->tm_sec);
	return;
}

/* abort routines */

/* error on bo file */
void	boer()
{
	abrtm1("AS02");		/* abort with AS02 error */
	/* no return */
}

/* error in lo file */
void	loer()
{
	abrtm1("AS03");		/* abort with AS03 error */
	/* no return */
}

/* error on temp file */
void	sker()
{
	abrtm1("AS04");		/* abort with AS04 error */
	/* no return */
}

/* error on xref file */
void	xrer()
{
	abrtm1("AS05");		/* abort with AS04 error */
	/* no return */
}

/* abort with message */
void	abortm(msg)
char * msg;
{
	if(!msg)abrtm1(0);	/* if no msg, just do abort */
	fprintf(stderr, "%s\n", msg);
	abrtm1("AS31");		/* abort with AS31 error */
	/* no return */
}

/* exit with abort status */
void	abrtm1(errorv)
char	*errorv;
{
	if (errorv)
	  fprintf (stderr, "Assembler abort: %s\n", errorv);
	dexit(2);		/* exit with abort status */
	/* no return */
}
