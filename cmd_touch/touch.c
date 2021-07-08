/*~!touch.c*/
/* Name:  touch.c Part No.: _______-____r
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

#ident	"@(#)make:touch.c	1.0"

#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#ifndef mpx
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#endif

int utime();

extern char *getcwd();
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
#endif

#define	dysize(A) (((A)%4)? 365: 366)
#define MAXN 128

struct stat stbuf;
int status;
int dmsize[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int isnumber();
int gpair();
char *cbp;
long timbuf, time();

int lgtime()
{
    register int i, y, t;
    int d, h, m;
    long nt;

    tzset();

    t = gpair();
    if (t < 1 || t > 12)
    	return(1);
    d = gpair();
    if (d < 1 || d > 31)
    	return(1);
    h = gpair();
    if (h == 24) {
    	h = 0;
    	d++;
    }
    m = gpair();
    if (m < 0 || m > 59)
    	return(1);
    y = gpair();
    if (y < 0) {
    	(void) time(&nt);
    	y = localtime(&nt)->tm_year;
    }
    if (*cbp == 'p')
    	h += 12;
    if (h < 0 || h > 23)
    	return(1);
    timbuf = 0;
    y += 1900;
    for (i = 1970; i < y; i++)
    	timbuf += dysize(i);
    /* Leap year */
    if (dysize(y) == 366 && t >= 3)
    	timbuf += 1;
    while (--t)
    	timbuf += dmsize[t-1];
    timbuf += (d - 1);
    timbuf *= 24;
    timbuf += h;
    timbuf *= 60;
    timbuf += m;
    timbuf *= 60;
    return(0);
}


int gpair()
{
    register int c, d;
    register char *cp;

    cp = cbp;
    if (*cp == 0)
    	return(-1);
    c = (*cp++ - '0') * 10;
    if (c < 0 || c > 100)
    	return(-1);
    if (*cp == 0)
    	return(-1);
    if ((d = *cp++ - '0') < 0 || d > 9)
    	return(-1);
    cbp = cp;
    return (c + d);
}


int main(argc, argv)
int argc;
char *argv[];
{
    register int c;
    char *ip;
    struct utbuf { 
    	long actime, modtime; 
    } times;

    int mflg = 1, aflg = 1, cflg = 0, nflg = 0, errflg = 0, optc, fd;
    extern char *optarg;
    extern int optind;

    while ((optc = getopt(argc, argv, "AaMmCc")) != EOF)
    	switch (optc) {
    	case 'M':
    	case 'm':
    	    mflg++;
    	    aflg--;
    	    break;
    	case 'A':
    	case 'a':
    	    aflg++;
    	    mflg--;
    	    break;
    	case 'C':
    	case 'c':
    	    cflg++;
    	    break;
    	case '?':
    	    errflg++;
    	}

    if (((argc - optind) < 1) || errflg) {
    	(void) fprintf(stderr, "usage: touch [-amc] [mmddhhmm[yy]] file ...\n");
    	exit(2);
    }
    status = 0;
    if (!isnumber(argv[optind]))
    	if ((aflg <= 0) || (mflg <= 0))
    	    timbuf = time((long *) 0);
    	else
    	    nflg++;
    else {
    	cbp = (char *)argv[optind++];
    	if (lgtime()) {
    	    (void) fprintf(stderr, "date: bad conversion\n");
    	    exit(2);
    	}
    	timbuf += timezone;
    	if (localtime(&timbuf)->tm_isdst)
    	    timbuf += -1 * 60 * 60;
    }
    for (c = optind; c < argc; c++) {
    	/* convert arg to a file name */
    	if((ip = cvtfname(argv[c])) == (char *)0) {
    	    fprintf(stderr, "touch: can't resolve path %s\n", argv[c]);
    	    status++;
    	    continue;
    	}
    	if (stat(ip, &stbuf)) {
    	    if (cflg) {
    	    	status++;
    	    	continue;
    	    } else if ((fd = creat (ip, 0666)) < 0) {
    	    	(void) fprintf(stderr, "touch: cannot create %s\n", argv[c]);
    	    	status++;
    	    	continue;
    	    } else {
    	    	(void) close(fd);
    	    	if (stat(ip, &stbuf)) {
    	    	    (void) fprintf(stderr, "touch: cannot stat %s\n", argv[c]);
    	    	    status++;
    	    	    continue;
    	    	}
    	    }
    	}

    	times.actime = times.modtime = timbuf;
    	if (mflg <= 0)
    	    times.modtime = stbuf.st_mtime;
    	if (aflg <= 0)
    	    times.actime = stbuf.st_atime;

    	if (utime(ip, (struct utbuf *)(nflg ? 0 : &times))) {
    	    (void) fprintf(stderr, "touch: cannot change times on %s\n",
    		argv[c]);
    	    status++;
    	    continue;
    	}
    }
    exit(status);
}


int isnumber(s)
char *s;
{
    register int c;

    while ((c = *s++))
    	if (!isdigit(c))
    	    return(0);
    return(1);
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
    		    cp = buf;	/* Don't back up beyond root */
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
            if((cp == buf) && ((*path == '@') || (*path == '^') ||
                (*path == '('))) {
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
