/* defs.h */
#ifdef DODEBUG
#define MACD
#define MACP
#define MACS
#endif
#undef BIN

#ifdef mpx
#include <types.h>
#endif

#include <stdio.h>
#include <string.h>

extern void *malloc();
extern void *realloc();
extern void free();
extern void exit();
extern void *calloc();
extern int  unlink();

#ifdef DOS
#define longp	long		/* 32 bits on everything else */
#define	int32	long		/* must be 32 bits */
#define	int16	unsigned short	/* must be 16 bits */
#define	int32f	long far	/* 32 bit far value */
#define chrfp	char far *	/* 32 bit pointer to char */
#define uchrfp	unsigned char far *	/* 32 bit pointer to char */
#define uchrfpp	unsigned char far * far *	/* 32 bit pointer to ptr */
#define FAR far
#else
#ifdef __alpha
#define longp	long		/* 64 bits on alpha */
#define	int32	int		    /* must be 32 bits */
#else

#define	int64	long long	    /* must be 64 bits */
#define	int32	int		    /* must be 32 bits */
#define	uint32	unsigned int32		/* must be 32 bits */
/* #define longp	long */ /* 32 bits on everything else */
#define longp	int32		/* 32 bits on everything else */
#endif
#define	uint8	unsigned char		/* must be 8 bits */
#define	int16	unsigned short	/* must be 16 bits */
#define chrfp	char *		/* 32 bit pointer to char */
#define uchrfp	unsigned char *	/* 32 bit pointer to char */
#define uchrfpp	unsigned char **	/* 32 bit pointer to ptr */
#define FAR
#endif
extern	void	reptr();

/*********************************/
/* variables defined in opcode.c */
/*********************************/

#ifdef DOS
extern	struct optab *opscan(char *);
extern	void	opinit();
extern	void	xopinit(struct optab *);
#else
extern	struct optab *opscan(/* char * */);
extern	void	opinit();
extern	void	xopinit(/* struct optab * */);
#endif

/* opcode table structure definition */
struct optab {
	struct optab *rlink;
	struct optab *llink;
	char 	*opcode;
	unsigned	binop:8;
	unsigned	aug:4;
	unsigned	varcode:4;
	unsigned	fieldnum:4;
	unsigned	subaug:4;
	unsigned	opproc:8;
};

extern	struct optab *opscan();
extern	struct optab opstab[];

/*****************************/
/* variables defined in io.c */
/*****************************/

#ifdef DOS
extern	void	str2upr(char *);
extern	void	ejct (char *);
extern	void	ejct2 (char *);
extern	void	pb(unsigned char *, int, int);
extern	void	pbp(int);
extern	void	mpxbb(unsigned char *, int);
extern	int	inpt();
extern	void	igen (int);
extern	void	releas ();
extern	void	pout();
extern	void	loch(struct tval *, int, char *);
extern	int	ppp(int, char *, int);
extern	int32	iread(int, char *);
extern	void	pbyt(char);
#else
extern	void	str2upr(/* char * */);
extern	void	ejct (/* char * */);
extern	void	ejct2 (/* char * */);
extern	void	pb(/* unsigned char *, int, int */);
extern	void	pbp(/* int */);
extern	void	mpxbb(/* unsigned char *, int */);
extern	int	inpt();
extern	void	igen (/* int */);
extern	void	releas ();
extern	void	pout();
extern	void	loch(/* struct tval *, int, char * */);
extern	int	ppp(/* int, char *, int */);
extern	int32	iread(/* int, char * */);
extern	void	pbyt(/* char */);
#endif

/*******************************/
/* variables defined in main.c */
/*******************************/

#ifdef DOS
extern	int		main(int, char **);
extern	void	cpas(char);
extern	void	dexit(int);
extern	void	siexit();
extern	void	error(char *, char *);
extern	int		frprintf(FILE *, char *, char *);
extern	void	getdt();
extern	void	boer();
extern	void	xrer();
extern	void	sker();
extern	void	loer();
extern	void	abortm(char *);
extern	void	abrtm1(char *);
#else
extern	int		main(/* int, char ** */);
extern	void	cpas(/* char */);
extern	void	dexit(/* int */);
extern	void	siexit();
extern	void	error(/* char *, char * */);
extern	int		frprintf(/* FILE *, char *, char * */);
extern	void	getdt();
extern	void	boer();
extern	void	xrer();
extern	void	sker();
extern	void	loer();
extern	void	abortm(/* char * */);
extern	void	abrtm1(/* char * */);
#endif
extern	char	bacflag;	/* flags for bacx codes */
extern	char	extflg;		/* external stringback control flag */
    				/* 1 - ext ref record needed */
    				/* 2 non-branch instruction flag */
extern	struct tval extwrd;	/* stringback control address */
extern	char	extnam[];	/* stringback control symbol */
extern	char	fpflag;		/* IEEE flags */
    				/* 1 saw IEEE instruction */
    				/* 2 option 55 set */
extern	char	PASS;		/* pass # 1=pass 1, 0=pass 2 */
extern	char	bits3;		/* object loader options */
#define EXPLFC	1		/* use expanded loader function codes */
extern	FILE	*outfd;		/* binary output file descriptor */
extern	FILE	*tempfd;	/* temperary file descriptor */
extern	char	*tempfile;	/* name of tempfile */
extern	char	*infile;	/* input file name */
extern	char	*curfile;	/* current input file name */
extern	char	*inputf[];	/* list of input files to process */
extern	int	numfproc;	/* number of files processed */
extern	char	errfound;	/* non zero when error found */
extern	int32	hwerct;		/* cumulative error count */

extern	int32	option;		/* option word */
extern	int32	optsav;		/* option save word */
#define LO	0x00000001	/* list output 		1=yes, 0=no */
#define BO	0x00000002	/* binary output 	1=yes, 0=no */
#define XREF	0x00000008	/* xref symbols		1=yes, 0=no */
#define DT	0x00000010	/* save date & time	1=yes, 0=no */
#define ASECT	0x00000020	/* do auto-sectioning	1=yes, 0=no */
#define ID	0x00000040	/* save program info	1=yes, 0=no */
#define BM	0x00000080	/* basemode option	1=yes, 0=no */
#define DSO	0x00000100	/* dsect only		1=yes, 0=no */
#define DBG	0x00000200	/* debug symbol output	1=yes, 0=no */
#define OPT11	0x00000400	/* option 11		1=yes, 0=no */
#define	OPT55	0x00000800	/* option 55, do IEEE	1=yes, 0=no */
#define	OPT56	0x00001000	/* option 56, noprnt *! 1=yes, 0=no */

/********************************/
/* variables defined in parse.c */
/********************************/

#ifdef DOS
extern	int	runst(int32);
extern	int	unst(int32);
extern	int	cunst(int32);
extern	void	upterm(char);		/* update terminator list */
extern	int	gbyte(int32);
extern	int	gbyt(int32);
extern	int	getabyte(int32);
extern	int	termchk (char, unsigned int32);
extern	void	grps();
extern	int	fac(int);
extern	struct	tval	val(int);
extern	void	tdat();
extern	void	tmd(int);
extern	void	tfn();
extern	void	tcy();
extern	void	tsh(int);
extern	void	tdg(int32, int, int);
extern	int32	*cnum(int);
extern	void	negate(int32 *);
extern	void	lefts(int32 *, int);
extern	void	rights(unsigned int32 *, int);
extern	void	add64(int32 *, int32 *);
extern	void	mulfp64(int32 *, int32 *);
extern	void	divfp64(int32 *, int32 *);
#else
extern	int	runst(/* int32 */);
extern	int	unst(/* int32 */);
extern	int	cunst(/* int32 */);
extern	void	upterm(/* char */);		/* update terminator list */
extern	int	gbyte(/* int32 */);
extern	int	gbyt(/* int32 */);
extern	int	getabyte(/* int32 */);
extern	int	termchk (/* char, unsigned int32 */);
extern	void	grps();
extern	int	fac(/* int */);
extern	struct	tval	val(/* int */);
extern	void	tdat();
extern	void	tmd(/* int */);
extern	void	tfn();
extern	void	tcy();
extern	void	tsh(/* int */);
extern	void	tdg(/* int32, int, int */);
extern	int32	*cnum(/* int */);
extern	void	negate(/* int32 * */);
extern	void	lefts(/* int32 *, int */);
extern	void	rights(/* unsigned int32 *, int */);
extern	void	add64(/* int32 *, int32 * */);
extern	void	mulfp64(/* int32 *, int32 * */);
extern	void	divfp64(/* int32 *, int32 * */);
#endif

struct	tval {			/* structure containing type, flags, value */
	unsigned  type:8;	/* its type */
	unsigned  flags:8;	/* misc flags */
	unsigned  tmp:16;	/* filler */
/* ngp value;		*/  /* and value */
	uint32    value;	/* and value */
};

extern	struct	tval	val ();
extern	int32	*cnum();

extern	int32	hwcmsize[];	/* common sizes */
extern	unsigned char	hbbs[];	/* binary output stack and count */
				/* first byte is count, then data */

/******************************/
/* variables defined pseudo.c */
/******************************/

#ifdef DOS
extern	void	arel();
extern	void	bouc (int32);
extern	int	tbou(int);
extern	void	bound ();
extern	void	ccp1();
extern	void	dpcom();
extern	void	equ();
extern	void	list();
extern	void	lpop();
extern	void	org();
extern	void	pagp();
extern	void	prog();
extern	void	ref ();
extern	void	res();
extern	void	rez();
extern	void	pcchk();
extern	void	rseis();
extern	void	eisset();
extern	void	eisreset();
extern	void	eismerge(int);
extern	void	sdirs();
extern	void	space();
extern	void	titl();
#else
extern	void	arel();
extern	void	bouc (/* int32 */);
extern	int	tbou(/* int */);
extern	void	bound ();
extern	void	ccp1();
extern	void	dpcom();
extern	void	equ();
extern	void	list();
extern	void	lpop();
extern	void	org();
extern	void	pagp();
extern	void	prog();
extern	void	ref ();
extern	void	res();
extern	void	rez();
extern	void	pcchk();
extern	void	rseis();
extern	void	eisset();
extern	void	eisreset();
extern	void	eismerge(/* int */);
extern	void	sdirs();
extern	void	space();
extern	void	titl();
#endif
extern	char	prodidl;	/* length of product id */
extern	char	prodid[];	/* product id 0-20 bytes */

/*********************************/
/* variables defined in symbol.c */
/*********************************/

#ifdef DOS
extern	struct symbol FAR * ss(struct tval *, char *);
extern	struct symbol FAR * macss(struct tval *, char *, int);
extern	void	prtsymt();
char	FAR * Memcpy(char FAR *, char *, int);
char	* memCpy(char *, char FAR *, int);
int	MemCmp(char FAR *, char FAR *, int);
int	memCmp(char *, char FAR *, int);
#else
extern	struct symbol* ss(/* struct tval *, char * */);
extern	struct symbol* macss(/* struct tval *, char *, int */);
extern	void	prtsymt();
char	FAR * Memcpy(/* char FAR *, char *, int */);
char	* memCpy(/* char *, char FAR *, int */);
int	MemCmp(/* char FAR *, char FAR *, int */);
int	memCmp(/* char *, char FAR *, int */);
#endif

/* symbol table structure definition */
struct symbol {
	struct symbol FAR *flink;	/* next entry address */
	struct symbol FAR *rlink;	/* right tree link address */
	struct symbol FAR *llink;	/* left tree link address */
	char	sym[8];		/* the symbol defined */
	struct	tval desc;	/* the symbol descriptor */
};

/* symbol table values */
#define TYPCON	0x00		/* type is a constant */
#define	TYPU	0x01		/* UNDEFINED SYMBOL TYPE CODE */
#define	TYPL	0x02		/* LITERAL ITEM CODE */
#define	TYPC	0x03		/* DEFINE A SYMBOL WITHIN COMMON BLOCK */
#define	TYPP	0x04		/* NORMAL PROGRAM DEFINED SYMBOL CODE */
#define	TYPM	0x05		/* MULTIPLY DEFINED SYMBOL TYPE CODE */
#define	TYPX	0x06		/* EXTERNAL TYPE SYMBOL CODE */
#define	TYPD	0x07		/* COMMON BLOCK DEFINITION NUMBER */
#define	TYSETSYM 0x08		/* SYMBOL ENTERED WITH A SET */
#define	TYMACDEF 0x09		/* MACRO DEFINITIION TYPE CODE */
#define	TYFRM	0x0A		/* FORM DIRECTORY ITEM */
#define	TYPDP	0x0C		/* DATAPOOL ITEM */
#define	TYMACREQ 0x0E		/* MACRO DATA REQUEST FLAG */
#define	TYPC2	0x02		/* TWO BIT TYPE CODE FOR COMMON */
#define	TYPREL	0x01		/* 2 BIT TYPE CODE FOR RELOCATABLE TYPES */

extern	char	dpitem[];	/* last datapool name */

extern	struct symbol FAR * ss();
extern	struct symbol FAR * macss();

extern	struct tval symval;	/* last symbol information */
extern	struct tval macval;	/* last macro symbol information */
extern	struct symbol FAR *symhead[]; /* symbol table head cell pointers */
extern	struct symbol FAR *symprevp; /* pointer to last symbol */
extern	struct symbol FAR *symtab;	/* address of 1st symbol in symtab */
extern	struct symbol FAR *macprevp; /* pointer to last macro symbol */
extern	struct symbol FAR *mactab;	/* address of 1st macro symbol */
#define	MACADD	1		/* add macro request */
#define	MACMOD	2		/* modify macro request */
#define	MACLOOK	4		/* lookup macro request */

/* stringback structure definition pointed to by symbol table for extern */
struct	strback {
	struct	tval dsdesc;	/* dsect descriptor */
	struct	tval csdesc;	/* csect descriptor */
};

/********************************/
/* variables defined in goasm.c */
/********************************/

#ifdef DOS
extern	int	goasm(char);
extern	void	tall();
extern	void	prtval (char *, struct tval *);
extern	void	next();
extern	void	aerr();
extern	void	cext();
extern	void	rset(char);
extern	char * csnegate (char *);
extern	void	ascttst(struct optab *);
#ifndef CAID
extern	void	stab();
#endif
extern	void	dtonly();
extern	void	enddt();
extern	int	yeanay();
extern	void	clrerr (char);
extern	void	seterr (char);
extern	void	bndwnopg();
extern	void	cdl();
extern	void	rtb();
extern	void	ler();
extern	void	calm();
extern	void	shf();
extern	void	nss();
extern	void	trsw();
extern	void	zrx();
extern	void	nords();
extern	void	setcpu();
extern	void	rro();
extern	void	gen16 (int, int, int);
extern	void	gen16a (iint, int, int, int);
extern	void	agen();
extern	void	agem(int32);
extern	void	gen32 (int, int, int32);
extern	void	bm();
extern	void	bi();
extern	void	bu();
extern	void	fpp();
extern	void	trip();
extern	void	exr();
extern	void	imop();
extern	void	io();
extern	void	svc();
extern	void	trap();
extern	void	extio();
extern	void	bndw();
extern	int32	ageq0(int32, int);
extern	int32	ageq(int32, int);
extern	void	pend();
extern	void	prlit();
extern	void	end2();
extern	void	bfo(struct symbol FAR *);
extern	void	bfn();
extern	void	bfn0();
#ifndef CAID
extern	void	bfn0a();
#endif
extern	void	bfa0 (int32);
extern	void	bfa (int32);
#ifndef CAID
extern	void	bfw (int32);
extern	void	bfh (int);
#endif
extern	void	bfb(int);
extern	void	data();
extern	void	vfd();
extern	void	vfdo(int32, int);
#else
extern	int	goasm(/* char */);
extern	void	tall();
extern	void	prtval (/* char *, struct tval * */);
extern	void	next();
extern	void	aerr();
extern	void	cext();
extern	void	rset(/* char */);
extern	char * csnegate (/* char * */);
extern	void	ascttst(/* struct optab * */);
extern	void	dtonly();
extern	void	enddt();
extern	int	yeanay();
extern	void	clrerr (/* char */);
extern	void	seterr (/* char */);
extern	void	bndwnopg();
extern	void	cdl();
extern	void	rtb();
extern	void	ler();
extern	void	calm();
extern	void	shf();
extern	void	nss();
extern	void	trsw();
extern	void	zrx();
extern	void	nords();
extern	void	setcpu();
extern	void	rro();
extern	void	gen16 (/* int, int, int */);
extern	void	gen16a (/* int, int, int, int */);
extern	void	agen();
extern	void	agem(/* int32 */);
extern	void	gen32 (/* int, int, int32 */);
extern	void	bm();
extern	void	bi();
extern	void	bu();
extern	void	fpp();
extern	void	trip();
extern	void	exr();
extern	void	imop();
extern	void	io();
extern	void	svc();
extern	void	trap();
extern	void	extio();
extern	void	bndw();
extern	int32	ageq0(/* int32, int */);
extern	int32	ageq(/* int32, int */);
extern	void	pend();
extern	void	prlit();
extern	void	end2();
extern	void	bfo(/* struct symbol FAR * */);
extern	void	bfn();
extern	void	bfn0();
extern	void	bfn0a();
extern	void	bfa0 (/* int32 */);
extern	void	bfa (/* int32 */);
extern	void	bfw (/* int32 */);
extern	void	bfh (/* int */);
extern	void	bfb(/* int */);
extern	void	data();
extern	void	vfd();
extern	void	vfdo(/* int32, int */);
#endif

extern	char	asctblb[];	/* holds label from bound processor */
extern	int32	asctblc;	/* holds curr loc cntr from bound processor */
extern	struct	tval asctbvl;	/* holds value from bound processor */
extern	char	asctflg;	/* control flags */
#define ASCTBND	1		/* set indicated deferred bound */
#define ASCTNOD	2		/* set by equ & org processors if $ illegal */
#define ASCTDTO	4		/* set during dataonly sequence */
#define ASCTFND	8		/* set by val when $ symbol is found */

extern	char	*csnegate();	/* routine to negate character string */
extern	char	dpflags;	/* datapool flags */
#define	DPFLG	1 		/* processing a datapool reference */
extern	char	eisflg;		/* EIS mode flags */
#define	EISOPC	1		/* set for context type instructions */
				/* else off */
#define	EISON	1		/* SEIS mode on */
#define EISOFF	0		/* SEIS mode off */

extern	char	endflag;	/* nozero when end opcode found */
extern	uint8	hwbyte[];  /* THIS WORD CONTAINS THE GENERATED CODE */
				/* FOR THE CURRENT LINE OF ASSEMBLY BROKEN */
				/* DOWN INTO UP TO 4 BYTES. THIS WORD IS */
				/* SET UP AS IF IT WOULD MAP INTO THE H */
				/* MEMORY, I.E. THE LEFT MOST BYTE IS FOR */
				/* BYTE 0, THE RIGHTMOST BYTES IS FOR BY */
				/* THE 3 OF THE WORD ADDRESS CONTAINED IN */
				/* LSTS */
extern	char	hwbytf[];	/* EACH BYTE IN THIS WORD CONTAINS A FLAG */
				/* TELLING WHETHER THE CORRESPONDING BYTE */
				/* OF HWBYTE CONTAINS A VALID BYTE FOR OUTPUT */
extern	int32	hwcmpb[];	/* bounding for dsect/csect */
extern	struct	tval hweval;	/* the mode evaluation of the word in hwbyte */
				/* It is is symbol description format */
extern	unsigned char	in[];	/* the input line */
extern	char	lablscan[];	/* label we are scanning for */
extern	char	prnt[];		/* the print buffer */
extern	struct	tval	ud;	/* undefined value entry */
/***************************************************/
extern	uint8	hwmspbuf;	/* count of chars in print buffer */
#define	TCWSIZE	108		    /* title buffer size */
extern	char 	tcwd[];		/* title buffer */
#define	TCWPROG	&tcwd[3]	/* program name 8 chars + 4 filler */
#define	TCWDATE	&tcwd[15]	/* date & time 24 chars */
#define	TCWTITL	&tcwd[43]	/* title of 64 chars max */
#define	TCWTTLE	&tcwd[107]	/* 4 char filler */
extern	char	FMTD_DT[];	/* object date and time */

#define BRL	120		        /* length of binary record */
extern  uint8	ppt;		/* binary record length (120) */
extern	uint8 	PBL[];	    /* binary buffer */
#define PBLF	PBL[0]		/* function code location */
#define PBLB	PBL[1]		/* record byte count */
extern	short	*pblc;
#define PBLC	*pblc		/* 2 byte checksum */
extern	short	*pbls;
#define PBLS	*pbls		/* 2 byte sequence number */
extern	unsigned char	*pblp;
#define PBLP	pblp		/* start of object data */

extern	int32	lice;		/* line count */
extern	int32	lict;		/* current line number */
extern	struct	tval	max;	/* maximum program size */
/* extern	char	imip; */ /* image in progress flag */

extern	char	unterm;		/* last unstring terminator */
extern	int	unstnp;		/* store pointer for unst */
extern	char	label[];	/* the unstrung label, any */
#define MAXCHARS	24	/* maximum chars in usname */
extern	char	usname[];	/* contains last 24 char name unstrung */
extern	uint8   pcmode;		/* current program mode */
#define PCABS	0		/* 0 - prog in abs mode */
#define PCDS	1		/* 1 - prog in dsect mode */
#define PCCOM	2		/* 2 - prog in common mode */
#define PCCS	3		/* 3 - prog in csect mode */
#define CSDS	0x01		/* csect/dsect flag, on = csect */
#define ABSREL	0x02		/* abs/rel flag, on = relocatable */
#define SREF	0x10000000	/* symbol referenced */
#define SUORD	0x20000000	/* symbol usage or definition */
#define SSORT	0x40000000	/* sort flag */
extern	int32	bits2;		/* holds some misc flags*/
#define ADDRERR	 0x01		/* set if illegal addr boundry ref */
#define ALVAL	 0x02		/* val has already evaluated operand */
#define MACPRINT 0x04		/* don't list macro expansions */
#define REPPRINT 0x08		/* don't list rept expansions */
#define NONGITEM 0x10		/* curr oper is list nong suppressable */
extern	char	hbstac[];	/* left to right terminator list */
extern	char	mpbuf[];	/* macro expansion buffer */
extern	int32	hwerrf;		/* error flags */

extern	unsigned char	spmac;	/* HOLDS FLAGS FOR SPECIAL CONDITIONS */
				/* IN MACRO PROCESSING.  THE BITS */
				/* ARE DETAILED BELOW. */
#define	DUMMY	0x01		/* 1 INDICATES UNSTRUNG NAME IS */
				/* A DUMMY ARGUMENT. */
#define	LPOOLM	0x02		/* 1 INDICATES AN LPOOL DIRECTIVE IS */
				/* BEING PROCESSED IN A MACRO EXPANSION */
#define	NOPGEN 	0x04		/* 1 INDICATES A NOP IS BEING */
				/* GENERATED TO GET TO THE CORRECT */
				/* BOUNDARY. */
#define	INTSS	0x08		/* 1 INDICATES SS IS PROCESSING AN */
				/* INTERNALLY GENERATED SYMBOL. */
#define	UNS	0x10		/* INDICATES TO ROUTINE GBYT THAT IT */
				/* WAS CALLED BY UNST. */
#define	INTGEN3	0x20		/* INDICATES TO GBYT & UNST THAT AN */
				/* INTERNAL SYMBOL HAS BEEN UNSTRUNG. */
#define	MBUFSW	0x40		/* 1 INDICATES PRNT BUFS WERE SWITCHED. */
#define	DEFFRM2	0x80		/* SET WHILE PROCESSING A FORM DIR. OR */
				/* A MACRO PROTO IN PASS 2. */


extern	short	macstate;	/* macro state flags */
extern	short	inptstat;	/* input macro states */
#define MACREP   0x0001		/* indicates a rept within a macro expan */
#define FORMGET  0x0002		/* generatng a form call */
#define CALLUS   0x0004		/* macro call in progress */
#define EXPAND   0x0008		/* expanding a macro */
#define UNSTFLAG 0x0010		/* is set, unst has dummy arg */
#define REUNSTF  0x0020		/* if set, part way thru a macro strung */
#define DEFMBODY 0x0040		/* working on a macro prototype */
#define CONDSCAN 0x0080		/* looking for ift, iff, goto label */
#define INTGEN   0x0100		/* internal label encountered */
#define RSCAN    0x0200		/* initial scan of rept area */
#define RPTGEN   0x0400		/* generating code for a rept */
#define FORMSCAN 0x0800		/* scanning a form statement */
#define INTGEN2  0x1000 	/* save state for INTGEN */
#define NOCOMMT  0x2000		/* set if not a comment line */
#define	BLANKLN  0x4000		/* we have a blank line */

extern	short	bits;		/* misc bits for print control */
#define	LPOOL31  0x0001		/* 1 INDICATES 31 LPOOL DIRECTIVES */
				/* HAVE BEEN PROCESSED. */
#define	ESCAPE2  0x0002		/* CHARACTER COMING THROUGH IS PROTECTED */
#define	BNDWS3   0x0004
#define	BNDWS4   0x0008		/* EXPAND MODE BITS STORE */
				/* SAVE BIT 5 FOR MACRO ASSEMBLER */
#define	TGSIGN   0x0010		/* SIGN BIT FOR IMPLICIT DATA TYPES */
#define	TFSIGN   0x0020		/* 0=+, 1=- FOR DECIMAL CONSTANT */
#define	PROGF    0x0040		/* 1 MEANS PROGRAM HAS BEEN ENTERED */
#define	XPONENT  0x0080		/* 1 MEANS USER ENTERED AN EXPON */
#define	NGPRINT  0x0100		/* 0 MEANS PRINT SUPPRESSED CODE GENRTN */
#define	APON     0x0200		/* 0 MEANS ALLOW LIST, NON-ZERO MEANS NO */
#define	APEX     0x0400		/* 0 MEANS ALLOW LISTING OF EXTENSION */
				/* IMAGES (I.E. EXTRA WORDS FROM DATA */
				/* STATEMENTS), ELSE DONT */
#define	CVFL     0x0800		/* 0 MEANS PROG COUNTER NOT TO BE PRINTED */
				/* 1 MEANS PROG COUNTER TO BE PRINTED */
#define	IMIN     0x1000		/* 0 IF THE BUFFER IMAGE HAS ALREADY */
				/* BEEN PRINTED, NON-ZERO IF IT HAS NOT */
				/* BEEN PRINTED YET */
#define	INSIG	 0x2000		/* the next space is insignificant */
#ifndef CAID
#define INSTAB	 0x4000		/* in stab op, ignore ';' in line */
#endif

struct swdata {
	void	(*function)();
};

/* misc equates */
#define	PTA	0		/* ABSOLUTE DATA */
#define	PTO	1		/* ABSOLUTE/RELOCATABLE ORIGIN */
#define	PTTR	3		/* ABS/REL TRANSFER ADDRESS */
#define	PTR	4		/* RELOCATABLE DATA */
#define	PTPN	5		/* PROGRAM NAME */
#define	PTED	7		/* DEFINE LOCAL SYM ABS/REL ADR (EX DEF) */
#define	PTEX	9		/* EXT STRINGBACK TERMINATION (EX REF) */
#define	PTCD	10		/* X'A' COMMON BLOCK DEFINITION */
#define	PTCR	11		/* X'B' DATA REFERRING TO COMMON */
#define	PTDP	12		/* X'C' datapool loader function code */
#define	EXPFUNC	13		/* X'D' EXPANDED LOADER FUNCTION CODE */
#define	PTCO	14		/* X'E' COMMON ORIGIN */
#define	LFSDEF	1		/* EXP.LDR.SUB.FUNC. FOR SECTION DEFINITION */
#define	LFSORIG	2		/* EXP.LDR.SUB.FUNC. FOR SECTION ORIGIN */
#define	LFSREL	3		/* EXP.LDR.SUB.FUNC. FOR SECTION RELOCATABLE */
#define	LFTRANS	4		/* EXP.LDR.SUB.FUNC. FOR TRANSFER ADDRESS */
#define	LFEXTDF	5		/* EXP.LDR.SUB.FUNC. FOR EXTERNAL DEFINITION */
#define	LFEXTRF	6		/* EXP.LDR.SUB.FUNC. FOR EXTERNAL REFERENCE */
				/* 11 IS USED FOR SYMBOLIC DEBUGGER */
#define	LFDTID	12		/* DATA/TIME AND PRODUCT ID INFO */
				/* FLAG=0 FOR DATE/TIME */
				/* FLAG=1 FOR PRODUCT ID INFO */
#define	LFMULDP	13		/* EXP.LDR.SUB.FUNC. FOR MULTIPLE DATAPOOL */
#define LFCDBUG 14		/* loader function code for debug symbol */
#define LFCBAC	15		/* BAC loader function code */

extern	struct optab *curops;	/* current opcode table pointer */

extern	struct symbol FAR *libsch();

extern	int32	inttag;		/* internal tag number */
extern	uint8   inscnt;		/* input scanner count */
extern	int32	hwact;		/* current state information */

extern	struct tval currpc;	/* address of leftmost byte in this line */
				/* of code.  Used to allocate label */
extern	struct tval sectpc[];	/* ABS, DATA, COMM, and CNTL */
				/* section counters in std sym format */

extern	struct	tval	dsize;	/* dsect size for section definition */
extern	struct	tval	csize;	/* csect size for section definition */

extern	int	reptype;	/* report type code */
extern	int16	high;		/* max char space in macro storage */
extern	unsigned char	defcnt;	/* macro definition count */

#define	MACPRO	0x01		/* PROTO PTR ENTRY CODE. */
#define	MACBAS	0x02		/* BASE PTR ENTRY CODE. */
#define	MACARG	0x04		/* ARG PTR ENTRY CODE. */
#define	MACIUP	0x08		/* INT SYM UNASSEM PASSED ENTRY CODE. */
#define	MACIU	0x10		/* INT SYM UNASSEM ENTRY CODE. */
#define	MACIA	0x20		/* INT SYM ASSEM ENTRY CODE. */
#define	MACIAP	0x40		/* INT SYM ASSEM PASSED ENTRY CODE. */

extern	char	hbbbct;

extern	char	argmin[];	/* MINIMUM NUMBER OF OPERANDS FOR opcodes */
extern	char	argmax[];	/* MAXIMUM NUMBER OF OPERANDS FOR opcodes */
extern	char	bndws1[];	/* PROGRAM COUNTER STATUS INDICATORS */
extern	char	bndws2[];	/* MODULO 2,4,8 MASKS */
extern	char	grpss2[];	/* OFFSET FOR B,H,W,D,A TYPE ADR RESP. */

extern	int32	hwindr;		/* contains the indirect flag, if any to be */
				/* merged into the current instr format */
#define INDFLAG	0x00100000	/* bit 11, ind flag */

extern	int	grpw;		/* number of parameters to do */
extern	struct tval litorgs[];	/* literal origins */
extern	struct tval expr[];	/* expression variable information */

extern	short	hbccct;		/* next common block count */
extern	char	tot;		/* length constant for tdat */
extern	char	hbtttf;		/* type of data being translated */
extern	uint8   hbavar;		/* holds addr variant to be used */
extern	char	hbbn;		/* common block/section number */
extern	char	hbbbfb;		/* 0 means no data bytes output */
extern	char	hbbbct;		/* NUMBER OF BYTES GENERATED FOR THIS  */
				/* LINE OF SOURCE OR OBJECT */
extern	struct tval hwltct;	/* literal pool count, and type */
extern	struct tval inag;	/* AUGEND TYPE AND VALUE */
extern	struct tval inac;	/* ACCUMULAND TYPE AND VALUE */
extern	struct tval accum;	/* 2nd ACCUMULAND TYPE AND VALUE */
extern	char	valundf;	/* undefined val returned from val */
extern	uint8	inagbn;		/* block # for common */
extern	uint8	inacbn;		/* block # for common */


/*struct	tval	dval;	*/	/* descriptor for the value unstrung */

extern	short	hhvfx;		/* this is a right to left bit stack */
extern	short	hhvfo;		/* the number of bits in the stack */
extern	short	hhvfs;		/* num of it req'd in the curr gen element */
extern	short	hhvff;		/* num of bits sent to gen/vfd routn */
extern	short	hhvfgb;		/* num of bits accepted for output to stack */
extern	int	secnac;		/* sect num of accumuland */

/********************************/
/* variables defined in macro.c */
/********************************/

#ifdef DOS
extern	void	macinit();
extern	void	macer();
extern	struct	symbol FAR *libsch(char *);
extern	int	readrec();
extern	int	prim();
extern	void	defmpro();
extern	void	endmpro();
extern	void	exitmp();
extern	void	formp();
extern	void	formexp();
extern	void	gotop();
extern	void	ifpro();
extern	void	macexp();
extern	void	mbyt(unsigned char);
extern	void	reptp();
extern	void	endrp();
extern	void	setpro();
#else
extern	void	macinit();
extern	void	macer();
extern	struct	symbol	FAR *libsch(/* char * */);
extern	int	readrec();
extern	int	prim();
extern	void	defmpro();
extern	void	endmpro();
extern	void	exitmp();
extern	void	formp();
extern	void	formexp();
extern	void	gotop();
extern	void	ifpro();
extern	void	macexp();
extern	void	mbyt(/* unsigned char */);
extern	void	reptp();
extern	void	endrp();
extern	void	setpro();
#endif
extern	unsigned char	dpnum;		/* symbol's datapool number */
extern	unsigned char	hwdpnum;	/* datapool number */
extern	int	level;		/* number of levels below repeat */
struct	macxe	{		/* macro expansion entry */
	int	pcnt;		/* parameter count */
	unsigned char	*clev;	/* current level pointer */
	uchrfp	maca;		/* macro pointer address */
};

extern	unsigned char	macparam[];	/* storage for dummy macro parameters */
extern	unsigned char	*macdptr;	/* pointer to dummy parameter storage */

/* stack is the current macro level definition pointer */
/* stackp points to the current level.  stackp is type macxe */
/* stackp->pcnt has the parameter count for the macro */
/* stackp->clev has pointer to base of 6w * #parameters storage in stk */
/* 		this area is for parameter substitution generation */
/* stackp->maca has pointer to the macro prototype (hwcmac->desc.value) */
extern	struct	macxe	stack[];	/* stack for upto 256 parameters */
extern	struct	macxe	*stackp;	/* pointer to stack */
extern	struct	macxe	*mpp;		/* macro prototype pointer */
extern	uchrfp	hwrepsp;		/* repeat prototype pointer */
extern	int32	repdone;		/* number of repeats done */

/* hwcmac points to the macro symbol table entry defined by macss */
/* this is also the address stored in the symbol table entry for this macro */
/* hwcmac->desc.value then points to the actual macro storage */
/* hwcmac->desc.tmp has the size of the macro in bytes */
/* hwcmac->desc.flags has the number of parameters */
/* hwcmac->sym has the macro name */

extern	uchrfp	hwcmac;			/* holds ptr to body of latest macro */
extern	uchrfp	hwcmacp;		/* holds chaining ptr to form list */
extern	struct symbol FAR *dmstp;	/* address of macros symbol entry */

extern	char	*stkp;		/* pointer to parameter expansion area in stk */
extern	char	stk[];		/* 4k macro parameter substitution area */
/* stk contains multiple 24 char parameter names used during expansion */
/* it is pointed to by the level pointers in stackp->clev */

/* extern	struct macro *macp;	*/	/* address of macros */

/********************************/
/* variables defined in xref.c */
/********************************/

extern void xref_cmd();		/* send command to xref */
#define PASS1  0x01 		/* Starting pass 1 */
#define PASS2  0x02		/* Starting pass 2 */
#define DOXREF 0x04		/* Do xref */
#define NOXREF 0x08		/* No xref */
extern void writerpt();		/* output xref report */
extern FILE*ut2fd;		/* UT2 */
extern char *xrbuf;		/* xref buffer 768*20 */
extern void writerep();		/* output cross reference */
