#ifndef _STDLIB_H
#define _STDLIB_H
 
#ident  "@(#)nbinclude:stdlib.h      1.0"
 
typedef struct {
         int    quot;
         int    rem;
        } div_t;
 
typedef struct {
         long   quot;
         long   rem;
        } ldiv_t;
 
#ifndef _SIZE_T
#define _SIZE_T
/*typedef unsigned int    size_t;*/
/*#ifndef size_t*/
/*#undef size_t*/
typedef long    size_t;
/*#endif*/
#endif
 
#ifndef NULL
#define NULL            0
#endif

#define EXIT_FAILURE    1
#define EXIT_SUCCESS    0
#define RAND_MAX        32767
 
#ifndef _WCHAR_T
#define _WCHAR_T
typedef long wchar_t;
#endif
 
/*extern unsigned char    _ctype[];*/
extern char    _ctype[];
 
#define MB_CUR_MAX      _ctype[520]
 
extern double atof();
extern int atoi();
extern long int atol();
extern double strtod();
extern long int strtol();
extern unsigned long strtoul();
 
extern int rand();
extern void srand();
 
extern char *calloc();
extern void free();
extern char *malloc();
extern char *realloc();
 
extern void abort();
extern int atexit();
extern void exit();
extern char *getenv();
extern int system();
 
extern char *bsearch();
extern void qsort();
 
extern int abs();
extern div_t div();
extern long int labs();
extern ldiv_t ldiv();
 
extern int mbtowc();
extern int mblen();
extern int wctomb();
 
extern size_t mbstowcs();
extern size_t wcstombs();
 
extern long a64l();
extern int dup2();
extern char *ecvt();
extern char *fcvt();
extern char *getcwd();
extern char *getlogin();
extern int getopt();
extern int getsubopt();
extern char *optarg;
extern int optind, opterr, optopt;
extern char *getpass();
extern int getpw();
extern char *gcvt();
extern int isatty();
extern void l3tol();
extern char *l64a();
extern void ltol3();
extern char *memalign();
extern char *mktemp();
extern int putenv();
extern char *realpath();
extern void swab();
extern char *ttyname();
extern int ttyslot();
extern char *valloc();
 
extern double drand48();
extern double erand48();
extern long jrand48();
extern void lcong48();
extern long lrand48();
extern long mrand48();
extern long nrand48();
extern unsigned short *seed48();
extern void srand48();
 
#define mblen(s, n)     mbtowc((wchar_t *)0, s, n)
 
#endif  /* _STDLIB_H */
