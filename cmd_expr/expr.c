/*~!expr.c*/
/* Name:  expr.c Part No.: _______-____r
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

#ident	"Make4MPX $Id: expr.c,v 1.2 2021/07/04 16:21:15 jbev Exp $"

/*
 * $Log: expr.c,v $
 * Revision 1.2  2021/07/04 16:21:15  jbev
 * Fix warning errors.
 *
 * Revision 1.1  1995/03/14 01:55:15  jbev
 * Initial revision
 *
 */

# define A_STRING 258
# define NOARG 259
# define OR 260
# define AND 261
# define EQ 262
# define LT 263
# define GT 264
# define GEQ 265
# define LEQ 266
# define NEQ 267
# define ADD 268
# define SUBT 269
# define MULT 270
# define DIV 271
# define REM 272
# define MCH 273
# define MATCH 274

#include <string.h>
#include <stdio.h>

void errxx();
void yyerror();
int ematch();
char *conjn();

#define ESIZE	256
#define error(c)	errxx()
#define EQL(x,y) !strcmp(x,y)

#define INIT	register char *sp = instring;
#define GETC()		(*sp++)
#define PEEKC()		(*sp)
#define UNGETC(c)	(--sp)
#ifdef gould
#define RETURN(c)	return 0
#else
#define RETURN(c)	return c
#endif
#define ERROR(c)	errxx()
#include "regexp.h"

#ifndef mpx
#include <stdlib.h>
#include <unistd.h>
#else
char *malloc();
#endif

long atol();
char *ltoa(), *strcpy(), *strncpy();
void exit();
char **Av;
char *buf;
int Ac;
int Argi;
int noarg;
int paren;

char Mstring[1][128];


char *operator[] = {
    "|", "&", "+", "-", "*", "/", "%", ":",
    "=", "==", "<", "<=", ">", ">=", "!=",
    "match", "\0" };


int op[] = {
    OR, AND, ADD,  SUBT, MULT, DIV, REM, MCH,
    EQ, EQ, LT, LEQ, GT, GEQ, NEQ,
    MATCH };


int pri[] = {
    1, 2, 3, 3, 3, 3, 3, 3, 4, 4, 5, 5, 5, 6, 7};


int yylex() 
{
    register char *p;
    register int i;

    if (Argi >= Ac) 
    	return NOARG;

    p = Av[Argi];

    if ((*p == '(' || *p == ')') && p[1] == '\0' )
    	return (int)*p;
    for (i = 0; *operator[i]; ++i)
    	if (EQL(operator[i], p))
    	    return op[i];


    return A_STRING;
}


char *rel(oper, r1, r2) 
int oper;
register char *r1, *r2;
{
    long i;

    if (ematch(r1, "-\\{0,1\\}[0-9]*$") && ematch(r2, "-\\{0,1\\}[0-9]*$"))
    	i = atol(r1) - atol(r2);
    else
    	i = strcmp(r1, r2);
    switch (oper) {
    case EQ:
    	i = i == 0;
    	break;
    case GT:
    	i = i > 0;
    	break;
    case GEQ:
    	i = i >= 0;
    	break;
    case LT:
    	i = i < 0;
    	break;
    case LEQ:
    	i = i <= 0;
    	break;
    case NEQ:
    	i = i != 0;
    	break;
    }
    return i ? "1" : "0";
}


char *arith(oper, r1, r2) 
int oper;
char *r1, *r2;
{
    long i1, i2;
    register char *rv;

    if (!(ematch(r1, "-\\{0,1\\}[0-9]*$") && ematch(r2, "-\\{0,1\\}[0-9]*$")))
    	yyerror("non-numeric argument");
    i1 = atol(r1);
    i2 = atol(r2);

    switch (oper) {
    case ADD:
    	i1 = i1 + i2;
    	break;
    case SUBT:
    	i1 = i1 - i2;
    	break;
    case MULT:
    	i1 = i1 * i2;
    	break;
    case DIV:
    	if (i2 == 0)
    	    yyerror("division by zero");
    	i1 = i1 / i2;
    	break;
    case REM:
    	if (i2 == 0)
    	    yyerror("division by zero");
    	i1 = i1 % i2;
    	break;
    }
    rv = malloc(16);
    (void) strcpy(rv, ltoa(i1));
    return rv;
}


char *conjn(oper, r1, r2) 
int oper;
char *r1, *r2;
{
    register char *rv = "0";

    switch (oper) {

    case OR:
    	if (EQL(r1, "0")
    	   || EQL(r1, ""))
    	    if (EQL(r2, "0")
    	       || EQL(r2, ""))
    	    	rv = "0";
    	    else
    	    	rv = r2;
    	else
    	    rv = r1;
    	break;
    case AND:
    	if (EQL(r1, "0")
    	   || EQL(r1, ""))
    	    rv = "0";
    	else if (EQL(r2, "0")
    	   || EQL(r2, ""))
    	    rv = "0";
    	else
    	    rv = r1;
    	break;
    }
    return rv;
}


char *match(s, p)
char *s, *p;
{
    register char *rv;

    (void) strcpy(rv = malloc(8), ltoa((long)ematch(s, p)));
    if (nbra) {
    	rv = malloc((unsigned) strlen(Mstring[0]) + 1);
    	(void) strcpy(rv, Mstring[0]);
    }
    return rv;
}


int ematch(s, p)
char *s;
register char *p;
{
    static char expbuf[ESIZE];
    char *compile();
    register int num;
    extern char *braslist[], *braelist[], *loc2;

    compile(p, expbuf, &expbuf[512], 0);
    if (nbra > 1)
    	yyerror("Too many '\\('s");
    if (advance(s, expbuf)) {
    	if (nbra == 1) {
    	    p = braslist[0];
    	    num = braelist[0] - p;
    	    if ((num > 127) || (num < 0)) 
    	    	yyerror("Paren problem");
    	    (void) strncpy(Mstring[0], p, num);
    	    Mstring[0][num] = '\0';
    	}
    	return(loc2 - s);
    }
    return(0);
}


void errxx()
{
    yyerror("RE error");
}


void yyerror(s)
char *s;
{
    (void) write(2, "expr: ", 6);
    (void) write(2, s, (unsigned) strlen(s));
    (void) write(2, "\n", 1);
    exit(2);
}


char *ltoa(l)
long l;
{
    static char str[20];
    register char *sp = (char *) &str[18];
    register int i;
    register int neg = 0;

    if (l == 0x80000000L)
    	return "-2147483648";
    if (l < 0)
    	++neg, l = -l;
    str[19] = '\0';
    do {
    	i = l % 10;
    	*sp-- = '0' + i;
    	l /= 10;
    } while (l);
    if (neg)
    	*sp-- = '-';
    return ++sp;
}


char *expres(prior, par)  
int prior, par;
{
    int ylex, temp = 0, op1;
    char *r1 = (char *)0, *ra, *rb;
    ylex = yylex();
    if (ylex >= NOARG && ylex < MATCH) {
    	yyerror("syntax error");
    }
    if (ylex == A_STRING) {
    	r1 = Av[Argi++];
    	temp = Argi;
    } else {
    	if (ylex == '(') {
    	    paren++;
    	    Argi++;
    	    r1 = expres(0, Argi);
    	    Argi--;
    	}
    }
lop:
    ylex = yylex();
    if (ylex > NOARG && ylex < MATCH) {
    	op1 = ylex;
    	Argi++;
    	if (pri[op1-OR] <= prior )
    	    return r1;
    	else {
    	    switch (op1) {
    	    case OR:
    	    case AND:
    	    	r1 = conjn(op1, r1, expres(pri[op1-OR], 0));
    	    	break;
    	    case EQ:
    	    case LT:
    	    case GT:
    	    case LEQ:
    	    case GEQ:
    	    case NEQ:
    	    	r1 = rel(op1, r1, expres(pri[op1-OR], 0));
    	    	break;
    	    case ADD:
    	    case SUBT:
    	    case MULT:
    	    case DIV:
    	    case REM:
    	    	r1 = arith(op1, r1, expres(pri[op1-OR], 0));
    	    	break;
    	    case MCH:
    	    	r1 = match(r1, expres(pri[op1-OR], 0));
    	    	break;
    	    }
    	    if (noarg == 1) {
    	    	return r1;
    	    }
    	    Argi--;
    	    goto lop;
    	}
    }
    ylex = yylex();
    if (ylex == ')') {
    	if (par == Argi) {
    	    yyerror("syntax error");
    	}
    	if (par != 0) {
    	    paren--;
    	    Argi++;
    	}
    	Argi++;
    	return r1;
    }
    ylex = yylex();
    if (ylex > MCH && ylex <= MATCH) {
    	if (Argi == temp) {
    	    return r1;
    	}
    	op1 = ylex;
    	Argi++;
    	switch (op1) {
    	case MATCH:
    	    rb = expres(pri[op1-OR], 0);
    	    ra = expres(pri[op1-OR], 0);
    	}
    	switch (op1) {
    	case MATCH:
    	    r1 = match(rb, ra);
    	    break;
    	}
    	if (noarg == 1) {
    	    return r1;
    	}
    	Argi--;
    	goto lop;
    }
    ylex = yylex();
    if (ylex == NOARG) {
    	noarg = 1;
    }
    return r1;
}


int main(argc, argv) 
int argc;
char **argv;
{
    Ac = argc;
    Argi = 1;
    noarg = 0;
    paren = 0;
    Av = argv;
    buf = expres(0, 1);
    if (Ac != Argi || paren != 0) {
    	yyerror("syntax error");
    }
    (void) write(1, buf, (unsigned) strlen(buf));
    (void) write(1, "\n", 1);
    exit ((!strcmp(buf, "0") || !buf[0]) ? 1 : 0);
    /* NOTREACHED */
}


