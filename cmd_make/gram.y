/*~!gram.y*/
/* Name:  gram.y Part No.: _______-____r
 *
 * Copyright 1994 - J B Systems, Morrison, CO
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

%{
#ident	"@(#)make:gram.y	1.0"
  %}

%{
#include "defs.h"
  %}

%term NAME SHELLINE START COLON DOUBLECOLON EQUAL A_STRING VERSION

%union
  {
  SHBLOCK yshblock;
  DEPBLOCK ydepblock;
  NAMEBLOCK ynameblock;
  CHARSTAR ycharstring;
}

%type <yshblock> SHELLINE, shlist, shellist
  %type <ynameblock> NAME, namelist, name
  %type <ydepblock> deplist, dlist
  %type <ycharstring> A_STRING


%%

%{
  DEPBLOCK pp;
  FSTATIC SHBLOCK prevshp;

  FSTATIC NAMEBLOCK lefts [NLEFTS];
  NAMEBLOCK leftp;
  FSTATIC int nlefts;

  LINEBLOCK lp, lpp;
  FSTATIC DEPBLOCK prevdep;
  FSTATIC int sepc;
int nextlin();
extern int yylex();
extern int yyparse();
extern void fatal();
extern void fatal1();
extern void yyerror();
extern void setvar();
extern int sindex();
%}


file:
| file comline
  ;

comline:
START
  | START macrodef
  | START namelist deplist shellist = {
  if (mainname == NULL && IS_OFF (INTRULE))
    if (lefts [0]->namep [0] != DOT || any (lefts [0]->namep, SLASH))
      mainname = lefts [0];
  while (--nlefts >= 0)
  {
    leftp = lefts [nlefts];
    if (leftp->septype == 0)
      leftp->septype = sepc;
    else if (leftp->septype != sepc)
      fprintf (stderr, "Inconsistent rules lines for `%s'\n",
        leftp->namep);
    else if (sepc==ALLDEPS && * (leftp->namep) !=DOT && $4!=0)
    {
      for (lp=leftp->linep; lp->nextline!=0; lp=lp->nextline)
        if (lp->shp)
          fprintf (stderr, "Multiple rules lines for `%s'\n",
            leftp->namep);
    }

    lp = ALLOC (lineblock);
    lp->nextline = 0;
    lp->depp = $3;
    lp->shp = $4;

    if (equal (leftp->namep, ".SUFFIXES") && $3==0)
      leftp->linep = 0;
    else if (leftp->linep == 0)
      leftp->linep = lp;
    else
    {
      for (lpp = leftp->linep; lpp->nextline!=0; lpp = lpp->nextline)
        ;
      if (sepc==ALLDEPS && leftp->namep [0]==DOT)
        lpp->shp = 0;
      lpp->nextline = lp;
    }
  }
}
| error
  ;

macrodef:
NAME EQUAL A_STRING =
  {
  setvar ($1, $3);
}
;

namelist:
name = {
  lefts [0] = $1;
  nlefts = 1;
}
| namelist name = {
  lefts [nlefts++] = $2;
  if (nlefts>NLEFTS) fatal ("Too many lefts");
}
;

name:
NAME =
  {
  if (($$ = srchname ($1)) == 0)
    $$ = makename ($1);
}
| NAME VERSION =
  {
  if (($$ = srchname ($1)) == 0)
    $$ = makename ($1);
}
;

deplist:
= {
  fatal1 ("Must be a separator on rules line %d", yylineno);
}
| dlist
  ;

dlist:
sepchar = {
  prevdep = 0;
  $$ = 0;
}
| dlist name = {
  pp = ALLOC (depblock);
  pp->nextdep = 0;
  pp->depname = $2;
  if (prevdep == 0) $$ = pp;
  else  prevdep->nextdep = pp;
  prevdep = pp;
}
;

sepchar:
COLON = {
  sepc = ALLDEPS;
}
| DOUBLECOLON = {
  sepc = SOMEDEPS;
}
;

shellist:
= {
  $$ = 0;
}
| shlist = {
  $$ = $1;
}
;

shlist:
SHELLINE = {
  $$ = $1;
  prevshp = $1;
}
| shlist SHELLINE = {
  $$ = $1;
  prevshp->nextsh = $2;
  prevshp = $2;
}
;


%%

/*  @(#)lex.c 3.1 */

#include <ctype.h>
int retsh();
void fstack();
int GETC();
extern CHARSTAR subst();
extern int get();
extern int any();

CHARSTAR zznextc; /* zero if need another line; otherwise points to next char */
int yylineno;
static char inmacro = NO;

int yylex ()
{
  register CHARSTAR p;
  register CHARSTAR q;
  static char word [128];
  CHARSTAR pword;

  pword = word;
  if (zznextc == 0)
    return (nextlin ());

  while (isspace (*zznextc))
    ++zznextc;

  if (inmacro == YES)
  {
    inmacro = NO;
    yylval.ycharstring = copys (zznextc);
    zznextc = 0;
    return (A_STRING);
  }

  if (*zznextc == CNULL)
    return (nextlin ());

  if (*zznextc == KOLON)
  {
    if (*++zznextc == KOLON)
    {
      ++zznextc;
      return (DOUBLECOLON);
    }
    else
      return (COLON);
  }

  if (*zznextc == EQUALS)
  {
    inmacro = YES;
    ++zznextc;
    return (EQUAL);
  }

  if (*zznextc == SKOLON)
    return (retsh (zznextc));

  p = zznextc;
  q = word;

  while (! (funny [(int)*p] & TERMINAL))
    *q++ = *p++;

  if (p != zznextc)
  {
    *q = CNULL;
    yylval.ycharstring = copys (pword);
    if (*p == RCURLY)
    {
      zznextc = p+1;
      return (VERSION);
    }
    if (*p == LCURLY)
      p++;
    zznextc = p;
    return (NAME);
  }

  else
  {
    fprintf (stderr, "Bad character %c (octal %o), line %d",
      *zznextc, *zznextc, yylineno);
    fatal (Nullstr);
  }
  return (0); /* never executed */
}


int retsh (q)
register CHARSTAR q;
{
  register CHARSTAR p;
  register int c;
  extern CHARSTAR *linesptr;
  SHBLOCK sp;

  for (p=q+1 ; *p==BLANK||*p==TAB ; ++p)
    ;

  sp = ALLOC (shblock);
  sp->nextsh = 0;
  sp->shbp = (fin == NULL ? p : copys (p));
  yylval.yshblock = sp;
  zznextc = 0;
  /*
  * The following if-else "thing" eats up newlines within
  * shell blocks.
  */
  if (fin == NULL)
  {
    if (linesptr [0])
      while (linesptr [1] && equal (linesptr [1], "\n"))
      {
        yylineno++;
        linesptr++;
      }
  }
  else
  {
    while ((c = GETC ()) == NEWLINE)
      yylineno++;
    if (c != EOF)
      ungetc (c, fin);
  }
  return (SHELLINE);
}

int nextlin ()
{
  register char c;
  register CHARSTAR p = (char *)0, t;
  static char yytext [INMAX];
  static CHARSTAR yytextl = yytext+INMAX;
  CHARSTAR text;
  char templin [INMAX];
  CHARSTAR templinl = templin + INMAX;
  char lastch;
  CHARSTAR lastchp;
  extern CHARSTAR *linesptr;
  int incom;
  int kc;
  int nflg;
  int poundflg;

again:
  incom = 0;
  zznextc = 0;
  poundflg = 0;

  if (fin == NULL)
  {
    if ((text = *linesptr++) == 0)
      return (0);
    ++yylineno;
    copstr (yytext, text);
  }

  else
  {
    yytext [0] = CNULL;
    for (p=yytext ; ; ++p)
    {
      if (p > yytextl)
        fatal ("line too long");
      kc = GETC ();
      if (kc == EOF)
      {
        *p = CNULL;
        return (0);
      }
      else if (kc == SKOLON)
        ++incom;
      else if (kc == TAB && p == yytext)
        ++incom;
      else if (kc==POUND && !incom && yytext [0] != TAB)
      {
        poundflg++;
        kc = CNULL;
      }
      else if (kc == NEWLINE)
      {
        ++yylineno;
        if (p==yytext || p [-1]!=BACKSLASH)
          break;
        if (incom || yytext [0] == TAB)
          *p++ = NEWLINE;
        else
          p [-1] = BLANK;
        nflg = YES;
        while ((kc = GETC ()))
        {
          if (kc != TAB && kc != BLANK && kc != NEWLINE)
            break;
          if (incom || yytext [0] == TAB)
          {
            if (nflg == YES && kc == TAB)
            {
              nflg = NO;
              continue;
            }
            if (kc == NEWLINE)
            {
              nflg = YES;
            }

            *p++ = kc;
          }
          if (kc == NEWLINE)
            ++yylineno;
        }

        if (kc == EOF)
        {
          *p = CNULL;
          return (0);
        }
      }
      *p = kc;
    }
    *p = CNULL;
    text = yytext;
  }

  c = text [0];

  if (c == TAB)
    return (retsh (text));

  /*
  * DO include FILES HERE.
  */
  if (sindex (text, "include") == 0 && (text [7] == BLANK || text [7] == TAB))
  {
    CHARSTAR pfile;

    for (p = &text[8]; *p != CNULL; p++)
      if (*p != TAB || *p != BLANK)
        break;
    pfile = p;
    for (;  *p != CNULL && *p != NEWLINE && *p != TAB && *p != BLANK; p++)
      ;
    if (*p != CNULL)
      *p = CNULL;

    /*
    * Start using new file.
    */
    fstack (pfile, &fin, &yylineno);
    goto again;
  }
  if (isalpha (c) || isdigit (c) || c==BLANK || c==DOT)
    for (p=text+1; *p!=CNULL; p++)
      if (*p == KOLON || *p == EQUALS)
        break;

  /* substtitute for macros on dependency line up to the semicolon if any */
  if (*p != EQUALS)
  {
    for (t = yytext ; *t!=CNULL && *t!=SKOLON ; ++t)
      ;

    lastchp = t;
    lastch = *t;
    *t = CNULL;

    subst (yytext, templin, templinl); /* Substitute for macros on dep lines */

    if (lastch)
    {
      for (t = templin ; *t ; ++t)
        ;
      *t = lastch;
      while ((*++t = *++lastchp))
        if (t >= templinl)
          fatal ("Macro substitution produced line too long");
    }

    p = templin;
    t = yytext;
    while ((*t++ = *p++));
  }

  if (poundflg == 0 || yytext [0] != CNULL)
  {
    zznextc = text;
    return (START);
  }
  else
    goto again;
}

/* #include "stdio.h" */ /* deleted 11/17/83 JCB */

/*
* GETC automatically unravels stacked include files. That is,
* during include file processing, when a new file is encountered
* fstack will stack the FILE pointer argument. Subsequent
* calls to GETC with the new FILE pointer will get characters
* from the new file. When an EOF is encountered, GETC will
* check to see if the file pointer has been stacked. If so,
* a character from the previous file will be returned.
* The external references are "GETC()" and "fstack(fname,stream,lno)".
* "Fstack(stfname,ream,lno)" is used to stack an old file pointer before
* the new file is assigned to the same variable. Also stacked are the
* file name and the old current lineno, generally, yylineno.
*/


static int morefiles;
static struct sfiles
  {
  char sfname [64];
  FILE *sfilep;
  int syylno;
}
sfiles [20];

int GETC ()
{
  register int c;

  c = getc (fin);
  while (c == EOF && morefiles)
  {
    fclose (fin);
    yylineno = sfiles [--morefiles].syylno;
    fin = sfiles [morefiles].sfilep;
    c = getc (fin);
  }
  return (c);
}

void fstack (newname, oldfp, oldlno)
register char *newname;
register FILE **oldfp;
register int *oldlno;
{
  if (access (newname, 4) != 0)
    /*
    * This get line can be removed if used elsewhere than make.
    */
#ifdef noinclude
    if (get (newname, CD, Nullstr) == NO)
      fatal1 ("Cannot read or get %s", newname);
#else
    if (get (newname, CD, Nullstr) == NO) {
      printf ("Cannot read or get %s\n", newname);
      return;
    }
#endif
  if (IS_ON (DBUG))
    printf ("Include file: \"%s\"\n", newname);
  /*
  * Stack the new file name, the old file pointer and the
  * old yylineno;
  */
  strcat (sfiles [morefiles].sfname, newname);
  sfiles [morefiles].sfilep = *oldfp;
  sfiles [morefiles++].syylno = *oldlno;
  yylineno = 0;
  if ((*oldfp=fopen (newname, "r")) == NULL)
    fatal1 ("Cannot open %s", newname);
}

