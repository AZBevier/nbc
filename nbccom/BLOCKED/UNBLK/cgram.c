 
# line 2 "cgram.y"
/* cgram.y */
 
/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */
 
#ifndef lint
static char *rcsid =
"@(#) (Gould) $Header: /u/nbc/nbccom/RCS/cgram.y,v 1.3 1995/02/10 18:44:17 jbev Exp $";
#endif
# define NAME 2
# define STRING 3
# define ICON 4
# define FCON 5
# define PLUS 6
# define MINUS 8
# define MUL 11
# define AND 14
# define OR 17
# define ER 19
# define QUEST 21
# define COLON 22
# define ANDAND 23
# define OROR 24
# define ASOP 25
# define RELOP 26
# define EQUOP 27
# define DIVOP 28
# define SHIFTOP 29
# define INCOP 30
# define UNOP 31
# define STROP 32
# define TYPE 33
# define CLASS 34
# define STRUCT 35
# define RETURN 36
# define GOTO 37
# define IF 38
# define ELSE 39
# define SWITCH 40
# define BREAK 41
# define CONTINUE 42
# define WHILE 43
# define DO 44
# define FOR 45
# define DEFAULT 46
# define CASE 47
# define SIZEOF 48
# define ENUM 49
# define LP 50
# define RP 51
# define LC 52
# define RC 53
# define LB 54
# define RB 55
# define CM 56
# define SM 57
# define ASSIGN 58
# define ASM 59
 
# line 131 "cgram.y"
#include "mfile1.h"
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
typedef int yytabelem;
 
# line 150 "cgram.y"
	static int fake = 0;
#ifndef FLEXNAMES
	static char fakename[NCHNAM+1];
#else
	static char fakename[24];
#endif
# define YYERRCODE 256
 
# line 905 "cgram.y"
 
 
NODE *
mkty( t, d, s ) unsigned t; {
	NODE *p;
	p = block( TYPE, NIL, NIL, t, d, s );
#ifndef BUG1
	if(ddebug) {
		printf("mkty(t=0x%x, d=%d, s=%d) returning %x\n",
			t, d, s, p);
		fwalk(p, eprint, 0);
	}
#endif
	return(p);
	}
 
NODE *
bdty( op, p, v ) NODE *p; {
	register NODE *q;
 
	q = block( op, p, NIL, INT, 0, INT );
 
	switch( op ){
 
	case UNARY MUL:
	case UNARY CALL:
		break;
 
	case LB:
		q->in.right = bcon(v);
		break;
 
	case NAME:
		q->tn.rval = v;
		break;
 
	default:
		cerror( "bad bdty" );
		}
 
#ifndef BUG1
	if(ddebug) {
		printf("bdty(op=%s, p=0x%x, v=0x%x) returning 0x%x\n",
			opst[op], p, v, q);
		fwalk(q, eprint, 0);
	}
#endif
 
	return( q );
	}
 
dstash( n ){ /* put n into the dimension table */
	if( curdim >= DIMTABSZ-1 ){
		cerror( "dimension table overflow");
		}
	dimtab[ curdim++ ] = n;
	}
 
savebc() {
	if( psavbc > & asavbc[BCSZ-4 ] ){
		cerror( "whiles, fors, etc. too deeply nested");
		}
	*psavbc++ = brklab;
	*psavbc++ = contlab;
	*psavbc++ = flostat;
	*psavbc++ = swx;
	flostat = 0;
	}
 
resetbc(mask){
 
	swx = *--psavbc;
	flostat = *--psavbc | (flostat&mask);
	contlab = *--psavbc;
	brklab = *--psavbc;
 
	}
 
addcase(p) NODE *p; { /* add case to switch */
 
	p = optim( p );  /* change enum to ints */
	if( p->in.op != ICON ){
		uerror( "non-constant case expression");
		return;
		}
	if( swp == swtab ){
		uerror( "case not in switch");
		return;
		}
	if( swp >= &swtab[SWITSZ] ){
		cerror( "switch table overflow");
		}
	swp->sval = p->tn.lval;
	deflab( swp->slab = getlab() );
	++swp;
	tfree(p);
	}
 
adddef(){ /* add default case to switch */
	if( swtab[swx].slab >= 0 ){
		uerror( "duplicate default in switch");
		return;
		}
	if( swp == swtab ){
		uerror( "default not inside switch");
		return;
		}
	deflab( swtab[swx].slab = getlab() );
	}
 
swstart(){
	/* begin a switch block */
	if( swp >= &swtab[SWITSZ] ){
		cerror( "switch table overflow");
		}
	swx = swp - swtab;
	swp->slab = -1;
	++swp;
	}
 
swend(){ /* end a switch block */
 
	register struct sw *swbeg, *p, *q, *r, *r1;
	CONSZ temp;
	int tempi;
 
	swbeg = &swtab[swx+1];
 
	/* sort */
 
	r1 = swbeg;
	r = swp-1;
 
	while( swbeg < r ){
		/* bubble largest to end */
		for( q=swbeg; q<r; ++q ){
			if( q->sval > (q+1)->sval ){
				/* swap */
				r1 = q+1;
				temp = q->sval;
				q->sval = r1->sval;
				r1->sval = temp;
				tempi = q->slab;
				q->slab = r1->slab;
				r1->slab = tempi;
				}
			}
		r = r1;
		r1 = swbeg;
		}
 
	/* it is now sorted */
 
	for( p = swbeg+1; p<swp; ++p ){
		if( p->sval == (p-1)->sval ){
			uerror( "duplicate case in switch, %d", tempi=p->sval );
			return;
			}
		}
 
	swepilog( swbeg-1, swp-swbeg );
	swp = swbeg-1;
	}
 
#ifndef BUG1
lookaround(yypvt)
register YYSTYPE *yypvt;
{
	register i;
	extern int eprint();
 
	for(i = (-6); i < 4; i++) {
		printf("yypvt[%d].nodep = %x\n", i, yypvt[i].nodep);
#ifdef linux
		if((yypvt[i].nodep > (NODE *) 0x20000) &&
		  (yypvt[i].nodep < (NODE *) 0x800000))
#else
		if(yypvt[i].nodep > (NODE *) 0x200000)
#endif
			fwalk(yypvt[i].nodep, eprint, 0);
	}
}
#endif
 
yytabelem yyexca[] ={
-1, 1,
	0, -1,
	2, 24,
	11, 24,
	50, 24,
	57, 24,
	-2, 0,
-1, 21,
	56, 82,
	57, 82,
	-2, 8,
-1, 26,
	56, 81,
	57, 81,
	-2, 80,
-1, 34,
	52, 47,
	-2, 45,
-1, 36,
	52, 39,
	-2, 37,
-1, 59,
	53, 51,
	57, 51,
	-2, 0,
-1, 111,
	33, 19,
	34, 19,
	35, 19,
	49, 19,
	-2, 14,
-1, 269,
	33, 17,
	34, 17,
	35, 17,
	49, 17,
	-2, 15,
-1, 286,
	33, 18,
	34, 18,
	35, 18,
	49, 18,
	-2, 16,
	};
# define YYNPROD 181
# define YYLAST 976
yytabelem yyact[]={
 
   205,   133,   251,    29,   226,    91,    89,    90,    29,   203,
    82,    79,    23,    80,    20,    95,    81,    23,    11,    10,
    15,   100,   149,    98,    94,   207,    29,   102,    48,   194,
    38,   286,    84,    83,    17,    23,   134,   112,   216,   217,
   221,     7,   225,   214,   215,   222,   223,   224,   228,   227,
    85,    24,    86,    77,   112,   243,    24,    61,   165,   218,
   300,   206,    29,   269,    11,    10,    15,    29,   168,   260,
   114,    23,    58,   259,    24,    22,    23,    47,    53,   135,
    17,    19,    98,   246,   245,   158,   201,   150,   154,   299,
     4,   105,   142,   143,   144,   145,   146,   147,    38,    37,
   293,   280,   255,   254,   198,   166,    93,   109,    18,   197,
    24,   187,    72,    68,   159,    24,   237,    73,   170,   171,
   172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
   182,   183,   184,   185,   164,   158,   101,   135,   188,   103,
   189,   287,    50,    96,   275,    26,    51,   237,   272,   150,
    21,   226,    91,    89,    90,   186,   273,    82,    40,   162,
    80,   116,    41,    81,   113,    76,   157,    43,    45,    42,
    44,   191,    40,    71,    50,    70,    41,    35,    51,    84,
    83,    75,    67,   231,   161,   216,   217,   221,   135,   225,
   214,   215,   222,   223,   224,   228,   227,    85,   241,    86,
   196,   112,   204,   156,   236,    97,   218,   104,   206,    33,
   233,   229,   160,   252,   295,   242,   163,   257,   247,   248,
   249,   250,   278,   253,   232,   239,   240,   235,   267,    50,
   261,   271,   138,    51,   140,   192,   202,    74,    66,   195,
   238,   110,     9,   289,   270,    29,   288,   236,   265,   266,
   196,    30,   141,   264,    23,    97,   139,    99,   219,   263,
   262,   155,    28,   281,   282,   252,   284,   283,    54,   226,
    91,    89,    90,   200,    55,    82,    59,   155,    80,   277,
    28,    81,    49,    11,    10,    15,   276,     5,   290,   195,
   296,    10,    56,    24,   252,    32,   297,    84,    83,    17,
   268,   123,   258,   216,   217,   221,   190,   225,   214,   215,
   222,   223,   224,   228,   227,    85,    99,    86,   119,   112,
   120,    28,   121,    62,   218,   123,   206,   115,   125,   151,
    11,   126,    15,   127,     8,   130,    59,   128,   129,   131,
   117,   124,   119,   122,    31,    97,    17,    88,    91,    89,
    90,   274,    36,    82,    69,    34,    80,   220,   120,    81,
   121,   111,   108,   123,   107,   298,   120,   136,   121,    52,
   118,   123,   132,   104,   125,    84,    83,   126,    63,   127,
   119,   130,    46,   128,   129,   131,   117,   124,   119,   122,
   199,   151,    92,    85,    57,    86,    60,   137,   169,   167,
   106,    65,   120,    64,   121,   219,    39,   123,     3,     2,
   125,   294,    27,   126,   153,   127,   118,   130,   132,   128,
   129,   131,   117,   124,   119,   122,    87,    12,    13,     6,
    25,    14,    16,   213,   211,   212,   210,   208,   120,   209,
   121,     1,     0,   123,     0,     0,   125,   292,     0,   126,
     0,   127,   118,   130,   132,   128,   129,   131,   117,   124,
   119,   122,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   120,     0,   121,     0,
   120,   123,   121,   291,   125,   123,     0,   126,   118,   127,
   132,   130,   285,   128,   129,   131,   117,   124,   119,   122,
   117,   124,   119,   122,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   120,     0,   121,     0,     0,   123,
     0,     0,   125,   219,     0,   126,   118,   127,   132,   130,
     0,   128,   129,   131,   117,   124,   119,   122,   120,     0,
   121,     0,     0,   123,     0,   120,   125,   121,     0,   126,
   123,   127,     0,   130,     0,   128,   129,   131,   117,   124,
   119,   122,     0,     0,   118,   279,   132,   119,   122,     0,
     0,     0,   120,     0,   121,     0,     0,   123,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   118,   244,
   132,   120,   117,   121,   119,   122,   123,     0,     0,   125,
     0,     0,   126,     0,   127,     0,   130,     0,   128,   129,
   131,   117,   124,   119,   122,   120,     0,   121,     0,     0,
   123,     0,     0,   125,     0,     0,   126,     0,   127,     0,
   130,   230,   128,   129,   131,   117,   124,   119,   122,     0,
   234,   118,     0,   132,     0,     0,     0,     0,     0,     0,
     0,   120,     0,   121,     0,   120,   123,   121,     0,   125,
   123,     0,   126,   125,   127,   118,   130,   132,   128,   129,
   131,   117,   124,   119,   122,   117,   124,   119,   122,     0,
     0,     0,     0,     0,     0,     0,     0,   120,     0,   121,
     0,     0,   123,     0,     0,   125,   193,     0,   126,     0,
   127,   118,   130,   132,   128,   129,   131,   117,   124,   119,
   122,   120,     0,   121,     0,     0,   123,     0,     0,   125,
     0,     0,   126,     0,   127,     0,   130,     0,   128,   129,
   131,   117,   124,   119,   122,     0,     0,   118,     0,   132,
    88,    91,    89,    90,     0,     0,    82,     0,     0,    80,
     0,     0,    81,     0,     0,     0,    88,    91,    89,    90,
     0,     0,     0,   132,     0,     0,     0,     0,    84,    83,
    88,    91,    89,    90,     0,     0,    82,     0,     0,    80,
     0,     0,    81,     0,    84,    83,    85,     0,    86,     0,
     0,     0,   120,     0,   121,   256,     0,   123,    84,    83,
   125,    11,    85,    15,    86,   127,     0,     0,     0,     0,
     0,     0,   117,   124,   119,   122,    85,    17,    86,    88,
    91,    89,    90,     0,     0,    82,     0,     0,    80,     0,
     0,    81,    88,    91,    89,    90,     0,     0,    82,     0,
     0,    80,     0,     0,    81,     0,     0,    84,    83,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    84,    83,     0,     0,     0,    85,     0,    86,     0,    78,
    88,    91,    89,    90,     0,     0,    82,     0,    85,    80,
    86,   152,    81,    88,    91,    89,    90,     0,     0,    82,
     0,     0,    80,     0,     0,    81,     0,     0,    84,    83,
     0,     0,   120,     0,   121,     0,     0,   123,     0,     0,
   125,    84,    83,   126,     0,   127,    85,   130,    86,   128,
   129,     0,   117,   124,   119,   122,     0,     0,   120,    85,
   121,   148,     0,   123,     0,     0,   125,     0,     0,   126,
     0,   127,     0,     0,     0,   128,     0,     0,   117,   124,
   119,   122,   120,     0,   121,     0,     0,   123,     0,     0,
   125,     0,     0,   126,     0,   127,     0,     0,     0,     0,
     0,     0,   117,   124,   119,   122 };
yytabelem yypact[]={
 
 -1000,    31, -1000, -1000,    51, -1000,    24, -1000,   297,   257,
 -1000,   262, -1000, -1000,   157,   353,   125,   350, -1000, -1000,
    42,   108, -1000,   243,   243,    26,   179,    20, -1000,   218,
 -1000,   297,   259,   297, -1000,   321, -1000, -1000, -1000, -1000,
   187,   127,   179,   108,   124,   122,    61, -1000, -1000, -1000,
   186,   126,   817, -1000, -1000, -1000, -1000,    49, -1000,    60,
    80, -1000,   -31,    65, -1000,   -15, -1000, -1000,   109,   868,
 -1000, -1000, -1000,   325, -1000, -1000,   106,   705,   345,   202,
   868,   868,   868,   868,   868,   881,   768,   830,   211, -1000,
 -1000, -1000,   150,   297,    79, -1000,   108,    92, -1000, -1000,
   131,   321, -1000, -1000,   108, -1000, -1000, -1000, -1000,     1,
    48, -1000, -1000, -1000,   705, -1000, -1000,   868,   868,   868,
   868,   868,   868,   868,   868,   868,   868,   868,   868,   868,
   868,   868,   868,    55, -1000,   705,   345, -1000, -1000,   868,
   304, -1000,   202,   202,   202,   202,   202,   202,   768,   184,
   645,   239, -1000,    53,   705, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000,    29, -1000, -1000, -1000,   149,   250,
   539,   705, -1000,   290,   290,   352, -1000,   566,   474,   786,
   649,   946,   922,   609,   705,   705,   130,   345,    55,   585,
 -1000,   176,   868, -1000,    62,   189,   239,   868, -1000,    60,
 -1000, -1000,     2, -1000, -1000,   532,    27, -1000,   267,   267,
   267,   267,   868,   267,    46,    45,   738,   300, -1000,    16,
   267,   210,   209, -1000,   203,   198,   227,   868,   278,     6,
   868, -1000, -1000,    95, -1000,   754,   202,   101, -1000,    93,
    62,   705, -1000, -1000, -1000, -1000, -1000,   247, -1000, -1000,
   236,   171,   681, -1000, -1000, -1000, -1000,   508,    44, -1000,
 -1000, -1000,   868,   868,   868,   868, -1000,   470, -1000, -1000,
   -26,   896, -1000, -1000,    86,   196, -1000,   193,   267, -1000,
 -1000,   432,   396,    43,   360, -1000, -1000, -1000,   163,   868,
 -1000, -1000, -1000,   868, -1000, -1000,   314,    32,     3, -1000,
 -1000 };
yytabelem yypgo[]={
 
     0,   441,   113,   439,   437,   436,   435,   434,   433,   432,
   431,   430,     0,     2,    11,    41,   429,   242,   428,   427,
    22,    29,   426,    15,   143,   145,   414,   412,   409,   408,
    14,   406,   403,   401,    25,   400,    68,     9,   399,   398,
    24,   334,   396,    21,    57,   394,   392,    72,   390,   382,
    75,   378,   369,     1,    36,   367,   364,   362,   361,   357,
   354 };
yytabelem yyr1[]={
 
     0,     1,     1,    28,    28,    28,    29,    29,    31,    29,
    32,    33,    33,    36,    36,    38,    38,    39,    39,    39,
    35,    35,    35,    16,    16,    15,    15,    15,    15,    15,
    41,    17,    17,    17,    17,    17,    18,    18,     9,     9,
    42,    42,    44,    44,    19,    19,    10,    10,    45,    45,
    47,    47,    40,    48,    40,    23,    23,    23,    23,    23,
    25,    25,    25,    25,    25,    25,    24,    24,    24,    24,
    24,    24,    24,    11,    49,    49,    49,    30,    51,    30,
    27,    50,    50,    50,    50,    50,    53,    53,    54,    54,
    43,    43,    46,    46,    52,    52,    55,    34,    34,    56,
    57,    58,    37,    37,    37,    37,    37,    37,    37,    37,
    37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
    37,    59,    59,    59,     7,     4,     3,     5,     6,     8,
    60,     2,    13,    13,    26,    26,    12,    12,    12,    12,
    12,    12,    12,    12,    12,    12,    12,    12,    12,    12,
    12,    12,    12,    14,    14,    14,    14,    14,    14,    14,
    14,    14,    14,    14,    14,    14,    14,    14,    14,    14,
    14,    20,    21,    21,    21,    21,    21,    21,    21,    22,
    22 };
yytabelem yyr2[]={
 
     0,     4,     1,     3,     5,     3,     5,     7,     1,     9,
     4,     4,     1,     4,     1,     7,     9,     7,     9,     0,
     7,     5,     5,     2,     1,     5,     4,     3,     3,     7,
     3,     2,     5,     7,     2,     2,    11,     5,     3,     5,
     2,     6,     3,     7,    11,     5,     3,     5,     2,     6,
     5,     3,     3,     1,     9,     2,     2,     7,     5,     3,
     5,     7,     7,     9,     3,     7,     5,     7,     7,     9,
     7,     7,     5,     5,     3,     7,     2,     2,     1,     8,
     3,     3,     3,     7,    13,     2,     2,     6,     3,     9,
     0,     2,     0,     2,     1,     2,     3,     2,     2,     9,
     7,     3,     5,     5,     5,     2,     5,     5,     5,    15,
     9,     5,     5,     5,     5,     7,     7,     2,     4,     4,
     4,     5,     7,     5,     3,     9,     7,     9,    13,     9,
     1,     5,     2,     1,     2,     7,     7,     7,     7,     7,
     7,     7,     7,     7,     7,     7,     7,     7,     7,    11,
     7,     7,     2,     5,     5,     5,     5,     5,     5,     5,
     9,     9,     9,     5,     7,     7,     3,     3,     3,     3,
     7,     5,     1,     5,    11,     5,     7,     9,     7,     5,
     4 };
yytabelem yychk[]={
 
 -1000,    -1,   -28,   -29,    59,   256,   -16,   -15,   -41,   -17,
    34,    33,   -19,   -18,   -10,    35,    -9,    49,    57,    57,
   -30,   -24,   -50,    11,    50,   -11,   -25,   -27,   256,     2,
   -17,   -41,    33,    52,     2,    52,     2,    57,    56,   -31,
    50,    54,   -25,   -24,   -25,   -24,   -49,    51,     2,   256,
    50,    54,   -52,    58,    50,   -17,    33,   -45,   -47,   -17,
   -42,   -44,     2,   -51,   -32,   -33,    51,    55,    -2,   -60,
    51,    51,    51,    56,    51,    55,    -2,   -12,    52,   -14,
    11,    14,     8,    31,    30,    48,    50,   -22,     2,     4,
     5,     3,   -46,    57,   -40,   -23,   -24,   -25,    22,   256,
   -43,    56,    58,   -50,   -24,   -34,   -35,   -56,   -57,   -15,
   256,   -58,    52,    55,   -12,     2,    55,    26,    56,    28,
     6,     8,    29,    11,    27,    14,    17,    19,    23,    24,
    21,    25,    58,   -53,   -54,   -12,   -55,    52,    30,    54,
    32,    50,   -14,   -14,   -14,   -14,   -14,   -14,    50,   -20,
   -12,   -17,    51,   -26,   -12,    50,    53,   -47,    56,    22,
    -2,    53,   -44,    -2,   -40,    57,    57,   -38,   -36,   -39,
   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
   -12,   -12,   -12,   -12,   -12,   -12,   -43,    56,   -53,   -12,
     2,   -20,    51,    51,   -21,    50,    11,    56,    51,   -48,
    -2,    57,   -36,   -37,    53,   -12,    59,   -34,    -4,    -3,
    -5,    -7,    -6,    -8,    41,    42,    36,    37,    57,   256,
   -59,    38,    43,    44,    45,    40,     2,    47,    46,   -15,
    22,    53,   -54,   -43,    55,    51,   -14,    54,    51,   -21,
   -21,   -12,   -23,    53,    57,    57,    56,   -37,   -37,   -37,
   -37,   -13,   -12,   -37,    57,    57,    57,   -12,     2,    57,
    53,   -37,    50,    50,    50,    50,    22,   -12,    22,    57,
   -30,   -12,    53,    55,    -2,    51,    39,    43,    51,    57,
    57,   -12,   -12,   -13,   -12,    22,    57,    55,    50,    50,
   -37,    51,    51,    57,    51,    51,   -12,   -13,    51,    57,
    57 };
yytabelem yydef[]={
 
     2,    -2,     1,     3,     0,     5,     0,    23,    27,    28,
    30,    31,    34,    35,     0,    46,     0,    38,     4,     6,
     0,    -2,    77,     0,     0,     0,    -2,    94,    85,    64,
    25,    26,    32,     0,    -2,     0,    -2,     7,    78,    12,
     0,   130,    60,    66,     0,     0,     0,    72,    74,    76,
     0,   130,     0,    95,    73,    29,    33,    92,    48,    -2,
    90,    40,    42,     0,     9,     0,    67,    68,     0,     0,
    65,    70,    71,     0,    61,    62,     0,    83,     0,   152,
     0,     0,     0,     0,     0,     0,     0,     0,   166,   167,
   168,   169,     0,    93,    50,    52,    55,    56,   130,    59,
     0,    91,   130,    79,    82,    10,    11,    97,    98,     0,
     0,    -2,   101,    69,   131,    75,    63,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    90,    86,    88,     0,    96,   153,     0,
     0,   180,   154,   155,   156,   157,   158,   159,     0,     0,
     0,   172,   163,     0,   134,   179,    44,    49,    53,   130,
    58,    36,    41,    43,     0,    21,    22,    14,     0,     0,
   136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
   146,   147,   148,     0,   150,   151,     0,    91,    90,     0,
   165,     0,     0,   170,   171,   172,   172,     0,   164,     0,
    57,    20,     0,    13,   100,     0,     0,   105,     0,     0,
     0,     0,   133,     0,     0,     0,     0,     0,   117,     0,
     0,     0,     0,   124,     0,     0,   166,     0,     0,     0,
     0,    84,    87,     0,   162,   161,   160,   130,   173,     0,
   175,   135,    54,    99,   102,   103,   104,   106,   107,   108,
     0,     0,   132,   111,   112,   113,   114,     0,     0,   118,
   119,   120,     0,     0,   133,     0,   121,     0,   123,    -2,
     0,   149,    89,   176,     0,   178,   126,     0,     0,   115,
   116,     0,     0,     0,     0,   122,    -2,   177,     0,     0,
   110,   125,   127,   133,   129,   174,     0,     0,     0,   128,
   109 };
typedef struct { char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif
 
#if YYDEBUG
 
yytoktype yytoks[] =
{
	"NAME",	2,
	"STRING",	3,
	"ICON",	4,
	"FCON",	5,
	"PLUS",	6,
	"MINUS",	8,
	"MUL",	11,
	"AND",	14,
	"OR",	17,
	"ER",	19,
	"QUEST",	21,
	"COLON",	22,
	"ANDAND",	23,
	"OROR",	24,
	"ASOP",	25,
	"RELOP",	26,
	"EQUOP",	27,
	"DIVOP",	28,
	"SHIFTOP",	29,
	"INCOP",	30,
	"UNOP",	31,
	"STROP",	32,
	"TYPE",	33,
	"CLASS",	34,
	"STRUCT",	35,
	"RETURN",	36,
	"GOTO",	37,
	"IF",	38,
	"ELSE",	39,
	"SWITCH",	40,
	"BREAK",	41,
	"CONTINUE",	42,
	"WHILE",	43,
	"DO",	44,
	"FOR",	45,
	"DEFAULT",	46,
	"CASE",	47,
	"SIZEOF",	48,
	"ENUM",	49,
	"LP",	50,
	"RP",	51,
	"LC",	52,
	"RC",	53,
	"LB",	54,
	"RB",	55,
	"CM",	56,
	"SM",	57,
	"ASSIGN",	58,
	"ASM",	59,
	"-unknown-",	-1	/* ends search */
};
 
char * yyreds[] =
{
	"-no such reduction-",
	"ext_def_list : ext_def_list external_def",
	"ext_def_list : /* empty */",
	"external_def : data_def",
	"external_def : ASM SM",
	"external_def : error",
	"data_def : oattributes SM",
	"data_def : oattributes init_dcl_list SM",
	"data_def : oattributes fdeclarator",
	"data_def : oattributes fdeclarator function_body",
	"function_body : arg_dcl_list compoundstmt",
	"arg_dcl_list : arg_dcl_list declaration",
	"arg_dcl_list : /* empty */",
	"stmt_list : stmt_list statement",
	"stmt_list : /* empty */",
	"r_dcl_stat_list : dcl_stat_list attributes SM",
	"r_dcl_stat_list : dcl_stat_list attributes init_dcl_list SM",
	"dcl_stat_list : dcl_stat_list attributes SM",
	"dcl_stat_list : dcl_stat_list attributes init_dcl_list SM",
	"dcl_stat_list : /* empty */",
	"declaration : attributes declarator_list SM",
	"declaration : attributes SM",
	"declaration : error SM",
	"oattributes : attributes",
	"oattributes : /* empty */",
	"attributes : class type",
	"attributes : type class",
	"attributes : class",
	"attributes : type",
	"attributes : type class type",
	"class : CLASS",
	"type : TYPE",
	"type : TYPE TYPE",
	"type : TYPE TYPE TYPE",
	"type : struct_dcl",
	"type : enum_dcl",
	"enum_dcl : enum_head LC moe_list optcomma RC",
	"enum_dcl : ENUM NAME",
	"enum_head : ENUM",
	"enum_head : ENUM NAME",
	"moe_list : moe",
	"moe_list : moe_list CM moe",
	"moe : NAME",
	"moe : NAME ASSIGN con_e",
	"struct_dcl : str_head LC type_dcl_list optsemi RC",
	"struct_dcl : STRUCT NAME",
	"str_head : STRUCT",
	"str_head : STRUCT NAME",
	"type_dcl_list : type_declaration",
	"type_dcl_list : type_dcl_list SM type_declaration",
	"type_declaration : type declarator_list",
	"type_declaration : type",
	"declarator_list : declarator",
	"declarator_list : declarator_list CM",
	"declarator_list : declarator_list CM declarator",
	"declarator : fdeclarator",
	"declarator : nfdeclarator",
	"declarator : nfdeclarator COLON con_e",
	"declarator : COLON con_e",
	"declarator : error",
	"nfdeclarator : MUL nfdeclarator",
	"nfdeclarator : nfdeclarator LP RP",
	"nfdeclarator : nfdeclarator LB RB",
	"nfdeclarator : nfdeclarator LB con_e RB",
	"nfdeclarator : NAME",
	"nfdeclarator : LP nfdeclarator RP",
	"fdeclarator : MUL fdeclarator",
	"fdeclarator : fdeclarator LP RP",
	"fdeclarator : fdeclarator LB RB",
	"fdeclarator : fdeclarator LB con_e RB",
	"fdeclarator : LP fdeclarator RP",
	"fdeclarator : name_lp name_list RP",
	"fdeclarator : name_lp RP",
	"name_lp : NAME LP",
	"name_list : NAME",
	"name_list : name_list CM NAME",
	"name_list : error",
	"init_dcl_list : init_declarator",
	"init_dcl_list : init_dcl_list CM",
	"init_dcl_list : init_dcl_list CM init_declarator",
	"xnfdeclarator : nfdeclarator",
	"init_declarator : nfdeclarator",
	"init_declarator : fdeclarator",
	"init_declarator : xnfdeclarator optasgn e",
	"init_declarator : xnfdeclarator optasgn LC init_list optcomma RC",
	"init_declarator : error",
	"init_list : initializer",
	"init_list : init_list CM initializer",
	"initializer : e",
	"initializer : ibrace init_list optcomma RC",
	"optcomma : /* empty */",
	"optcomma : CM",
	"optsemi : /* empty */",
	"optsemi : SM",
	"optasgn : /* empty */",
	"optasgn : ASSIGN",
	"ibrace : LC",
	"compoundstmt : dcmpstmt",
	"compoundstmt : cmpstmt",
	"dcmpstmt : begin r_dcl_stat_list stmt_list RC",
	"cmpstmt : begin stmt_list RC",
	"begin : LC",
	"statement : e SM",
	"statement : ASM SM",
	"statement : ASM CM",
	"statement : compoundstmt",
	"statement : ifprefix statement",
	"statement : ifelprefix statement",
	"statement : whprefix statement",
	"statement : doprefix statement WHILE LP e RP SM",
	"statement : forprefix .e RP statement",
	"statement : switchpart statement",
	"statement : BREAK SM",
	"statement : CONTINUE SM",
	"statement : RETURN SM",
	"statement : RETURN e SM",
	"statement : GOTO NAME SM",
	"statement : SM",
	"statement : error SM",
	"statement : error RC",
	"statement : label statement",
	"label : NAME COLON",
	"label : CASE e COLON",
	"label : DEFAULT COLON",
	"doprefix : DO",
	"ifprefix : IF LP e RP",
	"ifelprefix : ifprefix statement ELSE",
	"whprefix : WHILE LP e RP",
	"forprefix : FOR LP .e SM .e SM",
	"switchpart : SWITCH LP e RP",
	"con_e : /* empty */",
	"con_e : e",
	".e : e",
	".e : /* empty */",
	"elist : e",
	"elist : elist CM e",
	"e : e RELOP e",
	"e : e CM e",
	"e : e DIVOP e",
	"e : e PLUS e",
	"e : e MINUS e",
	"e : e SHIFTOP e",
	"e : e MUL e",
	"e : e EQUOP e",
	"e : e AND e",
	"e : e OR e",
	"e : e ER e",
	"e : e ANDAND e",
	"e : e OROR e",
	"e : e QUEST e COLON e",
	"e : e ASOP e",
	"e : e ASSIGN e",
	"e : term",
	"term : term INCOP",
	"term : MUL term",
	"term : AND term",
	"term : MINUS term",
	"term : UNOP term",
	"term : INCOP term",
	"term : SIZEOF term",
	"term : LP cast_type RP term",
	"term : SIZEOF LP cast_type RP",
	"term : term LB e RB",
	"term : funct_idn RP",
	"term : funct_idn elist RP",
	"term : term STROP NAME",
	"term : NAME",
	"term : ICON",
	"term : FCON",
	"term : STRING",
	"term : LP e RP",
	"cast_type : type null_decl",
	"null_decl : /* empty */",
	"null_decl : LP RP",
	"null_decl : LP null_decl RP LP RP",
	"null_decl : MUL null_decl",
	"null_decl : null_decl LB RB",
	"null_decl : null_decl LB con_e RB",
	"null_decl : LP null_decl RP",
	"funct_idn : NAME LP",
	"funct_idn : term LP",
};
#endif /* YYDEBUG */
/*~!yaccpar*/
/* Name:  yaccpar Part No.: _______-____r
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
 
#ident	"@(#)yacc:yaccpar	1.0"
 
/*
** Skeleton parser driver for yacc output
*/
 
/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab
#define YYACCEPT	return(0)
#define YYABORT		return(1)
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( "syntax error - cannot backup" );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif
 
/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */
 
/*
** driver internal defines
*/
#define YYFLAG		(-1000)
 
/*
** global variables used by the parser
*/
YYSTYPE yyv[ YYMAXDEPTH ];	/* value stack */
int yys[ YYMAXDEPTH ];		/* state stack */
 
YYSTYPE *yypv;			/* top of value stack */
int *yyps;			/* top of state stack */
 
int yystate;			/* current state */
int yytmp;			/* extra var (lasts between blocks) */
 
int yynerrs;			/* number of errors */
int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */
 
 
 
/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
int
yyparse()
{
	register YYSTYPE *yypvt;	/* top of value stack for $vars */
 
	/*
	** Initialize externals - yyparse may be called more than once
	*/
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;
 
	goto yystack;
	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */
 
		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;
 
		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
 
		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;
 
			printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ YYMAXDEPTH ] )	/* room on stack? */
		{
			yyerror( "yacc stack overflow" );
			YYABORT;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;
 
		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;
 
			printf( "Received token " );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}
 
	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;
 
				printf( "Received token " );
				if ( yychar == 0 )
					printf( "end-of-file\n" );
				else if ( yychar < 0 )
					printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register int *yyxi = yyexca;
 
				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}
 
		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( "syntax error" );
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
				yynerrs++;
			skip_init:
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;
 
					printf( "Error recovery discards " );
					if ( yychar == 0 )
						printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];
 
			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 2:
# line 160 "cgram.y"
ftnend(); break;
case 3:
# line 163 "cgram.y"
{ curclass = SNULL;  blevel = 0; } break;
case 4:
# line 166 "cgram.y"
{ asmout(); curclass = SNULL; blevel = 0; } break;
case 5:
# line 168 "cgram.y"
{ curclass = SNULL;  blevel = 0; } break;
case 6:
# line 172 "cgram.y"
{  yypvt[-1].nodep->in.op = FREE; } break;
case 7:
# line 174 "cgram.y"
{  yypvt[-2].nodep->in.op = FREE; } break;
case 8:
# line 175 "cgram.y"
{
			defid( tymerge(yypvt[-1].nodep,yypvt[-0].nodep), curclass==STATIC?STATIC:EXTDEF );
#ifndef LINT
			pfstab(stab[yypvt[-0].nodep->tn.rval].sname);
#endif
			} break;
case 9:
# line 181 "cgram.y"
{  
			    if( blevel ) cerror( "function level error" );
			    if( reached ) retstat |= NRETVAL; 
			    yypvt[-3].nodep->in.op = FREE;
			    ftnend();
			    } break;
case 12:
# line 192 "cgram.y"
{  blevel = 1; } break;
case 14:
# line 197 "cgram.y"
{  locctr(PROG);
			    bccode();
			    } break;
case 15:
# line 203 "cgram.y"
{  yypvt[-1].nodep->in.op = FREE; 
#ifndef LINT
			    plcstab(blevel);
#endif
			    } break;
case 16:
# line 209 "cgram.y"
{  yypvt[-2].nodep->in.op = FREE; 
#ifndef LINT
			    plcstab(blevel);
#endif
			    } break;
case 17:
# line 217 "cgram.y"
{  yypvt[-1].nodep->in.op = FREE; } break;
case 18:
# line 219 "cgram.y"
{  yypvt[-2].nodep->in.op = FREE; } break;
case 20:
# line 223 "cgram.y"
{ curclass = SNULL;  yypvt[-2].nodep->in.op = FREE; } break;
case 21:
# line 225 "cgram.y"
{ curclass = SNULL;  yypvt[-1].nodep->in.op = FREE; } break;
case 22:
# line 227 "cgram.y"
{  curclass = SNULL; } break;
case 24:
# line 231 "cgram.y"
{  yyval.nodep = mkty(INT,0,INT);  curclass = SNULL; } break;
case 25:
# line 234 "cgram.y"
{  yyval.nodep = yypvt[-0].nodep; } break;
case 27:
# line 237 "cgram.y"
{  yyval.nodep = mkty(INT,0,INT); } break;
case 28:
# line 239 "cgram.y"
{ curclass = SNULL ; } break;
case 29:
# line 241 "cgram.y"
{  yypvt[-2].nodep->in.type = types( yypvt[-2].nodep->in.type, yypvt[-0].nodep->in.type, UNDEF );
			    yypvt[-0].nodep->in.op = FREE;
			    } break;
case 30:
# line 248 "cgram.y"
{  curclass = yypvt[-0].intval; } break;
case 32:
# line 253 "cgram.y"
{  yypvt[-1].nodep->in.type = types( yypvt[-1].nodep->in.type, yypvt[-0].nodep->in.type, UNDEF );
			    yypvt[-0].nodep->in.op = FREE;
			    } break;
case 33:
# line 257 "cgram.y"
{  yypvt[-2].nodep->in.type = types( yypvt[-2].nodep->in.type, yypvt[-1].nodep->in.type, yypvt[-0].nodep->in.type );
			    yypvt[-1].nodep->in.op = yypvt[-0].nodep->in.op = FREE;
			    } break;
case 36:
# line 265 "cgram.y"
{ yyval.nodep = dclstruct(yypvt[-4].intval); } break;
case 37:
# line 267 "cgram.y"
{  yyval.nodep = rstruct(yypvt[-0].intval,0);  stwart = instruct; } break;
case 38:
# line 271 "cgram.y"
{  yyval.intval = bstruct(-1,0); stwart = SEENAME; } break;
case 39:
# line 273 "cgram.y"
{  yyval.intval = bstruct(yypvt[-0].intval,0); stwart = SEENAME; } break;
case 42:
# line 281 "cgram.y"
{  moedef( yypvt[-0].intval ); } break;
case 43:
# line 283 "cgram.y"
{  strucoff = yypvt[-0].intval;  moedef( yypvt[-2].intval ); } break;
case 44:
# line 287 "cgram.y"
{ yyval.nodep = dclstruct(yypvt[-4].intval);  } break;
case 45:
# line 289 "cgram.y"
{  yyval.nodep = rstruct(yypvt[-0].intval,yypvt[-1].intval); } break;
case 46:
# line 293 "cgram.y"
{  yyval.intval = bstruct(-1,yypvt[-0].intval);  stwart=0; } break;
case 47:
# line 295 "cgram.y"
{  yyval.intval = bstruct(yypvt[-0].intval,yypvt[-1].intval);  stwart=0;  } break;
case 50:
# line 303 "cgram.y"
{ curclass = SNULL;  stwart=0; yypvt[-1].nodep->in.op = FREE; } break;
case 51:
# line 305 "cgram.y"
{  if( curclass != MOU ){
				curclass = SNULL;
				}
			    else {
				sprintf( fakename, "$%dFAKE", fake++ );
#ifdef FLEXSTRINGS
				/* No need to hash this, we won't look it up */
				defid( tymerge(yypvt[-0].nodep, bdty(NAME,NIL,lookup( savestr(fakename), SMOS ))), curclass );
#else
				defid( tymerge(yypvt[-0].nodep, bdty(NAME,NIL,lookup( fakename, SMOS ))), curclass );
#endif
				werror("structure typed union member must be named");
				}
			    stwart = 0;
			    yypvt[-0].nodep->in.op = FREE;
			    } break;
case 52:
# line 325 "cgram.y"
{ defid( tymerge(yypvt[-1].nodep,yypvt[-0].nodep), curclass);  stwart = instruct; } break;
case 53:
# line 326 "cgram.y"
{yyval.nodep=yypvt[-2].nodep;} break;
case 54:
# line 327 "cgram.y"
{ defid( tymerge(yypvt[-4].nodep,yypvt[-0].nodep), curclass);  stwart = instruct; } break;
case 57:
# line 333 "cgram.y"
{  if( !(instruct&INSTRUCT) ) uerror( "field outside of structure" );
			    if( yypvt[-0].intval<0 || yypvt[-0].intval >= FIELD ){
				uerror( "illegal field size" );
				yypvt[-0].intval = 1;
				}
			    defid( tymerge(yypvt[-3].nodep,yypvt[-2].nodep), FIELD|yypvt[-0].intval );
			    yyval.nodep = NIL;
			    } break;
case 58:
# line 343 "cgram.y"
{  if( !(instruct&INSTRUCT) ) uerror( "field outside of structure" );
			    falloc( stab, yypvt[-0].intval, -1, yypvt[-2].nodep );  /* alignment or hole */
			    yyval.nodep = NIL;
			    } break;
case 59:
# line 348 "cgram.y"
{  yyval.nodep = NIL; } break;
case 60:
# line 353 "cgram.y"
{  umul:
				yyval.nodep = bdty( UNARY MUL, yypvt[-0].nodep, 0 ); } break;
case 61:
# line 356 "cgram.y"
{  uftn:
				yyval.nodep = bdty( UNARY CALL, yypvt[-2].nodep, 0 );  } break;
case 62:
# line 359 "cgram.y"
{  uary:
				yyval.nodep = bdty( LB, yypvt[-2].nodep, 0 );  } break;
case 63:
# line 362 "cgram.y"
{  bary:
				if( (int)yypvt[-1].intval <= 0 ) werror( "zero or negative subscript" );
				yyval.nodep = bdty( LB, yypvt[-3].nodep, yypvt[-1].intval );  } break;
case 64:
# line 366 "cgram.y"
{  yyval.nodep = bdty( NAME, NIL, yypvt[-0].intval );  } break;
case 65:
# line 368 "cgram.y"
{ yyval.nodep=yypvt[-1].nodep; } break;
case 66:
# line 371 "cgram.y"
{  goto umul; } break;
case 67:
# line 373 "cgram.y"
{  goto uftn; } break;
case 68:
# line 375 "cgram.y"
{  goto uary; } break;
case 69:
# line 377 "cgram.y"
{  goto bary; } break;
case 70:
# line 379 "cgram.y"
{ yyval.nodep = yypvt[-1].nodep; } break;
case 71:
# line 381 "cgram.y"
{
				if( blevel!=0 ) uerror("function declaration in bad context");
				yyval.nodep = bdty( UNARY CALL, bdty(NAME,NIL,yypvt[-2].intval), 0 );
				stwart = 0;
				} break;
case 72:
# line 387 "cgram.y"
{
				yyval.nodep = bdty( UNARY CALL, bdty(NAME,NIL,yypvt[-1].intval), 0 );
				stwart = 0;
				} break;
case 73:
# line 394 "cgram.y"
{
				/* turn off typedefs for argument names */
				stwart = SEENAME;
				if( stab[yypvt[-1].intval].sclass == SNULL )
				    stab[yypvt[-1].intval].stype = FTN;
				} break;
case 74:
# line 403 "cgram.y"
{ ftnarg( yypvt[-0].intval );  stwart = SEENAME; } break;
case 75:
# line 405 "cgram.y"
{ ftnarg( yypvt[-0].intval );  stwart = SEENAME; } break;
case 78:
# line 411 "cgram.y"
{yyval.nodep=yypvt[-2].nodep;} break;
case 80:
# line 415 "cgram.y"
{  defid( yypvt[-0].nodep = tymerge(yypvt[-1].nodep,yypvt[-0].nodep), curclass);
			    beginit(yypvt[-0].nodep->tn.rval);
			    } break;
case 81:
# line 422 "cgram.y"
{  NODE *p = yypvt[-0].nodep;
			    nidcl( tymerge(yypvt[-1].nodep,yypvt[-0].nodep) ); 
#ifndef BUG1
			    if(idebug)
#ifdef linux
				lookaround(yyvsp);
#else
				lookaround(yypvt);
#endif
#endif
			    if( ISARY(p->in.type) )
				outstab(&stab[p->tn.rval]);
			} break;
case 82:
# line 436 "cgram.y"
{  defid( tymerge(yypvt[-1].nodep,yypvt[-0].nodep), uclass(curclass) );
			    if(paramno) {
				uerror("can't declare parameters here");
				paramno = 0;
			    }
			} break;
case 83:
# line 444 "cgram.y"
{  NODE *p;
			    p = yypvt[-2].nodep;
			    doinit( yypvt[-0].nodep );
			    endinit(); 
#ifndef BUG1
			    if(idebug)
#ifdef linux
				lookaround(yyvsp);
#else
				lookaround(yypvt);
#endif
#endif
			    if( ISARY(p->in.type) )
				outstab(&stab[p->tn.rval]);
			} break;
case 84:
# line 460 "cgram.y"
{  NODE *p;
			    p = yypvt[-5].nodep;
			    endinit(); 
#ifndef BUG1
			    if(idebug)
#ifdef linux
				lookaround(yyvsp);
#else
				lookaround(yypvt);
#endif
#endif
			    if( ISARY(p->in.type) )
				outstab(&stab[p->tn.rval]);
			} break;
case 88:
# line 483 "cgram.y"
{  doinit( yypvt[-0].nodep ); } break;
case 89:
# line 485 "cgram.y"
{  irbrace(); } break;
case 94:
# line 497 "cgram.y"
{  werror( "old-fashioned initialization: use =" ); } break;
case 96:
# line 502 "cgram.y"
{  ilbrace(); } break;
case 99:
# line 512 "cgram.y"
{  
#ifndef LINT
			    prcstab(blevel);
#endif
			    --blevel;
			    if( blevel == 1 ) blevel = 0;
			    clearst( blevel );
			    checkst( blevel );
			    autooff = *--psavbc;
			    regvar = *--psavbc;
			    } break;
case 100:
# line 526 "cgram.y"
{  --blevel;
			    if( blevel == 1 ) blevel = 0;
			    clearst( blevel );
			    checkst( blevel );
			    autooff = *--psavbc;
			    regvar = *--psavbc;
			    } break;
case 101:
# line 536 "cgram.y"
{  if( blevel == 1 ) dclargs();
			    ++blevel;
			    if( psavbc > &asavbc[BCSZ-2] ) cerror( "nesting too deep" );
			    *psavbc++ = regvar;
			    *psavbc++ = autooff;
			    } break;
case 102:
# line 545 "cgram.y"
{ ecomp( yypvt[-1].nodep ); } break;
case 103:
# line 548 "cgram.y"
{ asmout(); } break;
case 104:
# line 551 "cgram.y"
{ asmout(); } break;
case 106:
# line 554 "cgram.y"
{ deflab(yypvt[-1].intval);
			   reached = 1;
			   } break;
case 107:
# line 558 "cgram.y"
{  if( yypvt[-1].intval != NOLAB ){
				deflab( yypvt[-1].intval );
				reached = 1;
				}
			    } break;
case 108:
# line 564 "cgram.y"
{  branch(  contlab );
			    deflab( brklab );
			    if( (flostat&FBRK) || !(flostat&FLOOP)) reached = 1;
			    else reached = 0;
			    resetbc(0);
			    } break;
case 109:
# line 571 "cgram.y"
{  deflab( contlab );
			    if( flostat & FCONT ) reached = 1;
			    ecomp( buildtree( CBRANCH, buildtree( NOT, yypvt[-2].nodep, NIL ), bcon( yypvt[-6].intval ) ) );
			    deflab( brklab );
			    reached = 1;
			    resetbc(0);
			    } break;
case 110:
# line 579 "cgram.y"
{  deflab( contlab );
			    if( flostat&FCONT ) reached = 1;
			    if( yypvt[-2].nodep ) ecomp( yypvt[-2].nodep );
			    branch( yypvt[-3].intval );
			    deflab( brklab );
			    if( (flostat&FBRK) || !(flostat&FLOOP) ) reached = 1;
			    else reached = 0;
			    resetbc(0);
			    } break;
case 111:
# line 589 "cgram.y"
{  if( reached ) branch( brklab );
			    deflab( yypvt[-1].intval );
			   swend();
			    deflab(brklab);
			    if( (flostat&FBRK) || !(flostat&FDEF) ) reached = 1;
			    resetbc(FCONT);
			    } break;
case 112:
# line 597 "cgram.y"
{  if( brklab == NOLAB ) uerror( "illegal break");
			    else if(reached) branch( brklab );
			    flostat |= FBRK;
			    if( brkflag ) goto rch;
			    reached = 0;
			    } break;
case 113:
# line 604 "cgram.y"
{  if( contlab == NOLAB ) uerror( "illegal continue");
			    else branch( contlab );
			    flostat |= FCONT;
			    goto rch;
			    } break;
case 114:
# line 610 "cgram.y"
{  retstat |= NRETVAL;
			    branch( retlab );
			rch:
			    if( !reached ) werror( "statement not reached");
			    reached = 0;
			    } break;
case 115:
# line 617 "cgram.y"
{  register NODE *temp;
			    idname = curftn;
			    temp = buildtree( NAME, NIL, NIL );
			    if(temp->in.type == TVOID)
				uerror("void function %s cannot return value",
					stab[idname].sname);
			    temp->in.type = DECREF( temp->in.type );
			    temp = buildtree( RETURN, temp, yypvt[-1].nodep );
			    /* now, we have the type of the RHS correct */
			    tfree(temp->in.left);
			    temp->in.op = FREE;
			    ecomp( buildtree( FORCE, temp->in.right, NIL ) );
			    retstat |= RETVAL;
			    branch( retlab );
			    reached = 0;
			    } break;
case 116:
# line 634 "cgram.y"
{  register NODE *q;
			    q = block( FREE, NIL, NIL, INT|ARY, 0, INT );
			    q->tn.rval = idname = yypvt[-1].intval;
			    defid( q, ULABEL );
			    stab[idname].suse = -lineno;
			    branch( stab[idname].offset );
			    goto rch;
			    } break;
case 121:
# line 648 "cgram.y"
{  register NODE *q;
			    q = block( FREE, NIL, NIL, INT|ARY, 0, LABEL );
			    q->tn.rval = yypvt[-1].intval;
			    defid( q, LABEL );
			    reached = 1;
			    } break;
case 122:
# line 655 "cgram.y"
{  addcase(yypvt[-1].nodep);
			    reached = 1;
			    } break;
case 123:
# line 659 "cgram.y"
{  reached = 1;
			    adddef();
			    flostat |= FDEF;
			    } break;
case 124:
# line 665 "cgram.y"
{  savebc();
			    if( !reached ) werror( "loop not entered at top");
			    brklab = getlab();
			    contlab = getlab();
			    deflab( yyval.intval = getlab() );
			    reached = 1;
			    } break;
case 125:
# line 674 "cgram.y"
{  ecomp( buildtree( CBRANCH, yypvt[-1].nodep, bcon( yyval.intval=getlab()) ) ) ;
			    reached = 1;
			    } break;
case 126:
# line 679 "cgram.y"
{  if( reached ) branch( yyval.intval = getlab() );
			    else yyval.intval = NOLAB;
			    deflab( yypvt[-2].intval );
			    reached = 1;
			    } break;
case 127:
# line 687 "cgram.y"
{  savebc();
			    if( !reached ) werror( "loop not entered at top");
			    if( yypvt[-1].nodep->in.op == ICON && yypvt[-1].nodep->tn.lval != 0 ) flostat = FLOOP;
			    deflab( contlab = getlab() );
			    reached = 1;
			    brklab = getlab();
			    if( flostat == FLOOP ) tfree( yypvt[-1].nodep );
			    else ecomp( buildtree( CBRANCH, yypvt[-1].nodep, bcon( brklab) ) );
			    } break;
case 128:
# line 698 "cgram.y"
{  if( yypvt[-3].nodep ) ecomp( yypvt[-3].nodep );
			    else if( !reached ) werror( "loop not entered at top");
			    savebc();
			    contlab = getlab();
			    brklab = getlab();
			    deflab( yyval.intval = getlab() );
			    reached = 1;
			    if( yypvt[-1].nodep ) ecomp( buildtree( CBRANCH, yypvt[-1].nodep, bcon( brklab) ) );
			    else flostat |= FLOOP;
			    } break;
case 129:
# line 710 "cgram.y"
{  savebc();
			    brklab = getlab();
			    ecomp( buildtree( FORCE, yypvt[-1].nodep, NIL ) );
			    branch( yyval.intval = getlab() );
			    swstart();
			    reached = 0;
			    } break;
case 130:
# line 719 "cgram.y"
{ yyval.intval=instruct; stwart=instruct=0; } break;
case 131:
# line 721 "cgram.y"
{  yyval.intval = icons( yypvt[-0].nodep );  instruct=yypvt[-1].intval; } break;
case 133:
# line 725 "cgram.y"
{ yyval.nodep=0; } break;
case 135:
# line 730 "cgram.y"
{  goto bop; } break;
case 136:
# line 734 "cgram.y"
{
			preconf:
			    if( yychar==RELOP||yychar==EQUOP||yychar==AND||yychar==OR||yychar==ER ){
			    precplaint:
				if( hflag ) werror( "precedence confusion possible: parenthesize!" );
				}
			bop:
			    yyval.nodep = buildtree( yypvt[-1].intval, yypvt[-2].nodep, yypvt[-0].nodep );
			    } break;
case 137:
# line 744 "cgram.y"
{  yypvt[-1].intval = COMOP;
			    goto bop;
			    } break;
case 138:
# line 748 "cgram.y"
{  goto bop; } break;
case 139:
# line 750 "cgram.y"
{  if(yychar==SHIFTOP) goto precplaint; else goto bop; } break;
case 140:
# line 752 "cgram.y"
{  if(yychar==SHIFTOP ) goto precplaint; else goto bop; } break;
case 141:
# line 754 "cgram.y"
{  if(yychar==PLUS||yychar==MINUS) goto precplaint; else goto bop; } break;
case 142:
# line 756 "cgram.y"
{  goto bop; } break;
case 143:
# line 758 "cgram.y"
{  goto preconf; } break;
case 144:
# line 760 "cgram.y"
{  if( yychar==RELOP||yychar==EQUOP ) goto preconf;  else goto bop; } break;
case 145:
# line 762 "cgram.y"
{  if(yychar==RELOP||yychar==EQUOP) goto preconf; else goto bop; } break;
case 146:
# line 764 "cgram.y"
{  if(yychar==RELOP||yychar==EQUOP) goto preconf; else goto bop; } break;
case 147:
# line 766 "cgram.y"
{  goto bop; } break;
case 148:
# line 768 "cgram.y"
{  goto bop; } break;
case 149:
# line 770 "cgram.y"
{  yyval.nodep=buildtree(QUEST, yypvt[-4].nodep, buildtree( COLON, yypvt[-2].nodep, yypvt[-0].nodep ) );
			    } break;
case 150:
# line 773 "cgram.y"
{  goto bop; } break;
case 151:
# line 775 "cgram.y"
{  goto bop; } break;
case 153:
# line 779 "cgram.y"
{  yyval.nodep = buildtree( yypvt[-0].intval, yypvt[-1].nodep, bcon(1) ); } break;
case 154:
# line 781 "cgram.y"
{ ubop:
			    yyval.nodep = buildtree( UNARY yypvt[-1].intval, yypvt[-0].nodep, NIL );
			    } break;
case 155:
# line 785 "cgram.y"
{  if( ISFTN(yypvt[-0].nodep->in.type) || ISARY(yypvt[-0].nodep->in.type) ){
				werror( "& before array or function: ignored" );
				yyval.nodep = yypvt[-0].nodep;
				}
			    else goto ubop;
			    } break;
case 156:
# line 792 "cgram.y"
{  goto ubop; } break;
case 157:
# line 794 "cgram.y"
{
			    yyval.nodep = buildtree( yypvt[-1].intval, yypvt[-0].nodep, NIL );
			    } break;
case 158:
# line 798 "cgram.y"
{  yyval.nodep = buildtree( yypvt[-1].intval==INCR ? ASG PLUS : ASG MINUS,
						yypvt[-0].nodep,
						bcon(1)  );
			    } break;
case 159:
# line 803 "cgram.y"
{  yyval.nodep = doszof( yypvt[-0].nodep ); } break;
case 160:
# line 805 "cgram.y"
{  yyval.nodep = buildtree( CAST, yypvt[-2].nodep, yypvt[-0].nodep );
			    yyval.nodep->in.left->in.op = FREE;
			    yyval.nodep->in.op = FREE;
			    yyval.nodep = yyval.nodep->in.right;
			    } break;
case 161:
# line 811 "cgram.y"
{  yyval.nodep = doszof( yypvt[-1].nodep ); } break;
case 162:
# line 813 "cgram.y"
{  yyval.nodep = buildtree( UNARY MUL, buildtree( PLUS, yypvt[-3].nodep, yypvt[-1].nodep ), NIL ); } break;
case 163:
# line 815 "cgram.y"
{  yyval.nodep=buildtree(UNARY CALL,yypvt[-1].nodep,NIL); } break;
case 164:
# line 817 "cgram.y"
{  yyval.nodep=buildtree(CALL,yypvt[-2].nodep,yypvt[-1].nodep); } break;
case 165:
# line 819 "cgram.y"
{  if( yypvt[-1].intval == DOT ){
				if( notlval( yypvt[-2].nodep ) )uerror("structure reference must be addressable");
				yypvt[-2].nodep = buildtree( UNARY AND, yypvt[-2].nodep, NIL );
				}
			    idname = yypvt[-0].intval;
			    yyval.nodep = buildtree( STREF, yypvt[-2].nodep, buildtree( NAME, NIL, NIL ) );
			    } break;
case 166:
# line 827 "cgram.y"
{  idname = yypvt[-0].intval;
			    /* recognize identifiers in initializations */
			    if( blevel==0 && stab[idname].stype == UNDEF ) {
				register NODE *q;
#ifndef FLEXNAMES
				werror( "undeclared initializer name %.8s", stab[idname].sname );
#else
				werror( "undeclared initializer name %s", stab[idname].sname );
#endif
				q = block( FREE, NIL, NIL, INT, 0, INT );
				q->tn.rval = idname;
				defid( q, EXTERN );
				}
			    yyval.nodep=buildtree(NAME,NIL,NIL);
			    stab[yypvt[-0].intval].suse = -lineno;
			} break;
case 167:
# line 844 "cgram.y"
{  yyval.nodep=bcon(0);
			    yyval.nodep->tn.lval = lastcon;
			    yyval.nodep->tn.rval = NONAME;
			    if( yypvt[-0].intval ) yyval.nodep->fn.csiz = yyval.nodep->in.type = ctype(LONG);
			    /* DJK put this in. DW took it out.
			    * if( <0 ){
			    *	$$->in.type = UNSIGNED;
			    * }
			    */
			    } break;
case 168:
# line 855 "cgram.y"
{  yyval.nodep=buildtree(FCON,NIL,NIL);
#ifdef MYATOF
			    yyval.nodep->fpn.fpnum = ifpn;
#else
			    yyval.nodep->fpn.dval = dcon;
#endif /* MYATOF */
			    } break;
case 169:
# line 863 "cgram.y"
{  yyval.nodep = getstr(); /* get string contents */ } break;
case 170:
# line 865 "cgram.y"
{ yyval.nodep=yypvt[-1].nodep; } break;
case 171:
# line 869 "cgram.y"
{
			yyval.nodep = tymerge( yypvt[-1].nodep, yypvt[-0].nodep );
			yyval.nodep->in.op = NAME;
			yypvt[-1].nodep->in.op = FREE;
			} break;
case 172:
# line 877 "cgram.y"
{ yyval.nodep = bdty( NAME, NIL, -1 ); } break;
case 173:
# line 879 "cgram.y"
{ yyval.nodep = bdty( UNARY CALL, bdty(NAME,NIL,-1),0); } break;
case 174:
# line 881 "cgram.y"
{  yyval.nodep = bdty( UNARY CALL, yypvt[-3].nodep, 0 ); } break;
case 175:
# line 883 "cgram.y"
{  goto umul; } break;
case 176:
# line 885 "cgram.y"
{  goto uary; } break;
case 177:
# line 887 "cgram.y"
{  goto bary;  } break;
case 178:
# line 889 "cgram.y"
{ yyval.nodep = yypvt[-1].nodep; } break;
case 179:
# line 893 "cgram.y"
{  if( stab[yypvt[-1].intval].stype == UNDEF ){
				register NODE *q;
				q = block( FREE, NIL, NIL, FTN|INT, 0, INT );
				q->tn.rval = yypvt[-1].intval;
				defid( q, EXTERN );
				}
			    idname = yypvt[-1].intval;
			    yyval.nodep=buildtree(NAME,NIL,NIL);
			    stab[idname].suse = -lineno;
			} break;
 
	}
	goto yystack;		/* reset registers in driver code */
}
