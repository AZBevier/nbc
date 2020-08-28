/* caid.c */
/* test program for AID for C debugger */

/* include a file */
#include "caid.h"
#include <stdio.h>

unsigned int	i;	/* a global variable */
static int j;	/* a local variable */
typedef int MEM;	/* typedefed */
/* extern int b;	/* an external */
char justc[6];		/* char array */
char justd[6][4];	/* 2 dim array */
char juste[6][4][5];	/* 3 dim array */
short sary[4];		/* short array */
int iary[5];		/* int array */
int *ipary[3];		/* int pointer array */
char alongname[] = "abcdefghijklmnopqrstuvwxyz";
enum numsy {zero, one, two, three, four};	/* an enumeration */
int ***nono;
int b;		/* an external */
MEM glob = 47;
int *ip = &glob;	/* an integer pointer */
int **aptr;	/* pointer to array of pointers */
short **sptr;	/* a short one */
char notused;

static struct mytest {
  char nchar0;
  short nhw0;
} newtest0 = {0,0};

static struct {
  char char0;
  short hw0;
} test0 = {0,0};

struct {
  char char1;
  short hw1;
} test1 = {0,0};

struct test2 {
    char abc;
    short asht;
    unsigned int bits:19;
};

static struct test2 stest2;
struct test2 ttest2;

struct play {
    union {
    	int aa;		/* a 32 bit word */
    	short bb[2];	/* two 16 bit words */
    } mary;		/* name of union */
    char c;
    unsigned bitv:6;	/* six bits */
    unsigned bity:6;	/* six more */
    unsigned bitval:4;	/* 4 bits */
    struct test2 extstr2; /* ext defined structure */
    int * gg;
    struct {
    	int * smallarray[4];
    	char littleone[2];
    	double fpnumbers[2];
    	struct mary * bigmarys;
    	struct {
    	    int firstone;
    	    char offset;
    	    union {
    		double fpnn;
    		char bytes[8];
    		int words[2];
    	    } level3;
    	} level2;
    } bigjohn;
    struct play * pp;
    char * line;
    double dw;
} john[4];		/* an array of them */
static int entry4();	/* define a function */

int main(a, sp)
register int a;
struct play * sp;
{
    a=0; i=0; j=1;
    sp->c = 0;
    sp->mary.aa = a;
    sp->mary.bb[1] = 0;
    sp->bity = 0;
    sp->bigjohn.fpnumbers[1] = 0;
    sp->bigjohn.level2.firstone = 0;
    sp->bigjohn.level2.level3.fpnn = 0;
    sp->dw = 0;
    entry4();		/* do call chain */
}

int entry1(param1, pp2)
int param1;
int **pp2;		/* point to array of pointers */
{
    /* start of this function */
    i = param1;		/* assignment to global */
    j = param1;		/* assignment to static */
    b =                 /* this is a long line */                  i                    *       /* still long */        j;
    i = **pp2;		/* set the indirect value */
}

short ** entry2(param2, iptr)
int param2;
int * iptr;
{
    int * jjk = iptr;	/* a pointer */
    /* start of this function */
    i = param2;		/* assignment to global */
    j = param2;		/* assignment to static */
    entry1(j, aptr);	/* call someone */
    return (sptr);	/* return short ** */
}

int entry3()
{
    int k;		/* a stack variable */
    struct play * sp = john;

    k = i;		/* stack assignment to global */
    k = j;		/* stack assignment to local */
    sp->mary.aa = j;	/* stack assignment to union in struct */
    entry2(k, ip);	/* two level call */
}

static int for_mike;	/* just between functions */
int	to_mike;	/* a global */

static int entry4()
{
    int l;
    static int lll;

    l = i;
    {			/* level 1 */
    	int ss;		/* a stack variable */
    	static int sss;	/* should be just a local */

    	ss = sss;
    	{			/* level 2 */
    	    int ss2;		/* a stack variable */
    	    static int sss2;	/* should be just a local */

    	    sss = sss2;
    	    ss2 = sss2;
    	}
    }
    entry3();			/* another call */
}
