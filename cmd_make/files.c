/*~!files.c*/
/* Name:  files.c Part No.: _______-____r
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

#ident	"@(#)make:files.c	1.0"

#include "defs.h"
#include <sys/stat.h>

#ifdef METERFILE
#include <pwd.h>
#endif

#ifdef NOAR
#include <ar.h>
#endif /* NOAR */

#ifdef mpx
#include <sys/a.out.h>
#endif

#ifndef mpx
#include <time.h>
#endif

extern int any();
extern void fatal();
extern void fatal1();

int umatch();
int amatch();

/* UNIX DEPENDENT PROCEDURES */

char archmem [256];
char archname [256]; /* name of archive library */


TIMETYPE exists (pname)
NAMEBLOCK pname;
{
  register CHARSTAR s;
  struct stat buf;
  TIMETYPE lookarch ();
  CHARSTAR filename;

  filename = pname->namep;

  if (any (filename, LPAREN))
#ifdef NOAR
    return (lookarch (filename));
#else
    return (0);
#endif /* NOAR */

  if (stat (filename, &buf) < 0)
  {
    s = findfl (filename);
    if (s != (CHARSTAR) -1)
    {
      pname->alias = copys (s);
      if (stat (pname->alias, &buf) == 0)
        return (buf.st_mtime);
    }
    return (0);
  }
  else
    return (buf.st_mtime);
}


TIMETYPE prestime ()
{
  TIMETYPE t;
  time (&t);
  return (t);
}

#ifndef MAXNAMLEN
#define MAXNAMLEN 16
#endif

FSTATIC char nbuf [MAXNAMLEN + 1];
FSTATIC CHARSTAR nbufend = &nbuf [MAXNAMLEN];

DEPBLOCK srchdir (pat, mkchain, nextdbl)
register CHARSTAR pat;	/* pattern to be matched in directory */
int mkchain;		/* nonzero if results to be remembered */
DEPBLOCK nextdbl;	/* final value for chain */
{
  DIR *dirf;
#ifdef mpx
  int i;
#endif
  CHARSTAR dirname, dirpref, endir, filepat, p;
  char temp [100];
  char fullname [100];
  CHARSTAR p1, p2;
  NAMEBLOCK q;
  DEPBLOCK thisdbl;
  DIRLL od;
  PATTERN patp;

  struct dirent *dptr;

  thisdbl = 0;

  if (mkchain == NO)
    for (patp=firstpat ; patp!=0 ; patp = patp->nextpattern)
      if (equal (pat, patp->patval))
        return (0);

  patp = ALLOC (pattern);
  patp->nextpattern = firstpat;
  firstpat = patp;
  patp->patval = copys (pat);

  endir = 0;

  for (p=pat; *p!=CNULL; ++p)
    if (*p==SLASH)
      endir = p;

  if (endir==0)
  {
    dirname = ".";
    dirpref = "";
    filepat = pat;
  }
  else
  {
    *endir = CNULL;
    dirpref = concat (pat, "/", temp);
    filepat = endir+1;
    dirname = temp;
  }
#ifdef mpx
  /* search for sys as last directory component and strip
   * for mpx
   */
  i = strlen(dirname);
  if (i > 4) {
    if((strcmp(&dirname[i-4],"sys/") == 0) ||
     (strcmp(&dirname[i-4],"SYS/") == 0))
      dirname[i-4] = 0;
  }
  if(strcmp(dirname, "./") == 0)
    dirname[1] = 0;
#endif /* mpx */

  dirf = NULL;

  for (od=firstod ; od!=0; od = od->nextopendir)
    if (equal (dirname, od->dirn))
    {
      dirf = od->dirfc;
      if (dirf != NULL) /* start over at the beginning */
#ifndef mpx
#define rewinddir(dirp) seekdir((dirp), (long)0)
#endif
        rewinddir(dirf);
      break;
    }

  if (dirf == NULL)
  {
    dirf = opendir (dirname);
    od = ALLOC (dirll);
    od->nextopendir = firstod;
    firstod = od;
    od->dirfc = dirf;
    od->dirn = copys (dirname);
#ifdef NASA_DEBUG
    printf ("Directory [%s] opened, fc [%d]\n", dirname, dirf);
#endif
  }

  if (dirf == NULL)
  {
    fprintf (stderr, "Directory %s: ", dirname);
    fatal ("Cannot open");
  }

  else for (dptr = readdir (dirf); dptr != NULL; dptr = readdir (dirf))
  {
    p1 = dptr->d_name;
    p2 = nbuf;
    while ((p2<nbufend) && (*p2++ = *p1++) !=CNULL);
    if (amatch (nbuf, filepat))
    {
      concat (dirpref, nbuf, fullname);
      if ((q=srchname (fullname)) ==0)
        q = makename (copys (fullname));
      if (mkchain)
      {
        thisdbl = ALLOC (depblock);
        thisdbl->nextdep = nextdbl;
        thisdbl->depname = q;
        nextdbl = thisdbl;
      }
    }
    };

  if (endir != 0)
    *endir = SLASH;

  return (thisdbl);
}

/* stolen from glob through find */

int amatch (s, p)
CHARSTAR s, p;
{
  register int cc, scc, k;
  int c, lc;

  scc = *s;
  lc = 077777;
  switch (c = *p)
  {

  case LSQUAR:
    k = 0;
    while ((cc = *++p))
    {
      switch (cc)
      {

      case RSQUAR:
        if (k)
          return (amatch (++s, ++p));
        else
          return (0);

      case MINUS:
        k |= ( (lc <= scc) & (scc <= (cc=p [1]) ) );
      }
      if (scc== (lc=cc))
        k++;
    }
    return (0);

  case QUESTN:
caseq:
    if (scc)
      return (amatch (++s, ++p));
    return (0);
  case STAR:
    return (umatch (s, ++p));
  case 0:
    return (!scc);
  }
  if (c==scc)
    goto caseq;
  return (0);
}

int umatch (s, p)
register CHARSTAR s, p;
{
  if (*p==0)
    return (1);
  while (*s)
    if (amatch (s++, p))
      return (1);
  return (0);
}

#ifdef METERFILE
int meteron=0; /* default: metering off */

meter (file)
CHARSTAR file;
{
  TIMETYPE tvec;
  CHARSTAR p, ctime ();
  FILE * mout;
  struct passwd *pwd, *getpwuid ();

  if (file==0 || meteron==0)
    return;

  pwd = getpwuid (getuid ());

  time (&tvec);

  if ((mout=fopen (file, "a")) != NULL)
  {
    p = ctime (&tvec);
    p [16] = CNULL;
    fprintf (mout, "User %s, %s\n", pwd->pw_name, p+4);
    fclose (mout);
  }
}
#endif

#ifdef NOAR
/* look inside archives for notations a(b) and a((b))
a(b)  is file member   b   in archive a
a((b))  is entry point  _b  in object archive a
*/

static struct ar_hdr arhead;
FILE *arfd;
long int arpos, arlen;

static struct exec objhead;

static struct nlist objentry;

int flexnames;
char *stringarea = NULL;

TIMETYPE lookarch (filename)
register CHARSTAR filename;
{
  register int i;
  CHARSTAR p, q;
  char s [256];
  int nsym, objarch;

  for (p = filename; *p!= LPAREN ; ++p)
    ;
  q = p++;

  if (*p == LPAREN)
  {
    char *temp,
      *ptemp;

    objarch = YES;
    ++p;
    ptemp = p;
    temp = copstr (archmem, "-- er, rather didn't find entry point ");
    while (*ptemp && (*ptemp != RPAREN)) {
      *temp++ = *ptemp++;
    }
    *temp = CNULL;
  }
  else
  {
    objarch = NO;
    for (i = 0; i < 127; i++)
    {
      if (p [i] == RPAREN)
      {
        i--;
        break;
      }
      archmem [i] = p [i];
    }
    archmem [++i] = 0;
  }
  *q = CNULL;
  copstr (archname, filename);
  i = openarch (filename);
  *q = LPAREN;
  if (i == -1)
    return (0);

  for (q = s ; *p!=CNULL && *p!=RPAREN ; *q++ = *p++ )
    ;

  *q = CNULL;
  while (getarch ())
  {
    if (objarch)
    {
      getobj ();
      nsym = objhead.a_syms / sizeof (objentry);
      for (i = 0; i<nsym ; ++i)
      {
        fread (&objentry, sizeof (objentry), 1, arfd);
        if ((objentry.n_type & N_EXT) &&
#ifndef mpx
          (flexnames ? !strcmp (stringarea + objentry.un.lx.strx, s) :
        !strncmp (objentry.n_name, s, 8)))
#else
          !strncmp (objentry.n_name, s, 8))
#endif
          {
          for (i = 0; i < 14; i++)
            archmem [i] = arhead.ar_name [i];
          archmem [++i] = 0;
out:
          clarch ();
          return (arhead.ar_date);
        }
      }
    }

    else if (!strncmp (arhead.ar_name, s, 14))
      goto out;
  }

  clarch ();
  return (0L);
}


clarch ()
  {
  fclose (arfd);
  if (stringarea != NULL) {
    free (stringarea);
  }
}


openarch (f)
  register CHARSTAR f;
{
  int word = 0;
  struct stat buf;

  if (stat (f, &buf) == -1)
    return (-1);
  arlen = buf.st_size;

  arfd = fopen (f, "r");
  if (arfd == NULL)
    return (-1);
  fread (&word, sizeof (word), 1, arfd);
  if (word != ARMAG)
    fatal1 ("%s is not an archive", f);
  /*
  * trick getarch() into jumping to the first archive member.
  */
  arpos = sizeof (word);
  arhead.ar_size = - (int) sizeof (arhead);
  return (0);
}



getarch ()
  {
  arpos += sizeof (arhead);
  arpos += (arhead.ar_size + 1) & ~1L;
  if (arpos >= arlen)
    return (0);
  fseek (arfd, arpos, 0);
  fread (&arhead, sizeof (arhead), 1, arfd);
  return (1);
}


getobj ()
  {
  long int skip;
  long oldposition;

  fread (&objhead, sizeof (objhead), 1, arfd);
  if (objhead.a_magic != A_MAGIC1)
    fatal1 ("%s is not an object module", arhead.ar_name);
  skip = objhead.a_text + objhead.a_data;
  skip += objhead.a_trsize + objhead.a_drsize;
#ifndef mpx
  if (objhead.a_symstrsiz > 0) { /* using flex names */
    flexnames = YES;
    oldposition = ftell (arfd);
    fseek (arfd, skip + objhead.a_syms, 1);
    if (stringarea != NULL) {
      free (stringarea);
    }
    if ((stringarea = malloc (objhead.a_symstrsiz)) == NULL) {
      fatal ("Cannot allocate memory for flex names");
    }
    fread (stringarea, 1, objhead.a_symstrsiz, arfd);
    fseek (arfd, oldposition, 0);
  }
  else { /* no flex names */
#endif
    flexnames = NO;
#ifndef mpx
  }
#endif
  fseek (arfd, skip, 1);
}
#endif /* NOAR */
