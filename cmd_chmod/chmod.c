/*~!chmod.c*/
/* Name:  chmod.c Part No.: _______-____r
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

#ident	"Makef4MPX $Id: chmod.c,v 1.3 2021/07/02 19:45:41 jbev Exp $"

/* $Log: chmod.c,v $
 * Revision 1.3  2021/07/02 19:45:41  jbev
 * Correct warnings for Linux.
 *
 * Revision 1.2  1995/03/14 03:53:55  jbev
 * Fix warning errors.
 *
 * Revision 1.1  1995/03/14  01:19:01  jbev
 * Initial revision
 *
 */

/*
 *  chmod [-d] [ugoa][+-=][rwxlstugo] files/[directory]
 *  change mode of files
 */

/*
 *  Note that many convolutions are necessary
 *  due to the re-use of bits between locking
 *  and setgid
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#ifndef mpx
#include <stdlib.h>
#endif

extern char *getcwd();
static char *cvtdname();
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
#else
#include <unistd.h>
#endif

static int newmode();
static int xabs();
static int who();
static int what();

#define MAXN 128

#define	USER	05700	/* user's bits */
#define	GROUP	02070	/* group's bits */
#define	OTHER	00007	/* other's bits */
#define	ALL	07777	/* all */

#define	READ	00444	/* read permit */
#define	WRITE	00222	/* write permit */
#define	EXEC	00111	/* exec permit */
#define	SETID	06000	/* set[ug]id */
#define	LOCK	02000	/* lock permit */
#define	STICKY	01000	/* sticky bit */

static char	*ms;
static struct	stat st;
static void errmsg();
static int dflag;

int main(argc, argv)
int argc;
char **argv;
{
    register int i;
    register char *p;
    int status = 0;
    int c;

    if (argc < 3) {
    	(void) fprintf(stderr, "Usage: chmod [-d] [ugoa][+-=][rwxlstugo] file/[directory] ...\n");
    	exit(2);
    }
    /* see if we are getting a directory name */
    if(*argv[1] == '-') {
    	if (argv[1][1] == 'd' || argv[1][1] == 'D') {
    	    /* we have a directory */
    	    dflag++;
    	    c = 3;
    	} else {
    	    (void) fprintf(stderr, "Usage: chmod [-d] [ugoa][+-=][rwxlstugo] file/[directory] ...\n");
    	    exit(2);
    	}
    } else {
    	/* we have a file */
    	c = 2;
    }
    for (i = c; i < argc; i++) {
    	if (dflag)
    	    p = cvtdname(argv[i]);
    	else
    	    p = cvtfname(argv[i]);
    	if (stat(p, &st) == -1) {
    	    errmsg(2, 0, "can't access %s\n", argv[i]);
    	    status = 1;
    	    continue;
    	}
    	ms = argv[c - 1];
#ifdef mpx
    	if (chmod(p, newmode(st.st_mode, p) & 0777) == -1) {
#else
    	if (chmod(p, newmode(st.st_mode, p)) == -1) {
#endif
    	    errmsg(2, 0, "can't change %s\n", argv[i]);
    	    status = 1;
    	    continue;
    	}
    }
    exit(status);
    /* NOTREACHED */
}

static int
newmode(nm, file)
unsigned int nm;
char *file;
{
    /* m contains USER|GROUP|OTHER information
       o contains +|-|= information
       b contains rwx(slt) information
     */
    register int o, m, b;
    register int lcheck, scheck, xcheck, goon;
    int om = nm;	/* save mode for file mode incompatibility return */

    if (*ms >= '0' && *ms <= '9')
    	return(xabs());
    do {
    	m = who();
    	while (o = what()) {
    	    /*
    	    this section processes permissions
    	     */
    	    b = 0;
    	    goon = 0;
    	    lcheck = scheck = xcheck = 0;
    	    switch (*ms) {
    		case 'U':
    		case 'u':
    		    b = (nm & USER) >> 6;
    		    goto dup;
    		case 'G':
    		case 'g':
    		    b = (nm & GROUP) >> 3;
    		    goto dup;
    		case 'O':
    		case 'o':
    		    b = (nm & OTHER);
    	    dup:
    		    b &= (READ|WRITE|EXEC);
    		    b |= (b << 3) | (b << 6);
    		    ms++;
    		    goon = 1;
    	    }
    	    while (goon == 0)
    		switch (*ms++) {
    		    case 'R':
    		    case 'r':
    			b |= READ;
    			continue;
    		    case 'W':
    		    case 'w':
    			b |= WRITE;
    			continue;
    		    case 'X':
    		    case 'x':
    			b |= EXEC;
    			xcheck = 1;
    			continue;
    		    case 'L':
    		    case 'l':
    			b |= LOCK;
    			m |= LOCK;
    			lcheck = 1;
    			continue;
    		    case 'S':
    		    case 's':
    			b |= SETID;
    			scheck = 1;
    			continue;
    		    case 'T':
    		    case 't':
    			b |= STICKY;
    			continue;
    		    default:
    			ms--;
    			goon = 1;
    		}

    	    b &= m;

    	    switch (o) {
    		case '+':

    		    /* is group execution requested? */
    		    if (xcheck == 1 && (b & GROUP & EXEC) == (GROUP & EXEC)) {

    			/* not locking, too! */
    			if (lcheck == 1) {
    			    errmsg(1, 3,
 "Group execution and locking not permitted together\n", (char *)0);
    			}

    			/* not if the file is already lockable */
    			if ((nm & GROUP & (LOCK | EXEC)) == LOCK) {
    			    errmsg(2, 0,
 "Group execution not permitted on %s, a lockable file\n", file);
    			    return(om);
    			}
    		    }

    		    /* is setgid on execution requested? */
    		    if (scheck == 1 && (b & GROUP & SETID) == (GROUP & SETID)) {

    			/* not locking, too! */
    			if (lcheck == 1 && (b & GROUP & EXEC) == (GROUP & EXEC)) {
    			    errmsg(1, 4,
 "Set-group-ID and locking not permitted together\n", (char *)0);
    			}

    			/* not if the file is already lockable */
    			if ((nm & GROUP & (LOCK | EXEC)) == LOCK) {
    			    errmsg(2, 0,
 "Set-group-ID not permitted on %s, a lockable file\n", file);
    			    return(om);
    			}
    		    }

    		    /* is setid on execution requested? */
    		    if (scheck == 1) {

    			/* the corresponding execution must be requested
    			 * or already set
    			 */
    			if (((nm | b) & m & EXEC & (USER | GROUP)) !=
    			  (m & EXEC & (USER | GROUP))) {
    			    errmsg(2, 0,
 "Execute permission required for set-ID on execution for %s\n", file);
    			    return(om);
    			}
    		    }

    		    /* is locking requested? */
    		    if (lcheck == 1) {

    			/* not if the file has group execution set */
    			/* NOTE: this also covers files with setgid */
    			if ((nm & GROUP & EXEC) == (GROUP & EXEC)) {
    			    errmsg(2, 0,
 "Locking not permitted on %s, a group executable file\n", file);
    			    return(om);
    			}
    		    }

    		    /* create new mode */
    		    nm |= b;
    		    break;

    		case '-':

    		    /* don't turn off locking, unless it's on */
    		    if (lcheck == 1 && scheck == 0 
    		      && (nm & GROUP & (LOCK | EXEC)) != LOCK)
    			b &= ~LOCK;

    		    /* don't turn off setgid, unless it's on */
    		    if (scheck == 1 && lcheck == 0
    		      && (nm & GROUP & (LOCK | EXEC)) == LOCK)
    			b &= ~(GROUP & SETID);

    		    /* if execution is being turned off and the corresponding
    		     * setid is not, turn setid off, too & warn the user */
    		    if (xcheck == 1 && scheck == 0
    		      && ((m & GROUP) == GROUP || (m & USER) == USER)
    		      && (nm & m & (SETID | EXEC)) == (m & (SETID | EXEC))) {
    			errmsg(2, 0,
 "Corresponding set-ID also disabled on %s since set-ID requires execute permission\n", file);
    			if ((b & USER & SETID) != (USER & SETID)
    			  && (nm & USER & (SETID | EXEC))
    			  == (m & USER & (SETID | EXEC)))
    			    b |= USER & SETID;
    			if ((b & GROUP & SETID) != (GROUP & SETID)
    			  && (nm & GROUP & (SETID | EXEC))
    			  == (m & GROUP & (SETID | EXEC)))
    			    b |= GROUP & SETID;
    		    }

    		    /* create new mode */
    		    nm &= ~b;
    		    break;

    		case '=':

    		    /* is locking requested? */
    		    if (lcheck == 1) {

    			/* not group execution, too! */
    			if ((b & GROUP & EXEC) == (GROUP & EXEC)) {
    			    errmsg(1, 3,
 "Group execution and locking not permitted together\n", (char *)0);
    			}

    			/* if the file has group execution set, turn it off! */
    			if ((m & GROUP) != GROUP) {
    			    nm &= ~(GROUP & EXEC);
    			}
    		    }

    		    /* is setid on execution requested?
    		     * the corresponding execution must be requested, too! */
    		    if (scheck == 1 && (b & EXEC & (USER | GROUP))
    		      != (m & EXEC & (USER | GROUP))) {
    			errmsg(1, 2,
 "Execute permission required for set-ID on execution\n", (char *)0);
    		    }

    		    /* create new mode */
    		    nm &= ~m;
    		    nm |= b;
    		    break;
    		}
    	    }
    	} while (*ms++ == ',');
    if (*--ms) {
    	errmsg(1, 5, "invalid mode\n", (char *)0);
    }
    return(nm);
}

static int
xabs()
{
    register int c, i;

    for ( i = 0; (c = *ms) >= '0' && c <= '7'; ms++)
    	i = (i << 3) + (c - '0');
    if (*ms) {
    	errmsg(1, 6, "invalid mode\n", (char *)0);
    }
    return(i);
}

static int
who()
{
    register int m;

    m = 0;
    for (;; ms++) switch (*ms) {
    case 'U':
    case 'u':
    	m |= USER;
    	continue;
    case 'G':
    case 'g':
    	m |= GROUP;
    	continue;
    case 'O':
    case 'o':
    	m |= OTHER;
    	continue;
    case 'A':
    case 'a':
    	m |= ALL;
    	continue;
    default:
    	if (m == 0)
    	    m = ALL;
    	return m;
    }
}

static int
what()
{
    switch (*ms) {
    	case '+':
    	case '-':
    	case '=':
    	    return *ms++;
    }
    return(0);
}

static void
errmsg(severity, code, format, file)
int severity, code;
char *format;
char *file;
{
    static char *msg[] = {
    	"",
    	"ERROR",
    	"WARNING",
    	""
    };

    (void) fprintf(stderr, "chmod: %s: ", msg[severity]);
    (void) fprintf(stderr, format, file);
    if (code != 0)
    	exit(code);
    return;
}

/* cvtdname
 * convert an arbitrary directory name to a qualified unix pathname.
 * return pointer to malloc'd name or null if error.
 */
static char *
cvtdname(path)
char *path;
{
    char *dirp, *dbuf, *retp;

    dbuf = (char *)malloc(MAXN);
#ifdef mpx
    /* make sure pathname is l/c */
    str2lc(path);
#endif
    /* get default working directory */
    dirp = getcwd(0, MAXN);
    /* see if just a name, if so add () around name */
    if (*path != '/' && *path != '@' && *path != '^' && *path != '('
      && *path != '.') {
    	/* put () around dir name to see if o.k. */
    	dbuf[0] = '(';		/* start with ( */
    	strcpy(&dbuf[1], path);	/* copy name */
    	strcat(dbuf, ")");	/* put on ) */
    	retp = pathname(dirp, dbuf);
    } else {
    	retp = pathname(dirp, path);
    }
    if (dbuf)
    	free(dbuf);
    if (dirp)
    	free(dirp);
    return(retp);
}

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

