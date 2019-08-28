/* mfile1.h */

/*
 * 	(c) Copyright 1995 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

/* $Id: mfile1.h,v 1.7 2019/01/31 21:57:26 jbev Exp $ */

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

/*
 * $Log: mfile1.h,v $
 * Revision 1.7  2019/01/31 21:57:26  jbev
 * Update for Linux
 *
 * Revision 1.6  1996/10/26 22:18:07  jbev
 * Alpha port fixes
 *
 * Revision 1.5  1996/03/20 21:35:50  jbev
 * Mods for alpha port.
 *
 * Revision 1.4  1995/03/06 19:18:32  jbev
 * Malloc tree node table instead of hard coding size.
 * Allow XTTval  and X2TTval to set node tree table size.
 * Add new option XJ and X2J to inhibit _ being prepended to names.
 * Correct XT[DS]val options for setting table sizes.
 *
 */

#include "macdefs.h"
#include "manifest.h"
#ifdef MYATOF
#include "float.h"
#endif

/*	storage classes  */
#define SNULL 0
#define AUTO 1
#define EXTERN 2
#define STATIC 3
#define REGISTER 4
#define EXTDEF 5
#define LABEL 6
#define ULABEL 7
#define MOS 8
#define PARAM 9
#define STNAME 10
#define MOU 11
#define UNAME 12
#define TYPEDEF 13
#define FORTRAN 14
#define ENAME 15
#define MOE 16
#define UFORTRAN 17
#define USTATIC 18
#define ABSLABEL 19
 /* field size is ORed in */
#define FIELD 0100
#define FLDSIZ 077
#ifndef BUG1
extern char    *scnames();
#endif

/*	location counters */
#define PROG 0
#define DATA 1
#define ADATA 2
#define STRNG 3
#define ISTRNG 4
#define STAB 5

#define FDATA 6

/* symbol table flags */
#define SMOS 01
#define SHIDDEN 02
#define SHIDES 04
#define SSET 010
#define SREF 020
#define SNONUNIQ 040
#define STAG 0100

# define IsLNAME 01	/* this variable is an atomic auto */
# define IsPNAME 02	/* this variable is an atomic param */
# define IsSREG 04	/* has this variable been pushed into a register */

#ifndef FIXDEF
#define FIXDEF(p)
#endif
#ifndef FIXARG
#define FIXARG(p)
#endif
#ifndef FIXSTRUCT
#define FIXSTRUCT(a,b)
#endif

 /* alignment of initialized quantities */
#ifndef AL_INIT
#define	AL_INIT ALINT
#endif

struct      symtab
{
    char       *sname;
    TWORD       stype;	/* type word */

    char        sclass;		/* storage class */
    char        slevel;		/* scope level */
    short       sflags;		/* flags for set, use, hidden, mos, etc. */
    char	optflags;	/* optimization flags */
    int         offset;		/* offset or value */
    short       dimoff;		/* offset into the dimension table */
    short       sizoff;		/* offset into the size table */
    short       suse;		/* line number of last use of the variable */
    short	uniqid;		/* unique identifier number in this function */
};


#ifndef ONEPASS

union       ndu
{
    struct {
	int         op;
	TWORD       type;
	int         cdim;
	int         csiz;
    }           fn;		/* front node */
    struct {
	int         op;
	TWORD       type;
	int         cdim;
	int         csiz;
	NODE       *left;
	NODE       *right;
    } in;			/* interior node */

    struct {
 /* this structure is the same as above, but is used when a value,
  * rather than address, is kept in +left */
	int         op;
	TWORD       type;
	int         cdim;
	int         csiz;
	long        lval;
	long        rval;
    } tn;			/* terminal node */

    struct {
 /* this structure is used when a floating point constant is being computed */
	int         op;
	TWORD       type;
	int         cdim;
	int         csiz;
#ifdef MYATOF
	FPN	    fpnum;
#else
	FP_DOUBLE   dval;
#endif
    } fpn;			/* floating point node */

};
#endif

#ifdef MPX
struct tstrngs /* structure for stuffing away strings for dsect output */
{
	int slabel;
	short length;
	char *strng;
	struct tstrngs *next;
};

extern struct tstrngs *begstrng;
extern struct tstrngs *currstng;

#endif

extern struct sw   *swp;
extern int  swx;

extern int  ftnno;
extern int  blevel;
extern int  instruct, stwart;
extern int  forcealign;		/* forced minimum alignment for struct/union */
				/* set by ALIGN directive (special comment) */
extern int  ininit;		/* in an initializer */
extern int  onlyuchar;		/* if true, only use unsigned chars, set by -XU */

#ifdef MPX			/* MPX has builtins */
extern int  dobuiltins;
#endif

extern int  lineno, nerrors;
typedef     union
{
    int         intval;
    NODE       *nodep;
}           YYSTYPE;
extern YYSTYPE  yylval;

extern CONSZ    lastcon;
extern FP_DOUBLE dcon;

extern char     ftitle[];
extern char     ititle[];
extern struct symtab    *stab;
extern int  curftn;
extern int  curclass;
extern int  curdim;
extern int  *dimtab;
extern int  paramstk[];
extern int  paramno;
extern int  autooff, argoff, strucoff;

extern int  regvar;
extern int  minrvar;
extern int  brkflag;
extern char     yytext[];

extern int  strflg;

extern OFFSZ    inoff;

extern int  reached;

/* tunnel to buildtree for name id's */

extern int  idname;

extern NODE    *nodep;
extern NODE    *lastfree;

extern int  cflag, hflag, pflag;

/* various labels */
extern int  brklab;
extern int  contlab;
extern int  flostat;
extern int  retlab;
extern int  retstat;

extern int  asavbc[], *psavbc;

/*	flags used in structures/unions */

#define SEENAME 01
#define INSTRUCT 02
#define INUNION 04
#define FUNNYNAME 010
#define TAGNAME 020

/*	flags used in the (elementary) flow analysis ... */

#define FBRK 02
#define FCONT 04
#define FDEF 010
#define FLOOP 020

/*	flags used for return status */

#define RETVAL 1
#define NRETVAL 2

/*	used to mark a constant with no name field */

#define NONAME 040000

 /* mark an offset which is undefined */

#define NOOFFSET (-10201)

/*	declarations of various functions */

extern      NODE
*buildtree(),
*bdty(),
*mkty(),
*rstruct(),
*dclstruct(),
*getstr(),
*tymerge(),
*stref(),
*offcon(),
*bcon(),
*bpsize(),
*convert(),
*pconvert(),
*oconvert(),
*ptmatch(),
*tymatch(),
*makety(),
*block(),
*doszof(),
*talloc(),
*optim(),
*strargs(),
*clocal();

OFFSZ tsize(),
psize();

TWORD types();

char       *exname(), *exdcon();

/* forward definitions */
extern void fixarg();
/*static int testtype();*/
extern void outstab();
extern void prcstab();
extern void pfstab();
extern void plcstab();
extern void psline();
extern void pstab();
/*static int entertype(); */
/*static void inittypes(); */
/*static void gentype(); */
/*static void genstruct(); */
/*static void geninfo(); */
extern void outstruct();
extern int locctr();
extern void cerror();
extern int lookup();
extern void walkf();
/*static void nwalkf(); */
extern void tprint();
extern void fwalk();
extern void deflab();
extern void def2lab();
extern int chkstr();
extern void chkpun();
extern int conval();
extern int isstrcon();
extern void p2tree();
extern void prtree();
extern void ecomp();
extern void prtdcon();
extern void putsman();
extern void eprint();
extern void DBprint();
extern void uerror();
extern void uderror();
extern void cerror();
extern void cderror();
extern void werror();
extern void wderror();
extern int moditype();
extern int opact();
extern int icons();
extern OFFSZ psize();
extern OFFSZ tsize();
extern int notlval();
extern int getlab();
extern int get2lab();
extern void tinit();
extern void tcheck();
extern void tfree();
extern void tfree1();
extern char *tstr();
extern void swepilog();
extern int readcoi();
extern int mainp1();
extern void lxenter();
extern void lxmore();
extern void lxinit();
extern void gettmpstr();
extern int settmpstr();
extern void lxstr();
extern void lxcom();
extern int yylex();
extern int lxres();
extern void lxtitle();
extern void asmout();
extern char *savestr();
extern char *hash();
extern void defid();
extern void StabInfoPrint();
extern void psave();
extern void ftnend();
extern void dclargs();
extern void moedef();
extern int bstruct();
extern void yyerror();
extern void yyaccpt();
extern void ftnarg();
extern int talign();
extern void inforce();
extern void vfdalign();
extern void beginit();
extern void instk();
extern void outbyte();
extern void endinit();
extern void doinit();
extern void gotscal();
extern void ilbrace();
extern void irbrace();
extern int upoff();
extern int oalloc();
extern int falloc();
extern void nidcl();
extern TWORD types();
extern void tyreduce();
extern void fixtype();
extern int uclass();
extern int fixclass();
extern void clearst();
extern void prstab();
extern void prsflags();
extern void pr_strdim();
extern void bccode();
extern int ctype();
extern int tlen();
extern void branch();
extern void defnam();
extern void dumpstr();
extern void putabyte();
extern void zecode();
extern void walkheap();
extern void makeheap();
extern int sselect();
extern int isnzs();
extern void negf();
extern void ecode();
extern void p2compile();
extern int divsk();
extern int fixcall();
extern int andable();
extern int nncon();
extern int ospow2();
extern int hide();
extern void dstash();
extern int CanBeLNAME();
extern int cisreg();
extern int fldal();
extern void efcode();
extern void cendarg();
extern void defalign();
extern void bfcode();
extern void lookat();
extern void vfdzero();
extern void cinit();
extern void incode();
extern void eprint();
extern void fincode();
extern void fldty();
extern int noinit();
extern void aobeg();
extern void aocode();
extern void aoend();
extern void unhide();
extern void movestab();
extern void zerof();
extern void LclReturn();
extern void lineid();
extern void p2bend();
extern void ParamFetch();
extern void p2bbeg();
extern void ejobcode();
extern void genswitch();
extern int getloi();
extern void defloi();
extern void p1init();
extern void p2init();
extern void mkdope();
extern int yyparse();
extern void putbyte();
extern int ispow2();
extern int isitfloat();

#define checkst(x)

#ifndef CHARCAST
/* to make character constants into character connstants */
/* this is a macro to defend against cross-compilers, etc. */
#define CHARCAST(x) (char)(x)
#endif

/* Dimension table is malloc in scan.c */
#define DIMTSZDEF 6000		/* was 1200 for 1 pass */
extern int DIMTABSZ;		/* size of the dimension/size table (was 800) */
/* Symbol table is malloc in scan.c */
#define SYMTSZDEF 4000		/* was 2000 for 1 pass */
extern int SYMTSZ;		/* size of the symbol table (was 1300) */

#ifdef TWOPASS
#define BCSZ 120	/*  (was 100) tbl size to save brk and cont lbls */
#define PARAMSZ 500 /* 150 */	/* size of the parameter stack */
#define SWITSZ 500	/*500*/	/* size of switch table */

#else

#define BCSZ 100	/*  (was 100) tbl size to save brk and cont lbls */
#define PARAMSZ 500 /* (500) 150 */	/* size of the parameter stack */
#define SWITSZ 250	/*500*/	/* size of switch table */
#endif

/*	special interfaces for yacc alone */
/*	These serve as abbreviations of 2 or more ops:
	ASOP	=, = ops
	RELOP	LE,LT,GE,GT
	EQUOP	EQ,NE
	DIVOP	DIV,MOD
	SHIFTOP	LS,RS
	ICOP	ICR,DECR
	UNOP	NOT,COMPL
	STROP	DOT,STREF

*/
#define ASOP 25
#define RELOP 26
#define EQUOP 27
#define DIVOP 28
#define SHIFTOP 29
#define INCOP 30
#define UNOP 31
#define STROP 32

#define LP 50
#define RP 51
#define LC 52
#define RC 53

NODE       *noshftfld();
NODE       *stref();
NODE       *strargs();
NODE       *buildtree();
NODE       *doszof();
NODE       *block();
NODE       *makety();
NODE       *tymatch();
NODE       *ptmatch();
NODE       *oconvert();
NODE       *pconvert();
void       econvert();
NODE       *bpsize();
NODE       *bcon();
extern NODE *talloc();
extern NODE *rstruct();
extern NODE *dclstruct();
extern NODE *getstr();
extern NODE *tymerge();

extern char *domalloc();
char       *hash();
char       *savestr();
extern int contype;
#ifndef BUG1
extern int  bdebug, idebug, tdebug, ddebug, edebug, xdebug, ydebug;
extern void eprint();
#endif

extern int sizeofflag; /* make sizeof string not generate data */

